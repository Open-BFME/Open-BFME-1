// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath
// stlport
// ?visit@Rva21ABF0Worker@@QAEXPAX@Z  @ 0x00225700 (484 bytes)
// Address-derived ring visitor. Identity: ILT pin 0x00003288 names
// Rva21ABF0Worker::visit(void*); the matched caller
// Rva21ABF0RingDispatch::dispatchAll (0x0021ABF0) reaches this body through
// that ILT. Retail returns with ret 4 at +0x1E1 and pads with INT3 at +0x1E4,
// which proves the 484-byte extent. The body tests a 192-bit kind mask, does
// drawable cleanup, applies a motive force, builds a DamageInfo, resolves a
// lookup object and kills it. No source declaration names the owner, so the
// symbol keeps its address token.
struct Rva21ABF0Node
{
	Rva21ABF0Node *next;
	Rva21ABF0Node *previous;
	void *value;
};

struct Rva21ABF0List
{
	Rva21ABF0Node *sentinel;

	Rva21ABF0Node *begin(void) const
	{
		return sentinel->next;
	}

	Rva21ABF0Node *end(void) const
	{
		return sentinel;
	}
};

class Rva21ABF0Worker;

extern void j_00003288(void);

struct Rva21ABF0WorkerCallView
{
	void visit(void *value);
};

class Object;

class Rva21ABF0RingDispatch
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual void slot15(void);
	virtual void slot16(void);
	virtual void slot17(void);
	virtual void slot18(void);
	virtual void slot19(void);
	virtual void slot20(void);
	virtual void slot21(void);
	virtual void slot22(void);
	virtual void slot23(void);
	virtual void slot24(void);
	virtual void slot25(void);
	virtual void slot26(void);
	virtual void slot27(void);
	virtual void slot28(void);
	virtual void slot29(void);
	virtual void slot30(void);
	virtual void slot31(void);
	virtual void slot32(void);
	virtual void slot33(void);
	virtual void slot34(void);
	virtual void slot35(void);
	virtual void slot36(Object *object, int flags);
	virtual void slot37(void);
	virtual void slot38(void);
	virtual void slot39(void);
	virtual void slot40(void);
	virtual void slot41(void);
	virtual void slot42(void);
	virtual void slot43(void);
	virtual void slot44(void);
	virtual void slot45(void);
	virtual void slot46(void);
	virtual void slot47(void);
	virtual void slot48(void);
	virtual void slot49(void);
	virtual void slot50(void);
	virtual void slot51(void);
	virtual void slot52(void);
	virtual void slot53(void);
	virtual void slot54(void);
	virtual void slot55(void);
	virtual void slot56(void);
	virtual void slot57(void);
	virtual void slot58(void);
	virtual void slot59(void);
	virtual void slot60(void);
	virtual void slot61(void);
	virtual void slot62(void);
	virtual void slot63(void);
	virtual void slot64(void);
	virtual Rva21ABF0List *first(void);
	virtual Rva21ABF0List *second(void);
	void dispatchAll(void);
	void finish(void);

private:
	char m_gap[0x998];
	Rva21ABF0Node *m_ring;
};

typedef float Real;

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
#define _OPERATOR_NEW_DEFINED_
#include "vector3.h"

struct KindOfMask
{
	_STL::bitset<192> m_bits;

	KindOfMask(int first, int second)
	{
		m_bits._Unchecked_set((size_t)first);
		m_bits._Unchecked_set((size_t)second);
	}
};

class Thing
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	bool isAnyKindOf(const KindOfMask &mask) const;
};

#include "../../../Libraries/Include/Lib/Coord3D.h"

class Gen_00411DD0
{
public:
	void bfmeSet(bool enabled);
};

class Drawable : public Gen_00411DD0
{
};

enum DamageType
{
	DAMAGE_UNRESISTABLE = 8
};

enum DeathType
{
	DEATH_NORMAL = 0,
	DEATH_BURNED = 3
};

struct BFMEDamageInfoInput
{
	unsigned char m_unknown00[8];
	int m_sourceID;
	unsigned char m_unknown0c[4];
	DamageType m_damageType;
	unsigned char m_unknown14[4];
	DeathType m_deathType;
	Real m_amount;
	int m_kill;
};

struct BFMEDamageInfo
{
	BFMEDamageInfo();
	BFMEDamageInfoInput in;
	unsigned char m_unknown24[0x5c - 0x24];
};

class Rva21ABF0BodyModule
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual Real getMaxHealth(void);
};

class PhysicsBehavior
{
public:
	void applyMotiveForce(const Coord3D *force);
};

struct Rva21ABF0LookupValue
{
	unsigned char m_unknown00[8];
	int m_id;
};

class Rva21ABF0LookupView
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual Rva21ABF0LookupValue *slot15(void);
};

class Object : public Thing
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual Drawable *getDrawable(void) const;
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void attemptDamage(BFMEDamageInfo *info);

	void kill(DamageType damageType, DeathType deathType);
	Rva21ABF0BodyModule *getBodyModule(void) const
	{
		return (Rva21ABF0BodyModule *)m_pointer200;
	}
	PhysicsBehavior *getPhysicsBehavior(void) const
	{
		return (PhysicsBehavior *)m_pointer208;
	}

	unsigned char m_unknown04[4];
	Real m_forceScaleX;
	unsigned char m_unknown0c[0x0c];
	Real m_forceScaleY;
	unsigned char m_unknown1c[0x58];
	int m_id;
	unsigned char m_unknown78[0xc4];
	float m_unknown13c;
	unsigned char m_unknown140[0x13];
	unsigned char m_unknown153;
	unsigned char m_unknown154[0xac];
	void *m_pointer200;
	unsigned char m_unknown204[4];
	void *m_pointer208;
	unsigned char m_unknown20c[0x138];
	unsigned char m_privateStatus;
};

class OpenContainModuleDataView
{
public:
	unsigned char m_unknown00[0x13c];
	Real m_damagePercentageToUnits;
	int m_containMax;
	unsigned char m_unknown144[0x0f];
	unsigned char m_unknown153;
};

class BFMEReportDamageSource
{
public:
	void report(Object *object, int flags);
};

class GameLogic
{
public:
	void destroyObject(Object *object);
	Object *findObjectByID(int objectID);
};

class Rva00367E30Logic : public GameLogic
{
};

// Retail 0x012F0898 is ?TheGameLogic@@3PAVGameLogic@@A (data_rows.csv,
// GameLogic.cpp); TheBfmeGameLogic was only a pin nothing defines.
class GameLogic;
extern GameLogic *TheGameLogic;
#define TheBfmeGameLogic ( reinterpret_cast<Rva00367E30Logic *>( TheGameLogic ) )
extern float g_bfmeDefaultBU;
int GetGameLogicRandomValue(int minimum, int maximum, char *source, int line);

class Rva21ABF0Worker
{
public:
	void *m_unknown00;
	OpenContainModuleDataView *m_moduleData;
	Object *m_owner;
	unsigned char m_unknown0c[0x14];
	Rva21ABF0RingDispatch m_dispatch;

	void visit(void *value);
};

void Rva21ABF0Worker::visit(void *value)
{
	Object *object = (Object *)value;
	Real damage;
	OpenContainModuleDataView *moduleData = m_moduleData;

	{
		KindOfMask mask(93, 96);
		if (object->isAnyKindOf(mask))
		{
			if (object->getDrawable() != 0)
				object->getDrawable()->bfmeSet(true);
			TheBfmeGameLogic->destroyObject(object);
			return;
		}
	}

	if (moduleData->m_unknown153)
	{
		m_dispatch.slot36(object, 0);
		PhysicsBehavior *physics = object->getPhysicsBehavior();
		if (physics != 0)
		{
			Vector3 scaled(object->m_forceScaleX, object->m_forceScaleY, 1.0f);
			int forceMagnitude = GetGameLogicRandomValue(
				2, 5,
				(char *)"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\OpenContain.cpp",
				0x840);
			scaled *= (Real)forceMagnitude;
            Coord3D force;
            force.x = scaled.X;
            force.y = scaled.Y;
            force.z = scaled.Z;
			physics->applyMotiveForce(&force);
		}

		object->kill(DAMAGE_UNRESISTABLE, DEATH_NORMAL);

		Rva21ABF0LookupView *lookup =
			(Rva21ABF0LookupView *)m_owner->m_pointer200;
		if (lookup != 0)
		{
			Rva21ABF0LookupValue *lookupValue = lookup->slot15();
			if (lookupValue != 0)
			{
				Object *reportedObject = TheBfmeGameLogic->findObjectByID(
					lookupValue->m_id);
				if (reportedObject != 0)
				{
					((BFMEReportDamageSource *)reportedObject)->report(object, 1);
					return;
				}
			}
		}
	}

	else {
	moduleData = m_moduleData;
	damage = object->getBodyModule()->getMaxHealth() *
		moduleData->m_damagePercentageToUnits;
	BFMEDamageInfo info;
	info.in.m_damageType = DAMAGE_UNRESISTABLE;
	info.in.m_deathType = DEATH_BURNED;
	info.in.m_sourceID = m_owner->m_id;
	info.in.m_amount = damage;
	object->attemptDamage(&info);

	if (object->m_privateStatus & 1)
		return;
	if (m_moduleData->m_damagePercentageToUnits == g_bfmeDefaultBU)
		object->kill(DAMAGE_UNRESISTABLE, DEATH_NORMAL);
}
}
