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

////// NetCommandWrapperList.h ////////////////////////////////
// Bryan Cleveland

#pragma once

#ifndef __NETCOMMANDWRAPPERLIST_H
#define __NETCOMMANDWRAPPERLIST_H

#include "GameNetwork/NetCommandList.h"

// BFME: retail dropped the MemoryPoolObject base from these wrappers. Proof:
// the node ctor @0x676380 has no SEH cleanup frame although its TU is compiled
// with EH on (processWrapper @0x676600 keeps its frame); under /EHs a ctor gets
// a cleanup frame iff the unwind must run a user-provided dtor, and
// MemoryPoolObject's inline-empty virtual dtor is user-provided. The glue macro
// still supplies both vtable slots (protected virtual dtor, getObjectMemoryPool)
// and all operators, so layout and sizeof are unchanged; deleteInstance replaces
// the inherited MemoryPoolObject member.
class NetCommandWrapperListNode
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(NetCommandWrapperListNode, "NetCommandWrapperListNode")
public:
	void deleteInstance() { delete this; }
public:
	NetCommandWrapperListNode(NetWrapperCommandMsg *msg);
	//virtual ~NetCommandWrapperListNode();

	Bool isComplete();
	UnsignedShort getCommandID();
	UnsignedInt getRawDataLength();
	void copyChunkData(NetWrapperCommandMsg *msg);
	UnsignedByte * getRawData();

	Int getPercentComplete(void);

	NetCommandWrapperListNode *m_next;

protected:
	UnsignedShort m_commandID;
	UnsignedByte *m_data;
	UnsignedInt m_dataLength;
	Bool *m_chunksPresent;
	UnsignedInt m_numChunks;
	UnsignedInt m_numChunksPresent;

};

class NetCommandWrapperList
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(NetCommandWrapperList, "NetCommandWrapperList")
public:
	void deleteInstance() { delete this; }
public:
	NetCommandWrapperList();
	//virtual ~NetCommandWrapperList();

	void init();
	void reset();

	void processWrapper(NetCommandRef *ref);
	NetCommandList * getReadyCommands();

	Int getPercentComplete(UnsignedShort wrappedCommandID);

protected:
	void removeFromList(NetCommandWrapperListNode *node);

	NetCommandWrapperListNode *m_list;
};

#endif