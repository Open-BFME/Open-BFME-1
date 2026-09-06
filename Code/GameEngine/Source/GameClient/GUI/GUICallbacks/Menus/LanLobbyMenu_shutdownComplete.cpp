// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseascii /Ireference/shims/stringbaseunicode /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME7: LanLobbyMenu.cpp's static shutdownComplete(WindowLayout*) at 0x004CE910,
// a near twin of WOLWelcomeMenu.cpp's (0x0050B190) over the LAN lobby's
// LANisShuttingDown/LANnextScreen statics (VA 0x012F3D49/0x012F3D4C); the
// tracked port compiles the ZH body, this TU carries the retail shape under a
// distinct name with a TU-local caller for the private esi convention.
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include "Lib/BaseType.h"
#include "string_base.h"
#include "Common/CRC.h"
#include "Common/GameEngine.h"
#include "Common/GlobalData.h"
#include "Common/MultiplayerSettings.h"
#include "Common/NameKeyGenerator.h"
#include "Common/Player.h"
#include "Common/PlayerTemplate.h"
#include "Common/QuotedPrintable.h"
#include "Common/UserPreferences.h"
#include "GameClient/AnimateWindowManager.h"
#include "GameClient/GameText.h"
#include "GameClient/MapUtil.h"
#include "GameClient/Mouse.h"
#include "GameClient/WindowLayout.h"
#include "GameClient/Gadget.h"
#include "GameClient/Shell.h"
#include "GameClient/ShellHooks.h"
#include "GameClient/KeyDefs.h"
#include "GameClient/GameInfoWindow.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/MessageBox.h"
#include "GameClient/GameWindowTransitions.h"
#include "GameLogic/GameLogic.h"
#include "GameNetwork/IPEnumeration.h"
#include "GameNetwork/LANAPICallbacks.h"
#include "GameNetwork/LANGameInfo.h"

class BfmeVirtualHideLayout
{
public:
	virtual void slot0() = 0;
	virtual void slot4() = 0;
	virtual void slot8() = 0;
	virtual void slotC() = 0;
	virtual void hide( Bool immediate ) = 0;
};

static Bool LANisShuttingDown = false;
static char *LANnextScreen = NULL;

static void shutdownCompleteLanLobbyMenu( WindowLayout *layout )
{
	LANisShuttingDown = false;

	// hide the layout
	((BfmeVirtualHideLayout *)layout)->hide( TRUE );

	// our shutdown is complete
	TheShell->shutdownComplete( layout, (LANnextScreen != NULL) );

	if (LANnextScreen != NULL)
	{
		TheShell->push(LANnextScreen);
	}

	LANnextScreen = NULL;
}

// absent-from-retail: TU-local caller keeping the static alive with the same
// private register convention its LanLobbyMenuUpdate/Shutdown callers give it.
void Rva004CE910ShutdownCaller( WindowLayout *layout, Bool done )
{
	if ( done )
		shutdownCompleteLanLobbyMenu( layout );
}

// absent-from-retail: in the LAN lobby TU the flag's address escapes (the
// tracked port hands it to helpers), so MSVC cannot assume `layout` does not
// alias it and keeps the store ahead of the vtable load, as retail does.
Bool *Rva004CE910ShutdownFlag( void )
{
	return &LANisShuttingDown;
}
