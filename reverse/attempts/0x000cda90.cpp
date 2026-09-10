// ?d_000cda90@@YAXXZ
// partial score=0.9 date=2026-09-10
// ?compareCastles@@YAHPAVObject@@PAVCastleBehavior@@01@Z
// cl: /O2

class Player;
class Object;
class CastleBehavior;

class ThingTemplate
{
public:
	ThingTemplate *getFinalOverride() const;
	unsigned int calcCostToBuild(const Player *player, int buildIndex) const;

private:
	void *m_vtable;
	ThingTemplate *m_override;

	friend int compareCastles(Object *, class CastleBehavior *, Object *, class CastleBehavior *);
};

class Object
{
public:
	Player *getControllingPlayer() const;

private:
	void *m_vtable;
	ThingTemplate *m_template;

	friend int compareCastles(Object *, class CastleBehavior *, Object *, class CastleBehavior *);
};

class CastleBehavior
{
public:
	int countCompleteStructures();
	unsigned int structureCount() const { return m_structuresEnd - m_structuresBegin; }

private:
	unsigned char m_pad[0xb8];
	void **m_structuresBegin;
	void **m_structuresEnd;

	friend int compareCastles(Object *, CastleBehavior *, Object *, CastleBehavior *);
};

int compareCastles(Object *first, CastleBehavior *firstCastle,
	Object *second, CastleBehavior *secondCastle)
{
	if (firstCastle)
	{
		if (secondCastle)
		{
			int firstComplete = firstCastle->countCompleteStructures();
			int secondComplete = secondCastle->countCompleteStructures();
			if (firstComplete != secondComplete)
				return firstComplete - secondComplete;

			return firstCastle->structureCount() - secondCastle->structureCount();
		}
		return 1;
	}

	if (secondCastle)
		return -1;

	unsigned int firstCost = 0;
	ThingTemplate *firstBase = first->m_template;
	ThingTemplate *firstTemplate = firstBase && firstBase->m_override
		? firstBase->m_override->getFinalOverride() : 0;
	if (firstTemplate)
		firstCost = firstTemplate->calcCostToBuild(first->getControllingPlayer(), -1);

	unsigned int secondCost = 0;
	ThingTemplate *secondBase = second->m_template;
	ThingTemplate *secondTemplate = secondBase && secondBase->m_override
		? secondBase->m_override->getFinalOverride() : 0;
	if (secondTemplate)
		secondCost = secondTemplate->calcCostToBuild(second->getControllingPlayer(), -1);

	return firstCost - secondCost;
}
