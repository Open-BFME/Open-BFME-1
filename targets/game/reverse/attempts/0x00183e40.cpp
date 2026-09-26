// ?onEnter@AIAttackAimAtTargetState@@UAE?AW4StateReturnType@@XZ
// partial score=0.35 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// BFME retail 0x00183E40: AIAttackAimAtTargetState::onEnter (523 bytes).
// The offsets and the pathfinder refresh are measured from the retail body.

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;

enum StateReturnType { STATE_CONTINUE = 0, STATE_SUCCESS = -1, STATE_FAILURE = -2 };
enum WhichTurretType { TURRET_INVALID = -1 };

struct Coord3D { Real x, y, z; };

class BfmeOutOfWeaponRangeObject;
class BfmeOutOfWeaponRangeWeapon;
class BfmeOutOfWeaponRangeTemplate;
class BfmeOutOfWeaponRangeStateMachine;
class Locomotor;
class AIUpdateInterface;

class BfmeOutOfWeaponRangeStateMachine
{
public:
	BfmeOutOfWeaponRangeObject *getGoalObject();
	BfmeOutOfWeaponRangeObject *owner() const
	{
		return *(BfmeOutOfWeaponRangeObject **)((const char *)this + 0x10);
	}
	const Coord3D *goalPosition() const
	{
		return (const Coord3D *)((const char *)this + 0x24);
	}
};

template <int N>
class BfmeAIUpdateSlots : public BfmeAIUpdateSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]);
};
template <> class BfmeAIUpdateSlots<0> {};

class AIUpdateInterface : public BfmeAIUpdateSlots<115>
{
public:
	virtual void addTargeter(Int id, Bool add);
	virtual Bool isTemporarilyPreventingAimSuccess() const;
	Locomotor *getCurLocomotor() const
	{
		return *(Locomotor **)((const char *)this + 0x1cc);
	}
	WhichTurretType getWhichTurretForCurWeapon() const;
	void setTurretTargetObject(WhichTurretType turret,
		BfmeOutOfWeaponRangeObject *victim, Bool forceAttacking);
	void setTurretTargetPosition(WhichTurretType turret, const Coord3D *position);
};

class BfmeOutOfWeaponRangeObject
{
public:
	BfmeOutOfWeaponRangeWeapon *getCurrentWeapon(Int slot);
	AIUpdateInterface *getAI() const
	{
		return *(AIUpdateInterface **)((const char *)this + 0x204);
	}
	BfmeOutOfWeaponRangeObject *getContainedBy() const
	{
		return *(BfmeOutOfWeaponRangeObject **)((const char *)this + 0x214);
	}
	BfmeOutOfWeaponRangeObject *getContain() const
	{
		return *(BfmeOutOfWeaponRangeObject **)((const char *)this + 0x1fc);
	}
	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const char *)this + 0x38);
	}
	Int getID() const
	{
		return *(const Int *)((const char *)this + 0x74);
	}
};

class BfmeOutOfWeaponRangeWeapon
{
public:
	BfmeOutOfWeaponRangeTemplate *getTemplate() const
	{
		return *(BfmeOutOfWeaponRangeTemplate **)((const char *)this + 4);
	}
	Bool isWithinAttackRange(const BfmeOutOfWeaponRangeObject *source,
		const BfmeOutOfWeaponRangeObject *target, Int extra) const;
	Bool isWithinAttackRange(const BfmeOutOfWeaponRangeObject *source,
		const Coord3D *targetPos, Int extra) const;
};

class BfmeOutOfWeaponRangeTemplate
{
public:
	Bool isContactWeapon() const;
	Bool isLeechRangeWeapon() const;
};

template <int N>
class Rva00183E40ContainSlots : public Rva00183E40ContainSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]);
};
template <> class Rva00183E40ContainSlots<0> {};

// The BFME vtable slots used here are +0x120 for a position and +0x124 for
// an object.  The slot-only prefix keeps those measured calls explicit.
class Rva00183E40Contain : public Rva00183E40ContainSlots<72>
{
public:
	virtual Bool attemptBestFirePointPosition(BfmeOutOfWeaponRangeObject *source,
		BfmeOutOfWeaponRangeWeapon *weapon, const Coord3D *targetPos);
	virtual Bool attemptBestFirePointPosition(BfmeOutOfWeaponRangeObject *source,
		BfmeOutOfWeaponRangeWeapon *weapon, BfmeOutOfWeaponRangeObject *victim);
};

// This call is the existing retail Locomotor-side helper at ILT 0x1A334.
struct Rva00170120Object {};
class Rva00170120Locomotor
{
public:
	Real check(Rva00170120Object *owner);
};

template <int N> class BitFlags;

class Object
{
public:
	Int getLayer() const;
	void setStatus(const class BitFlags<86> &status, Bool set);
};

class Pathfinder
{
public:
	void updateGoal(Object *object, const Coord3D *position, Int layer,
		const char *file, Int line);
};

class AI
{
public:
	Pathfinder *pathfinder() const
	{
		return *(Pathfinder **)((const char *)this + 0x0c);
	}
};

template <int N>
class BitFlags
{
public:
	BitFlags(Int)
		: word0(0x02000000), word1(0), word2(0) {}
	UnsignedInt word0, word1, word2;
};

class Gen00039BD5
{
public:
	void handle(Int value);
};

#pragma comment(linker, "/alternatename:?getGoalObject@BfmeOutOfWeaponRangeStateMachine@@QAEPAVBfmeOutOfWeaponRangeObject@@XZ=?j_0000e570@@YAXXZ")
#pragma comment(linker, "/alternatename:?getCurrentWeapon@BfmeOutOfWeaponRangeObject@@QAEPAVBfmeOutOfWeaponRangeWeapon@@H@Z=?j_00031a7f@@YAXXZ")
#pragma comment(linker, "/alternatename:?check@Rva00170120Locomotor@@QAEMPAURva00170120Object@@@Z=?j_0001a334@@YAXXZ")
#pragma comment(linker, "/alternatename:?updateGoal@Pathfinder@@QAEXPAVObject@@PBUCoord3D@@HPBDH@Z=?j_000294e2@@YAXXZ")
#pragma comment(linker, "/alternatename:?isWithinAttackRange@BfmeOutOfWeaponRangeWeapon@@QBE_NPBVBfmeOutOfWeaponRangeObject@@0H@Z=?j_0002e85c@@YAXXZ")
#pragma comment(linker, "/alternatename:?isWithinAttackRange@BfmeOutOfWeaponRangeWeapon@@QBE_NPBVBfmeOutOfWeaponRangeObject@@PBUCoord3D@@H@Z=?j_0002e951@@YAXXZ")
#pragma comment(linker, "/alternatename:?isContactWeapon@BfmeOutOfWeaponRangeTemplate@@QBE_NXZ=?j_0000b8ac@@YAXXZ")
#pragma comment(linker, "/alternatename:?isLeechRangeWeapon@BfmeOutOfWeaponRangeTemplate@@QBE_NXZ=?j_00028f74@@YAXXZ")
#pragma comment(linker, "/alternatename:?getLayer@Object@@QBEHXZ=?j_0003a391@@YAXXZ")
#pragma comment(linker, "/alternatename:?setStatus@Object@@QAEXABV?$BitFlags@$0FG@@@_N@Z=?j_000307e7@@YAXXZ")
#pragma comment(linker, "/alternatename:?handle@Gen00039BD5@@QAEXH@Z=?j_00039bd5@@YAXXZ")

#define TheAI (*(AI **)0x012EF214)
#define BfmeZeroRange (*(const Real *)0x01075350)

class BfmeStateBase
{
	virtual void stateSlot();
	unsigned char m_unreconstructed_000[0x18];

protected:
	BfmeOutOfWeaponRangeStateMachine *m_machine;
	unsigned char m_unreconstructed_020[4];
};

class AIAttackAimAtTargetState : public BfmeStateBase
{
private:
	Bool m_isAttackingObject;
	Bool m_canTurnInPlace;
	Bool m_setLocomotor;
	Bool m_isForceAttacking;

public:
	virtual StateReturnType onEnter();
};

// ?onEnter@AIAttackAimAtTargetState@@UAE?AW4StateReturnType@@XZ
StateReturnType AIAttackAimAtTargetState::onEnter()
{
	BfmeOutOfWeaponRangeObject *source = m_machine->owner();
	BfmeOutOfWeaponRangeWeapon *volatile weapon = source->getCurrentWeapon(0);
	BfmeOutOfWeaponRangeObject *victim = m_machine->getGoalObject();
	const Coord3D *targetPos = m_machine->goalPosition();
	AIUpdateInterface *sourceAI = source->getAI();
	AIUpdateInterface *victimAI = victim ? victim->getAI() : 0;

	m_setLocomotor = 0;
	Locomotor *curLoco = sourceAI->getCurLocomotor();
	m_canTurnInPlace = curLoco ?
		((Rva00170120Locomotor *)curLoco)->check((Rva00170120Object *)source) == BfmeZeroRange : 0;

	// Retail's line/file operands are the shared AIStates.cpp literal.
#line 9922 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIStates.cpp"
	((Pathfinder *)TheAI->pathfinder())->updateGoal((Object *)source, source->getPosition(),
		((Object *)source)->getLayer(), __FILE__, __LINE__);

	Bool inFiringRange;
	BfmeOutOfWeaponRangeObject *containedBy = source->getContainedBy();
	if (containedBy && weapon)
	{
		BfmeOutOfWeaponRangeObject *contain = containedBy->getContain();
		if (victim)
			inFiringRange = ((Rva00183E40Contain *)contain)->attemptBestFirePointPosition(source, weapon, victim);
		else
			inFiringRange = ((Rva00183E40Contain *)contain)->attemptBestFirePointPosition(source, weapon, targetPos);
	}
	else if (victim && weapon)
	{
		inFiringRange = weapon->isWithinAttackRange(source, victim, 0);
	}
	else if (weapon)
	{
		inFiringRange = weapon->isWithinAttackRange(source, targetPos, 0);
	}
	else
	{
		return STATE_FAILURE;
	}

	if (victimAI)
		victimAI->addTargeter(source->getID(), 1);

	WhichTurretType turret = sourceAI->getWhichTurretForCurWeapon();
	if (turret != TURRET_INVALID)
	{
		if (m_isAttackingObject)
			sourceAI->setTurretTargetObject(turret, victim, m_isForceAttacking);
		else
			sourceAI->setTurretTargetPosition(turret, targetPos);
	}
	else
	{
		Bool preventing = victimAI && victimAI->isTemporarilyPreventingAimSuccess();
		BfmeOutOfWeaponRangeTemplate *weaponTemplate = weapon->getTemplate();
		if (weaponTemplate->isContactWeapon() && inFiringRange && !preventing)
			return STATE_SUCCESS;
		if (weaponTemplate->isLeechRangeWeapon() && !inFiringRange)
			return STATE_FAILURE;
	}

	((Object *)source)->setStatus(BitFlags<86>(25), 1);
	((Gen00039BD5 *)this)->handle(1);
	return STATE_CONTINUE;
}
