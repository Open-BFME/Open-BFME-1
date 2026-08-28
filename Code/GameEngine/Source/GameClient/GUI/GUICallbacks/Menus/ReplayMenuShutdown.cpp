// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /ICode/Libraries/Source/WWVegas/WWLib

// ReplayMenu.cpp is where this callback belongs, and its ZH body is already
// there. It cannot be landed from that TU: the retail by-value AsciiString temp
// needs the StringBase-backed string class, and swapping ReplayMenu.cpp onto it
// renumbers every $L unwind label in the object, which breaks three landed
// gen-funclet rows (the labels shift and two of them tie three ways, so the gate
// can no longer name a body). Spelled here so ReplayMenu.cpp keeps its rows.

#include "Common/AsciiString.h"

typedef bool Bool;

class WindowLayout;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shell.h
class Shell
{
public:
    void shutdownComplete(WindowLayout *layout, Bool impendingPush);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h
class GameWindowTransitionsHandler
{
public:
    void reverse(AsciiString groupName);
};

// BFME opens this callback with a RecorderClass entry point ZH does not have.
// The global it is called on is TheRecorder (the same address carries
// RecorderClass::getMode at 0x0006BCCA), and the body at 0x00097360 copies two
// file statics back into TheWritableGlobalData. It has no other call site in the
// image, so the call shape is all of it that can be recovered.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Recorder.h
class RecorderClass
{
public:
    void restoreGlobalDataFields();
};

extern Shell *TheShell;
extern GameWindowTransitionsHandler *TheTransitionHandler;
extern RecorderClass *TheRecorder;

static Bool isShuttingDown;

// ?ReplayMenuShutdown@@YAXPAVWindowLayout@@PAX@Z
void ReplayMenuShutdown(WindowLayout *layout, void *userData)
{
    TheRecorder->restoreGlobalDataFields();

    Bool popImmediate = *(Bool *)userData;
    if (popImmediate)
    {
        // ZH hides the layout first here; BFME dropped that call.
        TheShell->shutdownComplete(layout, false);
        return;
    }

    TheTransitionHandler->reverse("ReplayMenuFade");
    isShuttingDown = true;
}
