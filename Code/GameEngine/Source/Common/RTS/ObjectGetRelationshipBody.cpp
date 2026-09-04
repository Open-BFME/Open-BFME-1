// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum KindOfType
{
	KINDOF_IMMOBILE = 2,
	KINDOF_UNRECONSTRUCTED_108 = 108,
	KINDOF_UNRECONSTRUCTED_132 = 132,
	KINDOF_UNRECONSTRUCTED_139 = 139
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad008[0xC8 - 8];
	UnsignedInt m_kindOf[5];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;

protected:
	void *m_vtable;
	ThingTemplate *m_template;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Relationship getRelationship(const Team *that) const;
};

class BfmeRelationEntry;

class BfmeRelationTest
{
public:
	Bool bfmeAllowsRelationship(Int test, const BfmeRelationEntry *entry) const;
};

class BfmeRelationEntry
{
public:
	void *m_vtable;
	BfmeRelationTest *m_test;
};

class BfmeRelationInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60();
	virtual const Object *bfmeGetRelationSource() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	BfmeRelationInterface *bfmeGetRelationInterface() const;

	const ThingTemplate *getFinalTemplate() const
	{
		const ThingTemplate *thingTemplate = m_template;
		if (thingTemplate && thingTemplate->m_nextOverride)
			thingTemplate = reinterpret_cast<const ThingTemplate *>(thingTemplate->m_nextOverride->getFinalOverride());
		return thingTemplate;
	}

	Team *getTeam() const { return m_team; }

	Bool getIsUndetectedDefector() const { return (m_privateStatus & UNDETECTED_DEFECTOR) != 0; }

	// Upstream keeps these private to Object; the shim below is the only reader here.
	enum ObjectPrivateStatusBits
	{
		EFFECTIVELY_DEAD = (1 << 0),
		UNDETECTED_DEFECTOR = (1 << 1)
	};

	unsigned char m_pad008[0x130 - 8];
	UnsignedInt m_status130;
	unsigned char m_pad134[0x23C - 0x134];
	Team *m_team;
	unsigned char m_pad240[0x26C - 0x240];
	BfmeRelationEntry *m_relationEntries[4];
	Int m_relationIndex;
	UnsignedInt m_value280;
	void *m_relationData;
	unsigned char m_pad288[0x344 - 0x288];
	unsigned char m_privateStatus;
};

class ObjectGetRelationshipShim : public Object
{
public:
	Relationship get(const Object *that) const;
};

Relationship ObjectGetRelationshipShim::get(const Object *that) const
{
	if (that)
	{
		const ThingTemplate *targetTemplate = that->getFinalTemplate();
		if ((targetTemplate->m_kindOf[1] & 0x00400000) != 0
			&& that->isKindOf(KINDOF_IMMOBILE))
		{
			if (isKindOf(KINDOF_UNRECONSTRUCTED_139)
				&& (m_status130 & 0x00001000) != 0)
				return ENEMIES;

			const Object *relationSource;
			if (isKindOf(KINDOF_UNRECONSTRUCTED_132))
			{
				relationSource = this;
			}
			else
			{
				if (!isKindOf(KINDOF_UNRECONSTRUCTED_108))
					goto ordinary_relationship;

				BfmeRelationInterface *relationInterface = bfmeGetRelationInterface();
				if (!relationInterface)
					goto ordinary_relationship;

				const Object *containedSource = bfmeGetRelationInterface()->bfmeGetRelationSource();
				if (!containedSource || !containedSource->isKindOf(KINDOF_UNRECONSTRUCTED_132))
					goto ordinary_relationship;
				relationSource = containedSource;
			}

			if (relationSource
				&& relationSource->m_relationData
				&& relationSource->m_relationEntries[relationSource->m_relationIndex])
			{
				BfmeRelationEntry *entry = relationSource->m_relationEntries[relationSource->m_relationIndex];
				if (entry->m_test->bfmeAllowsRelationship(6, entry))
					return ENEMIES;
			}
		}
	}

ordinary_relationship:
	const Team *myTeam = getTeam();
	if (myTeam && that)
	{
		if (getIsUndetectedDefector())
			return NEUTRAL; // so my AI does not give away my position by auto acquire
		else if (that->getIsUndetectedDefector())
			return ALLIES; // so I treat undetected defectors like they were my very own
		else
			return myTeam->getRelationship(that->getTeam());
	}

	return NEUTRAL;
}
