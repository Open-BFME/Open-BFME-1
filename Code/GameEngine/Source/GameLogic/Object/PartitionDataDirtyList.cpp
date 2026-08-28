// cl: /DNDEBUG /MD
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

// PartitionData::makeDirty (Code/GameEngine/Source/GameLogic/Object/ObjectFields.cpp,
// retail 0x008F7B30) calls this 31-byte body at retail 0x008F8C50 to link the
// PartitionData onto an intrusive dirty-modules list. It is defined here, in a
// sibling TU from its only caller, per docs/lessons: a definition this small
// placed in the caller's own file gets inlined by MSVC and breaks both bodies'
// matched bytes.
//
// The class/method name below is DESCRIPTIVE, not a recovered mangled identity:
// ZH's counterpart (GameEngine/Include/GameLogic/PartitionManager.h,
// PartitionData::prependToDirtyModules / PartitionManager::m_dirtyModules) takes
// the list head as a PartitionData** parameter and links via a direct
// m_prevDirty pointer to the previous node. This retail body instead reads the
// list head from a member at (container)+0x34 and gives each node an INDIRECT
// prev pointer (the address of whatever slot points at it: the head slot, or
// the previous node's next field) at node+0x14, with next at node+0x18 -- a
// different, branchless-unlink list algorithm, and the container type/offset-0
// relationship to PartitionData is unrecovered. Same role as ZH's dirty list,
// divergent implementation, so no exact upstream name applies; named on the
// same honest-descriptive precedent as ?SeedNextCommandIDFromPlayerCount@@YAXH@Z.

//-------------------------------------------------------------------------------------------------
/// PartitionData node stand-in local to this TU: only the two dirty-list link
/// fields this function touches are modeled; other members are unrecovered.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionData
{
public:
	unsigned char		_bfme_unknown0[ 0x14 ];
	PartitionData**	m_prevDirty;						///< +0x14
	PartitionData*	m_nextDirty;						///< +0x18
};

//-------------------------------------------------------------------------------------------------
/// BFME-only container for PartitionData's dirty-modules list (descriptive
/// name -- see file header comment). Interior layout before +0x34 unrecovered.
class PartitionDirtyListOwner
{
public:
	void prependDirtyModule( PartitionData* node );		///< retail 0x008F8C50

private:
	unsigned char		_bfme_unknown[ 0x34 ];
	PartitionData*	m_dirtyHead;						///< +0x34
};

//-------------------------------------------------------------------------------------------------
// ?prependDirtyModule@PartitionDirtyListOwner@@QAEXPAVPartitionData@@@Z
void PartitionDirtyListOwner::prependDirtyModule( PartitionData* node )
{
	PartitionData* oldHead = m_dirtyHead;

	node->m_nextDirty = oldHead;
	if( oldHead )
		oldHead->m_prevDirty = &node->m_nextDirty;

	node->m_prevDirty = &m_dirtyHead;
	m_dirtyHead = node;
}
