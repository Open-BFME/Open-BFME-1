// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// BFME ScoreKeeper::addObjectBuilt(Object *, Int) at 0x000EA5A0.
// The Object caller passes a count so the totals and template map use that
// count instead of the Zero Hour body's fixed increment.

#include <map>

typedef bool Bool;

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

class ThingTemplate;
class BfmeRvaA760Object;
class GameLogic;
class Overridable;

template <int Bits>
class BitFlags
{
public:
	bool testSetAndClear(const BitFlags<Bits> &mustBeSet, const BitFlags<Bits> &mustBeClear) const;
};

typedef BitFlags<116> KindOfMaskType;

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
	bool isKindOfMulti(const KindOfMaskType &mustBeSet, const KindOfMaskType &mustBeClear) const
	{
		return m_kindOf.testSetAndClear(mustBeSet, mustBeClear);
	}

private:
	unsigned char m_pad[0xC0];
	KindOfMaskType m_kindOf;
};

class Object
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
	unsigned int getStatusBits(void) const { return m_status; }

private:
	void *m_vptr;
	const ThingTemplate *m_template;
	unsigned char m_pad[0x90];
	unsigned int m_status;
};

class GameLogic
{
public:
	bool isScoringEnabled(void) const { return m_isScoringEnabled != 0; }

private:
	unsigned char m_pad[0x90];
	unsigned char m_isScoringEnabled;
};

class BfmeRvaA760ProbeInterface
{
public:
	bool accepts(BfmeRvaA760Object *obj, int arg);
};

class GlobalData
{
public:
	unsigned char m_pad[0x121C];
	BfmeRvaA760ProbeInterface m_unitScoreFilter;
};

extern GameLogic *TheBfmeGameLogic;
extern GlobalData *TheWritableGlobalData;

typedef _STL::map<const ThingTemplate *, int> ObjectCountMap;
typedef ObjectCountMap::iterator ObjectCountMapIt;

class ScoreKeeper
{
public:
	void addObjectBuilt(Object *o, int amount);

private:
	void *m_vtable;
	unsigned char m_pad0[0x88];
	int m_totalUnitsBuilt;
	unsigned char m_pad1[0x84];
	int m_totalBuildingsBuilt;
	unsigned char m_pad2[0x2C];
	ObjectCountMap m_objectsBuilt;
};

void ScoreKeeper::addObjectBuilt(Object *o, int amount)
{
	if (TheBfmeGameLogic->isScoringEnabled() == false)
		return;

	if (o->getStatusBits() & 0x800)
		return;

	Bool addToCount = false;
	if (o->getTemplate()->isKindOfMulti(scoringBuildingMask, KINDOFMASK_NONE))
	{
		m_totalBuildingsBuilt += amount;
		addToCount = true;
	}
	else if (o->getTemplate()->isKindOfMulti(scoringBuildingCreateMask, KINDOFMASK_NONE))
	{
		m_totalBuildingsBuilt += amount;
		addToCount = true;
	}
	else if (TheWritableGlobalData->m_unitScoreFilter.accepts((BfmeRvaA760Object *)o, 0))
	{
		m_totalUnitsBuilt += amount;
		addToCount = true;
	}
	if (!addToCount)
		return;

	int existingCount = 0;
	ObjectCountMapIt it = m_objectsBuilt.find(o->getTemplate());
	if (it != m_objectsBuilt.end())
		existingCount = it->second;
	int newCount = MAX(0, existingCount + amount);
	m_objectsBuilt[o->getTemplate()] = newCount;
}
