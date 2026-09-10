// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_MODULE_NO_MPO /Ireference/shims/dockupdate /Ireference/shims/bfmeobjectlayout /Ireference/shims/bfmekindof /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#define Matrix4x4 Matrix4

#include "PreRTS.h"

#include "Common/BitFlagsIO.h"
#include "Common/Radar.h"
#include "Common/PlayerList.h"
#include "Common/ThingTemplate.h"
#include "Common/ThingFactory.h"
#include "Common/Player.h"
#include "Common/Xfer.h"

#include "GameClient/GameClient.h"
#include "GameClient/Drawable.h"
#include "GameClient/GameText.h"
#include "GameClient/ParticleSys.h"
#include "GameClient/FXList.h"
#include "GameClient/ControlBar.h"

#include "GameLogic/GameLogic.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Object.h"
#include "GameLogic/ObjectIter.h"
#include "GameLogic/Weaponset.h"
#include "GameLogic/Weapon.h"
#include "GameLogic/TerrainLogic.h"
#include "GameLogic/Module/SpecialPowerModule.h"
#include "GameLogic/Module/BattlePlanUpdate.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/Module/ActiveBody.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/StealthDetectorUpdate.h"

// Player::iterateObjects ignores the callback return value, while the retail
// callback ABI returns Int; the call below casts to the upstream callback type.
extern Int paralyzeTroop( Object *obj, void *userData );

// BattlePlan's retail calls use the BFME vision-range setter body at
// 0x001BF3A0 via ILT 0x000228E0. Keep that layout-specific callee distinct:
// The BFME retail Object layout stores vision range at +0x194.
class BfmeBattlePlanVisionSetter
{
public:
	void setVisionRange( Real newVisionRange );
};

#pragma comment(linker, "/alternatename:?setVisionRange@BfmeBattlePlanVisionSetter@@QAEXM@Z=?j_000228e0@@YAXXZ")

// The retail Object keeps its BodyModuleInterface at +0x200.  The ordinary
// Object header's convenience accessor is a different-layout inline (+0x194),
// so keep this established BFME field view local to this TU.
class BattlePlanBodyInterfaceRetail
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual Real getHealth() const = 0;
	virtual void slot14() = 0;
	virtual Real getMaxHealth() const = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4c() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void setMaxHealth( Real maxHealth, MaxHealthChangeType healthChangeType ) = 0;
};

struct BattlePlanObjectBodyView
{
	unsigned char m_padding[ 0x200 ];
	BattlePlanBodyInterfaceRetail *m_body;
};

// Retail's BattlePlanModuleData puts these six fields at +0x84..+0x98;
// the upstream data header leaves a 0x10 gap in this BFME build.  The offsets
// are read directly from this body's retail loads, so keep the correction local.
struct BattlePlanUpdateModuleDataRetailView
{
	unsigned char m_padding[ 0x84 ];
	Real m_holdTheLineArmorDamageScalar;
	Real m_searchAndDestroySightRangeScalar;
	Real m_strategyCenterSearchAndDestroySightRangeScalar;
	Bool m_strategyCenterSearchAndDestroyDetectsStealth;
	Real m_strategyCenterHoldTheLineMaxHealthScalar;
	MaxHealthChangeType m_strategyCenterHoldTheLineMaxHealthChangeType;
};

// BattlePlanBonuses is a BFME plain field block at the retail call sites;
// the common MemoryPoolObject header would shift every member by four bytes.
struct BattlePlanBonusesRetailView
{
	Real m_armorScalar;
	Int m_bombardment;
	Int m_searchAndDestroy;
	Int m_holdTheLine;
	Real m_sightRangeScalar;
};

// ?setBattlePlan@BattlePlanUpdate@@IAEXW4BattlePlanStatus@@@Z matched 747 bytes
// Full retail body: 0x00285920 through ret 4 at 0x00285C08.
void BattlePlanUpdate::setBattlePlan( BattlePlanStatus plan )
{
	const BattlePlanUpdateModuleData *data = getBattlePlanUpdateModuleData();
	const BattlePlanUpdateModuleDataRetailView *retailData =
		(const BattlePlanUpdateModuleDataRetailView *)data;
	Object *obj = getObject();
	Player *player = obj->getControllingPlayer();
	if( player )
	{
		switch( m_planAffectingArmy )
		{
			case PLANSTATUS_BOMBARDMENT:
			{
				//Remove the previous plan!
				player->changeBattlePlan( PLANSTATUS_BOMBARDMENT, -1, m_bonuses );

				//The only building bonus is actually the turret, and that's already handled!
				break;
			}
			case PLANSTATUS_HOLDTHELINE:
			{
				//Remove the previous plan!
				player->changeBattlePlan( PLANSTATUS_HOLDTHELINE, -1, m_bonuses );

				//Remove building health bonuses
				if( retailData->m_strategyCenterHoldTheLineMaxHealthScalar != 1.0f )
				{
					BattlePlanBodyInterfaceRetail *body = ((BattlePlanObjectBodyView *)obj)->m_body;
					body->setMaxHealth( body->getMaxHealth() * 1.0f / retailData->m_strategyCenterHoldTheLineMaxHealthScalar, retailData->m_strategyCenterHoldTheLineMaxHealthChangeType );
				}
				break;
			}
			case PLANSTATUS_SEARCHANDDESTROY:
			{
				//Remove the previous plan!
				player->changeBattlePlan( PLANSTATUS_SEARCHANDDESTROY, -1, m_bonuses );

				//Remove sight range bonus
				if( retailData->m_strategyCenterSearchAndDestroySightRangeScalar != 1.0f )
				{
					((BfmeBattlePlanVisionSetter *)obj)->setVisionRange( obj->getVisionRange() * 1.0f / retailData->m_strategyCenterSearchAndDestroySightRangeScalar );
					obj->setShroudClearingRange( obj->getShroudClearingRange() * 1.0f / retailData->m_strategyCenterSearchAndDestroySightRangeScalar );
				}

				//Remove stealth detection
				if( retailData->m_strategyCenterSearchAndDestroyDetectsStealth )
				{
					static NameKeyType key_StealthDetectorUpdate = NAMEKEY( "StealthDetectorUpdate" );
					StealthDetectorUpdate *update = (StealthDetectorUpdate*)obj->findUpdateModule( key_StealthDetectorUpdate );
					if( update )
					{
						update->setSDEnabled( false );
					}
				}

				break;
			}
		}

		//Revert to default no-bonuses!
		((BattlePlanBonusesRetailView *)m_bonuses)->m_armorScalar = 1.0f;
		((BattlePlanBonusesRetailView *)m_bonuses)->m_sightRangeScalar = 1.0f;
		((BattlePlanBonusesRetailView *)m_bonuses)->m_bombardment = 0;
		((BattlePlanBonusesRetailView *)m_bonuses)->m_searchAndDestroy = 0;
		((BattlePlanBonusesRetailView *)m_bonuses)->m_holdTheLine = 0;

		//Add new bonuses!
		switch( plan )
		{
			case PLANSTATUS_NONE:
				//Paralyze troops!
				player->iterateObjects( (ObjectIterateFunc)paralyzeTroop, (void*)data );
				break;
			case PLANSTATUS_BOMBARDMENT:
				//Set the bombardment bonuses
				((BattlePlanBonusesRetailView *)m_bonuses)->m_bombardment = 1; //for weapon bonuses

				//Add the new plan!
				player->changeBattlePlan( PLANSTATUS_BOMBARDMENT, 1, m_bonuses );
				break;

			case PLANSTATUS_HOLDTHELINE:
				//Add building health bonuses
				if( retailData->m_strategyCenterHoldTheLineMaxHealthScalar )
				{
					BattlePlanBodyInterfaceRetail *body = ((BattlePlanObjectBodyView *)obj)->m_body;
					body->setMaxHealth( body->getMaxHealth() * retailData->m_strategyCenterHoldTheLineMaxHealthScalar, retailData->m_strategyCenterHoldTheLineMaxHealthChangeType );
				}

				//Set the hold-the-line bonuses
				((BattlePlanBonusesRetailView *)m_bonuses)->m_armorScalar = retailData->m_holdTheLineArmorDamageScalar;
				((BattlePlanBonusesRetailView *)m_bonuses)->m_holdTheLine = 1; //for weapon bonuses

				//Add the new plan!
				player->changeBattlePlan( PLANSTATUS_HOLDTHELINE, 1, m_bonuses );
				break;
			case PLANSTATUS_SEARCHANDDESTROY:
				//Add sight range bonus
				if( retailData->m_strategyCenterSearchAndDestroySightRangeScalar != 1.0f )
				{
					((BfmeBattlePlanVisionSetter *)obj)->setVisionRange( obj->getVisionRange() * retailData->m_strategyCenterSearchAndDestroySightRangeScalar );
					obj->setShroudClearingRange( obj->getShroudClearingRange() * retailData->m_strategyCenterSearchAndDestroySightRangeScalar );
				}

				//Enable stealth detection
				if( retailData->m_strategyCenterSearchAndDestroyDetectsStealth )
				{
					static NameKeyType key_StealthDetectorUpdate = NAMEKEY( "StealthDetectorUpdate" );
					StealthDetectorUpdate *update = (StealthDetectorUpdate*)obj->findUpdateModule( key_StealthDetectorUpdate );
					if( update )
					{
						update->setSDEnabled( true );
					}
				}

				//Set the search-and-destroy bonuses
				((BattlePlanBonusesRetailView *)m_bonuses)->m_searchAndDestroy = 1; //for weapon bonuses
				((BattlePlanBonusesRetailView *)m_bonuses)->m_sightRangeScalar = retailData->m_searchAndDestroySightRangeScalar;

				//Add the new plan!
				player->changeBattlePlan( PLANSTATUS_SEARCHANDDESTROY, 1, m_bonuses );
				break;
		}
		m_planAffectingArmy = plan;
	}
}
