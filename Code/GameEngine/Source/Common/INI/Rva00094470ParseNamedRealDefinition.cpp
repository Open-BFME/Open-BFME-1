// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/ini /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Open-BFME7: INI block parser at 0x00094470 (233 B): sibling of the 172-byte
// name+Bool parser at 0x000940F0.  Reads a name token and a Real token then
// allocates a 16-byte definition (constructor 0x00094820 taking the name as a
// const AsciiString reference so the token converts through a temporary
// guarded by the new-expression null check: that is the bit-flag tail) and
// hands it with the INI and a second name temporary to the cdecl
// registration routine at 0x00094010 in the same statement (both temporaries
// die at the end of it: the allocation temporary last).  Names are
// address-derived.

#include "PreRTS.h"
#include "Common/INI.h"

class Rva00094470Definition
{
public:
	Rva00094470Definition( const AsciiString &name, Real value );

private:
	char m_unreconstructed[ 16 ];
};

void Rva00094010Register( INI *ini, const AsciiString &name, Rva00094470Definition *definition );

class Rva00094470
{
public:
	static void parseDefinition( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseDefinition@Rva00094470@@SAXPAVINI@@PAX1PBX@Z
void Rva00094470::parseDefinition( INI *ini, void *, void *, const void * )
{
	const char *name = ini->getNextToken();
	Real value = INI::scanReal( ini->getNextToken() );
	Rva00094010Register( ini, name, new Rva00094470Definition( name, value ) );
}
