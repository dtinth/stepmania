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