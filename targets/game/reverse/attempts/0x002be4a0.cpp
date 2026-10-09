// ?onEnter@AIGiantBirdAttackState@@UAE?AW4StateReturnType@@XZ
// partial score=0.5112 date=2026-10-10
// cl: /DNDEBUG /MD /EHsc
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
#include "../../../../game/Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "../../../../game/Libraries/Include/Lib/Coord3D.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};


class Object;
class Module;
class ThingTemplate;
class Team;


class BfmeCalc919G
{
public:
	int bfmeCalc919G();
};

class BfmeVec3EJ;
class Matrix3D;
class Gen_000E5A50
{
public:
	float bfmeDistanceSquared(const BfmeVec3EJ *point) const;
};

class FXList
{
public:
	Bool bfmeIsBlocked();
	void doFXPos(const Coord3D *primary, const Matrix3D *matrix, float speed,
		const Coord3D *secondary) const;
};

class AIUpdateInterface;

class DrawableView
{
public:
	char m_pad00[0x94];
	FXList *m_fireFX;
};

enum WeaponSlotType
{
	WEAPON_SLOT_DEFAULT = 0
};

class WeaponData
{
public:
	char m_pad00[0x58];
	float m_speed58;
	char m_pad5c[0x38];
	FXList *m_fireFX94;
	char m_pad98[0x487];
	Bool m_enabled51f;
	Bool getEnabled() const { return m_enabled51f; }
	float getSpeed() const { return m_speed58; }
	FXList *getFireFX() const { return m_fireFX94; }
};

class Weapon
{
public:
	char m_pad00[4];
	WeaponData *m_data04;
	WeaponData *getData() const { return m_data04; }
};

class TargetSubobject
{
public:
	virtual void unused00() = 0;
	virtual void unused04() = 0;
	virtual void unused08() = 0;
	virtual void unused0c() = 0;
	virtual void unused10() = 0;
	virtual void unused14() = 0;
	virtual void unused18() = 0;
	virtual void unused1c() = 0;
	virtual void unused20() = 0;
	virtual void unused24() = 0;
	virtual void unused28() = 0;
	virtual void unused2c() = 0;
	virtual void unused30() = 0;
	virtual void unused34() = 0;
	virtual void unused38(Object *object) = 0;
	virtual void unused3c() = 0;
	virtual void unused40() = 0;
	virtual void unused44() = 0;
	virtual void unused48() = 0;
	virtual void unused4c() = 0;
	virtual void unused50() = 0;
	virtual void unused54() = 0;
	virtual void unused58() = 0;
	virtual void unused5c() = 0;
	virtual void unused60() = 0;
	virtual void unused64() = 0;
	virtual TargetSubobject *unused68() = 0;
	virtual void unused6c() = 0;
};

class ModuleRange
{
public:
	virtual void unused00() = 0;
	virtual void unused04() = 0;
	virtual void unused08() = 0;
	virtual void unused0c() = 0;
	virtual void unused10() = 0;
	virtual void unused14() = 0;
	virtual void unused18() = 0;
	virtual void unused1c() = 0;
	virtual void unused20() = 0;
	virtual void unused24() = 0;
	virtual void unused28() = 0;
	virtual void unused2c() = 0;
	virtual void unused30() = 0;
	virtual void unused34() = 0;
	virtual void unused38() = 0;
	virtual void unused3c() = 0;
	virtual void unused40() = 0;
	virtual void unused44() = 0;
	virtual void unused48() = 0;
	virtual void unused4c() = 0;
	virtual void unused50() = 0;
	virtual void unused54() = 0;
	virtual void unused58() = 0;
	virtual void unused5c() = 0;
	virtual void unused60() = 0;
	virtual void unused64() = 0;
	virtual void unused68() = 0;
	virtual void unused6c() = 0;
	virtual void unused70() = 0;
	virtual void unused74() = 0;
	virtual void unused78() = 0;
	virtual void unused7c() = 0;
	virtual void unused80() = 0;
	virtual void unused84() = 0;
	virtual void activate(Object *object) = 0;
};

class ModuleCollection
{
public:
	virtual void unused00() = 0;
	virtual void unused04() = 0;
	virtual void unused08() = 0;
	virtual void unused0c() = 0;
	virtual void unused10() = 0;
	virtual void unused14() = 0;
	virtual void unused18() = 0;
	virtual void unused1c() = 0;
	virtual void unused20() = 0;
	virtual void unused24() = 0;
	virtual void unused28() = 0;
	virtual void unused2c() = 0;
	virtual void unused30() = 0;
	virtual void unused34() = 0;
	virtual void unused38() = 0;
	virtual void unused3c() = 0;
	virtual void unused40() = 0;
	virtual void unused44() = 0;
	virtual void unused48() = 0;
	virtual void unused4c() = 0;
	virtual void unused50() = 0;
	virtual void unused54() = 0;
	virtual void unused58() = 0;
	virtual unsigned int getEnd() = 0;
	virtual void unused60() = 0;
	virtual void unused64() = 0;
	virtual void unused68() = 0;
	virtual void unused6c() = 0;
	virtual void unused70() = 0;
	virtual void unused74() = 0;
	virtual void unused78() = 0;
	virtual void unused7c() = 0;
	virtual void unused80() = 0;
	virtual void unused84() = 0;
	virtual void registerObject(Object *object) = 0;
	virtual void unused8c() = 0;
	virtual void unused90() = 0;
	virtual void unused94() = 0;
	virtual void unused98() = 0;
	virtual void unused9c() = 0;
	virtual void unuseda0() = 0;
	virtual void unuseda4() = 0;
	virtual void unuseda8() = 0;
	virtual void unusedac() = 0;
	virtual void unusedb0() = 0;
	virtual void unusedb4() = 0;
	virtual void unusedb8() = 0;
	virtual void unusedbc() = 0;
	virtual void unusedc0() = 0;
	virtual void unusedc4() = 0;
	virtual void unusedc8() = 0;
	virtual void unusedcc() = 0;
	virtual void unusedd0() = 0;
	virtual void unusedd4() = 0;
	virtual void unusedd8() = 0;
	virtual void unuseddc() = 0;
	virtual void unusede0() = 0;
	virtual void unusede4() = 0;
	virtual void unusede8() = 0;
	virtual void unusedec() = 0;
	virtual ModuleRange *getRange() = 0;
	virtual void unusedf4() = 0;
	virtual void unusedf8() = 0;
	virtual void unusedfc() = 0;
	virtual unsigned int getBegin(Int value) = 0;
	virtual ModuleRange *getHead() = 0;
};

class ModuleNode
{
public:
	ModuleNode *m_next;
	ModuleNode *m_previous;
	Module *m_value;
};

class ModuleListHead
{
public:
	ModuleNode *m_first;
};

class Module
{
public:
	char m_pad00[0x94];
	unsigned char m_flags94;
};

class AIUpdateInterface
{
public:
	virtual void unused000() = 0;
	virtual void unused004() = 0;
	virtual void unused008() = 0;
	virtual void unused00c() = 0;
	virtual void unused010() = 0;
	virtual void unused014() = 0;
	virtual void unused018() = 0;
	virtual void unused01c() = 0;
	virtual void unused020() = 0;
	virtual void unused024() = 0;
	virtual void unused028() = 0;
	virtual void unused02c() = 0;
	virtual void unused030() = 0;
	virtual void unused034() = 0;
	virtual void unused038() = 0;
	virtual void unused03c() = 0;
	virtual void unused040() = 0;
	virtual void unused044() = 0;
	virtual void unused048() = 0;
	virtual void unused04c() = 0;
	virtual void unused050() = 0;
	virtual void unused054() = 0;
	virtual void unused058() = 0;
	virtual void unused05c() = 0;
	virtual void unused060() = 0;
	virtual void unused064() = 0;
	virtual void unused068() = 0;
	virtual void unused06c() = 0;
	virtual void unused070() = 0;
	virtual void unused074() = 0;
	virtual void unused078() = 0;
	virtual void unused07c() = 0;
	virtual void unused080() = 0;
	virtual void unused084() = 0;
	virtual void unused088() = 0;
	virtual void unused08c() = 0;
	virtual void unused090() = 0;
	virtual void unused094() = 0;
	virtual void unused098() = 0;
	virtual void unused09c() = 0;
	virtual void unused0a0() = 0;
	virtual void unused0a4() = 0;
	virtual void unused0a8() = 0;
	virtual void unused0ac() = 0;
	virtual void unused0b0() = 0;
	virtual void unused0b4() = 0;
	virtual void unused0b8() = 0;
	virtual void unused0bc() = 0;
	virtual void unused0c0() = 0;
	virtual void unused0c4() = 0;
	virtual void unused0c8() = 0;
	virtual void unused0cc() = 0;
	virtual void unused0d0() = 0;
	virtual void unused0d4() = 0;
	virtual void unused0d8() = 0;
	virtual void unused0dc() = 0;
	virtual void unused0e0() = 0;
	virtual void unused0e4() = 0;
	virtual void unused0e8() = 0;
	virtual void unused0ec() = 0;
	virtual void unused0f0() = 0;
	virtual void unused0f4() = 0;
	virtual void unused0f8() = 0;
	virtual void unused0fc() = 0;
	virtual void unused100() = 0;
	virtual void unused104() = 0;
	virtual void unused108() = 0;
	virtual void unused10c() = 0;
	virtual void unused110() = 0;
	virtual void unused114() = 0;
	virtual void unused118() = 0;
	virtual void unused11c() = 0;
	virtual void unused120() = 0;
	virtual void unused124() = 0;
	virtual void unused128() = 0;
	virtual void unused12c() = 0;
	virtual void unused130() = 0;
	virtual void unused134() = 0;
	virtual void unused138() = 0;
	virtual void unused13c() = 0;
	virtual void unused140() = 0;
	virtual void unused144() = 0;
	virtual void unused148() = 0;
	virtual void unused14c() = 0;
	virtual AIUpdateInterface *getModuleCollection() = 0;

	float getRange() const { return m_goalRange470; }
	Bool testFlag(Int bit) const { return (m_flags3f0 >> bit) & 1; }
	Bool findNearestLabeledContactPointOnTarget(Object *target,
		Coord3D *result, const Coord3D *workingPosition, Bool skipCollideTest);
	Object *getCurrentVictim() const;

	char m_pad04[0x3ec];
	UnsignedInt m_flags3f0;
	UnsignedInt m_unreconstructed3f4;
	Int m_targetID3f8;
	UnsignedInt m_createdID3fc;
	char m_pad400[0x70];
	float m_goalRange470;
	char m_pad474[0x1c];
	char m_pad490[4];
	UnsignedInt m_field494;
};

class Object
{
public:
	virtual void unused00() = 0;
	virtual void unused04() = 0;
	virtual void unused08() = 0;
	virtual void unused0c() = 0;
	virtual void unused10() = 0;
	virtual void unused14() = 0;
	virtual void unused18() = 0;
	virtual void unused1c() = 0;
	virtual void unused20() = 0;
	virtual void unused24() = 0;
	virtual DrawableView *getDrawable() = 0;
	virtual void useAgainst(Object *target, Int targetID) = 0;
	protected:
	Module *findModule(NameKeyType key) const;
	friend class AIGiantBirdAttackState;
public:
	Weapon *getCurrentWeapon(WeaponSlotType *slot);
	AIUpdateInterface *getAI() const { return m_ai204; }
	Coord3D *getPosition() { return &m_position38; }
	Bool isDead() const { return (m_privateStatus344 & 1) != 0; }
	Bool getWorldspaceBestContactPoint(Coord3D *, const Coord3D *, const char *, Int, Int, Bool) const;
	void setFiringConditionForCurrentWeapon() const;

	char m_pad04[0x34];
	Coord3D m_position38;
	char m_pad44[0x30];
	Int m_id74;
	char m_pad78[0x184];
	ModuleCollection *m_modules1fc;
	char m_pad200[4];
	AIUpdateInterface *m_ai204;
	char m_pad208[0x0c];
	TargetSubobject *m_subobject214;
	char m_pad218[0x24];
	Team *m_team23c;
	char m_pad240[0x104];
	unsigned char m_privateStatus344;
	char m_pad345[0x8f];
};

class StateMachine
{
public:
	char m_pad00[0x10];
	Object *m_owner;
};

class State
{
public:
	virtual StateReturnType unused00() = 0;
	virtual void unused04() = 0;
	virtual void unused08() = 0;
	virtual void unused0c() = 0;
	virtual void unused10() = 0;
	virtual void unused14() = 0;
	virtual void unused18() = 0;

	Int m_id;
	Int m_successStateID;
	Int m_failureStateID;
	void *m_transitions[3];
	StateMachine *m_machine;
};

class AIGiantBirdAttackState : public State
{
public:
	virtual StateReturnType onEnter();

	char m_pad20[4];
	Int m_mode;
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

template<int N>
class BitFlags
{
public:
	_STL::bitset<N> m_words;
	BitFlags() {}
};

typedef BitFlags<86> ObjectStatusMaskType;

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *thing, Team *team,
		const ObjectStatusMaskType &status, UnsignedInt extra);
};

class Thing
{
public:
	void setMatrix(const Matrix3D *matrix);
};

class Rva001BE220Receiver
{
public:
	void dispatch(Int first, UnsignedInt second);
};

class BfmeHostETB
{
public:
	void bfmeApplyETB(class BfmeArgETB *argument);
};

extern GameLogic *TheBfmeGameLogic;
extern ThingFactory *TheThingFactory;
extern NameKeyGenerator *TheNameKeyGenerator;
Int GetGameLogicRandomValue(Int, Int, char *, Int);
extern void j_00001bae();
extern void j_00008a26();
extern void j_00011f77();
extern void j_00015ae6();
extern void j_00017512();
extern void j_0001bb21();
extern void j_0001f253();
extern void j_00023e0c();
extern void j_000261a2();
extern void j_0002852e();
extern void j_00028560();
extern void j_0002ae23();
extern void j_00031a7f();
extern void j_00034e91();
extern void j_000361ce();
extern void j_0003add7();
extern void j_0003ca65();
extern void j_0004494a();



static __forceinline Object *findObject(GameLogic *logic, Int id)
{
    typedef Object *(GameLogic::*Call)(Int);
    union { void *raw; Call member; } call;
    call.raw = (void *)j_0001f253;
    return (logic->*call.member)(id);
}

// Open BFME 2 donor: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AIGiantBirdAttackStateOnEnter.cpp
// ?onEnter@AIGiantBirdAttackState@@UAE?AW4StateReturnType@@XZ
StateReturnType AIGiantBirdAttackState::onEnter()
{
	Object *owner = m_machine->m_owner;
	AIUpdateInterface *ai = owner->getAI();
	if (ai == 0)
		return STATE_FAILURE;

	*(unsigned char *)((char *)ai + 0x490) = 1;
	if (owner->isDead())
		return STATE_FAILURE;

	if (ai->testFlag(3))
		return STATE_CONTINUE;

	if (m_mode == 0)
	{
		owner->setFiringConditionForCurrentWeapon();
		((BfmeHostETB *)owner)->bfmeApplyETB((BfmeArgETB *)owner->getPosition());
		return STATE_SUCCESS;
	}

	Object *victim = findObject(TheBfmeGameLogic, ai->m_targetID3f8);
	if (victim == 0 || victim->isDead())
		return STATE_SUCCESS;

	Coord3D pos;
	if (!ai->findNearestLabeledContactPointOnTarget(victim, &pos, owner->getPosition(), false))
	{
		victim->getWorldspaceBestContactPoint(&pos, owner->getPosition(), 0, 1,
			GetGameLogicRandomValue(0, 12345678, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate\\GiantBirdAIUpdate.cpp", 0x35B), false);
	}

	Real range = (8.5f > ai->getRange() * 3.0f ? 8.5f : ai->getRange() * 3.0f);
	if (((const Gen_000E5A50 *)owner)->bfmeDistanceSquared((const BfmeVec3EJ *)&pos) > range * range)
		return STATE_FAILURE;

	if (ai->testFlag(4))
	{
		Object *container = (Object *)victim->m_subobject214;
		if (container != 0)
		{
			ModuleCollection *victimContain = container->m_modules1fc;
			if (victimContain != 0)
			{
				TargetSubobject *rider = ((TargetSubobject *)victimContain)->unused68();
				if (rider != 0)
					rider->unused38(victim);
			}
		}

		ModuleCollection *contain = owner->m_modules1fc;
		ModuleRange *items = contain->getHead();
		Int count = 0;
		ModuleNode *head = *(ModuleNode **)items;
		for (ModuleNode *node = head->m_next; node != head; )
		{
			Module *item = node->m_value;
			node = node->m_next;
			if ((item->m_flags94 & 0x80) == 0)
			{
				++count;
				break;
			}
		}
		if (count == 0)
		{
			contain->registerObject(victim);
			ai->m_createdID3fc = victim->m_id74;
		}

		if ((Object *)victim->m_subobject214 == owner)
		{
			const Weapon *weapon = owner->getCurrentWeapon(0);
			if (weapon != 0 && weapon->getData() != 0 && weapon->getData()->getEnabled())
			{
				const FXList *fx = weapon->getData()->getFireFX();
				DrawableView *draw = owner->getDrawable();
				if (fx != 0 && draw != 0)
				{
					Real speed = weapon->getData()->getSpeed();
					const Matrix3D *mtx = (const Matrix3D *)((BfmeCalc919G *)draw)->bfmeCalc919G();
					if (!((FXList *)fx)->bfmeIsBlocked()) fx->doFXPos(victim->getPosition(), mtx, speed, victim->getPosition());
				}
			}
			ai->m_flags3f0 |= 0x40;
			return STATE_SUCCESS;
		}

		owner->setFiringConditionForCurrentWeapon();
		((BfmeHostETB *)owner)->bfmeApplyETB((BfmeArgETB *)victim->getPosition());
		return STATE_FAILURE;
	}

	owner->setFiringConditionForCurrentWeapon();
	owner->useAgainst(victim, victim->m_id74);

	if (victim->isDead() && ai->testFlag(5))
	{
		ai->m_flags3f0 &= ~0x20;
		ModuleCollection *contain = owner->m_modules1fc;
		if (contain != 0 && contain->getBegin(0) < contain->getEnd())
		{
			AsciiString name("");
			static NameKeyType key = TheNameKeyGenerator->nameToKey("CreateObjectDie");
			Module *module = victim->findModule(key);
			if (module != 0)
				name.set(*(AsciiString *)((char *)*(void **)((char *)module + 4) + 0x38));
			const ThingTemplate *tmplate =
				((BfmeThingFactory *)TheThingFactory)->findTemplate(name);
			if (tmplate != 0)
			{
				Team *team = victim->m_team23c;
				ObjectStatusMaskType mask;
				Object *created = TheThingFactory->newObject(tmplate, team, mask, 0);
				if (created != 0)
				{
					((Thing *)created)->setMatrix((const Matrix3D *)((char *)owner + 8));
					contain->registerObject(created);
					ai->m_flags3f0 |= 0x40;
					ai->m_createdID3fc = created->m_id74;
				}
			}
		}
	}
	else
	{
		AIUpdateInterface *victimAI = victim->getAI() ? victim->getAI()->getModuleCollection() : 0;
		if (victimAI != 0)
		{
			((Rva001BE220Receiver *)victim)->dispatch(0xA2, 5);
			((Rva001BE220Receiver *)victim)->dispatch(0x79, 5);
			if (victimAI->getCurrentVictim() == owner && ai->m_field494 == 1 &&
				victimAI->m_field494 == 0)
			{
				victim->useAgainst(owner, owner->m_id74);
				((Rva001BE220Receiver *)victim)->dispatch(6, 5);
			}
		}
	}
	return STATE_SUCCESS;
}
