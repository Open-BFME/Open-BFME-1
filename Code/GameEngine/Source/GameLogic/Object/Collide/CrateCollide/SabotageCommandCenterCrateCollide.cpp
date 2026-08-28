// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /DBFME_MODULE_NO_MPO
// stlport
// readable body of ??0ConvertToCarBombCrateCollide@@: Code/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/ConvertToCarBombCrateCollide.cpp
// readable body of ??0ConvertToHijackedVehicleCrateCollide@@: Code/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/ConvertToHijackedVehicleCrateCollide.cpp
// readable body of ??0DamDie@@: Code/GameEngine/Source/GameLogic/Object/Die/DamDie.cpp
// readable body of ??0EjectPilotDie@@: Code/GameEngine/Source/GameLogic/Object/Die/EjectPilotDie.cpp
// readable body of ??0RebuildHoleExposeDie@@: Code/GameEngine/Source/GameLogic/Object/Die/RebuildHoleExposeDie.cpp
// readable body of ??0W3DDefaultDraw@@QAE@PAVThing@@PBVModuleData@@@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DDefaultDraw.cpp
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#include "PreRTS.h"
#include "GameLogic/Module/SabotageCommandCenterCrateCollide.h"

SabotageCommandCenterCrateCollide::SabotageCommandCenterCrateCollide(
	Thing *thing, const ModuleData *moduleData)
	: CrateCollide(thing, moduleData)
{
}
