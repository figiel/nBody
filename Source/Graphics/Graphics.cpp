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
#include "Graphics.h"
#include "../World/World.h"
#include "../Math/Vector.h"
//--------------------------------------------------------------------------
CGraphics::CGraphics()
{
}
//--------------------------------------------------------------------------
CGraphics::~CGraphics()
{
}
//--------------------------------------------------------------------------
CGraphics & CGraphics::GetInstance()
{
  // Create instance of this object
  static CGraphics This;
  return This;
}
//--------------------------------------------------------------------------
void CGraphics::PreInit()
{
}
//--------------------------------------------------------------------------
void CGraphics::PostInit()
{
  // Get reference to this object
  CGraphics &This = GetInstance();

  Resize(640, 480);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_CULL_FACE);

  glClearColor(0.0, 0.0, 0.0, 1);
  glCullFace(GL_BACK);

  GLfloat _lightColor[] = { 1, 1, 1, 1 };
  GLfloat _lightPos[] = { 2, 2, 2, 1 };
  glLightfv(GL_LIGHT0, GL_AMBIENT, _lightColor);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, _lightColor);
  glLightfv(GL_LIGHT0, GL_POSITION, _lightPos);

  This.Quadric = gluNewQuadric();
}
//--------------------------------------------------------------------------
void CGraphics::PreDeinit()
{
  // Get reference to this object
  CGraphics &This = GetInstance();

  gluDeleteQuadric(This.Quadric);
}
//--------------------------------------------------------------------------
void CGraphics::PostDeinit()
{
}
//--------------------------------------------------------------------------
CSkeleton::ERunMode CGraphics::Run()
{
  // Get reference to this object
  CGraphics &This = GetInstance();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glTranslated(0, 0, -100);

  int NumberOfBodies = CWorld::GetBodiesCount();
  for(int i = 0; i < NumberOfBodies; i++)
  {
    if(i & 1)
    {
      float EAmbient[] = { 0.0215f, 0.0215f, 0.1745f, 0.55f };
      float EDiffuse[] = { 0.07568f, 0.07568f, 0.61424f, 0.55f };
      float ESpecular[] = { 0.633f, 0.633f, 0.727811f, 0.55f };
      glMaterialfv(GL_FRONT, GL_AMBIENT, EAmbient);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, EDiffuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR, ESpecular);
      glMaterialf(GL_FRONT, GL_SHININESS, 76.8f);
    }
    else
    {
      float AAmbient[] = { 0.1745f, 0.0215f, 0.0215f, 0.55f };
      float ADiffuse[] = { 0.61424f, 0.07568f, 0.07568f, 0.55f };
      float ASpecular[] = { 0.727811f, 0.633f, 0.633f, 0.55f };
      glMaterialfv(GL_FRONT, GL_AMBIENT, AAmbient);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, ADiffuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR, ASpecular);
      glMaterialf(GL_FRONT, GL_SHININESS, 76.8f);
    }

    CBody &Body = CWorld::GetBody(i);
    CVector Pos = Body.Position;
    glTranslated(Pos.x/1e6, Pos.y/1e6, Pos.z/1e6);
    gluSphere(This.Quadric, Body.Radius/1e6, 20, 20);
    glTranslated(-Pos.x/1e6, -Pos.y/1e6, -Pos.z/1e6);
  }

  // Does not need to be executen when 
  return CSkeleton::rmGoForIdle;
}
//--------------------------------------------------------------------------
void CGraphics::Resize(int Width, int Height)
{
  glViewport(0, 0, Width, Height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, (float) Width / (float) Height, 0.1, 1e6);
  glMatrixMode(GL_MODELVIEW);
}
//--------------------------------------------------------------------------
