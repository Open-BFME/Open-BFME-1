// ?friend_moveFormationToPos@AIGroup@@AAEXPBUCoord3D@@W4CommandSourceType@@@Z
// partial score=0.25 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// Partial reconstruction of BFME AIGroup::friend_moveFormationToPos.
// The Zero Hour implementation is the nearest named source twin; BFME replaced
// its small per-unit offset walk with the large formation planner at 0x0015AB50.
#include "PreRTS.h"

#include "Common/Player.h"
#include "GameLogic/AI.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/Module/AIUpdate.h"

static const Int PATH_DIAMETER_IN_CELLS = 6;

void AIGroup::friend_moveFormationToPos(const Coord3D *pos, CommandSourceType cmdSource)
{
	Real dx, dy;
	Coord3D center;
	if (!getCenter(&center))
		return;

	PathNode *startNode = NULL;
	PathNode *endNode = NULL;
	Coord3D endPoint = *pos;
	if (m_groundPath)
	{
		Coord3D startPoint = *m_groundPath->getFirstNode()->getPosition();
		Real farEnoughSqr = sqr(PATH_DIAMETER_IN_CELLS * PATHFIND_CELL_SIZE_F);
		PathNode *node;
		for (node = m_groundPath->getFirstNode(); node; node = node->getNextOptimized())
		{
			dx = node->getPosition()->x - startPoint.x;
			dy = node->getPosition()->y - startPoint.y;
			if (dx * dx + dy * dy > farEnoughSqr)
			{
				startNode = node;
				break;
			}
		}
		endPoint = *m_groundPath->getLastNode()->getPosition();
		for (node = m_groundPath->getFirstNode(); node; node = node->getNextOptimized())
		{
			dx = node->getPosition()->x - endPoint.x;
			dy = node->getPosition()->y - endPoint.y;
			if (dx * dx + dy * dy > farEnoughSqr)
				endNode = node;
		}
		PathNode *tmpNode = endNode;
		while (tmpNode)
		{
			if (tmpNode == startNode)
				endNode = NULL;
			tmpNode = tmpNode->getNextOptimized();
		}
		if (startNode == NULL || endNode == NULL)
		{
			m_groundPath->deleteInstance();
			m_groundPath = NULL;
			startNode = NULL;
			endNode = NULL;
		}
	}

	std::list<Object *>::iterator i;
	for (i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		if ((*i)->isDisabledByType(DISABLED_HELD))
			continue;
		Object *theUnit = *i;
		AIUpdateInterface *ai = theUnit->getAIUpdateInterface();
		Bool isDifferentFormation = false;
		Coord2D offset;
		if (isDifferentFormation)
		{
			Coord3D unitPos = *theUnit->getPosition();
			offset.x = unitPos.x - center.x;
			offset.y = unitPos.y - center.y;
			theUnit->setFormationOffset(offset);
		}
		theUnit->getFormationOffset(&offset);
		if (startNode)
		{
			std::vector<Coord3D> path;
			PathNode *node = startNode;
			while (node)
			{
				Coord3D dest = *node->getPosition();
				dest.x += offset.x;
				dest.y += offset.y;
				path.push_back(dest);
				if (node == endNode)
					break;
				node = node->getNextOptimized();
			}
			Coord3D dest = endPoint;
			dest.x += offset.x;
			dest.y += offset.y;
			TheAI->pathfinder()->adjustDestination(theUnit, ai->getLocomotorSet(), &dest, NULL);
			TheAI->pathfinder()->updateGoal(theUnit, &dest, LAYER_GROUND);
			path.push_back(dest);
			ai->aiFollowPath(&path, NULL, cmdSource);
		}
		else
		{
			Coord3D dest = endPoint;
			dest.x += offset.x;
			dest.y += offset.y;
			ai->aiMoveToPosition(&dest, cmdSource);
		}
	}
}
