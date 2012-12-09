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
#include "Skeleton.h"
#include "../World/World.h"
#include "../Physics/Physics.h"
#include "../Graphics/Graphics.h"
//--------------------------------------------------------------------------
CSkeleton::CSkeleton()
{
}
//--------------------------------------------------------------------------
CSkeleton::~CSkeleton()
{
}
//--------------------------------------------------------------------------
CSkeleton & CSkeleton::GetInstance()
{
  // Create instance of this object
  static CSkeleton This;
  return This;
}
//--------------------------------------------------------------------------
void CSkeleton::PreInit()
{
  // Modules pre-initialization
  CWorld::PreInit();
  CPhysics::PreInit();
  CGraphics::PreInit();
}
//--------------------------------------------------------------------------
void CSkeleton::PostInit()
{
  // Modules post-initialization
  CWorld::PostInit();
  CPhysics::PostInit();
  CGraphics::PostInit();
}
//--------------------------------------------------------------------------
void CSkeleton::PreDeinit()
{
  // Modules pre-deinitialization
  CWorld::PreDeinit();
  CPhysics::PreDeinit();
  CGraphics::PreDeinit();
}
//--------------------------------------------------------------------------
void CSkeleton::PostDeinit()
{
  // Modules post-deinitialization
  CWorld::PostDeinit();
  CPhysics::PostDeinit();
  CGraphics::PostDeinit();
}
//--------------------------------------------------------------------------
CSkeleton::ERunMode CSkeleton::Run()
{
  // By default, wait for messages before continuing processing
  ERunMode Mode, RunMode = rmGoForIdle;

  // Chose mode with highest priority of all run modes
  Mode = CWorld::Run();
  if(RunMode > Mode)
    RunMode = Mode;

  Mode = CPhysics::Run();
  if(RunMode > Mode)
    RunMode = Mode;

  Mode = CGraphics::Run();
  if(RunMode > Mode)
    RunMode = Mode;

  // Return chosen mode
  return RunMode;
}
//--------------------------------------------------------------------------
void CSkeleton::Resize(int Width, int Height)
{
  // Modules resize
  CGraphics::Resize(Width, Height);
}
//--------------------------------------------------------------------------
