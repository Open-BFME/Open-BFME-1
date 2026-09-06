// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ScoreKeeper::reset at retail RVA 0x000EA010.

#include <bitset>
#include <map>

typedef int Int;

template <int Bits>
class BitFlags
{
public:
	void set(Int bit)
	{
		m_bits._Unchecked_set((size_t)bit);
	}

private:
	_STL::bitset<Bits> m_bits;
};

typedef BitFlags<116> KindOfMaskType;

enum KindOfType
{
	KINDOF_STRUCTURE = 7,
	KINDOF_SCORE = 39,
	KINDOF_SCORE_CREATE = 40,
	KINDOF_SCORE_DESTROY = 41
};

static KindOfMaskType scoringBuildingMask;
static KindOfMaskType scoringBuildingDestroyMask;
static KindOfMaskType scoringBuildingCreateMask;

class ThingTemplate;
typedef _STL::map<const ThingTemplate *, Int> ObjectCountMap;

class ScoreKeeper
{
public:
	void reset(Int playerIdx);

private:
	void *m_vtable;
	Int m_totalMoneyEarned;
	Int m_totalMoneySpent;
	Int m_totalUnitsDestroyed[32];
	Int m_totalUnitsBuilt;
	Int m_totalUnitsLost;
	Int m_totalBuildingsDestroyed[32];
	Int m_totalBuildingsBuilt;
	Int m_totalBuildingsLost;
	Int m_heroesVetted;
	Int m_unitsVetted;
	Int m_powerPoints;
	Int m_pad128;
	Int m_regionCommandPoints;
	Int m_regionResources;
	Int m_regionPowerPoints;
	Int m_currentScore;
	unsigned int m_frameOverride;
	Int m_myPlayerIdx;
	ObjectCountMap m_objectsBuilt;
	ObjectCountMap m_objectsDestroyed[32];
	ObjectCountMap m_objectsLost;
	ObjectCountMap m_objectsCaptured;
};

void ScoreKeeper::reset(Int playerIdx)
{
	scoringBuildingMask.set(KINDOF_STRUCTURE);
	scoringBuildingMask.set(KINDOF_SCORE);
	scoringBuildingCreateMask.set(KINDOF_STRUCTURE);
	scoringBuildingCreateMask.set(KINDOF_SCORE_CREATE);
	scoringBuildingDestroyMask.set(KINDOF_STRUCTURE);
	scoringBuildingDestroyMask.set(KINDOF_SCORE_DESTROY);

	m_totalMoneyEarned = m_totalMoneySpent = 0;
	m_totalUnitsLost = m_totalUnitsBuilt = 0;
	m_totalBuildingsLost = m_totalBuildingsBuilt = 0;
	m_heroesVetted = 0;
	m_unitsVetted = 0;
	m_powerPoints = 0;
	m_frameOverride = 0;
	m_pad128 = 0;
	m_regionCommandPoints = 0;
	m_regionResources = 0;
	m_regionPowerPoints = 0;
	m_currentScore = 0;
	m_objectsBuilt.clear();
	m_objectsCaptured.clear();
	m_objectsLost.clear();
	for (Int i = 0; i < 32; ++i)
	{
		m_objectsDestroyed[i].clear();
		m_totalBuildingsDestroyed[i] = m_totalUnitsDestroyed[i] = 0;
	}
	m_myPlayerIdx = playerIdx;
}
