// ?findFactory@AIPlayer@@IAEPAVObject@@PBVThingTemplate@@_NPAH@Z
// partial score=0.93 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// readable body of ?findFactory@AIPlayer@@IAEPAVObject@@PBVThingTemplate@@_NPAH@Z
//
// BFME's findFactory is not the two-argument Zero Hour build-list query.  Its
// callers pass a build-index out pointer, and the retail body walks the live
// object list, asking each owned factory whether it can make the requested
// template.  The declarations below deliberately model only the fields and
// virtual slots reached by this body.

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

#define TheGameLogic (*(GameLogic **)0x012F0898)

class ThingTemplate
{
public:
	void *m_vtable;
	ThingTemplate *m_nextOverride;
	unsigned char m_unmodelled008[0xcc - 8];
	unsigned int m_kindOf;
	unsigned char m_unmodelled0d0[0x4cb - 0xd0];
	unsigned char m_bfmeProductionFlag;

	ThingTemplate *getFinalOverride();
	Bool isEquivalentTo(const ThingTemplate *other) const;
};

class Object
{
public:
	void *m_vtable;
	ThingTemplate *m_template;
	unsigned char m_unmodelled008[0x88 - 8];
	Object *m_nextObject;
	unsigned char m_unmodelled08c[0x90 - 0x8c];
	unsigned int m_status;
	unsigned char m_unmodelled094[0x1a4 - 0x94];
	unsigned int m_disabledMask;
	unsigned char m_unmodelled1a8[0x344 - 0x1a8];
	unsigned char m_bfmeFlags344;

	Player *getControllingPlayer() const;
	ProductionUpdateInterface *getProductionUpdateInterface();
	Object *getNextObject() const { return m_nextObject; }
};

class Player
{
public:
	unsigned char canBuildFromProduction() const
	{
		return *(const unsigned char *)((const char *)this + 0x681);
	}
};

class BfmeBuildIndexSelector
{
public:
	Int findBuildIndex(const ThingTemplate *thing, Int requestedIndex);
};

static Int bfmeFindBuildIndex(Player *player, const ThingTemplate *thing)
{
	return ((BfmeBuildIndexSelector *)((char *)player + 0x684))->
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

#define TheBuildAssistant (*(BuildAssistant **)0x012ED83C)

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
	virtual Int getProductionCount() const = 0;
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual ProductionEntry *firstProduction() const = 0;
};

class AIPlayer
{
protected:
	Object *findFactory(const ThingTemplate *thing, Bool busyOK,
		Int *buildIndex);

private:
	char m_prefix[0x0c];
	Player *m_player;
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
		if ((factoryTemplate->m_kindOf & 0x40000000) == 0)
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
		if ((factory->m_bfmeFlags344 & 1) != 0)
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
			goto foundFactory;
		}

	noBuildIndex:
		if (!buildAssistant->isPossibleToMakeUnit(factory, requestedThing, -1))
			goto nextFactory;
		if (production->getProductionCount() <= 0)
			goto foundFactory;
		if (m_player->canBuildFromProduction() == 0)
			goto nextFactory;

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
					requestedThing->isEquivalentTo(entryThing))
					goto considerBusy;
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
