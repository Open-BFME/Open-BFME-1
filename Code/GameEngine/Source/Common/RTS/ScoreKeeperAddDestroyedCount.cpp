// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Per-player ScoreKeeper destroyed-object increment. Player index at Player+0x24,
// totals array at +0x0c, map array of 32 STLport maps at +0x150 (12 bytes each).

#include <map>

class ThingTemplate;

typedef _STL::map<const ThingTemplate *, int> ObjectCountMap;
typedef ObjectCountMap::iterator ObjectCountMapIt;

class Player
{
public:
	int getPlayerIndex() const { return m_playerIndex; }

private:
	char m_pad[0x24];
	int m_playerIndex;					// +0x24
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ScoreKeeper.h
class ScoreKeeper
{
public:
	void addObjectDestroyedCount(const ThingTemplate *tmpl, const Player *player, int amount);

private:
	char m_pad0[0x0C];
	int m_totalDestroyed[32];				// +0x0c
	char m_pad1[0xC4];					// 0x150 - 0x8c
	ObjectCountMap m_objectsDestroyed[32];			// +0x150
};

void ScoreKeeper::addObjectDestroyedCount(const ThingTemplate *tmpl, const Player *player, int amount)
{
	int playerIdx = player->getPlayerIndex();
	m_totalDestroyed[playerIdx] += amount;
	ObjectCountMap &counts = m_objectsDestroyed[playerIdx];
	int existingCount = 0;
	ObjectCountMapIt it = counts.find(tmpl);
	if (it != counts.end())
		existingCount = it->second;
	counts[tmpl] = existingCount + amount;
}
