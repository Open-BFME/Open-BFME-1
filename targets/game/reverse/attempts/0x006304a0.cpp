// ?StartPatchCheck@@YAX_N@Z
// partial score=0.9404 date=2026-10-07
// cl: /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// LEVER: TU-local `static` globals (as in ZH MainMenuUtils.cpp) move retail's
// first difference from +0x2D to +0x3B; extern or defined-extern globals do not.
// Shipping needs StartPatchCheck in the TU that owns these statics.
#include "ascii_string.h"
#include "unicode_string.h"

typedef void (*GameWinMsgBoxFunc)();
class GameWindow;

class GameTextInterface
{
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0c(); virtual void slot10(); virtual void slot14();
    virtual void slot18(); virtual void slot1c(); virtual void slot20();
    virtual void slot24();
    virtual UnicodeString fetch(const char *label, bool *exists = 0);
};

static unsigned char checkingForPatchBeforeGameSpy;
static unsigned char onlineCancelFlag;
static unsigned char cantConnectBeforeOnline;
static unsigned char showOnlineShellFlag;
static bool s_asyncDNSLookupInProgress;
static int timeThroughOnline;
static int checksLeftBeforeOnline;
extern GameTextInterface *TheGameText;
extern const unsigned short g_Rva01088AF4EmptyWideString[];

extern int asyncGethostbyname(char *name);
void bfmeReallyStartPatchCheck();
void Rva0062EA60StartOnline();
void bfmeGoBHG();
GameWindow *MessageBoxOk(UnicodeString title, UnicodeString body, GameWinMsgBoxFunc ok);

void StartPatchCheck(bool checkingBeforeOnline)
{
    showOnlineShellFlag = checkingBeforeOnline;
    onlineCancelFlag = 1;
    timeThroughOnline++;
    checkingForPatchBeforeGameSpy = 1;
    cantConnectBeforeOnline = 0;
    checksLeftBeforeOnline = 0;

    MessageBoxOk(UnicodeString(g_Rva01088AF4EmptyWideString),
        TheGameText->fetch("GUI:CheckingForPatches"), bfmeGoBHG);
    s_asyncDNSLookupInProgress = true;
    switch (asyncGethostbyname("servserv.generals.ea.com"))
    {
    case 1:
        cantConnectBeforeOnline = 1;
        Rva0062EA60StartOnline();
        break;
    case 2:
        bfmeReallyStartPatchCheck();
        break;
    }
}
