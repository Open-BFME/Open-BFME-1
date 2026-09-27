// ?rva0016F7C0@Rva0016F7C0State@@QAE_NXZ
// partial score=0.978 date=2026-09-27
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/objectdlink
// stlport
//
// Retail 0x0016F7C0 (426B): opaque state condition reached through ILT
// 0x0000254F from the 0x00179B10 update body, which branches on AL.
// TheAI+0x14 data byte +0xB4 gates; State+0x1C machine, machine+0x10 owner
// (StateMachine+0x10 m_owner, witnessed); owner AI at +0x204, owner field
// +0x31C, AI int at +0x194 and locomotor at +0x1CC; member AI state machine
// at +0x30 (AIUpdateInterface+0x30 m_stateMachine, witnessed), current state
// at +0x1C (StateMachine+0x1C m_currentState, witnessed), state id at +4,
// compared against 0x36. The walk idiom is the matched AIPlayer::
// isSupplySourceAttacked shape: STL list at Player+0x288, prototype instance
// head at +0x274 drained through a DLINK_ITERATOR<Team> over
// Team::_bfme_nextInInstanceList (const PMF, symbols.csv pin at ILT
// 0x00022A70), each team's member list at Team+0x0C drained through a
// DLINK_ITERATOR<Object> over the Object DLINK PMF {0x00401140,-100,0} from
// ObjectDlinkPmf.h. Locals mirror retail: esi owner, way/int in [esp+0x18],
// damage source in [esp+0x1C], ok flag at [esp+0x13], player in [esp+0x28],
// list node in [esp+0x14], team in [esp+0x2C]. No caller, vtable slot, string
// or ZH twin proves a semantic owner, so the receiver and method keep the
// address token.
#include "ObjectDlinkPmf.h"
#include <list>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned int ObjectID;

class Player;

class Rva0016F7C0Locomotor
{
public:
	Bool field() const;
};

class Rva0016F7C0AI
{
public:
	Int wayAt194() const { return *(const Int *)((const char *)this + 0x194); }
	Rva0016F7C0Locomotor *locomotorAt1CC() const { return *(Rva0016F7C0Locomotor **)((const char *)this + 0x1CC); }
};

class Rva0016F7C0Object
{
public:
	Player *getControllingPlayer() const;
	Bool bfmeGetRecentDamageSource(ObjectID *source, UnsignedInt frames) const;
	Rva0016F7C0AI *getAI() const { return *(Rva0016F7C0AI **)((const char *)this + 0x204); }
	UnsignedInt field31C() const { return *(const UnsignedInt *)((const char *)this + 0x31C); }
};

#pragma comment(linker, "/alternatename:?field@Rva0016F7C0Locomotor@@QBE_NXZ=?j_00045fe3@@YAXXZ")
#pragma comment(linker, "/alternatename:?getControllingPlayer@Rva0016F7C0Object@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeGetRecentDamageSource@Rva0016F7C0Object@@QBE_NPAII@Z=?j_000402d2@@YAXXZ")

#define callMemberFunction(object, ptrToMember) ((object).*(ptrToMember))

template<class OBJCLASS>
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;
private:
	OBJCLASS* m_cur;
	GetNextFunc m_getNextFunc;
public:
	DLINK_ITERATOR(OBJCLASS* cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}

	void advance()
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}

	Bool done() const
	{
		return m_cur == 0;
	}

	OBJCLASS* cur() const
	{
		return m_cur;
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Team *_bfme_nextInInstanceList() const;				// symbols.csv pin, ILT 0x00022A70

	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;							// +0x0C

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	DLINK_ITERATOR<Team> iterate_TeamInstanceList()
	{
		return DLINK_ITERATOR<Team>(m_teamInstanceList, Team::_bfme_nextInInstanceList);
	}

	unsigned char m_unmodelled_000[0x274];
	Team *m_teamInstanceList;					// +0x274
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	typedef std::list<TeamPrototype *> PlayerTeamList;
	const PlayerTeamList *getPlayerTeams() const { return &m_playerTeams; }

private:
	unsigned char m_head[0x288];
	PlayerTeamList m_playerTeams;				// +0x288
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	char m_unmodelled000[0x14];
	void *m_aiData;							// +0x14
};

extern AI *TheAI;

struct Rva0016F7C0MemberState
{
	void *m_vptr;
	Int m_ID;								// +0x04
};

struct Rva0016F7C0MemberMachine
{
	char m_beforeCurrent[0x1C];
	Rva0016F7C0MemberState *m_currentState;				// +0x1C
};

class Rva0016F7C0Machine
{
public:
	char m_beforeOwner[0x10];
	Rva0016F7C0Object *m_owner;					// +0x10
};

class Rva0016F7C0State
{
public:
	Bool rva0016F7C0();
private:
	char m_beforeMachine[0x1C];
	Rva0016F7C0Machine *m_machine;					// +0x1C
};

// ?rva0016F7C0@Rva0016F7C0State@@QAE_NXZ
Bool Rva0016F7C0State::rva0016F7C0()
{
	void *aiData = TheAI->m_aiData;
	if (!*(const Bool *)((const char *)aiData + 0xB4))
		return true;
	Rva0016F7C0Object *owner = m_machine->m_owner;
	Rva0016F7C0AI *ai = owner->getAI();
	if (!ai)
		return true;
	UnsignedInt ownerField = owner->field31C();
	Int way = ai->wayAt194();
	if (way > 1)
		return true;
	Rva0016F7C0Locomotor *locomotor = ai->locomotorAt1CC();
	if (locomotor && !locomotor->field())
		return true;
	ObjectID damageSource;
	if (owner->bfmeGetRecentDamageSource((ObjectID *)&way, 4))
		return true;
	Bool ok = true;
	Player *player = owner->getControllingPlayer();
	Player::PlayerTeamList::const_iterator it;
	for (it = player->getPlayerTeams()->begin(); it != player->getPlayerTeams()->end(); ++it)
	{
		TeamPrototype *proto = *it;
		for (DLINK_ITERATOR<Team> iter = proto->iterate_TeamInstanceList(); !iter.done(); iter.advance())
		{
			Team *team = iter.cur();
			if (!team)
				continue;
			for (DLINK_ITERATOR<Object> objIter = team->iterate_TeamMemberList(); !objIter.done(); objIter.advance())
			{
				Object *obj = objIter.cur();
				if (!obj)
					continue;
				Rva0016F7C0Object *member = (Rva0016F7C0Object *)obj;
				if (member->field31C() != ownerField)
					continue;
				Rva0016F7C0AI *memberAI = member->getAI();
				if (member == owner)
					continue;
				if (member->bfmeGetRecentDamageSource(&damageSource, 4))
					return true;
				if (!memberAI)
					continue;
				Rva0016F7C0MemberMachine *machine =
					*(Rva0016F7C0MemberMachine **)((const char *)memberAI + 0x30);
				Rva0016F7C0MemberState *state = machine->m_currentState;
				if (!state)
					continue;
				if (state->m_ID != 0x36)
					continue;
				Rva0016F7C0Locomotor *memberLocomotor = memberAI->locomotorAt1CC();
				if (memberLocomotor && !memberLocomotor->field())
					continue;
				if (memberAI->wayAt194() != way)
					ok = false;
			}
		}
	}
	return ok;
}
