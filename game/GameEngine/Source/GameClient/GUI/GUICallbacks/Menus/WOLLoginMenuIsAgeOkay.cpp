// ?isAgeOkay@@YA_NAAVAsciiString@@0V1@@Z at retail 0x004FFB80.
// The local view preserves BFME's witnessed string layout and ABI.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#include <windows.h>
#include <stdlib.h>

// The empty AsciiString fallback, retail 0x0107388B
// (targets/game/reverse/symbols.csv: ?g_bfmeEmptyAscii@@3QBDB).
extern const char g_bfmeEmptyAscii[];

typedef bool Bool;
typedef int Int;

#include "../../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

template<> inline bool StringBase<char>::isEmpty() const
{
    return m_data == 0 || m_data->length == 0;
}

static Bool isAgeOkay(AsciiString &month, AsciiString &day, AsciiString year)
{
	if(month.StringBase<char>::isEmpty() || day.StringBase<char>::isEmpty() || year.StringBase<char>::isEmpty() || year.StringBase<char>::getLength() != 4)
		return FALSE;

	Int monthInt = atoi(month.str());
	Int dayInt = atoi(day.str());

	if(monthInt > 12 || dayInt > 31)
		return FALSE;
		// setup date buffer for local region date format
	month.format("%02.2d",monthInt);
	day.format("%02.2d",dayInt);

	// test the year first
	#define DATE_BUFFER_SIZE 256
	char dateBuffer[ DATE_BUFFER_SIZE ];
	GetDateFormat( LOCALE_SYSTEM_DEFAULT,
														 0, NULL,
														 "yyyy",
														 dateBuffer, DATE_BUFFER_SIZE );
	Int sysVal = atoi(dateBuffer);
	Int userVal = atoi(year.str());
	if(sysVal - userVal >= 14)
		return TRUE;
	else if( sysVal - userVal <= 12)
		return FALSE;

	GetDateFormat( LOCALE_SYSTEM_DEFAULT,
														 0, NULL,
														 "MM",
														 dateBuffer, DATE_BUFFER_SIZE );
	sysVal = atoi(dateBuffer);
	userVal = atoi(month.str());
	if(sysVal - userVal >0 )
		return TRUE;
	else if( sysVal -userVal < 0 )
		return FALSE;
	// month.format("%02.2d",userVal);
	GetDateFormat( LOCALE_SYSTEM_DEFAULT,
														 0, NULL,
														 "dd",
														 dateBuffer, DATE_BUFFER_SIZE );
	sysVal = atoi(dateBuffer);
	userVal = atoi(day.str());
	if(sysVal - userVal< 0)
		return FALSE;
	// day.format("%02.2d",userVal);
	return TRUE;
}

extern "C" __declspec(noinline) Bool Rva004FFB80IsAgeOkayEmitter(AsciiString &month, AsciiString &day, AsciiString year)
{
	return isAgeOkay(month, day, year);
}
