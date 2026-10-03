// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/weapon /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/ini_noinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "PreRTS.h"
#include "Common/INI.h"
#include "GameLogic/Weapon.h"
#include <math.h>

static inline float Rva000B94B0Scale(float value) { return value * 0.005f; }

/*static*/ void WeaponTemplate::parseShotDelay( INI* ini, void *instance, void * /*store*/, const void* /*userData*/ )
{
	// This smart parser allows both a single number for traditional delay, and a labeled pair of numbers for a delay range
	WeaponTemplate* self = (WeaponTemplate*)instance;
	static const char *MIN_LABEL = "Min";
	static const char *MAX_LABEL = "Max";

	const char* token = ini->getNextTokenOrNull(ini->getSepsColon());

	if( stricmp(token, MIN_LABEL) == 0 )
	{
	// Two entry min/max
		*reinterpret_cast<Int *>(reinterpret_cast<char *>(self) + 0x4B0) = INI::scanInt(ini->getNextToken(ini->getSepsColon()));
		token = ini->getNextTokenOrNull(ini->getSepsColon());
		if( stricmp(token, MAX_LABEL) != 0 )
		{
			// Messed up double entry
			*reinterpret_cast<Int *>(reinterpret_cast<char *>(self) + 0x4B4) = *reinterpret_cast<Int *>(reinterpret_cast<char *>(self) + 0x4B0);
		}
		else
			*reinterpret_cast<Int *>(reinterpret_cast<char *>(self) + 0x4B4) = INI::scanInt(ini->getNextToken(ini->getSepsColon()));
	}
	else 
	{
		// single entry, as in no label so the first token is just a number
		*reinterpret_cast<Int *>(reinterpret_cast<char *>(self) + 0x4B0) = INI::scanInt(token);
		*reinterpret_cast<Int *>(reinterpret_cast<char *>(self) + 0x4B4) = *reinterpret_cast<Int *>(reinterpret_cast<char *>(self) + 0x4B0);
	}

	// No matter what we have now, we want to convert it to frames from msec. 
	// ShotDelay used to use parseDurationUnsignedInt, and we are expanding on that.
	*reinterpret_cast<Int *>(reinterpret_cast<char *>(self) + 0x4B0) = ceilf(Rva000B94B0Scale((Real)*reinterpret_cast<Int *>(reinterpret_cast<char *>(self) + 0x4B0)));
	*reinterpret_cast<Int *>(reinterpret_cast<char *>(self) + 0x4B4) = ceilf(Rva000B94B0Scale((Real)*reinterpret_cast<Int *>(reinterpret_cast<char *>(self) + 0x4B4)));

}

