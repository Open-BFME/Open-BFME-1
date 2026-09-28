// ?calculateZonesIncremental@PathfindZoneManager@@AAEXPAPAVPathfindCell@@QAVPathfindLayer@@ABUIRegion2D@@@Z
// partial score=0.917 date=2026-09-27
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
// readable body of ?calculateZones@PathfindZoneManager@@QAEXPAPAVPathfindCell@@QAVPathfindLayer@@ABUIRegion2D@@@Z: game/GameEngine/Source/GameLogic/AI/AIPathfind.cpp

#include "Common/BitFlags.h"
#include "Lib/BaseType.h"

class PathfindCell;
class PathfindLayer;
struct IRegion2D;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindZoneManager
{
public:
	void calculateZones(PathfindCell **map, PathfindLayer layers[], const IRegion2D &globalBounds);

private:
	void calculateZonesIncremental(PathfindCell **map, PathfindLayer layers[],
		const IRegion2D &globalBounds);
	void method00405E80(PathfindCell **map, const IRegion2D &bounds,
		int startPercent, int endPercent);
	void method00402DB0(PathfindCell **map, const IRegion2D &bounds, bool unused);
	void method00403EC0(PathfindLayer *layers);
	void method00408480(PathfindCell **map, const IRegion2D &bounds,
		int startPercent, int endPercent);
	void method00404B10(PathfindCell **map, PathfindLayer *layers,
		const IRegion2D &bounds, int startPercent, int endPercent);
	void method00402F50(PathfindCell **map, PathfindLayer *layers,
		const IRegion2D &bounds);
	void method00402E90(int startPercent, int endPercent);

	unsigned char m_stateEnabled;
	unsigned char m_secondaryStateEnabled;
	unsigned char m_statePadding[2];
	int m_currentZone;
	IRegion2D m_cachedBounds;
	char m_pathfinderStorage[0x23604 - sizeof(IRegion2D)];
	std::vector<BitFlags<113> > m_pendingCells;
};

#pragma comment(linker, "/alternatename:?method00405E80@PathfindZoneManager@@AAEXPAPAVPathfindCell@@ABUIRegion2D@@HH@Z=?j_0002ff9f@@YAXXZ")
#pragma comment(linker, "/alternatename:?method00402DB0@PathfindZoneManager@@AAEXPAPAVPathfindCell@@ABUIRegion2D@@_N@Z=?j_000293c0@@YAXXZ")
#pragma comment(linker, "/alternatename:?method00403EC0@PathfindZoneManager@@AAEXPAVPathfindLayer@@@Z=?j_00044f7b@@YAXXZ")
#pragma comment(linker, "/alternatename:?method00408480@PathfindZoneManager@@AAEXPAPAVPathfindCell@@ABUIRegion2D@@HH@Z=?j_00037d67@@YAXXZ")
#pragma comment(linker, "/alternatename:?method00404B10@PathfindZoneManager@@AAEXPAPAVPathfindCell@@PAVPathfindLayer@@ABUIRegion2D@@HH@Z=?j_00024983@@YAXXZ")
#pragma comment(linker, "/alternatename:?method00402F50@PathfindZoneManager@@AAEXPAPAVPathfindCell@@PAVPathfindLayer@@ABUIRegion2D@@@Z=?j_00049d4b@@YAXXZ")
#pragma comment(linker, "/alternatename:?method00402E90@PathfindZoneManager@@AAEXHH@Z=?j_00021c6f@@YAXXZ")

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

extern double Gen01085F58;

void PathfindZoneManager::calculateZonesIncremental(PathfindCell **map,
	PathfindLayer layers[], const IRegion2D &globalBounds)
{
	if (m_stateEnabled && m_currentZone < 0)
	{
		m_stateEnabled = 0;
		m_currentZone = 0;
	}
	if (m_currentZone < 0)
		return;

	if (m_currentZone != 0)
	{
		int boundsDifference = globalBounds.lo.x ^ m_cachedBounds.lo.x;
		boundsDifference |= globalBounds.lo.y ^ m_cachedBounds.lo.y;
		boundsDifference |= globalBounds.hi.x ^ m_cachedBounds.hi.x;
		boundsDifference |= globalBounds.hi.y ^ m_cachedBounds.hi.y;
		if (boundsDifference != 0)
		{
			double resetTime = Gen01085F58;
			m_currentZone = 0;
			const IRegion2D *sourceBounds = &globalBounds;
			*(volatile double *)0x012F10B0 = resetTime;
			m_cachedBounds.lo.x = sourceBounds->lo.x;
			m_cachedBounds.lo.y = sourceBounds->lo.y;
			m_cachedBounds.hi.x = sourceBounds->hi.x;
			m_cachedBounds.hi.y = sourceBounds->hi.y;
		}
	}

	int zone = m_currentZone;
	if (zone < 0)
		goto zoneOneChecks;
	if (zone < 1)
	{
		int startPercent = zone * 100;
		method00405E80(map, globalBounds, startPercent, startPercent + 100);
		goto advanceZone;
	}

zoneOneChecks:
	if (zone < 1)
		goto zoneTwoChecks;
	if (zone < 2)
	{
		method00402DB0(map, globalBounds, false);
		method00403EC0(layers);
		goto advanceZone;
	}

zoneTwoChecks:
	if (zone < 2)
		goto zoneElevenChecks;
	if (zone < 11)
	{
		int startPercent = (zone - 2) * 100 / 9;
		int endPercent = (zone - 1) * 100 / 9;
		method00408480(map, globalBounds, startPercent, endPercent);
		goto advanceZone;
	}

zoneElevenChecks:
	if (zone < 11)
		goto zoneTwentyThreeChecks;
	if (zone < 23)
	{
		int startPercent = (zone - 11) * 100 / 12;
		int endPercent = (zone - 10) * 100 / 12;
		method00404B10(map, layers, globalBounds, startPercent, endPercent);
		goto advanceZone;
	}

zoneTwentyThreeChecks:
	if (zone < 23)
		goto finalZonePass;
	if (zone < 24)
	{
		int startPercent = (zone - 23) * 100;
		int endPercent = (zone - 22) * 100;
		method00402E90(startPercent, endPercent);
		goto advanceZone;
	}

finalZonePass:
	method00402F50(map, layers, globalBounds);
	m_currentZone = -1;

advanceZone:
	if (m_currentZone >= 0)
		++m_currentZone;
}
