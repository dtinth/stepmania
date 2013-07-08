#ifndef RAGE_QUADRATIC_HPP_
#define RAGE_QUADRATIC_HPP_

namespace Rage
{
    class Quadratic
    {
    public:
        void SetFromBezier( float, float, float, float );
        void GetBezier( float &, float &, float &, float & ) const;
        
        /* Cubic polynomial interpolation.  SetFromCubicPoly(-1, 0, 1, 2); Evaluate(p) will
         * interpolate between 0 and 1. */
        void SetFromCubic( float, float, float, float );
        
        float Evaluate( float fT ) const;
        float GetSlope( float fT ) const;
        
        /* Equivalent to Evaluate(0.0f) and Evaluate(1.0f), but faster: */
        inline float GetBezierStart() const
        {
            return d;
        }
        inline float GetBezierEnd() const
        {
            return a + b + c + d;
        }
        
    private:
        float a, b, c, d;
    };
}

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