/* Handle and provide an interface to the sound driver.  Delete sounds that
 * have been detached from their owner when they're finished playing.  Distribute Update
 * calls to all sounds. */
#include "stdafx.h"

#include "RageSoundManager.h"
#include "RageException.h"
#include "RageUtil.h"
#include "RageSound.h"
#include "RageLog.h"
#include "RageTimer.h"

#include "arch/arch.h"
#include "arch/Sound/RageSoundDriver.h"

RageSoundManager::RageSoundManager(CString drivers)
{
	driver = MakeRageSoundDriver(drivers);
	if(!driver)
		RageException::Throw("Couldn't find a sound driver that works");
}

RageSoundManager::~RageSoundManager()
{
	/* Clear any sounds that we own and havn't freed yet. */
	set<RageSound *>::iterator j = owned_sounds.begin();
	while(j != owned_sounds.end())
		delete *(j++);

	delete driver;
}

void RageSoundManager::StartMixing(RageSound *snd)
{
	driver->StartMixing(snd);
}

void RageSoundManager::StopMixing(RageSound *snd)
{
	driver->StopMixing(snd);

	/* The sound is finished, and should be deleted if it's in owned_sounds.
	 * However, this call might be *from* the sound itself, and it'd be
	 * a mess to delete it while it's on the call stack.  Instead, put it
	 * in a queue to delete, and delete it on the next update. */
	if(owned_sounds.find(snd) != owned_sounds.end()) {
		sounds_to_delete.insert(snd);
		owned_sounds.erase(snd);
	}

	map<RageSound *, FakeSound>::iterator fake = 
		fake_sounds.find(const_cast<RageSound *>(snd));
	if(fake != fake_sounds.end())
		fake_sounds.erase(fake);
}

int RageSoundManager::GetPosition(const RageSound *snd) const
{
	map<RageSound *, FakeSound>::const_iterator fake = 
		fake_sounds.find(const_cast<RageSound *>(snd));
	if(fake != fake_sounds.end())
	{
		float time_since = RageTimer::GetTimeSinceStart() - fake->second.begin;
		
		return int(time_since * 44100); // XXX
	}
	
	return driver->GetPosition(snd);
}

void RageSoundManager::Update(float delta)
{
	while(!sounds_to_delete.empty())
	{
		delete *sounds_to_delete.begin();
		sounds_to_delete.erase(sounds_to_delete.begin());
	}

	for(set<RageSound *>::iterator i = all_sounds.begin();
		i != all_sounds.end(); ++i)
		(*i)->Update(delta);

	driver->Update(delta);

	/* We keep a list of "fake" sound effects.  These are sound effects that
	 * have been requested to play, but the driver couldn't play them; usually
	 * because it's run out of sound channels.  Pretend we're playing them,
	 * since this should be uncommon. */
	{
		char buf[1024*16];
		map<RageSound *, FakeSound>::iterator j = fake_sounds.begin(),
			next = j;
		while(j != fake_sounds.end())
		{
			next++;

			RageSound *s = j->first;
			FakeSound &fake = j->second;

			int bytes = min(unsigned(delta * 44100*4), sizeof(buf));
			
			int now = int(RageTimer::GetTimeSinceStart() - fake.begin) * 44100;

			int got = s->GetPCM(buf, bytes, now);
			if(got < bytes)
				s->SoundStopped();

			j = next;
		}
	}
}

void RageSoundManager::AddFakeSound(RageSound *snd)
{
	map<RageSound *, FakeSound>::const_iterator fake = 
		fake_sounds.find(const_cast<RageSound *>(snd));

	ASSERT(fake == fake_sounds.end());
	FakeSound newfake;
	newfake.begin = RageTimer::GetTimeSinceStart();
	newfake.samples_read = 0;
	fake_sounds[snd] = newfake;
}

float RageSoundManager::GetPlayLatency() const
{
	return driver->GetPlayLatency();
}

void RageSoundManager::PlayCopy( const RageSound &snd )
{
	/* Make a copy of the sound and play it; this detaches the sound
	 * from the screen.  This has a few effects:
	 *
	 * 1. If this is called more than once, it actually plays a new
	 * copy of the sound, rather than rewinding the currently-playing
	 * one.  (This is important for keyed games.)
	 *
	 * 2. If the screen closes, the sound plays to completion.
	 *
	 * I'm not sure if copying will become a performance problem.  As a
	 * flag, we could play snd instead of a copy if snd isn't actually
	 * playing.  This would keep property 1 and lose 2, which would be
	 * fine for keyed games.  Copying a streamed sound reopens the sound;
	 * copying a prebuffered sound makes a new copy of the buffer (unless
	 * std::basic_string happens to be refcounted).  That's not too bad,
	 * but we might do five of these in the same frame ...
	 */

	RageSound *newsnd = new RageSound(snd);

	/* PlayCopy's sounds must always stop on their own. */
	newsnd->SetLooping(false);
	newsnd->SetAutoStop(true);

	/* We're responsible for freeing it. */
	owned_sounds.insert(newsnd);

	newsnd->Play();
}

void RageSoundManager::PlayOnce( CString sPath )
{
	/* We want this to start quickly, so don't try to prebuffer it. */
	RageSound *snd = new RageSound;
	snd->Load(sPath, false);

	/* We're responsible for freeing it. */
	owned_sounds.insert(snd);

	snd->Play();
}

void RageSoundManager::PlayOnceFromDir( CString sDir )
{
	if( sDir == "" )
		return;

	// make sure there's a backslash at the end of this path
	if( sDir[sDir.GetLength()-1] != '\\' )
		sDir += "\\";

	CStringArray arraySoundFiles;
	GetDirListing( sDir + "*.mp3", arraySoundFiles );
	GetDirListing( sDir + "*.wav", arraySoundFiles );
	GetDirListing( sDir + "*.ogg", arraySoundFiles );

	if( arraySoundFiles.empty() )
		return;

	int index = rand() % arraySoundFiles.size();
	PlayOnce( sDir + arraySoundFiles[index] );
}

/* Standalone helpers: */
/* The volume ranges from 0 - 128 */
#define ADJUST_VOLUME(s, v)	(s = Sint16((s*v)/SDL_MIX_MAXVOLUME))

/* Mix audio.  This is from SDL, but doesn't depend on the sound being
 * initialized.  We need higher-quality mixing; that'll probably require
 * having a 32-bit output buffer and another function to scale down to
 * 16-bit.  I don't know how to do that, though, and I can't find any
 * code; I don't even know how this is supposed to work (what should volume
 * be to mix an arbitrary number of sounds with *equal* volume?), so XXX. */
void RageSoundManager::MixAudio(Uint8 *dst, const Uint8 *src, Uint32 len, int volume)
{
	Uint16 format = AUDIO_S16SYS;

	if ( volume == 0 )
		return;

	switch (format) {
		case AUDIO_S16LSB: {
			Sint16 src1, src2;
			int dst_sample;
			const int max_audioval = ((1<<(16-1))-1);
			const int min_audioval = -(1<<(16-1));

			len /= 2;
			while ( len-- ) {
				src1 = ((src[1])<<8|src[0]);
				ADJUST_VOLUME(src1, volume);
				src2 = ((dst[1])<<8|dst[0]);
				src += 2;
				dst_sample = src1+src2;
				if ( dst_sample > max_audioval ) {
					dst_sample = max_audioval;
				} else
				if ( dst_sample < min_audioval ) {
					dst_sample = min_audioval;
				}
				dst[0] = Uint8(dst_sample&0xFF);
				dst_sample >>= 8;
				dst[1] = Uint8(dst_sample&0xFF);
				dst += 2;
			}
		}
		break;

		case AUDIO_S16MSB: {
			Sint16 src1, src2;
			int dst_sample;
			const int max_audioval = ((1<<(16-1))-1);
			const int min_audioval = -(1<<(16-1));

			len /= 2;
			while ( len-- ) {
				src1 = ((src[0])<<8|src[1]);
				ADJUST_VOLUME(src1, volume);
				src2 = ((dst[0])<<8|dst[1]);
				src += 2;
				dst_sample = src1+src2;
				if ( dst_sample > max_audioval ) {
					dst_sample = max_audioval;
				} else
				if ( dst_sample < min_audioval ) {
					dst_sample = min_audioval;
				}
				dst[1] = Uint8(dst_sample&0xFF);
				dst_sample >>= 8;
				dst[0] = Uint8(dst_sample&0xFF);
				dst += 2;
			}
		}
		break;
	}
}
