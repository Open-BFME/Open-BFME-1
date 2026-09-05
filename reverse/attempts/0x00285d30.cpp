// ?onObjectCreated@BattlePlanUpdate@@UAEXXZ
// partial score=0.4 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
// Open-BFME5: BattlePlanUpdate::onObjectCreated, split from the still-unmatched
// present-unmatched body in BattlePlanUpdate.cpp (that copy carries ZH's
// getInfoForAudioEvent() calls and a separate enableTurret() call which do not
// appear in the retail 380-byte body at 0x00285D30 -- release build inlined
// enableTurret() here but did not inline the getInfoForAudioEvent loop, which
// retail simply does not run in this body). DEBUG_CRASH is compiled out under
// NDEBUG, matching the retail early-return-on-null-template shape.
#include "PreRTS.h"

#include "GameLogic/Object.h"
#include "GameLogic/Weaponset.h"
#include "GameLogic/Weapon.h"
#include "GameLogic/Module/SpecialPowerModule.h"
#include "GameLogic/Module/BattlePlanUpdate.h"
#include "GameLogic/Module/AIUpdate.h"

// ?onObjectCreated@BattlePlanUpdate@@UAEXXZ
void BattlePlanUpdate::onObjectCreated()
{
	const BattlePlanUpdateModuleData *data = getBattlePlanUpdateModuleData();
	Object *obj = getObject();

	if( !data->m_specialPowerTemplate )
	{
		m_invalidSettings = true;
		return;
	}

	m_specialPowerModule = obj->getSpecialPowerModule( data->m_specialPowerTemplate );

	m_bombardmentUnpack.setEventName( data->m_bombardmentUnpackName );
	m_bombardmentPack.setEventName( data->m_bombardmentPackName );
	m_bombardmentAnnouncement.setEventName( data->m_bombardmentAnnouncementName );
	m_searchAndDestroyUnpack.setEventName( data->m_searchAndDestroyUnpackName );
	m_searchAndDestroyIdle.setEventName( data->m_searchAndDestroyIdleName );
	m_searchAndDestroyPack.setEventName( data->m_searchAndDestroyPackName );
	m_searchAndDestroyAnnouncement.setEventName( data->m_searchAndDestroyAnnouncementName );
	m_holdTheLineUnpack.setEventName( data->m_holdTheLineUnpackName );
	m_holdTheLinePack.setEventName( data->m_holdTheLinePackName );
	m_holdTheLineAnnouncement.setEventName( data->m_holdTheLineAnnouncementName );

	getObject()->setWeaponSetFlag( WEAPONSET_VETERAN );
	AIUpdateInterface *ai = obj->getAI();
	if( ai )
	{
		obj->setWeaponLock( PRIMARY_WEAPON, LOCKED_TEMPORARILY );
	}

	ai = getObject()->getAI();
	if( ai )
	{
		WhichTurretType tur = ai->getWhichTurretForCurWeapon();
		if( tur != TURRET_INVALID )
		{
			ai->setTurretEnabled( tur, false );
		}
	}
}
