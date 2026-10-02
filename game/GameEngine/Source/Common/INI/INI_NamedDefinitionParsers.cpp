// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Iinputs/reference/shims/ini /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// The two name-plus-scalar block parsers, 0x000940F0 (172 B) and 0x00094470
// (233 B). Each reads a name token and one scalar, allocates a small
// definition, and hands it with the INI and the name to the same cdecl
// registration routine at 0x00094010.
//
// They differ in the scalar and the size that follows from it: a Bool into a
// 12-byte definition, or a Real into a 16-byte one. Written apart, that the
// pair share a registration routine at all was not visible from either file.
//
// Both parsers call ILT 0x00023344 -> RVA 0x00094010. Use the single
// declaration owned by Rva00094010Register.cpp; the routine passes the
// definition pointer through without accessing its scalar-specific layout.

#include "PreRTS.h"
#include "Common/INI.h"

class Rva000940F0Definition
{
public:
	Rva000940F0Definition( const AsciiString &name, Bool flag );

private:
	char m_unreconstructed[ 12 ];
};

class Rva00094470Definition
{
public:
	Rva00094470Definition( const AsciiString &name, Real value );

private:
	char m_unreconstructed[ 16 ];
};

void Rva00094010Register( INI *ini, const AsciiString &name, Rva000940F0Definition *definition );

class Rva000940F0
{
public:
	static void parseDefinition( INI *ini, void *instance, void *store, const void *userData );
};

class Rva00094470
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

// ?parseDefinition@Rva00094470@@SAXPAVINI@@PAX1PBX@Z
void Rva00094470::parseDefinition( INI *ini, void *, void *, const void * )
{
	const char *name = ini->getNextToken();
	Real value = INI::scanReal( ini->getNextToken() );
	Rva00094010Register( ini, name, reinterpret_cast<Rva000940F0Definition *>(
		new Rva00094470Definition( name, value ) ) );
}
