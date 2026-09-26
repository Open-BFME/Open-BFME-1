// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/gamewindow /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Native WOLLoginMenuUpdate at 005001D0, 1693 bytes.
// Derived from the Zero Hour source; Copyright 2025 Electronic Arts Inc.
// GPL-3.0-or-later. BFME identity and layout witnesses:
// targets/game/reverse/identity_evidence/005001d0-login-update.md.
#define _WCTYPE_INLINE_DEFINED
#define __PLACEMENT_VEC_NEW_INLINE
#define ASCIISTRING_H
#define UNICODESTRING_H
#define _STLP_NO_EXCEPTIONS 1
#include "ascii_string.h"
#include "unicode_string.h"
#include <map>
namespace _STL { template<> struct less<AsciiString> { bool operator()(const AsciiString &a, const AsciiString &b)const {return a.compare(b)<0;} }; }

template <> inline const char *StringBase<char>::str() const
{
	return m_data ? m_data->data : "";
}
template <> inline const unsigned short *StringBase<unsigned short>::str() const
{
	return m_data ? m_data->data : (const unsigned short *)L"";
}

inline UnicodeString::UnicodeString()
{
	m_text = 0;
}
inline UnicodeString::UnicodeString(const wchar_t *s)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(s);
}
inline UnicodeString::UnicodeString(const UnicodeString &s)
{
	((StringBase<unsigned short> *)this)
		->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&s);
}
inline UnicodeString::~UnicodeString()
{
	((StringBase<unsigned short> *)this)->releaseBuffer();
}
inline UnicodeString &UnicodeString::operator=(const UnicodeString &s)
{
	((StringBase<unsigned short> *)this)->set(*(const StringBase<unsigned short> *)&s);
	return *this;
}

// The legacy window header embeds its own UnicodeString in unused inline
// accessors. Give that header-only view a distinct name while preserving the
// canonical native strings used by this body.
#undef UNICODESTRING_H
#define UnicodeString Rva00500A20HeaderUnicodeString
#include "GameClient/GameWindow.h"
#include "PreRTS.h"
#undef UnicodeString
#include <list>
#include <map>
#include <string>
#include "Common/FileSystem.h"
#include "Common/Registry.h"
#include "Common/UserPreferences.h"
#include "GameClient/GameText.h"
#include "GameClient/Shell.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetCheckBox.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/MessageBox.h"
extern Color GameSpyColor[];
enum {GSCOLOR_DEFAULT=0};
#include "GameNetwork/GameSpyOverlay.h"
#include "GameNetwork/WOLBrowser/WebBrowser.h"
template <> inline int StringBase<char>::getLength() const { return m_data ? m_data->length : 0; }
template <> inline bool StringBase<unsigned short>::isEmpty() const { return m_data == 0 || m_data->length == 0; }
template <> inline unsigned short StringBase<unsigned short>::getCharAt(int index) const { return m_data ? m_data->data[index] : 0; }
template <> inline int StringBase<unsigned short>::getLength() const { return m_data ? m_data->length : 0; }
#undef iswspace
extern "C" __declspec(dllimport) int __cdecl iswspace(unsigned short);

class GameSpyLoginPreferences : public UserPreferences
{
public:
	GameSpyLoginPreferences();
	virtual ~GameSpyLoginPreferences() {}

	virtual Bool load(AsciiString fname);
	virtual Bool write(void);

	AsciiString getPasswordForEmail( AsciiString email );
	AsciiString getDateForEmail( AsciiString email, AsciiString &month, AsciiString &date, AsciiString &year  );
	AsciiStringList getNicksForEmail( AsciiString email );
	void addLogin( AsciiString email, AsciiString nick, AsciiString password, AsciiString date );
	void forgetLogin( AsciiString email );
	AsciiStringList getEmails( void );

private:
	typedef std::map<AsciiString, AsciiString> PassMap;
	typedef std::map<AsciiString, AsciiString> DateMap;
	typedef std::map<AsciiString, AsciiStringList> NickMap;
	PassMap m_emailPasswordMap;
	NickMap m_emailNickMap;
	DateMap m_emailDateMap;
};


#include "Common/GameSpyMiscPreferences.h"
#include "GameClient/GameWindowTransitions.h"
// WindowLayout::hide slot +10 is independently verified by vtable VA010F7514
// and matched hide body 00497A00; the legacy GameWindow shim omits that slot.
class Rva005001D0Layout { public:
 virtual void slot0(); virtual void slot4(); virtual void slot8(); virtual void slotC(); virtual void hide(bool);
};
static Bool isShuttingDown, buttonPushed, loggedInOK;
static char *loginNextScreen;
static UnsignedInt loginAttemptTime;
static const UnsignedInt loginTimeoutInMS=10000;
static GameSpyLoginPreferences *loginPref;
void EnableLoginControls(Bool);
void checkLogin();
void TearDownGameSpy();
void SetUpGameSpy(const char *,const char *);
// Full verified helper from WOLLoginMenuShutdownThunk.cpp, visible here so
// MSVC preserves its private ESI argument contract. Its existing ledger owner
// remains unchanged; this TU claims only WOLLoginMenuUpdate.
static __declspec(noinline) void shutdownCompleteWOLLoginMenu(WindowLayout *layout)
{
 isShuttingDown=false;
 ((Rva005001D0Layout *)layout)->hide(true);
 TheShell->shutdownComplete(layout,loginNextScreen!=0);
 if(loginNextScreen!=0) {
  if(loginPref!=0) {loginPref->write();delete loginPref;loginPref=0;}
  TheShell->push(loginNextScreen);
 } else if(loginPref!=0) {loginPref->write();delete loginPref;loginPref=0;}
 loginNextScreen=0;
}
class PingResponse {public:std::string hostname;Int avgPing,repetitions;};
class PingerInterface { public:
 virtual void slot00(); virtual void slot04();virtual void slot08();virtual void slot0C();virtual void slot10();virtual void slot14();virtual void slot18();virtual Bool getResponse(PingResponse &);
};
extern PingerInterface *ThePinger;
// String prefix and complete 0x330 extent independently matched in
// GameNetwork/GameSpy/Thread/PeerResponseCopies.cpp. Payload fields below
// follow the reference declaration and this retail caller's aligned accesses.
class PeerResponse {
public:
 enum {PEERRESPONSE_LOGIN,PEERRESPONSE_DISCONNECT,PEERRESPONSE_MESSAGE,PEERRESPONSE_GROUPROOM};
 int peerResponseType;
 std::string groupRoomName,nick,oldNick;
 std::wstring text;
 std::string locale,stagingServerGameOptions;
 std::wstring stagingServerName;
 std::string stagingServerPingString,stagingServerLadderIP,stagingRoomMapName;
 std::string stagingRoomPlayerNames[8];
 std::string command,commandOptions;
 union {
 struct {int reason;} discon;
 struct {int id,numWaiting,maxWaiting,numGames,numPlaying;} groupRoom;
 struct {int profileID,wins,losses,roomType,flags;unsigned IP;int rankPoints,side,preorder;unsigned internalIP,externalIP;} player;
 char rvaPayloadF4[0x23C];
 };
 PeerResponse();~PeerResponse();
};
typedef char PeerResponseSizeCheck[sizeof(PeerResponse)==0x330?1:-1];
class GameSpyPeerMessageQueueInterface {public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0C();virtual void slot10();virtual void slot14();virtual void slot18();virtual void slot1C();virtual void slot20();virtual Bool getResponse(PeerResponse &);
};
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
// The 32-byte record copy at 004F97B0 and matched addGroupRoom/map body
// establish the extra final dword; its meaning remains address-derived.
class GameSpyGroupRoom {public:
 AsciiString m_name;UnicodeString m_translatedName;
 int m_groupID,m_numWaiting,m_maxWaiting,m_numGames,m_numPlaying,rvaField1C;
 GameSpyGroupRoom();GameSpyGroupRoom(const GameSpyGroupRoom&);~GameSpyGroupRoom();
};
typedef char GroupRoomSizeCheck[sizeof(GameSpyGroupRoom)==32?1:-1];
class GameSpyInfoInterface {public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0C();
 virtual void addGroupRoom(GameSpyGroupRoom);
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
 virtual void setLocalName(AsciiString);
 virtual void slot68();
 virtual void setLocalProfileID(int);
 virtual void slot70();
 virtual void slot74();
 virtual void slot78();
 virtual void slot7C();
 virtual void slot80();
 virtual void slot84();
 virtual void slot88();
 virtual void slot8C();
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
 virtual const AsciiString &getMOTD();
 virtual void slot108();
 virtual const AsciiString &getConfig();
 virtual void slot110();
 virtual void slot114();
 virtual void slot118();
 virtual void slot11C();
 virtual void slot120();
 virtual void slot124();
 virtual void slot128();
 virtual void slot12C();
 virtual void slot130();
 virtual void loadSavedIgnoreList();
 virtual void slot138();
 virtual void slot13C();
 virtual void slot140();
 virtual void slot144();
 virtual void setLocalIPs(unsigned,unsigned);
 virtual void slot14C();
 virtual void slot150();
 virtual void slot154();
 virtual void slot158();
 virtual void slot15C();
 virtual void slot160();
 virtual void slot164();
 virtual void setMaxMessagesPerUpdate(int);
 virtual void slot16C();
 virtual void slot170();
 virtual void slot174();
 virtual void readAdditionalDisconnects();
};
extern GameSpyInfoInterface *TheGameSpyInfo;

void WOLLoginMenuUpdate( WindowLayout * layout, void *userData)
{

	// We'll only be successful if we've requested to 
	if(isShuttingDown && TheShell->isAnimFinished() && TheTransitionHandler->isFinished())
		shutdownCompleteWOLLoginMenu(layout);

	if (TheShell->isAnimFinished() && !buttonPushed && TheGameSpyPeerMessageQueue)
	{
		PingResponse pingResp;
		if (ThePinger && ThePinger->getResponse(pingResp))
		{
			checkLogin();
		}

		PeerResponse resp;
		if (!loggedInOK && TheGameSpyPeerMessageQueue->getResponse( resp ))
		{
			switch (resp.peerResponseType)
			{
			case PeerResponse::PEERRESPONSE_GROUPROOM:
				{
					GameSpyGroupRoom room;
					room.m_groupID = resp.groupRoom.id;
					room.m_maxWaiting = resp.groupRoom.maxWaiting;
					room.m_name = resp.groupRoomName.c_str();
					room.m_translatedName = UnicodeString(L"TEST");
					room.m_numGames = resp.groupRoom.numGames;
					room.m_numPlaying = resp.groupRoom.numPlaying;
					room.m_numWaiting = resp.groupRoom.numWaiting;
					TheGameSpyInfo->addGroupRoom( room );
				}
				break;
			case PeerResponse::PEERRESPONSE_LOGIN:
				{
					loggedInOK = true;

					// fetch our player info
					TheGameSpyInfo->setLocalName( resp.nick.c_str() );
					TheGameSpyInfo->setLocalProfileID( resp.player.profileID );
					TheGameSpyInfo->loadSavedIgnoreList();
					TheGameSpyInfo->setLocalIPs(resp.player.internalIP, resp.player.externalIP);
					TheGameSpyInfo->readAdditionalDisconnects();
					//TheGameSpyInfo->setLocalEmail( resp.player.email );
					//TheGameSpyInfo->setLocalPassword( resp)

					GameSpyMiscPreferences miscPref;
					TheGameSpyInfo->setMaxMessagesPerUpdate(miscPref.getMaxMessagesPerUpdate());
				}
				break;
			case PeerResponse::PEERRESPONSE_DISCONNECT:
				{
					loginAttemptTime = 0;
					UnicodeString title, body;
					AsciiString disconMunkee;
					disconMunkee.format("GUI:GSDisconReason%d", resp.discon.reason);
					title = TheGameText->fetch( "GUI:GSErrorTitle" );
					body = TheGameText->fetch( disconMunkee );
					GSMessageBoxOk( title, body );
					EnableLoginControls( TRUE );

					// kill & restart the threads
					AsciiString motd = TheGameSpyInfo->getMOTD();
					AsciiString config = TheGameSpyInfo->getConfig();
					DEBUG_LOG(("Tearing down GameSpy from WOLLoginMenuUpdate(PEERRESPONSE_DISCONNECT)\n"));
					TearDownGameSpy();
					SetUpGameSpy( motd.str(), config.str() );
				}
				break;
			}
		}

		checkLogin();
	}

	if (TheGameSpyInfo && !buttonPushed && loginAttemptTime && (loginAttemptTime + loginTimeoutInMS < timeGetTime()))
	{
		// timed out a login attempt, so say so
		loginAttemptTime = 0;
		UnicodeString title, body;
		AsciiString disconMunkee;
		disconMunkee.format("GUI:GSDisconReason4");	// ("could not connect to server")
		title = TheGameText->fetch( "GUI:GSErrorTitle" );
		body = TheGameText->fetch( disconMunkee );
		GSMessageBoxOk( title, body );
		EnableLoginControls( TRUE );

		// kill & restart the threads
		AsciiString motd = TheGameSpyInfo->getMOTD();
		AsciiString config = TheGameSpyInfo->getConfig();
		DEBUG_LOG(("Tearing down GameSpy from WOLLoginMenuUpdate(login timeout)\n"));
		TearDownGameSpy();
		SetUpGameSpy( motd.str(), config.str() );
	}

}
