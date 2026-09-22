// ?garrisonAllUnits@Player@@QAEXW4CommandSourceType@@@Z
// partial score=0.9 date=2026-09-22
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DZH_EMIT_POOL_GLUE /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define PartitionFilterAcceptByKindOf BfmeCanonicalPartitionFilterAcceptByKindOf
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
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

// FILE: Player.cpp /////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Westwood Studios Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2001 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
// Project:   RTS3
//
// File name: Player.cpp
//
// Created:   Steven Johnson, October 2001
//
// Desc:      @todo
//
//-----------------------------------------------------------------------------

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#define DEFINE_SCIENCE_AVAILABILITY_NAMES

#include "Common/ActionManager.h"
#include "Common/BuildAssistant.h"
#include "Common/CRCDebug.h"
#include "Common/DisabledTypes.h"
#include "Common/GameState.h"
#include "Common/GlobalData.h"
#include "Common/MessageStream.h"
#include "Common/MiscAudio.h"
#include "Common/PerfTimer.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/PlayerTemplate.h"
#include "Common/ProductionPrerequisite.h"
#include "Common/Radar.h"
#include "Common/ResourceGatheringManager.h"
#include "Common/Team.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/TunnelTracker.h"
#include "Common/Upgrade.h"
#include "Common/WellKnownKeys.h"
#include "Common/Xfer.h"
#include "Common/BitFlagsIO.h"
#include "Common/SpecialPower.h"

#include "GameClient/ControlBar.h"
#include "GameClient/Drawable.h"
#include "GameClient/Eva.h"
#include "GameClient/GameClient.h"
#include "GameClient/GameText.h"

#include "GameLogic/AI.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/AISkirmishPlayer.h"
#include "GameLogic/ExperienceTracker.h"
#include "GameLogic/Object.h"
#include "GameLogic/Scripts.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/SidesList.h"
#include "GameLogic/Squad.h"
#include "GameLogic/RankInfo.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/Weapon.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/AutoDepositUpdate.h"
#include "GameLogic/Module/StealthUpdate.h"
#include "GameLogic/Module/SpecialPowerModule.h"
#include "GameLogic/Module/SupplyTruckAIUpdate.h"
#include "GameLogic/Module/BattlePlanUpdate.h"
#include "GameLogic/Module/ProductionUpdate.h"
#include "GameLogic/VictoryConditions.h"

#include "GameNetwork/GameInfo.h"

#undef PartitionFilterAcceptByKindOf

// +0x1a0. Both walkers below read it through this view.
// BFME's team-prototype list sits at +0x288; the vendored header lands it at
// +0x1a0. Both walkers below read it through this view.
// +0x1a0. Both walkers below read it through this view.
struct BfmePlayerTeamFields
{
	UnsignedByte m_unreconstructed_00[0x288];
	Player::PlayerTeamList m_playerTeamPrototypes;		///< retail this+0x288
};

class BfmeTeamInstanceLink
{
public:
	BfmeTeamInstanceLink *_bfme_nextInInstanceList();
};

class BfmePlayerObjectDlinkObject;

class BfmePlayerObjectVirtualTail
{
public:
	unsigned char m_vt[4];
};

class BfmePlayerObjectVbptrCarrier : public virtual BfmePlayerObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmePlayerObjectVtbl
{
public:
	virtual void bfmeObjectSlot0();
};

class BfmePlayerObjectDlinkBase
{
public:
	BfmePlayerObjectDlinkObject *dlink_next_TeamMemberList() const;
};

class BfmePlayerObjectDlinkPad
{
public:
	unsigned char m_pad[0x64];
};

class BfmePlayerObjectDlinkObject : public BfmePlayerObjectVtbl,
	public BfmePlayerObjectDlinkBase, public BfmePlayerObjectDlinkPad,
	public BfmePlayerObjectVbptrCarrier
{
public:
	unsigned char m_tail[0x40];
};

template <class ObjectType> class BfmePlayerDlinkIterator
{
public:
	typedef ObjectType *(ObjectType::*GetNextFunc)() const;

	BfmePlayerDlinkIterator(ObjectType *cur,
		GetNextFunc getNext)
		: m_cur(cur), m_getNext(getNext) { }

	Bool done() const { return m_cur == NULL; }
	ObjectType *cur() const { return m_cur; }

	void advance()
	{
		if (m_cur)
			m_cur = (m_cur->*m_getNext)();
	}

	private:
	ObjectType *m_cur;
	GetNextFunc m_getNext;
};

struct BfmePlayerTeamMemberListView
{
	unsigned char m_unmodelled_000[0x0c];
	BfmePlayerObjectDlinkObject *m_head;

	BfmePlayerDlinkIterator<BfmePlayerObjectDlinkObject> iterate() const
	{
		return BfmePlayerDlinkIterator<BfmePlayerObjectDlinkObject>(m_head,
			BfmePlayerObjectDlinkBase::dlink_next_TeamMemberList);
	}
};

class BfmePlayerTeamView
{
public:
	unsigned char m_unmodelled_000[0x0c];
	BfmePlayerObjectDlinkObject *m_head;

	BfmePlayerDlinkIterator<BfmePlayerObjectDlinkObject> iterate_TeamMemberList() const
	{
		return BfmePlayerDlinkIterator<BfmePlayerObjectDlinkObject>(m_head,
			BfmePlayerObjectDlinkBase::dlink_next_TeamMemberList);
	}
};

class BfmePlayerTeamInstanceIterator;

struct BfmePlayerTeamPrototypeInstances
{
	unsigned char m_unmodelled_000[0x274];
	BfmePlayerTeamView *m_teamInstanceList;
};

class BfmePlayerTeamInstanceIterator
{
public:
	BfmePlayerTeamInstanceIterator(BfmePlayerTeamView *head) : m_cur(head) { }

	Bool done() const { return m_cur == NULL; }
	BfmePlayerTeamView *cur() const { return m_cur; }

	void advance()
	{
		if (m_cur)
			m_cur = (BfmePlayerTeamView *)
				((BfmeTeamInstanceLink *)m_cur)->_bfme_nextInInstanceList();
	}

	private:
	BfmePlayerTeamView *m_cur;
	Int m_unmodelled;
};

struct BfmePlayerTeamListNode
{
	BfmePlayerTeamListNode *m_next;
	BfmePlayerTeamListNode *m_prev;
	BfmePlayerTeamPrototypeInstances *m_prototype;
};

typedef BitFlags<192> BfmeGarrisonKindOfMask;

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	__declspec(noinline) PartitionFilterAcceptByKindOf(
		const BfmeGarrisonKindOfMask &mustBeSet,
		const BfmeGarrisonKindOfMask &mustBeClear)
		: m_mustBeSet(mustBeSet), m_mustBeClear(mustBeClear) {}
	virtual Bool allow(Object *object);
	operator Int() const { return (Int)this; }

	BfmeGarrisonKindOfMask m_mustBeSet;
	BfmeGarrisonKindOfMask m_mustBeClear;
};

struct BfmeGarrisonResultEntry
{
	Object *m_object;
	UnsignedInt m_word04;
};

struct BfmeGarrisonResultData
{
	std::vector<BfmeGarrisonResultEntry> m_entries;
	BfmeGarrisonResultEntry *m_current;
	Int m_references;
};

struct BfmeResultA
{
	BfmeGarrisonResultData *m_value;

	BfmeResultA();
	BfmeResultA(const BfmeResultA &that);
	~BfmeResultA()
	{
		if (--m_value->m_references == 0)
			delete m_value;
	}

	Object *next(Object *&object)
	{
		if (m_value->m_current == m_value->m_entries.end())
			return NULL;
		object = (m_value->m_current++)->m_object;
		return object;
	}

	void first()
	{
		m_value->m_current = m_value->m_entries.begin();
	}
};

class BfmeResultForwardB
{
public:
	BfmeResultA bfmeForwardResultB(Int value);
};

class BfmeGarrisonContainView
{
public:
#define BFME_GARRISON_CONTAIN_SLOT(n) virtual void slot##n() = 0;
	BFME_GARRISON_CONTAIN_SLOT(00)
	BFME_GARRISON_CONTAIN_SLOT(01)
	BFME_GARRISON_CONTAIN_SLOT(02)
	BFME_GARRISON_CONTAIN_SLOT(03)
	BFME_GARRISON_CONTAIN_SLOT(04)
	BFME_GARRISON_CONTAIN_SLOT(05)
	BFME_GARRISON_CONTAIN_SLOT(06)
	BFME_GARRISON_CONTAIN_SLOT(07)
	BFME_GARRISON_CONTAIN_SLOT(08)
	BFME_GARRISON_CONTAIN_SLOT(09)
	BFME_GARRISON_CONTAIN_SLOT(10)
	BFME_GARRISON_CONTAIN_SLOT(11)
	BFME_GARRISON_CONTAIN_SLOT(12)
	BFME_GARRISON_CONTAIN_SLOT(13)
	BFME_GARRISON_CONTAIN_SLOT(14)
	BFME_GARRISON_CONTAIN_SLOT(15)
	BFME_GARRISON_CONTAIN_SLOT(16)
	BFME_GARRISON_CONTAIN_SLOT(17)
	BFME_GARRISON_CONTAIN_SLOT(18)
	BFME_GARRISON_CONTAIN_SLOT(19)
	BFME_GARRISON_CONTAIN_SLOT(20)
	BFME_GARRISON_CONTAIN_SLOT(21)
	BFME_GARRISON_CONTAIN_SLOT(22)
	BFME_GARRISON_CONTAIN_SLOT(23)
	BFME_GARRISON_CONTAIN_SLOT(24)
	BFME_GARRISON_CONTAIN_SLOT(25)
	BFME_GARRISON_CONTAIN_SLOT(26)
	BFME_GARRISON_CONTAIN_SLOT(27)
	BFME_GARRISON_CONTAIN_SLOT(28)
	BFME_GARRISON_CONTAIN_SLOT(29)
	BFME_GARRISON_CONTAIN_SLOT(30)
	BFME_GARRISON_CONTAIN_SLOT(31)
	BFME_GARRISON_CONTAIN_SLOT(32)
	BFME_GARRISON_CONTAIN_SLOT(33)
	BFME_GARRISON_CONTAIN_SLOT(34)
	BFME_GARRISON_CONTAIN_SLOT(35)
	BFME_GARRISON_CONTAIN_SLOT(36)
	BFME_GARRISON_CONTAIN_SLOT(37)
	BFME_GARRISON_CONTAIN_SLOT(38)
	BFME_GARRISON_CONTAIN_SLOT(39)
	BFME_GARRISON_CONTAIN_SLOT(40)
	BFME_GARRISON_CONTAIN_SLOT(41)
	BFME_GARRISON_CONTAIN_SLOT(42)
	BFME_GARRISON_CONTAIN_SLOT(43)
	BFME_GARRISON_CONTAIN_SLOT(44)
	BFME_GARRISON_CONTAIN_SLOT(45)
	BFME_GARRISON_CONTAIN_SLOT(46)
	BFME_GARRISON_CONTAIN_SLOT(47)
	BFME_GARRISON_CONTAIN_SLOT(48)
	BFME_GARRISON_CONTAIN_SLOT(49)
	BFME_GARRISON_CONTAIN_SLOT(50)
	BFME_GARRISON_CONTAIN_SLOT(51)
	BFME_GARRISON_CONTAIN_SLOT(52)
	BFME_GARRISON_CONTAIN_SLOT(53)
	BFME_GARRISON_CONTAIN_SLOT(54)
	BFME_GARRISON_CONTAIN_SLOT(55)
	BFME_GARRISON_CONTAIN_SLOT(56)
	BFME_GARRISON_CONTAIN_SLOT(57)
	BFME_GARRISON_CONTAIN_SLOT(58)
	BFME_GARRISON_CONTAIN_SLOT(59)
	BFME_GARRISON_CONTAIN_SLOT(60)
	BFME_GARRISON_CONTAIN_SLOT(61)
	BFME_GARRISON_CONTAIN_SLOT(62)
	BFME_GARRISON_CONTAIN_SLOT(63)
	BFME_GARRISON_CONTAIN_SLOT(64)
	BFME_GARRISON_CONTAIN_SLOT(65)
	BFME_GARRISON_CONTAIN_SLOT(66)
	BFME_GARRISON_CONTAIN_SLOT(67)
	BFME_GARRISON_CONTAIN_SLOT(68)
	BFME_GARRISON_CONTAIN_SLOT(69)
	BFME_GARRISON_CONTAIN_SLOT(70)
	BFME_GARRISON_CONTAIN_SLOT(71)
	BFME_GARRISON_CONTAIN_SLOT(72)
	BFME_GARRISON_CONTAIN_SLOT(73)
	BFME_GARRISON_CONTAIN_SLOT(74)
	BFME_GARRISON_CONTAIN_SLOT(75)
	virtual PlayerMaskType getPlayerWhoEntered() const = 0;
#undef BFME_GARRISON_CONTAIN_SLOT
};

class BfmeGarrisonObjectView
{
public:
	Player *getControllingPlayer() const;
	unsigned char m_unmodelled_000[0x1fc];
	BfmeGarrisonContainView *m_contain;
	unsigned char m_unmodelled_200[0x204 - 0x200];
	AIUpdateInterface *m_ai;
};

class BfmeGarrisonActionManagerView
{
public:
	Bool canEnterObject(const Object *obj, const Object *objectToEnter,
		CommandSourceType commandSource, CanEnterType mode, Bool *outResult);
};

class BfmeGarrisonAICommandView
{
public:
	void aiEnter(Object *object, CommandSourceType commandSource);
};

#pragma comment(linker, "/alternatename:?getControllingPlayer@BfmeGarrisonObjectView@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?canEnterObject@BfmeGarrisonActionManagerView@@QAE_NPBVObject@@0W4CommandSourceType@@W4CanEnterType@@PA_N@Z=?j_0002d588@@YAXXZ")
#pragma comment(linker, "/alternatename:?aiEnter@BfmeGarrisonAICommandView@@QAEXPAVObject@@W4CommandSourceType@@@Z=?j_000442a1@@YAXXZ")

// ?garrisonAllUnits@Player@@QAEXW4CommandSourceType@@@Z
void Player::garrisonAllUnits(CommandSourceType source)
{
	BfmeGarrisonKindOfMask mustBeSet(BfmeGarrisonKindOfMask::kInit,
		KINDOF_STRUCTURE);
	PartitionFilterAcceptByKindOf filter(
		mustBeSet, *(const BfmeGarrisonKindOfMask *)&KINDOFMASK_NONE);
	BfmeResultA iterBuilding =
		((BfmeResultForwardB *)ThePartitionManager)->bfmeForwardResultB((Int)filter);
	*(unsigned int *)&filter = 0x01083B5C;

	struct BfmePlayerTeamListField
	{
		unsigned char m_unmodelled_000[0x288];
		BfmePlayerTeamListNode *m_head;
	};
	BfmePlayerTeamListField *teams = (BfmePlayerTeamListField *)this;
	for (BfmePlayerTeamListNode *it = teams->m_head->m_next;
			it != teams->m_head; it = it->m_next)
	{
		for (BfmePlayerTeamInstanceIterator iter(
				it->m_prototype->m_teamInstanceList);
			!iter.done(); iter.advance())
		{
			BfmePlayerTeamView *team = iter.cur();
			if (!team)
				continue;

			BfmePlayerDlinkIterator<BfmePlayerObjectDlinkObject> iterObj =
				team->iterate_TeamMemberList();
			for (; !iterObj.done(); iterObj.advance())
			{
				BfmeGarrisonObjectView *obj =
					(BfmeGarrisonObjectView *)iterObj.cur();
				if (!obj)
					continue;

				AIUpdateInterface *ai = obj->m_ai;
				if (!ai)
					continue;

				Object *theBuilding;
				iterBuilding.first();
				while (iterBuilding.next(theBuilding))
				{
					BfmeGarrisonObjectView *building =
						(BfmeGarrisonObjectView *)theBuilding;
					BfmeGarrisonContainView *contain = building->m_contain;
					if (contain)
					{
						PlayerMaskType player = contain->getPlayerWhoEntered();
						if (!((player == 0) ||
							(player == obj->getControllingPlayer()->getPlayerMask())))
							continue;
					}

					Bool outResult;
					if (!((BfmeGarrisonActionManagerView *)TheActionManager)->canEnterObject(
						(Object *)obj, theBuilding, source, CHECK_CAPACITY, &outResult)
						|| outResult)
						continue;
					((BfmeGarrisonAICommandView *)((char *)ai + 0x20))->aiEnter(
						theBuilding, source);
				}
			}
		}
	}
}

//=============================================================================
