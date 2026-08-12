// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: retail-layout C++ conversion of TurretAI::setTurretTargetObject.

typedef bool Bool;
typedef unsigned int ObjectID;

enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};

class Weapon;

#define TEN_VIRTUALS(prefix) \
	virtual void prefix##0(); virtual void prefix##1(); \
	virtual void prefix##2(); virtual void prefix##3(); \
	virtual void prefix##4(); virtual void prefix##5(); \
	virtual void prefix##6(); virtual void prefix##7(); \
	virtual void prefix##8(); virtual void prefix##9()

class AIUpdateInterface
{
public:
	TEN_VIRTUALS(a);
	TEN_VIRTUALS(b);
	TEN_VIRTUALS(c);
	TEN_VIRTUALS(d);
	TEN_VIRTUALS(e);
	TEN_VIRTUALS(f);
	TEN_VIRTUALS(g);
	TEN_VIRTUALS(h);
	TEN_VIRTUALS(i);
	TEN_VIRTUALS(j);
	TEN_VIRTUALS(k);
	virtual void l0();
	virtual void l1();
	virtual void l2();
	virtual void l3();
	virtual void l4();
	virtual void removeTargeter(ObjectID, Bool);
};

class Object
{
private:
	char Pad0[0x3C];

public:
	unsigned int KindOf;

private:
	char Pad1[0x34];

public:
	ObjectID ID;

private:
	char Pad2[0x18C];

public:
	AIUpdateInterface *AI;

private:
	char Pad3[0x34];

public:
	void *Team;

private:
	char Pad4[0x104];

public:
	unsigned char Status;

	Weapon *getCurrentWeapon(WeaponSlotType *slot);
	ObjectID getID() const { return ID; }
};

struct TurretAIData
{
	char Pad[0x3C];
	unsigned int ControlledWeaponSlots;
};

struct State
{
	void *VTable;
	int ID;
};

class StateMachine
{
public:
	virtual void d0();
	virtual void d1();
	virtual void d2();
	virtual void d3();
	virtual void d4();
	virtual void d5();
	virtual void d6();
	virtual void d7();
	virtual void setState(int);
	virtual void d9();
	virtual void d10();
	virtual void d11();
	virtual void d12();
	virtual void d13();
	virtual void setGoalObject(Object *);

	char Pad[0x18];
	State *CurrentState;

	Object *getGoalObject();
};

class TurretAI
{
private:
	char Pad0[8];
	const TurretAIData *Data;
	char Pad1[4];
	Object *Owner;
	StateMachine *Machine;
	char Pad2[0x7C];
	void *VictimInitialTeam;
	int Target;
	char Pad3[0x0E];
	unsigned char ForceAttacking;
	unsigned char TargetWasSetByIdleMood;

public:
	void setTurretTargetObject(Object *victim, Bool forceAttacking);
};

void TurretAI::setTurretTargetObject(Object *victim, Bool forceAttacking)
{
	WeaponSlotType slot;
	if (victim == 0 || (victim->Status & 1) != 0 ||
		Owner->getCurrentWeapon(&slot) == 0 ||
		(Data->ControlledWeaponSlots & (1u << slot)) == 0) {
		victim = 0;
	}

	if (victim == 0 && Target == 1 && Machine != 0) {
		Object *self = Owner;
		Object *target = Machine->getGoalObject();
		if (self != 0 && target != 0) {
			AIUpdateInterface *targetAI = target->AI;
			if (targetAI != 0) {
				targetAI->removeTargeter(self->ID, false);
			}
		}
	}

	Machine->setGoalObject(victim);
	Target = victim != 0;
	TargetWasSetByIdleMood = 0;
	ForceAttacking = (unsigned char)forceAttacking;

	int stateID = Machine->CurrentState != 0 ? Machine->CurrentState->ID : 999999;
	if (victim != 0) {
		if (stateID != 2 && stateID != 3) {
			Machine->setState(2);
		}
		VictimInitialTeam = victim->Team;
	} else {
		if (stateID == 2 || stateID == 3) {
			Machine->setState(5);
		}
		VictimInitialTeam = 0;
	}
}
