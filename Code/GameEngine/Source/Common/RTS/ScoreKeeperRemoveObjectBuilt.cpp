// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ScoreKeeper::removeObjectBuilt at 0x000EA730.
// BFME uses the scorekeeper built-object map at +0x144; +0x2d0 is the lost map.

#include <map>

class GameLogic;
class Overridable;

template <int Bits>
class BitFlags
{
public:
	bool testSetAndClear(const BitFlags<Bits> &mustBeSet, const BitFlags<Bits> &mustBeClear) const;
	unsigned int m_bits[4];
};

typedef BitFlags<116> KindOfMaskType;

enum KindOfType
{
	KINDOF_STRUCTURE = 7,
	KINDOF_INFANTRY = 8,
	KINDOF_VEHICLE = 9,
	KINDOF_SCORE = 39,
	KINDOF_SCORE_CREATE = 40
};

extern const KindOfMaskType KINDOFMASK_NONE;
extern KindOfMaskType scoringBuildingMask;
extern KindOfMaskType scoringBuildingCreateMask;

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride(void) const;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	bool isKindOf(KindOfType kind) const;
	bool hasKind(KindOfType kind) const
	{
		return (m_kindOf.m_bits[(unsigned int)kind >> 5] & (1 << ((unsigned int)kind & 31))) != 0;
	}

	bool isKindOfMulti(const KindOfMaskType &mustBeSet, const KindOfMaskType &mustBeClear) const
	{
		return m_kindOf.testSetAndClear(mustBeSet, mustBeClear);
	}

private:
	unsigned char m_pad[0xC0];
	KindOfMaskType m_kindOf;
};

class Thing
{
public:
	const ThingTemplate *getTemplate(void) const
	{
		const ThingTemplate *tmpl = m_template;
		if (tmpl == 0)
			return 0;
		if (tmpl->m_nextOverride)
			tmpl = (const ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
		return tmpl;
	}
	bool isKindOf(KindOfType kind) const { return getTemplate()->isKindOf(kind); }
	unsigned int getStatusBits(void) const { return m_status; }

private:
	void *m_vptr;
	const ThingTemplate *m_template;
	unsigned char m_pad[0x90];
	unsigned int m_status;
};

class Object : public Thing
{
};

class GameLogic
{
public:
	bool isScoringEnabled(void) const { return m_isScoringEnabled != 0; }

private:
	unsigned char m_pad[0x90];
	unsigned char m_isScoringEnabled;
};

extern GameLogic *TheBfmeGameLogic;

typedef _STL::map<const ThingTemplate *, int> ObjectCountMap;
typedef ObjectCountMap::iterator ObjectCountMapIt;

class ScoreKeeper
{
public:
	void removeObjectBuilt(const Object *o);

private:
	unsigned char m_pad0[0x8c];
	int m_totalUnitsBuilt;
	unsigned char m_pad1[0x84];
	int m_totalBuildingsBuilt;
	unsigned char m_pad2[0x2c];
	ObjectCountMap m_objectsBuilt;
};

void ScoreKeeper::removeObjectBuilt(const Object *o)
{
	if (TheBfmeGameLogic->isScoringEnabled() == false)
		return;

	if (o->getStatusBits() & 0x800)
		return;

	if (o->getTemplate()->isKindOfMulti(scoringBuildingMask, KINDOFMASK_NONE))
	{
		--m_totalBuildingsBuilt;
	}
	else if (o->getTemplate()->isKindOfMulti(scoringBuildingCreateMask, KINDOFMASK_NONE))
	{
		--m_totalBuildingsBuilt;
	}
	else if (o->getTemplate()->hasKind(KINDOF_INFANTRY) || o->getTemplate()->isKindOf(KINDOF_VEHICLE))
	{
		if (o->getTemplate()->isKindOf(KINDOF_SCORE) || o->getTemplate()->isKindOf(KINDOF_SCORE_CREATE))
			--m_totalUnitsBuilt;
		else
			return;
	}
	else
		return;

	int existingCount = 0;
	ObjectCountMapIt it = m_objectsBuilt.find(o->getTemplate());
	if (it != m_objectsBuilt.end())
		existingCount = it->second;
	m_objectsBuilt[o->getTemplate()] = existingCount - 1;
}
