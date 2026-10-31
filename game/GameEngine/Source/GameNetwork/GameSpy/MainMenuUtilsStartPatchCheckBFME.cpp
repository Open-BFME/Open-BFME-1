// cl: /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /Iinputs/reference/shims/stringinline
// stlport
//
// BFME StartPatchCheck( Bool checkingBeforeOnline ), retail 0x006304A0.
// Zero Hour's MainMenuUtils.cpp version takes no argument; BFME stores the
// argument first and shows a plain OK message box while DNS resolves.
//
// Retail schedules the stores of four MainMenuUtils flags after the fetch
// call's vtable load, which VC7.1 does only for data it knows nothing else
// can alias: they were file statics of the retail MainMenuUtils TU, so they
// are spelled static here. The patch-check layout flag is the shared
// volatile byte its callbacks clear (0x012F7178), whose store stays ahead of
// that load.

#include "StringInline.h"

typedef void (*GameWinMsgBoxFunc)();
class GameWindow;

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0c(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1c(); virtual void slot20();
	virtual void slot24();
	virtual UnicodeString fetch( const char *label, bool *exists = 0 );
};

static unsigned char checkingForPatchBeforeGameSpy;
static bool cantConnectBeforeOnline;
static unsigned char showOnlineShellFlag;
static int checksLeftBeforeOnline;
extern volatile unsigned char g_rva012F7178PatchCheckLayoutActive;
// Shared one-byte owner in MainMenuUtils.cpp (VA 0x012F717A, data_rows.csv).
extern unsigned char s_asyncDNSLookupInProgress;
extern int timeThroughOnline;
extern GameTextInterface *TheGameText;
extern const unsigned short g_Rva01088AF4EmptyWideString[];

int asyncGethostbyname( char *name );
void bfmeReallyStartPatchCheck();
void Rva0062EA60StartOnline();
void bfmeGoBHG();
GameWindow *MessageBoxOk( UnicodeString title, UnicodeString body, GameWinMsgBoxFunc ok );

void StartPatchCheck( bool checkingBeforeOnline )
{
	showOnlineShellFlag = checkingBeforeOnline;
	timeThroughOnline++;
	g_rva012F7178PatchCheckLayoutActive = 1;
	checkingForPatchBeforeGameSpy = 1;
	cantConnectBeforeOnline = false;
	checksLeftBeforeOnline = 0;

	MessageBoxOk( UnicodeString( g_Rva01088AF4EmptyWideString ),
		TheGameText->fetch( "GUI:CheckingForPatches" ), bfmeGoBHG );
	s_asyncDNSLookupInProgress = true;
	switch ( asyncGethostbyname( "servserv.generals.ea.com" ) )
	{
	case 1:
		cantConnectBeforeOnline = true;
		Rva0062EA60StartOnline();
		break;
	case 2:
		bfmeReallyStartPatchCheck();
		break;
	}
}
