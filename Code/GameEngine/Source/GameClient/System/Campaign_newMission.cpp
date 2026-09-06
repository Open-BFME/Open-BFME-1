// ?newMission@Campaign@@QAEPAVMission@@VAsciiString@@@Z
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?newMission@Campaign@@QAEPAVMission@@VAsciiString@@@Z:
// Code/GameEngine/Source/GameClient/System/CampaignManager.cpp
//
// Same case-insensitive linked-list replace-or-insert shape as the already
// landed Campaign::getNextMission (Campaign_getNextMission.cpp): lower-case
// the incoming key, walk m_missions comparing mission->m_name against it,
// erase+deleteInstance an existing match, then allocate/construct a fresh
// Mission, set its name, and push_back it onto the list.
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

// BFME retail lifetime view, not the Generals pool implementation.
// Mission vtable VA 0x0110F658 slot zero jumps through 0x0044534A
// to the scalar deleting destructor at 0x009BBDF0. Its flag bit 1
// calls operator delete at 0x00C81EB0 after the object destructor.
// No vtable is emitted by this TU; the retail constructor installs it.
class MissionLifetimeView
{
protected:
	virtual ~MissionLifetimeView() {}
public:
	void deleteInstance()
	{
		if (this)
			delete this;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/CampaignManager.h
class Mission : public MissionLifetimeView
{
public:
	Mission();

	AsciiString m_name;					// this+0x04
	AsciiString m_mapName;					// this+0x08
	AsciiString m_nextMission;				// this+0x0C
	AsciiString m_movieLabel;				// this+0x10
	AsciiString m_missionObjectivesLabel[5];		// this+0x14
	unsigned char m_briefingVoice[112];			// this+0x28
	AsciiString m_locationNameLabel;			// this+0x98
	AsciiString m_unitNames[3];				// this+0x9C
	Int m_voiceLength;					// this+0xA8
};

typedef _STL::list<Mission *> MissionList;
typedef MissionList::iterator MissionListIt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/CampaignManager.h
class Campaign
{
public:
	Mission *newMission(AsciiString name);

private:
	char m_slice_pad[8];					// retail this+0x00 .. +0x07, untouched
	AsciiString m_firstMission;				// this+0x08
	char m_slice_padB[0x10 - 0x0C];			// this+0x0C, untouched
	MissionList m_missions;				// this+0x10
};

Mission *Campaign::newMission( AsciiString name )
{
	MissionListIt it;
	Mission *newMission;
	it = m_missions.begin();
	name.toLower();
	while(it != m_missions.end())
	{
		Mission *mission = *it;
		if(mission->m_name.compare(name) == 0)
		{
			m_missions.erase( it );
			if (mission)
				mission->deleteInstance();
			break;
		}
		else
			++it;
	}
	newMission = new Mission;
	newMission->m_name = name;
	m_missions.push_back(newMission);
	return newMission;
}
