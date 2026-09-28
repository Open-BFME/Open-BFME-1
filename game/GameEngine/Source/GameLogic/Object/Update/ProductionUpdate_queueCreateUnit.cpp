// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// ProductionUpdate::queueCreateUnit, retail 0x0029D790, 603 bytes.
//
// IDENTITY: the matched ProductionUpdate constructor (0x0029C9E0) installs the
// interface table 0x010C0E00; slot 3 (+0x0C) is the matched
// ProductionUpdate::queueUpgrade (0x0029D560) and slot 7 (+0x1C) reaches this
// body through ILT 0x0003A1BB.  Zero Hour's ProductionUpdateInterface puts
// queueCreateUnit at slot 7 after requestUniqueUnitID (+0x08, called here on
// this) and queueUpgrade (+0x0C), and the body is Zero Hour's queueCreateUnit
// with BFME's additions: a build-index path through the player's portrait
// list, a five-unit batch loop and two extra entry words.  Zero Hour calls
// unitType->calcCostToBuild(player) at the same point, which names the
// 0x0013E390 callee; BFME passes a second argument (-1).
//
// SHAPE: `Money *money = player->getMoney();` as its own local (Zero Hour's
// spelling) and `cost = 0` declared before the player make the allocator keep
// the player in esi and the cost in ebp, and leave retail's dead
// `add eax,0x48` at the loop bottom; `new ProductionEntry` with an inline
// constructor gives retail's construct-through-eax / `xor esi,esi` shape.

#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#define TRUE true
#define FALSE false
#define NULL 0

#pragma comment(linker, "/alternatename:?getControllingPlayer@Object@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?set@BfmeBuildIndexSetter@@QAEHH@Z=?j_000237d1@@YAXXZ")
#pragma comment(linker, "/alternatename:?findTemplate@BfmeThingFactory@@QAEPBVThingTemplate@@ABVAsciiString@@@Z=?j_00028560@@YAXXZ")
#pragma comment(linker, "/alternatename:?updateEntry@Rva000FA830PortraitList@@QAE_NHHPAPBVImage@@@Z=?j_0003a3f0@@YAXXZ")
#pragma comment(linker, "/alternatename:?isEquivalentTo@ThingTemplate@@QBE_NPBV1@@Z=?j_0003e80b@@YAXXZ")
#pragma comment(linker, "/alternatename:?withdraw@Money@@QAEII_N@Z=?j_00041894@@YAXXZ")
#pragma comment(linker, "/alternatename:?addToProductionQueue@ProductionUpdate@@IAEXPAVProductionEntry@@@Z=?j_000450f7@@YAXXZ")
#pragma comment(linker, "/alternatename:?getSelectedPortraitImage@ThingTemplatePortraitShim@@QBEPBVImage@@XZ=?j_00047e38@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000F9670@BfmeVecVLH@@QAEPBVThingTemplate@@H@Z=?j_00002135@@YAXXZ")

class Image;
class Object;
class Player;


class ThingTemplate
{
public:
	Int calcCostToBuild(const Player *player, Int buildIndex) const;
	Bool isEquivalentTo(const ThingTemplate *other) const;
	UnsignedInt rva0029D790FlagsD8() const { return m_flagsD8; }

private:
	char m_head[0xd8];
	UnsignedInt m_flagsD8;
};

// The matched portrait selector (0x0013EEC0) is a view of ThingTemplate.
class ThingTemplatePortraitShim
{
public:
	const Image *getSelectedPortraitImage() const;
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern BfmeThingFactory *TheThingFactory;

class BuildAssistant
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
	virtual Int rva0029D790Slot40(Object *builder, const ThingTemplate *what, Int buildIndex);
};
extern BuildAssistant *TheBuildAssistant;

class Money
{
public:
	UnsignedInt withdraw(UnsignedInt amount, Bool playSound);
	UnsignedInt countMoney() const { return m_money; }

private:
	void *m_vtable;
	UnsignedInt m_money;
};

// The player's list at +0x684 receives three matched callees, each under the
// ledger's own view name: the build-index cost (0x000F9570 via ILT 0x000237D1),
// the portrait update (0x000FA830) and the template lookup (0x000F9670).
class BfmeBuildIndexSetter
{
public:
	Int set(Int buildIndex);
};

class Rva000FA830PortraitList
{
public:
	Bool updateEntry(Int buildIndex, Int productionID, const Image **image);
};

class BfmeVecVLH
{
public:
	const ThingTemplate *rva000F9670(Int buildIndex);
};

class Player
{
public:
	Money *getMoney() { return &m_money; }
	BfmeBuildIndexSetter *getBuildIndexSetter() { return reinterpret_cast<BfmeBuildIndexSetter *>(&m_list684); }
	Rva000FA830PortraitList *getRva000FA830PortraitList() { return reinterpret_cast<Rva000FA830PortraitList *>(&m_list684); }
	BfmeVecVLH *getBfmeVecVLH() { return reinterpret_cast<BfmeVecVLH *>(&m_list684); }

private:
	char m_head[0x48];
	Money m_money;
	char m_pad50[0x684 - 0x50];
	char m_list684[4];
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

struct QuantityModifier
{
	AsciiString m_templateName;
	Int m_quantity;
};

// STLport vector<QuantityModifier> layout: start, finish, end of storage.
class QuantityModifierVector
{
public:
	const QuantityModifier *begin() const { return m_start; }
	const QuantityModifier *end() const { return m_finish; }

private:
	QuantityModifier *m_start;
	QuantityModifier *m_finish;
	QuantityModifier *m_endOfStorage;
};

class ProductionUpdateModuleData
{
	char m_head[0x1c];
public:
	QuantityModifierVector m_quantityModifiers;
	Int m_maxQueueEntries;
};

extern "C" void *bfmeVftVG[];

// Slot 0 of table 0x010C0D90 is the scalar deleting destructor (0x0029C290).
class ProductionEntryDeleteView
{
public:
	virtual void scalarDelete(UnsignedInt flags);
};

class ProductionEntry
{
public:
	ProductionEntry()
	{
		m_vtable = bfmeVftVG;
		m_type = 0;
		m_objectToProduce = NULL;
		m_upgradeToResearch = NULL;
		m_productionID = 1;
		m_percentComplete = 0;
		m_value18 = 0;
		m_value1c = 0;
		m_productionQuantityTotal = 0;
		m_productionQuantityProduced = 0;
		m_cost = 0;
		m_value2c = 0;
		m_value30 = 0;
		m_flag34 = false;
		m_portrait = NULL;
		m_next = NULL;
		m_prev = NULL;
		m_value44 = 0;
	}
	void deleteInstance()
	{
		reinterpret_cast<ProductionEntryDeleteView *>(this)->scalarDelete(1);
	}

	void **m_vtable;
	Int m_type;
	const ThingTemplate *m_objectToProduce;
	const void *m_upgradeToResearch;
	UnsignedInt m_productionID;
	float m_percentComplete;
	float m_value18;
	Int m_value1c;
	Int m_productionQuantityTotal;
	Int m_productionQuantityProduced;
	Int m_cost;
	Int m_value2c;
	UnsignedInt m_value30;
	Bool m_flag34;
	const Image *m_portrait;
	ProductionEntry *m_next;
	ProductionEntry *m_prev;
	Int m_value44;
};

class ProductionUpdate
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual UnsignedInt requestUniqueUnitID();
	virtual Bool queueUpgrade(const void *upgrade, const ThingTemplate *thingTemplate);
	virtual void slot10();
	virtual Bool isUpgradeInQueue(const void *upgrade) const;
	virtual void slot18();
	virtual Bool queueCreateUnit(const ThingTemplate *unitType, Int buildIndex,
		UnsignedInt productionID, UnsignedInt value30, Bool batch);

protected:
	void addToProductionQueue(ProductionEntry *production);

public:
	Object *getObject()
	{
		return *reinterpret_cast<Object **>(reinterpret_cast<char *>(this) - 0x18);
	}
	const ProductionUpdateModuleData *getProductionUpdateModuleData()
	{
		return *reinterpret_cast<ProductionUpdateModuleData **>(reinterpret_cast<char *>(this) - 0x1c);
	}
	ProductionUpdate *getOwner()
	{
		return reinterpret_cast<ProductionUpdate *>(reinterpret_cast<char *>(this) - 0x20);
	}

	char m_pad04[0x10];
	UnsignedInt m_productionCount;
};

Bool ProductionUpdate::queueCreateUnit(const ThingTemplate *unitType, Int buildIndex,
	UnsignedInt productionID, UnsignedInt value30, Bool batch)
{
	const ProductionUpdateModuleData *data = getProductionUpdateModuleData();
	Bool fromIndex = buildIndex != -1;
	if (fromIndex)
		unitType = NULL;

	if (TheBuildAssistant->rva0029D790Slot40(getObject(), unitType, buildIndex) != 0)
		return FALSE;

	if (m_productionCount >= (UnsignedInt)getProductionUpdateModuleData()->m_maxQueueEntries)
		return FALSE;

	Int cost = 0;
	Player *player = getObject()->getControllingPlayer();
	Money *money = player->getMoney();
	if (fromIndex)
		cost = player->getBuildIndexSetter()->set(buildIndex);
	else if ((unitType->rva0029D790FlagsD8() & 0x10000000) == 0)
		cost = unitType->calcCostToBuild(player, -1);

	Int count = batch ? 5 : 1;
	Bool first = TRUE;
	while (count != 0)
	{
		if (m_productionCount >= (UnsignedInt)getProductionUpdateModuleData()->m_maxQueueEntries)
			return TRUE;

		money->withdraw(cost, TRUE);
		ProductionEntry *production = new ProductionEntry;

		if (first)
		{
			production->m_productionID = productionID;
			first = FALSE;
		}
		else
			production->m_productionID = requestUniqueUnitID();

		production->m_productionQuantityTotal = 1;
		production->m_productionQuantityProduced = 0;
		if (!fromIndex)
		{
			for (const QuantityModifier *it = data->m_quantityModifiers.begin();
				it != data->m_quantityModifiers.end(); ++it)
			{
				const ThingTemplate *productionTemplate = TheThingFactory->findTemplate(it->m_templateName);
				if (productionTemplate && productionTemplate->isEquivalentTo(unitType))
				{
					production->m_productionQuantityTotal = it->m_quantity;
					break;
				}
			}
			production->m_type = 1;
			production->m_objectToProduce = unitType;
			production->m_portrait = reinterpret_cast<const ThingTemplatePortraitShim *>(unitType)->getSelectedPortraitImage();
		}
		else
		{
			production->m_type = 3;
			if (!player->getRva000FA830PortraitList()->updateEntry(buildIndex, production->m_productionID, &production->m_portrait))
			{
				production->deleteInstance();
				return FALSE;
			}
			production->m_objectToProduce = player->getBfmeVecVLH()->rva000F9670(buildIndex);
		}

		production->m_value2c = -1;
		production->m_value30 = value30;
		production->m_cost = cost;
		getOwner()->addToProductionQueue(production);
		--count;
		if (money->countMoney() < (UnsignedInt)cost)
			return TRUE;
	}
	return TRUE;
}
