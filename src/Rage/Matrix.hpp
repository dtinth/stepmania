#ifndef RAGE_MATRIX_HPP_
#define RAGE_MATRIX_HPP_

#include <array>

// Rage::Matrix elements are specified in row-major order.  This
// means that the translate terms are located in the fourth row and the
// projection terms in the fourth column.  This is consistent with the way
// MAX, Direct3D, and OpenGL all handle matrices.  Even though the OpenGL
// documentation is in column-major form, the OpenGL code is designed to
// handle matrix operations in row-major form.
namespace Rage
{
    struct Matrix
    {
    public:
        Matrix();
        
        Matrix( Matrix const&);
        Matrix( float, float, float, float,
               float, float, float, float,
               float, float, float, float,
               float, float, float, float);
        
        // access grants
        float& operator () ( int iRow, int iCol );
        float  operator () ( int iRow, int iCol ) const;
        
        // casting operators
        operator std::array<float, 4> ();
        operator std::array<float, 4> const () const;
        Matrix GetTranspose() const;
        
        std::array<std::array<float, 4>, 4> m;
    };
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