// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/ini /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Open-BFME7: INI block parser at 0x000940F0 (172 B): reads a name token
// into an AsciiString then a Bool token then allocates a 12-byte definition
// (constructor 0x000947C0 which is bfmeInitBWA in the ledger: base init with
// the name then the flag copied twice and a zeroed count) and hands it with
// the INI and the name to the cdecl registration routine at 0x00094010.
// Names are address-derived; the definition class is opaque here.

#include "PreRTS.h"
#include "Common/INI.h"

class Rva000940F0Definition
{
public:
	Rva000940F0Definition( const AsciiString &name, Bool flag );

private:
	char m_unreconstructed[ 12 ];
};

void Rva00094010Register( INI *ini, const AsciiString &name, Rva000940F0Definition *definition );

class Rva000940F0
{
public:
	static void parseDefinition( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseDefinition@Rva000940F0@@SAXPAVINI@@PAX1PBX@Z
void Rva000940F0::parseDefinition( INI *ini, void *, void *, const void * )
{
	AsciiString name = ini->getNextToken();
	Bool flag = INI::scanBool( ini->getNextToken() );
	Rva000940F0Definition *definition = new Rva000940F0Definition( name, flag );
	Rva00094010Register( ini, name, definition );
}
