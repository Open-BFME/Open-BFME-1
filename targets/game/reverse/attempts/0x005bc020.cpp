// ??1Campaign@@MAE@XZ
// partial score=0.82 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib
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
//
// Campaign::~Campaign, retail 0x005BC020 (186 bytes), complete through ret at
// 0x005BC0DA.  The body is the CampaignManager.cpp cleanup, with the retail
// Campaign layout from the canonical EA header.  The source view deliberately
// declares the string and Mission lifetime ABI without shallow-copy or dummy
// destructor definitions: retail calls the established AsciiString destructor
// and Mission's virtual scalar deleting destructor.
//
// Identity: the matched Campaign constructor at 0x005BBF40 installs vtable
// 0x0110F65C, and the matched named CampaignManager destructor at 0x005BC4E0
// owns the adjacent Campaign list and calls Campaign::deleteInstance().
////////////////////////////////////////////////////////////////////////////////

#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef unsigned short UnsignedShort;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/
// Include/Common/AsciiString.h.  Only the data layout is needed here; the
// lifetime declaration resolves to the established retail string destructor.
struct BfmeAsciiStringData
{
	int m_refCount;
	UnsignedShort m_length;
	UnsignedShort m_capacity;
	char m_data[1];
};

class AsciiString
{
public:
	AsciiString(const AsciiString &that);
	~AsciiString();

private:
	BfmeAsciiStringData *m_data;
};

// CampaignManager.h's Mission is a pooled polymorphic object.  The retail
// Campaign destructor uses the scalar deleting slot directly, so this view
// keeps only that proven virtual ABI and does not define a fake destructor.
class Mission
{
protected:
	virtual ~Mission();

public:
	void deleteInstance(void)
	{
		delete this;
	}
};

typedef _STL::list<Mission *> MissionList;
typedef MissionList::iterator MissionListIt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/
// Include/GameClient/CampaignManager.h.  The pool-glue vtable is represented by
// the declaration-only virtual destructor; no unused inline dtor is emitted.
class Campaign
{
public:
	AsciiString m_name;
	AsciiString m_firstMission;
	AsciiString m_campaignNameLabel;
	MissionList m_missions;
	AsciiString m_finalMovieName;

protected:
	virtual ~Campaign();
};

Campaign::~Campaign(void)
{
	Campaign *self = this;
	Mission *mission;
	MissionListIt it = self->m_missions.begin();
	while(it != self->m_missions.end())
	{
		mission = *it;
		it = self->m_missions.erase(it);
		if(mission)
			mission->deleteInstance();
	}
}
