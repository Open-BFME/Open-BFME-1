// ?d_00274e30@@YAXXZ
// partial score=0.28 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/iniexception /Ireference/shims/turretai /Ireference/shims/aiupdatelayout /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#include "PreRTS.h"
#include "Common/GlobalData.h"
#include "Common/ThingTemplate.h"
#include "GameLogic/AI.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/Locomotor.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Object.h"
#include "GameLogic/PolygonTrigger.h"

extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern void j_0003a17a(void);
typedef void (__cdecl *BFMEPathDebugLogFunction)(void *, const char *, ...);

struct BFMEComputePathFields
{
	char pad000[0x08];
	Object *m_object;
	char pad00C[0x30 - 0x0C];
	StateMachine *m_stateMachine;
	char pad034[0x140 - 0x34];
	Path *m_path;
	char pad144[0x160 - 0x144];
	UnsignedInt m_pathTimestamp;
	char pad164[0x16C - 0x164];
	Int m_blockedFrames;
	char pad170[0x1C0 - 0x170];
	void *m_locomotorSetName;
	char pad1C4[0x320 - 0x1C4];
	Bool m_isFinalGoal;
	char pad321[0x325 - 0x321];
	Bool m_isBlocked;
	Bool m_isBlockedAndStuck;
	char pad327[0x32E - 0x327];
	Bool m_retryPath;
};

// Zero Hour control-flow twin.  BFME's larger body adds CritterDesync tracing
// and uses the BFME AIUpdateInterface layout; this is the clean starting body.
Bool AIUpdateInterface::computePath( PathfindServicesInterface *pathServices, Coord3D *destination )
{
	BFMEComputePathFields *bfme = reinterpret_cast<BFMEComputePathFields *>(this);
	LocomotorSet *bfmeLocomotorSet = reinterpret_cast<LocomotorSet *>(reinterpret_cast<char *>(this) + 0x1A8);
	if (g_012F0239 && g_012ED4FC) {
		((BFMEPathDebugLogFunction)j_0003a17a)(g_012ED4FC,
			"CritterDesync: ComputePath43");
	}
	if (g_012F0239 && g_012ED4FC) {
		((BFMEPathDebugLogFunction)j_0003a17a)(g_012ED4FC,
			"CritterDesync:  Object %s(%d) called AIUpdateInterface::computePath()",
			getObject()->getTemplate()->getName().str(), getObject()->getID());
		if (g_012ED4FC) {
			double destinationX = destination->x;
			double destinationY = destination->y;
			double destinationZ = destination->z;
			((BFMEPathDebugLogFunction)j_0003a17a)(g_012ED4FC,
				"m_path=%s, m_locomotorSet=%s, destination=%g,%g,%g",
				bfme->m_path ? "VALID" : "NULL",
				bfme->m_locomotorSetName ? (const char *)bfme->m_locomotorSetName + 8 : "NULL",
				destinationX, destinationY, destinationZ);
		}
	}

	if (!bfme->m_isBlockedAndStuck) {
		destroyPath();
	}

	if (canComputeQuickPath()) {
		return computeQuickPath(destination);
	}
	bfme->m_retryPath = false;
	Region3D extent;
	TheTerrainLogic->getMaximumPathfindExtent(&extent);
	if (!extent.isInRegionNoZ(destination)) {
		Coord3D pos = *getObject()->getPosition();
		if (!extent.isInRegionNoZ(&pos)) {
			return computeQuickPath(destination);
		}
	}

	if ((bfme->m_stateMachine->getCurrentStateID() == AI_FOLLOW_EXITPRODUCTION_PATH) && canPathThroughUnits()) {
		Bool ok = computeQuickPath(destination);
		if (ok) {
			TheAI->pathfinder()->moveAlliesAwayFromDestination(getObject(), *destination);
			setCanPathThroughUnits(false);
			setGoalPositionClipped(destination, CMD_FROM_AI);
			return ok;
		}
	}

	Path *theNewPath = NULL;
	TheAI->pathfinder()->setIgnoreObstacleID(getIgnoredObstacleID());
	Coord3D originalDestination = *destination;
	LocomotorSurfaceTypeMask surfaces = bfmeLocomotorSet->getValidSurfaces();
	if (!bfme->m_isFinalGoal && TheAI->pathfinder()->isLinePassable(getObject(), surfaces,
			getObject()->getLayer(), *getObject()->getPosition(), originalDestination, false, true)) {
		return computeQuickPath(destination);
	}

	PathfindLayerEnum destinationLayer = TheTerrainLogic->getLayerForDestination(destination);
	if (TheAI->pathfinder()->validMovementPosition(getObject()->getCrusherLevel() > 0,
			destinationLayer, *bfmeLocomotorSet, destination) == FALSE) {
		theNewPath = NULL;
	} else if (bfme->m_isBlockedAndStuck) {
		theNewPath = pathServices->patchPath(getObject(), *bfmeLocomotorSet, getPath(), bfme->m_isBlockedAndStuck);
	} else {
		theNewPath = pathServices->findPath(getObject(), *bfmeLocomotorSet, getObject()->getPosition(), destination);
	}

	if (theNewPath == NULL && bfme->m_path == NULL) {
		Real pathCostFactor = 0.0f;
		theNewPath = pathServices->findClosestPath(getObject(), *bfmeLocomotorSet,
			getObject()->getPosition(), destination, bfme->m_isBlockedAndStuck, pathCostFactor, FALSE);
		bfme->m_retryPath = true;
	}
	TheAI->pathfinder()->setIgnoreObstacleID(INVALID_ID);
	if (theNewPath) {
		destroyPath();
		bfme->m_path = theNewPath;
		if (getCurLocomotor() && getCurLocomotor()->isUltraAccurate()) {
			theNewPath->updateLastNode(&originalDestination);
		}
		setLocomotorGoalPositionOnPath();
		if (!getObject()->isKindOf(KINDOF_NO_COLLIDE)) {
			TheAI->pathfinder()->moveAllies(getObject(), theNewPath);
		}
	} else if (bfme->m_path && bfme->m_isBlockedAndStuck) {
		destroyPath();
		setQueueForPathTime(LOGICFRAMES_PER_SECOND);
		Coord3D goalPos;
		Object *obj = getObject();
		goalPos = *obj->getPosition();
		TheAI->pathfinder()->snapPosition(obj, &goalPos);
		setFinalPosition(&goalPos);
		setLocomotorGoalNone();
		bfme->m_blockedFrames = 0;
		bfme->m_isBlocked = FALSE;
		bfme->m_isBlockedAndStuck = FALSE;
	}
	bfme->m_pathTimestamp = TheGameLogic->getFrame();
	bfme->m_blockedFrames = 0;
	bfme->m_isBlockedAndStuck = FALSE;
	return bfme->m_path != NULL;
}
