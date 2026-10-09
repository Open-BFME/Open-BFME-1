// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/bfmekindof /Iinputs/reference/shims/tunneltracker /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define BFME_STLP_NODE_ALLOC 1
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
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

// FILE: TunnelTracker.cpp ///////////////////////////////////////////////////////////
// The part of a Player's brain that holds the communal Passenger list of all tunnels.
// Author: Graham Smallwood, March, 2002

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/GameState.h"
#include "Common/GlobalData.h"
#include "Common/KindOf.h"
#include "Common/TunnelTracker.h"
#include "Common/Xfer.h"

#include "GameClient/ControlBar.h"
#include "GameClient/Drawable.h"

#include "GameLogic/AI.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"

#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/TunnelContain.h"

struct Rva000F8870Node
{
	Rva000F8870Node *m_next;
	Rva000F8870Node *m_prev;
	Object *m_value;
};

void __cdecl bfmeDeallocate(void *block, unsigned int bytes);


// ------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/Common/RTS/TunnelTracker_ctor.cpp

// ------------------------------------------------------------------------
// ??1TunnelTracker@@ present-unmatched
TunnelTracker::~TunnelTracker()
{
	m_tunnelIDs.clear();
}

// ------------------------------------------------------------------------
void TunnelTracker::iterateContained( ContainIterateFunc func, void *userData, Bool reverse )
{
	if (reverse)
	{
		// note that this has to be smart enough to handle items in the list being deleted
		// via the callback function.
		for(ContainedItemsList::reverse_iterator it = m_containList.rbegin(); it != m_containList.rend(); )
		{
			// save the obj...
			Object* obj = *it;
			
			// incr the iterator BEFORE calling the func (if the func removes the obj,
			// the iterator becomes invalid)
			++it;
			
			// call it
			(*func)( obj, userData );
		}
	}
	else
	{
		// note that this has to be smart enough to handle items in the list being deleted
		// via the callback function.
		for(ContainedItemsList::iterator it = m_containList.begin(); it != m_containList.end(); )
		{
			// save the obj...
			Object* obj = *it;
			
			// incr the iterator BEFORE calling the func (if the func removes the obj,
			// the iterator becomes invalid)
			++it;
			
			// call it
			(*func)( obj, userData );
		}
	}
}

// ------------------------------------------------------------------------
// ?getContainMax@TunnelTracker@@ present-unmatched
Int TunnelTracker::getContainMax() const
{
	return TheGlobalData->m_maxTunnelCapacity;
}

// ------------------------------------------------------------------------
void TunnelTracker::updateNemesis(const Object *target)
{
	if (getCurNemesis()==NULL) {
		if (target) {
			if (target->isKindOf(KINDOF_VEHICLE) || target->isKindOf(KINDOF_STRUCTURE) ||
				target->isKindOf(KINDOF_INFANTRY) || target->isKindOf(KINDOF_AIRCRAFT)) {
					m_curNemesisID = target->getID();
					m_nemesisTimestamp = TheGameLogic->getFrame();
			}
		}
	} else if (getCurNemesis()==target) {
		m_nemesisTimestamp = TheGameLogic->getFrame();
	}
}

// ------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/Common/RTS/TunnelTrackerGetCurNemesis.cpp

// ------------------------------------------------------------------------
// ?isValidContainerFor@TunnelTracker@@ present-unmatched
Bool TunnelTracker::isValidContainerFor(const Object* obj, Bool checkCapacity) const
{
	//October 11, 2002 -- Kris : Dustin wants ALL units to be able to use tunnels!
	// srj sez: um, except aircraft. 
	if (obj && !obj->isKindOf(KINDOF_AIRCRAFT))
	{
		if (checkCapacity)
		{
			Int containMax = getContainMax();
			Int containCount = getContainCount();
			return ( containCount < containMax );
		}
		else
		{
			return true;
		}
	}
	return false;
}

// ------------------------------------------------------------------------
// ?addToContainList@TunnelTracker@@ present-unmatched
void TunnelTracker::addToContainList( Object *obj )
{
	m_containList.push_back(obj);
	++m_containListSize;
}

// ------------------------------------------------------------------------
void TunnelTracker::removeFromContain( Object *obj, Bool exposeStealthUnits )
{

	ContainedItemsList::iterator it = std::find(m_containList.begin(), m_containList.end(), obj);
	if (it != m_containList.end())
	{
		Rva000F8870Node *node = *(Rva000F8870Node **)&it;
		Rva000F8870Node *next = node->m_next;
		Rva000F8870Node *prev = node->m_prev;
		prev->m_next = next;
		next->m_prev = prev;
		bfmeDeallocate(node, 12);
		--m_containListSize;
	}	

}

// ------------------------------------------------------------------------
Bool TunnelTracker::isInContainer( Object *obj )
{
	return (std::find(m_containList.begin(), m_containList.end(), obj) != m_containList.end()) ;
}

// ------------------------------------------------------------------------
// onTunnelCreated is owned by RTS/TunnelTracker_onTunnelCreated.cpp: its
// complete 56-byte retail body at RVA 0x000F8DD0 is reached through the packed
// ILT entry 0x00038938 by BfmeConv979, BfmeConv1101 and CaveContain's genuine
// tryToSetCaveIndex tail-call path. The 48-byte reference emitter here called
// _M_create_node out of line and competed with that verified definition.

// ------------------------------------------------------------------------
// ?onTunnelDestroyed@TunnelTracker@@ present-unmatched
void TunnelTracker::onTunnelDestroyed( const Object *deadTunnel )
{
	m_tunnelCount--;
	m_tunnelIDs.remove( deadTunnel->getID() );

	if( m_tunnelCount == 0 )
	{
		// Kill everyone in our contain list.  Cave in!
		iterateContained( destroyObject, NULL, FALSE );
		m_containList.clear();
		m_containListSize = 0;
	}
	else
	{
		Object *validTunnel = TheGameLogic->findObjectByID( m_tunnelIDs.front() );
		// Otherwise, make sure nobody inside remembers the dead tunnel as the one they entered 
		// (scripts need to use so there must be something valid here)
		for(ContainedItemsList::iterator it = m_containList.begin(); it != m_containList.end(); )
		{
			Object* obj = *it;
			++it;
			if( obj->getContainedBy() == deadTunnel )
				obj->onContainedBy( validTunnel );
		}
	}
}

// ------------------------------------------------------------------------
// ?destroyObject@TunnelTracker@@ present-unmatched
void TunnelTracker::destroyObject( Object *obj, void * )
{
	// Now that tunnels consider ContainedBy to be "the tunnel you entered", I need to say goodbye
	// llike other contain types so they don't look us up on their deletion and crash
	obj->onRemovedFrom( obj->getContainedBy() );
	TheGameLogic->destroyObject( obj );
}

// ------------------------------------------------------------------------
	// heal all the objects within the tunnel system using the iterateContained function
void TunnelTracker::healObjects(Real frames)
{
	iterateContained(healObject, &frames, FALSE);
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@TunnelTracker@@ present-unmatched
void TunnelTracker::crc( Xfer *xfer )
{

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
