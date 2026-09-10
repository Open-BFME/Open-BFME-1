// ?d_002284d0@@YAXXZ
// partial score=0.25 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Focused BFME ABI reconstruction of OpenContain::exitObjectViaDoor at
// retail 0x002284D0.  The retail entry is the +0x30 ExitInterface view.

#include "Common/AsciiString.h"
#include "GameClient/Drawable.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/OpenContain.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/Object.h"

#include <vector>

class BfmeOpenContainExitInterface
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0; virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0; virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0; virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0; virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0; virtual void slot26() = 0; virtual void slot27() = 0;
	virtual void slot28() = 0; virtual void slot29() = 0; virtual void slot30() = 0; virtual void slot31() = 0;
	virtual void slot32() = 0; virtual void slot33() = 0; virtual void slot34() = 0; virtual void slot35() = 0;
	virtual void removeFromContain(Object *object, Bool exposeStealthUnits) = 0;
};

class BfmeOpenContainExitModuleData
{
	unsigned char m_unreconstructed00[0x144];

public:
	Int m_numberOfExitPaths;
	UnsignedInt m_doorOpenTime;
};

class BfmeOpenContainExitObject
{
public:
	virtual void exitObjectViaDoor(Object *exitObj, ExitDoorType exitDoor);
};

// ?exitObjectViaDoor@BfmeOpenContainExitObject@@UAEXPAVObject@@W4ExitDoorType@@@Z
void BfmeOpenContainExitObject::exitObjectViaDoor(Object *exitObj, ExitDoorType exitDoor)
{
	DEBUG_ASSERTCRASH(exitDoor == DOOR_1, ("multiple exit doors not supported here"));

	register Object *exitObject = exitObj;
	register char *self = reinterpret_cast<char *>(this);
	BfmeOpenContainExitInterface *contain =
		reinterpret_cast<BfmeOpenContainExitInterface *>(self - 0x10);
	contain->removeFromContain(exitObject, FALSE);

	Object *me = *reinterpret_cast<Object **>(self - 0x28);
	BfmeOpenContainExitModuleData *moduleData =
		*reinterpret_cast<BfmeOpenContainExitModuleData **>(self - 0x2c);
	*reinterpret_cast<UnsignedInt *>(self + 0x3c) = moduleData->m_doorOpenTime;
	if (*reinterpret_cast<UnsignedInt *>(self + 0x3c))
	{
		me->clearAndSetModelConditionState(MODELCONDITION_DOOR_1_CLOSING,
			MODELCONDITION_DOOR_1_OPENING);
	}

	Int numberExits = moduleData->m_numberOfExitPaths;
	if (numberExits > 0)
	{
		AsciiString startBone("ExitStart");
		AsciiString endBone("ExitEnd");
		Coord3D startPosition;
		Coord3D endPosition;
		if (numberExits > 1)
		{
			char suffix[8];
			Int &whichExitPath = *reinterpret_cast<Int *>(self + 0x38);
			itoa(whichExitPath, suffix, 10);
			if (whichExitPath < 10)
			{
				startBone.concat('0');
				endBone.concat('0');
			}

			whichExitPath = (whichExitPath % numberExits) + 1;
			startBone.concat(suffix);
			endBone.concat(suffix);
		}
		me->getSingleLogicalBonePosition(startBone.str(), &startPosition, NULL);
		me->getSingleLogicalBonePosition(endBone.str(), &endPosition, NULL);

		Real exitAngle = me->getOrientation();
		PhysicsBehavior *physics = exitObject->getPhysics();
		Bool canFall = FALSE;
		if (physics)
			canFall = physics->getAllowToFall();
		exitObject->setPosition(&startPosition);
		exitObject->setOrientation(exitAngle);
		exitObject->setLayer(me->getLayer());

		AIUpdateInterface *ai = exitObject->getAI();
		AIUpdateInterface *myAi = me->getAI();
		TheAI->pathfinder()->addObjectToPathfindMap(exitObject);
		if (ai)
		{
			if (myAi && myAi->isIdle() && me->isKindOf(KINDOF_VEHICLE))
			{
				TheAI->pathfinder()->removeUnitFromPathfindMap(me);
				TheAI->pathfinder()->updatePos(me, me->getPosition());
				TheAI->pathfinder()->updateGoal(me, me->getPosition(),
					TheTerrainLogic->getLayerForDestination(me->getPosition()));
			}
			ai->ignoreObstacle(NULL);
			ai->setIgnoreCollisionTime(LOGICFRAMES_PER_SECOND);
			TheAI->pathfinder()->adjustToPossibleDestination(exitObject,
				ai->getLocomotorSet(), &endPosition);
		}

		std::vector<Coord3D> exitPath;
		exitPath.push_back(endPosition);
		exitPath.push_back(endPosition);
		if (*reinterpret_cast<Bool *>(self + 0x84))
			exitPath.push_back(*reinterpret_cast<Coord3D *>(self + 0x78));

		if (ai)
		{
			if (physics)
				physics->setAllowToFall(FALSE);
			ai->aiFollowPath(&exitPath, me, CMD_FROM_AI);
			TheAI->pathfinder()->updateGoal(exitObject, &endPosition,
				TheTerrainLogic->getLayerForDestination(&endPosition));
		}
		if (physics)
			physics->setAllowToFall(canFall);
	}
	else
	{
		TheAI->pathfinder()->addObjectToPathfindMap(exitObject);
	}
}
