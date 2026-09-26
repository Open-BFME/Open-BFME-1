// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/tunneltracker /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: CaveSystem.cpp /////////////////////////////////////////////////////////////////////////////////
// Author: Graham Smallwood July 2002
// Desc:   System responsible for keeping track of all cave systems on the map
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/GameState.h"
#include "Common/TunnelTracker.h"
#include "GameLogic/CaveSystem.h"

CaveSystem *TheCaveSystem = NULL;

// BFME's Xfer ABI differs from the Generals header used by the rest of the
// tree.  This local view keeps the three slots exercised by CaveSystem::xfer
// at their retail positions: mode at +08, version at +28, snapshot at +30,
// and unsigned-short transfer at +7C.
struct BfmeXferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class BfmeCaveXfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual Bool getXferMode();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion( BfmeXferVersion *version );
	virtual void slot11();
	virtual void xferSnapshot( void *snapshot );
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void xferUnsignedShort( UnsignedShort *value );
};

struct BfmeFormattedText
{
	char opaque[6];
};

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(
	BfmeFormattedText *result, Int tag, const char *format, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);

// ??0CaveSystem@@QAE@XZ present-unmatched
CaveSystem::CaveSystem()
{
}

// ??1CaveSystem@@UAE@XZ present-unmatched
CaveSystem::~CaveSystem()
{
}

// ?init@CaveSystem@@UAEXXZ present-unmatched
void CaveSystem::init()
{
}

// ?reset@CaveSystem@@UAEXXZ present-unmatched
void CaveSystem::reset()
{
	for( std::vector<TunnelTracker*>::iterator iter = m_tunnelTrackerVector.begin(); iter != m_tunnelTrackerVector.end(); iter++ )
	{
		TunnelTracker *currentTracker = *iter;
		if( currentTracker )// could be NULL, since we don't slide back to fill deleted entries so offsets don't shift
		{
			currentTracker->deleteInstance();
		}
	}
	m_tunnelTrackerVector.clear();
}

// ?update@CaveSystem@@UAEXXZ present-unmatched
void CaveSystem::update()
{
}

// byte-exact reconstruction: game/GameEngine/Source/GameLogic/System/CaveSystem_canSwitchIndexToIndex.cpp
// ?canSwitchIndexToIndex@CaveSystem@@QAE_NHH@Z present-unmatched
Bool CaveSystem::canSwitchIndexToIndex( Int oldIndex, Int newIndex )
{
	// When I grant permission, you need to do it.  ie call Unregister and then re-register with the new number
	TunnelTracker *oldTracker = NULL;
	TunnelTracker *newTracker = NULL;
	if( m_tunnelTrackerVector.size() > oldIndex )
	{
		oldTracker = m_tunnelTrackerVector[oldIndex];
		if( oldTracker && oldTracker->getContainCount() > 0 )
			return FALSE;// You can't switch a connection if one of the two is non empty
	}
	if( m_tunnelTrackerVector.size() > newIndex )
	{
		newTracker = m_tunnelTrackerVector[newIndex];
		if( newTracker && newTracker->getContainCount() > 0 )
			return FALSE;// You can't switch a connection if one of the two is non empty
	}

	// Both are either empty or non-existent, so go ahead.  
	// (Remember non-exist is only a valid case because you are going to do the switch now.)

	return TRUE;
}

void CaveSystem::registerNewCave( Int theIndex )
{
	Bool needToCreate = FALSE;
	if( theIndex >= m_tunnelTrackerVector.size() )
	{
		// You are new and off the edge, so I will fill NULLs up to you and then make a newTracker at that spot
		while( theIndex >= m_tunnelTrackerVector.size() )
			m_tunnelTrackerVector.push_back( NULL );

		needToCreate = TRUE;
	}
	else
	{
		// else you either exist or have existed, so I will either let things be or re-create that slot
		if( m_tunnelTrackerVector[theIndex] == NULL )
			needToCreate = TRUE;
	}

	if( needToCreate )// if true, we new theIndex is the index of a NULL to be filled
		m_tunnelTrackerVector[theIndex] = newInstance(TunnelTracker);
}

// ?unregisterCave@CaveSystem@@QAEXH@Z present-unmatched
void CaveSystem::unregisterCave( Int theIndex )
{
	// Doesn't need to do a thing.  ContainModule logic knows how to say goodbye, and a TunnelTracker
	// knows how to exist while having no entry points.
	theIndex;
}

TunnelTracker *CaveSystem::getTunnelTrackerForCaveIndex( Int theIndex )
{
	TunnelTracker *theTracker = NULL;
	if( theIndex < m_tunnelTrackerVector.size() )
	{
		theTracker = m_tunnelTrackerVector[theIndex];
	}

	DEBUG_ASSERTCRASH( theTracker != NULL, ("No one should be interested in a sub-cave that doesn't exist.") );

	return theTracker;
}

// ------------------------------------------------------------------------------------------------
/** Xfer Method
	* Version Info
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void CaveSystem::xfer( Xfer *xfer )
{
	BfmeCaveXfer *bfmeXfer = (BfmeCaveXfer *)xfer;

	{
		BfmeXferVersion version;
		version.m_version = 1;
		version.m_currentVersion = 1;
		bfmeXfer->xferVersion( &version );
	}

	// tunnel tracker size and data
	UnsignedShort count = m_tunnelTrackerVector.size();
	bfmeXfer->xferUnsignedShort( &count );
	TunnelTracker *tracker;
	if( bfmeXfer->getXferMode() )
	{
		std::vector< TunnelTracker* >::iterator it;

		for( it = m_tunnelTrackerVector.begin(); it != m_tunnelTrackerVector.end(); ++it )
		{

			// xfer data
			tracker = *it;
			bfmeXfer->xferSnapshot( tracker );

		}  // end

	}  // end if, save
	else
	{

		// the list must be empty now
		if( m_tunnelTrackerVector.empty() == FALSE )
		{
			BfmeFormattedText error;
			bfmeFormatText( &error, 5, 0 );
			_CxxThrowException( &error, (void *)0x011DFE5C );

		}  // end if

		// read each item
		for( UnsignedShort i = 0; i < count; ++i )
		{

			// allocate new tracker
			tracker = newInstance( TunnelTracker );

			// read data
			bfmeXfer->xferSnapshot( tracker );

			// put in vector
			m_tunnelTrackerVector.push_back( tracker );

		}  // end for, i

	}  // end else, laod

}  // end xfer
