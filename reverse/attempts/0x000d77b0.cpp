// ?becomingLocalPlayer@Player@@QAEX_N@Z
// partial score=0.45 date=2026-09-10
// stlport
#define Matrix4x4 Matrix4

#include "PreRTS.h"

#include "Common/GlobalData.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/Radar.h"

#include "GameClient/ControlBar.h"
#include "GameClient/Drawable.h"
#include "GameClient/GameClient.h"

#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/StealthUpdate.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"

// ?becomingLocalPlayer@Player@@QAEX_N@Z
void Player::becomingLocalPlayer(Bool yes)
{
	if (yes)
	{
		// This changes the color of the little dot on the upper right side of the screen indicating
		// which team is under control.
		if( TheGameClient )
		{
			RGBColor rgb;
			rgb.setFromInt(m_color);
			TheGameClient->setTeamColor(REAL_TO_INT(rgb.red*255), REAL_TO_INT(rgb.green*255), REAL_TO_INT(rgb.blue*255));
		}

		if( ThePartitionManager )
		{
			ObjectIterator *iter = ThePartitionManager->iterateAllObjects();
			for( Object* object = iter->first(); object; object = iter->next() )
			{
				// Added support for updating the perceptions of garrisoned buildings containing enemy stealth units.
				// When changing teams, it is necessary to update this information.
				ContainModuleInterface *contain = object->getContain();
				if( contain )
				{
					contain->recalcApparentControllingPlayer();
					TheRadar->removeObject( object );
					TheRadar->addObject( object );
				}

				if( object->isKindOf( KINDOF_DISGUISER ) )
				{
					//KM -- August 2002:
					//Added support for disguised objects, based on relationships, we either show the real color or the disguised color.
					Drawable *draw = object->getDrawable();
					if( draw )
					{
						StealthUpdate *update = object->getStealth();

						if( update && update->isDisguised() )
						{
							Player *disguisedPlayer = ThePlayerList->getNthPlayer( update->getDisguisedPlayerIndex() );
							if( getRelationship( object->getTeam() ) != ALLIES && isPlayerActive() )
							{
								//Neutrals and enemies will see this disguised unit as the team it's disguised as.
								if (TheGlobalData->m_timeOfDay == TIME_OF_DAY_NIGHT)
									draw->setIndicatorColor( disguisedPlayer->getPlayerNightColor());
								else
									draw->setIndicatorColor( disguisedPlayer->getPlayerColor() );
							}
							else
							{
								//Otherwise, the color will show up as the team it really belongs to.
								if (TheGlobalData->m_timeOfDay == TIME_OF_DAY_NIGHT)
									draw->setIndicatorColor(object->getNightIndicatorColor());
								else
									draw->setIndicatorColor( object->getIndicatorColor() );
							}
							TheRadar->removeObject( object );
							TheRadar->addObject( object );
						}
					}
				}
			}
			iter->deleteInstance();
		}

		if( TheControlBar )
			TheControlBar->markUIDirty();
	}
	else
	{
		// nothing to do
	}
}
