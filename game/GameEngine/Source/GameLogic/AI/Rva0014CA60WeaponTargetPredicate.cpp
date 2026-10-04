// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef int Int;
typedef float Real;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
// Retail calls nameToKey through the ILT thunk ?j_0003add7@@YAXXZ; it returns
// this enum by value, so the member-pointer typedef spells it ?AW4NameKeyType@@
// (retail's defining symbol is 0x0008FFC0).
enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

enum KindOfType
{
	KINDOF_0014CA60_HORDE = 0x6c,
	KINDOF_0014CA60_HORDE_MEMBER = 0x6d,
	KINDOF_0014CA60_SIEGE_TARGET = 0x5c
};

class Object;
class BfmeOutOfWeaponRangeObject;
class Module;

class BfmeOutOfWeaponRangeTemplate
{
};

class BfmeOutOfWeaponRangeWeapon
{
public:
	BfmeOutOfWeaponRangeTemplate *getTemplate() const
	{
		return *(BfmeOutOfWeaponRangeTemplate **)((const char *)this + 4);
	}
};

class BfmeFourSlotEntry : public BfmeOutOfWeaponRangeWeapon
{
};

class BfmeFourSlotTable
{
};

class HordeContainInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual BfmeOutOfWeaponRangeObject *slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual BfmeOutOfWeaponRangeObject *slot61();
};

class ContainModule
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual HordeContainInterface *slot26();
};

class AIUpdateInterface
{
public:
	char m_pad000[0x33a];
	Bool m_playerIdle;
};

class AIData
{
public:
	char m_pad000[0x98];
	Real m_hordeAttackRadius;
};

class AI
{
public:
	char m_pad000[0x14];
	AIData *m_data;
};

class NameKeyGenerator
{
};

class Module
{
};

class Object
{
public:
	char m_pad000[0x1fc];
	ContainModule *m_contain;
	char m_pad0200[4];
	AIUpdateInterface *m_ai;

	Bool hasStatus() const
	{
		return (*(const unsigned char *)((const char *)this + 0x98) & 8) != 0;
	}

	BfmeFourSlotTable *weaponSet() const
	{
		return (BfmeFourSlotTable *)((char *)this + 0x264);
	}
};

class BfmeOutOfWeaponRangeObject : public Object
{
};

class Rva00266340
{
};

extern AI *TheAI;
extern NameKeyGenerator *TheNameKeyGenerator;

// Retail calls every predicate below through an incremental-link thunk, so the
// direct call target is the 5-byte ILT thunk `?j_...@@YAXXZ`, not the member.
extern void j_00028f74();
extern void j_0002e85c();
extern void j_0003c8e9();
extern void j_0003251f();
extern void j_00048112();
extern void j_0003a391();
extern void j_0002ae23();
extern void j_00043ced();
extern void j_00014b4b();
extern void j_0003add7();

// ?rva0014ca60@@YA_NPAVBfmeOutOfWeaponRangeObject@@0@Z
Bool __cdecl rva0014ca60(BfmeOutOfWeaponRangeObject *source,
	BfmeOutOfWeaponRangeObject *target)
{
	if (!source || !target)
		return false;

	AIUpdateInterface *ai = source->m_ai;
	if (!ai)
		return false;

	unsigned int status = *(const unsigned int *)((const char *)source + 0x98);
	volatile Bool onGround;
	onGround = false;
	if ((status & 8) != 0 || ai->m_playerIdle)
		onGround = true;

	typedef Bool (BfmeOutOfWeaponRangeObject::*KindOf)(KindOfType) const;
	union { void (*fn)(); KindOf call; } kindOf = { j_0003251f };

	if ((source->*kindOf.call)(KINDOF_0014CA60_HORDE))
	{
		ContainModule *contain = source->m_contain;
		if (!contain)
			return false;

		HordeContainInterface *horde = contain->slot26();
		BfmeOutOfWeaponRangeObject *weaponObject = (source->*kindOf.call)(KINDOF_0014CA60_HORDE_MEMBER)
			? horde->slot20()
			: horde->slot61();
		if (!weaponObject)
			return false;

		Int slot = 0;
		BfmeFourSlotTable *weaponSet = weaponObject->weaponSet();
		for (; slot < 4; ++slot)
		{
			typedef BfmeFourSlotEntry *(BfmeFourSlotTable::*SlotGet)(Int);
			typedef Bool (BfmeOutOfWeaponRangeWeapon::*InRange)(const BfmeOutOfWeaponRangeObject *,
				const BfmeOutOfWeaponRangeObject *, Int) const;
			typedef Bool (BfmeOutOfWeaponRangeTemplate::*Leech)() const;
			typedef Int (Object::*Layer)() const;
			typedef Real (Object::*DistSq)(const Object *) const;
			typedef Real (Object::*Vision)() const;
			union { void (*fn)(); SlotGet call; } slotGet = { j_0003c8e9 };
			union { void (*fn)(); InRange call; } inRange = { j_0002e85c };
			union { void (*fn)(); Leech call; } leech = { j_00028f74 };
			union { void (*fn)(); Layer call; } layer = { j_0003a391 };
			union { void (*fn)(); DistSq call; } distSq = { j_00043ced };
			union { void (*fn)(); Vision call; } vision = { j_00014b4b };
			BfmeFourSlotEntry *weapon = (weaponSet->*slotGet.call)(slot);
			if (!weapon)
				continue;
			if ((weapon->*inRange.call)(source, target, 0))
				return true;
			BfmeOutOfWeaponRangeTemplate *tmpl = weapon->getTemplate();
			if (!(tmpl->*leech.call)())
				continue;
			if (onGround)
				goto rva0014ca60_fail;
			Bool sameLayer = (target->*layer.call)() == (source->*layer.call)();
			if (sameLayer)
				goto rva0014ca60_horde_distance;

			{
				if (!(target->*kindOf.call)(KINDOF_0014CA60_SIEGE_TARGET))
					continue;

				typedef NameKeyType (NameKeyGenerator::*NameToKey)(const char *);
				typedef Module *(Object::*FindModule)(NameKeyType) const;
				typedef Bool (Rva00266340::*Is)() const;
				union { void (*fn)(); NameToKey call; } nameToKey = { j_0003add7 };
				union { void (*fn)(); FindModule call; } findModule = { j_0002ae23 };
				union { void (*fn)(); Is call; } is = { j_00048112 };
				static NameKeyType siegeDeploySpecialPowerKey =
					(TheNameKeyGenerator->*nameToKey.call)("SiegeDeploySpecialPower");
				Module *module = (target->*findModule.call)(siegeDeploySpecialPowerKey);
				if (!module || !(((Rva00266340 *)module)->*is.call)())
					continue;

			}

			rva0014ca60_horde_distance:
			Real distance = (source->*distSq.call)(target);
			Real radius = (source->*vision.call)();
			if (radius > TheAI->m_data->m_hordeAttackRadius)
				radius = TheAI->m_data->m_hordeAttackRadius;
			if (distance < radius * radius)
				return true;
		}
		return false;
	}

	BfmeFourSlotTable *weaponSet = source->weaponSet();
	for (Int slot = 0; slot < 4; ++slot)
	{
		typedef BfmeFourSlotEntry *(BfmeFourSlotTable::*SlotGet)(Int);
		typedef Bool (BfmeOutOfWeaponRangeWeapon::*InRange)(const BfmeOutOfWeaponRangeObject *,
			const BfmeOutOfWeaponRangeObject *, Int) const;
		typedef Bool (BfmeOutOfWeaponRangeTemplate::*Leech)() const;
		typedef Int (Object::*Layer)() const;
		typedef Real (Object::*DistSq)(const Object *) const;
		typedef Real (Object::*Vision)() const;
		union { void (*fn)(); SlotGet call; } slotGet = { j_0003c8e9 };
		union { void (*fn)(); InRange call; } inRange = { j_0002e85c };
		union { void (*fn)(); Leech call; } leech = { j_00028f74 };
		union { void (*fn)(); Layer call; } layer = { j_0003a391 };
		union { void (*fn)(); DistSq call; } distSq = { j_00043ced };
		union { void (*fn)(); Vision call; } vision = { j_00014b4b };
		BfmeFourSlotEntry *weapon = (weaponSet->*slotGet.call)(slot);
		if (!weapon)
			continue;
		if ((weapon->*inRange.call)(source, target, 0))
			return true;
		BfmeOutOfWeaponRangeTemplate *tmpl = weapon->getTemplate();
		if (!(tmpl->*leech.call)())
			continue;
		if (onGround)
			goto rva0014ca60_fail;
		if ((target->*layer.call)() != (source->*layer.call)())
			continue;

		Real distance = (source->*distSq.call)(target);
		Real radius = (source->*vision.call)();
		if (radius > TheAI->m_data->m_hordeAttackRadius)
			radius = TheAI->m_data->m_hordeAttackRadius;
		if (distance < radius * radius)
			return true;
	}

	rva0014ca60_fail:
	return false;
}
