// readable body of ?connectsZones@PathfindLayer@@QAE_NPAVPathfindZoneManager@@ABVLocomotorSet@@HH@Z: Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
// BFME PathfindLayer::connectsZones. Unlike the later reference body, the
// 16-byte BFME cell stores its connect layer in flag bits 12..17 and the
// ground-cell zone must pass through both zone-manager equivalence maps.

typedef bool Bool;
typedef int Int;
typedef unsigned short zoneStorageType;

enum PathfindLayerEnum
{
	LAYER_INVALID = -1,
	LAYER_GROUND = 1,
	LAYER_FIRST_BRIDGE = 16
};

struct PathfindMovementProfile
{
	int acceptableSurfaces;
	Bool crusher;
	Bool terrainOnly;
	unsigned char padding[2];
	int layer;

	PathfindMovementProfile(int surfaces) :
		acceptableSurfaces(surfaces),
		crusher(false),
		terrainOnly(false),
		layer(LAYER_INVALID)
	{
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/LocomotorSet.h
class LocomotorSet
{
public:
	int getValidSurfaces(void) const { return m_validSurfaces; }

private:
	unsigned char opaque[0x10];
	int m_validSurfaces;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCell
{
public:
	zoneStorageType getZone(void) const { return m_zone; }
	PathfindLayerEnum getConnectLayer(void) const
	{
		return (PathfindLayerEnum)((m_flags >> 12) & 0x3f);
	}

private:
	unsigned char opaque[8];
	zoneStorageType m_zone;
	zoneStorageType m_nextZone;
	unsigned int m_flags;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct IRegion2D
{
	Int loX;
	Int loY;
	Int hiX;
	Int hiY;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	PathfindCell *getGroundCell(Int x, Int y) const
	{
		if (x < m_mapBounds.loX || x > m_mapBounds.hiX ||
			y < m_mapBounds.loY || y > m_mapBounds.hiY)
			return 0;
		return &m_map[x][y];
	}

private:
	unsigned char opaque[0x10];
	PathfindCell **m_map;
	IRegion2D m_mapBounds;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	Pathfinder *pathfinder(void) const { return m_pathfinder; }

private:
	unsigned char opaque[0x0c];
	Pathfinder *m_pathfinder;
};

extern "C" AI *TheAIParseDefinitionAI;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindZoneManager
{
public:
	zoneStorageType getEffectiveZone(
		const PathfindMovementProfile &profile, zoneStorageType zone) const;
	zoneStorageType bfmeEffectiveTerrainZone(
		const PathfindMovementProfile &profile, zoneStorageType zone) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindLayer
{
public:
	Bool connectsZones(PathfindZoneManager *zoneManager,
		const LocomotorSet &locomotorSet, Int zone1, Int zone2);

private:
	PathfindCell *m_blockOfMapCells;
	PathfindCell **m_layerCells;
	Int m_width;
	Int m_height;
	Int m_xOrigin;
	Int m_yOrigin;
	unsigned char opaque[0x34 - 0x18];
	Bool m_destroyed;
};

// ?connectsZones@PathfindLayer@@QAE_NPAVPathfindZoneManager@@ABVLocomotorSet@@HH@Z
Bool PathfindLayer::connectsZones(PathfindZoneManager *zoneManager,
	const LocomotorSet &locomotorSet, Int zone1, Int zone2)
{
	if (!m_destroyed)
		return false;

	Bool found1 = false;
	Bool found2 = false;
	for (Int i = 0; i < m_width; ++i)
	{
		for (Int j = 0; j < m_height; ++j)
		{
			PathfindCell *cell = &m_layerCells[i][j];
			PathfindLayerEnum connectLayer = cell->getConnectLayer();
			if (connectLayer == LAYER_GROUND || connectLayer >= LAYER_FIRST_BRIDGE)
			{
				PathfindCell *groundCell = TheAIParseDefinitionAI->pathfinder()->
					getGroundCell(i + m_xOrigin, j + m_yOrigin);
				if (groundCell)
				{
					PathfindMovementProfile profile(locomotorSet.getValidSurfaces());
					zoneStorageType zone = zoneManager->getEffectiveZone(
						profile, groundCell->getZone());
					zone = zoneManager->bfmeEffectiveTerrainZone(profile, zone);
					if (zone == zone1)
						found1 = true;
					if (zone == zone2)
						found2 = true;
				}
			}
		}
	}

	return found1 && found2;
}
