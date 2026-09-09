// cl: /DNDEBUG /MD
// readable body of ?privateAttackMoveToPosition@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// readable body of ?privateHunt@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// readable body of ?privateFaceObject@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// readable body of ?privateGetRepaired@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// readable body of ?privateGuardObject@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// readable body of ?privateGuardPosition@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// readable body of ?privateGuardRetaliate@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
//
// The AIUpdateInterface private command handlers that share one shape: guard
// the object, clear the state machine, record the command source, and set a
// state. These are the bodies AICommandInterface::aiDoCommand dispatches to.
//
//   privateExitInstantly         0x00271800  state 0x26
//   bfmePrivateCommand01         0x00273400  state 0x01
//   bfmePrivateCommand38         0x002734B0  state 0x38
//   privateMoveToPosition        0x00278280  state 0x01
//   bfmePrivateCommand3F         0x00278390  state 0x3F
//   bfmePrivateCommand25         0x00278430  state 0x25
//   bfmePrivateCommand1C         0x002784A0  state 0x1C
//   bfmePrivateCommand1D         0x00278540  state 0x1D
//   bfmePrivateCommand1E         0x002785E0  state 0x1E
//   bfmePrivateCommand37         0x00278680  state 0x37
//   bfmePrivateCommand1B         0x002787D0  state 0x1B
//   privateAttackMoveToPosition  0x00279050  state 0x21
//   privateHunt                  0x00279100  state 0x11
//   privateFaceObject            0x00279180  state 0x1F
//   privateGetRepaired           0x00279360  state 0x18
//   privateGuardObject           0x002793C0  state 0x10
//   privateGuardPosition         0x00279450  state 0x10
//   privateGuardAreaFromPosition 0x002794E0  state 0x10
//   privateGuardRetaliate        0x002795D0  state 0x3E
//
// plus one query that belongs with them because it reads the same object:
//
//   bfmeCurrentWeaponTemplateFlag4  0x00278790, 44 bytes
//
// They sat in nineteen files, each re-declaring AIUpdateInterface out to
// whatever field its own body reached, so the class existed in nineteen partial
// versions that had to agree and nothing checked that they did. Declared once
// here, the fields line up with upstream's own order at +0x48 onward
// (m_lastCommandSource, m_guardMode, m_guardTargetType[2], the guard location,
// m_objectToGuard) -- which is the confirmation no single file could give. The
// same was true of StateMachine: six of the files declared 9 virtual slots and
// the rest 15, so in those six the slot at vtable+0x38 did not exist at all.
//
// Two things only the whole set can say.
//
// The state machine slot at vtable+0x38 has one meaning. Three of the merged
// files reached it through a placeholder -- `slot38(void *)` in two of them and
// `slot38(int)` in the third -- while privateExitInstantly and
// privateGuardRetaliate, which never sat beside them, called it
// setGoalObject(const Object *). It is the goal object: bfmePrivateCommand01
// and 38 set it from their argument and then read the position out of that same
// object at +0x38 for the voice response, and bfmePrivateCommand1B clears it by
// passing null.
//
// bfmePrivateCommand01 and privateMoveToPosition enter the SAME state. Both
// call setState(1); privateMoveToPosition takes a position and prepares the
// state action with it, bfmePrivateCommand01 takes an object, makes it the goal
// and takes the position from it. They are the position and object forms of one
// order, and the two files named the constant differently -- BFME_AI_MOVE_TO
// against BFME_AI_STATE_01 -- so nothing connected them. The same happened to
// the byte at +0x32B, which bfmePrivateCommand01 called m_flag32b and
// privateAttackMoveToPosition called m_isAiDead; both bodies read it as the
// same early-out.
//
// privateMoveToPosition's BfmeVirtualSlots<96> base is what pins isIdle() to
// its retail vtable slot. The private commands are declared after it and none
// of them dispatches through this vtable, so their own slot numbers are not
// evidence of anything.
//
// That 96 is corroborated from the other side of the call, by a different route.
// This TU derives it from INSIDE the class: privateMoveToPosition calls its own
// isIdle() through this, so isIdle has to be the first own virtual behind a
// 96-slot base. AIGroupStatePredicates.cpp derives it from OUTSIDE:
// AIGroup::isIdle calls ai->isIdle() through an AIUpdateInterface pointer and
// reproduces retail's dispatch only with 96 declared slots ahead of the method,
// which it writes out as a padding run rather than a template base. Two bodies,
// two call directions, two constructions, one number.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_AI = 1,
	CMD_FROM_INTERNAL = 2
};

enum KindOfType
{
	KINDOF_PROJECTILE = 0x19
};

enum GuardMode
{
	GUARDMODE_NORMAL = 0
};

enum GuardTargetType
{
	GUARDTARGET_OBJECT = 1,
	GUARDTARGET_LOCATION = 2,
	GUARDTARGET_AREA = 3,
	GUARDTARGET_NONE = 4
};

enum StateID
{
	BFME_AI_MOVE_TO = 0x01,
	BFME_AI_GUARD = 0x10,
	BFME_AI_HUNT = 0x11,
	BFME_AI_GET_REPAIRED = 0x18,
	BFME_AI_STATE_1B = 0x1B,
	BFME_AI_STATE_1C = 0x1C,
	BFME_AI_STATE_1D = 0x1D,
	BFME_AI_STATE_1E = 0x1E,
	BFME_AI_FACE_OBJECT = 0x1F,
	BFME_AI_ATTACK_MOVE_TO = 0x21,
	BFME_AI_STATE_25 = 0x25,
	BFME_AI_EXIT_INSTANTLY = 0x26,
	BFME_AI_STATE_37 = 0x37,
	BFME_AI_STATE_38 = 0x38,
	BFME_AI_GUARD_RETALIATE = 0x3E,
	BFME_AI_STATE_3F = 0x3F
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x, y, z;
};

class WeaponSetFlags
{
public:
	Bool test(Int type) const { return (m_words[0] & (1U << type)) != 0; }

	UnsignedInt m_words[1];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponTemplate
{
public:
	unsigned char m_unmodelled_00[0x4D4];
	unsigned char m_bit0 : 1;
	unsigned char m_bit1 : 1;
	unsigned char m_bit2 : 1;
	unsigned char m_bit3 : 1;
	unsigned char m_bit4 : 1;					// WeaponTemplate+0x4D4 bit 4
};

// The weapon handle bfmeCurrentWeaponTemplateFlag4 asks the object for. It is
// the same question privateAttackMoveToPosition and privateGuardRetaliate ask
// through Object::getCurrentWeapon -- both take a null slot argument and both
// come back with the object's current weapon -- but the two calls are pinned
// separately, ?bfmeAskCLE@BfmeSubCLE@@ through ILT 0x00009C41 and
// ?getCurrentWeapon@Object@@ through ILT 0x00031A7F to body 0x001BE230. Until
// one caller settles whether those two thunks reach the same body, both
// spellings stay, and this one is reached by a cast the way the other
// address-named helpers in this TU are.
class BfmeXCLE
{
public:
	const WeaponTemplate *getTemplate() const { return m_template; }

private:
	void *m_vtable;
	const WeaponTemplate *m_template;			// +0x04
};

class BfmeSubCLE
{
public:
	BfmeXCLE *bfmeAskCLE(int);					///< ILT 0x00009C41
};

class Weapon
{
public:
	unsigned char m_unmodelled_00[0x20];
	Int m_shotsFired;
	unsigned char m_unmodelled_24[0x34 - 0x24];
	Int m_maxShotCount;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	unsigned char m_unmodelled_08[0xC8 - 8];
	UnsignedInt m_kindof[3];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	Bool isKindOf(KindOfType t) const;

	virtual void slot00();
	ThingTemplate *m_template;
};

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PolygonTrigger.h
class PolygonTrigger
{
public:
	void getCenterPoint(Coord3D *position) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/OpenContain.h
class HordeContainInterface
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual void slot26() = 0; virtual void slot27() = 0;
	virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30() = 0; virtual void slot31() = 0;
	virtual void exitObject(Object *, CommandSourceType) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
class ContainModuleInterface
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual HordeContainInterface *getHordeContainInterface() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	Bool isMobile() const;
	Coord3D getPosition() const;
	const WeaponSetFlags &getWeaponSetFlags() const;
	Weapon *getCurrentWeapon(WeaponSlotType *wslot);

	unsigned char m_unmodelled_08[0x74 - 8];
	UnsignedInt m_id;							// +0x74
	unsigned char m_unmodelled_78[0x90 - 0x78];
	UnsignedInt m_status;						// +0x90
	unsigned char m_flags;						// +0x94
	unsigned char m_unmodelled_95[0x1FC - 0x95];
	ContainModuleInterface *m_contain;			// +0x1FC
	unsigned char m_unmodelled_200[0x214 - 0x200];
	Object *m_containedBy;						// +0x214
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	Object *getGoalObject();
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void clear();
	virtual void slot18();
	virtual void slot1C();
	virtual void setState(StateID state);
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void setGoalObject(const Object *object);
};

class Rva001B5CC0
{
public:
	void set(const char *other);
};

class Rva002BC470StateAction
{
public:
	void prepare(void *first, void *second);
};

class Rva0016AD50
{
public:
	void bfmeSnapshot();
};

#pragma comment(linker, "/alternatename:?bfmeSnapshot@Rva0016AD50@@QAEXXZ=?j_0002d308@@YAXXZ")

class Rva0016AD90
{
public:
	void setTemporaryState(StateID state, int frameCount);
};

#pragma comment(linker, "/alternatename:?setTemporaryState@Rva0016AD90@@QAEXW4StateID@@H@Z=?j_00044319@@YAXXZ")

template<int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template<>
class BfmeVirtualSlots<0>
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface : public BfmeVirtualSlots<96>
{
public:
	virtual Bool isIdle() const = 0;
	virtual Bool bfmeCurrentWeaponTemplateFlag4() const;

	void setGoalPositionClipped(const Coord3D *pos, CommandSourceType cmdSource);

protected:
	virtual void privateExitInstantly(Object *objectToExit, CommandSourceType cmdSource);
	virtual void bfmePrivateCommand01(void *first, CommandSourceType cmdSource);
	virtual void bfmePrivateCommand38(void *first, CommandSourceType cmdSource);
	virtual void privateMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
	virtual void bfmePrivateCommand3F(void *first, CommandSourceType cmdSource);
	virtual void bfmePrivateCommand25(void *first, CommandSourceType cmdSource);
	virtual void bfmePrivateCommand1C(const Coord3D *pos, CommandSourceType cmdSource);
	virtual void bfmePrivateCommand1D(const Coord3D *pos, CommandSourceType cmdSource);
	virtual void bfmePrivateCommand1E(const Coord3D *pos, CommandSourceType cmdSource);
	virtual void bfmePrivateCommand37(const Coord3D *pos, CommandSourceType cmdSource);
	virtual void bfmePrivateCommand1B(void *first, CommandSourceType cmdSource);
	void bfmePrivateCommand31(Object *obj, CommandSourceType cmdSource);
	virtual void bfmePrivateCommand39(Object *victim, CommandSourceType cmdSource);
	virtual void privateAttackMoveToPosition(const Coord3D *pos, Int maxShotsToFire, CommandSourceType cmdSource);
	virtual void privateHunt(CommandSourceType cmdSource);
	virtual void privateFaceObject(Object *obj, CommandSourceType cmdSource);
	virtual void privateGetRepaired(Object *repairDepot, CommandSourceType cmdSource);
	virtual void privateGuardObject(Object *objectToGuard, GuardMode guardMode, CommandSourceType cmdSource);
	virtual void privateGuardPosition(const Coord3D *pos, GuardMode guardMode, CommandSourceType cmdSource);
	virtual void privateGuardAreaFromPosition(const PolygonTrigger *area, GuardMode guardMode,
		CommandSourceType cmdSource, const Coord3D *position);
	virtual void privateGuardRetaliate(Object *victim, const Coord3D *pos, Int maxShotsToFire, CommandSourceType cmdSource);

	void playMoveVoiceResponse(const Coord3D *position);
	void playAttackVoiceResponse(Object *victim);
	void playAttackVoiceResponse(const Coord3D *position);
	void setCurrentVictim(const Object *victim);

	unsigned char m_unmodelled_04[4];
	Object *m_object;
	unsigned char m_unmodelled_0C[0x30 - 0x0C];
	StateMachine *m_stateMachine;
	unsigned char m_unmodelled_34[0x48 - 0x34];
	CommandSourceType m_lastCommandSource;

	// Merging the seven files exposed a collision none of them could see:
	// privateGuardObject and privateGuardPosition write the guard mode to
	// +0x4C, and privateGetRepaired writes its repair-depot pointer to the
	// same word. Both stores are byte-verified against retail, so BFME really
	// does reuse this slot; nothing in these bodies says which name it wore,
	// and upstream's field order (m_guardMode here) covers only one of them.
	union
	{
		GuardMode m_guardMode;					// +0x4C, the guard commands
		Object *m_repairDepot;					// +0x4C, privateGetRepaired
	};
	GuardTargetType m_guardTargetType[2];		// +0x50

	// privateGuardAreaFromPosition writes three floats here, which is what
	// turns the guess that +0x58 is upstream's m_locationToGuard into
	// something byte-verified. Note that privateGuardPosition does NOT write
	// it: that body stores only the z word, and it stores it at +0x68, past
	// the end of this member.
	Coord3D m_locationToGuard;					// +0x58

	UnsignedInt m_objectToGuard;				// +0x64
	UnsignedInt m_guardExtra;					// +0x68

	// The second collision this TU exposes. privateFaceObject stores the
	// object it is turning towards at +0x6C; privateGuardAreaFromPosition
	// stores the polygon it is guarding at the same word. Both stores are
	// byte-verified, so BFME reuses this slot the way it reuses +0x4C.
	union
	{
		Object *m_faceObject;					// +0x6C, privateFaceObject
		const PolygonTrigger *m_areaToGuard;	// +0x6C, the area guard
	};
	unsigned char m_unmodelled_70[0x16C - 0x70];
	int m_blockedFrames;						// +0x16C
	unsigned char m_unmodelled_170[0x1CC - 0x170];
	Rva001B5CC0 *m_curLocomotor;				// +0x1CC
	unsigned char m_unmodelled_1D0[0x325 - 0x1D0];
	unsigned char m_isBlocked;					// +0x325
	unsigned char m_isBlockedAndStuck;			// +0x326
	unsigned char m_unmodelled_327[0x32B - 0x327];
	unsigned char m_isAiDead;					// +0x32B
};

// Retail 0x00271800. The preceding 0x00271760 body is privateDock. This one
// asks the object's contain interface at +0x1FC for a BFME horde exit view and
// uses it if there is one, before falling back to the exit-instantly state.
void AIUpdateInterface::privateExitInstantly(Object *objectToExit, CommandSourceType cmdSource)
{
	Object *us = m_object;
	if (!objectToExit)
		objectToExit = us->m_containedBy;

	if (!objectToExit)
		return;

	ContainModuleInterface *contain = us->m_contain;
	if (contain)
	{
		HordeContainInterface *horde = contain->getHordeContainInterface();
		if (horde)
		{
			horde->exitObject(objectToExit, cmdSource);
			return;
		}
	}

	m_stateMachine->clear();
	m_stateMachine->setGoalObject(objectToExit);
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_EXIT_INSTANTLY);
}

// Retail 0x00273400. The object form of the move order privateMoveToPosition
// gives the position form: m_isAiDead gates it, the argument becomes the goal
// object, and the voice response reads that object's position at +0x38.
void AIUpdateInterface::bfmePrivateCommand01(void *first, CommandSourceType cmdSource)
{
	if (m_isAiDead)
		return;
	if (!m_object->isMobile())
		return;

	if (m_curLocomotor)
		m_curLocomotor->set((const char *)m_object);

	m_stateMachine->clear();
	m_stateMachine->setGoalObject((const Object *)first);
	m_blockedFrames = 0;
	m_isBlocked = 0;
	m_isBlockedAndStuck = 0;
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_MOVE_TO);

	if (cmdSource == CMD_FROM_PLAYER || cmdSource == CMD_FROM_AI)
		playMoveVoiceResponse((const Coord3D *)((const char *)first + 0x38));
}

// Retail 0x002734B0. bfmePrivateCommand01 without the m_isAiDead gate,
// entering state 0x38.
void AIUpdateInterface::bfmePrivateCommand38(void *first, CommandSourceType cmdSource)
{
	if (!m_object->isMobile())
		return;

	if (m_curLocomotor)
		m_curLocomotor->set((const char *)m_object);

	m_stateMachine->clear();
	m_stateMachine->setGoalObject((const Object *)first);
	m_blockedFrames = 0;
	m_isBlocked = 0;
	m_isBlockedAndStuck = 0;
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_STATE_38);

	if (cmdSource == CMD_FROM_PLAYER || cmdSource == CMD_FROM_AI)
		playMoveVoiceResponse((const Coord3D *)((const char *)first + 0x38));
}

// Retail 0x00278280. BFME rejects mine-clearing details, preserves the active
// goal for an internal move, and uses a 100-frame temporary move state when the
// unit is busy.
void AIUpdateInterface::privateMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource)
{
	if (!m_object->isMobile())
		return;
	if (m_object->getWeaponSetFlags().test(8))
		return;

	if (m_curLocomotor)
		m_curLocomotor->set((const char *)m_object);

	if (!isIdle() && cmdSource == CMD_FROM_INTERNAL)
	{
		reinterpret_cast<Rva0016AD50 *>(m_stateMachine)->bfmeSnapshot();
		reinterpret_cast<Rva002BC470StateAction *>(this)->prepare((void *)pos, (void *)cmdSource);
		m_blockedFrames = 0;
		m_isBlocked = 0;
		m_isBlockedAndStuck = 0;
		reinterpret_cast<Rva0016AD90 *>(m_stateMachine)->setTemporaryState(BFME_AI_MOVE_TO, 100);
		return;
	}

	m_stateMachine->clear();
	reinterpret_cast<Rva002BC470StateAction *>(this)->prepare((void *)pos, (void *)cmdSource);
	m_blockedFrames = 0;
	m_isBlocked = 0;
	m_isBlockedAndStuck = 0;
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_MOVE_TO);

	if (cmdSource == CMD_FROM_PLAYER || cmdSource == CMD_FROM_AI)
		playMoveVoiceResponse(pos);
}

// Retail 0x00278390. Gated on weapon-set bit 8 like privateMoveToPosition, but
// with no voice response.
void AIUpdateInterface::bfmePrivateCommand3F(void *first, CommandSourceType cmdSource)
{
	if (!m_object->isMobile())
		return;
	if (m_object->getWeaponSetFlags().test(8))
		return;

	if (m_curLocomotor)
		m_curLocomotor->set((const char *)m_object);

	m_stateMachine->clear();
	reinterpret_cast<Rva002BC470StateAction *>(this)->prepare(first, (void *)cmdSource);
	m_blockedFrames = 0;
	m_isBlocked = 0;
	m_isBlockedAndStuck = 0;
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_STATE_3F);
}

// Retail 0x00278430. No locomotor notification and no voice response.
void AIUpdateInterface::bfmePrivateCommand25(void *first, CommandSourceType cmdSource)
{
	if (!m_object->isMobile())
		return;

	m_stateMachine->clear();
	reinterpret_cast<Rva002BC470StateAction *>(this)->prepare(first, (void *)cmdSource);
	m_blockedFrames = 0;
	m_isBlocked = 0;
	m_isBlockedAndStuck = 0;
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_STATE_25);
}

// Retail 0x002784A0, 0x00278540, 0x002785E0 and 0x00278680: one body four times
// over states 0x1C, 0x1D, 0x1E and 0x37, differing in the constant alone.
void AIUpdateInterface::bfmePrivateCommand1C(const Coord3D *pos, CommandSourceType cmdSource)
{
	if (!m_object->isMobile())
		return;

	if (m_curLocomotor)
		m_curLocomotor->set((const char *)m_object);

	m_stateMachine->clear();
	reinterpret_cast<Rva002BC470StateAction *>(this)->prepare((void *)pos, (void *)cmdSource);
	m_blockedFrames = 0;
	m_isBlocked = 0;
	m_isBlockedAndStuck = 0;
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_STATE_1C);

	if (cmdSource == CMD_FROM_PLAYER || cmdSource == CMD_FROM_AI)
		playMoveVoiceResponse(pos);
}

void AIUpdateInterface::bfmePrivateCommand1D(const Coord3D *pos, CommandSourceType cmdSource)
{
	if (!m_object->isMobile())
		return;

	if (m_curLocomotor)
		m_curLocomotor->set((const char *)m_object);

	m_stateMachine->clear();
	reinterpret_cast<Rva002BC470StateAction *>(this)->prepare((void *)pos, (void *)cmdSource);
	m_blockedFrames = 0;
	m_isBlocked = 0;
	m_isBlockedAndStuck = 0;
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_STATE_1D);

	if (cmdSource == CMD_FROM_PLAYER || cmdSource == CMD_FROM_AI)
		playMoveVoiceResponse(pos);
}

void AIUpdateInterface::bfmePrivateCommand1E(const Coord3D *pos, CommandSourceType cmdSource)
{
	if (!m_object->isMobile())
		return;

	if (m_curLocomotor)
		m_curLocomotor->set((const char *)m_object);

	m_stateMachine->clear();
	reinterpret_cast<Rva002BC470StateAction *>(this)->prepare((void *)pos, (void *)cmdSource);
	m_blockedFrames = 0;
	m_isBlocked = 0;
	m_isBlockedAndStuck = 0;
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_STATE_1E);

	if (cmdSource == CMD_FROM_PLAYER || cmdSource == CMD_FROM_AI)
		playMoveVoiceResponse(pos);
}

void AIUpdateInterface::bfmePrivateCommand37(const Coord3D *pos, CommandSourceType cmdSource)
{
	if (!m_object->isMobile())
		return;

	if (m_curLocomotor)
		m_curLocomotor->set((const char *)m_object);

	m_stateMachine->clear();
	reinterpret_cast<Rva002BC470StateAction *>(this)->prepare((void *)pos, (void *)cmdSource);
	m_blockedFrames = 0;
	m_isBlocked = 0;
	m_isBlockedAndStuck = 0;
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_STATE_37);

	if (cmdSource == CMD_FROM_PLAYER || cmdSource == CMD_FROM_AI)
		playMoveVoiceResponse(pos);
}

// Retail 0x002787D0, the shortest of the family: it clears the goal object
// rather than setting one, and skips the locomotor, the blocked counters and
// the voice response.
void AIUpdateInterface::bfmePrivateCommand1B(void *first, CommandSourceType cmdSource)
{
	if (!m_object->isMobile())
		return;

	m_stateMachine->clear();
	m_stateMachine->setGoalObject(0);
	reinterpret_cast<Rva002BC470StateAction *>(this)->prepare(first, (void *)cmdSource);
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_STATE_1B);
}

// Retail 0x002788B0. A contained unit cannot accept this object-order state.
void AIUpdateInterface::bfmePrivateCommand31(Object *obj, CommandSourceType cmdSource)
{
	if (m_isAiDead)
		return;
	if (!m_object->isMobile())
		return;
	if (m_object->m_containedBy)
		return;

	Object *oldGoal = m_stateMachine->getGoalObject();
	Object *target = obj;
	m_stateMachine->clear();
	m_stateMachine->setGoalObject(target);
	m_lastCommandSource = cmdSource;
	setCurrentVictim(oldGoal);
	m_stateMachine->setState((StateID)0x31);

	if (!cmdSource || cmdSource == CMD_FROM_AI)
		playMoveVoiceResponse((const Coord3D *)((const char *)target + 0x38));
}

// Retail 0x00273730. BFME command 0x39 orders a giant bird to force-attack
// one object with one shot, then answers player and AI orders with attack voice.
void AIUpdateInterface::bfmePrivateCommand39(Object *victim, CommandSourceType cmdSource)
{
	if (!victim)
		return;

	m_stateMachine->clear();
	m_stateMachine->setGoalObject(victim);
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState((StateID)0x2e);

	Weapon *weapon = m_object->getCurrentWeapon(0);
	if (weapon)
	{
		weapon->m_maxShotCount = 1;
		weapon->m_shotsFired = 0;
	}

	if (cmdSource == CMD_FROM_PLAYER || cmdSource == CMD_FROM_AI)
		playAttackVoiceResponse(victim);
}

// Retail 0x00279050. m_isAiDead, isMobile, weapon-set bit 8,
// setGoalPositionClipped, setState(0x21), max-shot count, move voice for
// command sources 0 and 1.
void AIUpdateInterface::privateAttackMoveToPosition(const Coord3D *pos, Int maxShotsToFire, CommandSourceType cmdSource)
{
	if (m_isAiDead)
		return;
	if (!m_object->isMobile())
		return;
	if (m_object->getWeaponSetFlags().test(8))
		return;

	m_stateMachine->clear();
	setGoalPositionClipped(pos, cmdSource);
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_ATTACK_MOVE_TO);

	Weapon *weapon = m_object->getCurrentWeapon(0);
	if (weapon)
	{
		weapon->m_maxShotCount = maxShotsToFire;
		weapon->m_shotsFired = 0;
	}

	if (cmdSource == CMD_FROM_PLAYER || cmdSource == CMD_FROM_AI)
		playMoveVoiceResponse(pos);
}

// Retail 0x00279100. isMobile, inlined isKindOf(KINDOF_PROJECTILE), the +0x94
// flag, then clear and a tail-call setState(0x11).
void AIUpdateInterface::privateHunt(CommandSourceType cmdSource)
{
	if (!m_object->isMobile())
		return;

	Object *obj = m_object;
	ThingTemplate *tmpl = obj->m_template;
	if (tmpl && tmpl->m_nextOverride)
		tmpl = (ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
	if (tmpl->m_kindof[0] & 0x2000000)
		return;

	if (obj->m_flags & 0x20)
		return;

	m_stateMachine->clear();
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_HUNT);
}

// Retail 0x00279180.
void AIUpdateInterface::privateFaceObject(Object *obj, CommandSourceType cmdSource)
{
	if (!m_object->isMobile())
		return;

	ThingTemplate *const volatile *templateSlot = &m_object->m_template;
	ThingTemplate *tmpl = *templateSlot;
	if (tmpl && tmpl->m_nextOverride)
		tmpl = (ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
	if (tmpl->m_kindof[0] & 0x2000000)
		return;

	m_faceObject = obj;
	m_stateMachine->clear();
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_FACE_OBJECT);

	if (cmdSource == CMD_FROM_PLAYER || cmdSource == CMD_FROM_AI)
	{
		Coord3D pos = obj->getPosition();
		playAttackVoiceResponse(&pos);
	}
}

// Retail 0x00279360. Guards the object's +0x94 flag and isMobile /
// isKindOf(KINDOF_PROJECTILE), stores the depot at +0x4C, clears the state
// machine, then setState(0x18).
void AIUpdateInterface::privateGetRepaired(Object *repairDepot, CommandSourceType cmdSource)
{
	if (m_object->m_flags & 0x20)
		return;
	if (!m_object->isMobile())
		return;
	if (m_object->isKindOf(KINDOF_PROJECTILE))
		return;

	m_repairDepot = repairDepot;
	m_stateMachine->clear();
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_GET_REPAIRED);
}

// Retail 0x002793C0. Same +0x94 / isMobile / isKindOf(PROJECTILE) guards as
// privateGetRepaired, then the two-slot guard-target type, the object ID at
// +0x74, setState(0x10).
void AIUpdateInterface::privateGuardObject(Object *objectToGuard, GuardMode guardMode, CommandSourceType cmdSource)
{
	if (m_object->m_flags & 0x20)
		return;
	if (!m_object->isMobile())
		return;
	if (m_object->isKindOf(KINDOF_PROJECTILE))
		return;

	if (m_guardTargetType[1] == GUARDTARGET_NONE)
		m_guardTargetType[1] = GUARDTARGET_OBJECT;
	else
		m_guardTargetType[0] = GUARDTARGET_OBJECT;

	m_guardMode = guardMode;
	m_objectToGuard = objectToGuard->m_id;
	m_stateMachine->clear();
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_GUARD);
}

// Retail 0x00279450, the sibling of privateGuardObject: same guards, guard
// target type 2, object-to-guard cleared, the position's z word copied to
// +0x68, setState(0x10).
void AIUpdateInterface::privateGuardPosition(const Coord3D *pos, GuardMode guardMode, CommandSourceType cmdSource)
{
	if (m_object->m_flags & 0x20)
		return;
	if (!m_object->isMobile())
		return;
	if (m_object->isKindOf(KINDOF_PROJECTILE))
		return;

	if (m_guardTargetType[1] == GUARDTARGET_NONE)
		m_guardTargetType[1] = GUARDTARGET_LOCATION;
	else
		m_guardTargetType[0] = GUARDTARGET_LOCATION;

	m_guardMode = guardMode;
	m_objectToGuard = 0;
	m_guardExtra = *(UnsignedInt *)&pos->z;
	m_stateMachine->clear();
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_GUARD);
}

// Retail 0x002794E0, the BFME script variant of guard-area: it keeps the area
// pointer but takes an optional waypoint position for the location the guard
// state uses. A null position falls back to the area's own centre.
void AIUpdateInterface::privateGuardAreaFromPosition(const PolygonTrigger *area,
	GuardMode guardMode, CommandSourceType cmdSource, const Coord3D *position)
{
	if (m_object->m_flags & 0x20)
		return;
	if (!m_object->isMobile())
		return;
	if (m_object->isKindOf(KINDOF_PROJECTILE))
		return;

	if (m_guardTargetType[1] == GUARDTARGET_NONE)
		m_guardTargetType[1] = GUARDTARGET_AREA;
	else
		m_guardTargetType[0] = GUARDTARGET_AREA;

	m_guardMode = guardMode;
	m_areaToGuard = area;
	Coord3D localPosition;
	if (!position)
		area->getCenterPoint(&localPosition);
	else
		localPosition = *position;
	m_locationToGuard = localPosition;
	m_objectToGuard = 0;
	m_stateMachine->clear();
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_GUARD);
}

// Retail 0x002795D0. Null-victim guard, clear, setGoalObject,
// setGoalPositionClipped, setState(0x3e), then the current weapon's max-shot
// count at +0x34.
void AIUpdateInterface::privateGuardRetaliate(Object *victim, const Coord3D *pos, Int maxShotsToFire, CommandSourceType cmdSource)
{
	if (!victim)
		return;

	m_stateMachine->clear();
	m_stateMachine->setGoalObject(victim);
	setGoalPositionClipped(pos, cmdSource);
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_GUARD_RETALIATE);

	Weapon *weapon = m_object->getCurrentWeapon(0);
	if (weapon)
		weapon->m_maxShotCount = maxShotsToFire;
}

// Retail 0x00278790. Not a command handler but the same reads: the object's
// status word at +0x90 must carry 0x400000, and then bit 4 of the current
// weapon's template at +0x4D4 is the answer.
Bool AIUpdateInterface::bfmeCurrentWeaponTemplateFlag4() const
{
	Object *obj = m_object;
	if ((obj->m_status & 0x400000) == 0)
		return false;
	else
	{
		BfmeXCLE *weapon = reinterpret_cast<BfmeSubCLE *>(obj)->bfmeAskCLE(0);
		if (!weapon)
			return false;
		return weapon->getTemplate()->m_bit4;
	}
}
