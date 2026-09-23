// ?d_0029d790@@YAXXZ
// partial score=0.109 date=2026-09-23
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

class Image;
class Player;
class Object;
class ProductionEntry;

class Money
{
public:
	UnsignedInt withdraw(UnsignedInt amount, Bool playSound);
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class ThingTemplate
{
public:
	virtual void rva0029D790Slot00();
	virtual void rva0029D790Slot01();
	virtual UnsignedInt rva0029D790Slot02() const;
	Int calcCostToBuild(const Player *player, Int buildIndex) const;
	Bool isEquivalentTo(const ThingTemplate *other) const;
};

class ThingTemplatePortraitShim
{
public:
	const Image *getSelectedPortraitImage() const;

private:
	char m_bfmeBeforePortraitName[0x34];
	mutable AsciiString m_bfmePortraitName;
	char m_bfmeBeforeCachedPortrait[0x394 - 0x38];
	mutable const Image *m_bfmeCachedPortrait;
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

struct BfmeElemVLH
{
	AsciiString m_name;
	UnsignedByte m_opaque04[0x5c];
};

class BfmeVecVLH
{
public:
	BfmeElemVLH *bfmeAtVLH(Int index);
	const ThingTemplate *rva000F9670(Int index);

private:
	Int m_opaque00;
	BfmeElemVLH *m_begin;
	BfmeElemVLH *m_end;
};

class BfmeBuildIndexSetter
{
public:
	Int set(Int value);

private:
	UnsignedByte m_prefix[0x42c];
	Int m_value;
};

class Rva000FA830PortraitList
{
public:
	Bool updateEntry(Int index, Int key, const Image **image);

private:
	void *m_vtable;
	void *m_begin;
	void *m_end;
	void *m_unused;
	Player *m_player;
};

struct ProductionUpdateModuleDataView
{
	UnsignedByte m_prefix[0x1c];
	const UnsignedByte *m_quantityBegin;
	const UnsignedByte *m_quantityEnd;
	UnsignedByte m_padding24[4];
	Int m_maxQueueEntries;
};

struct ProductionEntryLayout
{
	void *m_vptr;
	Int m_type;
	const ThingTemplate *m_objectToProduce;
	void *m_unknown0c;
	UnsignedInt m_productionID;
	float m_progress14;
	float m_unknown18;
	Int m_unknown1c;
	Int m_productionQuantity;
	Int m_quantityProduced;
	Int m_cost;
	Int m_unknown2c;
	UnsignedInt m_unknown30;
	Bool m_unknown34;
	UnsignedByte m_padding35[3];
	const Image *m_portrait;
	ProductionEntryLayout *m_next;
	ProductionEntryLayout *m_prev;
	Int m_unknown44;
};

class ProductionEntrySlot00View
{
public:
	virtual void *rva0029D790Slot00(UnsignedInt flags);
};

class Rva0029D790BuildAssistantView
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
	virtual Int rva0029D790Slot16(Object *object, UnsignedInt value, Int index);
};

class ProductionUpdate
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual Bool queueUpgrade(const void *upgrade, const ThingTemplate *thingTemplate);
	virtual void slot10();
	virtual Bool isUpgradeInQueue(const void *upgrade) const;

	Bool rva0029D790(const ThingTemplate *thingTemplate, Int index,
		UnsignedInt productionID, UnsignedInt value, Bool repeat);

protected:
	void addToProductionQueue(ProductionEntry *production);
};

#define TheBuildAssistant (*(Rva0029D790BuildAssistantView **)0x012ED83C)
#define TheThingFactory (*(BfmeThingFactory **)0x012EF1D8)

extern void j_00020824();
extern void j_0000da8a();
extern void j_000237d1();
extern void j_00028560();
extern void j_0003a3f0();
extern void j_0003e80b();
extern void j_00041894();
extern void j_000450f7();
extern void j_00047e38();
extern void j_00002135();

#pragma comment(linker, "/alternatename:?getControllingPlayer@Object@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?calcCostToBuild@ThingTemplate@@QBEHPBVPlayer@@H@Z=?j_0000da8a@@YAXXZ")
#pragma comment(linker, "/alternatename:?set@BfmeBuildIndexSetter@@QAEHH@Z=?j_000237d1@@YAXXZ")
#pragma comment(linker, "/alternatename:?findTemplate@BfmeThingFactory@@QAEPBVThingTemplate@@ABVAsciiString@@@Z=?j_00028560@@YAXXZ")
#pragma comment(linker, "/alternatename:?updateEntry@Rva000FA830PortraitList@@QAE_NHHPAPBVImage@@@Z=?j_0003a3f0@@YAXXZ")
#pragma comment(linker, "/alternatename:?isEquivalentTo@ThingTemplate@@QBE_NPBVThingTemplate@@@Z=?j_0003e80b@@YAXXZ")
#pragma comment(linker, "/alternatename:?withdraw@Money@@QAEII_N@Z=?j_00041894@@YAXXZ")
#pragma comment(linker, "/alternatename:?addToProductionQueue@ProductionUpdate@@IAEXPAVProductionEntry@@@Z=?j_000450f7@@YAXXZ")
#pragma comment(linker, "/alternatename:?getSelectedPortraitImage@ThingTemplatePortraitShim@@QBEPBVImage@@XZ=?j_00047e38@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000F9670@BfmeVecVLH@@QAEPBVThingTemplate@@H@Z=?j_00002135@@YAXXZ")

extern void *__cdecl operator new(UnsignedInt size);

Bool ProductionUpdate::rva0029D790(const ThingTemplate *thingTemplate,
	Int index, UnsignedInt productionID, UnsignedInt value, Bool repeat)
{
	ProductionUpdateModuleDataView * volatile moduleData =
		*(ProductionUpdateModuleDataView **)((char *)this - 0x1c);
	Object *object = *(Object **)((char *)this - 0x18);
	if (index != -1)
		value = 0;
	if (TheBuildAssistant->rva0029D790Slot16(object, value, index) == 0)
		return false;
	if (*(Int *)((char *)this + 0x14) >= moduleData->m_maxQueueEntries)
		return false;

	Player *player = object->getControllingPlayer();
	Int cost = 0;
	if (index != -1)
		cost = ((BfmeBuildIndexSetter *)((char *)player + 0x684))->set((Int)productionID);
	else if ((*(const UnsignedInt *)((const char *)thingTemplate + 0xd8) & 0x10000000) == 0)
		cost = thingTemplate->calcCostToBuild(player, -1);

	Int remaining = 1 + (repeat ? 4 : 0);
	repeat = true;
	do
	{
		if (*(Int *)((char *)this + 0x14) >= moduleData->m_maxQueueEntries)
			return true;

		((Money *)((char *)player + 0x48))->withdraw((UnsignedInt)cost, true);
		ProductionEntryLayout *entry = (ProductionEntryLayout *)operator new(0x48);
		if (entry != 0)
		{
			entry->m_vptr = (void *)0x010C0D90;
			entry->m_type = 0;
			entry->m_objectToProduce = 0;
			entry->m_unknown0c = 0;
			entry->m_productionID = 1;
			entry->m_progress14 = 0;
			entry->m_unknown18 = 0;
			entry->m_unknown1c = 0;
			entry->m_productionQuantity = 0;
			entry->m_quantityProduced = 0;
			entry->m_cost = 0;
			entry->m_unknown2c = 0;
			entry->m_unknown30 = 0;
			entry->m_unknown34 = false;
			entry->m_portrait = 0;
			entry->m_next = 0;
			entry->m_prev = 0;
			entry->m_unknown44 = 0;
		}

		if (repeat)
		{
			entry->m_productionID = productionID;
			repeat = false;
		}
		else
			entry->m_productionID = thingTemplate->rva0029D790Slot02();

		entry->m_productionQuantity = 1;
		entry->m_quantityProduced = 0;
		if (index == -1)
		{
			const UnsignedByte *modifier = moduleData->m_quantityBegin;
			const UnsignedByte *end = moduleData->m_quantityEnd;
			if (modifier != end)
			{
				do
				{
					const AsciiString &name = *(const AsciiString *)modifier;
					const ThingTemplate *candidate = TheThingFactory->findTemplate(name);
					if (candidate != 0 && candidate->isEquivalentTo(thingTemplate))
					{
						entry->m_productionQuantity = *(const Int *)(modifier + 4);
						break;
					}
					modifier += 8;
				}
				while (modifier != end);
			}
			entry->m_type = 1;
			entry->m_objectToProduce = thingTemplate;
			entry->m_portrait = ((const ThingTemplatePortraitShim *)thingTemplate)->getSelectedPortraitImage();
		}
		else
		{
			entry->m_type = 3;
			if (!((Rva000FA830PortraitList *)((char *)player + 0x684))->updateEntry(
				index, (Int)entry->m_productionID, &entry->m_portrait))
			{
				((ProductionEntrySlot00View *)entry)->rva0029D790Slot00(1);
				return false;
			}
			entry->m_objectToProduce = ((BfmeVecVLH *)((char *)player + 0x684))->rva000F9670(index);
		}

		entry->m_unknown2c = -1;
		entry->m_unknown30 = value;
		entry->m_cost = cost;
		((ProductionUpdate *)((char *)this - 0x20))->addToProductionQueue((ProductionEntry *)entry);
		if (*(UnsignedInt *)((char *)player + 0x4c) < (UnsignedInt)cost)
			return true;
		--remaining;
	}
	while (remaining != 0);
	return true;
}
