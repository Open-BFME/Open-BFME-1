// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x00546170, 289 bytes. Free function in the OnlineHome dump file:
// GetLocalTime then write APT:CurrentDate / APT:CurrentTime through
// WindowManager::bfme_setAptText. Date/time formatters are the ZH
// getUnicodeDateBuffer / getUnicodeTimeBuffer ILTs.

#include "../../../../../reference/shims/stringinline/StringInline.h"

struct _SYSTEMTIME
{
	unsigned short wYear;
	unsigned short wMonth;
	unsigned short wDayOfWeek;
	unsigned short wDay;
	unsigned short wHour;
	unsigned short wMinute;
	unsigned short wSecond;
	unsigned short wMilliseconds;
};

typedef struct _SYSTEMTIME SYSTEMTIME;

extern "C" __declspec(dllimport) void __stdcall GetLocalTime( SYSTEMTIME *now );

UnicodeString getUnicodeDateBuffer( SYSTEMTIME timeVal );
UnicodeString getUnicodeTimeBuffer( SYSTEMTIME timeVal );

class WindowManager
{
public:
	void bfme_setAptText( const AsciiString &name, const UnicodeString &text );
};

extern WindowManager *g_theWindowManager;

void updateAptCurrentDateAndTime()
{
	SYSTEMTIME now;
	GetLocalTime( &now );
	{
		AsciiString name( "APT:CurrentDate" );
		g_theWindowManager->bfme_setAptText( name, getUnicodeDateBuffer( now ) );
	}
	{
		AsciiString name( "APT:CurrentTime" );
		g_theWindowManager->bfme_setAptText( name, getUnicodeTimeBuffer( now ) );
	}
}
