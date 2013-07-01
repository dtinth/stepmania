#ifndef RAGE_VECTOR4_HPP_
#define RAGE_VECTOR4_HPP_

namespace Rage
{
	struct Vector4
	{
		Vector4();
		Vector4(float, float, float, float);
        
		// casting
		operator float* ();
		operator float const * ();
        
		// member math
		Vector4& operator +=(Vector4 const &);
		Vector4& operator -=(Vector4 const &);
		Vector4& operator *=(float);
		Vector4& operator /=(float);
        
		float x;
		float y;
        float z;
        float w;
	};
    
	inline bool operator == (Vector4 const &lhs, Vector4 const &rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
	}
    
	inline bool operator != (Vector4 const &lhs, Vector4 const &rhs)
	{
		return !operator==(lhs, rhs);
	}
    
	inline Vector4 operator + (Vector4 lhs, Vector4 const &rhs)
	{
		lhs += rhs;
		return lhs;
	}
    
	inline Vector4 operator - (Vector4 lhs, Vector4 const &rhs)
	{
		lhs -= rhs;
		return lhs;
	}
    
	inline Vector4 operator * (Vector4 lhs, float rhs)
	{
		lhs *= rhs;
		return lhs;
	}
    
	inline Vector4 operator / (Vector4 lhs, float rhs)
	{
		lhs /= rhs;
		return lhs;
	}
}



#endif

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