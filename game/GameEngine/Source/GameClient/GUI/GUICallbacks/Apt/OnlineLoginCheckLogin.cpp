// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/gamewindow /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/psplayerstats /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// ?_bfme_checkLogin@BfmeAptScreenOnlineLogin@@QAEXXZ
// Open-BFME: BfmeAptScreenOnlineLogin::checkLogin, retail 0x00550AD0, 1130 bytes.
//
// The Apt-screen port of Zero Hour WOLLoginMenu.cpp checkLogin(): once the
// login succeeded (+0x94) and ThePinger has finished, save the ping string
// (timeout from GameSpyConfig::getPingTimeoutInMs, slot +0x0c), clear the
// login flag and attempt time (+0x98), request the group rooms, signal
// SHELL_SCRIPT_HOOK_GENERALS_ONLINE_LOGIN and cache the local player stats,
// statement for statement like the matched static checkLogin (0x004FFFC0).
// BFME adds the OptionPreferences "HasGotOnline" write and stores the login
// through the member GameSpyLoginPreferences (+0x3C; matched addLogin
// 0x00082790) the way the matched WOLLoginMenuSystem does, with the password
// kept only when the remember checkbox (+0x80) is set, then opens
// "OnlineHome". Callers: the login update body at 0x0055215A and 0x0055284D
// (ILT 0x0000DC6A). Layout follows the matched constructor (0x005538A0) and
// text getters; the +0x34 context callee keeps its ledger placeholder name.
//
// BFME UserPreferences has four virtuals (vtable 0x01076FC0 for the login
// preferences): destructor, load(UnicodeString) 0x000ACD50, load(AsciiString),
// write at +0x0C; VC7.1 reaches the member's write through that slot.
#define _WCTYPE_INLINE_DEFINED
#define __PLACEMENT_VEC_NEW_INLINE
#define ASCIISTRING_H
#define UNICODESTRING_H
#define _STLP_NO_EXCEPTIONS 1
#include "ascii_string.h"
#include "unicode_string.h"
#include <map>
#include <string>

#include "PreRTS.h"
#include "GameNetwork/GameSpy/PersistentStorageThread.h"
#include "GameClient/ShellHooks.h"

// Retail inlines ~UnicodeString: temporaries are released by a direct call to
// StringBase<unsigned short>::releaseBuffer (0x008881D0), not the ??1UnicodeString stub.
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }

typedef char BfmeCheckLoginStatsSize[sizeof(PSPlayerStats) == 0x1c4 ? 1 : -1];

typedef std::map<AsciiString, AsciiString> PreferenceMap;

class UserPreferences : public PreferenceMap
{
public:
	virtual ~UserPreferences();
	virtual Bool load(AsciiString fname);
	virtual Bool load(const UnicodeString &fname);
	virtual Bool write(void);

protected:
	AsciiString m_filename;
};

class OptionPreferences : public UserPreferences
{
public:
	OptionPreferences();
	virtual ~OptionPreferences();
};

class GameSpyMiscPreferences : public UserPreferences
{
public:
	GameSpyMiscPreferences();
	virtual ~GameSpyMiscPreferences();
	AsciiString getCachedStats(void);
};

class GameSpyLoginPreferences : public UserPreferences
{
public:
	void addLogin(AsciiString email, AsciiString nick, AsciiString password, AsciiString date);

private:
	unsigned char m_maps[0x24];
};

class GameSpyConfigInterface
{
public:
	virtual ~GameSpyConfigInterface();
	virtual void getPingServers(void);
	virtual Int getNumPingRepetitions(void);
	virtual Int getPingTimeoutInMs(void);
};
extern GameSpyConfigInterface *TheGameSpyConfig;

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
	virtual void slot1C();
	virtual Bool arePingsInProgress();
	virtual void slot24();
	virtual void slot28();
	virtual AsciiString getPingString(Int timeout);
};
extern PingerInterface *ThePinger;

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

class GameWindow;
Bool GadgetCheckBoxIsChecked(GameWindow *g);

class BfmeThingVGH
{
public:
	void bfmeGoVGH(const char *name);
};

class BfmeAptWindowContext
{
public:
	BfmeThingVGH *m_context;
	int m_z38;
};

class _bfme_AptGameWindow
{
public:
	virtual ~_bfme_AptGameWindow();

private:
	int m_z04, m_z08, m_z0C, m_z10, m_z14, m_z18;
	int m_z1C, m_z20, m_z24, m_z28, m_z2C, m_z30;

protected:
	BfmeAptWindowContext m_ctx;
};

class BfmeAptScreenOnlineLogin : public _bfme_AptGameWindow
{
public:
	virtual ~BfmeAptScreenOnlineLogin();

	void _bfme_checkLogin();
	UnicodeString bfmeGetTextAt74() const;
	UnicodeString bfmeGetTextAt78() const;
	UnicodeString bfmeGetTextAt7C() const;

private:
	GameSpyLoginPreferences m_state;
	GameWindow *m_control74;
	GameWindow *m_control78;
	GameWindow *m_control7C;
	GameWindow *m_control80;
	GameWindow *m_control84;
	int m_pad88;
	int m_flag8C;
	int m_z90;
	char m_loggedInOK;
	char m_needsRefresh;
	int m_z98;
};

void BfmeAptScreenOnlineLogin::_bfme_checkLogin()
{
	if (m_loggedInOK && ThePinger && !ThePinger->arePingsInProgress())
	{
		OptionPreferences pref;
		pref["HasGotOnline"] = "yes";
		pref.write();

		// save off our ping string
		AsciiString pingStr = ThePinger->getPingString(TheGameSpyConfig->getPingTimeoutInMs());
		TheGameSpyInfo->setPingString(pingStr);

		m_loggedInOK = false; // don't try this again
		m_z98 = 0;

		// start looking for group rooms
		TheGameSpyInfo->clearGroupRoomList();

		SignalUIInteraction(SHELL_SCRIPT_HOOK_GENERALS_ONLINE_LOGIN);

		// read in some cached data
		GameSpyMiscPreferences mPref;
		PSPlayerStats localPSStats = GameSpyPSMessageQueueInterface::parsePlayerKVPairs(mPref.getCachedStats().str());
		localPSStats.id = TheGameSpyInfo->getLocalProfileID();
		TheGameSpyInfo->setCachedLocalPlayerStats(localPSStats);

		AsciiString email;
		email.translate(bfmeGetTextAt74());
		AsciiString login;
		AsciiString password;
		login.translate(bfmeGetTextAt78());
		if (m_control80 && GadgetCheckBoxIsChecked(m_control80))
			password.translate(bfmeGetTextAt7C());
		else
			password.clear();

		m_state["lastName"] = login;
		m_state["lastEmail"] = email;
		m_state["useProfiles"] = "yes";
		AsciiString date("01/01/1970");
		m_state.addLogin(email, login, password, date);
		m_state.write();

		m_ctx.m_context->bfmeGoVGH("OnlineHome");
	}
}
