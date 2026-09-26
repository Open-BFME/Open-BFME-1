// ?onContaining@RiderChangeContain@@UAEXPAVObject@@_N@Z
// partial score=0.16 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
// stlport
#define Matrix4x4 Matrix4
#include "PreRTS.h"
#define DEFINE_LOCOMOTORSET_NAMES
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/ThingTemplate.h"
#include "Common/ThingFactory.h"
#include "Common/Xfer.h"
#include "GameClient/ControlBar.h"
#include "GameClient/Drawable.h"
#include "GameClient/InGameUI.h"
#include "GameLogic/AI.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/ExperienceTracker.h"
#include "GameLogic/Object.h"
#include "GameLogic/Locomotor.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/Module/StealthUpdate.h"
#include "GameLogic/Module/RiderChangeContain.h"

void RiderChangeContain::onContaining(Object *rider, Bool wasSelected)
{
	if (getObject()->getRelationship(rider) != ALLIES)
	{
		TransportContain::onContaining(rider, wasSelected);
		return;
	}

	Object *obj = getObject();
	m_containing = TRUE;
	if (m_payloadCreated)
		obj->getAI()->aiEvacuateInstantly(TRUE, CMD_FROM_AI);

	Drawable *containDraw = getObject()->getDrawable();
	if (containDraw && wasSelected && !containDraw->isSelected())
	{
		GameMessage *teamMsg = TheMessageStream->appendMessage(GameMessage::MSG_CREATE_SELECTED_GROUP);
		teamMsg->appendBooleanArgument(FALSE);
		teamMsg->appendObjectIDArgument(getObject()->getID());
		TheInGameUI->selectDrawable(containDraw);
		TheInGameUI->setDisplayedMaxWarning(FALSE);
	}

	const RiderChangeContainModuleData *data = getRiderChangeContainModuleData();
	for (int i = 0; i < MAX_RIDERS; i++)
	{
		const ThingTemplate *thing = TheThingFactory->findTemplate(data->m_riders[i].m_templateName);
		if (thing->isEquivalentTo(rider->getTemplate()))
		{
			obj->setModelConditionState(data->m_riders[i].m_modelConditionFlagType);
			obj->setWeaponSetFlag(data->m_riders[i].m_weaponSetFlag);
			obj->setStatus(MAKE_OBJECT_STATUS_MASK(data->m_riders[i].m_objectStatusType));
			obj->setCommandSetStringOverride(data->m_riders[i].m_commandSet);
			TheControlBar->markUIDirty();

			AIUpdateInterface *ai = obj->getAI();
			if (ai)
				ai->chooseLocomotorSet(data->m_riders[i].m_locomotorSetType);

			if (obj->getStatusBits().test(OBJECT_STATUS_STEALTHED))
			{
				StealthUpdate *stealth = obj->getStealth();
				if (stealth)
					stealth->markAsDetected();
			}

			ExperienceTracker *riderTracker = rider->getExperienceTracker();
			ExperienceTracker *bikeTracker = obj->getExperienceTracker();
			bikeTracker->setVeterancyLevel(riderTracker->getVeterancyLevel(), FALSE);
			riderTracker->setExperienceAndLevel(0, FALSE);
			break;
		}
	}

	TransportContain::onContaining(rider, wasSelected);
	m_containing = FALSE;
}
