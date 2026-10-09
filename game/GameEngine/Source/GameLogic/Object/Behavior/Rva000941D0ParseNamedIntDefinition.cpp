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

// Matched ledger row ?bfmeInitBWB@BfmeThingBWB@@QAEPAV1@PAXH@Z: the body at
// 0x000947F0, reached through ILT 0x0003D30C.  Same thiscall shape as the
// constructor above (record address, integer value) returning the record.
// Layout mirrors the owning TU (16-byte record: head, type tag, two values).
class BfmeThingBWB
{
public:
	BfmeThingBWB *bfmeInitBWB( void *what, int value );

	unsigned char m_bfmeHead[ 4 ];
	int m_bfmeNum;
	int m_bfmeA;
	int m_bfmeB;
};

class Rva000940F0Definition;

void Rva00094010Register( INI *ini, const AsciiString &name, Rva000940F0Definition *definition );

class Rva000941D0
{
public:
	static void parseDefinition( INI *ini, void *instance, void *store, const void *userData );
};

// ??0Rva000947F0Definition@@QAE@ABVAsciiString@@H@Z
// The new-expression in parseDefinition below calls through here.  This is
// the same 16-byte record initialization the matched 0x000947F0 body performs
// (StringBase copy at +0, type tag 1 at +4, integer at +8/+12, record in EAX),
// so the link binds a retail-identical copy.  Noinline keeps the constructor
// call out of line so the caller keeps retail's new-expression shape
// (including the EAX reload).
__declspec( noinline ) Rva000947F0Definition::Rva000947F0Definition( const AsciiString &name, int value )
{
	( (AsciiString *)this )->AsciiString::AsciiString( name );
	( (BfmeThingBWB *)this )->m_bfmeA = value;
	( (BfmeThingBWB *)this )->m_bfmeB = value;
	( (BfmeThingBWB *)this )->m_bfmeNum = 1;
}

// ?parseDefinition@Rva000941D0@@SAXPAVINI@@PAX1PBX@Z
void Rva000941D0::parseDefinition( INI *ini, void *, void *, const void * )
{
	const char *name = ini->getNextToken();
	int value = INI::scanInt( ini->getNextToken() );
	Rva00094010Register( ini, AsciiString( name ),
		reinterpret_cast<Rva000940F0Definition *>(
			new Rva000947F0Definition( name, value ) ) );
}
