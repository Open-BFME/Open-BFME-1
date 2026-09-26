// cl: /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include <list>
#include "ascii_string.h"
#include "unicode_string.h"

class GameWindow;
typedef void (*GameWinMsgBoxFunc)();

class GameTextInterface
{
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0c(); virtual void slot10(); virtual void slot14();
    virtual void slot18(); virtual void slot1c(); virtual void slot20();
    virtual void slot24();
    virtual UnicodeString fetch(const char *label, bool *exists = 0);
};

class ScriptEngine
{
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
    virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
    virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
    virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3c();
    virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4c();
    virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5c();
    virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6c();
    virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7c();
    virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8c();
    virtual void slot90(); virtual void slot94(); virtual void slot98(); virtual void slot9c();
    virtual void signalUIInteract(const AsciiString &name);
};

class WindowManager { public: void bfme_hideBackground(bool hide); };
class Rva0051D690 { public: void apply(); };
class Shell { public: void push(AsciiString filename, bool shutdownImmediate = false); };

class QueuedDownload
{
public:
    AsciiString server, userName, password, file, localFile, regKey;
    unsigned char tryResume;
};

extern unsigned char checkingForPatchBeforeGameSpy;
extern unsigned char onlineCancelFlag;
extern unsigned char cantConnectBeforeOnline;
extern unsigned char mustDownloadPatch;
extern unsigned char showOnlineShellFlag;
extern std::list<QueuedDownload> queuedDownloads;
extern WindowManager *TheWindowManager;
extern Rva0051D690 *g_rva012F49B4;
extern GameTextInterface *TheGameText;
extern ScriptEngine *TheScriptEngine;
extern Shell *TheShell;
extern char *MOTDBuffer;
extern char *configBuffer;
extern const char *bfmeOnlineHookName;

void j_00042a50();
void j_00048a2c();
void SetUpGameSpy(const char *, const char *);
bool hasWriteAccess();
GameWindow *MessageBoxOk(UnicodeString title, UnicodeString body, GameWinMsgBoxFunc ok);
GameWindow *MessageBoxOkCancel(UnicodeString title, UnicodeString body, GameWinMsgBoxFunc ok, GameWinMsgBoxFunc cancel);
GameWindow *MessageBoxYesNo(UnicodeString title, UnicodeString body, GameWinMsgBoxFunc yes, GameWinMsgBoxFunc no);
void noPatchBeforeOnlineCallback();
void patchBeforeOnlineCallback();

void Rva0062EA60StartOnline()
{
    unsigned char hadCancel = onlineCancelFlag;
    checkingForPatchBeforeGameSpy = 0;
    if (hadCancel)
    {
        j_00042a50();
        onlineCancelFlag = 0;
    }

    if (cantConnectBeforeOnline || queuedDownloads.size())
    {
        if (TheWindowManager)
            TheWindowManager->bfme_hideBackground(false);
        if (g_rva012F49B4)
            g_rva012F49B4->apply();
        if (cantConnectBeforeOnline)
        {
            MessageBoxOk(TheGameText->fetch("GUI:CannotConnectToServservTitle"),
                TheGameText->fetch("GUI:CannotConnectToServserv"), noPatchBeforeOnlineCallback);
            return;
        }
    }

    if (queuedDownloads.size())
    {
        if (!hasWriteAccess())
            MessageBoxOk(TheGameText->fetch("GUI:Error"),
                TheGameText->fetch("GUI:MustHaveAdminRights"), noPatchBeforeOnlineCallback);
        else if (mustDownloadPatch)
            MessageBoxOkCancel(TheGameText->fetch("GUI:PatchAvailable"),
                TheGameText->fetch("GUI:MustPatchForOnline"), patchBeforeOnlineCallback,
                noPatchBeforeOnlineCallback);
        else
            MessageBoxYesNo(TheGameText->fetch("GUI:PatchAvailable"),
                TheGameText->fetch("GUI:CanPatchForOnline"), patchBeforeOnlineCallback,
                noPatchBeforeOnlineCallback);
        return;
    }

    {
        AsciiString hook(bfmeOnlineHookName);
        TheScriptEngine->signalUIInteract(hook);
    }
    SetUpGameSpy(MOTDBuffer, configBuffer);
    if (MOTDBuffer) { delete[] MOTDBuffer; MOTDBuffer = 0; }
    if (configBuffer) { delete[] configBuffer; configBuffer = 0; }
    if (showOnlineShellFlag)
        j_00048a2c();
    else
        TheShell->push(AsciiString("Menus/GameSpyLoginProfile.wnd"), false);
}
