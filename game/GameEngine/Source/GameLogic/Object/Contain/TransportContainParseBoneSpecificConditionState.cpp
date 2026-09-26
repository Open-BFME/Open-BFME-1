// BFME TransportContain parser for BoneSpecificConditionState.

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include "Common/AsciiString.h"
#include <map>

typedef unsigned int UnsignedInt;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken( int flags );
	const char *getNextTokenOrNull( const char *seps = 0 );
	static UnsignedInt scanUnsignedInt( const char *token );
};

class GenItem;

class Gen000140D8
{
public:
	bool handle( GenItem *item, bool *foundNormal, bool *foundAddOrSub );
};

extern "C" void *memset( void *, int, unsigned int );
#pragma intrinsic( memset )

class ModelConditionFlags
{
public:
	UnsignedInt m_bits[10];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TransportContain.h
class TransportContain
{
public:
	static void parseBoneSpecificConditionState(
		INI *ini, void *store, const void *userData);
};

void TransportContain::parseBoneSpecificConditionState(
	INI *ini, void *store, const void *)
{
	UnsignedInt state[11];
	state[0] = INI::scanUnsignedInt(ini->getNextToken(0));
	memset(state + 1, 0, sizeof(UnsignedInt) * 10);
	bool foundNormal = false;
	bool foundAddOrSub = false;
	const char *token = 0;

	while ((token = ini->getNextTokenOrNull(0)) != 0)
	{
		if (!reinterpret_cast<Gen000140D8 *>(state + 1)->handle(
			(GenItem *)token, &foundNormal, &foundAddOrSub))
			break;
	}

	ModelConditionFlags *result = &(*reinterpret_cast<
		std::map<UnsignedInt, ModelConditionFlags> *>(
			reinterpret_cast<char *>(store) + 0x120))[state[0]];
	*result = *reinterpret_cast<ModelConditionFlags *>(state + 1);
}
