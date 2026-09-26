// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Iinputs/reference/shims/ini /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Open-BFME7: INI field parser at 0x000BCE80 (225 B).  Zero Hour's
// parseScienceVector shape without the leading clear: each token is looked
// up in TheSpecialPowerStore (findSpecialPowerTemplate hands the name by
// value to the private finder) and the ID of its final override is pushed
// onto the vector the store argument points at.  The override walk is the
// header's recursive getFinalOverride inlined twice before the out-of-line
// call.  The parser name is address-derived.

#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "PreRTS.h"
#include "Common/INI.h"
#include "Common/SpecialPower.h"

class Rva000BCE80
{
public:
	static void parseSpecialPowerIDVector( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseSpecialPowerIDVector@Rva000BCE80@@SAXPAVINI@@PAX1PBX@Z
void Rva000BCE80::parseSpecialPowerIDVector( INI *ini, void *, void *store, const void * )
{
	std::vector<UnsignedInt> *ids = (std::vector<UnsignedInt> *)store;
	for( const char *token = ini->getNextTokenOrNull(); token != NULL; token = ini->getNextTokenOrNull() )
	{
		const SpecialPowerTemplate *spTemplate = TheSpecialPowerStore->findSpecialPowerTemplate( token );
		if( spTemplate )
			ids->push_back( spTemplate->getID() );
	}
}
