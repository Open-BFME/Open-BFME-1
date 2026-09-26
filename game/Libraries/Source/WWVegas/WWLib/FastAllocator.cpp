// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// FastAllocator's inline lock sites use the BFME spin-call model, not the
// reference mutex.h class whose inline-asm constructor materializes a sentry.
#include "wwstring.h"
#define MUTEX_H
#include "fastallocator.h"
#include <new.h>

// The retail allocator keeps a standalone COMDAT for this inline member.
// Taking its address in the owning TU preserves that real implementation.
typedef void *(FastAllocatorGeneral::*FastAllocatorGeneralAlloc)(unsigned int);
FastAllocatorGeneralAlloc _FastAllocatorGeneralAlloc = &FastAllocatorGeneral::Alloc;

static FastAllocatorGeneral* generalAllocator; //This general allocator will do all allocations for us.

FastAllocatorGeneral* FastAllocatorGeneral::Get_Allocator()
{
	if (!generalAllocator) {
		generalAllocator=reinterpret_cast<FastAllocatorGeneral*>(::malloc(sizeof(FastAllocatorGeneral)));

		new (generalAllocator) FastAllocatorGeneral();
	}
	return generalAllocator;
}

// ??0FastAllocatorGeneral@@ is implemented by the exact retail thunk in
// FastAllocatorGeneralCtorThunk.cpp.
