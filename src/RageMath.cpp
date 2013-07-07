/*
 * Most of these prototypes match up with the D3DX math functions.  Take a
 * function name, replace "Rage" with "D3DX" and look it up in the D3D SDK
 * docs for details.
 */

#include "global.h"
#include "RageMath.h"
#include "RageTypes.h"
#include <float.h>

void RageVec3ClearBounds( Rage::Vector3 &mins, Rage::Vector3 &maxs )
{
	mins = Rage::Vector3( FLT_MAX, FLT_MAX, FLT_MAX );
	maxs = mins * -1;
}

void RageVec3AddToBounds( const Rage::Vector3 &p, Rage::Vector3 &mins, Rage::Vector3 &maxs )
{
	mins.x = min( mins.x, p.x );
	mins.y = min( mins.y, p.y );
	mins.z = min( mins.z, p.z );
	maxs.x = max( maxs.x, p.x );
	maxs.y = max( maxs.y, p.y );
	maxs.z = max( maxs.z, p.z );
}

void RageVec2Normalize( Rage::Vector2* pOut, const Rage::Vector2* pV )
{
	float scale = 1.0f / sqrtf( pV->x*pV->x + pV->y*pV->y );
	pOut->x = pV->x * scale;
	pOut->y = pV->y * scale;
}

void RageVec3Normalize( Rage::Vector3* pOut, const Rage::Vector3* pV )
{
	float scale = 1.0f / sqrtf( pV->x*pV->x + pV->y*pV->y + pV->z*pV->z );
	pOut->x = pV->x * scale;
	pOut->y = pV->y * scale;
	pOut->z = pV->z * scale;
}

void RageVec3TransformCoord( Rage::Vector3* pOut, const Rage::Vector3* pV, const Rage::Matrix* pM )
{
	Rage::Vector4 temp( pV->x, pV->y, pV->z, 1.0f );	// translate
	RageVec4TransformCoord( &temp, &temp, pM );
	*pOut = Rage::Vector3( temp.x/temp.w, temp.y/temp.w, temp.z/temp.w );
}

void RageVec3TransformNormal( Rage::Vector3* pOut, const Rage::Vector3* pV, const Rage::Matrix* pM )
{
	Rage::Vector4 temp( pV->x, pV->y, pV->z, 0.0f );	// don't translate
	RageVec4TransformCoord( &temp, &temp, pM );
	*pOut = Rage::Vector3( temp.x, temp.y, temp.z );
}

#define m00 m[0][0]
#define m01 m[0][1]
#define m02 m[0][2]
#define m03 m[0][3]
#define m10 m[1][0]
#define m11 m[1][1]
#define m12 m[1][2]
#define m13 m[1][3]
#define m20 m[2][0]
#define m21 m[2][1]
#define m22 m[2][2]
#define m23 m[2][3]
#define m30 m[3][0]
#define m31 m[3][1]
#define m32 m[3][2]
#define m33 m[3][3]

void RageVec4TransformCoord( Rage::Vector4* pOut, const Rage::Vector4* pV, const Rage::Matrix* pM )
{
	const Rage::Matrix &a = *pM;
	const Rage::Vector4 &v = *pV;
	*pOut = Rage::Vector4(
		a.m00*v.x+a.m10*v.y+a.m20*v.z+a.m30*v.w,
		a.m01*v.x+a.m11*v.y+a.m21*v.z+a.m31*v.w,
		a.m02*v.x+a.m12*v.y+a.m22*v.z+a.m32*v.w,
		a.m03*v.x+a.m13*v.y+a.m23*v.z+a.m33*v.w );
}

void RageMatrixIdentity( Rage::Matrix* pOut )
{
	static float identity[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
	memcpy(&pOut->m00, identity, sizeof(identity));
/*	*pOut = Rage::Matrix(
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1 );
*/
}

void RageMatrixTranslation( Rage::Matrix* pOut, float x, float y, float z )
{
	RageMatrixIdentity(pOut);
	pOut->m[3][0] = x;
	pOut->m[3][1] = y;
	pOut->m[3][2] = z;
}

void RageMatrixScaling( Rage::Matrix* pOut, float x, float y, float z )
{
	RageMatrixIdentity(pOut);
	pOut->m[0][0] = x;
	pOut->m[1][1] = y;
	pOut->m[2][2] = z;
}

void RageMatrixSkewX( Rage::Matrix* pOut, float fAmount )
{
	RageMatrixIdentity(pOut);
	pOut->m[1][0] = fAmount;
}

void RageMatrixSkewY( Rage::Matrix* pOut, float fAmount )
{
	RageMatrixIdentity(pOut);
	pOut->m[0][1] = fAmount;
}

/*
 * Return:
 *
 * Rage::Matrix translate;
 * Rage::MatrixTranslation( &translate, fTransX, fTransY, fTransZ );
 * Rage::Matrix scale;
 * Rage::MatrixScaling( &scale, fScaleX, float fScaleY, float fScaleZ );
 * Rage::MatrixMultiply( pOut, &translate, &scale );
 */
void RageMatrixTranslate( Rage::Matrix* pOut, float fTransX, float fTransY, float fTransZ )
{
	pOut->m00 = 1;
	pOut->m01 = 0;
	pOut->m02 = 0;
	pOut->m03 = 0;

	pOut->m10 = 0;
	pOut->m11 = 1;
	pOut->m12 = 0;
	pOut->m13 = 0;

	pOut->m20 = 0;
	pOut->m21 = 0;
	pOut->m22 = 1;
	pOut->m23 = 0;

	pOut->m30 = fTransX;
	pOut->m31 = fTransY;
	pOut->m32 = fTransZ;
	pOut->m33 = 1;
}

void RageMatrixScale( Rage::Matrix* pOut, float fScaleX, float fScaleY, float fScaleZ )
{
	pOut->m00 = fScaleX;
	pOut->m01 = 0;
	pOut->m02 = 0;
	pOut->m03 = 0;

	pOut->m10 = 0;
	pOut->m11 = fScaleY;
	pOut->m12 = 0;
	pOut->m13 = 0;

	pOut->m20 = 0;
	pOut->m21 = 0;
	pOut->m22 = fScaleZ;
	pOut->m23 = 0;

	pOut->m30 = 0;
	pOut->m31 = 0;
	pOut->m32 = 0;
	pOut->m33 = 1;
}

void RageMatrixRotationX( Rage::Matrix* pOut, float theta )
{
	theta *= PI/180;

	RageMatrixIdentity(pOut);
	pOut->m[1][1] = RageFastCos(theta);
	pOut->m[2][2] = pOut->m[1][1];

	pOut->m[2][1] = RageFastSin(theta);
	pOut->m[1][2] = -pOut->m[2][1];
}

void RageMatrixRotationY( Rage::Matrix* pOut, float theta )
{
	theta *= PI/180;

	RageMatrixIdentity(pOut);
	pOut->m[0][0] = RageFastCos(theta);
	pOut->m[2][2] = pOut->m[0][0];

	pOut->m[0][2] = RageFastSin(theta);
	pOut->m[2][0] = -pOut->m[0][2];
}

void RageMatrixRotationZ( Rage::Matrix* pOut, float theta )
{
	theta *= PI/180;

	RageMatrixIdentity(pOut);
	pOut->m[0][0] = RageFastCos(theta);
	pOut->m[1][1] = pOut->m[0][0];

	pOut->m[0][1] = RageFastSin(theta);
	pOut->m[1][0] = -pOut->m[0][1];
}

/* Return RageMatrixRotationX(rX) * RageMatrixRotationY(rY) * RageMatrixRotationZ(rZ)
 * quickly (without actually doing two complete matrix multiplies), by removing the
 * parts of the matrix multiplies that we know will be 0. */
void RageMatrixRotationXYZ( Rage::Matrix* pOut, float rX, float rY, float rZ )
{
	rX *= PI/180;
	rY *= PI/180;
	rZ *= PI/180;

	const float cX = RageFastCos(rX);
	const float sX = RageFastSin(rX);
	const float cY = RageFastCos(rY);
	const float sY = RageFastSin(rY);
	const float cZ = RageFastCos(rZ);
	const float sZ = RageFastSin(rZ);

	/*
	 * X*Y:
	 * Rage::Matrix(
	 *	cY,  sY*sX, sY*cX, 0,
	 *	0,   cX,    -sX,   0,
	 *	-sY, cY*sX, cY*cX, 0,
	 *	0, 0, 0, 1
	 * );
	 *
	 * X*Y*Z:
	 *
	 * Rage::Matrix(
	 *	cZ*cY, cZ*sY*sX+sZ*cX, cZ*sY*cX+sZ*(-sX), 0,
	 *	(-sZ)*cY, (-sZ)*sY*sX+cZ*cX, (-sZ)*sY*cX+cZ*(-sX), 0,
	 *	-sY, cY*sX, cY*cX, 0,
	 *	0, 0, 0, 1
	 * );
	 */

	pOut->m00 = cZ*cY;
	pOut->m01 = cZ*sY*sX+sZ*cX;
	pOut->m02 = cZ*sY*cX+sZ*(-sX);
	pOut->m03 = 0;
	pOut->m10 = (-sZ)*cY;
	pOut->m11 = (-sZ)*sY*sX+cZ*cX;
	pOut->m12 = (-sZ)*sY*cX+cZ*(-sX);
	pOut->m13 = 0;
	pOut->m20 = -sY;
	pOut->m21 = cY*sX;
	pOut->m22 = cY*cX;
	pOut->m23 = 0;
	pOut->m30 = 0;
	pOut->m31 = 0;
	pOut->m32 = 0;
	pOut->m33 = 1;
}

void RageQuatMultiply( Rage::Vector4* pOut, const Rage::Vector4 &pA, const Rage::Vector4 &pB )
{
	Rage::Vector4 out;
	out.x = pA.w * pB.x + pA.x * pB.w + pA.y * pB.z - pA.z * pB.y;
	out.y = pA.w * pB.y + pA.y * pB.w + pA.z * pB.x - pA.x * pB.z;
	out.z = pA.w * pB.z + pA.z * pB.w + pA.x * pB.y - pA.y * pB.x;
	out.w = pA.w * pB.w - pA.x * pB.x - pA.y * pB.y - pA.z * pB.z;

	float dist, square;

	square = out.x * out.x + out.y * out.y + out.z * out.z + out.w * out.w;
	
	if (square > 0.0)
		dist = 1.0f / sqrtf(square);
	else dist = 1;

	out.x *= dist;
	out.y *= dist;
	out.z *= dist;
	out.w *= dist;

	*pOut = out;
}

Rage::Vector4 RageQuatFromH(float theta )
{
	theta *= PI/180.0f;
	theta /= 2.0f;
	theta *= -1;
	const float c = RageFastCos(theta);
	const float s = RageFastSin(theta);

	return Rage::Vector4(0, s, 0, c);
}

Rage::Vector4 RageQuatFromP(float theta )
{
	theta *= PI/180.0f;
	theta /= 2.0f;
	theta *= -1;
	const float c = RageFastCos(theta);
	const float s = RageFastSin(theta);

	return Rage::Vector4(s, 0, 0, c);
}

Rage::Vector4 RageQuatFromR(float theta )
{
	theta *= PI/180.0f;
	theta /= 2.0f;
	theta *= -1;
	const float c = RageFastCos(theta);
	const float s = RageFastSin(theta);

	return Rage::Vector4(0, 0, s, c);
}


/* Math from http://www.gamasutra.com/features/19980703/quaternions_01.htm . */

/* prh.xyz -> heading, pitch, roll */
void RageQuatFromHPR(Rage::Vector4* pOut, Rage::Vector3 hpr )
{
	hpr *= PI;
	hpr /= 180.0f;
	hpr /= 2.0f;

	const float sX = RageFastSin(hpr.x);
	const float cX = RageFastCos(hpr.x);
	const float sY = RageFastSin(hpr.y);
	const float cY = RageFastCos(hpr.y);
	const float sZ = RageFastSin(hpr.z);
	const float cZ = RageFastCos(hpr.z);

	pOut->w = cX * cY * cZ + sX * sY * sZ;
	pOut->x = sX * cY * cZ - cX * sY * sZ;
	pOut->y = cX * sY * cZ + sX * cY * sZ;
	pOut->z = cX * cY * sZ - sX * sY * cZ;
}

/*
 * Screen orientatoin:  the "floor" is the XZ plane, and Y is height; in other
 * words, the screen is the XY plane and negative Z goes into it.
 */

/* prh.xyz -> pitch, roll, heading */
void RageQuatFromPRH(Rage::Vector4* pOut, Rage::Vector3 prh )
{
	prh *= PI;
	prh /= 180.0f;
	prh /= 2.0f;

	/* Set cX to the cosine of the angle we want to rotate on the X axis,
	 * and so on.  Here, hpr.z (roll) rotates on the Z axis, hpr.x (heading)
	 * on Y, and hpr.y (pitch) on X. */
	const float sX = RageFastSin(prh.y);
	const float cX = RageFastCos(prh.y);
	const float sY = RageFastSin(prh.x);
	const float cY = RageFastCos(prh.x);
	const float sZ = RageFastSin(prh.z);
	const float cZ = RageFastCos(prh.z);

	pOut->w = cX * cY * cZ + sX * sY * sZ;
	pOut->x = sX * cY * cZ - cX * sY * sZ;
	pOut->y = cX * sY * cZ + sX * cY * sZ;
	pOut->z = cX * cY * sZ - sX * sY * cZ;
}

void RageMatrixFromQuat( Rage::Matrix* pOut, const Rage::Vector4 q )
{
	float xx = q.x * (q.x + q.x);
	float xy = q.x * (q.y + q.y);
	float xz = q.x * (q.z + q.z);

	float wx = q.w * (q.x + q.x);
	float wy = q.w * (q.y + q.y);
	float wz = q.w * (q.z + q.z);

	float yy = q.y * (q.y + q.y);
	float yz = q.y * (q.z + q.z);

	float zz = q.z * (q.z + q.z);
	// careful.  The param order is row-major, which is the 
	// transpose of the order shown in the OpenGL docs.
	*pOut = Rage::Matrix(
		1-(yy+zz), xy+wz,     xz-wy,     0,
		xy-wz,     1-(xx+zz), yz+wx,     0,
		xz+wy,     yz-wx,     1-(xx+yy), 0,
		0,         0,         0,         1 );
}

void RageQuatSlerp(Rage::Vector4 *pOut, const Rage::Vector4 &from, const Rage::Vector4 &to, float t)
{
	float to1[4];

	// calc cosine
	float cosom = from.x * to.x + from.y * to.y + from.z * to.z + from.w * to.w;

	// adjust signs (if necessary)
	if ( cosom < 0 )
	{
		cosom = -cosom;
		to1[0] = - to.x;
		to1[1] = - to.y;
		to1[2] = - to.z;
		to1[3] = - to.w;
	}
	else
	{
		to1[0] = to.x;
		to1[1] = to.y;
		to1[2] = to.z;
		to1[3] = to.w;
	}

	// calculate coefficients
	float scale0, scale1;
	if ( cosom < 0.9999f )
	{
		// standard case (slerp)
		float omega = acosf(cosom);
		float sinom = RageFastSin(omega);
		scale0 = RageFastSin((1.0f - t) * omega) / sinom;
		scale1 = RageFastSin(t * omega) / sinom;
	}
	else
	{
		// "from" and "to" quaternions are very close 
		//  ... so we can do a linear interpolation
		scale0 = 1.0f - t;
		scale1 = t;
	}
	// calculate final values
	pOut->x = scale0 * from.x + scale1 * to1[0];
	pOut->y = scale0 * from.y + scale1 * to1[1];
	pOut->z = scale0 * from.z + scale1 * to1[2];
	pOut->w = scale0 * from.w + scale1 * to1[3];
}

Rage::Matrix RageLookAt(
	float eyex, float eyey, float eyez,
	float centerx, float centery, float centerz,
	float upx, float upy, float upz )
{
	Rage::Vector3 Z(eyex - centerx, eyey - centery, eyez - centerz);
	RageVec3Normalize(&Z, &Z);

	Rage::Vector3 Y(upx, upy, upz);

	Rage::Vector3 X(
		 Y.y * Z.z - Y.z * Z.y,
		-Y.x * Z.z + Y.z * Z.x,
		 Y.x * Z.y - Y.y * Z.x);

	Y = Rage::Vector3(
		 Z.y * X.z - Z.z * X.y,
		 -Z.x * X.z + Z.z * X.x,
		 Z.x * X.y - Z.y * X.x );

	RageVec3Normalize(&X, &X);
	RageVec3Normalize(&Y, &Y);

	Rage::Matrix mat(
		X.x, Y.x, Z.x, 0,
		X.y, Y.y, Z.y, 0,
		X.z, Y.z, Z.z, 0,
		0,    0,    0,    1 );

	Rage::Matrix mat2;
	RageMatrixTranslation(&mat2, -eyex, -eyey, -eyez);

	Rage::Matrix ret = mat * mat2;

	return ret;
}

void RageMatrixAngles( Rage::Matrix* pOut, const Rage::Vector3 &angles )
{
	const Rage::Vector3 angles_radians( angles * 2*PI / 360 );
	
	const float sy = RageFastSin( angles_radians.z );
	const float cy = RageFastCos( angles_radians.z );
	const float sp = RageFastSin( angles_radians.y );
	const float cp = RageFastCos( angles_radians.y );
	const float sr = RageFastSin( angles_radians.x );
	const float cr = RageFastCos( angles_radians.x );

	RageMatrixIdentity( pOut );


	// matrix = (Z * Y) * X
	pOut->m[0][0] = cp*cy;
	pOut->m[0][1] = cp*sy;
	pOut->m[0][2] = -sp;
	pOut->m[1][0] = sr*sp*cy+cr*-sy;
	pOut->m[1][1] = sr*sp*sy+cr*cy;
	pOut->m[1][2] = sr*cp;
	pOut->m[2][0] = (cr*sp*cy+-sr*-sy);
	pOut->m[2][1] = (cr*sp*sy+-sr*cy);
	pOut->m[2][2] = cr*cp;
}

void RageMatrixTranspose( Rage::Matrix* pOut, const Rage::Matrix* pIn )
{
	for( int i=0; i<4; i++)
		for( int j=0; j<4; j++)
			pOut->m[j][i] = pIn->m[i][j];
}

float RageFastSin( float x )
{
	// from 0 to PI
	// sizeof(table) == 4096 == one page of memory in Windows
	static float table[1024];

	static bool bInited = false;
	if( !bInited )
	{
		bInited = true;
		for( unsigned i=0; i<ARRAYLEN(table); i++ )
		{
			float z = SCALE(i,0,ARRAYLEN(table),0.0f,PI);
			table[i] = sinf(z);
		}
	}

	// optimization
	if( x == 0 )
		return 0;

	float fIndex = SCALE( x, 0.0f, PI*2, 0, ARRAYLEN(table)*2 );

	// lerp using samples from the table
	int iSampleIndex[2];
	iSampleIndex[0] = (int)floorf(fIndex);
	iSampleIndex[1] = iSampleIndex[0]+1;

	float fRemainder = fIndex - iSampleIndex[0];
	for( unsigned i=0; i<ARRAYLEN(iSampleIndex); i++ )
		iSampleIndex[i] %= ARRAYLEN(table) * 2;

	DEBUG_ASSERT( fRemainder>=0 && fRemainder<=1 );

	float fValue[ARRAYLEN(iSampleIndex)];
	for( unsigned i=0; i<ARRAYLEN(iSampleIndex); i++ )
	{
		int &iSample = iSampleIndex[i];
		float &fVal = fValue[i];

		if( iSample >= int(ARRAYLEN(table)) )	// PI <= iSample < 2*PI
		{
			// sin(x) == -sin(PI+x)
			iSample -= ARRAYLEN(table);
			DEBUG_ASSERT( iSample>=0 && iSample<int(ARRAYLEN(table)) );
			fVal = -table[iSample];
		}
		else
		{
			fVal = table[iSample];
		}
	}

	return SCALE( fRemainder, 0.0f, 1.0f, fValue[0], fValue[1] );
}

float RageFastCos( float x )
{
	return RageFastSin( x + 0.5f*PI );
}

float RageQuadratic::Evaluate( float fT ) const
{
	// optimized (m_fA * fT*fT*fT) + (m_fB * fT*fT) + (m_fC * fT) + m_fD;
	return ((m_fA*fT + m_fB)*fT + m_fC)*fT + m_fD;
}

void RageQuadratic::SetFromBezier( float fX1, float fX2, float fX3, float fX4 )
{
	m_fD = fX1;
	m_fC = 3.0f * (fX2 - fX1);
	m_fB = 3.0f * (fX3 - fX2) - m_fC;
	m_fA = fX4 - fX1 - m_fC - m_fB;
}

void RageQuadratic::GetBezier( float &fX1, float &fX2, float &fX3, float &fX4 ) const
{
	fX1 = m_fD;
	fX2 = m_fD + m_fC/3.0f;
	fX3 = m_fD + 2*m_fC/3.0f + m_fB/3.0f;
	fX4 = m_fD + m_fC + m_fB + m_fA;
}

/* Cubic polynomial interpolation.  SetFromCubicPoly(-1, 0, 1, 2); Evaluate(p) will
 * interpolate between 0 and 1. */
void RageQuadratic::SetFromCubic( float fX1, float fX2, float fX3, float fX4 )
{
	m_fA = -1.0f/6.0f*fX1 + +3.0f/6.0f*fX2 + -3.0f/6.0f*fX3 + 1.0f/6.0f*fX4;
	m_fB =  3.0f/6.0f*fX1 + -6.0f/6.0f*fX2 +  3.0f/6.0f*fX3;
	m_fC = -2.0f/6.0f*fX1 + -3.0f/6.0f*fX2 +            fX3 + -1.0f/6.0f*fX4;
	m_fD =                             fX2;
}

float RageQuadratic::GetSlope( float fT ) const
{
	return 3*m_fA*fT*fT + 2*m_fB*fT + m_fC;
}

void RageBezier2D::Evaluate( float fT, float *pX, float *pY ) const
{
	*pX = m_X.Evaluate( fT );
	*pY = m_Y.Evaluate( fT );
}

float RageBezier2D::EvaluateYFromX( float fX ) const
{
	/* Quickly approximate T using Newton-Raphelson successive optimization (see
	 * http://www.tinaja.com/text/bezmath.html).  This usually finds T within an
	 * acceptable error margin in a few steps. */
	float fT = SCALE( fX, m_X.GetBezierStart(), m_X.GetBezierEnd(), 0, 1 );
	while(1)
	{
		float fGuessedX = m_X.Evaluate( fT );
		float fError = fX-fGuessedX;

		/* If our guess is good enough, evaluate the result Y and return. */
		if( unlikely(fabsf(fError) < 0.0001f) )
			return m_Y.Evaluate( fT );

		float fSlope = m_X.GetSlope( fT );
		fT += fError/fSlope;
	}
}

void RageBezier2D::SetFromBezier(
		float fC1X, float fC1Y, float fC2X, float fC2Y,
		float fC3X, float fC3Y, float fC4X, float fC4Y )
{
	m_X.SetFromBezier( fC1X, fC2X, fC3X, fC4X );
	m_Y.SetFromBezier( fC1Y, fC2Y, fC3Y, fC4Y );
}

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
