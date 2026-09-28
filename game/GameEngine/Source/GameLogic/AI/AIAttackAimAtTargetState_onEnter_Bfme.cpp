// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?onEnter@AIAttackAimAtTargetState@@UAE?AW4StateReturnType@@XZ: game/GameEngine/Source/GameLogic/AI/AIStates.cpp
// BFME layout reconstruction for retail RVA 0x00183E40 (523 bytes).
//
// IDENTITY.  The exact constructor 0x00171180 installs vtable 0x01097C60 and
// stores m_isAttackingObject at +0x24, m_canTurnInPlace at +0x25,
// m_setLocomotor at +0x26 and m_isForceAttacking at +0x27, which is the
// AIStateMachine.h member order, so the class and the lift's name stand.  The
// vtable's slot 4 is this body (through ILT 0x0000B12C).
//
// ZERO COMPARISON.  `fld dword ptr [0x01075350]` is the shared zero constant
// every BFME range compare loads, so the min-speed test is written against the
// named global rather than a literal.  The DEBUG_ASSERT pair the pathfinder
// refresh carries is the file/line retail pushed (VA 0x0109769C and 0x26C3).

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;
typedef unsigned int ObjectID;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum WhichTurretType
{
	TURRET_INVALID = -1
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

// OBJECT_STATUS_IS_AIMING_WEAPON is entry 25 of the shipped
// ObjectStatusTypes list, and retail's mask argument is the literal
// 0x02000000, i.e. bit 25 of word 0.
enum ObjectStatusTypes
{
	OBJECT_STATUS_IS_AIMING_WEAPON = 25
};

// The leech-range tail tests bit 0x400 of the dword at Object+0x98. No
// shipped member name is evidenced at that offset, so the mask is
// address-derived and self-labelling rather than guessed at.
enum { BFME_OBJECT_RVA00183E40_STATUS_0X400 = 0x00000400 };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
// The template argument is 86: Object::setStatus's recovered name is
// ?setStatus@Object@@QAEXABV?$BitFlags@$0FG@@@_N@Z.  STLport's bitset ctor
// supplies the zero-register/OR initialization retail compiled.
template <size_t NUMBITS>
class BitFlags
{
public:
	// just a little syntactic sugar so that there is no "foo = 0" compatible ctor
	enum BogusInitType
	{
		kInit = 0
	};

	inline BitFlags()
	{
	}

	inline BitFlags(BogusInitType k, Int idx1)
	{
		m_bits.set(idx1);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

#define MAKE_OBJECT_STATUS_MASK(k) ObjectStatusMaskType(ObjectStatusMaskType::kInit, (k))

class Object;
class Weapon;
class BfmeOutOfWeaponRangeTemplate;
class AIUpdateInterface;
class ContainModuleInterface;
class Rva00170120Locomotor;

template <Int N>
class BfmeAIUpdateSlots : public BfmeAIUpdateSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]);
};
template <> class BfmeAIUpdateSlots<0> {};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
// 115 vtable slots precede the two declared virtuals (addTargeter at +0x1cc,
// isTemporarilyPreventingAimSuccess at +0x1d0), and the locomotor pointer
// shares the 115th slot's data offset.
class AIUpdateInterface : public BfmeAIUpdateSlots<115>
{
public:
	virtual void addTargeter(ObjectID id, Bool add);                    // vtable +0x1cc
	virtual Bool isTemporarilyPreventingAimSuccess() const;             // vtable +0x1d0

	WhichTurretType getWhichTurretForCurWeapon() const;
	void setTurretTargetObject(WhichTurretType turret, Object *target, Bool isForceAttacking);
	void setTurretTargetPosition(WhichTurretType turret, const Coord3D *position);

	Rva00170120Locomotor *getCurLocomotor() const
	{
		return m_curLocomotor;
	}

	unsigned char m_unreconstructed_000[0x1cc - sizeof(BfmeAIUpdateSlots<115>)];
	Rva00170120Locomotor *m_curLocomotor;                              // retail this+0x1cc
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
public:
	const BfmeOutOfWeaponRangeTemplate *getTemplate() const
	{
		return m_template;
	}

	Bool isWithinAttackRange(const Object *source, const Object *victim, Int forceAttacking) const;
	Bool isWithinAttackRange(const Object *source, const Coord3D *position, Int forceAttacking) const;

	unsigned char m_unreconstructed_000[0x04];
	const BfmeOutOfWeaponRangeTemplate *m_template;                     // retail this+0x04
};

// Zero Hour spells isContactWeapon()/isLeechRangeWeapon() on Weapon; BFME
// calls both on the template (ecx is weapon+0x04 in retail), and the ledger
// pins ILT 0x0000B8AC and ILT 0x00028F74 to that class's two thunks.
class BfmeOutOfWeaponRangeTemplate
{
public:
	Bool isContactWeapon() const;
	Bool isLeechRangeWeapon() const;
};

template <Int N>
class Rva00183E40ContainSlots : public Rva00183E40ContainSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]);
};
template <> class Rva00183E40ContainSlots<0> {};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
// VC7.1 emits the reverse of declaration order, so the Object* overload is
// declared first and lands on the later slot (+0x124) as retail calls it.
class ContainModuleInterface : public Rva00183E40ContainSlots<72>
{
public:
	virtual Bool attemptBestFirePointPosition(Object *source, Weapon *weapon, Object *victim);  // +0x124
	virtual Bool attemptBestFirePointPosition(Object *source, Weapon *weapon, const Coord3D *position); // +0x120
};

// The float the min-speed probe returns is compared against Zero Hour's
// `curLoco->getMinSpeed() == 0.0f`, but BFME passes the owner to the
// accessor, so the call carries one pointer the callee pops.  Only the
// identity the ledger pin carries is used: ILT 0x0001A334 is pinned as
// Rva00170120Locomotor::check(Rva00170120Object *), and both names keep the
// address token this sibling TU (Rva00170120State_update.cpp) already uses.
struct Rva00170120Object
{
};

class Rva00170120Locomotor
{
public:
	Real check(Rva00170120Object *owner);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Weapon *getCurrentWeapon(WeaponSlotType *slot);
	Int getLayer() const;
	void setStatus(const ObjectStatusMaskType &status, Bool set);

	AIUpdateInterface *getAI() const
	{
		return m_ai;
	}

	Object *getContainedBy() const
	{
		return m_containedBy;
	}

	ContainModuleInterface *getContain() const
	{
		return m_contain;
	}

	const Coord3D *getPosition() const
	{
		return &m_position;
	}

	ObjectID getID() const
	{
		return m_id;
	}

	unsigned char m_unreconstructed_000[0x38];
	Coord3D m_position;                                                 // retail this+0x38
	unsigned char m_unreconstructed_044[0x74 - 0x44];
	ObjectID m_id;                                                      // retail this+0x74
	unsigned char m_unreconstructed_078[0x98 - 0x78];
	UnsignedInt m_unreconstructed_098;                                   // retail this+0x98
	unsigned char m_unreconstructed_09c[0x1fc - 0x9c];
	ContainModuleInterface *m_contain;                                   // retail this+0x1fc
	unsigned char m_unreconstructed_200[0x204 - 0x200];
	AIUpdateInterface *m_ai;                                            // retail this+0x204
	unsigned char m_unreconstructed_208[0x214 - 0x208];
	Object *m_containedBy;                                              // retail this+0x214
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	Object *getGoalObject();

	unsigned char m_unreconstructed_000[0x10];
	Object *m_owner;                                                    // retail this+0x10
	unsigned char m_unreconstructed_014[0x24 - 0x14];
	Coord3D m_goalPosition;                                             // retail this+0x24
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
// The layer arrives as the Int Object::getLayer() returns, and BFME's
// updateGoal takes the DEBUG_ASSERT file and line as well.
class Pathfinder
{
public:
	void updateGoal(Object *object, const Coord3D *position, Int layer, const char *file, Int line);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	Pathfinder *pathfinder() const
	{
		return m_pathfinder;
	}

	unsigned char m_unreconstructed_000[0x0c];
	Pathfinder *m_pathfinder;                                           // retail this+0x0c
};

extern AI *TheAI;
// The shared zero constant at 0x01075350, read by name in
// ?getAdjustedVisionRangeForObject@AI@@SAMPBVObject@@H@Z and here.
extern const float BfmeZeroRange;

// The per-frame body behind the 8-byte index forwarders: 0x00039BD5 is a
// five-byte `jmp 0x0017BA90`, and vtable slot 6 of AIAttackAimAtTargetState
// (0x01097C60) is the recovered forwarder 0x001840D0, which pushes the
// constant 0 and tail-calls the same body.  onEnter below pushes 1 and
// returns its result, so the ABI this TU needs is the one 0x0017BA90's
// `ret 4` shows: one Int popped, the result left in EAX.  The class name
// stays address-derived (the ledger pins only the void-returning
// ?handle@Gen00039BD5@@QAEXH@Z here, used by TinyIndexedForwarders.cpp for
// the forwarder that discards the result), so the value-returning spelling
// keeps that address token and says only what the body proves.
class Gen00039BD5
{
public:
	StateReturnType stateReturn(Int index);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIAttackAimAtTargetState
{
public:
	virtual StateReturnType onEnter();

	unsigned char m_unreconstructed_004[0x1c - 0x04];
	StateMachine *m_machine;                                            // retail this+0x1c
	unsigned char m_unreconstructed_020[0x24 - 0x20];
	Bool m_isAttackingObject;                                           // retail this+0x24
	Bool m_canTurnInPlace;                                              // retail this+0x25
	Bool m_setLocomotor;                                                // retail this+0x26
	Bool m_isForceAttacking;                                            // retail this+0x27
};

// ?onEnter@AIAttackAimAtTargetState@@UAE?AW4StateReturnType@@XZ
StateReturnType AIAttackAimAtTargetState::onEnter()
{
	Object *source = m_machine->m_owner;
	Weapon *weapon = source->getCurrentWeapon((WeaponSlotType *)NULL);
	Object *victim = m_machine->getGoalObject();
	AIUpdateInterface *sourceAI = source->getAI();
	const Coord3D *targetPos = &m_machine->m_goalPosition;
	AIUpdateInterface *victimAI = victim ? victim->getAI() : NULL;

	Rva00170120Locomotor *curLoco = sourceAI->getCurLocomotor();
	m_setLocomotor = false;
	m_canTurnInPlace = curLoco ?
		curLoco->check(reinterpret_cast<Rva00170120Object *>(source)) == BfmeZeroRange : false;

	TheAI->pathfinder()->updateGoal(source, source->getPosition(), source->getLayer(),
		"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIStates.cpp", 0x26c3);

	Bool inFiringRange;
	Object *containedBy = source->getContainedBy();
	if (containedBy && weapon)
	{
		ContainModuleInterface *contain = containedBy->getContain();
		if (victim)
			inFiringRange = contain->attemptBestFirePointPosition(source, weapon, victim);
		else
			inFiringRange = contain->attemptBestFirePointPosition(source, weapon, targetPos);
	}
	else if (victim && weapon)
		inFiringRange = weapon->isWithinAttackRange(source, victim, 0);
	else if (weapon)
		inFiringRange = weapon->isWithinAttackRange(source, targetPos, 0);
	else
		return STATE_FAILURE;

	// add ourself as a targeter BEFORE calling isTemporarilyPreventingAimSuccess().
	if (victimAI)
		victimAI->addTargeter(source->getID(), true);

	WhichTurretType tur = sourceAI->getWhichTurretForCurWeapon();
	if (tur != TURRET_INVALID)
	{
		if (m_isAttackingObject)
			sourceAI->setTurretTargetObject(tur, victim, m_isForceAttacking);
		else
			sourceAI->setTurretTargetPosition(tur, &m_machine->m_goalPosition);
	}
	else
	{
		Bool preventing = victimAI && victimAI->isTemporarilyPreventingAimSuccess();

		// Contact weapons don't aim.  They just go boom.
		if (weapon->getTemplate()->isContactWeapon() && inFiringRange && !preventing)
			return STATE_SUCCESS;

		if (weapon->getTemplate()->isLeechRangeWeapon() && !inFiringRange)
			return STATE_FAILURE;
	}

	if (source->m_unreconstructed_098 & BFME_OBJECT_RVA00183E40_STATUS_0X400)
		return STATE_SUCCESS;

	source->setStatus(MAKE_OBJECT_STATUS_MASK(OBJECT_STATUS_IS_AIMING_WEAPON), true);
	return reinterpret_cast<Gen00039BD5 *>(this)->stateReturn(1);
}
