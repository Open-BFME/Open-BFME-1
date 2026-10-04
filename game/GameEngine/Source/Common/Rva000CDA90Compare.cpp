// ?Rva000CDA90Compare@@YAHPAVObject@@PAVCastleBehavior@@01@Z
// Free-function comparator sorting Objects by their CastleBehavior module:
// complete-structure count, then total structure count, then (with no
// CastleBehavior at all) build cost via ThingTemplate::calcCostToBuild.
// cl: /O2

class Player;
class Object;
class CastleBehavior;

class BfmeSubBIA
{
public:
	int ask();

	void *m_vtable;
	BfmeSubBIA *m_bfmeNextOverride;
};

class ThingTemplate
{
public:
	int calcCostToBuild(const Player *player, int buildIndex) const;

private:
	void *m_vtable;
	ThingTemplate *m_nextOverride;

	friend int Rva000CDA90Compare(Object *, class CastleBehavior *, Object *, class CastleBehavior *);
};

class Object
{
public:
	Player *getControllingPlayer() const;

private:
	void *m_vtable;
	ThingTemplate *m_template;

	friend int Rva000CDA90Compare(Object *, class CastleBehavior *, Object *, class CastleBehavior *);
};

// The complete 231-byte retail caller passes each CastleBehavior pointer
// unchanged in ECX through ILT 0x00048761 to the 157-byte body at 0x0036F910.
// It takes no stack arguments and returns the compared value in EAX. Preserve
// the existing provider's exact local ABI view without claiming a type identity.
typedef int ObjectID;

class Rva0036F910Owner
{
public:
	int countCompleteStructures();
	int countCompleteStructuresSecondary();

private:
	char m_pad000[0xb8];
	ObjectID *m_begin;
	ObjectID *m_end;
	char m_pad0c0[0xdc - 0xc0];
	ObjectID *m_secondaryBegin;
	ObjectID *m_secondaryEnd;
};

class CastleBehavior
{
public:
	unsigned int structureCount() const { return m_structuresEnd - m_structuresBegin; }

private:
	unsigned char m_pad[0xb8];
	void **m_structuresBegin;
	void **m_structuresEnd;

	friend int Rva000CDA90Compare(Object *, CastleBehavior *, Object *, CastleBehavior *);
};

int Rva000CDA90Compare(Object *first, CastleBehavior *firstCastle,
	Object *second, CastleBehavior *secondCastle)
{
	if (firstCastle)
	{
		if (secondCastle)
		{
			int firstComplete = ((Rva0036F910Owner *)firstCastle)->countCompleteStructures();
			int secondComplete = ((Rva0036F910Owner *)secondCastle)->countCompleteStructures();
			if (firstComplete != secondComplete)
				return firstComplete - secondComplete;

			void **firstEnd = firstCastle->m_structuresEnd;
			void **firstBegin = firstCastle->m_structuresBegin;
			void **secondBegin = secondCastle->m_structuresBegin;
			void **secondEnd = secondCastle->m_structuresEnd;
			return (firstEnd - firstBegin) - (secondEnd - secondBegin);
		}
		return 1;
	}

	if (secondCastle)
		return -1;

	unsigned int firstCost;
	ThingTemplate *firstBase = first->m_template;
	if (firstBase)
	{
		ThingTemplate *firstTemplate = firstBase->m_nextOverride
			? (ThingTemplate *)((BfmeSubBIA *)firstBase->m_nextOverride)->ask()
			: firstBase;
		firstCost = firstTemplate
			? firstTemplate->calcCostToBuild(first->getControllingPlayer(), -1) : 0;
	}
	else
	{
		firstCost = 0;
	}

	unsigned int secondCost;
	ThingTemplate *secondBase = second->m_template;
	if (secondBase)
	{
		ThingTemplate *secondTemplate = secondBase->m_nextOverride
			? (ThingTemplate *)((BfmeSubBIA *)secondBase->m_nextOverride)->ask()
			: secondBase;
		secondCost = secondTemplate
			? secondTemplate->calcCostToBuild(second->getControllingPlayer(), -1) : 0;
	}
	else
	{
		secondCost = 0;
	}

	return firstCost - secondCost;
}
