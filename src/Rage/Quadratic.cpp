#include "Quadratic.hpp"

namespace Rage
{
    void Quadratic::SetFromBezier( float x1, float x2, float x3, float x4 )
    {
        d = x1;
        c = 3.0f * (x2 - x1);
        b = 3.0f * (x3 - x2) - c;
        a = x4 - x1 - c - b;
    }
    
    void Quadratic::GetBezier( float &x1, float &x2, float &x3, float &x4 ) const
    {
        x1 = d;
        x2 = d + c/3.0f;
        x3 = d + 2*c/3.0f + b/3.0f;
        x4 = d + c + b + a;
    }
    
    void Quadratic::SetFromCubic( float x1, float x2, float x3, float x4 )
    {
        a = -1.0f/6.0f*x1 + +3.0f/6.0f*x2 + -3.0f/6.0f*x3 + 1.0f/6.0f*x4;
        b =  3.0f/6.0f*x1 + -6.0f/6.0f*x2 +  3.0f/6.0f*x3;
        c = -2.0f/6.0f*x1 + -3.0f/6.0f*x2 + x3 + -1.0f/6.0f*x4;
        d = x2;
    }
    
    float Quadratic::Evaluate(float t) const
    {
        if (t == 0)
        {
            return GetBezierStart();
        }
        if (t == 1)
        {
            return GetBezierEnd();
        }
        
        return (a * t * t * t) + (b * t * t) + (c * t) + d;
    }
    
    float Quadratic::GetSlope( float t ) const
    {
        return 3 * a * t * t + 2 * b * t + c;
    }
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