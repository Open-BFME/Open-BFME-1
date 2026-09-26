// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DZH_EMIT_POOL_GLUE /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Retail 0x00325700, 374 bytes. BFME walks BOTH masks: every discovered-by
// player (outer while) against every skirmish player (inner while).
//
// ScriptConditions::evaluateSkirmishPlayerHasDiscoveredPlayer, matched to the
// Zero Hour twin at
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp:2648.
// BFME resolves both Parameters to PlayerMaskType via
// ScriptEngine::unidentified_0034DB40 (proven at
// game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineGetPlayerMaskFromParameter.cpp)
// instead of ZH's playerFromParam(), then walks players with
// PlayerList::getEachPlayerFromMask (proven at
// game/GameEngine/Source/Common/RTS/PlayerList.cpp) instead of a direct
// Player*. The team/team-instance/team-member walk below is the same
// PlayerTeamList (std::list<TeamPrototype*>) -> team-instance dlink ->
// team-member dlink shape already proven at
// game/GameEngine/Source/Common/RTS/Player_addScience_bfme.cpp, reused
// verbatim (same field offsets, same virtual-base member-function-pointer
// idiom for the two dlink advances).

#define BFME_STLP_NODE_ALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include "PreRTS.h"
#include "Common/Player.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	unsigned char m_unmodelled[0x1c];
};

// Non-virtual out-of-line call: matches
// game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineGetPlayerMaskFromParameter.cpp
// (retail 0x0034DB40), declared-not-defined so it stays a REL32 call here.
class ScriptEngine
{
public:
	PlayerMaskType unidentified_0034DB40(Parameter *);
};
extern ScriptEngine *TheScriptEngine;

// Non-virtual out-of-line call: matches
// game/GameEngine/Source/Common/RTS/PlayerList.cpp (retail 0x000DF4A0).
class PlayerList
{
public:
	Player *getEachPlayerFromMask(PlayerMaskType &maskToAdjust);
};
extern PlayerList *ThePlayerList;

struct BfmePlayerIndexField
{
	unsigned char m_unreconstructed_000[0x24];
	Int m_playerIndex;					// this+0x24
};

struct BfmePlayerTeamFields
{
	unsigned char m_unreconstructed_000[0x288];
	Player::PlayerTeamList m_playerTeamPrototypes;		// this+0x288
};

// Same team-instance / team-member dlink shape as
// game/GameEngine/Source/Common/RTS/Player_addScience_bfme.cpp.
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

	BfmePlayerDlinkIterator(ObjectType *cur, GetNextFunc getNext)
		: m_cur(cur), m_getNext(getNext) { }

	bool done() const { return m_cur == 0; }
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

class BfmePlayerTeamView
{
public:
	unsigned char m_unmodelled_000[0x0c];
	BfmePlayerObjectDlinkObject *m_head;		// this+0xc

	BfmePlayerDlinkIterator<BfmePlayerObjectDlinkObject> iterate_TeamMemberList() const
	{
		return BfmePlayerDlinkIterator<BfmePlayerObjectDlinkObject>(m_head,
			BfmePlayerObjectDlinkBase::dlink_next_TeamMemberList);
	}
};

struct BfmePlayerTeamPrototypeInstances
{
	unsigned char m_unmodelled_000[0x274];
	BfmePlayerTeamView *m_teamInstanceList;	// this+0x274
};

class BfmePlayerTeamInstanceIterator
{
public:
	BfmePlayerTeamInstanceIterator(BfmePlayerTeamView *head) : m_cur(head) { }

	bool done() const { return m_cur == 0; }
	BfmePlayerTeamView *cur() const { return m_cur; }

	void advance()
	{
		if (m_cur)
			m_cur = (BfmePlayerTeamView *)
				((BfmeTeamInstanceLink *)m_cur)->_bfme_nextInInstanceList();
	}

private:
	BfmePlayerTeamView *m_cur;
	int m_unmodelled;
};

// Object (with getShroudedStatus) comes from the real
// inputs/reference/shims/sweep/GameLogic/Object.h, pulled in transitively.

class ScriptConditions
{
protected:
	Bool evaluateSkirmishPlayerHasDiscoveredPlayer(Parameter *, Parameter *);
};

// ?evaluateSkirmishPlayerHasDiscoveredPlayer@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateSkirmishPlayerHasDiscoveredPlayer(
	Parameter *pSkirmishPlayerParm, Parameter *pDiscoveredByParm)
{
	PlayerMaskType discoveredByMask = TheScriptEngine->unidentified_0034DB40(pDiscoveredByParm);
	if (!discoveredByMask)
		return FALSE;

	PlayerMaskType playerMask = TheScriptEngine->unidentified_0034DB40(pSkirmishPlayerParm);

	while (discoveredByMask)
	{
		Player *discoveredBy = ThePlayerList->getEachPlayerFromMask(discoveredByMask);
		if (!discoveredBy)
			continue;

		Int discoveredByIndex = ((BfmePlayerIndexField *)discoveredBy)->m_playerIndex;

		PlayerMaskType mask = playerMask;
		while (mask)
		{
			Player *player = ThePlayerList->getEachPlayerFromMask(mask);
			if (!player)
				continue;

			BfmePlayerTeamFields *teamFields = (BfmePlayerTeamFields *)player;
			for (Player::PlayerTeamList::iterator it = teamFields->m_playerTeamPrototypes.begin();
				it != teamFields->m_playerTeamPrototypes.end(); ++it)
			{
				for (BfmePlayerTeamInstanceIterator teams(
						((BfmePlayerTeamPrototypeInstances *)(*it))->m_teamInstanceList);
					!teams.done(); teams.advance())
				{
					BfmePlayerTeamView *team = teams.cur();
					if (!team)
						continue;

					for (BfmePlayerDlinkIterator<BfmePlayerObjectDlinkObject> objects =
							team->iterate_TeamMemberList();
						!objects.done(); objects.advance())
					{
						BfmePlayerObjectDlinkObject *object = objects.cur();
						if (!object)
							continue;

						ObjectShroudStatus status =
							((Object *)object)->getShroudedStatus(discoveredByIndex);
						if (status == OBJECTSHROUD_CLEAR || status == OBJECTSHROUD_PARTIAL_CLEAR)
							return TRUE;
					}
				}
			}
		}
	}

	return FALSE;
}
