// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/moduledata /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /DBFME_MODULE_NO_MPO
// stlport
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameLogic/Module/LockWeaponCreate.h"

LockWeaponCreateModuleData::LockWeaponCreateModuleData()
{
	m_slotToLock = PRIMARY_WEAPON;
}

LockWeaponCreate::~LockWeaponCreate()
{
}

// 0x0024FC20. The base call reaches CreateModule's constructor at 0x0024F450
// through ILT 0x00026CAB, and the three vtable stores that follow are this
// class's own (0x010B18E4 / 0x010B1820 / 0x010B180C) -- the constructor the
// name getter, destructor and pool glue at 0x0024FC60..0x0024FD70 belong to.
LockWeaponCreate::LockWeaponCreate( Thing *thing, const ModuleData *moduleData )
	: CreateModule( thing, moduleData )
{
}
