// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
// readable body of ?calculateZones@PathfindZoneManager@@QAEXPAPAVPathfindCell@@QAVPathfindLayer@@ABUIRegion2D@@@Z: Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp

#include "Common/BitFlags.h"

class PathfindCell;
class PathfindLayer;
struct IRegion2D;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindZoneManager
{
public:
	void calculateZones(PathfindCell **map, PathfindLayer layers[], const IRegion2D &globalBounds);

private:
	void calculateZonesIncremental(PathfindCell **map, PathfindLayer layers[],
		const IRegion2D &globalBounds);

	unsigned char m_stateEnabled;
	unsigned char m_secondaryStateEnabled;
	unsigned char m_statePadding[2];
	int m_currentZone;
	char m_pathfinderStorage[0x23604];
	std::vector<BitFlags<113> > m_pendingCells;
};

void PathfindZoneManager::calculateZones(PathfindCell **map, PathfindLayer layers[],
	const IRegion2D &globalBounds)
{
	m_stateEnabled = 0;
	m_secondaryStateEnabled = 0;
	m_pendingCells.clear();
	m_currentZone = 0;
	do
	{
		calculateZonesIncremental(map, layers, globalBounds);
	}
	while (m_currentZone >= 0);
}
