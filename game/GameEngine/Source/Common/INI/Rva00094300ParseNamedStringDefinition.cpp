// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Iinputs/reference/shims/ini /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Open-BFME7: INI block parser at 0x00094300 (286 B). It reads two
// name-value tokens, constructs the 16-byte BfmeRecVVJ record, and registers
// the record through the shared 0x00023344 registration thunk.

#include "PreRTS.h"
#include "Common/INI.h"

class BfmeStrVVJ
{
};

class BfmeRecVVJ
{
public:
	BfmeRecVVJ( const BfmeStrVVJ &first, const BfmeStrVVJ &second );

private:
	char m_unreconstructed[ 16 ];
};

class Rva00094470Definition;

void Rva00094010Register( INI *ini, const AsciiString &name, Rva00094470Definition *definition );

class Rva00094300
{
public:
	static void parseDefinition( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseDefinition@Rva00094300@@SAXPAVINI@@PAX1PBX@Z
void Rva00094300::parseDefinition( INI *ini, void *, void *, const void * )
{
	const char *name = ini->getNextToken();
	volatile const char *value = ini->getNextToken();
	Rva00094010Register( ini, AsciiString( name ), reinterpret_cast<Rva00094470Definition *>( new BfmeRecVVJ(
		reinterpret_cast<const BfmeStrVVJ &>( AsciiString( name ) ),
		reinterpret_cast<const BfmeStrVVJ &>( AsciiString( const_cast<const char *>( value ) ) ) ) ) );
}
