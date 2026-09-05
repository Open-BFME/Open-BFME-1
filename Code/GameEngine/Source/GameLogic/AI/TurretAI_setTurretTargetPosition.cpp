// cl: /DNDEBUG /MD /EHsc
//
// BFME TurretAI::setTurretTargetPosition. Same shape as the ZH body in
// TurretAI.cpp except retail does not call areTurretsLinked; a failed weapon
// check just nulls pos.

enum TurretTargetType
{
	TARGET_NONE = 0,
	TARGET_OBJECT = 1,
	TARGET_POSITION = 2
};

enum TurretStateType
{
	TURRETAI_IDLE = 0,
	TURRETAI_IDLESCAN = 1,
	TURRETAI_AIM = 2,
	TURRETAI_FIRE = 3,
	TURRETAI_RECENTER = 4,
	TURRETAI_HOLD = 5
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

struct Coord3D
{
	float x, y, z;
};

class Weapon;
class Object;
class AIUpdateInterface;

class Object
{
public:
	Weapon *getCurrentWeapon(WeaponSlotType *slot);

	char m_pad74[0x74];
	int m_id;
	char m_pad204[0x204 - 0x78];
	AIUpdateInterface *m_ai;
};

class AIUpdateInterface
{
public:
#define V(n) virtual void v##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
	V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
	V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79)
	V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87) V(88) V(89)
	V(90) V(91) V(92) V(93) V(94) V(95) V(96) V(97) V(98) V(99)
	V(100) V(101) V(102) V(103) V(104) V(105) V(106) V(107) V(108) V(109)
	V(110) V(111) V(112) V(113) V(114)
#undef V
	virtual void addTargeter(int id, bool add);
};

typedef unsigned int StateID;
enum StateReturnType { STATE_CONTINUE = 0, STATE_SUCCESS = -1, STATE_FAILURE = -2 };

class State
{
public:
	virtual void v00();
	StateID m_id;
};

class StateMachine
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual StateReturnType setState(StateID id);
	virtual void v24();
	virtual void v28();
	virtual void v2c();
	virtual void v30();
	virtual void v34();
	virtual void setGoalObject(Object *obj);

	StateID getCurrentStateID() const
	{
		return m_curState ? m_curState->m_id : 999999;
	}

	Object *getGoalObject();
	void setGoalPosition(const Coord3D *pos);

	char m_pad4[0x18];
	State *m_curState;
};

class TurretAIData
{
public:
	char m_pad[0x3c];
	int m_turretWeaponSlots;
};

class TurretAI
{
public:
	void setTurretTargetPosition(const Coord3D *pos);

private:
	void *m_vptr;
	char m_pad4[4];
	TurretAIData *m_data;
	char m_padc[4];
	Object *m_owner;
	StateMachine *m_turretStateMachine;
	char m_pad18[0x94 - 0x18];
	void *m_victimInitialTeam;
	int m_target;
	char m_pad9c[0xab - 0x9c];
	char m_targetWasSetByIdleMood;
};

// ?setTurretTargetPosition@TurretAI@@QAEXPBUCoord3D@@@Z
void TurretAI::setTurretTargetPosition(const Coord3D *pos)
{
	WeaponSlotType wslot;
	if (!pos || !m_owner->getCurrentWeapon(&wslot) || (m_data->m_turretWeaponSlots & (1 << wslot)) == 0)
		pos = 0;

	if (m_target == TARGET_OBJECT && m_turretStateMachine)
	{
		Object *self = m_owner;
		Object *target = m_turretStateMachine->getGoalObject();
		if (self && target)
		{
			AIUpdateInterface *targetAI = target->m_ai;
			if (targetAI)
				targetAI->addTargeter(self->m_id, false);
		}
	}

	m_turretStateMachine->setGoalObject(0);
	if (pos)
		m_turretStateMachine->setGoalPosition(pos);
	m_target = pos ? TARGET_POSITION : TARGET_NONE;
	m_targetWasSetByIdleMood = 0;

	StateID sid = m_turretStateMachine->getCurrentStateID();
	if (pos)
	{
		if (sid != TURRETAI_AIM && sid != TURRETAI_FIRE)
			m_turretStateMachine->setState(TURRETAI_AIM);
		m_victimInitialTeam = 0;
	}
	else
	{
		if (sid == TURRETAI_AIM || sid == TURRETAI_FIRE)
			m_turretStateMachine->setState(TURRETAI_HOLD);
		m_victimInitialTeam = 0;
	}
}
