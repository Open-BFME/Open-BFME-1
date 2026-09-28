// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/gamewindow /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/psplayerstats /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Native BFME checkLogin at 0x004FFFC0, 418 bytes.
// ZH twin: WOLLoginMenu.cpp checkLogin() (GeneralsMD). BFME keeps the same
// statement shape but its own ABI: GameSpyInfo slots clearGroupRoomList +0x08,
// getLocalProfileID +0x70, setCachedLocalPlayerStats +0x8c, setPingString
// +0x110 (witnessed off this body's own call sites, same TU-local-slot style
// as the landed WOLLoginMenuUpdate at 0x005001D0); Pinger slots
// arePingsInProgress +0x20 / getPingString +0x2c (ZH PingThread.h order);
// BFME PSPlayerStats (0x1c4, psplayerstats shim) with by-value
// parsePlayerKVPairs (landed 0x00659670) exactly like the landed
// WOLGameSetupMenuUpdate call site.
#define _WCTYPE_INLINE_DEFINED
#define __PLACEMENT_VEC_NEW_INLINE
#define ASCIISTRING_H
#define UNICODESTRING_H
#define _STLP_NO_EXCEPTIONS 1
#include "ascii_string.h"
#include "unicode_string.h"
#include <map>
#include <string>

template <> inline const char *StringBase<char>::str() const
{
	return m_data ? m_data->data : "";
}

#include "PreRTS.h"
#include "Common/UserPreferences.h"
#include "Common/GameSpyMiscPreferences.h"
#include "GameNetwork/GameSpy/PersistentStorageThread.h"
#include "GameClient/Shell.h"
#include "GameClient/ShellHooks.h"

typedef char BfmeCheckLoginStatsSize[sizeof(PSPlayerStats) == 0x1c4 ? 1 : -1];

class PingResponse
{
public:
	std::string hostname;
	Int avgPing, repetitions;
};

// TU-local Pinger view. Slot order is ZH PingThread.h (destructor slot +0x00
// elided the way the landed WOLLoginMenuUpdate TU spells it); the two slots
// this body needs are arePingsInProgress +0x20 and getPingString +0x2c.
class PingerInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual Bool getResponse(PingResponse &resp);
	virtual Bool arePingsInProgress();
	virtual void slot24();
	virtual void slot28();
	virtual AsciiString getPingString(Int timeout);
};
extern PingerInterface *ThePinger;

// TU-local GameSpyInfo view. Positional slot order matches the landed
// WOLLoginMenuUpdate TU; the four slots this body calls carry their real ZH
// PeerDefs names (same names the BFME APT twin note on symbols.csv confirms
// at these offsets: +0x08, +0x70, +0x8c, +0x110).
class GameSpyInfoInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void clearGroupRoomList();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6C();
	virtual Int getLocalProfileID();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void setCachedLocalPlayerStats(PSPlayerStats stats);
	virtual void slot90();
	virtual void slot94();
	virtual void slot98();
	virtual void slot9C();
	virtual void slotA0();
	virtual void slotA4();
	virtual void slotA8();
	virtual void slotAC();
	virtual void slotB0();
	virtual void slotB4();
	virtual void slotB8();
	virtual void slotBC();
	virtual void slotC0();
	virtual void slotC4();
	virtual void slotC8();
	virtual void slotCC();
	virtual void slotD0();
	virtual void slotD4();
	virtual void slotD8();
	virtual void slotDC();
	virtual void slotE0();
	virtual void slotE4();
	virtual void slotE8();
	virtual void slotEC();
	virtual void slotF0();
	virtual void slotF4();
	virtual void slotF8();
	virtual void slotFC();
	virtual void slot100();
	virtual void slot104();
	virtual void slot108();
	virtual void slot10C();
	virtual void setPingString(const AsciiString &ping);
};
extern GameSpyInfoInterface *TheGameSpyInfo;

static Bool loggedInOK = false;
static Bool buttonPushed = false;
static char *nextScreen = NULL;
static UnsignedInt loginAttemptTime = 0;

// this is used to check if we've got all the pings
void checkLogin(void)
{
	if (loggedInOK && ThePinger && !ThePinger->arePingsInProgress())
	{
		// save off our ping string, and end those threads
		AsciiString pingStr = ThePinger->getPingString(1000);
		DEBUG_LOG(("Ping string is %s\n", pingStr.str()));
		TheGameSpyInfo->setPingString(pingStr);

		buttonPushed = true;
		loggedInOK = false; // don't try this again

		loginAttemptTime = 0;

		// start looking for group rooms
		TheGameSpyInfo->clearGroupRoomList();

		SignalUIInteraction(SHELL_SCRIPT_HOOK_GENERALS_ONLINE_LOGIN);
		nextScreen = "Menus/WOLWelcomeMenu.wnd";
		TheShell->pop();

		// read in some cached data
		GameSpyMiscPreferences mPref;
		PSPlayerStats localPSStats = GameSpyPSMessageQueueInterface::parsePlayerKVPairs(mPref.getCachedStats().str());
		localPSStats.id = TheGameSpyInfo->getLocalProfileID();
		TheGameSpyInfo->setCachedLocalPlayerStats(localPSStats);
	}
}
