// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/campaignmanagerascii /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ?freeStaticStrings@GameWindowManager@@UAEXXZ: Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp

// FILE: GameWindowManager_freeStaticStrings.cpp //////////////////////////////
//
// GameWindowManager::freeStaticStrings, retail 0x00485930. BFME-only; Zero
// Hour's GameWindowManager.cpp calls no such thing, though BFME's destructor
// does, one line before it deletes TheTransitionHandler.
//
// The body is four AsciiString releases and nothing else. The four strings are
// adjacent at 0x012F2570, 0x012F2574, 0x012F2578 and 0x012F257C, and the rest
// of the compiland uses them as scratch builders - each is filled through
// StringBase<char>::set(const char *, int) and then read back with str()
// inlined, at 0x004867E3, 0x00486944, 0x004869F4 and 0x00486AA4 among others.
// Nothing in the image names them, so they are reached as one array; that is a
// claim about their adjacency, which the four immediates prove, and not about
// what BFME calls them.
//
// The last release is a tail jump, which is what MSVC does with the final call
// of a void member at /O2 - not a fifth string handled differently.
//
// Kept out of GameWindowManager.cpp because that file compiles against the
// vendored AsciiString, and this body needs the StringBase-backed one whose
// destructor resolves to 0x00887940.
//
///////////////////////////////////////////////////////////////////////////////

#include <stddef.h>

#include "Common/AsciiString.h"

extern AsciiString TheGameWindowManagerScratchStrings[ 4 ];		// 0x012F2570

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
	virtual void freeStaticStrings();
};

// ?freeStaticStrings@GameWindowManager@@UAEXXZ
void GameWindowManager::freeStaticStrings()
{
	TheGameWindowManagerScratchStrings[ 0 ].~AsciiString();
	TheGameWindowManagerScratchStrings[ 1 ].~AsciiString();
	TheGameWindowManagerScratchStrings[ 2 ].~AsciiString();
	TheGameWindowManagerScratchStrings[ 3 ].~AsciiString();
}
