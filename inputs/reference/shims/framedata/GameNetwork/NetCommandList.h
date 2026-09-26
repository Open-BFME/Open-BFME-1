#pragma once

#ifndef __NETCOMMANDLIST_H
#define __NETCOMMANDLIST_H

// TU-scoped stand-in for the real GameNetwork/NetCommandList.h. BFME dropped the
// MemoryPoolObject base from the Net* wrapper classes, so the
// ZH header's MEMORY_POOL_GLUE is wrong here in two ways: it makes operator new
// and operator delete protected, which stops FrameData::init from writing
// `new NetCommandList`, and it implies a pool free where retail plain-deletes.
// Retail's FrameData::init (0x00670170) allocates 0x10 bytes through the
// ordinary operator new, and FrameData::~FrameData (0x00670150) releases the
// list through vtable slot 0 with the deleting flag.
//
// Scoped through the same private /Ireference/shims/framedata include as
// FrameData.h -- every other TU still resolves this header to the real one.

#include "Common/GameMemory.h"
#include "GameNetwork/NetCommandRef.h"

class NetCommandList
{
public:
	NetCommandList();
	virtual ~NetCommandList();

	void init();
	void reset();
	NetCommandRef *addMessage(NetCommandMsg *cmdMsg);
	Bool isEqualCommandMsg(NetCommandMsg *msg1, NetCommandMsg *msg2);
	NetCommandRef *getFirstMessage();
	NetCommandRef *findMessage(NetCommandMsg *msg);
	NetCommandRef *findMessage(UnsignedShort commandID, UnsignedByte playerID);
	void removeMessage(NetCommandRef *msg);
	void appendList(NetCommandList *list);
	Int length();

protected:
	NetCommandRef *m_first;							// this+0x04, after the vptr
	NetCommandRef *m_last;
	NetCommandRef *m_lastMessageInserted;
};

#endif
