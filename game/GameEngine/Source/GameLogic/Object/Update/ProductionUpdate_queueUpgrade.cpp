// cl: /DNDEBUG /MD /EHsc
// BFME's queue-upgrade body receives the production interface subobject.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#define TRUE true
#define FALSE false
#define NULL 0

// Retail calls each of the bodies below through an incremental-link thunk, so
// this TU reaches them through the thunk addresses rather than through the
// stand-in member/free names.
extern void j_00020824();	// ILT -> Object::getControllingPlayer
extern void j_0000ba37();	// ILT -> Object::hasUpgrade
extern void j_000077b6();	// ILT -> Object::affectedByUpgrade
extern void j_00020c8e();	// ILT -> Player::hasUpgradeInProduction
extern void j_0001cea9();	// ILT -> UpgradeCenter::canAffordUpgrade
extern void j_00047dfc();	// ILT -> ProductionEntry::ProductionEntry
extern void j_0003f8d7();	// ILT -> UpgradeTemplate::calcCostToBuild
extern void j_00041894();	// ILT -> Money::withdraw
extern void j_000450f7();	// ILT -> ProductionUpdate::addToProductionQueue
extern void j_0000e6e7();	// ILT -> rva0036BB10FindCastleMemberBehavior

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

	char m_bfmeBase[4];
	UpgradeType m_type;
	char m_bfmeLayout08[0x10c];
	Int m_bfmeLayout114;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeCenter
{
public:
};

extern UpgradeCenter *TheUpgradeCenter;

class Money
{
public:
};

class Player
{
public:
	Bool hasUpgradeComplete(const UpgradeTemplate *upgrade);
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

class Object
{
public:
};

class ProductionEntry
{
public:
	virtual ~ProductionEntry();

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

// View of ProductionEntry used only to reach its constructor through a
// pointer-to-member, since the constructor is never called on real storage here.
struct ProductionEntryCtor
{
	ProductionEntryCtor *construct();
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

	typedef Player *(Object::*GetControllingPlayer)() const;
	typedef Bool (Object::*HasUpgrade)(const UpgradeTemplate *) const;
	typedef Bool (Object::*AffectedByUpgrade)(const UpgradeTemplate *) const;
	typedef Bool (Player::*HasUpgradeInProduction)(const UpgradeTemplate *);
	typedef Bool (UpgradeCenter::*CanAffordUpgrade)(Player *, const UpgradeTemplate *, const ThingTemplate *, Bool) const;
	typedef Int (UpgradeTemplate::*CalcCostToBuild)(Player *, const ThingTemplate *) const;
	typedef UnsignedInt (Money::*Withdraw)(UnsignedInt, Bool);
	typedef void (ProductionUpdate::*AddToQueue)(ProductionEntry *);
	typedef ProductionEntryCtor *(ProductionEntryCtor::*Construct)();
	typedef Module *(__cdecl *FindCastleMemberBehavior)(const Object *);

	union { void (*fn)(); GetControllingPlayer call; } uControllingPlayer = { j_00020824 };
	union { void (*fn)(); HasUpgrade call; } uHasUpgrade = { j_0000ba37 };
	union { void (*fn)(); AffectedByUpgrade call; } uAffectedByUpgrade = { j_000077b6 };
	union { void (*fn)(); HasUpgradeInProduction call; } uHasUpgradeInProduction = { j_00020c8e };
	union { void (*fn)(); CanAffordUpgrade call; } uCanAffordUpgrade = { j_0001cea9 };
	union { void (*fn)(); CalcCostToBuild call; } uCalcCostToBuild = { j_0003f8d7 };
	union { void (*fn)(); Withdraw call; } uWithdraw = { j_00041894 };
	union { void (*fn)(); AddToQueue call; } uAddToQueue = { j_000450f7 };
	union { void (*fn)(); Construct call; } uCtor = { j_00047dfc };
	union { void (*fn)(); FindCastleMemberBehavior call; } uFindCastleMemberBehavior = { j_0000e6e7 };

	Player *player = (getObject()->*uControllingPlayer.call)();
	if (upgrade->getUpgradeType() == UPGRADE_TYPE_PLAYER &&
		(TheUpgradeCenter->*uCanAffordUpgrade.call)(player, upgrade, thingTemplate, FALSE) == FALSE)
		return FALSE;
	if (upgrade->getUpgradeType() == UPGRADE_TYPE_OBJECT)
	{
		if ((getObject()->*uHasUpgrade.call)(upgrade) == TRUE)
			return FALSE;
		if ((getObject()->*uAffectedByUpgrade.call)(upgrade) == FALSE)
			return FALSE;
	}
	if (isUpgradeInQueue(upgrade) == TRUE)
		return FALSE;

	if (upgrade->getUpgradeType() == UPGRADE_TYPE_PLAYER &&
		(player->hasUpgradeComplete(upgrade) ||
		 (player->*uHasUpgradeInProduction.call)(upgrade)))
		return FALSE;

	if (*reinterpret_cast<UnsignedInt *>(reinterpret_cast<char *>(this) + 0x14) >=
		*reinterpret_cast<UnsignedInt *>(reinterpret_cast<char *>(*reinterpret_cast<ProductionUpdateModuleData **>(reinterpret_cast<char *>(this) - 0x1c)) + 0x28))
		return FALSE;

	ProductionEntry *allocated = static_cast<ProductionEntry *>(::operator new(0x48));
	if (allocated != NULL)
		production = reinterpret_cast<ProductionEntry *>(
			(reinterpret_cast<ProductionEntryCtor *>(allocated)->*uCtor.call)());
	else
		production = NULL;
	production->m_type = 2;
	production->m_upgradeToResearch = upgrade;
	production->m_productionID = 0;
	production->m_productionQuantity = upgrade->m_bfmeLayout114;
	production->m_cost = (upgrade->*uCalcCostToBuild.call)(player, thingTemplate);

	(player->m_money.*uWithdraw.call)(production->m_cost, TRUE);
	Object *object = getObject();
	Module *module = uFindCastleMemberBehavior.call(object);
	if (module != NULL && module->m_data->m_isCastleMember)
		*reinterpret_cast<float *>(reinterpret_cast<char *>(object) + 0x258) = (float)production->m_cost;

	(reinterpret_cast<ProductionUpdate *>(reinterpret_cast<char *>(this) - 0x20)->*uAddToQueue.call)(production);
	player->addUpgrade(upgrade, UPGRADE_STATUS_IN_PRODUCTION);
	return TRUE;
}
