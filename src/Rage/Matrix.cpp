#include "Matrix.hpp"

namespace Rage
{
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
    
    Matrix::Matrix() {}
    
    Matrix::Matrix(Matrix const & other)
    {
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                this->m[j][i] = other.m[j][i];
            }
        }
    }
    
    Matrix::Matrix(float v00, float v01, float v02, float v03,
                   float v10, float v11, float v12, float v13,
                   float v20, float v21, float v22, float v23,
                   float v30, float v31, float v32, float v33)
    {
        m00=v00; m01=v01; m02=v02; m03=v03;
        m10=v10; m11=v11; m12=v12; m13=v13;
        m20=v20; m21=v21; m22=v22; m23=v23;
        m30=v30; m31=v31; m32=v32; m33=v33;
    }
    
    float& Matrix::operator () ( int iRow, int iCol )
    {
        return m[iCol][iRow];
    }
    float Matrix::operator () (int iRow, int iCol) const
    {
        return m[iCol][iRow];
    }
    
	Matrix& Matrix::operator+=(Matrix const &rhs)
	{
		this->m00 += rhs.m00;
		this->m01 += rhs.m01;
		this->m02 += rhs.m02;
		this->m03 += rhs.m03;
		this->m10 += rhs.m10;
		this->m11 += rhs.m11;
		this->m12 += rhs.m12;
		this->m13 += rhs.m13;
		this->m20 += rhs.m20;
		this->m21 += rhs.m21;
		this->m22 += rhs.m22;
		this->m23 += rhs.m23;
		this->m30 += rhs.m30;
		this->m31 += rhs.m31;
		this->m32 += rhs.m32;
		this->m33 += rhs.m33;
		return *this;
	}

	Matrix& Matrix::operator-=(Matrix const &rhs)
	{
		this->m00 -= rhs.m00;
		this->m01 -= rhs.m01;
		this->m02 -= rhs.m02;
		this->m03 -= rhs.m03;
		this->m10 -= rhs.m10;
		this->m11 -= rhs.m11;
		this->m12 -= rhs.m12;
		this->m13 -= rhs.m13;
		this->m20 -= rhs.m20;
		this->m21 -= rhs.m21;
		this->m22 -= rhs.m22;
		this->m23 -= rhs.m23;
		this->m30 -= rhs.m30;
		this->m31 -= rhs.m31;
		this->m32 -= rhs.m32;
		this->m33 -= rhs.m33;
		return *this;
	}

	Matrix& Matrix::operator*=(float rhs)
	{
		this->m00 *= rhs;
		this->m01 *= rhs;
		this->m02 *= rhs;
		this->m03 *= rhs;
		this->m10 *= rhs;
		this->m11 *= rhs;
		this->m12 *= rhs;
		this->m13 *= rhs;
		this->m20 *= rhs;
		this->m21 *= rhs;
		this->m22 *= rhs;
		this->m23 *= rhs;
		this->m30 *= rhs;
		this->m31 *= rhs;
		this->m32 *= rhs;
		this->m33 *= rhs;
		return *this;
	}

	Matrix& Matrix::operator*=(Matrix const &rhs)
	{
		Matrix lhs(*this);
		this->m00 = rhs.m00*lhs.m00+rhs.m01*lhs.m10+rhs.m02*lhs.m20+rhs.m03*lhs.m30;
		this->m01 = rhs.m00*lhs.m01+rhs.m01*lhs.m11+rhs.m02*lhs.m21+rhs.m03*lhs.m31;
		this->m02 = rhs.m00*lhs.m02+rhs.m01*lhs.m12+rhs.m02*lhs.m22+rhs.m03*lhs.m32;
		this->m03 = rhs.m00*lhs.m03+rhs.m01*lhs.m13+rhs.m02*lhs.m23+rhs.m03*lhs.m33;
		this->m10 = rhs.m10*lhs.m00+rhs.m11*lhs.m10+rhs.m12*lhs.m20+rhs.m13*lhs.m30;
		this->m11 = rhs.m10*lhs.m01+rhs.m11*lhs.m11+rhs.m12*lhs.m21+rhs.m13*lhs.m31;
		this->m12 = rhs.m10*lhs.m02+rhs.m11*lhs.m12+rhs.m12*lhs.m22+rhs.m13*lhs.m32;
		this->m13 = rhs.m10*lhs.m03+rhs.m11*lhs.m13+rhs.m12*lhs.m23+rhs.m13*lhs.m33;
		this->m20 = rhs.m20*lhs.m00+rhs.m21*lhs.m10+rhs.m22*lhs.m20+rhs.m23*lhs.m30;
		this->m21 = rhs.m20*lhs.m01+rhs.m21*lhs.m11+rhs.m22*lhs.m21+rhs.m23*lhs.m31;
		this->m22 = rhs.m20*lhs.m02+rhs.m21*lhs.m12+rhs.m22*lhs.m22+rhs.m23*lhs.m32;
		this->m23 = rhs.m20*lhs.m03+rhs.m21*lhs.m13+rhs.m22*lhs.m23+rhs.m23*lhs.m33;
		this->m30 = rhs.m30*lhs.m00+rhs.m31*lhs.m10+rhs.m32*lhs.m20+rhs.m33*lhs.m30;
		this->m31 = rhs.m30*lhs.m01+rhs.m31*lhs.m11+rhs.m32*lhs.m21+rhs.m33*lhs.m31;
		this->m32 = rhs.m30*lhs.m02+rhs.m31*lhs.m12+rhs.m32*lhs.m22+rhs.m33*lhs.m32;
		this->m33 = rhs.m30*lhs.m03+rhs.m31*lhs.m13+rhs.m32*lhs.m23+rhs.m33*lhs.m33;

		return *this;
	}
    
    Matrix::operator std::array<float, 4> ()
    {
        return m[0];
    }
    Matrix::operator std::array<float, 4> const () const
    {
        return m[0];
    }
    
    Matrix Matrix::GetTranspose() const
    {
        return Matrix(m00,m10,m20,m30,m01,m11,m21,m31,m02,m12,m22,m32,m03,m13,m23,m33);
    }

	std::ostream& operator<<(std::ostream &os, Matrix const &obj)
	{
		os << "Matrix["
			<< '[' << obj.m00 << ", " << obj.m01 << ", " << obj.m02 << ", " << obj.m03 << "], "
			<< '[' << obj.m10 << ", " << obj.m11 << ", " << obj.m12 << ", " << obj.m13 << "], "
			<< '[' << obj.m20 << ", " << obj.m21 << ", " << obj.m22 << ", " << obj.m23 << "], "
			<< '[' << obj.m30 << ", " << obj.m31 << ", " << obj.m32 << ", " << obj.m33 << "]]";
		return os;
	}
}

/*
 * Copyright (c) 2006-2013 Glenn Maynard
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