// ?findFactory@AIPlayer@@IAEPAVObject@@PBVThingTemplate@@_NPAH@Z
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ?findFactory@AIPlayer@@IAEPAVObject@@PBVThingTemplate@@_NPAH@Z: Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp
//
// BFME's findFactory is not the two-argument Zero Hour build-list query.  Its
// callers pass a build-index out pointer, and the retail body walks the live
// object list, asking each owned factory whether it can make the requested
// template.  The declarations below deliberately model only the fields and
// virtual slots reached by this body.

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

#define NULL 0

class ThingTemplate;
class Object;
class Player;
class ProductionUpdateInterface;

class GameLogic
{
public:
	Object *getFirstObject();
};

extern GameLogic *TheGameLogic;

class ThingTemplate
{
public:
	void *m_vtable;
	ThingTemplate *m_nextOverride;
	unsigned char m_unmodelled008[0x20 - 8];
	AsciiString m_nameString;							// +0x20
	unsigned char m_unmodelled024[0xcc - 0x24];
	// Retail tests bit 30 of this word; the current naming witness conflicts.
	unsigned int m_shadowOffsetY;
	unsigned char m_unmodelled0d0[0x4cb - 0xd0];
	unsigned char m_bfmeProductionFlag;

	const AsciiString &getName() const { return m_nameString; }
	ThingTemplate *getFinalOverride();
	Bool isEquivalentTo(const ThingTemplate *other) const;
};

class Object
{
public:
	void *m_vtable;
	ThingTemplate *m_template;
	unsigned char m_unmodelled008[0x74 - 8];
	Int m_id;											// +0x74
	unsigned char m_unmodelled078[0x88 - 0x78];
	Object *m_nextObject;
	unsigned char m_unmodelled08c[0x90 - 0x8c];
	unsigned int m_status;
	unsigned char m_unmodelled094[0x1a4 - 0x94];
	unsigned int m_disabledMask;
	unsigned char m_unmodelled1a8[0x344 - 0x1a8];
	unsigned char m_privateStatus;

	Player *getControllingPlayer() const;
	ProductionUpdateInterface *getProductionUpdateInterface();
	Object *getNextObject() const { return m_nextObject; }
	Int getID() const { return m_id; }
};

class Player
{
public:
	unsigned char canBuildFromProduction() const
	{
		return *(const unsigned char *)((const char *)this + 0x681);
	}
};

// Existing ILT 0000A7A9 routes to the measured selector body at 000FA8B0.
// Its owner name is unresolved; preserve an RVA-qualified call-site view.
extern void j_0000a7a9();
class Rva000FA8B0Selector
{
public:
	__forceinline Int findBuildIndex(const ThingTemplate *thing, Int requestedIndex)
	{
		typedef Int (Rva000FA8B0Selector::*Call)(const ThingTemplate *, Int);
		union { void (*raw)(); Call member; } target;
		target.raw = j_0000a7a9;
		return (this->*target.member)(thing, requestedIndex);
	}
};

static Int bfmeFindBuildIndex(Player *player, const ThingTemplate *thing)
{
	return ((Rva000FA8B0Selector *)((char *)player + 0x684))->
		findBuildIndex(thing, -1);
}

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
	virtual void slot16();
	virtual Bool isPossibleToMakeUnit(Object *factory,
		const ThingTemplate *thing, Int buildIndex) = 0;
};

extern BuildAssistant *TheBuildAssistant;

class ProductionEntry
{
public:
	void *m_vtable;
	Int m_type;
	ThingTemplate *m_thing;
};

class ProductionUpdateInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual Int requestUniqueUnitID() = 0;					// +0x08
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual Bool queueCreateUnit(const ThingTemplate *unitType, Int buildIndex,
		Int productionID, Int bfmeC, Int bfmeD) = 0;		// +0x1C
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual Int getProductionCount() const = 0;
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual ProductionEntry *firstProduction() const = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class WorkOrder
{
public:
	char m_unmodelled000[0x4];
	const ThingTemplate *m_thing;						// +0x04
	Int m_factoryID;									// +0x08
};

struct GlobalData
{
	char m_unmodelled000[0xa88];
	Int m_debugAI;										// +0xA88
};

extern GlobalData *TheGlobalData;

class ScriptEngine
{
public:
	void AppendDebugMessage(const AsciiString &strToAdd, Bool mustAdd);
};

extern ScriptEngine *TheScriptEngine;

class AIPlayer
{
protected:
	virtual Bool startTraining(WorkOrder *order, Bool busyOK, AsciiString teamName);
	Object *findFactory(const ThingTemplate *thing, Bool busyOK,
		Int *buildIndex);

private:
	char m_prefix[0x0c - 0x04];							// after the vtable pointer
	Player *m_player;									// +0x0C
};

Object *AIPlayer::findFactory(const ThingTemplate *thing, Bool busyOK,
	Int *buildIndex)
{
	const ThingTemplate *requestedThing = thing;
	Object *busyFactory = NULL;
	if (requestedThing == NULL)
		return NULL;
	if (buildIndex != NULL)
		*buildIndex = -1;

	Object *factory = TheGameLogic->getFirstObject();
	while (factory != NULL)
	{
		if (factory->getControllingPlayer() != m_player)
			goto nextFactory;

		ThingTemplate *factoryTemplate = factory->m_template;
		if (factoryTemplate != NULL && factoryTemplate->m_nextOverride != NULL)
			factoryTemplate = factoryTemplate->m_nextOverride->getFinalOverride();
		if ((factoryTemplate->m_shadowOffsetY & 0x40000000) == 0)
			goto nextFactory;
		if ((factory->m_status & 4) != 0 ||
			(factory->m_status & 0x80000) != 0)
			goto nextFactory;
		if (factory->m_disabledMask != 0)
			goto nextFactory;

		ProductionUpdateInterface *production =
			factory->getProductionUpdateInterface();
		if (production == NULL)
			goto nextFactory;
		if ((factory->m_privateStatus & 1) != 0)
			goto nextFactory;

		Int availableBuildIndex = bfmeFindBuildIndex(
			factory->getControllingPlayer(), requestedThing);
		BuildAssistant *buildAssistant = TheBuildAssistant;
		if (availableBuildIndex != -1)
		{
			if (!buildAssistant->isPossibleToMakeUnit(factory, NULL,
				availableBuildIndex))
				goto nextFactory;
			if (buildIndex != NULL)
				*buildIndex = availableBuildIndex;
			goto afterBuildIndex;
		}

		if (!buildAssistant->isPossibleToMakeUnit(factory, requestedThing, -1))
			goto nextFactory;

	afterBuildIndex:
		if (production->getProductionCount() <= 0)
			goto foundFactory;
		if (m_player->canBuildFromProduction() == 0)
			goto considerBusy;

		ProductionEntry *entry = production->firstProduction();
		if (entry != NULL)
		{
			Int type = entry->m_type - 1;
			if (type != 0)
				type -= 2;
			if (type == 0)
			{
				ThingTemplate *entryThing = entry->m_thing;
				if (entryThing != NULL && entryThing->m_bfmeProductionFlag != 0 &&
					!requestedThing->isEquivalentTo(entryThing))
					goto foundFactory;
			}
		}

	considerBusy:
		if (busyOK)
			busyFactory = factory;

	nextFactory:
		factory = factory->getNextObject();
	}

	goto busyResult;

busyResult:
	return busyOK ? busyFactory : NULL;

foundFactory:
	return factory;
}

// ?startTraining@AIPlayer@@MAE_NPAVWorkOrder@@_NVAsciiString@@@Z
// Slot 24 (+0x60) of AIPlayer's table 0x010968B0 (0x00166EF0). Zero Hour's
// body; BFME's findFactory reports the build index that queueCreateUnit then
// takes, with (-1, 0) after the unit ID. Compiled beside findFactory, as in
// retail's AIPlayer.cpp: with the callee's body visible MSVC reuses the
// order slot for the index, as retail does. AISkirmishPlayer::startTraining
// (AISkirmishPlayer_startTraining.cpp) is the same source without it.
Bool AIPlayer::startTraining( WorkOrder *order, Bool busyOK, AsciiString teamName)
{
	Int buildIndex;										// written by findFactory
	Object *factory = findFactory(order->m_thing, busyOK, &buildIndex);
	if( factory )
	{
		ProductionUpdateInterface *pu = factory->getProductionUpdateInterface();
		if (pu && pu->queueCreateUnit( order->m_thing, buildIndex, pu->requestUniqueUnitID(), -1, 0 )) {
			order->m_factoryID = factory->getID(); 
			if (TheGlobalData->m_debugAI) {
				AsciiString teamStr = "Queuing ";
				((StringBase<char> *)&teamStr)->concat(*(const StringBase<char> *)&order->m_thing->getName());
				teamStr.concat(" for ");
				teamStr.concat(teamName);
				TheScriptEngine->AppendDebugMessage(teamStr, false);
			}
			return true;
		}
	}  // end if

	return false;

}
