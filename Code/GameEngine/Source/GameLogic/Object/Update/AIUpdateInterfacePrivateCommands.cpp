// cl: /DNDEBUG /MD
// readable body of ?privateAttackMoveToPosition@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// readable body of ?privateHunt@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// readable body of ?privateFaceObject@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// readable body of ?privateGetRepaired@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// readable body of ?privateGuardObject@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// readable body of ?privateGuardPosition@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// readable body of ?privateGuardRetaliate@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
//
// The seven AIUpdateInterface private command handlers that share one shape:
// guard the object, clear the state machine, record the command source, and
// set a state.
//
//   privateAttackMoveToPosition  0x00279050
//   privateHunt                  0x00279100
//   privateFaceObject            0x00279180
//   privateGetRepaired           0x00279360
//   privateGuardObject           0x002793C0
//   privateGuardPosition         0x00279450
//   privateGuardRetaliate        0x002795D0
//
// They sat in seven files, each re-declaring AIUpdateInterface out to whatever
// field its own body reached, so the class existed in seven partial versions
// that had to agree and nothing checked that they did. Declared once here, the
// fields line up with upstream's own order at +0x48 onward (m_lastCommandSource,
// m_guardMode, m_guardTargetType[2], the guard location, m_objectToGuard) --
// which is the confirmation no single file could give.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_AI = 1
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
	GUARDTARGET_NONE = 4
};

enum StateID
{
	BFME_AI_GUARD = 0x10,
	BFME_AI_HUNT = 0x11,
	BFME_AI_GET_REPAIRED = 0x18,
	BFME_AI_FACE_OBJECT = 0x1F,
	BFME_AI_ATTACK_MOVE_TO = 0x21,
	BFME_AI_GUARD_RETALIATE = 0x3E
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	Bool isMobile() const;
	Coord3D getPosition() const;
	const WeaponSetFlags &getWeaponSetFlags() const;
	Weapon *getCurrentWeapon(WeaponSlotType *wslot);

	unsigned char m_unmodelled_08[0x74 - 8];
	UnsignedInt m_id;
	unsigned char m_unmodelled_78[0x94 - 0x78];
	unsigned char m_flags;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	void setGoalPositionClipped(const Coord3D *pos, CommandSourceType cmdSource);

protected:
	virtual void privateAttackMoveToPosition(const Coord3D *pos, Int maxShotsToFire, CommandSourceType cmdSource);
	virtual void privateHunt(CommandSourceType cmdSource);
	virtual void privateFaceObject(Object *obj, CommandSourceType cmdSource);
	virtual void privateGetRepaired(Object *repairDepot, CommandSourceType cmdSource);
	virtual void privateGuardObject(Object *objectToGuard, GuardMode guardMode, CommandSourceType cmdSource);
	virtual void privateGuardPosition(const Coord3D *pos, GuardMode guardMode, CommandSourceType cmdSource);
	virtual void privateGuardRetaliate(Object *victim, const Coord3D *pos, Int maxShotsToFire, CommandSourceType cmdSource);

	void playMoveVoiceResponse(const Coord3D *position);
	void playAttackVoiceResponse(const Coord3D *position);

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
	unsigned char m_unmodelled_58[0x64 - 0x58];	// upstream's m_locationToGuard
	UnsignedInt m_objectToGuard;				// +0x64
	UnsignedInt m_guardExtra;					// +0x68
	Object *m_faceObject;						// +0x6C
	unsigned char m_unmodelled_70[0x32B - 0x70];
	unsigned char m_isAiDead;					// +0x32B
};

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
