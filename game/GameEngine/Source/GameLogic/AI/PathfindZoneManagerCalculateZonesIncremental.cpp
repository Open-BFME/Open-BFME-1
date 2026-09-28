// ?calculateZonesIncremental@PathfindZoneManager@@AAEXPAPAVPathfindCell@@QAVPathfindLayer@@ABUIRegion2D@@@Z
// cl: /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/GameEngine/Source/Common
// stlport
// Identity: named calculateZones caller and ILT 0x00033BEA to 0x00408AD0.
// Retail stage-zero reset includes the cached region and file-local timer.
// readable body of ?calculateZones@PathfindZoneManager@@QAEXPAPAVPathfindCell@@QAVPathfindLayer@@ABUIRegion2D@@@Z: game/GameEngine/Source/GameLogic/AI/AIPathfind.cpp

#include "region.h"
// Same native aggregate copy used by region.cpp, visible to this caller.
inline IRegion2D &IRegion2D::operator=(const IRegion2D &that)
{
    struct BoundsWords { int x_min, y_min, x_max, y_max; };
    *(BoundsWords *)this = *(const BoundsWords *)&that;
    return *this;
}

class PathfindCell;
struct LayerRecord403EC0;
class ZoneLayers403EC0 { public: void update(LayerRecord403EC0 *); };
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
public:
	void method00405E80(PathfindCell **map, const IRegion2D &bounds,
		int startPercent, int endPercent);
	void bfmeCollapseZones(PathfindCell **map, const IRegion2D &bounds, bool unused);

	void bfmeCalcZonesIncrementalStep00408480(PathfindCell **map, const IRegion2D &bounds,
		int startPercent, int endPercent);
	void method00404B10(PathfindCell **map, PathfindLayer *layers,
		const IRegion2D &bounds, int startPercent, int endPercent);
	void method00402F50(PathfindCell **map, PathfindLayer *layers,
		const IRegion2D &bounds);
	void bfmeFlattenZones(int startPercent, int endPercent);

private:
	unsigned char m_stateEnabled;
	unsigned char m_secondaryStateEnabled;
	unsigned char m_statePadding[2];
	int m_currentZone;
	IRegion2D m_cachedBounds;
	char m_pathfinderStorage[0x23604 - sizeof(IRegion2D)];

};


extern double Gen01085F58;
static double ZoneResetTime00408AD0;

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

    if (m_currentZone == 0 || globalBounds != m_cachedBounds)
    {
        double resetTime = Gen01085F58;
        m_currentZone = 0;
        ZoneResetTime00408AD0 = resetTime;
        m_cachedBounds = globalBounds;
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
		bfmeCollapseZones(map, globalBounds, false);
		((ZoneLayers403EC0 *)this)->update((LayerRecord403EC0 *)layers);
		goto advanceZone;
	}

zoneTwoChecks:
	if (zone < 2)
		goto zoneElevenChecks;
	if (zone < 11)
	{
		int startPercent = (zone - 2) * 100 / 9;
		int endPercent = (zone - 1) * 100 / 9;
		bfmeCalcZonesIncrementalStep00408480(map, globalBounds, startPercent, endPercent);
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
		bfmeFlattenZones(startPercent, endPercent);
		goto advanceZone;
	}

finalZonePass:
	method00402F50(map, layers, globalBounds);
	m_currentZone = -1;

advanceZone:
	if (m_currentZone >= 0)
		++m_currentZone;
}
