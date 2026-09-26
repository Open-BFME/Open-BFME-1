// cl: /DNDEBUG /DWIN32 /D_WINDOWS /DBFME_STLP_NODE_ALLOC /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

// FILE: ObjectCreationListStoreCtor.cpp //////////////////////////////////////////////////////////
// The ObjectCreationListStore constructor and the three map members it inlines.
//
// Retail's ObjectCreationList translation unit is asymmetric about the STL
// allocator: every ALLOCATION in it goes through the node free list
// (push 0x20; call 0x0082E540, which buckets by (n-1)>>3 into the array at
// 0x0130B1C0), while every DEALLOCATION goes through ??3@YAXPAX@Z at
// 0x00881EB0 with the pointer alone.  No single _STLP_USE_NEWALLOC setting
// reproduces that pair: measured over ObjectCreationList.cpp, node_alloc fixes
// these four constructors and reddens thirteen destructors, and __new_alloc
// does the reverse.  BFME evidently shipped an STLport whose
// __new_alloc::allocate was re-pointed at the node allocator and left
// out of line, which inputs/vendor/stlport/stl/_alloc.h defines inline
// (`{ return __stl_new(__n); }`) and so folds to ::operator new.
//
// Until that becomes a shim header, the allocating side lives here, compiled
// with /DBFME_STLP_NODE_ALLOC, and the deallocating side stays in
// ObjectCreationList.cpp.  Nothing else in this file is claimed.

#include "PreRTS.h"

#include "GameLogic/ObjectCreationList.h"

ObjectCreationListStore::ObjectCreationListStore()
{
}
