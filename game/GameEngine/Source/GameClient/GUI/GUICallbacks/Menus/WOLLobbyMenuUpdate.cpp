// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/gamewindow /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Native lobby callbacks: Update at 004FD9B0 (4536 bytes with switch tables),
// Init at 004FBBE0 (1711 bytes), playerTooltip at 004FA800 (1517 bytes).
// Derived from WOLLobbyMenu.cpp; Copyright 2025 Electronic Arts Inc.,
// GPL-3.0-or-later. Identity, helper ABI and BFME layout evidence:
// targets/game/reverse/identity_evidence/004fd9b0-lobby-update.md and
// targets/game/reverse/identity_evidence/004fbbe0-lobby-init.md and
// targets/game/reverse/identity_evidence/004fa800-player-tooltip.md.
#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#define ASCIISTRING_H
#define UNICODESTRING_H
#include "ascii_string.h"
#include "unicode_string.h"

template <> inline const char *StringBase<char>::str() const {
  return m_data ? m_data->data : "";
}
template <>
inline const unsigned short *StringBase<unsigned short>::str() const {
  return m_data ? m_data->data : (const unsigned short *)L"";
}

inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::UnicodeString(const wchar_t *s) {
  ((StringBase<unsigned short> *)this)
      ->StringBase<unsigned short>::StringBase(s);
}
inline UnicodeString::UnicodeString(const UnicodeString &s) {
  ((StringBase<unsigned short> *)this)
      ->StringBase<unsigned short>::StringBase(
          *(const StringBase<unsigned short> *)&s);
}
inline UnicodeString::~UnicodeString() {
  ((StringBase<unsigned short> *)this)->releaseBuffer();
}
inline UnicodeString &UnicodeString::operator=(const UnicodeString &s) {
  ((StringBase<unsigned short> *)this)
      ->set(*(const StringBase<unsigned short> *)&s);
  return *this;
}

// The legacy window header embeds its own UnicodeString in unused inline
// accessors. Give that header-only view a distinct name while preserving the
// canonical native strings used by this body.
#undef UNICODESTRING_H
#define UnicodeString Rva004FD9B0HeaderUnicodeString
#include "GameClient/GameWindow.h"
#include "PreRTS.h"
#undef UnicodeString
#include <list>
#include <map>
#include <string>
#include <time.h>

#include "Common/GameState.h"
#include "Common/CustomMatchPreferences.h"
#include "Common/PlayerTemplate.h"
#include "GameClient/Mouse.h"
#include "GameClient/GadgetListBox.h"
#include "GameNetwork/RankPointValue.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetTextEntry.h"
#include "Common/NameKeyGenerator.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GameText.h"
#include "GameClient/GameWindowTransitions.h"
#include "GameClient/Shell.h"
#include "GameClient/ShellHooks.h"
#include "GameNetwork/GameSpyOverlay.h"
extern Color GameSpyColor[];
const int GSCOLOR_DEFAULT = 0;
const int GroupRoom = 1;
const int PEERTrue = 1;
enum {
  PEERJoinSuccess,
  PEERFullRoom,
  PEERInviteOnlyRoom,
  PEERBannedFromRoom,
  PEERBadPassword,
  PEERAlreadyInRoom,
  PEERNoConnection = 7,
  Rva004FD9B0JoinResult9 = 9
};
enum { PEER_ADD, PEER_UPDATE, PEER_REMOVE, PEER_CLEAR };
extern const AsciiString Rva01336E50EmptyAscii;
extern const UnicodeString Rva01336E54EmptyUnicode;
// String prefix, 0x330 extent and payload fields follow the independently
// matched PeerResponse copy/assignment bodies and aligned retail accesses.
class PeerResponse {
public:
  enum {
    PEERRESPONSE_LOGIN,
    PEERRESPONSE_DISCONNECT,
    PEERRESPONSE_MESSAGE,
    PEERRESPONSE_GROUPROOM,
    PEERRESPONSE_STAGINGROOM,
    PEERRESPONSE_STAGINGROOMLISTCOMPLETE,
    PEERRESPONSE_STAGINGROOMPLAYERINFO,
    PEERRESPONSE_JOINGROUPROOM,
    PEERRESPONSE_CREATESTAGINGROOM,
    PEERRESPONSE_JOINSTAGINGROOM,
    PEERRESPONSE_PLAYERJOIN,
    PEERRESPONSE_PLAYERLEFT,
    PEERRESPONSE_PLAYERCHANGEDNICK,
    PEERRESPONSE_PLAYERINFO,
    PEERRESPONSE_PLAYERCHANGEDFLAGS,
    PEERRESPONSE_ROOMUTM,
    PEERRESPONSE_PLAYERUTM
  };
  int peerResponseType;
  std::string groupRoomName, nick, oldNick;
  std::wstring text;
  std::string locale, stagingServerGameOptions;
  std::wstring stagingServerName;
  std::string stagingServerPingString, stagingServerLadderIP,
      stagingRoomMapName;
  std::string stagingRoomPlayerNames[8];
  std::string command, commandOptions;
  union {
    struct {
      int reason;
    } discon;
    struct {
      int id;
      bool ok;
    } joinGroupRoom;
    struct {
      int result;
    } createStagingRoom;
    struct {
      int id;
      bool ok;
      bool isHostPresent;
      int result;
    } joinStagingRoom;
    struct {
      bool isPrivate, isAction;
      int profileID;
    } message;
    struct {
      int profileID, wins, losses, roomType, flags;
      unsigned IP;
      int rankPoints, side, preorder;
      unsigned internalIP, externalIP;
    } player;
    struct {
      int id, action;
      bool isStaging, requiresPassword, allowObservers;
      unsigned version, exeCRC, iniCRC, rvaPayload18;
      unsigned short ladderPort;
      int wins[8], losses[8], profileID[8], faction[8], color[8], numPlayers,
          numObservers, maxPlayers, percentComplete, useStats;
    } stagingRoom;
    char extent[0x23c];
  };
  PeerResponse();
  PeerResponse(const PeerResponse &);
  ~PeerResponse();
};
typedef char ResponseSize[sizeof(PeerResponse) == 0x330 ? 1 : -1];
class BuddyInfo {
public:
 int m_id; AsciiString m_name,m_email,m_countryCode;
 int m_status; UnicodeString m_statusString,m_locationString;
};
typedef std::map<int,BuddyInfo> BuddyInfoMap;
class PlayerInfo {
public:
  AsciiString name, baseName, locale;
  int wins, losses, profileID, flags, rankPoints, rva20, rva24, rva28, side,
      preorder;
  PlayerInfo();
  PlayerInfo(const PlayerInfo &);
  ~PlayerInfo();
};
struct AsciiComparator {
  bool operator()(AsciiString, AsciiString) const;
};
typedef std::map<AsciiString, PlayerInfo, AsciiComparator> PlayerInfoMap;
class GameSpyGroupRoom {
public:
  AsciiString m_name;
  UnicodeString m_translatedName;
  int m_groupID, m_numWaiting, m_maxWaiting, m_numGames, m_numPlaying, rva1C;
  GameSpyGroupRoom();
};
typedef std::map<int, GameSpyGroupRoom> GroupRoomMap;
enum SlotState {
  SLOT_OPEN,
  SLOT_CLOSED,
  SLOT_EASY_AI,
  SLOT_MED_AI,
  SLOT_BRUTAL_AI,
  SLOT_PLAYER
};
struct GameSlotConnectInfo {
  unsigned rva0;
  unsigned short rva4;
  GameSlotConnectInfo() : rva0(0), rva4(0) {}
};
class GameSlot {
public:
  virtual void reset();
  char opaque04[8];
  int color;
  char opaque10[0x40 - 0x10];
  void setColor(int c) { color = c; }
  void setPlayerTemplate(int);
  UnicodeString getName() const;
  void setState(SlotState, UnicodeString = Rva01336E54EmptyUnicode,
                const GameSlotConnectInfo * = &GameSlotConnectInfo());
};
class GameSpyGameSlot : public GameSlot {
public:
  int rva40, profileID;
  char opaque48[0x10];
  int wins, losses;
  char opaque60[0x18];
  void setWins(int n) { wins = n; }
  void setLosses(int n) { losses = n; }
  void setProfileID(int n) { profileID = n; }
};
class GameInfo {
public:
  virtual void slot00();
  virtual void slot04();
  virtual void reset();
  char opaque04[0x50];
  int useStats;
  const GameSlot *getConstSlot(int) const;
  void setMap(AsciiString);
  void setUseStats(int n) { useStats = n; }
};
// The independently matched room copy constructor fixes GameInfo at 0x58,
// eight 0x78-byte slots and the complete 0x468-byte room. Unknown words
// retain offset names. The lobby writes room+438 from response payload+18.
class GameSpyStagingRoom : public GameInfo {
public:
  GameSpyGameSlot m_slots[8];
  UnicodeString gameName;
  int id;
  void *transport;
  AsciiString localName;
  bool requiresPassword, allowObservers;
  unsigned version, exeCRC, iniCRC, rva438;
  bool rva43C;
  int rva440;
  AsciiString ladderIP, pingString;
  int ping;
  unsigned short ladderPort;
  int numPlayers, maxPlayers, numObservers, rva460, rva464;
  GameSpyStagingRoom();
  GameSpyStagingRoom(const GameSpyStagingRoom &);
  ~GameSpyStagingRoom();
  GameSpyGameSlot *getGameSpySlot(int);
  void setGameName(UnicodeString);
  void setPingString(AsciiString);
  void setLadderIP(AsciiString);
  void setID(int n) { id = n; }
  void setHasPassword(bool n) { requiresPassword = n; }
  void setAllowObservers(bool n) { allowObservers = n; }
  void setVersion(unsigned n) { version = n; }
  void setExeCRC(unsigned n) { exeCRC = n; }
  void setIniCRC(unsigned n) { iniCRC = n; }
  void setLadderPort(unsigned short n) { ladderPort = n; }
  void setReportedNumPlayers(int n) { numPlayers = n; }
  void setReportedMaxPlayers(int n) { maxPlayers = n; }
  void setReportedNumObservers(int n) { numObservers = n; }
};
typedef char RoomSize[sizeof(GameSpyStagingRoom) == 0x468 ? 1 : -1];
class GameSpyInfoInterface {
public:
  virtual void slot00();
  virtual void reset();
  virtual void slot08();
  virtual GroupRoomMap *getGroupRoomList();
  virtual void slot10();
  virtual void slot14();
  virtual void joinGroupRoom(int);
  virtual void slot1C();
  virtual void slot20();
  virtual void joinBestGroupRoom(bool = true);
  virtual void setCurrentGroupRoom(int);
  virtual int getCurrentGroupRoom();
  virtual void slot30();
  virtual void slot34();
  virtual void slot38();
  virtual void slot3C();
  virtual void updatePlayerInfo(PlayerInfo,
                                AsciiString = Rva01336E50EmptyAscii);
  virtual void playerLeftGroupRoom(AsciiString);
  virtual PlayerInfoMap *getPlayerInfoMap();
  virtual PlayerInfo *rva00632850Lookup(const char *);
  virtual void slot50();
  virtual BuddyInfoMap *getBuddyMap();
  virtual void slot58();
  virtual void slot5C();
  virtual void slot60();
  virtual void slot64();
  virtual AsciiString getLocalName();
  virtual void slot6C();
  virtual void slot70();
  virtual void slot74();
  virtual void slot78();
  virtual void slot7C();
  virtual void slot80();
  virtual void slot84();
  virtual void slot88();
  virtual void slot8C();
  virtual void slot90();
  virtual void clearStagingRoomList();
  virtual void slot98();
  virtual void slot9C();
  virtual void addStagingRoom(GameSpyStagingRoom);
  virtual void updateStagingRoom(GameSpyStagingRoom);
  virtual void removeStagingRoom(GameSpyStagingRoom);
  virtual bool hasStagingRoomListChanged();
  virtual void slotB0();
  virtual void markAsStagingRoomHost();
  virtual void slotB8();
  virtual void sawFullGameList();
  virtual void slotC0();
  virtual GameSpyStagingRoom *getCurrentStagingRoom();
  virtual void slotC8();
  virtual void setGameOptions();
  virtual void slotD0();
  virtual void slotD4();
  virtual void slotD8();
  virtual void slotDC();
  virtual void slotE0();
  virtual void registerTextWindow(GameWindow *);
  virtual void slotE8();
  virtual int addText(UnicodeString, Color, GameWindow *);
  virtual void addChat(AsciiString, int, UnicodeString, bool, bool,
                       GameWindow *);
  virtual void slotF4();
  virtual void slotF8();
  virtual void slotFC();
  virtual void slot100();
  virtual void slot104();
  virtual void slot108();
  virtual void slot10C();
  virtual void slot110();
  virtual void slot114();
  virtual void slot118();
  virtual void slot11C();
  virtual void slot120();
  virtual void slot124();
  virtual void slot128();
  virtual bool isSavedIgnored(int);
  virtual void slot130();
  virtual void slot134();
  virtual void slot138();
  virtual void slot13C();
  virtual void slot140();
  virtual bool isIgnored(AsciiString);
  virtual void slot148();
  virtual void slot14C();
  virtual void slot150();
  virtual void slot154();
  virtual void slot158();
  virtual void slot15C();
  virtual void slot160();
  virtual void slot164();
  virtual void slot168();
  virtual int getMaxMessagesPerUpdate();
};
class PeerRequest {
public:
  enum {
    PEERREQUEST_JOINSTAGINGROOM = 11,
    PEERREQUEST_STARTGAMELIST = 7,
    PEERREQUEST_GETEXTENDEDSTAGINGROOMINFO = 20
  };
  int peerRequestType;
  std::string nick;
  std::wstring text;
  std::string password;
  char opaque28[0xe4 - 0x28];
  union {
    struct {
      int id;
    } stagingRoom;
    struct {
      bool restrictGameList;
    } gameList;
    char extent[0xb0];
  };
  PeerRequest();
  ~PeerRequest();
};

class GameSpyPeerMessageQueueInterface {
public:
  virtual void slot00();
  virtual void slot04();
  virtual void slot08();
  virtual void slot0C();
  virtual void slot10();
  virtual void slot14();
  virtual void addRequest(const PeerRequest &);
  virtual void slot1C();
  virtual void slot20();
  virtual bool getResponse(PeerResponse &);
};
class GameSpyConfigInterface {
public:
  virtual void slot00();
  virtual void slot04();
  virtual void slot08();
  virtual void slot0C();
  virtual void slot10();
  virtual void slot14();
  virtual void slot18();
  virtual void slot1C();
  virtual int getQMChannel();
  virtual void slot24();
  virtual void slot28();
  virtual void slot2C();
  virtual void slot30();
  virtual void slot34();
  virtual bool restrictGamesToLobby();
};

extern GameSpyInfoInterface *TheGameSpyInfo;
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
extern GameSpyConfigInterface *TheGameSpyConfig;
extern std::list<PeerResponse> TheLobbyQueuedUTMs;
class Rva004FD9B0Logic {
public:
  char opaque00[0x3c];
  unsigned frame;
  char opaque40[0xcc];
  int gameMode;
  bool isInShellGame() { return gameMode == 4; }
  unsigned getFrame() { return frame; }
};
extern Rva004FD9B0Logic *TheGameLogic;
class Glo00EF3330 {
public:
  void h004893E0();
  void h00489410();
};
// Calls at +48/+BA use the independently matched transition critical-section
// increment/decrement helpers. The guard preserves retail unwind behavior.
class Rva004FD9B0TransitionGuard {
public:
  Rva004FD9B0TransitionGuard() {
    if (TheTransitionHandler)
      ((Glo00EF3330 *)TheTransitionHandler)->h004893E0();
  }
  ~Rva004FD9B0TransitionGuard() {
    if (TheTransitionHandler)
      ((Glo00EF3330 *)TheTransitionHandler)->h00489410();
  }
};
class Rva004FD9B0Layout {
public:
  virtual void slot00();
  virtual void slot04();
  virtual void slot08();
  virtual void slot0C();
  virtual void hide(bool);
};
static bool justEntered, isShuttingDown, raiseMessageBoxes, buttonPushed;
static int initialGadgetDelay = 2, groupRoomToJoin;
static char *nextScreen;
static unsigned gameListRefreshTime, playerListRefreshTime;
static GameWindow *comboLobbyGroupRooms, *listboxLobbyChat;
void TearDownGameSpy();
void HandleBuddyResponses();
void HandlePersistentStorageResponses();
void RaiseGSMessageBox();
static bool s_tryingToHostOrJoin;
inline void SetLobbyAttemptHostJoin(bool v) { s_tryingToHostOrJoin = v; }
void RefreshGameListBoxes();
void PopulateLobbyPlayerListbox();
// These three visible private helpers preserve the retail register argument
// contracts. The two clone helpers below move their existing ownership here;
// shutdownComplete keeps its independent owner.
static __declspec(noinline) void
shutdownCompleteWOLLobbyMenu(WindowLayout *layout) {
  isShuttingDown = false;
  ((Rva004FD9B0Layout *)layout)->hide(true);
  TheShell->shutdownComplete(layout, nextScreen != 0);
  if (nextScreen)
    TheShell->push(nextScreen);
  nextScreen = 0;
}
__forceinline void refreshPlayerList() {
  if (playerListRefreshTime == 0 ||
      playerListRefreshTime + 5000 <= timeGetTime()) {
    PopulateLobbyPlayerListbox();
    playerListRefreshTime = timeGetTime();
  }
}
__forceinline void refreshGameList() {
  if (TheGameSpyInfo &&
      (gameListRefreshTime == 0 ||
       gameListRefreshTime + 10000 <= timeGetTime()) &&
      TheGameSpyInfo->hasStagingRoomListChanged()) {
    RefreshGameListBoxes();
    gameListRefreshTime = timeGetTime();
  }
}
static int g_colorCurrentRoom, g_colorRoom;
static void populateGroupRoomListbox_004FA240(GameWindow *lb) {
  if (!lb)
    return;

  GadgetComboBoxReset(lb);
  int indexToSelect = -1;
  GroupRoomMap::iterator iter;

  for (iter = TheGameSpyInfo->getGroupRoomList()->begin();
       iter != TheGameSpyInfo->getGroupRoomList()->end(); ++iter) {
    GameSpyGroupRoom room = iter->second;
    if (room.m_groupID != TheGameSpyConfig->getQMChannel()) {
      if (room.m_groupID == TheGameSpyInfo->getCurrentGroupRoom()) {
        int selected = GadgetComboBoxAddEntry(lb, room.m_translatedName,
                                              g_colorCurrentRoom);
        GadgetComboBoxSetItemData(lb, selected, (void *)room.m_groupID);
        indexToSelect = selected;
      } else {
        int selected =
            GadgetComboBoxAddEntry(lb, room.m_translatedName, g_colorRoom);
        GadgetComboBoxSetItemData(lb, selected, (void *)room.m_groupID);
      }
    }
  }

  GadgetComboBoxSetSelectedPos(lb, indexToSelect, false);
}
class BFMEPlayerInfoString : private StringBase<char> {
public:
  BFMEPlayerInfoString &operator=(const char *text) {
    StringBase<char>::set(text, text ? strlen(text) : 0);
    return *this;
  }
};

class BFMEPlayerInfoLayout {
public:
  BFMEPlayerInfoString m_name;
  BFMEPlayerInfoString m_baseName;
  BFMEPlayerInfoString m_locale;
  Int m_wins;
  Int m_losses;
  Int m_profileID;
  Int m_flags;
  Int m_rankPoints;
  Int m_bfmeBookkeeping[3];
  Int m_side;
  Int m_preorder;
};

typedef char
    BFMEPlayerInfoStringSize[sizeof(BFMEPlayerInfoString) == 4 ? 1 : -1];
typedef char
    BFMEPlayerInfoLayoutSize[sizeof(BFMEPlayerInfoLayout) == 0x34 ? 1 : -1];

static void fillPlayerInfo_004F9920(const PeerResponse *resp, PlayerInfo *info) {
  BFMEPlayerInfoLayout *bfmeInfo =
      reinterpret_cast<BFMEPlayerInfoLayout *>(info);
  char baseName[256] = {0};
  strncpy(baseName, resp->nick.c_str(), 255);
  char *suffix = strrchr(baseName, '-');
  if (suffix)
    *suffix = 0;

  const char *nick = resp->nick.c_str();
  bfmeInfo->m_name = nick;
  bfmeInfo->m_baseName = baseName;
  bfmeInfo->m_profileID = resp->player.profileID;
  bfmeInfo->m_flags = resp->player.flags;
  bfmeInfo->m_wins = resp->player.wins;
  bfmeInfo->m_losses = resp->player.losses;
  const char *locale = resp->locale.c_str();
  bfmeInfo->m_locale = locale;
  bfmeInfo->m_rankPoints = resp->player.rankPoints;
  bfmeInfo->m_side = resp->player.side;
  bfmeInfo->m_preorder = resp->player.preorder;
}

template <> inline int StringBase<char>::getLength() const {
  return m_data ? m_data->length : 0;
}
template <> inline void StringBase<char>::concat(char c) { concat(&c, 1); }
// The real 91-byte comparison remains visible for exception analysis.
// Its independent emitted body exactly matches 00090570.
template <>
__declspec(noinline) int StringBase<char>::compare(const char *str) const {
  int strLen = str ? (int)strlen(str) : 0;
  int len = m_data ? m_data->length : 0;
  const char *data = m_data ? m_data->data : "";
  int result = memcmp(data, str, len < strLen ? len : strLen);
  return result == 0 ? len - strLen : result;
}
__declspec(noinline) bool operator==(const StringBase<char> &a, const char *b) {
  return a.compare(b) == 0;
}
inline bool rva004FD9B0AsciiEquals(const AsciiString &a, const char *b) {
  return (const StringBase<char> &)a == b;
}
void WOLLobbyMenuUpdate(WindowLayout *layout, void *userData) {
  if (justEntered) {
    if (initialGadgetDelay == 1) {
      Rva004FD9B0TransitionGuard transitionGuard;
      TheTransitionHandler->remove("MainMenuDefaultMenuLogoFade");
      TheTransitionHandler->setGroup("WOLCustomLobbyFade");
      initialGadgetDelay = 2;
      justEntered = FALSE;
    } else
      initialGadgetDelay--;
  }
  if (TheGameLogic->isInShellGame() && TheGameLogic->getFrame() == 1) {
    SignalUIInteraction(SHELL_SCRIPT_HOOK_GENERALS_ONLINE_ENTERED_FROM_GAME);
  }

  if (isShuttingDown && TheShell->isAnimFinished() &&
      TheTransitionHandler->isFinished())
    shutdownCompleteWOLLobbyMenu(layout);

  if (raiseMessageBoxes) {
    RaiseGSMessageBox();
    raiseMessageBoxes = false;
  }

  if (TheShell->isAnimFinished() && TheTransitionHandler->isFinished() &&
      !buttonPushed && TheGameSpyPeerMessageQueue) {
    HandleBuddyResponses();
    HandlePersistentStorageResponses();

    Int allowedMessages = TheGameSpyInfo->getMaxMessagesPerUpdate();
    Bool sawImportantMessage = FALSE;
    Bool shouldRepopulatePlayers = FALSE;
    PeerResponse resp;
    while (allowedMessages-- && !sawImportantMessage &&
           TheGameSpyPeerMessageQueue->getResponse(resp)) {
      switch (resp.peerResponseType) {
      case PeerResponse::PEERRESPONSE_JOINGROUPROOM:
        sawImportantMessage = TRUE;
        if (resp.joinGroupRoom.ok) {

          TheGameSpyInfo->setCurrentGroupRoom(resp.joinGroupRoom.id);
          TheGameSpyInfo->getPlayerInfoMap()->clear();
          GroupRoomMap::iterator iter =
              TheGameSpyInfo->getGroupRoomList()->find(resp.joinGroupRoom.id);
          if (iter != TheGameSpyInfo->getGroupRoomList()->end()) {
            GameSpyGroupRoom room = iter->second;
            UnicodeString msg;
            msg.format(TheGameText->fetch("GUI:LobbyJoined"),
                       room.m_translatedName.str());
            TheGameSpyInfo->addText(msg, GameSpyColor[GSCOLOR_DEFAULT], NULL);
          }
        } else {
          TheGameSpyInfo->joinBestGroupRoom();
        }
        populateGroupRoomListbox_004FA240(comboLobbyGroupRooms);
        shouldRepopulatePlayers = TRUE;
        break;
      case PeerResponse::PEERRESPONSE_PLAYERCHANGEDFLAGS: {
        PlayerInfo p;
        fillPlayerInfo_004F9920(&resp, &p);
        TheGameSpyInfo->updatePlayerInfo(p);
        shouldRepopulatePlayers = TRUE;
      } break;
      case PeerResponse::PEERRESPONSE_PLAYERCHANGEDNICK: {
        PlayerInfo p;
        fillPlayerInfo_004F9920(&resp, &p);
        TheGameSpyInfo->updatePlayerInfo(p);
        shouldRepopulatePlayers = TRUE;
      } break;
      case PeerResponse::PEERRESPONSE_PLAYERINFO: {
        PlayerInfo p;
        fillPlayerInfo_004F9920(&resp, &p);
        TheGameSpyInfo->updatePlayerInfo(p);
        shouldRepopulatePlayers = TRUE;
      } break;
      case PeerResponse::PEERRESPONSE_PLAYERJOIN: {
        if (resp.player.roomType == GroupRoom) {
          PlayerInfo p;
          fillPlayerInfo_004F9920(&resp, &p);
          TheGameSpyInfo->updatePlayerInfo(p);
          shouldRepopulatePlayers = TRUE;
        }
      } break;
      case PeerResponse::PEERRESPONSE_PLAYERUTM:
      case PeerResponse::PEERRESPONSE_ROOMUTM: {
        TheLobbyQueuedUTMs.push_back(resp);
      } break;
      case PeerResponse::PEERRESPONSE_PLAYERLEFT: {
        PlayerInfo p;
        fillPlayerInfo_004F9920(&resp, &p);
        TheGameSpyInfo->playerLeftGroupRoom(resp.nick.c_str());
        shouldRepopulatePlayers = TRUE;
      } break;
      case PeerResponse::PEERRESPONSE_MESSAGE: {
        TheGameSpyInfo->addChat(resp.nick.c_str(), resp.message.profileID,
                                UnicodeString(resp.text.c_str()),
                                !resp.message.isPrivate, resp.message.isAction,
                                listboxLobbyChat);
      } break;
      case PeerResponse::PEERRESPONSE_DISCONNECT: {
        sawImportantMessage = TRUE;
        UnicodeString title, body;
        AsciiString disconMunkee;
        disconMunkee.format("GUI:GSDisconReason%d", resp.discon.reason);
        title = TheGameText->fetch("GUI:GSErrorTitle");
        body = TheGameText->fetch(disconMunkee);
        GameSpyCloseAllOverlays();
        GSMessageBoxOk(title, body);
        TheGameSpyInfo->reset();
        TheShell->pop();
        TearDownGameSpy();
      } break;
      case PeerResponse::PEERRESPONSE_CREATESTAGINGROOM: {
        sawImportantMessage = TRUE;
        SetLobbyAttemptHostJoin(FALSE);
        if (resp.createStagingRoom.result == PEERJoinSuccess) {

          buttonPushed = true;
          nextScreen = "Menus/GameSpyGameOptionsMenu.wnd";
          TheShell->pop();
          TheGameSpyInfo->markAsStagingRoomHost();
          TheGameSpyInfo->setGameOptions();
        }
      } break;
      case PeerResponse::PEERRESPONSE_JOINSTAGINGROOM: {
        sawImportantMessage = TRUE;
        SetLobbyAttemptHostJoin(FALSE);
        Bool isHostPresent = TRUE;
        if (resp.joinStagingRoom.ok == PEERTrue) {
          GameSpyStagingRoom *room = TheGameSpyInfo->getCurrentStagingRoom();
          if (!room) {
            isHostPresent = FALSE;
          } else {
            isHostPresent = FALSE;
            for (Int i = 0; i < MAX_SLOTS; ++i) {
              AsciiString hostName;
              hostName.translate(room->getConstSlot(0)->getName());
              const char *firstPlayer = resp.stagingRoomPlayerNames[i].c_str();
              char playerName[256] = {0};
              strncpy(playerName, firstPlayer, 255);
              char *suffix = strrchr(playerName, '-');
              if (suffix)
                *suffix = 0;
              if (!strcmp(hostName.str(), playerName)) {
                isHostPresent = TRUE;
              }
            }
          }
        }
        if (resp.joinStagingRoom.ok == PEERTrue && isHostPresent) {

          buttonPushed = true;
          nextScreen = "Menus/GameSpyGameOptionsMenu.wnd";
          TheShell->pop();
        } else {
          UnicodeString s;

          switch (resp.joinStagingRoom.result) {
          case PEERFullRoom:
            s = TheGameText->fetch("GUI:JoinFailedRoomFull");
            break;
          case PEERInviteOnlyRoom:
            s = TheGameText->fetch("GUI:JoinFailedInviteOnly");
            break;
          case PEERBannedFromRoom:
            s = TheGameText->fetch("GUI:JoinFailedBannedFromRoom");
            break;
          case PEERBadPassword:
            s = TheGameText->fetch("GUI:JoinFailedBadPassword");
            break;
          case PEERAlreadyInRoom:
            s = TheGameText->fetch("GUI:JoinFailedAlreadyInRoom");
            break;
          case PEERNoConnection:
            s = TheGameText->fetch("GUI:JoinFailedNoConnection");
            break;
          case Rva004FD9B0JoinResult9:
            s = TheGameText->fetch("GUI:JoinFailedGameInPlay");
            break;
          default:
            s = TheGameText->fetch("GUI:JoinFailedDefault");
            break;
          }
          GSMessageBoxOk(TheGameText->fetch("GUI:JoinFailedDefault"), s);
          if (groupRoomToJoin) {
            TheGameSpyInfo->joinGroupRoom(groupRoomToJoin);
            groupRoomToJoin = 0;
          } else {
            TheGameSpyInfo->joinBestGroupRoom();
          }
        }
      } break;
      case PeerResponse::PEERRESPONSE_STAGINGROOMLISTCOMPLETE:
        TheGameSpyInfo->sawFullGameList();
        break;
      case PeerResponse::PEERRESPONSE_STAGINGROOM: {
        GameSpyStagingRoom room;
        switch (resp.stagingRoom.action) {
        case PEER_CLEAR:
          TheGameSpyInfo->clearStagingRoomList();

          break;
        case PEER_ADD:
        case PEER_UPDATE: {
          if (resp.stagingRoom.percentComplete == 100) {
            TheGameSpyInfo->sawFullGameList();
          }

          Bool serverOk = TRUE;
          if (!resp.stagingRoomMapName.length()) {
            serverOk = FALSE;
          }

          Bool sawSelf = FALSE;

          if (rva004FD9B0AsciiEquals(TheGameSpyInfo->getLocalName(),
                                     resp.stagingRoomPlayerNames[0].c_str())) {
            sawSelf = TRUE;
          }

          if (sawSelf)
            serverOk = FALSE;

          if (serverOk) {
            room.setGameName(UnicodeString(resp.stagingServerName.c_str()));
            room.setUseStats(resp.stagingRoom.useStats);
            room.setID(resp.stagingRoom.id);
            room.setHasPassword(resp.stagingRoom.requiresPassword);
            room.setVersion(resp.stagingRoom.version);
            room.setExeCRC(resp.stagingRoom.exeCRC);
            room.setIniCRC(resp.stagingRoom.iniCRC);
            room.rva438 = resp.stagingRoom.rvaPayload18;
            room.setAllowObservers(resp.stagingRoom.allowObservers);

            room.setPingString(resp.stagingServerPingString.c_str());
            room.setLadderIP(resp.stagingServerLadderIP.c_str());
            room.setLadderPort(resp.stagingRoom.ladderPort);
            room.setReportedNumPlayers(resp.stagingRoom.numPlayers);
            room.setReportedMaxPlayers(resp.stagingRoom.maxPlayers);
            room.setReportedNumObservers(resp.stagingRoom.numObservers);

            Int i;
            AsciiString gsMapName = resp.stagingRoomMapName.c_str();
            AsciiString mapName = "";
            for (i = 0; i < gsMapName.getLength(); ++i) {
              char c = ((const StringBase<char> *)&gsMapName)->getCharAt(i);
              if (c != '/')
                ((StringBase<char> &)mapName).concat(c);
              else
                ((StringBase<char> &)mapName).concat('\\');
            }
            room.setMap(TheGameState->portableMapPathToRealMapPath(mapName));

            Int numPlayers = 0;
            for (i = 0; i < MAX_SLOTS; ++i) {
              GameSpyGameSlot *slot = room.getGameSpySlot(i);
              if (slot) {
                slot->setWins(resp.stagingRoom.wins[i]);
                slot->setLosses(resp.stagingRoom.losses[i]);
                slot->setProfileID(resp.stagingRoom.profileID[i]);
                slot->setPlayerTemplate(resp.stagingRoom.faction[i]);
                slot->setColor(resp.stagingRoom.color[i]);
                if (resp.stagingRoom.profileID[i] == SLOT_EASY_AI) {
                  slot->setState(SLOT_EASY_AI);
                  ++numPlayers;
                } else if (resp.stagingRoom.profileID[i] == SLOT_MED_AI) {
                  slot->setState(SLOT_MED_AI);
                  ++numPlayers;
                } else if (resp.stagingRoom.profileID[i] == SLOT_BRUTAL_AI) {
                  slot->setState(SLOT_BRUTAL_AI);
                  ++numPlayers;
                } else if (resp.stagingRoomPlayerNames[i].length()) {
                  UnicodeString nameUStr;
                  nameUStr.translate(resp.stagingRoomPlayerNames[i].c_str());
                  slot->setState(SLOT_PLAYER, nameUStr);
                  ++numPlayers;
                } else {
                  slot->setState(SLOT_OPEN);
                }
              }
            }
            DEBUG_ASSERTCRASH(numPlayers, ("Game had no players!\n"));

            if (resp.stagingRoom.action == PEER_ADD) {
              TheGameSpyInfo->addStagingRoom(room);

            } else {
              TheGameSpyInfo->updateStagingRoom(room);
            }
          } else {
            room.setID(resp.stagingRoom.id);
            TheGameSpyInfo->removeStagingRoom(room);
          }
          break;
        }
        case PEER_REMOVE:
          room.setID(resp.stagingRoom.id);
          TheGameSpyInfo->removeStagingRoom(room);

          break;
        default:

          break;
        }
      } break;
      }
    }
    refreshPlayerList();

    refreshGameList();
  }
}

extern GameSpyStagingRoom *TheGameSpyGame;
static GameWindow *parent, *buttonBack, *buttonHost, *buttonRefresh,
    *buttonJoin, *buttonBuddy, *buttonEmote, *textEntryChat,
    *listboxLobbyPlayers;
static int parentWOLLobbyID, buttonBackID, buttonHostID, buttonRefreshID,
    buttonJoinID, buttonBuddyID, buttonEmoteID, textEntryChatID,
    listboxLobbyPlayersID, listboxLobbyChatID, comboLobbyGroupRoomsID;
static bool DontShowMainMenu;
void playerTooltip(GameWindow *, WinInstanceData *, unsigned);
void GrabWindowInfo();
void ToggleGameListType();
void WOLLobbyMenuInit(WindowLayout *layout, void *userData) {
  nextScreen = NULL;
  buttonPushed = false;
  isShuttingDown = false;

  SetLobbyAttemptHostJoin(FALSE);

  gameListRefreshTime = 0;
  playerListRefreshTime = 0;

  parentWOLLobbyID = TheNameKeyGenerator->nameToKey(
      AsciiString("WOLCustomLobby.wnd:WOLLobbyMenuParent"));
  parent = TheWindowManager->winGetWindowFromId(NULL, parentWOLLobbyID);

  buttonBackID = TheNameKeyGenerator->nameToKey(
      AsciiString("WOLCustomLobby.wnd:ButtonBack"));
  buttonBack = TheWindowManager->winGetWindowFromId(parent, buttonBackID);

  buttonHostID = TheNameKeyGenerator->nameToKey(
      AsciiString("WOLCustomLobby.wnd:ButtonHost"));
  buttonHost = TheWindowManager->winGetWindowFromId(parent, buttonHostID);

  buttonRefreshID = TheNameKeyGenerator->nameToKey(
      AsciiString("WOLCustomLobby.wnd:ButtonRefresh"));
  buttonRefresh = TheWindowManager->winGetWindowFromId(parent, buttonRefreshID);

  buttonJoinID = TheNameKeyGenerator->nameToKey(
      AsciiString("WOLCustomLobby.wnd:ButtonJoin"));
  buttonJoin = TheWindowManager->winGetWindowFromId(parent, buttonJoinID);
  buttonJoin->winEnable(FALSE);

  buttonBuddyID = TheNameKeyGenerator->nameToKey(
      AsciiString("WOLCustomLobby.wnd:ButtonBuddy"));
  buttonBuddy = TheWindowManager->winGetWindowFromId(parent, buttonBuddyID);

  buttonEmoteID = TheNameKeyGenerator->nameToKey(
      AsciiString("WOLCustomLobby.wnd:ButtonEmote"));
  buttonEmote = TheWindowManager->winGetWindowFromId(parent, buttonEmoteID);

  textEntryChatID = TheNameKeyGenerator->nameToKey(
      AsciiString("WOLCustomLobby.wnd:TextEntryChat"));
  textEntryChat = TheWindowManager->winGetWindowFromId(parent, textEntryChatID);

  listboxLobbyPlayersID = TheNameKeyGenerator->nameToKey(
      AsciiString("WOLCustomLobby.wnd:ListboxPlayers"));
  listboxLobbyPlayers =
      TheWindowManager->winGetWindowFromId(parent, listboxLobbyPlayersID);
  listboxLobbyPlayers->winSetTooltipFunc(playerTooltip);

  listboxLobbyChatID = TheNameKeyGenerator->nameToKey(
      AsciiString("WOLCustomLobby.wnd:ListboxChat"));
  listboxLobbyChat =
      TheWindowManager->winGetWindowFromId(parent, listboxLobbyChatID);
  TheGameSpyInfo->registerTextWindow(listboxLobbyChat);

  comboLobbyGroupRoomsID = TheNameKeyGenerator->nameToKey(
      AsciiString("WOLCustomLobby.wnd:ComboBoxGroupRooms"));
  comboLobbyGroupRooms =
      TheWindowManager->winGetWindowFromId(parent, comboLobbyGroupRoomsID);

  GadgetTextEntrySetText(textEntryChat, Rva01336E54EmptyUnicode);

  populateGroupRoomListbox_004FA240(comboLobbyGroupRooms);

  ((Rva004FD9B0Layout *)layout)->hide(false);

  if (!TheGameSpyInfo->getCurrentGroupRoom()) {
    if (groupRoomToJoin) {
      TheGameSpyInfo->joinGroupRoom(groupRoomToJoin);
      groupRoomToJoin = 0;
    } else {
      TheGameSpyInfo->joinBestGroupRoom();
    }
  }

  GrabWindowInfo();

  TheGameSpyInfo->clearStagingRoomList();
  PeerRequest req;
  req.peerRequestType = PeerRequest::PEERREQUEST_STARTGAMELIST;
  req.gameList.restrictGameList = TheGameSpyConfig->restrictGamesToLobby();
  TheGameSpyPeerMessageQueue->addRequest(req);

  TheShell->showShellMap(TRUE);
  TheGameSpyGame->reset();

  CustomMatchPreferences pref;

  if (pref.usesLongGameList()) {
    ToggleGameListType();
  }

  TheWindowManager->winSetFocus(textEntryChat);
  raiseMessageBoxes = true;

  TheLobbyQueuedUTMs.clear();
  justEntered = TRUE;
  initialGadgetDelay = 2;
  GameWindow *win = TheWindowManager->winGetWindowFromId(
      NULL, TheNameKeyGenerator->nameToKey("WOLCustomLobby.wnd:GadgetParent"));
  if (win)
    win->winHide(TRUE);
  DontShowMainMenu = TRUE;
}
// PlayerTemplate+8 is m_side according to the field witness. This caller
// reads the side string by reference; the Zero Hour value-return accessor
// would introduce a copy lifetime absent from retail.
struct Rva004FA800SideView {
  int nameKey;
  UnicodeString displayName;
  AsciiString side;
};
// The real 91-byte comparison remains visible for exception analysis.
// Its independent emitted body exactly matches 00090570.
template <>
__declspec(noinline) int
StringBase<char>::compareNoCase(const StringBase<char> &other) const {
  int theirLength = other.getLength();
  const char *theirData = other.str();
  int myLength = getLength();
  const char *myData = str();
  int result = _memicmp(myData, theirData,
                        myLength < theirLength ? myLength : theirLength);
  return result ? result : myLength - theirLength;
}
void playerTooltip(GameWindow *window, WinInstanceData *instData,
                   UnsignedInt mouse) {
  Int x, y, row, col;
  x = mouse & 0xffff;
  y = mouse >> 16;

  GadgetListBoxGetEntryBasedOnXY(window, x, y, row, col);

  if (row == -1 || col == -1) {
    TheMouse->setCursorTooltip(Rva01336E54EmptyUnicode);
    return;
  }

  UnicodeString uName = GadgetListBoxGetText(window, row, 2);
  AsciiString aName;
  aName.translate(uName);

  PlayerInfo *info = TheGameSpyInfo->rva00632850Lookup(aName.str());
  if (!info)
    return;
  Bool isLocalPlayer =
      (((const StringBase<char> &)TheGameSpyInfo->getLocalName())
           .compareNoCase((const StringBase<char> &)info->baseName) == 0);

  if (col == 0) {
    if (info->preorder) {
      TheMouse->setCursorTooltip(
          TheGameText->fetch("TOOLTIP:LobbyOfficersClub"));
    } else {
      TheMouse->setCursorTooltip(Rva01336E54EmptyUnicode);
    }
    return;
  }

  AsciiString playerLocale = info->locale;
  AsciiString localeIdentifier;
  localeIdentifier.format("WOL:Locale%2.2d", atoi(playerLocale.str()));
  Int playerWins = info->wins;
  Int playerLosses = info->losses;
  UnicodeString playerInfo;
  playerInfo.format(TheGameText->fetch("TOOLTIP:PlayerInfo"),
                    TheGameText->fetch(localeIdentifier).str(), playerWins,
                    playerLosses);

  UnicodeString tooltip = Rva01336E54EmptyUnicode;
  if (isLocalPlayer) {
    tooltip.format(TheGameText->fetch("TOOLTIP:LocalPlayer"), uName.str());
  } else {

    if (TheGameSpyInfo->getBuddyMap()->find(info->profileID) !=
        TheGameSpyInfo->getBuddyMap()->end()) {

      tooltip.format(TheGameText->fetch("TOOLTIP:BuddyPlayer"), uName.str());
    } else {
      if (info->profileID) {

        tooltip.format(TheGameText->fetch("TOOLTIP:ProfiledPlayer"),
                       uName.str());
      } else {

        tooltip.format(TheGameText->fetch("TOOLTIP:GenericPlayer"),
                       uName.str());
      }
    }
  }

  if ((info->profileID && TheGameSpyInfo->isSavedIgnored(info->profileID)) ||
      TheGameSpyInfo->isIgnored(info->name)) {
    ((StringBase<unsigned short> &)tooltip)
        .concat((const StringBase<unsigned short> &)TheGameText->fetch(
            "TOOLTIP:IgnoredModifier"));
  }

  if (info->profileID) {
    ((StringBase<unsigned short> &)tooltip)
        .concat((const StringBase<unsigned short> &)playerInfo);
  }

  Int rank = 0;
  Int i = 0;
  while (info->rankPoints >= TheRankPointValues->m_ranks[i + 1])
    ++i;
  rank = i;
  AsciiString sideName = "GUI:RandomSide";
  if (info->side > 0) {
    const PlayerTemplate *fac =
        ThePlayerTemplateStore->getNthPlayerTemplate(info->side);
    if (fac) {
      sideName.format("SIDE:%s",
                      ((const Rva004FA800SideView *)fac)->side.str());
    }
  }
  AsciiString rankName;
  rankName.format("GUI:GSRank%d", rank);
  UnicodeString tmp;
  tmp.format(L"\n%ls %ls", TheGameText->fetch(sideName).str(),
             TheGameText->fetch(rankName).str());
  ((StringBase<unsigned short> &)tooltip)
      .concat((const StringBase<unsigned short> &)tmp);

  TheMouse->setCursorTooltip(tooltip, -1, NULL, 1.5f);
}
