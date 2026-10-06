// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/campaignmanagerascii /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?findLadder@LadderList@@QAEPBVLadderInfo@@ABVAsciiString@@G@Z: game/GameEngine/Source/GameNetwork/GameSpy/LadderDefs.cpp
// Open-BFME5: lift MASM dump to standalone C++ thunk.

#include "Common/AsciiString.h"

template <> inline int StringBase<char>::compare(const StringBase<char> &str) const
{
	int otherLength = str.m_data ? str.m_data->length : 0;
	const char *otherData = str.m_data ? str.m_data->data : (const char *)"";
	int length = m_data ? m_data->length : 0;
	const char *data = m_data ? m_data->data : (const char *)"";
	int result = memcmp(data, otherData, length < otherLength ? length : otherLength);
	return result ? result : length - otherLength;
}

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
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/LadderDefs.h
class LadderInfo
{
public:
	char m_pad[0x28];
	AsciiString address;
	unsigned short port;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/LadderDefs.h
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
		if (((const StringBase<char> *)&li->address)->compare(*(const StringBase<char> *)&addr) == 0 && li->port == port)
			return li;
	}

	for (LadderListNode *n = m_standardLadders->next; n != m_standardLadders; n = n->next)
	{
		LadderInfo *li = (LadderInfo *)n->value;
		if (((const StringBase<char> *)&li->address)->compare(*(const StringBase<char> *)&addr) == 0 && li->port == port)
			return li;
	}

	for (LadderListNode *n = m_localLadders->next; n != m_localLadders; n = n->next)
	{
		LadderInfo *li = (LadderInfo *)n->value;
		if (((const StringBase<char> *)&li->address)->compare(*(const StringBase<char> *)&addr) == 0 && li->port == port)
			return li;
	}

	return 0;
}
