// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

// The 0x00507E10 WOLQuickMatchMenu shutdown callback calls the 0x00048E73
// incremental-link thunk with its WindowLayout receiver in ecx. The thunk
// reaches this 0x005057C0 body, which completes the shutdown and pushes the
// pending screen name when one exists.

#include "Common/AsciiString.h"

#include "../../../../Include/Common/ScalarTypes.h"

class WindowLayout
{
public:
    virtual void slot0(void);
    virtual void slot1(void);
    virtual void slot2(void);
    virtual void slot3(void);
    virtual void slot4(bool);
    void shutdownComplete(void);
};

class Shell
{
public:
    void shutdownComplete(WindowLayout *layout, Bool hasPending);
    void push(AsciiString filename, Bool shutdownImmediate);
};

extern Shell *TheShell;
// Retail VA 0x012F4804: the pending next-screen name cell (4 zero bytes).
const char *g_Va012F4804 = 0;

static Bool isShuttingDown = false;

void WindowLayout::shutdownComplete(void)
{
    isShuttingDown = false;
    slot4(true);
    TheShell->shutdownComplete(
        this, g_Va012F4804 != 0);
    if (g_Va012F4804 != 0)
        TheShell->push(
            AsciiString(g_Va012F4804), false);
    g_Va012F4804 = 0;
}
