// ?d_003e6300@@YAXXZ
// partial score=0.11 date=2026-09-24
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/terrainlogic /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4
#include "PreRTS.h"
#include "GameLogic/AIPathfind.h"
#include "Common/GlobalData.h"
#include "GameLogic/Locomotor.h"
#include "GameLogic/Object.h"
#include "GameLogic/TerrainLogic.h"

class Rva003E6300Owner : public Pathfinder
{
public:
	Bool method(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest);
};

class Rva003E6300TerrainView
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *dest);
};

#pragma comment(linker, "/alternatename:?getLayerForDestination@Rva003E6300TerrainView@@QAE?AW4PathfindLayerEnum@@PAVObject@@PBUCoord3D@@@Z=?j_0001c675@@YAXXZ")

#define m_zoneManager (*reinterpret_cast<PathfindZoneManager *>(reinterpret_cast<char *>(this) + 0xC9C))

Bool Rva003E6300Owner::method(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest)
{
	Int radius;
	Bool center;
	getRadiusAndCenter(obj, radius, center);
	ICoord2D goalCellNdx;
	Coord3D adjustDest = *dest;
	if (!center) {
		adjustDest.x += PATHFIND_CELL_SIZE_F / 2;
		adjustDest.y += PATHFIND_CELL_SIZE_F / 2;
	}
	if (worldToCell(&adjustDest, &goalCellNdx)) {
		return false;
	}

	PathfindLayerEnum destinationLayer = reinterpret_cast<Rva003E6300TerrainView *>(TheTerrainLogic)
		->getLayerForDestination(obj, dest);
	PathfindCell *goalCell = getCell(destinationLayer, goalCellNdx.x, goalCellNdx.y);
	Coord3D from = *obj->getPosition();
	ICoord2D startCellNdx;
	worldToCell(&from, &startCellNdx);
	PathfindLayerEnum layer = LAYER_GROUND;
	if (obj) {
		layer = obj->getLayer();
	}
	PathfindCell *parentCell = getClippedCell(layer, &from);
	if (parentCell == 0) {
		return false;
	}

	Int zone1;
	Int zone2;
	Bool isCrusher = obj ? obj->getCrusherLevel() > 0 : false;
	zone1 = m_zoneManager.getEffectiveZone(
		locomotorSet.getValidSurfaces(), isCrusher, parentCell->getZone());
	Bool isObstacle = false;
	if (parentCell->getType() == PathfindCell::CELL_OBSTACLE) {
		isObstacle = true;
	}
	if (isObstacle) {
		zone1 = m_zoneManager.getEffectiveTerrainZone(zone1);
		zone1 = m_zoneManager.getEffectiveZone(
			locomotorSet.getValidSurfaces(), isCrusher, zone1);
	}
	zone2 = m_zoneManager.getEffectiveZone(
		locomotorSet.getValidSurfaces(), isCrusher, goalCell->getZone());

	if (zone1 == zone2) {
		if (checkDestination(obj, goalCellNdx.x, goalCellNdx.y,
			destinationLayer, radius, center)) {
			return true;
		}
	}

	enum { MAX_CELLS_TO_TRY = 400 };
	Int limit = MAX_CELLS_TO_TRY;
	Int i = goalCellNdx.x;
	Int j = goalCellNdx.y;
	Int delta = 1;
	Int count;
	while (limit > 0) {
		for (count = delta; count > 0; count--) {
			i++;
			limit--;
			if (checkForPossible(isCrusher, zone1, center, locomotorSet,
				i, j, destinationLayer, dest, isObstacle)) {
				if (checkDestination(obj, i, j, destinationLayer, radius, center)) {
					return true;
				}
			}
		}
		for (count = delta; count > 0; count--) {
			j++;
			limit--;
			if (checkForPossible(isCrusher, zone1, center, locomotorSet,
				i, j, destinationLayer, dest, isObstacle)) {
				if (checkDestination(obj, i, j, destinationLayer, radius, center)) {
					return true;
				}
			}
		}
		delta++;
		for (count = delta; count > 0; count--) {
			i--;
			limit--;
			if (checkForPossible(isCrusher, zone1, center, locomotorSet,
				i, j, destinationLayer, dest, isObstacle)) {
				if (checkDestination(obj, i, j, destinationLayer, radius, center)) {
					return true;
				}
			}
		}
		for (count = delta; count > 0; count--) {
			j--;
			limit--;
			if (checkForPossible(isCrusher, zone1, center, locomotorSet,
				i, j, destinationLayer, dest, isObstacle)) {
				if (checkDestination(obj, i, j, destinationLayer, radius, center)) {
					return true;
				}
			}
		}
		delta++;
	}
	return false;
}
