#include "Bezier2D.hpp"
#include <cmath>
#include "Util.hpp"

namespace Rage
{
    void Bezier2D::SetFromBezier( float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4 )
    {
        x.SetFromBezier( x1, x2, x3, x4 );
        y.SetFromBezier( y1, y2, y3, y4 );
    }
    
    std::pair<float, float> Bezier2D::Evaluate(float t) const
    {
        return std::make_pair(x.Evaluate(t), x.Evaluate(t));
    }
    
    float Bezier2D::EvaluateYFromX( float fX ) const
    {
        /* Quickly approximate T using Newton-Raphelson successive optimization (see
         * http://www.tinaja.com/text/bezmath.html).  This usually finds T within an
         * acceptable error margin in a few steps. */
        float t = Scale( fX, x.GetBezierStart(), x.GetBezierEnd(), 0.f, 1.f );
        while(true)
        {
            float guessedX = x.Evaluate( t );
            float error = fX - guessedX;
            
            /* If our guess is good enough, evaluate the result Y and return. */
            if( std::abs(error) < 0.0001f )
                return y.Evaluate( t );
            
            float slope = x.GetSlope( t );
            t += error / slope;
        }
    }
}

/*
 * Copyright (c) 2001-2013 Chris Danford, Glenn Maynard
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