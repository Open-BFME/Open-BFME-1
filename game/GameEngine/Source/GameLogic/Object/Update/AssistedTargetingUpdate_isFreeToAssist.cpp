// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/weapon /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/ini_noinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "PreRTS.h"
#include "GameLogic/Object.h"
#include "GameLogic/Weapon.h"
// Grok promote from masm_dumps — retail 0x0027FCE0 size 56
// was: game/masm_dumps/_cache__isFreeToAssist_AssistedTargetingUpdate__QBE_NXZ_27FCE0.asm

class AssistedTargetingObjectShim {
public:
	void *find(int flags);
};

class AssistedTargetingUpdate { public: bool isFreeToAssist(void) const; };

// ?isFreeToAssist@AssistedTargetingUpdate@@QBE_NXZ
bool AssistedTargetingUpdate::isFreeToAssist(void) const
{
	AssistedTargetingObjectShim *object =
		(AssistedTargetingObjectShim *)*(const void **)((const unsigned char *)this + 8);
	if (((Object *)object)->isAbleToAttack()) {
		if (object->find(0)) {
			Weapon *result = (Weapon *)object->find(0);
			if (!result->getStatus())
				return true;
		}
	}
	return false;
}
