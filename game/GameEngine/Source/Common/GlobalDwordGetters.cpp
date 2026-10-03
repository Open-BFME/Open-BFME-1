// cl: /Igame/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
#include "dx8wrapper.h"

// 58 six-byte functions with one shape:
//
//     mov eax,[<address>] / ret
//
// WHAT THE BYTES SHOW.  A dword is read from a FIXED address -- not from `this`
// and not from any argument -- and returned.  `this` is never touched and
// nothing is popped, so the body says nothing about an enclosing class and is
// spelled as a free function; the `A1` short encoding only exists for eax, so
// the load is a whole dword and the result is the return value.
//
// Every address lands in .data, so each one names a mutable global.  57
// distinct globals are read by the 58 bodies (two bodies read the same one),
// and each global is declared once here and named for the address it sits at.
// The address slot itself is filled by the patcher from the target binary and
// the build checks that every reference to a given symbol resolves to one
// address, so a global shared by two bodies is checked to be one global.
//
// Most globals and functions retain address-derived names; AptGetSwfVersion
// is pinned in symbols.csv. The global at 0x012F4C64
// is the slot LookAtTranslator's constructor publishes itself into
// (game/GameEngine/Source/GameClient/MessageStream/LookAtTranslator_ctor.cpp), and
// that ctor is matched at retail, so the global is `TheLookAtTranslator` and is
// spelled as the reference header GameClient/LookAtXlat.h spells it.  Only the
// forward declaration is repeated here: this TU has no include path, and the
// pointed-to class is never dereferenced, so no layout is needed or claimed.

class LookAtTranslator;
extern LookAtTranslator *TheLookAtTranslator;

// 0x012ACC30 is not a free global: retail defines it as the static member
// Rva001A1A30::s_value (declared and defined in TinyGlobalStores.cpp), so the
// reference is spelled with its defining name to link.
class Rva001A1A30
{
public:
	static int s_value;
};

extern int g_Va012BA938;
extern int g_Va012D6DB0;
extern int g_Va012D6DB4;
extern int g_Va012D6DB8;
extern int g_Va012D7198;
extern int g_Va012ED614;
extern int g_Va012EF4D0;
extern int g_Va012F4964;
extern int g_Va012F496C;
extern int g_Va012F4988;
extern int g_Va012F4998;
extern int g_Va012F49B0;
extern int g_Va012F49B4;
extern void *g_rva012F49D0;
extern int g_Va012F49D4;
extern int g_Va012F49E4;
extern int g_Va012F49FC;
extern int g_Va012F4AAC;
extern int g_Va012F4ABC;
extern int g_Va012F4ACC;
extern int g_Va012F4AD4;
extern int g_Va012F4B40;
extern int g_Va012F4B44;
extern int g_Va012F4B54;
extern int g_Va012F4C38;

extern int g_Va012F9CF4;
extern int g_Va012F9D08;
extern int g_Va01304B5C;
extern int g_Va01304B60;
// Retail's hubsingle.cpp assertion names this cell; createServiceHubImpl.cpp
// owns its definition. Only the static pointer declaration is needed here.
class ServiceHubImpl
{
public:
	static ServiceHubImpl *gInstance;
};
extern int g_Va0130A5A0;
extern int g_Va0130B198;
extern int g_Va01336E80;
extern int g_Va01337824;
extern int g_Va0133F420;
extern int g_Va0133F460;
extern int g_Va013400CC;
extern int g_Va013400F8;
extern int g_Va0134052C;
extern int g_Va01340578;
extern int g_Va01341140;
extern int g_Va01346DFC;
extern int g_Va01346E00;
extern int g_Va01346E04;
extern int g_Va01346E08;
extern int g_Va01346E2C;
extern int g_Va01346E40;
extern int g_Va01346E48;
extern int g_Va01346E50;
extern int g_Va01346E5C;
extern int g_Va0134B20C;
extern int g_Va0134FBB0;
extern int g_Va0135280C;
extern int g_Va01352810;

int Rva00096A50Get( void )
{
	return g_Va012ED614;
}

int Rva001A19D0Get( void )
{
	return g_Va012EF4D0;
}

int Rva001A1A20Get( void )
{
	return Rva001A1A30::s_value;
}

int Rva001ADD20Get( void )
{
	return g_Va012EF4D0;
}

int Rva003828F0Get( void )
{
	return g_Va012F4998;
}

int Rva00382910Get( void )
{
	return g_Va012F4ACC;
}

int Rva003968E0Get( void )
{
	return g_Va012F4B40;
}

int Rva003968F0Get( void )
{
	return g_Va012F4AD4;
}

int Rva00396900Get( void )
{
	return g_Va012F4B54;
}

int Rva0043A5F0Get( void )
{
	return g_Va012F4C38;
}

int Rva0046ECB0Get( void )
{
	return reinterpret_cast<int>(TheLookAtTranslator);
}

int Rva0049CA60Get( void )
{
	return g_Va012F4988;
}

int Rva004C1090Get( void )
{
	return g_Va012F4964;
}

int Rva004E9B20Get( void )
{
	return g_Va012F4AAC;
}

int Rva004F0750Get( void )
{
	return g_Va012F49FC;
}

int Rva00510B40Get( void )
{
	return reinterpret_cast<int>(g_rva012F49D0);
}

int Rva00558420Get( void )
{
	return g_Va012F4ABC;
}

int Rva00569130Get( void )
{
	return g_Va012F4B44;
}

int Rva00569140Get( void )
{
	return g_Va012F49B0;
}

int Rva00570170Get( void )
{
	return g_Va012F49B4;
}

int Rva00588800Get( void )
{
	return g_Va012F49E4;
}

int Rva005F08E0Get( void )
{
	return reinterpret_cast<int>(DX8Wrapper::_Get_D3D_Device8());
}

int Rva00623790Get( void )
{
	return g_Va012F49D4;
}

int Rva0066CE50Get( void )
{
	return g_Va012F496C;
}

int Rva006C07C0Get( void )
{
	return g_Va01340578;
}

int Rva006E1920Get( void )
{
	return g_Va012BA938;
}

int Rva006E1A20Get( void )
{
	return g_Va0133F420;
}

int Rva007175A0Get( void )
{
	return g_Va012F9D08;
}

int Rva00751F30Get( void )
{
	return g_Va01304B60;
}

int Rva00751F40Get( void )
{
	return g_Va01304B5C;
}

int Rva00782E20Get( void )
{
	return g_Va012D7198;
}

int Rva0078AE20Get( void )
{
	return g_Va012D6DB4;
}

int Rva0078AE30Get( void )
{
	return g_Va012D6DB8;
}

int Rva007C5560Get( void )
{
	return g_Va012F9CF4;
}

int Rva007EB260Get( void )
{
	return reinterpret_cast<int>(ServiceHubImpl::gInstance);
}

struct Rva007EB810Diag;
Rva007EB810Diag *Rva007EB810Get( void )
{
	return reinterpret_cast<Rva007EB810Diag *>(g_Va0130A5A0);
}

int Rva0081C390Get( void )
{
	return g_Va0130B198;
}

int Rva0088CDE0Get( void )
{
	return g_Va01336E80;
}

unsigned int AptGetSwfVersion( void )
{
	return g_Va01337824;
}

int Rva008FD440Get( void )
{
	return g_Va0133F460;
}

int Rva00902130Get( void )
{
	return g_Va013400F8;
}

int Rva00902160Get( void )
{
	return g_Va012D6DB0;
}

int Rva00903060Get( void )
{
	return g_Va013400CC;
}

int Rva00903E70Get( void )
{
	return g_Va01341140;
}

int Rva00910F00Get( void )
{
	return g_Va0134052C;
}

int Rva00937160Get( void )
{
	return g_Va01346E08;
}

int Rva00937220Get( void )
{
	return g_Va01346E48;
}

int Rva00937230Get( void )
{
	return g_Va01346E5C;
}

int Rva00937250Get( void )
{
	return g_Va01346E00;
}

int Rva00937260Get( void )
{
	return g_Va01346E04;
}

int Rva00937270Get( void )
{
	return g_Va01346E2C;
}

int Rva009372B0Get( void )
{
	return g_Va01346DFC;
}

int Rva009372C0Get( void )
{
	return g_Va01346E50;
}

int Rva009372D0Get( void )
{
	return g_Va01346E40;
}

int Rva00956A80Get( void )
{
	return g_Va0134B20C;
}

int Rva009F8081Get( void )
{
	return g_Va0134FBB0;
}

int Rva00AFE950Get( void )
{
	return g_Va01352810;
}

int Rva00AFE960Get( void )
{
	return g_Va0135280C;
}

