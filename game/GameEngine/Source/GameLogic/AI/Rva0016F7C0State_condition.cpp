// cl: /DNDEBUG /DWIN32 /MD /EHsc
// stlport
// Retail 0x0016F7C0: AI state condition reached through ILT 0x0000254F from the 0x00179B10 update body.
#include <list>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned int ObjectID;

class Player;

// Landed at 0x0016E3C0 in Q2OverrideChainFieldReads.cpp; retail calls it through ILT 0x00045FE3.
class Rva0016E3C0
{
public:
	Bool field() const;
};

class Rva0016F7C0Locomotor : public Rva0016E3C0
{
};

class Rva0016F7C0AI
{
public:
	Int wayAt194() const { return *(const Int *)((const char *)this + 0x194); }
	Rva0016F7C0Locomotor *locomotorAt1CC() const { return *(Rva0016F7C0Locomotor **)((const char *)this + 0x1CC); }
};

class Object;

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

// Introduces the vbptr at its own +0 and lands at Object+0x68 (the shape the {0x00401140,-100,0} DLINK PMF needs).
class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0( void ); };

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList( void ) const;
};

class BfmeObjectDlinkPad { public: unsigned char m_pad[0x64]; };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	Player *getControllingPlayer() const;
	Bool bfmeGetRecentDamageSource(ObjectID *sourceID, UnsignedInt frames) const;

	unsigned char m_tail[0x40];
};

class Rva0016F7C0Object : public Object
{
public:
	Rva0016F7C0AI *getAI() const { return *(Rva0016F7C0AI **)((const char *)this + 0x204); }
	UnsignedInt field31C() const { return *(const UnsignedInt *)((const char *)this + 0x31C); }
};

#define callMemberFunction(object, ptrToMember) ((object).*(ptrToMember))

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
template<class OBJCLASS>
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
	if (owner->bfmeGetRecentDamageSource(&damageSource, 4))
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
				if (!machine->m_currentState || machine->m_currentState->m_ID != 0x36)
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
