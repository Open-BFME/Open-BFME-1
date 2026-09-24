// ?d_003e6ee0@@YAXXZ
// partial score=0.26 date=2026-09-24
// stlport
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/terrainlogic /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// Extracted best available source body for the partial at 0x003E6EE0.
// The owning TU remains the Zero Hour twin under Code/GameEngine/Source/GameLogic/AI.

#define Matrix4x4 Matrix4
#include "PreRTS.h"
#include "GameLogic/AIPathfind.h"
#include "Common/PerfTimer.h"
#include "Common/Player.h"
#include "Common/CRCDebug.h"
#include "Common/GlobalData.h"
#include "Common/LatchRestore.h"
#include "Common/ThingTemplate.h"
#include "Common/ThingFactory.h"
#include "GameClient/Line2D.h"
#include "GameLogic/AI.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Locomotor.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/TerrainLogic.h"
#include "GameLogic/Weapon.h"
#include "Common/UnitTimings.h"
#include "Common/Xfer.h"
#include "Common/XferCRC.h"
#include "Common/PerfMetrics.h"

struct TCheckMovementInfo
{
	ICoord2D cell;
	PathfindLayerEnum layer;
	Int radius;
	Bool centerInCell;
	Bool considerTransient;
	LocomotorSurfaceTypeMask acceptableSurfaces;
	Int allyFixedCount;
	Bool enemyFixed;
	Bool allyMoving;
	Bool allyGoal;
};

struct BfmeAIUpdateInterfaceView
{
	unsigned char m_pad[0x328];
	Bool m_canPathThroughUnits;
	Bool canPathThroughUnits(void) const { return m_canPathThroughUnits; }
};

struct BfmeObjectAIView
{
	unsigned char m_pad[0x204];
	AIUpdateInterface *m_ai;
};

struct BfmePathfindCellView
{
	unsigned char m_pad[0x0C];
	unsigned int m_packed;
	PathfindLayerEnum getLayer(void) const
	{
		return (PathfindLayerEnum)((m_packed >> 6) & 0x3F);
	}
};

struct ExamineCellsStruct
{
	Int cellCallback( PathfindCell *from, PathfindCell *to, Int x, Int y );
	unsigned char m_payload[0x30];
};

class Rva003DB820Helper
{
public:
	void initialize( void *pathfinder, void *locomotorSet, Int centerInCell,
		Int radius, void *obj, Int isHuman, void *goalCell, Int attackDistance );
};

class Rva003E2F30Iterator
{
public:
	Int iterateCellsAlongLine( const ICoord2D &start, const ICoord2D &end,
		PathfindLayerEnum layer, ExamineCellsStruct *userData );
};

#pragma comment(linker, "/alternatename:?initialize@Rva003DB820Helper@@QAEXPAX0HH0H0H@Z=?j_00049ee0@@YAXXZ")
#pragma comment(linker, "/alternatename:?iterateCellsAlongLine@Rva003E2F30Iterator@@QAEHABUICoord2D@@0W4PathfindLayerEnum@@PAUExamineCellsStruct@@@Z=?j_00031c50@@YAXXZ")

const Int COST_ORTHOGONAL = 10;
const Int COST_DIAGONAL = 14;
Int Pathfinder::examineNeighboringCells(PathfindCell *parentCell, PathfindCell *goalCell, const LocomotorSet& locomotorSet, 
																				 Bool isHuman, Bool centerInCell, Int radius, const ICoord2D &startCellNdx,
																				 const Object *obj, Int attackDistance)
{
		BfmeAIUpdateInterfaceView *ai =
			(BfmeAIUpdateInterfaceView *)((BfmeObjectAIView *)obj)->m_ai;
		Bool canPathThroughUnits = false;
		if (ai)
			canPathThroughUnits = ai->canPathThroughUnits();
		Bool isCrusher = obj->getCrusherLevel() > 0;
		if (attackDistance==NO_ATTACK && !m_isTunneling && !locomotorSet.isDownhillOnly() && goalCell) {
			ExamineCellsStruct info;
			struct PathCellsVector
			{
				void *begin;
				void *end;
				void *capacity;
			};
			PathCellsVector *pathCells = (PathCellsVector *)((char *)this + 0x2470c);
			Int callbackAttackDistance = pathCells->begin == pathCells->end ? attackDistance : 0;
			((Rva003DB820Helper *)&info)->initialize(this, (void *)&locomotorSet,
				centerInCell, radius, (void *)obj, isHuman, goalCell,
				callbackAttackDistance);
			ICoord2D start, end;
			start.x = parentCell->getXIndex();
			start.y = parentCell->getYIndex();
			end.x = goalCell->getXIndex();
			end.y = goalCell->getYIndex();
			((Rva003E2F30Iterator *)this)->iterateCellsAlongLine(
				start, end,
				((BfmePathfindCellView *)parentCell)->getLayer(), &info);
		}

		Int cellCount = 0;
		// expand search to neighboring orthogonal cells
		static ICoord2D delta[] = 
		{ 
			{ 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 }, 
			{ 1, 1 }, { -1, 1 }, { -1, -1 }, { 1, -1 } 
		};
		const Int numNeighbors = 8;
		const Int firstDiagonal = 4;
		ICoord2D newCellCoord;
		PathfindCell *newCell;
		const Int adjacent[5] = {0, 1, 2, 3, 0};
		Bool neighborFlags[8] = {false, false, false, false, false, false, false};

		UnsignedInt newCostSoFar;



		for( int i=0; i<numNeighbors; i++ )
		{
			neighborFlags[i] = false;
			// determine neighbor cell to try
			newCellCoord.x = parentCell->getXIndex() + delta[i].x;
			newCellCoord.y = parentCell->getYIndex() + delta[i].y;

			// get the neighboring cell
			newCell = getCell(
				((BfmePathfindCellView *)parentCell)->getLayer(),
				newCellCoord.x, newCellCoord.y );

			// check if cell is on the map
			if (newCell == NULL)
				continue;

			Bool notZonePassable = false;
			if ((((BfmePathfindCellView *)newCell)->getLayer()==LAYER_GROUND) &&
				!m_zoneManager.isPassable(newCellCoord.x, newCellCoord.y)) {
				notZonePassable = true;
			}
			if (isHuman) {
				// check if new cell is in logical map.	(computer can move off logical map)
				if (newCellCoord.x < m_logicalExtent.lo.x) continue;
				if (newCellCoord.y < m_logicalExtent.lo.y) continue; 
				if (newCellCoord.x > m_logicalExtent.hi.x) continue; 
				if (newCellCoord.y > m_logicalExtent.hi.y) continue; 
			}

			// check if this neighbor cell is already on the open (waiting to be tried) 
			// or closed (already tried) lists
			Bool onList = false;
			if (newCell->hasInfo()) {
				if (newCell->getOpen() || newCell->getClosed())
				{
					// already on one of the lists 
					onList = true;
				}
			}
			if (onList) {
				// we have already examined this one, so continue.
				continue;
			}
			if (i>=firstDiagonal) {
				// make sure one of the adjacent sides is open.
				if (!neighborFlags[adjacent[i-4]] && !neighborFlags[adjacent[i-3]]) {
					continue;
				}
			}

			// do the gravity check here
			if ( locomotorSet.isDownhillOnly() )
			{
				Coord3D fromPos;
				fromPos.x = parentCell->getXIndex() * PATHFIND_CELL_SIZE_F ;
				fromPos.y = parentCell->getYIndex() * PATHFIND_CELL_SIZE_F ;
				fromPos.z = TheTerrainLogic->getGroundHeight(fromPos.x , fromPos.y);

				Coord3D toPos;
				toPos.x = newCellCoord.x * PATHFIND_CELL_SIZE_F ;
				toPos.y = newCellCoord.y * PATHFIND_CELL_SIZE_F ;
				toPos.z = TheTerrainLogic->getGroundHeight(toPos.x , toPos.y);

				if ( fromPos.z < toPos.z )
					continue;
			}



			Bool movementValid = true;
			Bool dozerHack = false;
			if (validMovementPosition( isCrusher, locomotorSet.getValidSurfaces(), newCell, parentCell )) {
			}	else {
				movementValid = false;
				if (obj->isKindOf(KINDOF_DOZER)) {
					if (newCell->getType()==PathfindCell::CELL_OBSTACLE) {
						Object *obstacle = TheGameLogic->findObjectByID(newCell->getObstacleID());
						if (obstacle && !(obj->getRelationship(obstacle)==ENEMIES)) {
							movementValid = true;
							dozerHack = true;
						}
					}
				}
				if (!movementValid && !m_isTunneling) {
					continue;
				}
			}	
			if (!dozerHack) 
				neighborFlags[i] = true;

			TCheckMovementInfo info;
			info.cell = newCellCoord;
			info.layer = ((BfmePathfindCellView *)parentCell)->getLayer();
			info.centerInCell = centerInCell;
			info.radius = radius;
			info.considerTransient = false;
			info.acceptableSurfaces = locomotorSet.getValidSurfaces();
			Int dx = newCellCoord.x-startCellNdx.x;
			Int dy = newCellCoord.y-startCellNdx.y;
			if (dx<0) dx = -dx;
			if (dy<0) dy = -dy;
			if (dx>1+radius) info.considerTransient = false;
			if (dy>1+radius) info.considerTransient = false;
			if (!checkForMovement(obj, info) || info.enemyFixed) {
				if (!m_isTunneling) {
					continue;
				}
				movementValid = false;
			}	
			if (movementValid && !newCell->getPinched()) {
				//Note to self - only turn off tunneling after check for movement.jba. 
				m_isTunneling = false;
			}
			if (!newCell->hasInfo()) {
				if (!newCell->allocateInfo(newCellCoord)) {
					// Out of cells for pathing...
 					return cellCount;
				}								
				cellCount++;
			}

			newCostSoFar = newCell->costSoFar( parentCell );
			if (info.allyMoving && dx<10 && dy<10) {
				newCostSoFar += 3*COST_DIAGONAL;
			}
			if (newCell->getType() == PathfindCell::CELL_CLIFF && !newCell->getPinched() ) {
				Coord3D fromPos;
				fromPos.x = parentCell->getXIndex() * PATHFIND_CELL_SIZE_F ;
				fromPos.y = parentCell->getYIndex() * PATHFIND_CELL_SIZE_F ;
				fromPos.z = TheTerrainLogic->getGroundHeight(fromPos.x , fromPos.y);

				Coord3D toPos;
				toPos.x = newCellCoord.x * PATHFIND_CELL_SIZE_F ;
				toPos.y = newCellCoord.y * PATHFIND_CELL_SIZE_F ;
				toPos.z = TheTerrainLogic->getGroundHeight(toPos.x , toPos.y);

				if ( fabs(fromPos.z - toPos.z)<PATHFIND_CELL_SIZE_F) {
					newCostSoFar += 7*COST_DIAGONAL;
				}
			} else if (newCell->getPinched()) {
				newCostSoFar += COST_ORTHOGONAL;
			}
			newCell->setBlockedByAlly(false);
			if (info.allyFixedCount>0) {
				Int costFactor = 3*COST_DIAGONAL;
				if (attackDistance != NO_ATTACK) {
					costFactor = 3*COST_DIAGONAL;
				}
				if (canPathThroughUnits) {
					newCostSoFar += costFactor;
				}	else {
					newCell->setBlockedByAlly(true);
					newCostSoFar += costFactor;
				}
			} 
			Int costRemaining = 0;
			if (goalCell) {
				if (attackDistance == NO_ATTACK)  {
					costRemaining = newCell->costToGoal( goalCell );
				}	else {
					dx = newCellCoord.x - goalCell->getXIndex();
					dy = newCellCoord.y - goalCell->getYIndex();
					costRemaining = COST_ORTHOGONAL*sqrt(dx*dx + dy*dy);
					costRemaining -= attackDistance/2;
					if (costRemaining<0) costRemaining=0;
					if (info.allyGoal) {
						if (obj->isKindOf(KINDOF_VEHICLE)) {
							newCostSoFar += 3*COST_ORTHOGONAL; 
						}	else {
							// Infantry can pass through infantry.
							newCostSoFar += COST_ORTHOGONAL;
						}
					}
				}
			}
			if (notZonePassable) {
				newCostSoFar += 100*COST_ORTHOGONAL;
			}
			if (newCell->getType()==PathfindCell::CELL_OBSTACLE) {
				newCostSoFar += 100*COST_ORTHOGONAL;
			}
			// check if this neighbor cell is already on the open (waiting to be tried) 
			// or closed (already tried) lists
			if (onList)
			{
				// already on one of the lists - if existing costSoFar is less, 
				// the new cell is on a longer path, so skip it
				if (newCell->getCostSoFar() <= newCostSoFar)
					continue;
			}
			if (m_isTunneling) {
				if (!validMovementPosition( isCrusher, locomotorSet.getValidSurfaces(), newCell, parentCell )) {
					newCostSoFar += 10*COST_ORTHOGONAL;
				}
			}
			newCell->setCostSoFar(newCostSoFar);
			// keep track of path we're building - point back to cell we moved here from
			newCell->setParentCell(parentCell) ;
			if (m_isTunneling) {
				costRemaining = 0; // find the closest valid cell.
			}
			newCell->setTotalCost(newCell->getCostSoFar() + costRemaining) ;

			//DEBUG_LOG(("Cell (%d,%d), Parent cost %d, newCostSoFar %d, cost rem %d, tot %d\n", 
			//	newCell->getXIndex(), newCell->getYIndex(), 
			//	newCell->costSoFar(parentCell), newCostSoFar, costRemaining, newCell->getCostSoFar() + costRemaining));

			// if newCell was on closed list, remove it from the list
			if (newCell->getClosed())
				m_closedList = newCell->removeFromClosedList( m_closedList );

			// if the newCell was already on the open list, remove it so it can be re-inserted in order
			if (newCell->getOpen())
				m_openList = newCell->removeFromOpenList( m_openList );

			// insert newCell in open list such that open list is sorted, smallest total path cost first
			m_openList = newCell->putOnSortedOpenList( m_openList );
		}
	return cellCount;
}
