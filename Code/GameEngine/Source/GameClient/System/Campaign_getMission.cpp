// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Campaign::getMission(AsciiString), retail 0x005BC110, complete 271-byte body.
//
// Identity is tied to the named CampaignManager::setCampaignAndMission body at
// 0x005BC9A0: its match-found path calls ILT 0x0000770C, which jumps directly
// to 0x005BC110 after storing the Campaign*; the caller then stores the returned
// Mission*. The retail body has three cleanup exits; the final found-result
// path ends with ret 4 at 0x005BC21C and padding begins at 0x005BC21F.
// The old drift inventory's 260-byte size stopped before that complete tail.
//
// The view types intentionally declare the authentic string lifetime helpers
// without shallow inline semantics.  Only the body below is reconstructed.
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
	UnsignedShort m_len;
	UnsignedShort m_pad;
};

class AsciiString
{
public:
	AsciiString(void) : m_data(0) {}
	AsciiString(const AsciiString &that);
	~AsciiString();

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

class Mission
{
public:
	char m_bfme_vptr[4];
	AsciiString m_name;
};

typedef _STL::list<Mission *> MissionList;
typedef MissionList::iterator MissionListIt;

class Campaign
{
public:
	Mission *getMission(AsciiString missionName);

private:
	char m_slice_pad[8];
	AsciiString m_firstMission;
	char m_slice_padB[0x10 - 0x0C];
	MissionList m_missions;
};

// ?getMission@Campaign@@QAEPAVMission@@VAsciiString@@@Z
Mission *Campaign::getMission( AsciiString missionName )
{
	if(missionName.isEmpty())
		return 0;

	MissionListIt it;
	it = m_missions.begin();
	while(it != m_missions.end())
	{
		Mission *mission = *it;
		if(mission->m_name.compare(missionName) == 0)
			return mission;
		++it;
	}
	return 0;
}
