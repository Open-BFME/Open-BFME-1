// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ?findLadder@LadderList@@QAEPBVLadderInfo@@ABVAsciiString@@G@Z: Code/GameEngine/Source/GameNetwork/GameSpy/LadderDefs.cpp
// Open-BFME5: lift MASM dump to standalone C++ thunk.

#include "Common/AsciiString.h"

// Minimal doubly-linked-list node shape matching the STLport list node retail
// uses here: next@0, prev@4, value(LadderInfo*)@8. The list member itself is
// just the head/sentinel node pointer (no cached size) -- begin() is
// head->next, end() is head.
struct LadderListNode
{
	LadderListNode *next;
	LadderListNode *prev;
	void *value;
};

// Only the tail of LadderInfo that findLadder actually touches: address at
// +0x28, port at +0x2c (proven by the retail body's field offsets).
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/LadderDefs.h
class LadderInfo
{
public:
	char m_pad[0x28];
	AsciiString address;
	unsigned short port;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/LadderDefs.h
class LadderList
{
public:
	const LadderInfo *findLadder(const AsciiString &addr, unsigned short port);

private:
	LadderListNode *m_localLadders;
	LadderListNode *m_specialLadders;
	LadderListNode *m_standardLadders;
};

// ?findLadder@LadderList@@QAEPBVLadderInfo@@ABVAsciiString@@G@Z
const LadderInfo *LadderList::findLadder(const AsciiString &addr, unsigned short port)
{
	for (LadderListNode *n = m_specialLadders->next; n != m_specialLadders; n = n->next)
	{
		LadderInfo *li = (LadderInfo *)n->value;
		if (li->address.compare(addr) == 0 && li->port == port)
			return li;
	}

	for (LadderListNode *n = m_standardLadders->next; n != m_standardLadders; n = n->next)
	{
		LadderInfo *li = (LadderInfo *)n->value;
		if (li->address.compare(addr) == 0 && li->port == port)
			return li;
	}

	for (LadderListNode *n = m_localLadders->next; n != m_localLadders; n = n->next)
	{
		LadderInfo *li = (LadderInfo *)n->value;
		if (li->address.compare(addr) == 0 && li->port == port)
			return li;
	}

	return 0;
}
