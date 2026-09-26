// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// The HouseColor block -- BFME-only, next door to WeatherData.cpp and reached
// the same way.
//
// The system is named, not guessed: GameEngine::init pushes the literal
// "TheHouseColorSystem" at 0x0007A148 immediately before pushing 0x012F0FEC,
// and the registrar it calls is the already-landed
// ??$initSubsystem@VHouseColorSystem@@@@..., so the class is HouseColorSystem.
//
// What the parser does with it is all that is recoverable here: parse over the
// system itself, then hand two of its AsciiStrings - the ones at +8 and +0xC,
// with str() inlined against the eight-byte StringBase header - to a two
// argument __cdecl function at 0x00900D70 that nothing in the image names. The
// members and that callee are named for what this one call site proves.
//
#include "PreRTS.h"
#include "Common/INI.h"

class HouseColorSystem
{
public:
	char m_pad[ 0x08 ];
	char *m_stringAt8;			// AsciiString
	char *m_stringAtC;			// AsciiString

	static const FieldParse m_fieldParseTable[];
};

extern HouseColorSystem *TheHouseColorSystem;		// 0x012F0FEC

// AsciiString::str() inlined: the characters sit past the eight-byte StringBase
// header, and an empty string reads as the shared "".
static const char *bfmeStr( const char *text )
{
	return text ? text + 8 : "";
}

void bfmeRegisterHouseColor( const char *first, const char *second );

// ?parseHouseColor@@YAXPAVINI@@@Z
void parseHouseColor( INI *ini )
{
	if( !TheHouseColorSystem )
		return;

	ini->initFromINI( TheHouseColorSystem, HouseColorSystem::m_fieldParseTable );

	bfmeRegisterHouseColor( bfmeStr( TheHouseColorSystem->m_stringAtC ),
													bfmeStr( TheHouseColorSystem->m_stringAt8 ) );
}
