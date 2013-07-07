/* RageMath - vector/matrix math utilities. */

#ifndef RAGE_MATH_H
#define RAGE_MATH_H

#include "Rage/Vector2.hpp"
#include "Rage/Vector3.hpp"
#include "Rage/Vector4.hpp"
#include "Rage/Matrix.hpp"
#include "Rage/Quadratic.hpp"

#define PI		(3.141592653589793f)
#define DegreeToRadian( degree ) ((degree) * (PI / 180.0f))
#define RadianToDegree( radian ) ((radian) * (180.0f / PI))

void RageVec3ClearBounds( Rage::Vector3 &mins, Rage::Vector3 &maxs );
void RageVec3AddToBounds( const Rage::Vector3 &p, Rage::Vector3 &mins, Rage::Vector3 &maxs );

void RageVec2Normalize( Rage::Vector2* pOut, const Rage::Vector2* pV );
void RageVec3Normalize( Rage::Vector3* pOut, const Rage::Vector3* pV );
void RageVec3TransformCoord( Rage::Vector3* pOut, const Rage::Vector3* pV, const Rage::Matrix* pM );
void RageVec3TransformNormal( Rage::Vector3* pOut, const Rage::Vector3* pV, const Rage::Matrix* pM );
void RageVec4TransformCoord( Rage::Vector4* pOut, const Rage::Vector4* pV, const Rage::Matrix* pM );
void RageMatrixIdentity( Rage::Matrix* pOut );

void RageMatrixTranslation( Rage::Matrix* pOut, float x, float y, float z );
void RageMatrixScaling( Rage::Matrix* pOut, float x, float y, float z );
void RageMatrixSkewX( Rage::Matrix* pOut, float fAmount );
void RageMatrixSkewY( Rage::Matrix* pOut, float fAmount );
void RageMatrixTranslate( Rage::Matrix* pOut, float fTransX, float fTransY, float fTransZ );
void RageMatrixScale( Rage::Matrix* pOut, float fScaleX, float fScaleY, float fScaleZ );
void RageMatrixRotationX( Rage::Matrix* pOut, float fTheta );
void RageMatrixRotationY( Rage::Matrix* pOut, float fTheta );
void RageMatrixRotationZ( Rage::Matrix* pOut, float fTheta );
void RageMatrixRotationXYZ( Rage::Matrix* pOut, float rX, float rY, float rZ );
void RageQuatFromHPR(Rage::Vector4* pOut, Rage::Vector3 hpr );
void RageQuatFromPRH(Rage::Vector4* pOut, Rage::Vector3 prh );
void RageMatrixFromQuat( Rage::Matrix* pOut, const Rage::Vector4 q );
void RageQuatSlerp(Rage::Vector4 *pOut, const Rage::Vector4 &from, const Rage::Vector4 &to, float t);
Rage::Vector4 RageQuatFromH(float theta);
Rage::Vector4 RageQuatFromP(float theta);
Rage::Vector4 RageQuatFromR(float theta);
void RageQuatMultiply( Rage::Vector4* pOut, const Rage::Vector4 &pA, const Rage::Vector4 &pB );
Rage::Matrix RageLookAt(
	float eyex, float eyey, float eyez,
	float centerx, float centery, float centerz,
	float upx, float upy, float upz );
void RageMatrixAngles( Rage::Matrix* pOut, const Rage::Vector3 &angles );
void RageMatrixTranspose( Rage::Matrix* pOut, const Rage::Matrix* pIn );

float RageFastSin( float x ) CONST_FUNCTION;
float RageFastCos( float x ) CONST_FUNCTION;

class RageBezier2D
{
public:
	void SetFromBezier( float fC1X, float fC2X, float fC3X, float fC4X,
			    float fC1Y, float fC2Y, float fC3Y, float fC4Y );

	void Evaluate( float fT, float *pX, float *pY ) const;
	float EvaluateYFromX( float fX ) const;

private:
    Rage::Quadratic m_X;
    Rage::Quadratic m_Y;
};

#endif

/*
 * Copyright (c) 2001-2006 Chris Danford, Glenn Maynard
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
