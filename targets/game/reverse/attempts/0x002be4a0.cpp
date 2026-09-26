// ?d_002be4a0@@YAXXZ
// partial score=0.17 date=2026-09-25
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/stringinline

#define _STLP_NO_EXCEPTIONS 1
#include "../../../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

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

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;
class Module;
class ThingTemplate;
class Team;

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}
	void set(const AsciiString &other)
	{
		((StringBase<char> *)this)->set(
			*(const StringBase<char> *)&other);
	}
};

class BfmeCalc919G
{
public:
	int bfmeCalc919G();
};

class Gen_000E5A50
{
public:
	float bfmeDistanceSquared(const void *point) const;
};

class FXList
{
public:
	Bool bfmeIsBlocked();
	void doFXPos(const Coord3D *primary, const void *matrix, float speed,
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
	unsigned char m_enabled51f;
};

class Weapon
{
public:
	char m_pad00[4];
	WeaponData *m_data04;
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
	virtual Module *getEnd() = 0;
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
	virtual Module *getBegin() = 0;
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
	virtual AIUpdateInterface *getModuleCollection() = 0;

	Bool findNearestLabeledContactPointOnTarget(Object *target,
		Coord3D *result, const Coord3D *workingPosition, Bool skipCollideTest);
	Object *getCurrentVictim();

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
	Module *findModule(NameKeyType key) const;

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
	UnsignedInt m_words[3];
	BitFlags() : m_words() {}
};

typedef BitFlags<86> ObjectStatusMaskType;

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
	void setMatrix(const void *matrix);
};

class Rva001BE220Receiver
{
public:
	void invoke(Int first, Int second);
};

class BfmeHostETB
{
public:
	void bfmeApplyETB(void *argument);
};

#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)
#define TheThingFactory (*(ThingFactory **)0x012EF1D8)
#define TheNameKeyGenerator (*(NameKeyGenerator **)0x012ED600)
#define g_bfmeK1266A (*(float *)0x01075338)
#define g_bfmeK1266B (*(float *)0x010C7960)
#define g_CreateObjectDieInit (*(unsigned char *)0x012F02C8)
#define g_CreateObjectDieKey (*(NameKeyType *)0x012F02C4)

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

#pragma comment(linker, "/alternatename:?bfmeCalc919G@BfmeCalc919G@@QAEHXZ=?j_00017512@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeDistanceSquared@Gen_000E5A50@@QBEMPBX@Z=?j_00008a26@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeIsBlocked@FXList@@QAE_NXZ=?j_00011f77@@YAXXZ")
#pragma comment(linker, "/alternatename:?doFXPos@FXList@@QBEXPBUCoord3D@@PBVM@@M0@Z=?j_0001bb21@@YAXXZ")
#pragma comment(linker, "/alternatename:?findNearestLabeledContactPointOnTarget@AIUpdateInterface@@QAE_NPAVObject@@PAUCoord3D@@PBU2@_N@Z=?j_00015ae6@@YAXXZ")
#pragma comment(linker, "/alternatename:?findObjectByID@GameLogic@@QAEPAVObject@@H@Z=?j_0001f253@@YAXXZ")
#pragma comment(linker, "/alternatename:?setFiringConditionForCurrentWeapon@Object@@QBEXXZ=?j_00023e0c@@YAXXZ")
#pragma comment(linker, "/alternatename:?getCurrentVictim@AIUpdateInterface@@QBEPAVObject@@XZ=?j_000261a2@@YAXXZ")
#pragma comment(linker, "/alternatename:?invoke@Rva001BE220Receiver@@QAEXHH@Z=?j_0002852e@@YAXXZ")
#pragma comment(linker, "/alternatename:?findModule@Object@@QBEPAVModule@@W4NameKeyType@@@Z=?j_0002ae23@@YAXXZ")
#pragma comment(linker, "/alternatename:?getCurrentWeapon@Object@@QAEPAVObject@@PAW4WeaponSlotType@@@Z=?j_00031a7f@@YAXXZ")
#pragma comment(linker, "/alternatename:?getWorldspaceBestContactPoint@Object@@QBE_NPAUCoord3D@@PBU2@PBDHH_N@Z=?j_00034e91@@YAXXZ")
#pragma comment(linker, "/alternatename:?setMatrix@Thing@@QAEXPBVM@@Z=?j_000361ce@@YAXXZ")
#pragma comment(linker, "/alternatename:?nameToKey@NameKeyGenerator@@QAE?AW4NameKeyType@@PBD@Z=?j_0003add7@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeApplyETB@BfmeHostETB@@QAEXPAX@Z=?j_0003ca65@@YAXXZ")
#pragma comment(linker, "/alternatename:?findTemplate@ThingFactory@@QAEPBVThingTemplate@@ABVAsciiString@@@Z=?j_00028560@@YAXXZ")
#pragma comment(linker, "/alternatename:?newObject@ThingFactory@@QAEPAVObject@@PBVThingTemplate@@PAVTeam@@ABV?$BitFlags@$0FG@@@I@Z=?j_0004494a@@YAXXZ")

typedef int (__cdecl *RandomCall)(Int, Int, char *, Int);
typedef Object *(GameLogic::*FindObjectCall)(Int);
typedef Bool (AIUpdateInterface::*FindContactCall)(Object *, Coord3D *, const Coord3D *, Bool);
typedef Bool (Object::*ContactPointCall)(Coord3D *, const Coord3D *, const char *, Int, Int, Bool) const;
typedef void (Object::*SetFireCall)() const;
typedef void (BfmeHostETB::*ApplyETBCall)(void *);
typedef Weapon *(Object::*GetCurrentWeaponCall)(WeaponSlotType *);

static __forceinline Object *findObject(GameLogic *logic, Int id)
{
	union { void *raw; FindObjectCall member; } call;
	call.raw = (void *)j_0001f253;
	return (logic->*call.member)(id);
}

static __forceinline Bool findContact(AIUpdateInterface *ai, Object *target,
	Coord3D *result, const Coord3D *position)
{
	union { void *raw; FindContactCall member; } call;
	call.raw = (void *)j_00015ae6;
	return (ai->*call.member)(target, result, position, false);
}

static __forceinline Bool getContact(Object *target, Coord3D *result,
	const Coord3D *position, Int seed)
{
	union { void *raw; ContactPointCall member; } call;
	call.raw = (void *)j_00034e91;
	return (target->*call.member)(result, position, 0, 1, seed, false);
}

static __forceinline void setFiring(Object *object)
{
	union { void *raw; SetFireCall member; } call;
	call.raw = (void *)j_00023e0c;
	(object->*call.member)();
}

static __forceinline void applyETB(Object *object, void *argument)
{
	union { void *raw; ApplyETBCall member; } call;
	call.raw = (void *)j_0003ca65;
	(((BfmeHostETB *)object)->*call.member)(argument);
}

StateReturnType AIGiantBirdAttackState::onEnter()
{
	Object *owner = m_machine->m_owner;
	AIUpdateInterface *ai = owner->m_ai204;
	if (ai == 0)
		return STATE_FAILURE;

	*(unsigned char *)((char *)ai + 0x490) = 1;
	if ((owner->m_privateStatus344 & 1) != 0)
		return STATE_FAILURE;
	if (((ai->m_flags3f0 >> 3) & 1) == 0)
		return STATE_CONTINUE;

	if (m_mode == 0)
	{
		setFiring(owner);
		applyETB(owner, &owner->m_position38);
		return STATE_FAILURE;
	}

	Object *target = findObject(TheBfmeGameLogic, ai->m_targetID3f8);
	if (target == 0 || (target->m_privateStatus344 & 1) != 0)
		return STATE_SUCCESS;

	Coord3D contact;
	volatile Int stackSlot = 0;
	if (!findContact(ai, target, &contact, &owner->m_position38))
	{
		union { void *raw; RandomCall function; } randomCall;
		randomCall.raw = (void *)j_00001bae;
		Int seed = randomCall.function(0, 0xBC614E,
			(char *)0x010C7710, 0x35B);
		getContact(target, &contact, &owner->m_position38, seed);
	}

	float radius = ai->m_goalRange470 * g_bfmeK1266A;
	if (radius <= g_bfmeK1266B)
		radius = 8.5f;
	if (((Gen_000E5A50 *)owner)->bfmeDistanceSquared(&contact) > radius * radius)
		return STATE_FAILURE;

	if (((ai->m_flags3f0 >> 4) & 1) == 0)
	{
		setFiring(owner);
		applyETB(owner, &target->m_position38);
		goto targetTail;
	}

	if (target->m_subobject214 != 0)
	{
		TargetSubobject *part = target->m_subobject214;
		TargetSubobject *module = *(TargetSubobject **)
			((char *)part + 0x1fc);
		if (module != 0)
		{
			TargetSubobject *result = module->unused68(), *unused = result;
			if (result != 0)
				result->unused38(target);
		}
	}

	ModuleCollection *modules = owner->m_modules1fc;
	ModuleRange *range = modules->getHead();
	ModuleNode *head = *(ModuleNode **)((char *)range);
	ModuleNode *node = head->m_next;
	while (node != head)
	{
		Module *module = node->m_value;
		node = node->m_next;
		if ((module->m_flags94 & 0x80) == 0)
			break;
	}
	if (node == head)
	{
		modules->registerObject(target);
		ai->m_createdID3fc = target->m_id74;
	}

	if ((Object *)target->m_subobject214 != owner)
	{
		setFiring(owner);
		applyETB(owner, &target->m_position38);
		return STATE_FAILURE;
	}

	union
	{
		void *raw;
		GetCurrentWeaponCall member;
	} getCurrentWeaponCast;
	getCurrentWeaponCast.raw = (void *)j_00031a7f;
	Weapon *weapon = (owner->*getCurrentWeaponCast.member)(
		(WeaponSlotType *)0);
	if (weapon != 0 && weapon->m_data04 != 0 &&
		weapon->m_data04->m_enabled51f != 0)
	{
		FXList *fx = weapon->m_data04->m_fireFX94;
		DrawableView *drawable = owner->getDrawable();
		if (fx != 0 && drawable != 0)
		{
			BfmeCalc919G *calc = (BfmeCalc919G *)drawable;
			void *matrix = (void *)calc->bfmeCalc919G();
			if (!fx->bfmeIsBlocked())
			{
				fx->doFXPos(&target->m_position38, matrix,
					weapon->m_data04->m_speed58, &target->m_position38);
				ai->m_flags3f0 |= 0x40;
				return STATE_SUCCESS;
			}
		}
	}

	setFiring(owner);
	owner->useAgainst(target, target->m_id74);

	if ((target->m_privateStatus344 & 1) == 0 &&
		(ai->m_flags3f0 & 0x20) != 0)
	{
		ai->m_flags3f0 &= 0xffffffdf;
		ModuleCollection *ownerModules = owner->m_modules1fc;
		if (ownerModules == 0)
			return STATE_SUCCESS;
		Module *moduleBegin = ownerModules->getBegin();
		Module *moduleEnd = ownerModules->getEnd();
		if (moduleBegin >= moduleEnd)
			return STATE_SUCCESS;
		if (g_CreateObjectDieInit == 0)
		{
			g_CreateObjectDieInit = 1;
			g_CreateObjectDieKey =
				TheNameKeyGenerator->nameToKey("CreateObjectDie");
		}
		AsciiString moduleName((const char *)0x0107301C);
		Module *createDie = target->findModule(g_CreateObjectDieKey);
		if (createDie != 0)
		{
			AsciiString *name = *(AsciiString **)((char *)createDie + 4);
			moduleName.set(*(AsciiString *)((char *)name + 0x38));
		}
		const ThingTemplate *thing =
			TheThingFactory->findTemplate(moduleName);
		if (thing != 0)
		{
			ObjectStatusMaskType status;
			Object *created = TheThingFactory->newObject(
				thing, target->m_team23c, status, 0);
			if (created != 0)
			{
				((Thing *)created)->setMatrix((const void *)
					((char *)owner + 8));
				ownerModules->registerObject(created);
				ai->m_flags3f0 |= 0x40;
				ai->m_createdID3fc = created->m_id74;
			}
		}
		return STATE_SUCCESS;
	}

	targetTail:
	{
		AIUpdateInterface *targetAI = target->m_ai204;
		if (targetAI != 0)
		{
			AIUpdateInterface *related = targetAI->getModuleCollection();
			if (related != 0)
			{
				((Rva001BE220Receiver *)target)->invoke(0xa2, 5);
				((Rva001BE220Receiver *)target)->invoke(0x79, 5);
				Object *victim = related->getCurrentVictim();
				if (victim == owner && targetAI->m_field494 == 1 &&
					related->m_field494 == 0)
				{
					target->useAgainst(owner, owner->m_id74);
					((Rva001BE220Receiver *)target)->invoke(6, 5);
				}
			}
		}
	}

	return STATE_SUCCESS;
}
