/* RageTypes - vector and matrix types. */

#ifndef RAGETYPES_H
#define RAGETYPES_H

#include "EnumHelper.h"
#include "Rage/Vector2.hpp"
#include "Rage/Vector3.hpp"

enum BlendMode
{
	BLEND_NORMAL,
	BLEND_ADD,
	BLEND_SUBTRACT,
	BLEND_MODULATE,
	BLEND_COPY_SRC,
	BLEND_ALPHA_MASK,
	BLEND_ALPHA_KNOCK_OUT,
	BLEND_ALPHA_MULTIPLY,
	BLEND_WEIGHTED_MULTIPLY,
	BLEND_INVERT_DEST,
	BLEND_NO_EFFECT,
	NUM_BlendMode,
	BlendMode_Invalid
};
LuaDeclareType( BlendMode );

enum TextureMode
{
	// Affects one texture stage. Texture is modulated with the diffuse color.
	TextureMode_Modulate,

	/* Affects one texture stage. Color is replaced with white, leaving alpha.
	 * Used with BLEND_ADD to add glow. */
	TextureMode_Glow,

	// Affects one texture stage. Color is added to the previous texture stage.
	TextureMode_Add,

	NUM_TextureMode,
	TextureMode_Invalid
};
LuaDeclareType( TextureMode );

enum EffectMode
{
	EffectMode_Normal,
	EffectMode_Unpremultiply,
	EffectMode_ColorBurn,
	EffectMode_ColorDodge,
	EffectMode_VividLight,
	EffectMode_HardMix,
	EffectMode_Overlay,
	EffectMode_Screen,
	EffectMode_YUYV422,
	NUM_EffectMode,
	EffectMode_Invalid
};
LuaDeclareType( EffectMode );

enum CullMode
{
	CULL_BACK,
	CULL_FRONT,
	CULL_NONE,
	NUM_CullMode,
	CullMode_Invalid
};
LuaDeclareType( CullMode );

enum ZTestMode
{
	ZTEST_OFF,
	ZTEST_WRITE_ON_PASS,
	ZTEST_WRITE_ON_FAIL,
	NUM_ZTestMode,
	ZTestMode_Invalid
};
LuaDeclareType( ZTestMode );

enum PolygonMode
{
	POLYGON_FILL,
	POLYGON_LINE,
	NUM_PolygonMode,
	PolygonMode_Invalid
};
LuaDeclareType( PolygonMode );

enum TextGlowMode
{
	TextGlowMode_Inner,
	TextGlowMode_Stroke,
	TextGlowMode_Both,
	NUM_TextGlowMode,
	TextGlowMode_Invalid
};
LuaDeclareType( TextGlowMode );

struct lua_State;

struct RageColor
{
public:
	RageColor(): r(0), g(0), b(0), a(0) {}
	explicit RageColor( const float * f ): r(f[0]), g(f[1]), b(f[2]), a(f[3]) {}
	RageColor( float r1, float g1, float b1, float a1 ): r(r1), g(g1), b(b1), a(a1) {}
	
	// casting
	operator float* ()					{ return &r; };
	operator const float* () const				{ return &r; };
	
	// assignment operators
	RageColor& operator += ( const RageColor& other )	{ r+=other.r; g+=other.g; b+=other.b; a+=other.a; return *this; }
	RageColor& operator -= ( const RageColor& other )	{ r-=other.r; g-=other.g; b-=other.b; a-=other.a; return *this; }
	RageColor& operator *= ( const RageColor& other )	{ r*=other.r; g*=other.g; b*=other.b; a*=other.a; return *this; }
	RageColor& operator *= ( float f )			{ r*=f; g*=f; b*=f; a*=f; return *this; }
	/* Divide is rarely useful: you can always use multiplication, and you don't have to
		* worry about div/0. */
	//    RageColor& operator /= ( float f )		{ r/=f; g/=f; b/=f; a/=f; return *this; }
	
	// binary operators
	RageColor operator + ( const RageColor& other ) const	{ return RageColor( r+other.r, g+other.g, b+other.b, a+other.a ); }
	RageColor operator - ( const RageColor& other ) const	{ return RageColor( r-other.r, g-other.g, b-other.b, a-other.a ); }
	RageColor operator * ( const RageColor& other ) const	{ return RageColor( r*other.r, g*other.g, b*other.b, a*other.a ); }
	RageColor operator * ( float f ) const			{ return RageColor( r*f, g*f, b*f, a*f ); }
	// Divide is useful for using with the SCALE macro
	RageColor operator / ( float f ) const			{ return RageColor( r/f, g/f, b/f, a/f ); }
	
	friend RageColor operator * ( float f, const RageColor& other )	{ return other*f; } // What is this for?  Did I add this?  -Chris
	
	bool operator == ( const RageColor& other ) const	{ return r==other.r && g==other.g && b==other.b && a==other.a; }
	bool operator != ( const RageColor& other ) const	{ return !operator==(other); }
	
	bool FromString( const RString &str )
	{
		int result = sscanf( str, "%f,%f,%f,%f", &r, &g, &b, &a );
		if( result == 3 )
		{
			a = 1;
			return true;
		}
		if( result == 4 )
			return true;
		
		int ir=255, ib=255, ig=255, ia=255;
		result = sscanf( str, "#%2x%2x%2x%2x", &ir, &ig, &ib, &ia );
		if( result >= 3 )
		{
			r = ir / 255.0f; g = ig / 255.0f; b = ib / 255.0f;
			if( result == 4 )
				a = ia / 255.0f;
			else
				a = 1;
			return true;
		}
		
		r=1; b=1; g=1; a=1;
		return false;
	}

	RString ToString() const;
	static RString NormalizeColorString( RString sColor );

	void PushTable( lua_State *L ) const;
	void FromStack( lua_State *L, int iPos );
	void FromStackCompat( lua_State *L, int iPos );

	float r, g, b, a;
} SM_ALIGN(16);

/* Convert floating-point 0..1 value to integer 0..255 value. *
 *
 * As a test case,
 *
 * int cnts[1000]; memset(cnts, 0, sizeof(cnts));
 * for( float n = 0; n <= 1.0; n += 0.0001 ) cnts[FTOC(n)]++;
 * for( int i = 0; i < 256; ++i ) printf("%i ", cnts[i]);
 *
 * should output the same value (+-1) 256 times.  If this function is
 * incorrect, the first and/or last values may be biased. */
inline unsigned char FTOC(float a)
{
        /* lfintf is much faster than C casts.  We don't care which way negative values
         * are rounded, since we'll clamp them to zero below.  Be sure to truncate (not
         * round) positive values.  The highest value that should be converted to 1 is
         * roughly (1/256 - 0.00001); if we don't truncate, values up to (1/256 + 0.5)
         * will be converted to 1, which is wrong. */
        int ret = lrintf(a*256.f - 0.5f);

        /* Benchmarking shows that clamping here, as integers, is much faster than clamping
         * before the conversion, as floats. */
        if( ret<0 ) return 0;
        else if( ret>255 ) return 255;
        else return (unsigned char) ret;
}

/* Color type used only in vertex lists.  OpenGL expects colors in
 * r, g, b, a order, independent of endianness, so storing them this
 * way avoids endianness problems.  Don't try to manipulate this; only
 * manip RageColors. */
/* Perhaps the math in RageColor could be moved to RageVColor.  We don't need the 
 * precision of a float for our calculations anyway.   -Chris */
class RageVColor
{
public:
	uint8_t b,g,r,a;	// specific ordering required by Direct3D

	RageVColor(): b(0), g(0), r(0), a(0) { }
	RageVColor(const RageColor &rc): b(0), g(0), r(0), a(0) { *this = rc; }
	RageVColor &operator= (const RageColor &rc)
	{
		r = FTOC(rc.r); g = FTOC(rc.g); b = FTOC(rc.b); a = FTOC(rc.a);
		return *this;
	}
};

namespace StepMania
{
	template <class T>
	class Rect
	{
public:
		Rect(): left(0), top(0), right(0), bottom(0) {}
		Rect(T l, T t, T r, T b): left(l), top(t), right(r), bottom(b) {}
		
		T GetWidth() const	{ return right-left; };
		T GetHeight() const	{ return bottom-top;  };
		T GetCenterX() const	{ return (left+right)/2; };
		T GetCenterY() const	{ return (top+bottom)/2; };
		
		bool operator==( const Rect &other ) const
		{
#define COMPARE( x )	if( x != other.x ) return false
			COMPARE( left );
			COMPARE( top );
			COMPARE( right );
			COMPARE( bottom );
#undef COMPARE
			return true;
		}
		bool operator!=( const Rect &other ) const { return !operator==(other); }
		
		T left, top, right, bottom;
	};
}
typedef StepMania::Rect<int> RectI;
typedef StepMania::Rect<float> RectF;

/* Structure for our custom vertex type.  Note that these data structes 
 * have the same layout that D3D expects. */
struct RageSpriteVertex	// has color
{
	RageSpriteVertex(): p(), n(), c(), t() {}
	Rage::Vector3 p; // position
	Rage::Vector3 n; // normal
	RageVColor  c; // diffuse color
	Rage::Vector2 t; // texture coordinates
};

RageColor scale( float x, float l1, float h1, const RageColor &a, const RageColor &b );

#endif

/*
 * Copyright (c) 2001-2002 Chris Danford
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, and/or sell copies of the Software, and to permit persons to
 * whom the Software is furnished to do so, provided that the above
 * copyright notice(s) and this permission notice appear in all copies of
 * the Software and that both the above copyright notice(s) and this
 * permission notice appear in supporting documentation.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF
 * THIRD PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS
 * INCLUDED IN THIS NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */
