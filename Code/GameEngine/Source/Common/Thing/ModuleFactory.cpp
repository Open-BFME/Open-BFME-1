// cl: /DNDEBUG /MD /EHsc /Ireference/shims/asciistring8 /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: ModuleFactory.cpp ////////////////////////////////////////////////////////////////////////
// Author: Colin Day, September 2001
// Desc:	 TheModuleFactory is where we actually instance modules for objects
//				 and drawbles.  Those modules are things such as an UpdateModule
//			   or DamageModule or DrawModule etc.
//	
//				 TheModuleFactory will contain a list of ModuleTemplates, when we
//				 request a new module, we will look for that template in our
//				 list and create it
//
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/Module.h"

template <class T> struct BFMEFactoryInstanceSize
{
	enum { VALUE = sizeof(T) };
};

template <class T, unsigned int SIZE> class BFMEFactoryModuleData : public ModuleData
{
public:
	BFMEFactoryModuleData();

private:
	char m_storage[SIZE - sizeof(ModuleData)];
};

template <class T> struct BFMEFactoryModuleDataChoice
{
	typedef T Type;
};

class AIUpdateInterface;
class AssaultTransportAIUpdate;
class AssistedTargetingUpdate;
class BattlePlanUpdate;
class BridgeBehavior;
class BridgeTowerBehavior;
class CaveContain;
class CashHackSpecialPower;
class CostModifierUpgrade;
class CreateCrateDie;
class CreateObjectDie;
class CrushDie;
class DeployStyleAIUpdate;
class DestroyDie;
class DozerAIUpdate;
class DynamicShroudClearingRangeUpdate;
class FXListDie;
class FireWeaponCollide;
class FireWeaponUpdate;
class FlammableUpdate;
class GarrisonContain;
class HealContain;
class InactiveBody;
class InstantDeathBehavior;
class KeepObjectDie;
class LaserUpdate;
class LifetimeUpdate;
class OCLUpdate;
class OpenContain;
class ProductionUpdate;
class RadiusDecalUpdate;
class RiderChangeContain;
class SlavedUpdate;
class SlowDeathBehavior;
class SpawnBehavior;
class SpecialAbilityUpdate;
class SpecialPowerCompletionDie;
class StealthUpdate;
class StructureCollapseUpdate;
class SubObjectsUpgrade;
class SupplyTruckAIUpdate;
class SwayClientUpdate;
class ToppleUpdate;
class TransportAIUpdate;
class TransportContain;
class TunnelContain;
class UpgradeDie;
class WanderAIUpdate;
class WorkerAIUpdate;

template <> struct BFMEFactoryInstanceSize<AIUpdateInterface> { enum { VALUE = 0x340 }; };
template <> struct BFMEFactoryInstanceSize<AssaultTransportAIUpdate> { enum { VALUE = 0x3A0 }; };
template <> struct BFMEFactoryInstanceSize<AssistedTargetingUpdate> { enum { VALUE = 0x20 }; };
template <> struct BFMEFactoryInstanceSize<BattlePlanUpdate> { enum { VALUE = 0x748 }; };
template <> struct BFMEFactoryInstanceSize<BridgeBehavior> { enum { VALUE = 0x488 }; };
template <> struct BFMEFactoryInstanceSize<BridgeTowerBehavior> { enum { VALUE = 0x24 }; };
template <> struct BFMEFactoryInstanceSize<CaveContain> { enum { VALUE = 0xE4 }; };
template <> struct BFMEFactoryInstanceSize<CashHackSpecialPower> { enum { VALUE = 0x2C }; };
template <> struct BFMEFactoryInstanceSize<CostModifierUpgrade> { enum { VALUE = 0x24 }; };
template <> struct BFMEFactoryInstanceSize<CreateCrateDie> { enum { VALUE = 0x14 }; };
template <> struct BFMEFactoryInstanceSize<CreateObjectDie> { enum { VALUE = 0x14 }; };
template <> struct BFMEFactoryInstanceSize<CrushDie> { enum { VALUE = 0x14 }; };
template <> struct BFMEFactoryInstanceSize<DeployStyleAIUpdate> { enum { VALUE = 0x408 }; };
template <> struct BFMEFactoryInstanceSize<DestroyDie> { enum { VALUE = 0x14 }; };
template <> struct BFMEFactoryInstanceSize<DozerAIUpdate> { enum { VALUE = 0x46C }; };
template <> struct BFMEFactoryInstanceSize<DynamicShroudClearingRangeUpdate> { enum { VALUE = 0x230 }; };
template <> struct BFMEFactoryInstanceSize<FXListDie> { enum { VALUE = 0x14 }; };
template <> struct BFMEFactoryInstanceSize<FireWeaponCollide> { enum { VALUE = 0x1C }; };
template <> struct BFMEFactoryInstanceSize<FireWeaponUpdate> { enum { VALUE = 0x24 }; };
template <> struct BFMEFactoryInstanceSize<FlammableUpdate> { enum { VALUE = 0x50 }; };
template <> struct BFMEFactoryInstanceSize<GarrisonContain> { enum { VALUE = 0x9B8 }; };
template <> struct BFMEFactoryInstanceSize<HealContain> { enum { VALUE = 0xD4 }; };
template <> struct BFMEFactoryInstanceSize<InactiveBody> { enum { VALUE = 0x1C }; };
template <> struct BFMEFactoryInstanceSize<InstantDeathBehavior> { enum { VALUE = 0x14 }; };
template <> struct BFMEFactoryInstanceSize<KeepObjectDie> { enum { VALUE = 0x14 }; };
template <> struct BFMEFactoryInstanceSize<LaserUpdate> { enum { VALUE = 0x54 }; };
template <> struct BFMEFactoryInstanceSize<LifetimeUpdate> { enum { VALUE = 0x28 }; };
template <> struct BFMEFactoryInstanceSize<OCLUpdate> { enum { VALUE = 0x28 }; };
template <> struct BFMEFactoryInstanceSize<OpenContain> { enum { VALUE = 0xD4 }; };
template <> struct BFMEFactoryInstanceSize<ProductionUpdate> { enum { VALUE = 0xE8 }; };
template <> struct BFMEFactoryInstanceSize<RadiusDecalUpdate> { enum { VALUE = 0x34 }; };
template <> struct BFMEFactoryInstanceSize<RiderChangeContain> { enum { VALUE = 0x110 }; };
template <> struct BFMEFactoryInstanceSize<SlavedUpdate> { enum { VALUE = 0x44 }; };
template <> struct BFMEFactoryInstanceSize<SlowDeathBehavior> { enum { VALUE = 0x50 }; };
template <> struct BFMEFactoryInstanceSize<SpawnBehavior> { enum { VALUE = 0x60 }; };
template <> struct BFMEFactoryInstanceSize<SpecialAbilityUpdate> { enum { VALUE = 0xE8 }; };
template <> struct BFMEFactoryInstanceSize<SpecialPowerCompletionDie> { enum { VALUE = 0x1C }; };
template <> struct BFMEFactoryInstanceSize<StealthUpdate> { enum { VALUE = 0x44 }; };
template <> struct BFMEFactoryInstanceSize<StructureCollapseUpdate> { enum { VALUE = 0x44 }; };
template <> struct BFMEFactoryInstanceSize<SubObjectsUpgrade> { enum { VALUE = 0x24 }; };
template <> struct BFMEFactoryInstanceSize<SupplyTruckAIUpdate> { enum { VALUE = 0x3D4 }; };
template <> struct BFMEFactoryInstanceSize<SwayClientUpdate> { enum { VALUE = 0x2C }; };
template <> struct BFMEFactoryInstanceSize<ToppleUpdate> { enum { VALUE = 0x58 }; };
template <> struct BFMEFactoryInstanceSize<TransportAIUpdate> { enum { VALUE = 0x340 }; };
template <> struct BFMEFactoryInstanceSize<TransportContain> { enum { VALUE = 0xE4 }; };
template <> struct BFMEFactoryInstanceSize<TunnelContain> { enum { VALUE = 0xD8 }; };
template <> struct BFMEFactoryInstanceSize<UpgradeDie> { enum { VALUE = 0x14 }; };
template <> struct BFMEFactoryInstanceSize<WanderAIUpdate> { enum { VALUE = 0x340 }; };
template <> struct BFMEFactoryInstanceSize<WorkerAIUpdate> { enum { VALUE = 0x508 }; };

class ActiveBodyModuleData;
class AutoDepositUpdateModuleData;
class BattlePlanUpdateModuleData;
class BoneFXUpdateModuleData;
class CashHackSpecialPowerModuleData;
class ChinookAIUpdateModuleData;
class CommandSetUpgradeModuleData;
class CreateCrateDieModuleData;
class CreateObjectDieModuleData;
class CrushDieModuleData;
class DemoTrapUpdateModuleData;
class DynamicShroudClearingRangeUpdateModuleData;
class FireWeaponUpdateModuleData;
class FireWeaponWhenDeadBehaviorModuleData;
class GarrisonContainModuleData;
class InternetHackContainModuleData;
class LaserUpdateModuleData;
class MaxHealthUpgradeModuleData;
class OCLSpecialPowerModuleData;
class OCLUpdateModuleData;
class OpenContainModuleData;
class PhysicsBehaviorModuleData;
class ProductionUpdateModuleData;
class SlowDeathBehaviorModuleData;
class SpecialAbilityUpdateModuleData;
class StealthDetectorUpdateModuleData;
class StructureCollapseUpdateModuleData;
class StructureToppleUpdateModuleData;
class SupplyCenterDockUpdateModuleData;
class SupplyTruckAIUpdateModuleData;
class ToppleUpdateModuleData;
class TransitionDamageFXModuleData;
class TransportContainModuleData;
class TunnelContainModuleData;
class WaveGuideUpdateModuleData;
class WorkerAIUpdateModuleData;
class UnitCrateCollideModuleData;
class UpgradeDieModuleData;

template <> struct BFMEFactoryInstanceSize<ActiveBodyModuleData> { enum { VALUE = 0x5C }; };
template <> struct BFMEFactoryInstanceSize<AutoDepositUpdateModuleData> { enum { VALUE = 0x20 }; };
template <> struct BFMEFactoryInstanceSize<BattlePlanUpdateModuleData> { enum { VALUE = 0xA0 }; };
template <> struct BFMEFactoryInstanceSize<BoneFXUpdateModuleData> { enum { VALUE = 0xD94 }; };
template <> struct BFMEFactoryInstanceSize<CashHackSpecialPowerModuleData> { enum { VALUE = 0x220 }; };
template <> struct BFMEFactoryInstanceSize<ChinookAIUpdateModuleData> { enum { VALUE = 0x16C }; };
template <> struct BFMEFactoryInstanceSize<CommandSetUpgradeModuleData> { enum { VALUE = 0x74 }; };
template <> struct BFMEFactoryInstanceSize<CreateCrateDieModuleData> { enum { VALUE = 0x38 }; };
template <> struct BFMEFactoryInstanceSize<CreateObjectDieModuleData> { enum { VALUE = 0x3C }; };
template <> struct BFMEFactoryInstanceSize<CrushDieModuleData> { enum { VALUE = 0x204 }; };
template <> struct BFMEFactoryInstanceSize<DemoTrapUpdateModuleData> { enum { VALUE = 0x3C }; };
template <> struct BFMEFactoryInstanceSize<DynamicShroudClearingRangeUpdateModuleData> { enum { VALUE = 0x58 }; };
template <> struct BFMEFactoryInstanceSize<FireWeaponUpdateModuleData> { enum { VALUE = 0x10 }; };
template <> struct BFMEFactoryInstanceSize<FireWeaponWhenDeadBehaviorModuleData> { enum { VALUE = 0xB4 }; };
template <> struct BFMEFactoryInstanceSize<GarrisonContainModuleData> { enum { VALUE = 0x33C }; };
template <> struct BFMEFactoryInstanceSize<InternetHackContainModuleData> { enum { VALUE = 0x16C }; };
template <> struct BFMEFactoryInstanceSize<LaserUpdateModuleData> { enum { VALUE = 0x1C }; };
template <> struct BFMEFactoryInstanceSize<MaxHealthUpgradeModuleData> { enum { VALUE = 0x78 }; };
template <> struct BFMEFactoryInstanceSize<OCLSpecialPowerModuleData> { enum { VALUE = 0x230 }; };
template <> struct BFMEFactoryInstanceSize<OCLUpdateModuleData> { enum { VALUE = 0x18 }; };
template <> struct BFMEFactoryInstanceSize<OpenContainModuleData> { enum { VALUE = 0x168 }; };
template <> struct BFMEFactoryInstanceSize<PhysicsBehaviorModuleData> { enum { VALUE = 0x5C }; };
template <> struct BFMEFactoryInstanceSize<ProductionUpdateModuleData> { enum { VALUE = 0x48 }; };
template <> struct BFMEFactoryInstanceSize<SlowDeathBehaviorModuleData> { enum { VALUE = 0x1A8 }; };
template <> struct BFMEFactoryInstanceSize<SpecialAbilityUpdateModuleData> { enum { VALUE = 0x254 }; };
template <> struct BFMEFactoryInstanceSize<StealthDetectorUpdateModuleData> { enum { VALUE = 0x13C }; };
template <> struct BFMEFactoryInstanceSize<StructureCollapseUpdateModuleData> { enum { VALUE = 0xF8 }; };
template <> struct BFMEFactoryInstanceSize<StructureToppleUpdateModuleData> { enum { VALUE = 0xB8 }; };
template <> struct BFMEFactoryInstanceSize<SupplyCenterDockUpdateModuleData> { enum { VALUE = 0x1C }; };
template <> struct BFMEFactoryInstanceSize<SupplyTruckAIUpdateModuleData> { enum { VALUE = 0xF4 }; };
template <> struct BFMEFactoryInstanceSize<ToppleUpdateModuleData> { enum { VALUE = 0x2C }; };
template <> struct BFMEFactoryInstanceSize<TransitionDamageFXModuleData> { enum { VALUE = 0x1040 }; };
template <> struct BFMEFactoryInstanceSize<TransportContainModuleData> { enum { VALUE = 0x17C }; };
template <> struct BFMEFactoryInstanceSize<TunnelContainModuleData> { enum { VALUE = 0x248 }; };
template <> struct BFMEFactoryInstanceSize<WaveGuideUpdateModuleData> { enum { VALUE = 0x16C }; };
template <> struct BFMEFactoryInstanceSize<WorkerAIUpdateModuleData> { enum { VALUE = 0x100 }; };
template <> struct BFMEFactoryInstanceSize<UnitCrateCollideModuleData> { enum { VALUE = 0x5C }; };
template <> struct BFMEFactoryInstanceSize<UpgradeDieModuleData> { enum { VALUE = 0x38 }; };

#define BFME_FACTORY_DATA_CHOICE(T) \
	template <> struct BFMEFactoryModuleDataChoice<T> \
	{ \
		typedef BFMEFactoryModuleData<T, BFMEFactoryInstanceSize<T>::VALUE> Type; \
	};

BFME_FACTORY_DATA_CHOICE(ActiveBodyModuleData)
BFME_FACTORY_DATA_CHOICE(AutoDepositUpdateModuleData)
BFME_FACTORY_DATA_CHOICE(BattlePlanUpdateModuleData)
BFME_FACTORY_DATA_CHOICE(BoneFXUpdateModuleData)
BFME_FACTORY_DATA_CHOICE(CashHackSpecialPowerModuleData)
BFME_FACTORY_DATA_CHOICE(ChinookAIUpdateModuleData)
BFME_FACTORY_DATA_CHOICE(CommandSetUpgradeModuleData)
BFME_FACTORY_DATA_CHOICE(CreateCrateDieModuleData)
BFME_FACTORY_DATA_CHOICE(CreateObjectDieModuleData)
BFME_FACTORY_DATA_CHOICE(CrushDieModuleData)
BFME_FACTORY_DATA_CHOICE(DemoTrapUpdateModuleData)
BFME_FACTORY_DATA_CHOICE(DynamicShroudClearingRangeUpdateModuleData)
BFME_FACTORY_DATA_CHOICE(FireWeaponUpdateModuleData)
BFME_FACTORY_DATA_CHOICE(FireWeaponWhenDeadBehaviorModuleData)
BFME_FACTORY_DATA_CHOICE(GarrisonContainModuleData)
BFME_FACTORY_DATA_CHOICE(InternetHackContainModuleData)
BFME_FACTORY_DATA_CHOICE(LaserUpdateModuleData)
BFME_FACTORY_DATA_CHOICE(MaxHealthUpgradeModuleData)
BFME_FACTORY_DATA_CHOICE(OCLSpecialPowerModuleData)
BFME_FACTORY_DATA_CHOICE(OCLUpdateModuleData)
BFME_FACTORY_DATA_CHOICE(OpenContainModuleData)
BFME_FACTORY_DATA_CHOICE(PhysicsBehaviorModuleData)
BFME_FACTORY_DATA_CHOICE(ProductionUpdateModuleData)
BFME_FACTORY_DATA_CHOICE(SlowDeathBehaviorModuleData)
BFME_FACTORY_DATA_CHOICE(SpecialAbilityUpdateModuleData)
BFME_FACTORY_DATA_CHOICE(StealthDetectorUpdateModuleData)
BFME_FACTORY_DATA_CHOICE(StructureCollapseUpdateModuleData)
BFME_FACTORY_DATA_CHOICE(StructureToppleUpdateModuleData)
BFME_FACTORY_DATA_CHOICE(SupplyCenterDockUpdateModuleData)
BFME_FACTORY_DATA_CHOICE(SupplyTruckAIUpdateModuleData)
BFME_FACTORY_DATA_CHOICE(ToppleUpdateModuleData)
BFME_FACTORY_DATA_CHOICE(TransitionDamageFXModuleData)
BFME_FACTORY_DATA_CHOICE(TransportContainModuleData)
BFME_FACTORY_DATA_CHOICE(TunnelContainModuleData)
BFME_FACTORY_DATA_CHOICE(UnitCrateCollideModuleData)
BFME_FACTORY_DATA_CHOICE(UpgradeDieModuleData)
BFME_FACTORY_DATA_CHOICE(WaveGuideUpdateModuleData)
BFME_FACTORY_DATA_CHOICE(WorkerAIUpdateModuleData)

#undef BFME_FACTORY_DATA_CHOICE

#undef MAKE_STANDARD_MODULE_MACRO
#undef MP_GLUE_ALLOCATE
#define MP_GLUE_ALLOCATE(ARGCLASS) ::operator new(BFMEFactoryInstanceSize<ARGCLASS>::VALUE)
#define MAKE_STANDARD_MODULE_MACRO( cls ) \
public: \
	static Module* friend_newModuleInstance( Thing *thing, const ModuleData* moduleData ) \
	{ \
		return new(cls::cls##_GLUE_NOT_IMPLEMENTED) cls(thing, moduleData); \
	} \
	virtual NameKeyType getModuleNameKey() const { static NameKeyType nk = NAMEKEY(#cls); return nk; } \
protected: \
	virtual void crc( Xfer *xfer ); \
	virtual void xfer( Xfer *xfer ); \
	virtual void loadPostProcess( void );
#include "Common/ModuleFactory.h"
#include "Common/NameKeyGenerator.h"
#include "../../../Include/GameLogic/Module/DamageModule.h"
#include "../../../Include/GameLogic/Module/CollideModule.h"

class RetailUpdateModuleDataBase : public ModuleData
{
public:
	RetailUpdateModuleDataBase();
	static void buildFieldParse(MultiIniFieldParse& p)
	{
		BehaviorModuleData::buildFieldParse(p);
	}

private:
	char m_bfmeLayoutPadding[ 0x5C ];
};

class RetailUpdateModuleData : public RetailUpdateModuleDataBase
{
};

#undef MAKE_STANDARD_MODULE_DATA_MACRO_ABC
#define MAKE_STANDARD_MODULE_DATA_MACRO_ABC( cls, clsmd ) \
private: \
	const clsmd* get##clsmd() const { return (clsmd*)getModuleData(); } \
public: \
	static ModuleData* friend_newModuleData(INI* ini) \
	{ \
		RetailUpdateModuleData* data = MSGNEW( "AllModuleData" ) RetailUpdateModuleData; \
		if (ini) ini->initFromINIMultiProc(data, RetailUpdateModuleData::buildFieldParse); \
		return data; \
	}
#include "GameLogic/Module/UpdateModule.h"
#undef MAKE_STANDARD_MODULE_DATA_MACRO_ABC
#define MAKE_STANDARD_MODULE_DATA_MACRO_ABC( cls, clsmd ) \
private: \
	const clsmd* get##clsmd() const { return (clsmd*)getModuleData(); } \
public: \
	static ModuleData* friend_newModuleData(INI* ini) \
	{ \
		typedef BFMEFactoryModuleDataChoice<clsmd>::Type RetailModuleDataType; \
		RetailModuleDataType* data = ::new RetailModuleDataType; \
		if (ini) ini->initFromINIMultiProc(data, clsmd::buildFieldParse); \
		return (ModuleData*)data; \
	}

// behavior includes
#include "GameLogic/Module/AutoHealBehavior.h"
#include "GameLogic/Module/GrantStealthBehavior.h"
#include "GameLogic/Module/NeutronBlastBehavior.h"
#include "GameLogic/Module/BehaviorModule.h"
#include "GameLogic/Module/BridgeBehavior.h"
#include "GameLogic/Module/BridgeScaffoldBehavior.h"
#include "GameLogic/Module/BridgeTowerBehavior.h"
#include "GameLogic/Module/CountermeasuresBehavior.h"
#include "GameLogic/Module/DumbProjectileBehavior.h"
#include "GameLogic/Module/InstantDeathBehavior.h"
#include "GameLogic/Module/SlowDeathBehavior.h"
#include "GameLogic/Module/HelicopterSlowDeathUpdate.h"
#include "GameLogic/Module/NeutronMissileSlowDeathUpdate.h"
#include "../../../Include/GameLogic/Module/CaveContain.h"
#include "GameLogic/Module/OpenContain.h"
#include "GameLogic/Module/OverchargeBehavior.h"
#include "GameLogic/Module/HealContain.h"
#include "GameLogic/Module/GarrisonContain.h"
#include "GameLogic/Module/InternetHackContain.h"
#include "GameLogic/Module/RailedTransportContain.h"
#include "GameLogic/Module/RiderChangeContain.h"
#include "GameLogic/Module/TransportContain.h"
#include "GameLogic/Module/MobNexusContain.h"
#include "GameLogic/Module/TunnelContain.h"
#include "GameLogic/Module/OverlordContain.h"
#include "GameLogic/Module/HelixContain.h"
#include "GameLogic/Module/ParachuteContain.h"
#ifdef ALLOW_SURRENDER
#include "GameLogic/Module/POWTruckBehavior.h"
#include "GameLogic/Module/PrisonBehavior.h"
#include "GameLogic/Module/PropagandaCenterBehavior.h"
#endif 
#include "GameLogic/Module/PropagandaTowerBehavior.h"
#include "GameLogic/Module/BunkerBusterBehavior.h"
#include "GameLogic/Module/FireWeaponWhenDamagedBehavior.h"
#include "GameLogic/Module/FireWeaponWhenDeadBehavior.h"
#include "GameLogic/Module/GenerateMinefieldBehavior.h"
#include "GameLogic/Module/ParkingPlaceBehavior.h"
#include "GameLogic/Module/FlightDeckBehavior.h"
#include "GameLogic/Module/PoisonedBehavior.h"
#include "GameLogic/Module/RebuildHoleBehavior.h"
#include "GameLogic/Module/SupplyWarehouseCripplingBehavior.h"
#include "GameLogic/Module/TechBuildingBehavior.h"
#include "GameLogic/Module/MinefieldBehavior.h"
#include "GameLogic/Module/BattleBusSlowDeathBehavior.h"
#include "GameLogic/Module/JetSlowDeathBehavior.h"

// die includes
#include "GameLogic/Module/CreateCrateDie.h"
#include "GameLogic/Module/CreateObjectDie.h"
#include "GameLogic/Module/CrushDie.h"
#include "GameLogic/Module/DamDie.h"
#include "GameLogic/Module/DestroyDie.h"
#include "GameLogic/Module/EjectPilotDie.h"
#include "GameLogic/Module/FXListDie.h"
#include "GameLogic/Module/RebuildHoleExposeDie.h"
#include "GameLogic/Module/SpecialPowerCompletionDie.h"
#include "GameLogic/Module/UpgradeDie.h"
#include "GameLogic/Module/KeepObjectDie.h"

// logic update includes
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/AnimationSteeringUpdate.h"
#include "GameLogic/Module/AssistedTargetingUpdate.h"
#include "GameLogic/Module/BaseRegenerateUpdate.h"
#include "GameLogic/Module/BoneFXUpdate.h"
#include "GameLogic/Module/ChinookAIUpdate.h"
#include "GameLogic/Module/DefaultProductionExitUpdate.h"
#include "GameLogic/Module/DeletionUpdate.h"
#include "GameLogic/Module/SmartBombTargetHomingUpdate.h"
#include "GameLogic/Module/DeliverPayloadAIUpdate.h"
#include "GameLogic/Module/DozerAIUpdate.h"
#include "GameLogic/Module/DynamicGeometryInfoUpdate.h"
#include "GameLogic/Module/DynamicShroudClearingRangeUpdate.h"
#include "GameLogic/Module/EnemyNearUpdate.h"
#include "GameLogic/Module/FireSpreadUpdate.h"
#include "GameLogic/Module/FirestormDynamicGeometryInfoUpdate.h"
#include "GameLogic/Module/FireWeaponUpdate.h"
#include "GameLogic/Module/FlammableUpdate.h"
#include "GameLogic/Module/FloatUpdate.h"
#include "GameLogic/Module/TensileFormationUpdate.h"
#include "GameLogic/Module/HackInternetAIUpdate.h"
#include "GameLogic/Module/DeployStyleAIUpdate.h"
#include "GameLogic/Module/AssaultTransportAIUpdate.h"
#include "GameLogic/Module/HeightDieUpdate.h"
#include "GameLogic/Module/HordeUpdate.h"
#include "GameLogic/Module/JetAIUpdate.h"
#include "GameLogic/Module/LaserUpdate.h"
#include "GameLogic/Module/PointDefenseLaserUpdate.h"
#include "GameLogic/Module/CleanupHazardUpdate.h"
#include "GameLogic/Module/AutoFindHealingUpdate.h"
#include "GameLogic/Module/CommandButtonHuntUpdate.h"
#include "GameLogic/Module/PilotFindVehicleUpdate.h"
#include "GameLogic/Module/DemoTrapUpdate.h"
#include "GameLogic/Module/ParticleUplinkCannonUpdate.h"
#include "GameLogic/Module/SpectreGunshipUpdate.h"
#include "GameLogic/Module/SpectreGunshipDeploymentUpdate.h"
#include "GameLogic/Module/BaikonurLaunchPower.h"
#include "GameLogic/Module/BattlePlanUpdate.h"
#include "GameLogic/Module/LifetimeUpdate.h"
#include "GameLogic/Module/RadiusDecalUpdate.h"
#include "GameLogic/Module/AutoDepositUpdate.h"
#include "GameLogic/Module/MissileAIUpdate.h"
#include "GameLogic/Module/NeutronMissileUpdate.h"
#include "GameLogic/Module/OCLUpdate.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#ifdef ALLOW_SURRENDER
#include "GameLogic/Module/POWTruckAIUpdate.h"
#endif
#include "GameLogic/Module/ProductionUpdate.h"
#include "GameLogic/Module/ProjectileStreamUpdate.h"
#include "GameLogic/Module/ProneUpdate.h"
#include "GameLogic/Module/QueueProductionExitUpdate.h"
#include "GameLogic/Module/RadarUpdate.h"
#include "GameLogic/Module/RepairDockUpdate.h"
#ifdef ALLOW_SURRENDER
#include "GameLogic/Module/PrisonDockUpdate.h"
#endif
#include "GameLogic/Module/RailedTransportDockUpdate.h"
#include "GameLogic/Module/RailedTransportAIUpdate.h"
#include "GameLogic/Module/RailroadGuideAIUpdate.h"
#include "GameLogic/Module/SlavedUpdate.h"
#include "GameLogic/Module/MobMemberSlavedUpdate.h"
#include "GameLogic/Module/SpecialAbilityUpdate.h"
#include "GameLogic/Module/MissileLauncherBuildingUpdate.h"
#include "GameLogic/Module/StealthDetectorUpdate.h"
#include "GameLogic/Module/StealthUpdate.h"
#include "GameLogic/Module/SpawnPointProductionExitUpdate.h"
#include "GameLogic/Module/SpawnBehavior.h"
#include "GameLogic/Module/SpyVisionUpdate.h"
#include "GameLogic/Module/StickyBombUpdate.h"
#include "GameLogic/Module/FireOCLAfterWeaponCooldownUpdate.h"
#include "GameLogic/Module/HijackerUpdate.h"
#include "GameLogic/Module/StructureCollapseUpdate.h"
#include "GameLogic/Module/StructureToppleUpdate.h"
#include "GameLogic/Module/SupplyCenterDockUpdate.h"
#include "GameLogic/Module/SupplyCenterProductionExitUpdate.h"
#include "GameLogic/Module/SupplyTruckAIUpdate.h"
#include "GameLogic/Module/SupplyWarehouseDockUpdate.h"
#include "GameLogic/Module/ToppleUpdate.h"
#include "GameLogic/Module/TransportAIUpdate.h"
#include "GameLogic/Module/WanderAIUpdate.h"
#include "GameLogic/Module/WaveGuideUpdate.h"
#include "GameLogic/Module/WeaponBonusUpdate.h"
#include "GameLogic/Module/WorkerAIUpdate.h"
#include "GameLogic/Module/PowerPlantUpdate.h"
#include "GameLogic/Module/CheckpointUpdate.h"
#include "GameLogic/Module/EMPUpdate.h"

// upgrade includes
#include "GameLogic/Module/ActiveShroudUpgrade.h"
#include "GameLogic/Module/ArmorUpgrade.h"
#include "GameLogic/Module/CommandSetUpgrade.h"
#include "GameLogic/Module/GrantScienceUpgrade.h"
#include "GameLogic/Module/PassengersFireUpgrade.h"
#include "GameLogic/Module/LocomotorSetUpgrade.h"
#include "GameLogic/Module/ObjectCreationUpgrade.h"
#include "GameLogic/Module/RadarUpgrade.h"
#include "GameLogic/Module/PowerPlantUpgrade.h"
#include "GameLogic/Module/ReplaceObjectUpgrade.h"
#include "GameLogic/Module/ModelConditionUpgrade.h"
#include "GameLogic/Module/StatusBitsUpgrade.h"
#include "GameLogic/Module/SubObjectsUpgrade.h"
#include "GameLogic/Module/StealthUpgrade.h"
#include "GameLogic/Module/UnpauseSpecialPowerUpgrade.h"
#include "GameLogic/Module/WeaponBonusUpgrade.h"
#include "GameLogic/Module/WeaponSetUpgrade.h"
#include "GameLogic/Module/WeaponBonusUpgrade.h"
#include "GameLogic/Module/CostModifierUpgrade.h"
#include "GameLogic/Module/ExperienceScalarUpgrade.h"
#include "GameLogic/Module/MaxHealthUpgrade.h"

// create includes
#include "GameLogic/Module/LockWeaponCreate.h"
#include "GameLogic/Module/SupplyCenterCreate.h"
#include "GameLogic/Module/SupplyWarehouseCreate.h"
#include "GameLogic/Module/GrantUpgradeCreate.h"
#include "GameLogic/Module/PreorderCreate.h"
#include "GameLogic/Module/SpecialPowerCreate.h"
#include "GameLogic/Module/VeterancyGainCreate.h"

// damage includes
#include "GameLogic/Module/BoneFXDamage.h"
#include "GameLogic/Module/TransitionDamageFX.h"

// collide includes
#include "GameLogic/Module/FireWeaponCollide.h"
#include "GameLogic/Module/SquishCollide.h"

#include "GameLogic/Module/ConvertToCarBombCrateCollide.h"
#include "GameLogic/Module/ConvertToHijackedVehicleCrateCollide.h"
#include "GameLogic/Module/HealCrateCollide.h"
#include "GameLogic/Module/MoneyCrateCollide.h"
#include "GameLogic/Module/SabotageCommandCenterCrateCollide.h"
#include "GameLogic/Module/SabotageFakeBuildingCrateCollide.h"
#include "GameLogic/Module/SabotageInternetCenterCrateCollide.h"
#include "GameLogic/Module/SabotageMilitaryFactoryCrateCollide.h"
#include "GameLogic/Module/SabotagePowerPlantCrateCollide.h"
#include "GameLogic/Module/SabotageSuperweaponCrateCollide.h"
#include "GameLogic/Module/SabotageSupplyCenterCrateCollide.h"
#include "GameLogic/Module/SabotageSupplyDropzoneCrateCollide.h"
#include "GameLogic/Module/SalvageCrateCollide.h"
#include "GameLogic/Module/ShroudCrateCollide.h"
#include "GameLogic/Module/UnitCrateCollide.h"

// BFME: VeterancyCrateCollide switched from createMemoryPool to findMemoryPool
#undef MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE
#define MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(ARGCLASS, ARGPOOLNAME) \
	MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
	GCMP_FIND(ARGCLASS, ARGPOOLNAME)

#include "GameLogic/Module/VeterancyCrateCollide.h"

// BFME: every module pool is a central pre-created lookup (findMemoryPool,
// 1 arg) - keep the shim default (GCMP_FIND) for all remaining headers.
#undef MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE
#define MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(ARGCLASS, ARGPOOLNAME) \
	MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
	GCMP_FIND(ARGCLASS, ARGPOOLNAME)

// body includes
#include "GameLogic/Module/InactiveBody.h"
#include "GameLogic/Module/ActiveBody.h"
#include "GameLogic/Module/HighlanderBody.h"
#include "GameLogic/Module/ImmortalBody.h"
#include "GameLogic/Module/StructureBody.h"
#include "GameLogic/Module/HiveStructureBody.h"
#include "GameLogic/Module/UndeadBody.h"

// contain includes
// (none)

// special power modules
#include "GameLogic/Module/CashHackSpecialPower.h"
#include "GameLogic/Module/DefectorSpecialPower.h"
#ifdef ALLOW_DEMORALIZE
#include "GameLogic/Module/DemoralizeSpecialPower.h"
#endif
#include "GameLogic/Module/OCLSpecialPower.h"
#include "GameLogic/Module/SpecialAbility.h"
#include "GameLogic/Module/SpyVisionSpecialPower.h"
#include "GameLogic/Module/CashBountyPower.h"
#include "GameLogic/Module/CleanupAreaPower.h"
#include "GameLogic/Module/FireWeaponPower.h"

// destroy includes
// (none)

// client update includes
#include "GameClient/Module/AnimatedParticleSysBoneClientUpdate.h"
#include "GameClient/Module/SwayClientUpdate.h"
#include "GameClient/Module/BeaconClientUpdate.h"

ModuleData* bfmeFactoryAnchorAutoDepositUpdateModuleData() { return ::new AutoDepositUpdateModuleData; }
ModuleData* bfmeFactoryAnchorCommandSetUpgradeModuleData() { return ::new CommandSetUpgradeModuleData; }
ModuleData* bfmeFactoryAnchorCreateCrateDieModuleData() { return ::new CreateCrateDieModuleData; }
ModuleData* bfmeFactoryAnchorFireWeaponWhenDeadBehaviorModuleData() { return ::new FireWeaponWhenDeadBehaviorModuleData; }
ModuleData* bfmeFactoryAnchorStealthDetectorUpdateModuleData() { return ::new StealthDetectorUpdateModuleData; }
ModuleData* bfmeFactoryAnchorStructureCollapseUpdateModuleData() { return ::new StructureCollapseUpdateModuleData; }
ModuleData* bfmeFactoryAnchorStructureToppleUpdateModuleData() { return ::new StructureToppleUpdateModuleData; }
ModuleData* bfmeFactoryAnchorSupplyTruckAIUpdateModuleData() { return ::new SupplyTruckAIUpdateModuleData; }
ModuleData* bfmeFactoryAnchorUnitCrateCollideModuleData() { return ::new UnitCrateCollideModuleData; }
ModuleData* bfmeFactoryAnchorUpgradeDieModuleData() { return ::new UpgradeDieModuleData; }
ModuleData* bfmeFactoryAnchorBoneFXUpdateModuleData() { return ::new BoneFXUpdateModuleData; }
ModuleData* bfmeFactoryAnchorCrushDieModuleData() { return ::new CrushDieModuleData; }
ModuleData* bfmeFactoryAnchorSpecialAbilityUpdateModuleData() { return ::new SpecialAbilityUpdateModuleData; }
ModuleData* bfmeFactoryAnchorTunnelContainModuleData() { return ::new TunnelContainModuleData; }
ModuleData* bfmeFactoryAnchorWorkerAIUpdateModuleData() { return ::new WorkerAIUpdateModuleData; }

// PUBLIC DATA ////////////////////////////////////////////////////////////////////////////////////
ModuleFactory *TheModuleFactory = NULL;  ///< the module factory singleton

// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??0ModuleFactory@@QAE@XZ present-unmatched
ModuleFactory::ModuleFactory( void )
{
	m_moduleTemplateMap.clear();
	m_moduleDataList.clear();
	
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1ModuleFactory@@UAE@XZ present-unmatched
ModuleFactory::~ModuleFactory( void )
{
	m_moduleTemplateMap.clear();

	for (ModuleDataList::iterator i = m_moduleDataList.begin(); i != m_moduleDataList.end(); ++i)
	{
		const ModuleData* data = *i;
		delete data;
	}
	m_moduleDataList.clear();

}

//-------------------------------------------------------------------------------------------------
/** Initialize the module factory.  Any class that needs to be attached
	* to objects or drawables as modules needs to add a template
	* for that class here */
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/System/module_factory.cpp
// ?init@ModuleFactory@@UAEXXZ present-unmatched
void ModuleFactory::init( void )
{

	// behavior modules
	addModule( AutoHealBehavior );
	addModule( GrantStealthBehavior );
	addModule( NeutronBlastBehavior );
	addModule( BridgeBehavior );
	addModule( BridgeScaffoldBehavior );
	addModule( BridgeTowerBehavior );
	addModule( CountermeasuresBehavior );
	addModule( DumbProjectileBehavior );
	addModule( PhysicsBehavior );
	addModule( InstantDeathBehavior );
	addModule( SlowDeathBehavior );
	addModule( HelicopterSlowDeathBehavior );
	addModule( NeutronMissileSlowDeathBehavior );
	addModule( CaveContain );
	addModule( OpenContain );
	addModule( OverchargeBehavior );
	addModule( HealContain );
	addModule( GarrisonContain );
	addModule( InternetHackContain );
	addModule( TransportContain );
	addModule( RiderChangeContain );
	addModule( RailedTransportContain );
	addModule( MobNexusContain );
	addModule( TunnelContain );
	addModule( OverlordContain );
	addModule( HelixContain );
	addModule( ParachuteContain );
#ifdef ALLOW_SURRENDER
	addModule( POWTruckBehavior );
	addModule( PrisonBehavior );
	addModule( PropagandaCenterBehavior );
#endif
	addModule( PropagandaTowerBehavior );
	addModule( BunkerBusterBehavior );
	addModule( FireWeaponWhenDamagedBehavior );
	addModule( FireWeaponWhenDeadBehavior );
	addModule( GenerateMinefieldBehavior );
	addModule( ParkingPlaceBehavior );
	addModule( FlightDeckBehavior );
	addModule( PoisonedBehavior );
	addModule( RebuildHoleBehavior );
	addModule( SupplyWarehouseCripplingBehavior );
	addModule( TechBuildingBehavior );
	addModule( MinefieldBehavior );
	addModule( BattleBusSlowDeathBehavior );
	addModule( JetSlowDeathBehavior );
	addModule( RailroadBehavior );
	addModule( SpawnBehavior );

	// die modules
	addModule( DestroyDie );
	addModule( FXListDie );
	addModule( CrushDie );
	addModule( DamDie );
	addModule( CreateCrateDie );
	addModule( CreateObjectDie );
	addModule( EjectPilotDie );
	addModule( SpecialPowerCompletionDie );
	addModule( RebuildHoleExposeDie );
	addModule( UpgradeDie );
	addModule( KeepObjectDie );

	// update modules
	addModule( AssistedTargetingUpdate );
	addModule( AutoFindHealingUpdate );
	addModule( BaseRegenerateUpdate );
	addModule( StealthDetectorUpdate );
	addModule( StealthUpdate );
	addModule( DeletionUpdate );
	addModule( SmartBombTargetHomingUpdate );
	addModule( DynamicShroudClearingRangeUpdate );
	addModule( DeployStyleAIUpdate );
	addModule( AssaultTransportAIUpdate );
	addModule( HordeUpdate );
	addModule( ToppleUpdate );
	addModule( EnemyNearUpdate );
	addModule( LifetimeUpdate );
	addModule( RadiusDecalUpdate );
	addModule( EMPUpdate );
  addModule( LeafletDropBehavior );
	addModule( AutoDepositUpdate );
	addModule( WeaponBonusUpdate );
	addModule( MissileAIUpdate );
	addModule( NeutronMissileUpdate );
	addModule( FireSpreadUpdate );
	addModule( FireWeaponUpdate );
	addModule( FlammableUpdate );
	addModule( FloatUpdate );
	addModule( TensileFormationUpdate );
	addModule( HeightDieUpdate );
	addModule( ChinookAIUpdate );
	addModule( JetAIUpdate );
	addModule( AIUpdateInterface );
	addModule( SupplyTruckAIUpdate );
	addModule( DeliverPayloadAIUpdate );
	addModule( HackInternetAIUpdate );
	addModule( DynamicGeometryInfoUpdate );
	addModule( FirestormDynamicGeometryInfoUpdate );
	addModule( LaserUpdate );
	addModule( PointDefenseLaserUpdate );
	addModule( CleanupHazardUpdate );
	addModule( CommandButtonHuntUpdate );
	addModule( PilotFindVehicleUpdate );
	addModule( DemoTrapUpdate );
	addModule( ParticleUplinkCannonUpdate );
	addModule( SpectreGunshipUpdate );
	addModule( SpectreGunshipDeploymentUpdate );
	addModule( BaikonurLaunchPower );
	addModule( BattlePlanUpdate );
	addModule( ProjectileStreamUpdate );
	addModule( QueueProductionExitUpdate );
	addModule( RepairDockUpdate );
#ifdef ALLOW_SURRENDER
	addModule( PrisonDockUpdate );
#endif
	addModule( RailedTransportDockUpdate );
	addModule( DefaultProductionExitUpdate );
	addModule( SpawnPointProductionExitUpdate );
	addModule( SpyVisionUpdate );
	addModule( SlavedUpdate );
	addModule( MobMemberSlavedUpdate );
	addModule( OCLUpdate );
	addModule( SpecialAbilityUpdate );
	addModule( MissileLauncherBuildingUpdate );
	addModule( SupplyCenterProductionExitUpdate );
	addModule( SupplyCenterDockUpdate );
	addModule( SupplyWarehouseDockUpdate );
	addModule( DozerAIUpdate );
#ifdef ALLOW_SURRENDER
	addModule( POWTruckAIUpdate );
#endif
	addModule( RailedTransportAIUpdate );
	addModule( ProductionUpdate );
	addModule( ProneUpdate );
	addModule( StickyBombUpdate );
	addModule( FireOCLAfterWeaponCooldownUpdate );
	addModule( HijackerUpdate );
	addModule( StructureToppleUpdate );
	addModule( StructureCollapseUpdate );
	addModule( BoneFXUpdate );
	addModule( RadarUpdate );
	addModule( AnimationSteeringUpdate );
	addModule( TransportAIUpdate );
	addModule( WanderAIUpdate );
	addModule( WaveGuideUpdate );
	addModule( WorkerAIUpdate );
	addModule( PowerPlantUpdate );
	addModule( CheckpointUpdate );

	// upgrade modules
	addModule( CostModifierUpgrade );
	addModule( ActiveShroudUpgrade );
	addModule( ArmorUpgrade );
	addModule( CommandSetUpgrade );
	addModule( GrantScienceUpgrade );
	addModule( PassengersFireUpgrade );
	addModule( StatusBitsUpgrade );
	addModule( SubObjectsUpgrade );
	addModule( StealthUpgrade );
	addModule( RadarUpgrade );
	addModule( PowerPlantUpgrade );
	addModule( LocomotorSetUpgrade );
	addModule( ObjectCreationUpgrade );
	addModule( ReplaceObjectUpgrade );
	addModule( ModelConditionUpgrade );
	addModule( UnpauseSpecialPowerUpgrade );
	addModule( WeaponBonusUpgrade );
	addModule( WeaponSetUpgrade );
	addModule( WeaponBonusUpgrade );
	addModule( ExperienceScalarUpgrade );
	addModule( MaxHealthUpgrade );

	// create modules
	addModule( LockWeaponCreate );
	addModule( PreorderCreate );
	addModule( SupplyCenterCreate );
	addModule( SupplyWarehouseCreate );
	addModule( SpecialPowerCreate );
	addModule( GrantUpgradeCreate );
	addModule( VeterancyGainCreate );

	// damage modules
	addModule( BoneFXDamage );
	addModule( TransitionDamageFX );

	// collide modules
	addModule( FireWeaponCollide );
	addModule( SquishCollide );

	addModule( HealCrateCollide );
	addModule( MoneyCrateCollide );
	addModule( ShroudCrateCollide );
	addModule( UnitCrateCollide );
	addModule( VeterancyCrateCollide );
	addModule( ConvertToCarBombCrateCollide );
	addModule( ConvertToHijackedVehicleCrateCollide );
	addModule( SabotageCommandCenterCrateCollide );
	addModule( SabotageFakeBuildingCrateCollide );
	addModule( SabotageInternetCenterCrateCollide );
	addModule( SabotageMilitaryFactoryCrateCollide );
	addModule( SabotagePowerPlantCrateCollide );
	addModule( SabotageSuperweaponCrateCollide );
	addModule( SabotageSupplyCenterCrateCollide );
	addModule( SabotageSupplyDropzoneCrateCollide );
	addModule( SalvageCrateCollide );

	// body modules
	addModule( InactiveBody );
	addModule( ActiveBody );
	addModule( HighlanderBody );
	addModule( ImmortalBody );
	addModule( StructureBody );
	addModule( HiveStructureBody );
	addModule( UndeadBody );

	// contain modules
	// (none)

	// special power modules
	addModule( CashHackSpecialPower );
	addModule( DefectorSpecialPower );
#ifdef ALLOW_DEMORALIZE
	addModule( DemoralizeSpecialPower );
#endif
	addModule( OCLSpecialPower );
	addModule( FireWeaponPower );
	addModule( SpecialAbility );
	addModule( SpyVisionSpecialPower );
	addModule( CashBountyPower );
	addModule( CleanupAreaPower );

	// destroy modules
	// (none)

	// client update modules
	addModule( AnimatedParticleSysBoneClientUpdate );
	addModule( SwayClientUpdate );
	addModule( BeaconClientUpdate );

}  // end init

//-------------------------------------------------------------------------------------------------
// The interface mask is at ModuleTemplate+0x0C, not the vendored +0x08. Nothing
// else in the body moves, including the isEmpty() guard and the tail.
struct BfmeModuleTemplateMask
{
	unsigned char m_unreconstructed_000[ 0x0c ];
	Int m_whichInterfaces;					///< retail this+0x0C
};

Int ModuleFactory::findModuleInterfaceMask(const AsciiString& name, ModuleType type)
{
	if (name.isEmpty())
		return 0;

	const ModuleTemplate* moduleTemplate = findModuleTemplate(name, type);
	if (moduleTemplate)
	{
		return ((const BfmeModuleTemplateMask *)moduleTemplate)->m_whichInterfaces;
	}

	return 0;
}

//-------------------------------------------------------------------------------------------------
ModuleData* ModuleFactory::newModuleDataFromINI(INI* ini, const AsciiString& name, ModuleType type,
																								const AsciiString& moduleTag)
{
	if (name.isEmpty())
		return NULL;

	const ModuleTemplate* moduleTemplate = findModuleTemplate(name, type);
	if (moduleTemplate)
	{
		ModuleData* md = (*moduleTemplate->m_createDataProc)(ini);
		md->setModuleTagNameKey( NAMEKEY( moduleTag ) );
		m_moduleDataList.push_back(md);
		return md;
	}

	return NULL;
}

// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
/*static*/ NameKeyType ModuleFactory::makeDecoratedNameKey(const AsciiString& name, ModuleType type)
{
	char tmp[256];
	tmp[0] = '0' + (int)type;
	strcpy(&tmp[1], name.str());
	return TheNameKeyGenerator->nameToKey(tmp);
}

//-------------------------------------------------------------------------------------------------
const ModuleFactory::ModuleTemplate* ModuleFactory::findModuleTemplate(const AsciiString& name, ModuleType type)
{
	NameKeyType namekey = makeDecoratedNameKey(name, type);

  ModuleTemplateMap::const_iterator it = m_moduleTemplateMap.find(namekey);
  if (it == m_moduleTemplateMap.end()) 
	{
		DEBUG_CRASH(( "Module name '%s' not found\n", name.str() ));
		return NULL;
	}
	else
	{
		return &(*it).second;
	}
}

//-------------------------------------------------------------------------------------------------
/** Allocate a new acton class istance given the name */
//-------------------------------------------------------------------------------------------------
Module *ModuleFactory::newModule( Thing *thing, const AsciiString& name, const ModuleData* moduleData, ModuleType type )
{
	// sanity
	if( name.isEmpty() )
	{
		DEBUG_CRASH(("attempting to create module with empty name\n"));
		return NULL;
	}
	const ModuleTemplate* mt = findModuleTemplate(name, type);
	if (mt)
	{
		Module* mod = (*mt->m_createProc)( thing, moduleData );

#ifdef _DEBUG
		if (type == MODULETYPE_BEHAVIOR)
		{
			BehaviorModule* bm = (BehaviorModule*)mod;

			DEBUG_ASSERTCRASH(
				((mt->m_whichInterfaces & (MODULEINTERFACE_BODY)) != 0) == (bm->getBody() != NULL), 
				("getInterfaceMask bad for MODULE_BODY (%s)\n",name.str()));
			DEBUG_ASSERTCRASH(
				((mt->m_whichInterfaces & (MODULEINTERFACE_COLLIDE)) != 0) == (bm->getCollide() != NULL), 
				("getInterfaceMask bad for MODULE_COLLIDE (%s)\n",name.str()));
			DEBUG_ASSERTCRASH(
				((mt->m_whichInterfaces & (MODULEINTERFACE_CONTAIN)) != 0) == (bm->getContain() != NULL), 
				("getInterfaceMask bad for MODULE_CONTAIN (%s)\n",name.str()));
			DEBUG_ASSERTCRASH(
				((mt->m_whichInterfaces & (MODULEINTERFACE_CREATE)) != 0) == (bm->getCreate() != NULL), 
				("getInterfaceMask bad for MODULE_CREATE (%s)\n",name.str()));
			DEBUG_ASSERTCRASH(
				((mt->m_whichInterfaces & (MODULEINTERFACE_DAMAGE)) != 0) == (bm->getDamage() != NULL), 
				("getInterfaceMask bad for MODULE_DAMAGE (%s)\n",name.str()));
			DEBUG_ASSERTCRASH(
				((mt->m_whichInterfaces & (MODULEINTERFACE_DESTROY)) != 0) == (bm->getDestroy() != NULL), 
				("getInterfaceMask bad for MODULE_DESTROY (%s)\n",name.str()));
			DEBUG_ASSERTCRASH(
				((mt->m_whichInterfaces & (MODULEINTERFACE_DIE)) != 0) == (bm->getDie() != NULL), 
				("getInterfaceMask bad for MODULE_DIE (%s)\n",name.str()));
			DEBUG_ASSERTCRASH(
				((mt->m_whichInterfaces & (MODULEINTERFACE_SPECIAL_POWER)) != 0) == (bm->getSpecialPower() != NULL), 
				("getInterfaceMask bad for MODULE_SPECIAL_POWER (%s)\n",name.str()));
			DEBUG_ASSERTCRASH(
				((mt->m_whichInterfaces & (MODULEINTERFACE_UPDATE)) != 0) == (bm->getUpdate() != NULL), 
				("getInterfaceMask bad for MODULE_UPDATE (%s)\n",name.str()));
			DEBUG_ASSERTCRASH(
				((mt->m_whichInterfaces & (MODULEINTERFACE_UPGRADE)) != 0) == (bm->getUpgrade() != NULL), 
				("getInterfaceMask bad for MODULE_UPGRADE (%s)\n",name.str()));
		}
#endif

		return mod;
	}

	return NULL;

}  // end newModule

//-------------------------------------------------------------------------------------------------
/** Add a module template to our list of templates */
//-------------------------------------------------------------------------------------------------
// ?addModuleInternal@ModuleFactory@@IAEXP6APAVModule@@PAVThing@@PBVModuleData@@@ZP6APAV4@PAVINI@@@ZW4ModuleType@@ABVAsciiString@@H@Z present-unmatched
void ModuleFactory::addModuleInternal( NewModuleProc proc, NewModuleDataProc dataproc, ModuleType type, const AsciiString& name, Int whichIntf )
{
	NameKeyType namekey = makeDecoratedNameKey(name, type);
	ModuleTemplate& mtm = m_moduleTemplateMap[namekey];	// this creates it if it does not exist already
	mtm.m_createProc = proc;
	mtm.m_createDataProc = dataproc;
	mtm.m_whichInterfaces = whichIntf;
}

//-------------------------------------------------------------------------------------------------
// ?crc@ModuleFactory@@UAEXPAVXfer@@@Z present-unmatched
void ModuleFactory::crc( Xfer *xfer )
{
	for (ModuleDataList::iterator mdIt = m_moduleDataList.begin(); mdIt != m_moduleDataList.end(); ++mdIt)
	{
		((ModuleData *)(*mdIt))->crc(xfer);
	}
}

//-------------------------------------------------------------------------------------------------
// ?xfer@ModuleFactory@@UAEXPAVXfer@@@Z present-unmatched
void ModuleFactory::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	for (ModuleDataList::iterator mdIt = m_moduleDataList.begin(); mdIt != m_moduleDataList.end(); ++mdIt)
	{
		((ModuleData *)(*mdIt))->xfer(xfer);
	}
}

//-------------------------------------------------------------------------------------------------
// ?loadPostProcess@ModuleFactory@@UAEXXZ present-unmatched
void ModuleFactory::loadPostProcess( void )
{
}
