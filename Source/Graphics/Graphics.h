//--------------------------------------------------------------------------
//
// nBody -v1.0
//
// Copyright (c) 2012, Mariusz Moczala and Tomasz Stachowiak
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// - Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// - Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the distribution.
// - Neither the name of the copyright holders nor the names of its
//   contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT
// HOLDERS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
#ifndef GRAPHICS_H
#define GRAPHICS_H
//--------------------------------------------------------------------------
#include "..\Skeleton\Skeleton.h"

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
//--------------------------------------------------------------------------
class CGraphics
{
  private:

    CGraphics();
    CGraphics(const CGraphics &);
    CGraphics & operator = (const CGraphics &);

    static CGraphics & GetInstance();

    GLUquadricObj *Quadric;


  public:

    ~CGraphics();

    static void PreInit();
    static void PostInit();
    static void PreDeinit();
    static void PostDeinit();
    static CSkeleton::ERunMode Run();
    static void Resize(int Width, int Height);
};
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
