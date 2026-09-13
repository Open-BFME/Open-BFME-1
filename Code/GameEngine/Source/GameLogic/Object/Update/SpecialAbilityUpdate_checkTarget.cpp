// cl: /O2 /DNDEBUG /DWIN32 /MD /EHsc
// ?checkTarget@SpecialAbilityUpdate@@QAE_NPAVObject@@@Z

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef Int ObjectID;

#pragma comment(linker, "/alternatename:?affectedByUpgrade@Object@@QBE_NPBVUpgradeTemplate@@@Z=?j_000077b6@@YAXXZ")

class UpgradeTemplate;

class BfmeThingND
{
public:
	void *bfmeFindND(const UnsignedInt *mask);
};

extern BfmeThingND *TheUpgradeCenter;
extern void j_0001df16();

static void *bfmeFindUpgrade(const UnsignedInt *mask)
{
	typedef void *(BfmeThingND::*Function)(const UnsignedInt *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0001df16;
	return (reinterpret_cast<BfmeThingND *>(TheUpgradeCenter)->*fn.member)(mask);
}

class HordeContainInterface
{
public:
	virtual Bool slot00() = 0; virtual Bool slot01() = 0;
	virtual Bool slot02() = 0; virtual Bool slot03() = 0;
	virtual Bool slot04() = 0; virtual Bool slot05() = 0;
	virtual Bool slot06() = 0; virtual Bool slot07() = 0;
	virtual Bool slot08() = 0; virtual Bool slot09() = 0;
	virtual Bool slot10() = 0; virtual Bool slot11() = 0;
	virtual Bool slot12() = 0; virtual Bool slot13() = 0;
	virtual Bool slot14() = 0; virtual Bool slot15() = 0;
	virtual Bool slot16() = 0; virtual Bool slot17() = 0;
	virtual Bool slot18() = 0; virtual Bool slot19() = 0;
	virtual Bool slot20() = 0; virtual Bool slot21() = 0;
	virtual Bool slot22() = 0; virtual Bool slot23() = 0;
	virtual Bool slot24() = 0; virtual Bool slot25() = 0;
	virtual Bool slot26() = 0; virtual Bool slot27() = 0;
	virtual Bool slot28() = 0; virtual Bool slot29() = 0;
	virtual Bool slot30() = 0; virtual Bool slot31() = 0;
	virtual Bool slot32() = 0; virtual Bool slot33() = 0;
	virtual Bool slot34() = 0; virtual Bool slot35() = 0;
	virtual Bool slot36() = 0; virtual Bool slot37() = 0;
	virtual Bool slot38() = 0; virtual Bool slot39() = 0;
	virtual Bool slot40() = 0; virtual Bool canReceive(void *upgrade) = 0;
};

class ContainModuleInterface
{
public:
	virtual Bool slot00() = 0; virtual Bool slot01() = 0;
	virtual Bool slot02() = 0; virtual Bool slot03() = 0;
	virtual Bool slot04() = 0; virtual Bool slot05() = 0;
	virtual Bool slot06() = 0; virtual Bool slot07() = 0;
	virtual Bool slot08() = 0; virtual Bool slot09() = 0;
	virtual Bool slot10() = 0; virtual Bool slot11() = 0;
	virtual Bool slot12() = 0; virtual Bool slot13() = 0;
	virtual Bool slot14() = 0; virtual Bool slot15() = 0;
	virtual Bool slot16() = 0; virtual Bool slot17() = 0;
	virtual Bool slot18() = 0; virtual Bool slot19() = 0;
	virtual Bool slot20() = 0; virtual Bool slot21() = 0;
	virtual Bool slot22() = 0; virtual Bool slot23() = 0;
	virtual Bool slot24() = 0; virtual Bool slot25() = 0;
	virtual HordeContainInterface *getHordeContainInterface() = 0;
};

class Object
{
public:
	Bool affectedByUpgrade(const UpgradeTemplate *upgrade) const;

	char m_pad00[0x78];
	ObjectID m_producerID;
	char m_pad7c[0x180];
	ContainModuleInterface *m_contain;
	char m_pad200[0x14];
	Object *m_containedBy;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheBfmeGameLogic;

class SpecialAbilityUpdate
{
public:
	Bool checkTarget(Object *target);
};

// ?checkTarget@SpecialAbilityUpdate@@QAE_NPAVObject@@@Z
Bool SpecialAbilityUpdate::checkTarget(Object *target)
{
	Object *source = *reinterpret_cast<Object **>(
		reinterpret_cast<char *>(this) + 8);
	void *upgrade = bfmeFindUpgrade(reinterpret_cast<const UnsignedInt *>(
		reinterpret_cast<const char *>(source) + 0x224));

	if (upgrade == 0)
		return false;

	if (target->m_containedBy != 0)
	{
		Object *producer = TheBfmeGameLogic->findObjectByID(target->m_producerID);
		if (producer == 0)
			goto fail;

		ContainModuleInterface *contain = producer->m_contain;
		if (contain == 0)
			goto fail;

		HordeContainInterface *horde = contain->getHordeContainInterface();
		if (horde == 0)
			goto fail;

		if (horde->canReceive(upgrade))
			return true;
		goto fail;
	}

	if (target->affectedByUpgrade(
		reinterpret_cast<const UpgradeTemplate *>(upgrade)))
		return true;

fail:
	return false;
}
