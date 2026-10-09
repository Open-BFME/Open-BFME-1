// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Copyright 2025 Electronic Arts Inc. Licensed under GPL-3.0-or-later.
#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#include "ascii_string.h"
#include "unicode_string.h"
#include <list>
#include <map>
#include <string>
#include <string.h>
#pragma intrinsic(strcmp)
template <>
__declspec(noinline) inline int StringBase<char>::compare(const char *str) const {
 int strLen=str?(int)strlen(str):0;
 int len=m_data?m_data->length:0;
 const char *data=m_data?m_data->data:"";
 int result=memcmp(data,str,len<strLen?len:strLen);
 return result==0?len-strLen:result;
}
inline __declspec(noinline) bool operator==(const StringBase<char> &a,const char *b) { return a.compare(b)==0; }
template <> inline void StringBase<char>::concat(char c) { concat(&c, 1); }
typedef int Int;
typedef bool Bool;
typedef int Color;
const int MAX_SLOTS = 8;
class GameWindow;
extern const AsciiString Rva01336E50EmptyAscii;
inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::UnicodeString(const wchar_t *s) { ((StringBase<unsigned short>*)this)->StringBase<unsigned short>::StringBase(s); }
inline UnicodeString::UnicodeString(const UnicodeString &s) { ((StringBase<unsigned short>*)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short>*)&s); }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->releaseBuffer(); }
inline UnicodeString &UnicodeString::operator=(const UnicodeString &s) { ((StringBase<unsigned short>*)this)->set(*(const StringBase<unsigned short>*)&s); return *this; }
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
  void setState(SlotState, UnicodeString = UnicodeString::TheEmptyString,
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
// GameInfo occupies 0x58 bytes, followed by eight 0x78-byte slots.
// Unknown room words retain offset names.
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
  virtual void RvaSlot24(int);
  virtual void setCurrentGroupRoom(int);
  virtual int getCurrentGroupRoom();
  virtual void RvaSlot30(int);
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
  virtual bool sendChat(UnicodeString, bool, GameWindow *);
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

class GameSpyPeerMessageQueueInterface {
public:
#define SLOT(n) virtual void slot##n();
 SLOT(00) SLOT(04) SLOT(08) SLOT(0C) SLOT(10) SLOT(14) SLOT(18) SLOT(1C) SLOT(20)
#undef SLOT
 virtual bool getResponse(PeerResponse &);
};
class GameTextInterface {
public:
#define SLOT(n) virtual void slot##n();
 SLOT(00) SLOT(04) SLOT(08) SLOT(0C) SLOT(10) SLOT(14) SLOT(18) SLOT(1C) SLOT(20)
#undef SLOT
 virtual UnicodeString fetch(const char *, bool * = 0);
 virtual UnicodeString fetch(AsciiString, bool * = 0);
};
class Shell { public: void pop(); };
class GameState { public: AsciiString portableMapPathToRealMapPath(const AsciiString &) const; };
extern Shell *TheShell;
extern GameState *TheGameState;
extern GameTextInterface *TheGameText;
extern GameSpyInfoInterface *TheGameSpyInfo;
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
extern std::list<PeerResponse> TheLobbyQueuedUTMs;
extern int GameSpyColor[];
extern void *g_obj12F49F4;
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
void HandleBuddyResponses();
void HandlePersistentStorageResponses();
void SetLobbyAttemptHostJoin(bool);
void GameSpyCloseAllOverlays();
void GSMessageBoxOk(UnicodeString, UnicodeString, void (*)() = 0);
void TearDownGameSpy();
void RefreshGameListBoxes();
int GadgetListBoxAddEntryText(GameWindow *, UnicodeString, int, int, int, bool);
void Rva00533EA0(GameWindow *);
void Rva0052DD50CopyListRow(const struct Rva0052DD50ListSource *, struct Rva0052DD50ListRow *);
class BfmeAptScreenOnlineChat {
public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0C();
 virtual void slot10();
 virtual void Rva005351C0();
 void rva0052E990();
 void Rva005337E0();
 void Rva00534380();
 unsigned char m_prefix[0x3c];
 GameWindow *m_playersList;
 GameWindow *m_friendsList;
 unsigned char m_gap48[0xc];
 GameWindow *m_chatList;
 unsigned char m_gap58[0x9c-0x58];
 unsigned m_time9C, m_timeA0;
};

// ?Rva005351C0@BfmeAptScreenOnlineChat@@UAEXXZ
void BfmeAptScreenOnlineChat::Rva005351C0()
{
 if (TheGameSpyPeerMessageQueue) {
  HandleBuddyResponses();
  HandlePersistentStorageResponses();
  int allowedMessages=TheGameSpyInfo->getMaxMessagesPerUpdate();
  bool sawImportantMessage=false;
  PeerResponse resp;
  while (allowedMessages-- && !sawImportantMessage && TheGameSpyPeerMessageQueue->getResponse(resp)) {
   switch(resp.peerResponseType) {
   case 7:
    sawImportantMessage=true;
    if (resp.joinGroupRoom.ok) {
     TheGameSpyInfo->setCurrentGroupRoom(resp.joinGroupRoom.id);
     TheGameSpyInfo->RvaSlot30(resp.joinGroupRoom.id);
     TheGameSpyInfo->getPlayerInfoMap()->clear();
     GroupRoomMap::iterator iter=TheGameSpyInfo->getGroupRoomList()->find(resp.joinGroupRoom.id);
     if (iter != TheGameSpyInfo->getGroupRoomList()->end()) {
      UnicodeString msg;
      msg.format(TheGameText->fetch("GUI:LobbyJoined"),iter->second.m_translatedName.str());
      GadgetListBoxAddEntryText(m_chatList,msg,GameSpyColor[1],-1,-1,true);
     }
    } else {
     TheGameSpyInfo->RvaSlot24(2);
    }
    rva0052E990();
    break;
   case 14: {
    PlayerInfo p;
    Rva0052DD50CopyListRow((const Rva0052DD50ListSource*)&resp,(Rva0052DD50ListRow*)&p);
    TheGameSpyInfo->updatePlayerInfo(p);
   } break;
   case 12: {
    PlayerInfo p;
    Rva0052DD50CopyListRow((const Rva0052DD50ListSource*)&resp,(Rva0052DD50ListRow*)&p);
    TheGameSpyInfo->updatePlayerInfo(p);
   } break;
   case 13:
   case 22: {
    PlayerInfo p;
    Rva0052DD50CopyListRow((const Rva0052DD50ListSource*)&resp,(Rva0052DD50ListRow*)&p);
    TheGameSpyInfo->updatePlayerInfo(p);
   } break;
   case 10:
    if (resp.player.roomType==1) {
     PlayerInfo p;
     Rva0052DD50CopyListRow((const Rva0052DD50ListSource*)&resp,(Rva0052DD50ListRow*)&p);
     TheGameSpyInfo->updatePlayerInfo(p);
    }
    break;
   case 15:
   case 16:
    TheLobbyQueuedUTMs.push_back(resp);
    break;
   case 11: {
    PlayerInfo p;
    Rva0052DD50CopyListRow((const Rva0052DD50ListSource*)&resp,(Rva0052DD50ListRow*)&p);
    TheGameSpyInfo->playerLeftGroupRoom(resp.nick.c_str());
   } break;
   case 2:
    TheGameSpyInfo->addChat(resp.nick.c_str(),resp.message.profileID,UnicodeString(resp.text.c_str()),!resp.message.isPrivate,resp.message.isAction,m_chatList);
    break;
   case 1: {
    sawImportantMessage=true;
    UnicodeString title,body;
    AsciiString disconMunkee;
    disconMunkee.format("GUI:GSDisconReason%d",resp.discon.reason);
    title=TheGameText->fetch("GUI:GSErrorTitle");
    body=TheGameText->fetch(disconMunkee);
    GameSpyCloseAllOverlays();
    GSMessageBoxOk(title,body);
    TheGameSpyInfo->reset();
    TheShell->pop();
    TearDownGameSpy();
   } break;
   case 9: {
    sawImportantMessage=true;
    SetLobbyAttemptHostJoin(false);
    bool isHostPresent=true;
    if (resp.joinStagingRoom.ok==1) {
     GameSpyStagingRoom *room=TheGameSpyInfo->getCurrentStagingRoom();
     if (!room) isHostPresent=false;
     else {
      isHostPresent=false;
      for (int i=0;i<8;++i) {
       AsciiString hostName;
       hostName.translate(room->getConstSlot(0)->getName());
       const char *firstPlayer=resp.stagingRoomPlayerNames[i].c_str();
       if (!strcmp(hostName.str(),firstPlayer)) isHostPresent=true;
      }
     }
    }
    if (resp.joinStagingRoom.ok==1 && isHostPresent) {
    } else {
     UnicodeString s;
     switch(resp.joinStagingRoom.result) {
     case 1:s=TheGameText->fetch("GUI:JoinFailedRoomFull");break;
     case 2:s=TheGameText->fetch("GUI:JoinFailedInviteOnly");break;
     case 3:s=TheGameText->fetch("GUI:JoinFailedBannedFromRoom");break;
     case 4:s=TheGameText->fetch("GUI:JoinFailedBadPassword");break;
     case 5:s=TheGameText->fetch("GUI:JoinFailedAlreadyInRoom");break;
     case 7:s=TheGameText->fetch("GUI:JoinFailedNoConnection");break;
     default:s=TheGameText->fetch("GUI:JoinFailedDefault");break;
     }
     GSMessageBoxOk(TheGameText->fetch("GUI:JoinFailedDefault"),s);
     if (g_obj12F49F4) {
      TheGameSpyInfo->joinGroupRoom((int)g_obj12F49F4);
      g_obj12F49F4=0;
     } else TheGameSpyInfo->RvaSlot24(2);
    }
   } break;
   case 5:
    TheGameSpyInfo->sawFullGameList();
    break;
   case 4: {
    GameSpyStagingRoom room;
    switch(resp.stagingRoom.action) {
    case 3:
     TheGameSpyInfo->clearStagingRoomList();
     break;
    case 0:
    case 1: {
     if (resp.stagingRoom.percentComplete==100) TheGameSpyInfo->sawFullGameList();
     bool serverOk=true;
     if (!resp.stagingRoomMapName.length()) serverOk=false;
     bool sawSelf=false;
     if (*(const StringBase<char>*)&TheGameSpyInfo->getLocalName()==resp.stagingRoomPlayerNames[0].c_str()) sawSelf=true;
     if (sawSelf) serverOk=false;
     if (serverOk) {
      room.setGameName(UnicodeString(resp.stagingServerName.c_str()));
      room.setUseStats(resp.stagingRoom.useStats);
      room.setID(resp.stagingRoom.id);
      room.setHasPassword(resp.stagingRoom.requiresPassword);
      room.setVersion(resp.stagingRoom.version);
      room.setExeCRC(resp.stagingRoom.exeCRC);
      room.setIniCRC(resp.stagingRoom.iniCRC);
      room.rva438=resp.stagingRoom.rvaPayload18;
      room.setAllowObservers(resp.stagingRoom.allowObservers);
      room.setPingString(resp.stagingServerPingString.c_str());
      room.setLadderIP(resp.stagingServerLadderIP.c_str());
      room.setLadderPort(resp.stagingRoom.ladderPort);
      room.setReportedNumPlayers(resp.stagingRoom.numPlayers);
      room.setReportedMaxPlayers(resp.stagingRoom.maxPlayers);
      room.setReportedNumObservers(resp.stagingRoom.numObservers);
      int i;
      AsciiString gsMapName=resp.stagingRoomMapName.c_str();
      AsciiString mapName="";
      for (i=0;i<gsMapName.getLength();++i) {
       char c=((const StringBase<char>*)&gsMapName)->getCharAt(i);
       if (c!='/') ((StringBase<char>&)mapName).concat(c);
       else ((StringBase<char>&)mapName).concat('\\');
      }
      room.setMap(TheGameState->portableMapPathToRealMapPath(mapName));
      for (i=0;i<8;++i) {
       GameSpyGameSlot *slot=room.getGameSpySlot(i);
       if (slot) {
        slot->setWins(resp.stagingRoom.wins[i]);
        slot->setLosses(resp.stagingRoom.losses[i]);
        slot->setProfileID(resp.stagingRoom.profileID[i]);
        slot->setPlayerTemplate(resp.stagingRoom.faction[i]);
        slot->setColor(resp.stagingRoom.color[i]);
        if (resp.stagingRoom.profileID[i]==SLOT_EASY_AI) slot->setState(SLOT_EASY_AI);
        else if (resp.stagingRoom.profileID[i]==SLOT_MED_AI) slot->setState(SLOT_MED_AI);
        else if (resp.stagingRoom.profileID[i]==SLOT_BRUTAL_AI) slot->setState(SLOT_BRUTAL_AI);
        else if (resp.stagingRoomPlayerNames[i].length()) {
         UnicodeString nameUStr;
         nameUStr.translate(resp.stagingRoomPlayerNames[i].c_str());
         slot->setState(SLOT_PLAYER,nameUStr);
        } else slot->setState(SLOT_OPEN);
       }
      }
      if (resp.stagingRoom.action==0) TheGameSpyInfo->addStagingRoom(room);
      else TheGameSpyInfo->updateStagingRoom(room);
     } else {
      room.setID(resp.stagingRoom.id);
      TheGameSpyInfo->removeStagingRoom(room);
     }
    } break;
    case 2:
     room.setID(resp.stagingRoom.id);
     TheGameSpyInfo->removeStagingRoom(room);
     break;
    }
   } break;
   }
  }
  unsigned long (__stdcall *nowFunction)()=timeGetTime;
  if (!m_time9C || m_time9C+5000<=nowFunction()) {
   Rva005337E0();
   Rva00533EA0(m_friendsList);
   Rva00534380();
   m_time9C=nowFunction();
  }
  if (TheGameSpyInfo) {
   if (!m_timeA0 || m_timeA0+10000<=nowFunction()) {
    if (TheGameSpyInfo->hasStagingRoomListChanged()) {
     RefreshGameListBoxes();
     m_timeA0=nowFunction();
    }
   }
  }
 }
}
