// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Iinputs/reference/shims/ini /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// The body at 0x000941D0 reads an integer named definition.  The allocated
// record is the independently matched BfmeThingBWB shape; its initializer
// consumes the address of a temporary AsciiString and the scanned integer.

#include "PreRTS.h"
#include "Common/INI.h"

class Rva00094470Definition;

void Rva00094010Register( INI *ini, const AsciiString &name, Rva00094470Definition *definition );

// The target calls 0x000947F0 through its ILT thunk after allocating a
// 16-byte record.  Its matched body has the constructor-compatible thiscall
// ABI (AsciiString const &, int value) and returns this in EAX.  Keep the
// owner address-derived until a stronger identity witness appears.
class Rva000947F0Definition
{
public:
	Rva000947F0Definition( const AsciiString &name, int value );

	unsigned char m_unreconstructed[ 16 ];
};

class Rva000941D0
{
public:
	static void parseDefinition( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseDefinition@Rva000941D0@@SAXPAVINI@@PAX1PBX@Z
void Rva000941D0::parseDefinition( INI *ini, void *, void *, const void * )
{
	const char *name = ini->getNextToken();
	int value = INI::scanInt( ini->getNextToken() );
	Rva00094010Register( ini, AsciiString( name ),
		reinterpret_cast<Rva00094470Definition *>(
			new Rva000947F0Definition( name, value ) ) );
}
