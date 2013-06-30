#include "Vector2.hpp"

namespace Rage
{
	Vector2::Vector2() : x(0), y(0) {}

	Vector2::Vector2(float a, float b) : x(a), y(b) {}

	Vector2::Vector2(float const *f) : x(f[0]), y(f[1]) {}

	Vector2::Vector2(std::array<float, 2> const &f) : x(f[0]), y(f[1]) {}

	Vector2::operator float * ()
	{
		return &x;
	}

	Vector2::operator float const * ()
	{
		return &x;
	}

	Vector2& Vector2::operator+=(Vector2 const &rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}

	Vector2& Vector2::operator-=(Vector2 const &rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		return *this;
	}

	Vector2& Vector2::operator*=(float rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		return *this;
	}

	Vector2& Vector2::operator/=(float rhs)
	{
		this->x /= rhs;
		this->y /= rhs;
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