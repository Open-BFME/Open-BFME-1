// cl: /DNDEBUG /MD /EHsc  /Igame/GameEngine/Include/Precompiled /Iinputs/reference/shims/objectdlink /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// AIGuardIdleState portion of retail AIGuard.cpp: update at 0015E510 and
// complete destructor at 0015D180. The real Team average stays visible and
// non-inlined so the position output has the retail lifetime and copy order.
// Its authoritative 186-byte row remains Rva000EDCD0TeamEstimatePosition.cpp.
// novtable preserves the destructor's five-byte jump to State::~State.
// Evidence: targets/game/reverse/identity_evidence/0015e510-visible-team-position.md.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned int TeamID;
typedef bool Bool;
typedef float Real;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

#include "../../../../Libraries/Source/WWVegas/WWMath/coord.h"
class AIUpdateInterface
{
public:
	Int getCrateID() const { return *(const Int *)((const char *)this + 0x218); }
};

#include "ObjectDlinkPmf.h"
static inline const Coord3D *getPosition(const Object *p) { return (const Coord3D *)((const char *)p+0x38); }
static inline AIUpdateInterface *getAI(const Object *p) {return *(AIUpdateInterface **)((const char *)p+0x204);}
#define callMemberFunction(object,ptrToMember)  ((object).*(ptrToMember))

// upstream: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameMemory.h
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

// Object +0x38: the position the body sums (address-derived view).
struct Rva000EDCD0ObjectPosition
{
	unsigned char m_before[0x38];
	Coord3D m_position;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}

	void getEstimateTeamPosition_000EDCD0(Coord3D *pos) const;
};

// ?getEstimateTeamPosition_000EDCD0@Team@@QBEXPAUCoord3D@@@Z present-unmatched
inline __declspec(noinline) void Team::getEstimateTeamPosition_000EDCD0(Coord3D *pos) const
{
	Coord3D sum;
	sum.x = 0.0f;
	sum.y = 0.0f;
	sum.z = 0.0f;
	int count = 0;
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		if (!obj)
			continue;
		const Coord3D *p = &((const Rva000EDCD0ObjectPosition *)obj)->m_position;
		sum.x += p->x;
		sum.y += p->y;
		sum.z += p->z;
		++count;
	}
	Real scale = 1.0f / count;
	sum.x *= scale;
	sum.y *= scale;
	sum.z *= scale;
	*pos = sum;
}

class TeamFactory
{
public:
	Team *findTeamByID(TeamID id);
};

#include "../../Common/Thing/GameLogicObjectLookup.h"
class AIData
{
public:
	unsigned char m_fields[0x40];
	UnsignedInt m_guardEnemyScanRate;
};

class AI
{
public:
	unsigned char m_fields[0x14];
	AIData *m_data;
	AIData *getAiData() { return m_data; }
};

extern GameLogic *TheGameLogic;
extern TeamFactory *TheTeamFactory;
extern AI *TheAI;

class AIGuardMachine
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void setState(int state);

	Bool lookForInnerTarget(void);
	Object *getOwner() const { return m_owner; }
	Object *findTargetToGuardByID() { return TheGameLogic->findObjectByID(m_targetToGuard); }
	Team *findTeamToGuardByID() { return TheTeamFactory->findTeamByID(m_teamToGuard); }

protected:
	unsigned char m_unmodelled04[0x0C];
	Object *m_owner;
	unsigned char m_unmodelled14[0x30];
	Int m_targetToGuard;
	TeamID m_teamToGuard;
};

class State
{
public:
 virtual ~State();
};

class __declspec(novtable) AIGuardIdleState : public State
{
public:
 virtual ~AIGuardIdleState();
	virtual StateReturnType update();

private:
	unsigned char m_stateFields04[0x18];
	AIGuardMachine *m_machine;
	unsigned char m_unreconstructed20[4];
	UnsignedInt m_nextEnemyScanTime;
	Coord3D m_guardeePos;
};

#define PATHFIND_CELL_SIZE_F 10.0f

StateReturnType AIGuardIdleState::update()
{
	UnsignedInt now = *(const unsigned int *)((const char *)TheGameLogic+0x3c);
	if (now < m_nextEnemyScanTime)
		return (StateReturnType)(m_nextEnemyScanTime - now);

	m_nextEnemyScanTime = now + TheAI->getAiData()->m_guardEnemyScanRate;

	AIGuardMachine *machine = m_machine;
	if (getAI(machine->getOwner())->getCrateID() != 0)
	{
		machine->setState(0x138c);
		return (StateReturnType)(m_nextEnemyScanTime - now);
	}

	if (machine->lookForInnerTarget())
		return STATE_SUCCESS;

	Object *targetToGuard = machine->findTargetToGuardByID();
	Team *teamToGuard = machine->findTeamToGuardByID();
	Coord3D pos;
	if (targetToGuard == 0 && teamToGuard == 0)
		return (StateReturnType)(m_nextEnemyScanTime - now);
	if (targetToGuard) pos = *getPosition(targetToGuard);
	else teamToGuard->getEstimateTeamPosition_000EDCD0(&pos);

	Real delta = m_guardeePos.x - pos.x;
	if (delta * delta > 4 * PATHFIND_CELL_SIZE_F * PATHFIND_CELL_SIZE_F)
	{
		m_guardeePos = pos;
		return STATE_FAILURE;
	}
	delta = m_guardeePos.y - pos.y;
	if (delta * delta > 4 * PATHFIND_CELL_SIZE_F * PATHFIND_CELL_SIZE_F)
	{
		m_guardeePos = pos;
		return STATE_FAILURE;
	}
	return (StateReturnType)(m_nextEnemyScanTime - now);
}

AIGuardIdleState::~AIGuardIdleState()
{
}
