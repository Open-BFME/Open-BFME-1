// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef int Int;
typedef float Real;

enum KindOfType
{
	KINDOF_0014CA60_HORDE = 0x6c,
	KINDOF_0014CA60_HORDE_MEMBER = 0x6d,
	KINDOF_0014CA60_SIEGE_TARGET = 0x5c
};

typedef int NameKeyType;

class Object;
class BfmeOutOfWeaponRangeObject;
class Module;

class BfmeOutOfWeaponRangeTemplate
{
public:
	Bool isLeechRangeWeapon() const;
};

class BfmeOutOfWeaponRangeWeapon
{
public:
	Bool isWithinAttackRange(const BfmeOutOfWeaponRangeObject *source,
		const BfmeOutOfWeaponRangeObject *target,
		Int extra) const;

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
public:
	BfmeFourSlotEntry *bfmeGet(Int slot);
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
	Bool m_isDoingGroundMovement;
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
public:
	NameKeyType nameToKey(const char *name);
};

class Module
{
public:
	Bool is() const;
};

class Object
{
public:
	Int getLayer() const;
	Module *findModule(NameKeyType key) const;
	Real getDistanceSquared(const Object *target) const;
	Real getVisionRange() const;

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
public:
	Bool isKindOf(KindOfType kind) const;
};

class Rva00266340
{
public:
	Bool is() const;
};

extern AI *TheAI;
extern NameKeyGenerator *TheNameKeyGenerator;

#pragma comment(linker, "/alternatename:?isLeechRangeWeapon@BfmeOutOfWeaponRangeTemplate@@QBE_NXZ=?j_00028f74@@YAXXZ")
#pragma comment(linker, "/alternatename:?isWithinAttackRange@BfmeOutOfWeaponRangeWeapon@@QBE_NPBVBfmeOutOfWeaponRangeObject@@0H@Z=?j_0002e85c@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeGet@BfmeFourSlotTable@@QAEPAVBfmeFourSlotEntry@@H@Z=?j_0003c8e9@@YAXXZ")
#pragma comment(linker, "/alternatename:?isKindOf@BfmeOutOfWeaponRangeObject@@QBE_NW4KindOfType@@@Z=?j_0003251f@@YAXXZ")
#pragma comment(linker, "/alternatename:?is@Rva00266340@@QBE_NXZ=?j_00048112@@YAXXZ")
#pragma comment(linker, "/alternatename:?getLayer@Object@@QBEHXZ=?j_0003a391@@YAXXZ")
#pragma comment(linker, "/alternatename:?findModule@Object@@IBEPAVModule@@W4NameKeyType@@@Z=?j_0002ae23@@YAXXZ")
#pragma comment(linker, "/alternatename:?is@Module@@QBE_NXZ=?j_00048112@@YAXXZ")
#pragma comment(linker, "/alternatename:?getDistanceSquared@Object@@QBEMPBV1@@Z=?j_00043ced@@YAXXZ")
#pragma comment(linker, "/alternatename:?getVisionRange@Object@@QBEMXZ=?j_00014b4b@@YAXXZ")
#pragma comment(linker, "/alternatename:?nameToKey@NameKeyGenerator@@QAE?AW4NameKeyType@@PBD@Z=?j_0003add7@@YAXXZ")

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
	if ((status & 8) != 0 || ai->m_isDoingGroundMovement)
		onGround = true;

	if (source->isKindOf(KINDOF_0014CA60_HORDE))
	{
		ContainModule *contain = source->m_contain;
		if (!contain)
			return false;

		HordeContainInterface *horde = contain->slot26();
		BfmeOutOfWeaponRangeObject *weaponObject = source->isKindOf(KINDOF_0014CA60_HORDE_MEMBER)
			? horde->slot20()
			: horde->slot61();
		if (!weaponObject)
			return false;

		Int slot = 0;
		BfmeFourSlotTable *weaponSet = weaponObject->weaponSet();
		for (; slot < 4; ++slot)
		{
			BfmeFourSlotEntry *weapon = weaponSet->bfmeGet(slot);
			if (!weapon)
				continue;
			if (weapon->isWithinAttackRange(source, target, 0))
				return true;
			if (!weapon->getTemplate()->isLeechRangeWeapon())
				continue;
			if (onGround)
				goto rva0014ca60_fail;
			Bool sameLayer = target->getLayer() == source->getLayer();
			if (sameLayer)
				goto rva0014ca60_horde_distance;

			{
				if (!target->isKindOf(KINDOF_0014CA60_SIEGE_TARGET))
					continue;

				static NameKeyType siegeDeploySpecialPowerKey =
					TheNameKeyGenerator->nameToKey("SiegeDeploySpecialPower");
				Module *module = target->findModule(siegeDeploySpecialPowerKey);
			if (!module || !((Rva00266340 *)module)->is())
					continue;

			}

			rva0014ca60_horde_distance:
			Real distance = source->getDistanceSquared(target);
			Real radius = source->getVisionRange();
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
		BfmeFourSlotEntry *weapon = weaponSet->bfmeGet(slot);
		if (!weapon)
			continue;
		if (weapon->isWithinAttackRange(source, target, 0))
			return true;
		if (!weapon->getTemplate()->isLeechRangeWeapon())
			continue;
		if (onGround)
			goto rva0014ca60_fail;
		if (target->getLayer() != source->getLayer())
			continue;

		Real distance = source->getDistanceSquared(target);
		Real radius = source->getVisionRange();
		if (radius > TheAI->m_data->m_hordeAttackRadius)
			radius = TheAI->m_data->m_hordeAttackRadius;
		if (distance < radius * radius)
			return true;
	}

	rva0014ca60_fail:
	return false;
}
