// ?fillMapMask@Rva0055AE10QuickMatch@@QAEXPAURva0055AE10Request@@@Z
// partial score=0.9825 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/gamewindow /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// ?fillMapMask@Rva0055AE10QuickMatch@@QAEXPAURva0055AE10Request@@@Z
// Retail 0x0055AE10, 800 bytes: BFME Apt quick-match request map mask
// (caller _bfme_sendStartQuickMatchRequest 0x0055B200 passes the screen in
// ECX and the request on the stack). Zero Hour's QM map selection reworked:
// maps from the selected ladder (playersPerTeam*2) or the config QM list
// ((numPlayers combo + 1) * 2), MapMetaData pointers collected, partitioned
// with a 25-valued predicate, erased past the partition, std::sort, then one
// qmMaps bit per map whose m_numPlayers equals numPlayers.
// Built on the matched WOLQuickMatchMenuUpdate.cpp declarations (list,
// MapCache, config). Probe: 800/800 B, shape 1.000, 14 bytes of stack-slot
// allocation only (maps/temporary-list slots swapped; retail keeps md,
// selected and the by-value temp esp in the dead parameter home).
// LANDING BLOCKER: the out-of-line STL helpers this body calls are matched
// only under placeholder instantiations that one real std::sort/partition
// over vector<const MapMetaData*> cannot name: __introsort_loop 0x004567A0
// (int*/Q4Sort004567A0), __insertion_sort 0x00453A80 (Q3SortElem4),
// __unguarded_insertion_sort 0x00453180 (free s4uis00453180), __partition
// 0x00450B90 (Rva00450B90Item/Predicate), vector insert overflow 0x00452300
// (gen shim). They need identity corrections before this body can link.
// Native BFME quick-match update; full object-form callback at 00506720.
// Derived from WOLQuickMatchMenu.cpp; Copyright 2025 Electronic Arts Inc.,
// GPL-3.0-or-later. The original owner name is not established.
// Boundary, layout, ABI, and ownership evidence:
// targets/game/reverse/identity_evidence/00506720-quickmatch-update.md.
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
#define UnicodeString Rva00506720HeaderUnicodeString
#include "GameClient/GameWindow.h"
#include "PreRTS.h"
#undef UnicodeString
#include <list>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <time.h>

#include "Common/CustomMatchPreferences.h"
#include "Common/GameState.h"
#include "Common/NameKeyGenerator.h"
#include "Common/PlayerTemplate.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/GameText.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GameWindowTransitions.h"
#include "GameClient/Mouse.h"
#include "GameClient/Shell.h"
#include "GameClient/ShellHooks.h"
#include "GameNetwork/GameSpyOverlay.h"
#include "GameNetwork/RankPointValue.h"
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
    PEERRESPONSE_PLAYERUTM,
    PEERRESPONSE_QUICKMATCHSTATUS
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
      unsigned char ok;
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
    struct {
      int status, poolSize, mapIdx, seed;
      unsigned IP[8];
      unsigned short port[8];
      int side[8], color[8], nat[8];
    } qmStatus;
    char extent[0x23c];
  };
  PeerResponse();
  PeerResponse(const PeerResponse &);
  ~PeerResponse();
};
typedef char ResponseSize[sizeof(PeerResponse) == 0x330 ? 1 : -1];
typedef std::map<int, unsigned int> PerGeneralMap;
class PSPlayerStats {
public:
  PSPlayerStats();
  PSPlayerStats(const PSPlayerStats &);
  ~PSPlayerStats();
  PSPlayerStats &operator=(const PSPlayerStats &);
  Int id;                           // +0x000
  PerGeneralMap wins;               // +0x004
  PerGeneralMap losses;             // +0x010
  PerGeneralMap currentWinStreaks;  // +0x01c
  PerGeneralMap currentLossStreaks; // +0x028
  PerGeneralMap worstLossStreaks;   // +0x034
  PerGeneralMap bestWinStreaks;     // +0x040
  PerGeneralMap games;              // +0x04c
  PerGeneralMap duration;           // +0x058
  PerGeneralMap unitsKilled;        // +0x064
  PerGeneralMap unitsLost;          // +0x070
  PerGeneralMap unitsBuilt;         // +0x07c
  PerGeneralMap buildingsKilled;    // +0x088
  PerGeneralMap buildingsLost;      // +0x094
  PerGeneralMap buildingsBuilt;     // +0x0a0
  PerGeneralMap earnings;           // +0x0ac
  PerGeneralMap discons;            // +0x0b8
  PerGeneralMap desyncs;            // +0x0c4
  PerGeneralMap surrenders;         // +0x0d0
  PerGeneralMap gamesOf2p;          // +0x0dc
  PerGeneralMap gamesOf3p;          // +0x0e8
  PerGeneralMap gamesOf4p;          // +0x0f4
  PerGeneralMap gamesOf5p;          // +0x100
  PerGeneralMap gamesOf6p;          // +0x10c
  PerGeneralMap gamesOf7p;          // +0x118
  PerGeneralMap gamesOf8p;          // +0x124
  PerGeneralMap customGames;        // +0x130
  PerGeneralMap QMGames;            // +0x13c
  Int locale;                       // +0x148
  std::string dateCreated;          // +0x14c
  Int gamesAsRandom;                // +0x158
  std::string options;              // +0x15c
  std::string systemSpec;           // +0x168
  Real lastFPS;                     // +0x174
  Int lastSide;                     // +0x178
  Int gamesInRowWithLastSide;       // +0x17c
  Int challengeMedals;              // +0x180
  Int battleHonors;                 // +0x184
  Int winsInARow;                   // +0x188
  Int maxWinsInARow;                // +0x18c
  Int lossesInARow;                 // +0x190
  Int maxLossesInARow;              // +0x194
  Int gamesOn1_1_Ladder;            // +0x198
  Int gamesOn2_2_Ladder;            // +0x19c
  Int disconsInARow;                // +0x1a0
  Int maxDisconsInARow;             // +0x1a4
  Int desyncsInARow;                // +0x1a8
  Int maxDesyncsInARow;             // +0x1ac
  Int best1v1LadderRank;            // +0x1b0
  Int best2v2LadderRank;            // +0x1b4
  std::string lastLadderPlayed;     // +0x1b8
};

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
class GameSpyInfoInterface {
public:
  virtual void slot00();
  virtual void reset();
  virtual void slot08();
  virtual void unused_getGroupRoomList();
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
  virtual void unused_playerLeftGroupRoom();
  virtual PlayerInfoMap *getPlayerInfoMap();
  virtual void unused_rva00632850Lookup();
  virtual void slot50();
  virtual void unused_getBuddyMap();
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
  virtual void unused_addStagingRoom();
  virtual void unused_updateStagingRoom();
  virtual void unused_removeStagingRoom();
  virtual bool hasStagingRoomListChanged();
  virtual void leaveStagingRoom();
  virtual void markAsStagingRoomHost();
  virtual void slotB8();
  virtual void sawFullGameList();
  virtual void slotC0();
  virtual void *getCurrentStagingRoom();
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
  virtual bool isDisconnectedAfterGameStart(int *) const;
  virtual void markAsDisconnectedAfterGameStart(int);
  virtual void slot160();
  virtual void slot164();
  virtual void slot168();
  virtual int getMaxMessagesPerUpdate();
};
class GameSpyPeerMessageQueueInterface {
public:
  virtual void slot00();
  virtual void slot04();
  virtual void slot08();
  virtual void slot0C();
  virtual void slot10();
  virtual void slot14();
  virtual void slot18();
  virtual void slot1C();
  virtual void slot20();
  virtual bool getResponse(PeerResponse &);
};
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

#include "Common/NameKeyGenerator.h"
#include "GameClient/MessageBox.h"
#include <stdlib.h>
#include <string.h>
template <>
__declspec(noinline) int
StringBase<char>::compareNoCase(const StringBase<char> &other) const {
  int n = other.m_data ? other.m_data->length : 0;
  const char *otherData = other.m_data ? other.m_data->data : "";
  int myLen = m_data ? m_data->length : 0;
  const char *data = m_data ? m_data->data : "";
  int result = _memicmp(data, otherData, myLen < n ? myLen : n);
  if (!result)
    result = myLen - n;
  return result;
}
class GameSpyPSMessageQueueInterface {
public:
  virtual void slot00();
  virtual void slot04();
  virtual void slot08();
  virtual void slot0C();
  virtual void slot10();
  virtual void slot14();
  virtual void slot18();
  virtual void slot1C();
  virtual void trackPlayerStats(PSPlayerStats);
  virtual PSPlayerStats findPlayerStatsByID(int);
  static PSPlayerStats parsePlayerKVPairs(std::string);
};
extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;
class GameSpyConfigInterface {
public:
  virtual void slot00();
  virtual void slot04();
  virtual void slot08();
  virtual void slot0C();
  virtual void slot10();
  virtual void slot14();
  virtual std::list<AsciiString> getQMMaps();
};
extern GameSpyInfoInterface *TheGameSpyInfo;
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
extern GameSpyConfigInterface *TheGameSpyConfig;
enum SlotState {
  SLOT_OPEN,
  SLOT_CLOSED,
  SLOT_EASY_AI,
  SLOT_MED_AI,
  SLOT_BRUTAL_AI,
  SLOT_PLAYER
};

struct GameSlotConnectInfo {
  unsigned ip;
  unsigned short port;
  GameSlotConnectInfo() : ip(0), port(0) {}
};
class GameSlot {
public:
  virtual void reset();
  SlotState state;
  bool accepted, hasMap, muted;
  int color, startPos, side, team, origColor, origStart, origSide;
  UnicodeString name;
  AsciiString nameKey; // BFME transports an IP and a 16-bit port in the
                       // connection record.
  GameSlotConnectInfo connect;
  int nat;
  unsigned lastFrame;
  bool disconnected;
  void setState(SlotState, UnicodeString = Rva01336E54EmptyUnicode,
                const GameSlotConnectInfo * = &GameSlotConnectInfo());
  bool isHuman() const;
  void setIP(unsigned n) { connect.ip = n; }
  void setColor(int n) { color = n; }
  void setPlayerTemplate(int);
  void setNATBehavior(int n) { nat = n; }
  void setTeamNumber(int n) { team = n; }
};
class Rva00505D10StringOwner {
public:
  AsciiString value();
};
class Gen00505D40 {
public:
  void bfmeSet(AsciiString);
};
class GameSpyGameSlot : public GameSlot {
public:
  int profileID;
  AsciiString login, locale;
  char extra50[0x28];
  void setProfileID(int n) { profileID = n; }
};
extern void j_0001f4a6();
class GameInfo {
public:
  virtual void slot00();
  virtual void slot04();
  virtual void reset();
  char opaque04[8];
  bool inGame, inProgress;
  char opaque0E[0x2e];
  AsciiString mapName;
  unsigned crc, mapSize;
  int mapMask, seed;
  int rva50, useStats;
  void setMap(AsciiString);
  __forceinline void setSeed(int n) {
    typedef void (GameInfo::*Method)(int);
    union {
      void (*raw)();
      Method member;
    } f;
    f.raw = j_0001f4a6;
    (this->*f.member)(n);
  }
  void enterGame();
  int getSlotNum(AsciiString) const;
};
class GameSpyStagingRoom : public GameInfo {
public:
  GameSpyGameSlot slots[8];
  UnicodeString gameName;
  int id;
  void *transport;
  AsciiString localName;
  bool requiresPassword, allowObservers;
  unsigned version, exeCRC, iniCRC, rva438;
  bool quickmatch;
  int qmMode;
  AsciiString ladderIP, pingString;
  int ping;
  unsigned short ladderPort;
  int numPlayers, maxPlayers, numObservers, rva460, rva464;
  GameSpyGameSlot *getGameSpySlot(int);
  void launchGame();
  virtual void startGame(int);
  void setGameName(UnicodeString);
  void setLadderIP(AsciiString);
  void setLadderPort(unsigned short n) { ladderPort = n; }
  bool isGameInProgress() const { return inProgress; }
  __forceinline void markGameAsQM(int mode) {
    quickmatch = true;
    qmMode = mode;
  }
};
extern GameSpyStagingRoom *TheGameSpyGame;
class LadderInfo {
public:
  char opaque00[0x28];
  AsciiString address;
  unsigned short port;
};
extern void j_00021864();
class Rva005053C0Owner {
public:
  __forceinline const LadderInfo *lookup() {
    typedef const LadderInfo *(Rva005053C0Owner::*Method)();
    union {
      void (*raw)();
      Method member;
    } f;
    f.raw = j_00021864;
    return (this->*f.member)();
  }
};
extern void j_0003b746();
class Rva505C80WindowVisibilityThunk {
public:
  __forceinline void updateVisibility() {
    typedef void (Rva505C80WindowVisibilityThunk::*Method)();
    union {
      void (*raw)();
      Method member;
    } f;
    f.raw = j_0003b746;
    (this->*f.member)();
  }
};
class Rva00506720Windows {
public:
  char opaque00[0x294];
  GameWindow *textWindow;
  void *rva298;
  GameWindow *widen;
  __forceinline GameWindow *getTextWindow() const { return textWindow; }
  const LadderInfo *getLadderInfo() {
    return ((Rva005053C0Owner *)this)->lookup();
  }
};
extern Rva00506720Windows *Rva012F4820QuickMatchWindows;
#define quickmatchTextWindow (Rva012F4820QuickMatchWindows->getTextWindow())
#define buttonWiden (Rva012F4820QuickMatchWindows->widen)
#define getLadderInfo() (Rva012F4820QuickMatchWindows->getLadderInfo())
class WindowLayout;
class Rva00506720Layout {
public:
  void update(void *);
};
extern void j_00048e73();
class Rva005057C0Layout {
public:
  __forceinline void shutdownComplete() {
    typedef void (Rva005057C0Layout::*Method)();
    union {
      void (*raw)();
      Method member;
    } f;
    f.raw = j_00048e73;
    (this->*f.member)();
  }
};
static bool isShuttingDown, raiseMessageBoxes, buttonPushed;
static char *nextScreen;
static NameKeyType buttonBuddiesID;
enum NATStateType { NATSTATE_DONE = 3, NATSTATE_FAILED = 4 };
class NAT {
public:
  virtual ~NAT();
  NATStateType update();
  void processGlobalMessage(int, const char *);
};
extern NAT *TheNAT;

void HandleBuddyResponses();
void HandlePersistentStorageResponses();
void SendStatsToOtherPlayers(const GameInfo *);
void TearDownGameSpy();
class MapMetaData {
public:
  char opaque00[0x20];
  int m_numPlayers;
};
class MapCache {
public:
  const MapMetaData *findMap(AsciiString);
};
extern MapCache *TheMapCache;
class Rva00506720UI {
public:
  virtual void slot00();
  virtual void slot04();
  virtual void slot08();
  virtual void slot0C();
  virtual void slot10();
  virtual void slot14();
  virtual void slot18();
  virtual void slot1C();
  virtual void slot20();
  virtual void slot24();
  virtual void slot28();
  virtual void slot2C();
  virtual void __cdecl message(AsciiString, ...);
};
extern Rva00506720UI *TheInGameUI;
enum QMStatus {
  QM_IDLE,
  QM_JOININGQMCHANNEL,
  QM_LOOKINGFORBOT,
  QM_SENTINFO,
  QM_WORKING,
  QM_POOLSIZE,
  QM_WIDENINGSEARCH,
  QM_MATCHED,
  QM_INCHANNEL,
  QM_NEGOTIATINGFIREWALLS,
  QM_STARTINGGAME,
  QM_COULDNOTFINDBOT,
  QM_COULDNOTFINDCHANNEL,
  QM_COULDNOTNEGOTIATEFIREWALLS,
  QM_STOPPED
};
// ECX is the layout; the single stack argument is unused (ret 4).

// Retail 0x0055AE10 (800 bytes): fills the quick-match request's map mask
// for BFME's Apt quick-match screen (caller _bfme_sendStartQuickMatchRequest,
// 0x0055B200, passes the screen in ECX and the request on the stack).
class Rva0055AE10LadderInfo {
public:
  char opaque00[0x0c];
  int playersPerTeam;
  char opaque10[0x0c];
  std::list<AsciiString> validMaps;
};
class LadderList {
public:
  const Rva0055AE10LadderInfo *findLadderByIndex(int index);
};
extern LadderList *TheLadderList;
void GadgetComboBoxGetSelectedPos(GameWindow *combo, int *selected);
void *GadgetComboBoxGetItemData(GameWindow *combo, int selected);

struct Rva0055AE10Request {
  char opaque000[0xd0];
  std::vector<bool> qmMaps;
};

struct Rva0055AE10MapPredicate {
  int value;
  Rva0055AE10MapPredicate(int v) : value(v) {}
  bool operator()(const MapMetaData *md) const;
};
struct Rva0055AE10MapCompare {
  bool operator()(const MapMetaData *a, const MapMetaData *b) const;
};

class Rva0055AE10QuickMatch {
public:
  void fillMapMask(Rva0055AE10Request *req);

private:
  char opaque00[0x60];
  GameWindow *numPlayersCombo;
  char opaque64[0x08];
  GameWindow *ladderCombo;
};

void Rva0055AE10QuickMatch::fillMapMask(Rva0055AE10Request *req) {
  req->qmMaps.clear();

  std::list<AsciiString> maps;
  int selected;
  GadgetComboBoxGetSelectedPos(ladderCombo, &selected);
  int index = (int)GadgetComboBoxGetItemData(ladderCombo, selected);
  const Rva0055AE10LadderInfo *li = TheLadderList->findLadderByIndex(index);
  int numPlayers;
  if (li) {
    numPlayers = li->playersPerTeam * 2;
    maps = li->validMaps;
  } else {
    selected = 0;
    GadgetComboBoxGetSelectedPos(numPlayersCombo, &selected);
    if (selected < 0)
      selected = 0;
    numPlayers = (selected + 1) * 2;
    maps = TheGameSpyConfig->getQMMaps();
  }

  std::vector<const MapMetaData *> validMaps;
  for (std::list<AsciiString>::const_iterator it = maps.begin();
       it != maps.end(); ++it) {
    const MapMetaData *md = TheMapCache->findMap(*it);
    if (md)
      validMaps.push_back(md);
  }
  validMaps.erase(std::partition(validMaps.begin(), validMaps.end(),
                                 Rva0055AE10MapPredicate(25)),
                  validMaps.end());
  std::sort(validMaps.begin(), validMaps.end(), Rva0055AE10MapCompare());

  for (std::vector<const MapMetaData *>::iterator mit = validMaps.begin();
       mit != validMaps.end(); ++mit) {
    if ((*mit)->m_numPlayers == numPlayers)
      req->qmMaps.push_back(true);
  }
}
