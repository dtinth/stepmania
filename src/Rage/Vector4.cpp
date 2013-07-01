#include "Vector4.hpp"

namespace Rage
{
	Vector4::Vector4() : x(0), y(0), z(0), w(0) {}
    
	Vector4::Vector4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
    
	Vector4::operator float * ()
	{
		return &x;
	}
    
	Vector4::operator float const * ()
	{
		return &x;
	}
    
	Vector4& Vector4::operator+=(Vector4 const &rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
        this->z += rhs.z;
        this->w += rhs.w;
		return *this;
	}
    
	Vector4& Vector4::operator-=(Vector4 const &rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
        this->z -= rhs.z;
        this->w -= rhs.w;
		return *this;
	}
    
	Vector4& Vector4::operator*=(float rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
        this->z *= rhs;
        this->w *= rhs;
		return *this;
	}
    
	Vector4& Vector4::operator/=(float rhs)
	{
		this->x /= rhs;
		this->y /= rhs;
        this->z /= rhs;
        this->w /= rhs;
		return *this;
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