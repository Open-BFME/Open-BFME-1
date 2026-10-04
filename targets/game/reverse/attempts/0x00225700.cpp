// ?visit@Rva21ABF0Worker@@QAEXPAX@Z
// partial score=0.4566 date=2026-10-04
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
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

template <int N>
class BitFlags
{
	_STL::bitset<N> m_bits;

public:
	enum BogusInitType { kInit = 0 };

	BitFlags(BogusInitType, int first, int second)
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
	bool isAnyKindOf(const BitFlags<192> &mask) const;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

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

class Rva21ABF0PhysicsBehavior
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
	Rva21ABF0PhysicsBehavior *getPhysicsBehavior(void) const
	{
		return (Rva21ABF0PhysicsBehavior *)m_pointer208;
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

extern Rva00367E30Logic *TheBfmeGameLogic;
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

void Rva21ABF0RingDispatch::dispatchAll(void)
{
	Rva21ABF0Node *node = m_ring->next;

	while (node != m_ring) {
		void *value = node->value;
		node = node->next;
		union
		{
			void *asVoid;
			void (Rva21ABF0WorkerCallView::*asMember)(void *);
		} call;
		call.asVoid = reinterpret_cast<void *>(j_00003288);
		(reinterpret_cast<Rva21ABF0WorkerCallView *>(
			(char *)this - 0x20)->*call.asMember)(value);
	}

	finish();
}

void Rva21ABF0RingDispatch::finish(void)
{
	Rva21ABF0List *list;
	Rva21ABF0Node *node;
	register int pass;
	pass = 0;
	do {
		if (pass)
			list = second();
		else
			list = first();

		if (list == 0)
			continue;

		node = list->begin();
		if (node == list->end())
			continue;

		Rva21ABF0Worker *worker =
			(Rva21ABF0Worker *)((char *)this - 0x20);
		do {
			void *value = node->value;
			node = node->next;
			union
			{
				void *asVoid;
				void (Rva21ABF0WorkerCallView::*asMember)(void *);
			} call;
			call.asVoid = reinterpret_cast<void *>(j_00003288);
			(reinterpret_cast<Rva21ABF0WorkerCallView *>(worker)->*
				call.asMember)(value);
		} while (node != list->end());

	} while (++pass < 2);
}

void Rva21ABF0Worker::visit(void *value)
{
	Object *object = (Object *)value;
	Real damage;
	OpenContainModuleDataView *moduleData = m_moduleData;

	{
		BitFlags<192> mask(BitFlags<192>::kInit, 93, 96);
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
		Rva21ABF0PhysicsBehavior *physics = object->getPhysicsBehavior();
		if (physics != 0)
		{
			Real forceScaleX = object->m_forceScaleX;
			Real forceScaleY = object->m_forceScaleY;
			int forceMagnitude = GetGameLogicRandomValue(
				2, 5,
				(char *)"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\OpenContain.cpp",
				0x840);
			Coord3D force = {
				forceScaleX * forceMagnitude,
				forceMagnitude * forceScaleY,
				(Real)forceMagnitude
			};
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

	damage = object->getBodyModule()->getMaxHealth() *
		m_moduleData->m_damagePercentageToUnits;
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
