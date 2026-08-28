// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?getNextMission@Campaign@@QAEPAVMission@@PAV2@@Z: Code/GameEngine/Source/GameClient/System/CampaignManager.cpp
// Open-BFME: Campaign::getNextMission, retail 0x005BC270, 319 bytes.
//
// The reference's body unchanged: take the campaign's first mission name when
// asked for the start, otherwise the current mission's next-mission name;
// lower-case it; and walk the mission list for the one whose own name matches.
//
// The layout falls out of it. A mission carries its name at +0x04 and its
// next-mission name at +0x0C behind the pool object's vptr, and the campaign
// its first-mission name at +0x08 with the mission list at +0x10.
//
// The comparison is the inlined case-sensitive one this tree has landed
// several times, but here the name being searched for is a local, so its
// length and buffer are hoisted out of the loop rather than reloaded each
// iteration -- the compiler can see nothing in the loop touches it.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);

struct BfmeAsciiStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;					// this+0x04
	UnsignedShort m_pad;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(void) : m_data(0) {}
	AsciiString(const AsciiString &that);
	~AsciiString();

	AsciiString &operator=(const AsciiString &that);		// retail 0x00887C90

	void toLower(void);					// retail 0x00887DA0

	Int getLength(void) const { return m_data ? m_data->m_len : 0; }
	const char *str(void) const { return m_data ? (const char *)(m_data + 1) : ""; }

	Bool isEmpty(void) const { return m_data == 0 || m_data->m_len == 0; }

	Int compare(const AsciiString &other) const
	{
		Int lenOther = other.getLength();
		const char *pOther = other.str();
		Int lenThis = getLength();
		const char *pThis = str();
		Int shorter = lenThis < lenOther ? lenThis : lenOther;

		Int diff = memcmp(pThis, pOther, shorter);
		if (diff != 0)
			return diff;

		return lenThis - lenOther;
	}

private:
	BfmeAsciiStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/CampaignManager.h
class Mission
{
public:
	char m_bfme_vptr[4];					// this+0x00
	AsciiString m_name;					// this+0x04
	char m_bfme_map[4];					// this+0x08
	AsciiString m_nextMission;				// this+0x0C
};

typedef _STL::list<Mission *> MissionList;
typedef MissionList::iterator MissionListIt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/CampaignManager.h
class Campaign
{
public:
	Mission *getNextMission(Mission *current);

private:
	char m_slice_pad[8];					// retail this+0x00 .. +0x07, untouched
	AsciiString m_firstMission;				// this+0x08
	char m_slice_padB[0x10 - 0x0C];				// this+0x0C, untouched
	MissionList m_missions;					// this+0x10
};

Mission *Campaign::getNextMission( Mission *current)
{
	AsciiString name;
	//if passed a Null pointer, load the first mission
	if(!current)
	{
		name = m_firstMission;
	}
	else
		name = current->m_nextMission;
	name.toLower();
	MissionListIt it;
	it = m_missions.begin();
	// we've reached the end of the campaign
	if(name.isEmpty())
		return 0;
	while(it != m_missions.end())
	{
		Mission *mission = *it;
		if(mission->m_name.compare(name) == 0)
			return mission;
		++it;
	}
	return 0;
}
