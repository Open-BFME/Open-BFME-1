// cl: /DNDEBUG /MD /EHsc
// BFME's queue-upgrade body receives the production interface subobject.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#define TRUE true
#define FALSE false
#define NULL 0

#pragma comment(linker, "/alternatename:?getControllingPlayer@Object@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?hasUpgrade@Object@@QBE_NPBVUpgradeTemplate@@@Z=?j_0000ba37@@YAXXZ")
#pragma comment(linker, "/alternatename:?affectedByUpgrade@Object@@QBE_NPBVUpgradeTemplate@@@Z=?j_000077b6@@YAXXZ")
#pragma comment(linker, "/alternatename:?hasUpgradeInProduction@Player@@QAE_NPBVUpgradeTemplate@@@Z=?j_00020c8e@@YAXXZ")
#pragma comment(linker, "/alternatename:?canAffordUpgrade@UpgradeCenter@@QBE_NPAVPlayer@@PBVUpgradeTemplate@@PBVThingTemplate@@_N@Z=?j_0001cea9@@YAXXZ")
#pragma comment(linker, "/alternatename:??0ProductionEntry@@QAE@XZ=?j_00047dfc@@YAXXZ")
#pragma comment(linker, "/alternatename:?calcCostToBuild@UpgradeTemplate@@QBEHPAVPlayer@@PBVThingTemplate@@@Z=?j_0003f8d7@@YAXXZ")
#pragma comment(linker, "/alternatename:?withdraw@Money@@QAEII_N@Z=?j_00041894@@YAXXZ")
#pragma comment(linker, "/alternatename:?addToProductionQueue@ProductionUpdate@@IAEXPAVProductionEntry@@@Z=?j_000450f7@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0036BB10FindCastleMemberBehavior@@YAPAVModule@@PBVObject@@@Z=?j_0000e6e7@@YAXXZ")

enum UpgradeType
{
	UPGRADE_TYPE_PLAYER = 0,
	UPGRADE_TYPE_OBJECT = 1
};

enum UpgradeStatusType
{
	UPGRADE_STATUS_IN_PRODUCTION = 1
};

class Object;
class Player;
class Module;
class ModuleData;
class Money;
class ThingTemplate;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeTemplate
{
public:
	UpgradeType getUpgradeType() const { return m_type; }
	Int calcCostToBuild(Player *player, const ThingTemplate *thingTemplate) const;

	char m_bfmeBase[4];
	UpgradeType m_type;
	char m_bfmeLayout08[0x10c];
	Int m_bfmeLayout114;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeCenter
{
public:
	Bool canAffordUpgrade(Player *player, const UpgradeTemplate *upgrade,
		const ThingTemplate *thingTemplate, Bool forceCheck) const;
};

extern UpgradeCenter *TheUpgradeCenter;

class Money
{
public:
	UnsignedInt withdraw(UnsignedInt amount, Bool playSound);
};

class Player
{
public:
	Bool hasUpgradeComplete(const UpgradeTemplate *upgrade);
	Bool hasUpgradeInProduction(const UpgradeTemplate *upgrade);
	class Upgrade *addUpgrade(const UpgradeTemplate *upgrade, UpgradeStatusType status);

	char m_bfmeHead[0x48];
	Money m_money;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
};

class ProductionUpdateModuleData
{
	char m_bfmeHead[0x28];
public:
	Int m_maxQueueEntries;
};

class CastleMemberModuleData
{
	char m_bfmeHead[0x28];
public:
	Bool m_isCastleMember;
};

class Module
{
public:
	virtual ~Module();

	CastleMemberModuleData *m_data;
};

Module *rva0036BB10FindCastleMemberBehavior(const Object *object);

class Object
{
public:
	Player *getControllingPlayer() const;
	Bool hasUpgrade(const UpgradeTemplate *upgrade) const;
	Bool affectedByUpgrade(const UpgradeTemplate *upgrade) const;
};

class ProductionEntry
{
public:
	enum ProductionEntryMagicEnum
	{
		ProductionEntry_GLUE_NOT_IMPLEMENTED = 0
	};

	ProductionEntry() throw();
	virtual ~ProductionEntry();
	static void *operator new(unsigned int size, ProductionEntryMagicEnum)
	{
		return ::operator new(size);
	}

	Int m_type;
	char m_padding08[4];
	const UpgradeTemplate *m_upgradeToResearch;
	Int m_productionID;
	char m_padding14[0x14];
	Int m_cost;
	char m_padding2c[0xc];
	Int m_productionQuantity;
	char m_padding3c[0xc];
};

struct BfmeProductionUpdateLayout
{
	char m_padding00[4];
	ProductionUpdateModuleData *m_moduleData;
	Object *m_object;
	char m_padding0c[0x1c];
	void *m_productionQueue;
	void *m_productionQueueTail;
	UnsignedInt m_uniqueID;
	UnsignedInt m_productionCount;
};

class ProductionUpdate
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual Bool queueUpgrade(const UpgradeTemplate *upgrade, const ThingTemplate *thingTemplate);
	virtual void slot10();
	virtual Bool isUpgradeInQueue(const UpgradeTemplate *upgrade) const;

	protected:
	void addToProductionQueue(ProductionEntry *production);

	public:
	Object *getObject()
	{
		return *reinterpret_cast<Object **>(reinterpret_cast<unsigned char *>(this) - 0x18);
	}
	ProductionUpdate *getOwner()
	{
		return reinterpret_cast<ProductionUpdate *>(reinterpret_cast<char *>(this) - 0x20);
	}
};

Bool ProductionUpdate::queueUpgrade(const UpgradeTemplate *upgradeArg, const ThingTemplate *thingTemplate)
{
	ProductionEntry *production;
	register const UpgradeTemplate *upgrade = upgradeArg;
	if (upgrade == NULL)
		return FALSE;

	Player *player = getObject()->getControllingPlayer();
	if (upgrade->getUpgradeType() == UPGRADE_TYPE_PLAYER &&
		TheUpgradeCenter->canAffordUpgrade(player, upgrade, thingTemplate, FALSE) == FALSE)
		return FALSE;
	if (upgrade->getUpgradeType() == UPGRADE_TYPE_OBJECT)
	{
		if (getObject()->hasUpgrade(upgrade) == TRUE)
			return FALSE;
		if (getObject()->affectedByUpgrade(upgrade) == FALSE)
			return FALSE;
	}
	if (isUpgradeInQueue(upgrade) == TRUE)
		return FALSE;

	if (upgrade->getUpgradeType() == UPGRADE_TYPE_PLAYER &&
		(player->hasUpgradeComplete(upgrade) ||
		 player->hasUpgradeInProduction(upgrade)))
		return FALSE;

	if (*reinterpret_cast<UnsignedInt *>(reinterpret_cast<char *>(this) + 0x14) >=
		*reinterpret_cast<UnsignedInt *>(reinterpret_cast<char *>(*reinterpret_cast<ProductionUpdateModuleData **>(reinterpret_cast<char *>(this) - 0x1c)) + 0x28))
		return FALSE;

	production = new (ProductionEntry::ProductionEntry_GLUE_NOT_IMPLEMENTED) ProductionEntry;
	production->m_type = 2;
	production->m_upgradeToResearch = upgrade;
	production->m_productionID = 0;
	production->m_productionQuantity = upgrade->m_bfmeLayout114;
	production->m_cost = upgrade->calcCostToBuild(player, thingTemplate);

	player->m_money.withdraw(production->m_cost, TRUE);
	Object *object = getObject();
	Module *module = rva0036BB10FindCastleMemberBehavior(object);
	if (module != NULL && module->m_data->m_isCastleMember)
		*reinterpret_cast<float *>(reinterpret_cast<char *>(object) + 0x258) = (float)production->m_cost;

	reinterpret_cast<ProductionUpdate *>(reinterpret_cast<char *>(this) - 0x20)->addToProductionQueue(production);
	player->addUpgrade(upgrade, UPGRADE_STATUS_IN_PRODUCTION);
	return TRUE;
}
