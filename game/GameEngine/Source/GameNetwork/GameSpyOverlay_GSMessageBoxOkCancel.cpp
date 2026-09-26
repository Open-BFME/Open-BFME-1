// cl: /DNDEBUG /DWIN32 /D_WINDOWS /DIN_ADDR=in_addr /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// Open-BFME7: byte-twin of ?GSMessageBoxYesNo@@YAXVUnicodeString@@0P6AXXZ1@Z
// (game/GameEngine/Source/GameNetwork/GameSpyOverlay.cpp, retail 0x00627E90).
// Retail 0x00627D80, 217B: GSMessageBoxOkCancel. GameSpyOverlay.cpp already
// has a readable reconstruction of this function (unmatched, no functions.csv
// row), but its field-write order is off by one swap: retail stores
// cancelFunc, THEN reOpenPlayerInfoFlag=TRUE, THEN okFunc=newOkFunc; the
// existing source stores okFunc/cancelFunc before reOpenPlayerInfoFlag; the
// compiler schedules the two pointer stores around the flag store, so the flag
// store must come FIRST in source for retail's cancel-flag-ok order. Per
// file policy the tracked file is left untouched and the fix lives here.
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

static GameWinMsgBoxFunc okFunc = NULL;
static GameWinMsgBoxFunc cancelFunc = NULL;
static volatile Bool reOpenPlayerInfoFlag = FALSE;

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
void GSMessageBoxOkCancel(UnicodeString title, UnicodeString message, GameWinMsgBoxFunc newCancelFunc, GameWinMsgBoxFunc newOkFunc)
{
	if (reOpenPlayerInfoFlag)
	{
		b_00042a50();
		reOpenPlayerInfoFlag = FALSE;
	}
	if (okFunc)
		okFunc = NULL;
	if (cancelFunc)
		cancelFunc = NULL;
	MessageBoxOkCancel(title, message, messageBoxOK, messageBoxCancel);
	reOpenPlayerInfoFlag = TRUE;
	cancelFunc = newCancelFunc;
	okFunc = newOkFunc;
}
