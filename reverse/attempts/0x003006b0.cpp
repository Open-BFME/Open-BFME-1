// ?doCreateReinforcements@ScriptActions@@IAEXABVAsciiString@@0@Z
// partial score=0.24 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/scriptenginelayout /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4

#include "PreRTS.h"
#include "Common/PartitionSolver.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/Team.h"
#include "GameLogic/AI.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/DeliverPayloadAIUpdate.h"
#include "GameLogic/Module/TransportContain.h"
#include "GameLogic/ScriptActions.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/AIPathfind.h"

// Zero Hour twin of the BFME reinforcement creation body at 0x003006B0.
void ScriptActions::doCreateReinforcements(const AsciiString& team, const AsciiString& waypoint)
{
	TeamPrototype *theTeamProto = TheTeamFactory->findTeamPrototype(team);
	Coord3D destination;
	Bool needToMoveToDestination = false;
	Waypoint *way = TheTerrainLogic->getWaypointByName(waypoint);
	if (way == NULL)
		return;

	destination = *way->getLocation();
	if (!theTeamProto)
		return;

	const TeamTemplateInfo *pInfo = theTeamProto->getTemplateInfo();
	Coord3D origin = destination;
	way = TheTerrainLogic->getWaypointByName(pInfo->m_startReinforceWaypoint);
	if (way) {
		origin = *way->getLocation();
		if (origin.x != destination.x || origin.y != destination.y)
			needToMoveToDestination = true;
	}

	Team *theTeam = TheTeamFactory->createInactiveTeam(team);
	if (theTeam == NULL)
		return;

	const ThingTemplate *transportTemplate;
	const ThingTemplate *unitTemplate;
	Object *transport = NULL;
	ContainModuleInterface *contain = NULL;
	transportTemplate = TheThingFactory->findTemplate(pInfo->m_transportUnitType);
	if (transportTemplate) {
		transport = TheThingFactory->newObject(transportTemplate, theTeam);
		transport->setPosition(&origin);
		transport->setOrientation(0.0f);
		if (transport)
			contain = transport->getContain();
	}
	Int transportCount = 1;

	static NameKeyType key_DeliverPayloadAIUpdate = NAMEKEY("DeliverPayloadAIUpdate");
	DeliverPayloadAIUpdate *dp = NULL;
	if (transport)
		dp = (DeliverPayloadAIUpdate *)transport->findUpdateModule(key_DeliverPayloadAIUpdate);

	const ThingTemplate *putInContainerTemplate = NULL;
	if (dp)
		putInContainerTemplate = dp->getPutInContainerTemplateViaModuleData();

	Int i, j;
	for (i = 0; i < pInfo->m_numUnitsInfo; i++) {
		unitTemplate = TheThingFactory->findTemplate(pInfo->m_unitsInfo[i].unitThingName);
		Coord3D pos = origin;
		if (unitTemplate && theTeam) {
			Object *obj = NULL;
			for (j = 0; j < pInfo->m_unitsInfo[i].maxUnits; j++) {
				obj = TheThingFactory->newObject(unitTemplate, theTeam);
				if (obj) {
					pos.x = origin.x + 2.25 * j * obj->getGeometryInfo().getMajorRadius();
					pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y);
					obj->setPosition(&pos);
					obj->setOrientation(0.0f);
				}
			}
			if (obj)
				pos.y += 2 * obj->getGeometryInfo().getMajorRadius();
		}
		origin.y = pos.y;
	}

	origin = destination;
	if (pInfo->m_teamStartsFull) {
		EntriesVec vecOfUnits;
		SpacesVec vecOfTransports;
		for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
			Object *obj = iter.cur();
			if (!obj || obj == transport)
				continue;
			if (obj->isKindOf(KINDOF_TRANSPORT)) {
				ContainModuleInterface *itemContain = obj->getContain();
				if (itemContain)
					vecOfTransports.push_back(std::make_pair(obj->getID(), ((TransportContain *)itemContain)->getContainMax()));
			} else {
				Int slots = obj->getTransportSlotCount();
				if (slots == 0)
					slots = 0x7fffff;
				vecOfUnits.push_back(std::make_pair(obj->getID(), slots));
			}
		}

		PartitionSolver partition(vecOfUnits, vecOfTransports, PREFER_FAST_SOLUTION);
		partition.solve();
		SolutionVec solution = partition.getSolution();
		for (int solutionIndex = 0; solutionIndex < solution.size(); ++solutionIndex) {
			Object *unit = TheGameLogic->findObjectByID(solution[solutionIndex].first);
			Object *trans = TheGameLogic->findObjectByID(solution[solutionIndex].second);
			if (!unit || !trans)
				continue;
			ContainModuleInterface *itemContain = trans->getContain();
			if (itemContain)
				itemContain->addToContain(unit);
		}
	}

	contain = NULL;
	if (transport)
		contain = transport->getContain();
	if (contain) {
		for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
			Object *obj = iter.cur();
			if (!obj)
				continue;
			if (obj->getTemplate()->isEquivalentTo(transport->getTemplate()))
				continue;
			if (obj->getContainedBy() != NULL)
				continue;

			Coord3D pos = origin;
			pos.x += transportCount * transport->getGeometryInfo().getMajorRadius();
			pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y);
			if (contain->isValidContainerFor(obj, false)) {
				if (!contain->isValidContainerFor(obj, true)) {
					transport = TheThingFactory->newObject(transportTemplate, theTeam);
					transport->setPosition(&pos);
					transportCount++;
					transport->setOrientation(0.0f);
					if (transport)
						contain = transport->getContain();
				}
				if (putInContainerTemplate) {
					Object *container = TheThingFactory->newObject(putInContainerTemplate, theTeam);
					container->setPosition(&pos);
					if (container->getContain() && container->getContain()->isValidContainerFor(obj, true)) {
						container->getContain()->addToContain(obj);
						obj = container;
					}
				}
				contain->addToContain(obj);
			}
		}
	}

	if (theTeam) {
		if (transport) {
			for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
				Object *obj = iter.cur();
				if (!obj)
					continue;
				AIUpdateInterface *ai = obj->getAIUpdateInterface();
				if (obj->getTemplate()->isEquivalentTo(transport->getTemplate())) {
					if (dp) {
						dp->deliverPayloadViaModuleData(&destination);
					} else if (pInfo->m_transportsExit) {
						if (ai) {
							ai->chooseLocomotorSet(LOCOMOTORSET_NORMAL);
							ai->aiMoveToAndEvacuateAndExit(&destination, CMD_FROM_SCRIPT);
						}
					} else if (ai) {
						ai->chooseLocomotorSet(LOCOMOTORSET_NORMAL);
						ai->aiMoveToAndEvacuate(&destination, CMD_FROM_SCRIPT);
					}
				} else if (!obj->isDisabledByType(DISABLED_HELD) && ai) {
					ai->chooseLocomotorSet(LOCOMOTORSET_NORMAL);
					ai->aiMoveToPosition(&destination, CMD_FROM_SCRIPT);
				}
			}
		} else {
			theTeam->setActive();
			if (needToMoveToDestination) {
				AIGroup *theGroup = TheAI->createGroup();
				if (!theGroup)
					return;
				theTeam->getTeamAsAIGroup(theGroup);
				theGroup->groupMoveToPosition(&destination, false, CMD_FROM_SCRIPT);
			}
		}
	}
}
