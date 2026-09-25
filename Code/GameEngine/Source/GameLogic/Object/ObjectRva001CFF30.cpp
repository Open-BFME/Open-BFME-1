// ?rva001cff30@Object@@UAEXPAV1@@Z
// partial score=0.97 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc
// BFME Object vtable 0x0109EE58 slot 26 (+0x68), retail 0x001CFF30, 532 bytes.
// The slot holds ILT 0x0001B7FC, whose jmp lands here; the Object constructor at
// 0x001D29A0 installs that vtable. The method's name is unproven, so it keeps the
// address token. What the body proves: given the Object that engaged it, an idle
// or attacking unit that is not already busy on another target answers with
// AIUpdateInterface::bfmeAttackTarget, then asks an enemy non-mine attacker the
// same question through this very slot, guarded against re-entry by the byte at
// +0x36A.
//
// Status and KindOf numbers are read from the retail name tables
// (ObjectStatusMaskType names at 0x012A6670, KindOfMaskType names at 0x012AA068).

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Object;
class Player;

enum KindOfType
{
	KINDOF_STRUCTURE = 7,
	KINDOF_MINE = 54
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_STEALTHED = 15,
	OBJECT_STATUS_DETECTED = 17,
	OBJECT_STATUS_IS_MELEE_ATTACKING = 28,
	OBJECT_STATUS_HORDE_MEMBER = 37,
	OBJECT_STATUS_UNCONTROLLABLY_SCARED = 68
};

enum Relationship
{
	ENEMIES = 0
};

enum CrushSquishTestType
{
	TEST_CRUSH_OR_SQUISH = 2
};

#define BFME_SLOT(n) virtual Int bfmeSlot##n() = 0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	BFME_SLOT(000); BFME_SLOT(001); BFME_SLOT(002); BFME_SLOT(003); BFME_SLOT(004);
	BFME_SLOT(005); BFME_SLOT(006); BFME_SLOT(007); BFME_SLOT(008); BFME_SLOT(009);
	BFME_SLOT(010); BFME_SLOT(011); BFME_SLOT(012); BFME_SLOT(013); BFME_SLOT(014);
	BFME_SLOT(015); BFME_SLOT(016); BFME_SLOT(017); BFME_SLOT(018); BFME_SLOT(019);
	BFME_SLOT(020); BFME_SLOT(021); BFME_SLOT(022); BFME_SLOT(023); BFME_SLOT(024);
	BFME_SLOT(025); BFME_SLOT(026); BFME_SLOT(027); BFME_SLOT(028); BFME_SLOT(029);
	BFME_SLOT(030); BFME_SLOT(031); BFME_SLOT(032); BFME_SLOT(033); BFME_SLOT(034);
	BFME_SLOT(035); BFME_SLOT(036); BFME_SLOT(037); BFME_SLOT(038); BFME_SLOT(039);
	BFME_SLOT(040); BFME_SLOT(041); BFME_SLOT(042); BFME_SLOT(043); BFME_SLOT(044);
	BFME_SLOT(045); BFME_SLOT(046); BFME_SLOT(047); BFME_SLOT(048); BFME_SLOT(049);
	BFME_SLOT(050); BFME_SLOT(051); BFME_SLOT(052); BFME_SLOT(053); BFME_SLOT(054);
	BFME_SLOT(055); BFME_SLOT(056); BFME_SLOT(057); BFME_SLOT(058); BFME_SLOT(059);
	BFME_SLOT(060); BFME_SLOT(061); BFME_SLOT(062); BFME_SLOT(063); BFME_SLOT(064);
	BFME_SLOT(065); BFME_SLOT(066); BFME_SLOT(067); BFME_SLOT(068); BFME_SLOT(069);
	BFME_SLOT(070); BFME_SLOT(071); BFME_SLOT(072); BFME_SLOT(073); BFME_SLOT(074);
	BFME_SLOT(075); BFME_SLOT(076); BFME_SLOT(077); BFME_SLOT(078); BFME_SLOT(079);
	BFME_SLOT(080); BFME_SLOT(081); BFME_SLOT(082); BFME_SLOT(083); BFME_SLOT(084);
	BFME_SLOT(085); BFME_SLOT(086); BFME_SLOT(087); BFME_SLOT(088); BFME_SLOT(089);
	BFME_SLOT(090); BFME_SLOT(091); BFME_SLOT(092); BFME_SLOT(093); BFME_SLOT(094);
	BFME_SLOT(095);
	// slots 96, 97 and 99 as AIGroupStatePredicates.cpp and
	// ObjectDamageAndWeapons.cpp name them
	virtual Bool isIdle() const = 0;			// +0x180
	virtual Bool isAttacking() const = 0;		// +0x184
	BFME_SLOT(098);
	virtual Bool isBusy() const = 0;			// +0x18C

	UnsignedInt getMoodMatrixValue() const;
	void bfmeAttackTarget(Object *target);

	unsigned char m_pad004[0x335 - 0x4];
	Bool m_bfmeTargeting;					// +0x335
};

// Object vtable slots 0..24; which of them Thing declares is not modelled.
class Thing
{
public:
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03); BFME_SLOT(04);
	BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07); BFME_SLOT(08); BFME_SLOT(09);
	BFME_SLOT(10); BFME_SLOT(11); BFME_SLOT(12); BFME_SLOT(13); BFME_SLOT(14);
	BFME_SLOT(15); BFME_SLOT(16); BFME_SLOT(17); BFME_SLOT(18); BFME_SLOT(19);
	BFME_SLOT(20); BFME_SLOT(21); BFME_SLOT(22); BFME_SLOT(23); BFME_SLOT(24);

	Bool isKindOf(KindOfType kind) const;
};

#undef BFME_SLOT

class Rva001E1770ByteField
{
public:
	unsigned char get() const;
};

// Object_rva001CC790_crushPolicy.cpp models the same Object+0x26C array
class Weapon
{
private:
	unsigned char m_pad00[4];

public:
	Rva001E1770ByteField *m_template;		// +0x04
};

// The 0x001C14E0 query, under the spelling its matched row carries.
class BfmeThingAFA
{
public:
	bool bfmeAskAFA(void *targetObject);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	// slot 25, +0x64 (ILT 0x0000B366 -> 0x001BE070)
	virtual Object *bfmeGetCurrentVictimIfAttacking() const;
	// slot 26, +0x68
	virtual void rva001cff30(Object *otherObject);

	Bool testStatus(Int status) const;
	Relationship getRelationship(const Object *other) const;
	Player *getControllingPlayer() const;
	bool crushPolicy(Object *other, CrushSquishTestType testType) const;
	Object *bfmeResolveMeleeTarget(Int unused);
	Bool rva001c7530();
	// 0x001CAEE0: status STEALTHED set and DETECTED clear, as seen by the player
	Bool queryRva001CAEE0(const Player *viewer) const;
	void rva001c7200();

private:
	unsigned char m_pad004[0x204 - 0x4];
	AIUpdateInterface *m_ai;				// +0x204
	unsigned char m_pad208[0x26c - 0x208];
	Weapon *m_weapons[4];					// +0x26C
	UnsignedInt m_curWeapon;				// +0x27C
	unsigned char m_pad280[4];
	void *m_weaponSet;						// +0x284
	unsigned char m_pad288[0x36a - 0x288];
	Bool m_isHandlingReciprocalAttackReentry;	// +0x36A
};

Bool bfmeMeleeHordeTargetInvalid(Object *attacker, Object *target);

void Object::rva001cff30(Object *otherObject)
{
	if (otherObject == 0)
		return;
	AIUpdateInterface *ai = m_ai;
	if (ai == 0)
		return;
	if (m_isHandlingReciprocalAttackReentry)
		return;
	if (bfmeMeleeHordeTargetInvalid(this, otherObject))
		return;

	Object *victim = bfmeGetCurrentVictimIfAttacking();
	if (!ai->m_bfmeTargeting && victim != 0)
	{
		Bool sameTarget = (otherObject == victim);
		if (otherObject->testStatus(OBJECT_STATUS_HORDE_MEMBER))
		{
			Object *victimHorde = victim->bfmeResolveMeleeTarget(0);
			if (otherObject->bfmeResolveMeleeTarget(0) == victimHorde)
				sameTarget = true;
		}
		if ((!testStatus(OBJECT_STATUS_HORDE_MEMBER) || otherObject->isKindOf(KINDOF_STRUCTURE)) && !sameTarget)
			return;
	}

	if (ai->isBusy())
		return;
	if (m_weaponSet == 0)
		return;
	Weapon *weapon = m_weapons[m_curWeapon];
	if (weapon == 0)
		return;
	if (!weapon->m_template->get())
		return;
	if (crushPolicy(otherObject, TEST_CRUSH_OR_SQUISH) && rva001c7530())
		return;
	Object *horde = bfmeResolveMeleeTarget(0);
	if (testStatus(OBJECT_STATUS_HORDE_MEMBER) && horde != 0 &&
		horde->crushPolicy(otherObject, TEST_CRUSH_OR_SQUISH) && horde->rva001c7530())
		return;
	if (ai->getMoodMatrixValue() & 0x2000)
		return;
	if (!((BfmeThingAFA *)this)->bfmeAskAFA(otherObject))
		return;
	if (!ai->isIdle() && !ai->isAttacking())
		return;
	if (testStatus(OBJECT_STATUS_UNCONTROLLABLY_SCARED))
		return;
	if (testStatus(OBJECT_STATUS_IS_MELEE_ATTACKING))
		return;
	if (otherObject->queryRva001CAEE0(getControllingPlayer()))
		return;
	if (testStatus(OBJECT_STATUS_STEALTHED) && !testStatus(OBJECT_STATUS_DETECTED))
		return;

	ai->bfmeAttackTarget(otherObject);
	rva001c7200();
	m_isHandlingReciprocalAttackReentry = true;
	if (otherObject->getRelationship(this) == ENEMIES && !otherObject->isKindOf(KINDOF_MINE))
		otherObject->rva001cff30(this);
	m_isHandlingReciprocalAttackReentry = false;
}
