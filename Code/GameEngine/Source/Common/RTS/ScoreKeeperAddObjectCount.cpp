// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ScoreKeeper count increment: add `amount` to a running total at +0x90 and
// to the ThingTemplate* -> int map at +0x2d0. Same find-then-assign shape as
// Zero Hour's addObjectCaptured / addObjectBuilt inner update.

#include <map>

class ThingTemplate;

typedef _STL::map<const ThingTemplate *, int> ObjectCountMap;
typedef ObjectCountMap::iterator ObjectCountMapIt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ScoreKeeper.h
class ScoreKeeper
{
public:
	void addObjectCount(const ThingTemplate *tmpl, int amount);

private:
	char m_pad0[0x90];
	int m_total;					// +0x90
	char m_pad1[0x23C];				// 0x2d0 - 0x94
	ObjectCountMap m_objects;			// +0x2d0
};

void ScoreKeeper::addObjectCount(const ThingTemplate *tmpl, int amount)
{
	m_total += amount;
	int existingCount = 0;
	ObjectCountMapIt it = m_objects.find(tmpl);
	if (it != m_objects.end())
		existingCount = it->second;
	m_objects[tmpl] = existingCount + amount;
}
