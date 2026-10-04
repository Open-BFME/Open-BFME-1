// cl: /DNDEBUG /DWIN32 /D_WINDOWS /DIN_ADDR=in_addr /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// Open-BFME7: byte-twin of ?GSMessageBoxYesNo@@YAXVUnicodeString@@0P6AXXZ1@Z
// (game/GameEngine/Source/GameNetwork/GameSpyOverlay.cpp, retail 0x00627E90).
// Retail 0x00627D80, 217B: GSMessageBoxOkCancel. GameSpyOverlay.cpp already
// has a readable reconstruction of this function (unmatched, no functions.csv
// row), but its field-write order is off by one swap: retail stores
// cancelFunc, THEN g_Va012F70A4=TRUE, THEN okFunc=newOkFunc; the
// existing source stores okFunc/cancelFunc before g_Va012F70A4; the
// compiler schedules the two pointer stores around the flag store, so the flag
// store must come FIRST in source for retail's cancel-flag-ok order. The
// shared globals are defined in GameSpyOverlay.cpp.
#define Matrix4x4 Matrix4  // BFME renamed it
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameClient/MessageBox.h"

template <typename T> class StringBase
{
private:
	StringBase( const StringBase<T> &other );
	friend class UnicodeString;
};

inline UnicodeString::UnicodeString( const UnicodeString &other )
{
	((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(
		*(const StringBase<wchar_t> *)&other);
}

void b_00042a50( void );

extern GameWinMsgBoxFunc okFunc;
extern GameWinMsgBoxFunc cancelFunc;
extern volatile Bool g_Va012F70A4;

static void messageBoxOK( void )
{
	if (okFunc)
	{
		okFunc();
		okFunc = NULL;
	}
}

static void messageBoxCancel( void )
{
	if (cancelFunc)
	{
		cancelFunc();
		cancelFunc = NULL;
	}
}

// ?GSMessageBoxOkCancel@@YAXVUnicodeString@@0P6AXXZ1@Z
void GSMessageBoxOkCancel(UnicodeString title, UnicodeString message, GameWinMsgBoxFunc newOkFunc, GameWinMsgBoxFunc newCancelFunc)
{
	if (g_Va012F70A4)
	{
		b_00042a50();
		g_Va012F70A4 = FALSE;
	}
	if (okFunc)
		okFunc = NULL;
	if (cancelFunc)
		cancelFunc = NULL;
	MessageBoxOkCancel(title, message, messageBoxOK, messageBoxCancel);
	g_Va012F70A4 = TRUE;
	okFunc = newOkFunc;
	cancelFunc = newCancelFunc;
}
