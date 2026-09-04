// ?joinTeam@AIUpdateInterface@@UAEXXZ
// partial score=0.99 date=2026-09-04
// cl: /DNDEBUG /MD
//
// Retail 0x0027D4F0: AIUpdateInterface::joinTeam.
// This TU keeps the BFME Object/AI offsets local and retains the
// virtually-inherited Object team-member PMF used by the retail iterator.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned int ObjectID;

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

enum StateID
{
	INVALID_STATE_ID = 0xF423F
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x, y, z;
};

class AIUpdateInterface;
class Team;

class AICommandInterface
{
public:
	void aiMoveToPosition(const Coord3D *position, CommandSourceType commandSource);
};

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0( void ); };

class Object;

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList( void ) const;
};

class BfmeObjectDlinkPad { public: unsigned char m_pad[0x64]; };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	Bool isMobile() const;

	Team *getTeam() const
	{
		return *reinterpret_cast<Team * const *>(
			reinterpret_cast<const char *>(this) + 0x23C);
	}

	AIUpdateInterface *getAI() const
	{
		return *reinterpret_cast<AIUpdateInterface * const *>(
			reinterpret_cast<const char *>(this) + 0x204);
	}

	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(
			reinterpret_cast<const char *>(this) + 0x38);
	}

	Bool isHeld() const
	{
		return (*reinterpret_cast<const unsigned char *>(
			reinterpret_cast<const char *>(this) + 0x1A4) & 8) != 0;
	}
};

typedef Object *(Object::*BfmeGetNextTeamMemberFunc)( void ) const;

#define callMemberFunction(object, ptrToMember) ((object).*(ptrToMember))

template<class OBJCLASS>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc) {}

	void advance()
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}

	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	void *m_vptr;
	void *m_unmodelled04;
	void *m_unmodelled08;
	Object *m_head;

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	unsigned char m_unmodelled00[4];
	StateID m_id;
	StateID getID() const { return m_id; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void clear() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void setState(StateID state) = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void setGoalObject(const Object *object) = 0;

	void setGoalWaypoint(const void *waypoint);
	void setGoalPosition(const Coord3D *position);
	Object *getGoalObject();
	const Coord3D *getGoalPosition() const { return &m_goalPosition; }

	StateID getCurrentStateID() const
	{
		return m_currentState ? m_currentState->getID() : INVALID_STATE_ID;
	}

	unsigned char m_unmodelled04[0x1C - 4];
	State *m_currentState;
	unsigned char m_unmodelled20[0x24 - 0x20];
	Coord3D m_goalPosition;
};

class Waypoint;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIStateMachine : public StateMachine
{
public:
	virtual void setGoalObject(const Object *object) = 0;
	void setGoalWaypoint(const Waypoint *waypoint);
};

#define BFME_AI_SLOT(N) virtual void aiSlot##N() = 0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	BFME_AI_SLOT(00); BFME_AI_SLOT(01); BFME_AI_SLOT(02); BFME_AI_SLOT(03);
	BFME_AI_SLOT(04); BFME_AI_SLOT(05); BFME_AI_SLOT(06); BFME_AI_SLOT(07);
	BFME_AI_SLOT(08); BFME_AI_SLOT(09); BFME_AI_SLOT(10); BFME_AI_SLOT(11);
	BFME_AI_SLOT(12); BFME_AI_SLOT(13); BFME_AI_SLOT(14); BFME_AI_SLOT(15);
	BFME_AI_SLOT(16); BFME_AI_SLOT(17); BFME_AI_SLOT(18); BFME_AI_SLOT(19);
	BFME_AI_SLOT(20); BFME_AI_SLOT(21); BFME_AI_SLOT(22); BFME_AI_SLOT(23);
	BFME_AI_SLOT(24); BFME_AI_SLOT(25); BFME_AI_SLOT(26); BFME_AI_SLOT(27);
	BFME_AI_SLOT(28); BFME_AI_SLOT(29); BFME_AI_SLOT(30); BFME_AI_SLOT(31);
	BFME_AI_SLOT(32); BFME_AI_SLOT(33); BFME_AI_SLOT(34); BFME_AI_SLOT(35);
	BFME_AI_SLOT(36); BFME_AI_SLOT(37); BFME_AI_SLOT(38); BFME_AI_SLOT(39);
	BFME_AI_SLOT(40); BFME_AI_SLOT(41); BFME_AI_SLOT(42); BFME_AI_SLOT(43);
	BFME_AI_SLOT(44); BFME_AI_SLOT(45); BFME_AI_SLOT(46); BFME_AI_SLOT(47);
	BFME_AI_SLOT(48); BFME_AI_SLOT(49); BFME_AI_SLOT(50); BFME_AI_SLOT(51);
	BFME_AI_SLOT(52); BFME_AI_SLOT(53); BFME_AI_SLOT(54); BFME_AI_SLOT(55);
	BFME_AI_SLOT(56); BFME_AI_SLOT(57); BFME_AI_SLOT(58); BFME_AI_SLOT(59);
	BFME_AI_SLOT(60); BFME_AI_SLOT(61); BFME_AI_SLOT(62); BFME_AI_SLOT(63);
	BFME_AI_SLOT(64); BFME_AI_SLOT(65); BFME_AI_SLOT(66); BFME_AI_SLOT(67);
	BFME_AI_SLOT(68); BFME_AI_SLOT(69); BFME_AI_SLOT(70); BFME_AI_SLOT(71);
	BFME_AI_SLOT(72); BFME_AI_SLOT(73); BFME_AI_SLOT(74); BFME_AI_SLOT(75);
	BFME_AI_SLOT(76); BFME_AI_SLOT(77); BFME_AI_SLOT(78); BFME_AI_SLOT(79);
	BFME_AI_SLOT(80); BFME_AI_SLOT(81); BFME_AI_SLOT(82); BFME_AI_SLOT(83);
	BFME_AI_SLOT(84); BFME_AI_SLOT(85); BFME_AI_SLOT(86); BFME_AI_SLOT(87);
	BFME_AI_SLOT(88); BFME_AI_SLOT(89); BFME_AI_SLOT(90); BFME_AI_SLOT(91);
	BFME_AI_SLOT(92); BFME_AI_SLOT(93); BFME_AI_SLOT(94); BFME_AI_SLOT(95);
	virtual Bool isIdle() const = 0;
	BFME_AI_SLOT(97); BFME_AI_SLOT(98); BFME_AI_SLOT(99); BFME_AI_SLOT(100);
	BFME_AI_SLOT(101); BFME_AI_SLOT(102); BFME_AI_SLOT(103); BFME_AI_SLOT(104);
	BFME_AI_SLOT(105); BFME_AI_SLOT(106); BFME_AI_SLOT(107); BFME_AI_SLOT(108);
	BFME_AI_SLOT(109); BFME_AI_SLOT(110); BFME_AI_SLOT(111); BFME_AI_SLOT(112);
	BFME_AI_SLOT(113); BFME_AI_SLOT(114); BFME_AI_SLOT(115); BFME_AI_SLOT(116);
	BFME_AI_SLOT(117); BFME_AI_SLOT(118); BFME_AI_SLOT(119); BFME_AI_SLOT(120);
	BFME_AI_SLOT(121); BFME_AI_SLOT(122); BFME_AI_SLOT(123); BFME_AI_SLOT(124);
	BFME_AI_SLOT(125); BFME_AI_SLOT(126);
	virtual Bool chooseLocomotorSet(Int set) = 0;
	virtual void joinTeam();

	unsigned char m_unmodelled04[4];
	Object *m_object;
	unsigned char m_unmodelled0C[0x30 - 0x0C];
	AIStateMachine *m_stateMachine;
	unsigned char m_unmodelled34[0x48 - 0x34];
	CommandSourceType m_lastCommandSource;
	unsigned char m_unmodelled4C[0x32B - 0x4C];
	unsigned char m_isAiDead;

	Object *getObject() { return m_object; }
	AIStateMachine *getStateMachine() { return m_stateMachine; }
	const AIStateMachine *getStateMachine() const { return m_stateMachine; }
	Object *getGoalObject() { return m_stateMachine->getGoalObject(); }
	const Coord3D *getGoalPosition() const { return m_stateMachine->getGoalPosition(); }
	StateID getCurrentStateID() const { return getStateMachine()->getCurrentStateID(); }
	void setLastCommandSource(CommandSourceType source) { m_lastCommandSource = source; }

};

#undef BFME_AI_SLOT

void AIUpdateInterface::joinTeam()
{
	if (m_isAiDead)
		return;

	if (getObject()->isMobile() == false)
		return;

	chooseLocomotorSet(0);
	getStateMachine()->clear();
	getStateMachine()->setGoalWaypoint(0);

	Object *obj = getObject();
	Object *other = 0;
	Team *team = obj->getTeam();
	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *anObj = iter.cur();
		if (!anObj)
		{
			continue;
		}
		if (obj == anObj)
		{
			continue;
		}
		else if (anObj->getAI())
		{
			if (!anObj->isHeld())
			{
				other = anObj;
				break;
			}
		}
	}

	if (other) {
		AIUpdateInterface *ai = other->getAI();
		if (ai->isIdle()) {
			reinterpret_cast<AICommandInterface *>(
				reinterpret_cast<char *>(this) + 0x20)->aiMoveToPosition(
				other->getPosition(), CMD_FROM_AI);
			return;
		}
		if (ai->getGoalObject()) {
			getStateMachine()->setGoalObject(ai->getGoalObject());
		} else {
			getStateMachine()->setGoalPosition(ai->getGoalPosition());
		}
		StateID state = getCurrentStateID();
		setLastCommandSource(CMD_FROM_AI);
		getStateMachine()->setState(state);
	}
}
