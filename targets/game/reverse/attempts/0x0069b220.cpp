// ?d_0069b220@@YAXXZ
// partial score=0.97 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
//                                                                          
//                       Westwood Studios Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2001 - All Rights Reserved                  
//                                                                          
//----------------------------------------------------------------------------
//
// Project:   RTS3
//
// File name: GameAudio.cpp
//
// Created:   5/01/01
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//         Includes                                                      
//----------------------------------------------------------------------------

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// BFME de-pooled this glue: retail's per-class `operator delete(void*, MagicEnum)`
// is one 12-byte body (0x007EFFF0) that calls the CRT free IMPORT THUNK -- a
// `call rel32` into `jmp [__imp__free]` -- where ::operator delete (0x00881EB0)
// is a different function. <stdlib.h> declares free __declspec(dllimport) under
// /MD, which compiles to the `ff 15` indirect form instead, so the C-linkage
// redeclaration below is what names `_free` for the linker's thunk; it is
// namespaced so every other free() call in this TU keeps the indirect form
// retail also uses. Same TU-scoped override Team.cpp already carries.
// Retail's pooled operator new here is 14 bytes at 0x007EFFE0 calling the
// MSVCR71 malloc import thunk at 0x009F6C34, the same shape as the delete side.
namespace BfmePoolGlue { extern "C" void __cdecl free(void *); extern "C" void *__cdecl malloc(size_t); }
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ return BfmePoolGlue::malloc(s); } \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ BfmePoolGlue::free(p); } \
protected: \
	inline void *operator new(size_t s) { return ::operator new(s); } \
	inline void operator delete(void *p) { ::operator delete(p); } \
private: \
	virtual MemoryPool *getObjectMemoryPool() { return ARGCLASS::getClassMemoryPool(); } \
public:
#include "Common/GameAudio.h"

#include "Common/AudioAffect.h"
#include "Common/AudioEventInfo.h"
#include "Common/AudioEventRTS.h"
#include "Common/AudioHandleSpecialValues.h"
#include "Common/AudioRequest.h"
#include "Common/AudioSettings.h"
#include "Common/FileSystem.h"
#include "Common/GameEngine.h"
#include "Common/GameMusic.h"
#include "Common/GameSounds.h"
#include "Common/MiscAudio.h"
#include "Common/OSDisplay.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/UserPreferences.h"

#include "GameClient/ControlBar.h"
#include "GameClient/Drawable.h"
#include "GameClient/View.h"

#include "GameLogic/GameLogic.h"
#include "GameLogic/TerrainLogic.h"

#include "WWMath/Matrix3D.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _INTERNAL
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

class Rva00589320Player;

class Rva002EE330PlayerList
{
public:
	Rva00589320Player *getLocalPlayer();
};

class Counted
{
public:
	virtual ~Counted();

	void Add_Ref()
	{
		InterlockedIncrement(&m_refCount);
	}

	void Release_Ref()
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
};

class AudioEventInfoRef
{
public:
	AudioEventInfoRef(const AudioEventInfoRef &other) : m_info(other.m_info)
	{
		if (m_info)
			m_info->Add_Ref();
	}

	~AudioEventInfoRef()
	{
		if (m_info)
			m_info->Release_Ref();
	}

	Counted *m_info;
};

class Rva0069B220
{
public:
	Bool method(const AudioEventRTS *audioEvent);
};

Bool Rva0069B220::method(const AudioEventRTS *audioEvent)
{
	if (ThePlayerList == NULL)
	return TRUE;

	Player *localPlayer = (Player *)((Rva002EE330PlayerList *)ThePlayerList)
		->getLocalPlayer();
	AudioEventInfoRef retainedInfo(*(const AudioEventInfoRef *)((const char *)audioEvent + 8));
	Counted *info = retainedInfo.m_info;
	unsigned int typeAt84 = *(unsigned int *)((char *)info + 0x84);
	if (typeAt84 == 0 || typeAt84 == 3)
		return TRUE;

	unsigned int restrictions = *(unsigned int *)((char *)info + 0x38);
	if ((restrictions & 0x1e0) == 0 || (restrictions & ST_EVERYONE) != 0)
		return TRUE;

	Player *owningPlayer = ThePlayerList->getNthPlayer(audioEvent->getPlayerIndex());
	if ((*(unsigned int *)((char *)info + 0x38) & ST_PLAYER) != 0 &&
		(*(unsigned int *)((char *)info + 0x38) & ST_UI) != 0 &&
		owningPlayer == NULL)
		return TRUE;

	if (owningPlayer == NULL || localPlayer == NULL)
		return FALSE;

	const Team *localTeam = *(Team **)((char *)localPlayer + 0x230);
	if (localTeam == NULL)
		return FALSE;

	if (owningPlayer == localPlayer)
		return (*(unsigned int *)((char *)info + 0x38) & ST_PLAYER) != 0;

	if (owningPlayer->getRelationship(localTeam) == ALLIES)
		return (*(unsigned int *)((char *)info + 0x38) & ST_ALLIES) != 0;

	return (*(unsigned int *)((char *)info + 0x38) & ST_ENEMIES) != 0;
}

//-------------------------------------------------------------------------------------------------
