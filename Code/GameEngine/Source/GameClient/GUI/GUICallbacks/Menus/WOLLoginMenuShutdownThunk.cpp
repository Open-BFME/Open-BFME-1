// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /ICode/Libraries/Source/WWVegas/WWLib

#include "Common/AsciiString.h"

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WindowLayout.h
class WindowLayout
{
public:
    virtual void unused00();
    virtual void unused01();
    virtual void unused02();
    virtual void unused03();
    virtual void hide(Bool hide);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
    virtual void unused00(); virtual void unused01(); virtual void unused02();
    virtual void unused03(); virtual void unused04(); virtual void unused05();
    virtual void unused06(); virtual void unused07(); virtual void unused08();
    virtual void unused09(); virtual void unused10(); virtual void unused11();
    virtual void unused12(); virtual void unused13(); virtual void unused14();
    virtual void unused15(); virtual void unused16(); virtual void unused17();
    virtual void unused18(); virtual void unused19(); virtual void unused20();
    virtual void unused21(); virtual void unused22(); virtual void unused23();
    virtual void unused24(); virtual void unused25(); virtual void unused26();
    virtual void unused27(); virtual void unused28(); virtual void unused29();
    virtual void unused30(); virtual void unused31(); virtual void unused32();
    virtual void unused33(); virtual void unused34(); virtual void unused35();
    virtual void unused36(); virtual void unused37(); virtual void unused38();
    virtual void unused39();
    virtual void clearTabList();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shell.h
class Shell
{
public:
    void shutdownComplete(WindowLayout *layout, Bool impendingPush);
    // Retail pushes FALSE for the second argument before constructing the
    // AsciiString temp (0x004FFA9C: `push ebx` with ebx == 0), and the pinned
    // callee is ?push@Shell@@QAEXVAsciiString@@_N@Z at 0x00580080 -- a
    // by-value AsciiString plus a defaulted Bool, not a char *.
    void push(AsciiString screen, Bool shelldown = false);
    void reverseAnimatewindow();
};

// write() is reached through vtable slot 0x0c and the delete through the
// scalar-deleting destructor at slot 0x00 (0x004FFA7D: `mov edx,[ecx]` /
// `call [edx+0xc]`; 0x004FFA8C: `push 1` / `call [eax]`), so this is a
// polymorphic preferences object, not the plain struct spelled here before.
class GameSpyLoginPreferences
{
public:
    virtual ~GameSpyLoginPreferences();
    virtual void unused04();
    virtual void unused08();
    virtual void write();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h
class GameWindowTransitionsHandler
{
public:
    void reverse(AsciiString groupName);
};

extern GameWindowManager *TheWindowManager;
extern Shell *TheShell;
extern GameWindowTransitionsHandler *TheTransitionHandler;

static Bool isShuttingDown;
static Bool loggedInOK;
static GameSpyLoginPreferences *loginPref;
// COFF names file-scope statics alike; this must not alias WOLWelcomeMenu's state.
static char *loginNextScreen;

// Retail spells this `static void shutdownComplete(WindowLayout *)`, but that
// name is file-scoped and ~30 menu TUs each define their own. symbols.csv is a
// flat name->address map with no room for two meanings of one key, so the
// resolver would pick whichever copy happened to reproduce a displacement
// first. Spelled per-TU here so the pin is unambiguous; retail symbol is
// ?shutdownComplete@@YAXPAVWindowLayout@@@Z in WOLLoginMenu.cpp @0x004FFA40.
static __declspec(noinline) void shutdownCompleteWOLLoginMenu(WindowLayout *layout)
{
    isShuttingDown = false;
    layout->hide(true);
    TheShell->shutdownComplete(layout, loginNextScreen != 0);

    if (loginNextScreen != 0)
    {
        if (loginPref != 0)
        {
            loginPref->write();
            delete loginPref;
            loginPref = 0;
        }
        TheShell->push(loginNextScreen);
    }
    else if (loginPref != 0)
    {
        loginPref->write();
        delete loginPref;
        loginPref = 0;
    }

    loginNextScreen = 0;
}

// ?WOLLoginMenuShutdown@@YAXPAVWindowLayout@@PAX@Z
void WOLLoginMenuShutdown(WindowLayout *layout, void *userData)
{
    isShuttingDown = true;
    loggedInOK = false;
    TheWindowManager->clearTabList();

    Bool popImmediate = *(Bool *)userData;
    if (popImmediate)
    {
        shutdownCompleteWOLLoginMenu(layout);
        return;
    }

    TheShell->reverseAnimatewindow();
    TheTransitionHandler->reverse("GameSpyLoginProfileFade");
}
