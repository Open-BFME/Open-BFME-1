// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

////// NetCommandWrapperList.cpp ////////////////////////////////
// Bryan Cleveland

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// BFME de-pooled this glue: retail's per-class `operator delete(void*, MagicEnum)`
// is one 12-byte body (0x007EFFF0) that calls the CRT free IMPORT THUNK -- a
// `call rel32` into `jmp [__imp__free]` -- where ::operator delete (0x00881EB0)
// is a different function. <stdlib.h> declares free __declspec(dllimport) under
// /MD, which compiles to the `ff 15` indirect form instead, so the C-linkage
// redeclaration below is what names `_free` for the linker's thunk; it is
// namespaced so every other free() call in this TU keeps the indirect form
// retail also uses. Same TU-scoped override Team.cpp already carries.
namespace BfmePoolGlue { extern "C" void __cdecl free(void *); }
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ return MP_GLUE_ALLOCATE(ARGCLASS); } \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ BfmePoolGlue::free(p); } \
protected: \
	inline void *operator new(size_t s) { return ::operator new(s); } \
	inline void operator delete(void *p) { ::operator delete(p); } \
private: \
	virtual MemoryPool *getObjectMemoryPool() { return ARGCLASS::getClassMemoryPool(); } \
public:

#include "GameNetwork/NetCommandWrapperList.h"
#include "GameNetwork/NetPacket.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
////// NetCommandWrapperListNode ///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

NetCommandWrapperListNode::NetCommandWrapperListNode(NetWrapperCommandMsg *msg) 
{
	//Added By Sadullah Nader
	//Initializations inserted
	m_next = NULL;

	//

	m_numChunks = msg->getNumChunks();
	m_chunksPresent = NEW Bool[m_numChunks];	// pool[]ify
	m_numChunksPresent = 0;

	for (Int i = 0; i < m_numChunks; ++i) {
		m_chunksPresent[i] = FALSE;
	}

	m_dataLength = msg->getTotalDataLength();
	m_data = NEW UnsignedByte[m_dataLength];	// pool[]ify

	m_commandID = msg->getWrappedCommandID();
}

NetCommandWrapperListNode::~NetCommandWrapperListNode() {
	if (m_chunksPresent != NULL) {
		delete[] m_chunksPresent;
		m_chunksPresent = NULL;
	}

	if (m_data != NULL) {
		delete[] m_data;
		m_data = NULL;
	}
}

Bool NetCommandWrapperListNode::isComplete() {
	return m_numChunksPresent == m_numChunks;
}

// A value of 100 means every chunk arrived. Partial transfers are capped at
// 99 even when the floating-point percentage rounds up. Retail uses the normal
// C++ x87-to-int conversion helper; no assembly escape hatch is needed.
namespace {
inline const int &wrapperPercentMin(const int &a, const int &b)
{
    return a < b ? a : b;
}
}
Int NetCommandWrapperListNode::getPercentComplete()
{
    if (m_numChunksPresent == m_numChunks)
        return 100;
    return wrapperPercentMin(99,
        static_cast<int>(static_cast<float>(m_numChunksPresent) /
                         static_cast<float>(m_numChunks) * 100.0f));
}

UnsignedShort NetCommandWrapperListNode::getCommandID() {
	return m_commandID;
}

UnsignedInt NetCommandWrapperListNode::getRawDataLength() {
	return m_dataLength;
}

void NetCommandWrapperListNode::copyChunkData(NetWrapperCommandMsg *msg) {
	if (msg == NULL) {
		DEBUG_CRASH(("Trying to copy data from a non-existent wrapper command message"));
		return;
	}

	DEBUG_ASSERTCRASH(msg->getChunkNumber() < m_numChunks, ("MunkeeChunk %d of %d\n",
		msg->getChunkNumber(), m_numChunks));
	if (msg->getChunkNumber() >= m_numChunks)
		return;

	DEBUG_LOG(("NetCommandWrapperListNode::copyChunkData() - copying chunk %d\n",
		msg->getChunkNumber()));

	if (m_chunksPresent[msg->getChunkNumber()] == TRUE) {
		// we already received this chunk, no need to recopy it.
		return;
	}

	m_chunksPresent[msg->getChunkNumber()] = TRUE;
	UnsignedInt offset = msg->getDataOffset();
	memcpy(m_data + offset, msg->getData(), msg->getDataLength());
	++m_numChunksPresent;
}

UnsignedByte * NetCommandWrapperListNode::getRawData() {
	return m_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////// NetCommandWrapperList ///////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

NetCommandWrapperList::NetCommandWrapperList() {
	m_list = NULL;
}

NetCommandWrapperList::~NetCommandWrapperList() {
	NetCommandWrapperListNode *nextNode;
	while (m_list != NULL) {
		nextNode = m_list->m_next;
		m_list->deleteInstance();
		m_list = nextNode;
	}
}

void NetCommandWrapperList::init() {
	m_list = NULL;
}

void NetCommandWrapperList::reset() {
	NetCommandWrapperListNode *nextNode;
	while (m_list != NULL) {
		nextNode = m_list->m_next;
		m_list->deleteInstance();
		m_list = nextNode;
	}
}

Int NetCommandWrapperList::getPercentComplete(UnsignedShort wrappedCommandID)
{
	NetCommandWrapperListNode *matchingNode = m_list;

	while ((matchingNode != NULL) && (matchingNode->getCommandID() != wrappedCommandID)) {
		matchingNode = matchingNode->m_next;
	}

	if (!matchingNode)
		return 0;

	return matchingNode->getPercentComplete();
}

void NetCommandWrapperList::processWrapper(NetCommandRef *ref) {
	NetCommandWrapperListNode *matchingNode = m_list;
	// BFME de-pooled NetCommandRef: the command pointer is at +0, without
	// the reference header's inherited pool/vtable field. This is getCommand().
	NetWrapperCommandMsg *msg = *(NetWrapperCommandMsg **)ref;

	while ((matchingNode != NULL) && (matchingNode->getCommandID() != msg->getWrappedCommandID())) {
		matchingNode = matchingNode->m_next;
	}

	if (matchingNode == NULL) {
		matchingNode = newInstance(NetCommandWrapperListNode)(msg);
		matchingNode->m_next = m_list;
		m_list = matchingNode;
	}

	matchingNode->copyChunkData(msg);
}

// byte-exact reconstruction: Code/GameEngine/Source/GameNetwork/NetCommandWrapperList_getReadyCommands.cpp
// ?getReadyCommands@NetCommandWrapperList@@QAEPAVNetCommandList@@XZ present-unmatched
NetCommandList * NetCommandWrapperList::getReadyCommands() 
{
	NetCommandList *retlist = newInstance(NetCommandList);
	retlist->init();

	NetCommandWrapperListNode *temp = m_list;
	NetCommandWrapperListNode *next = NULL;

	while (temp != NULL) {
		next = temp->m_next;
		if (temp->isComplete()) {
			NetCommandRef *msg = NetPacket::ConstructNetCommandMsgFromRawData(temp->getRawData(), temp->getRawDataLength());
			NetCommandRef *ret = retlist->addMessage(msg->getCommand());
			ret->setRelay(msg->getRelay());

			msg->deleteInstance();
			msg = NULL;

			removeFromList(temp);
			temp = NULL;
		}
		temp = next;
	}

	return retlist;
}

void NetCommandWrapperList::removeFromList(NetCommandWrapperListNode *node) {
	if (node == NULL) {
		return;
	}

	NetCommandWrapperListNode *currentNode = m_list;
	NetCommandWrapperListNode *previousNode = NULL;

	while ((currentNode != NULL) && (currentNode->getCommandID() != node->getCommandID())) {
		previousNode = currentNode;
		currentNode = currentNode->m_next;
	}

	if (currentNode == NULL) {
		return;
	}

	if (previousNode == NULL) {
		m_list = currentNode->m_next;
		currentNode->deleteInstance();
		currentNode = NULL;
	} else {
		previousNode->m_next = currentNode->m_next;
		currentNode->deleteInstance();
		currentNode = NULL;
	}
}
