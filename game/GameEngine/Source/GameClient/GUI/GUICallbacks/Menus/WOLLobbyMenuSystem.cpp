// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/gamewindow /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Native WOLLobbyMenuSystem, RVA 004FC7C0, 3452 bytes including switch tables.
// Derived from WOLLobbyMenu.cpp; Copyright 2025 Electronic Arts Inc.,
// GPL-3.0-or-later. Identity, helper ABI and BFME layout evidence:
// targets/game/reverse/identity_evidence/004fc7c0-lobby-system.md.
#define __PLACEMENT_VEC_NEW_INLINE
#define ASCIISTRING_H
#define UNICODESTRING_H
#include "ascii_string.h"
#include "unicode_string.h"

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
#define UnicodeString Rva004FC7C0HeaderUnicodeString
#include "GameClient/GameWindow.h"
#include "PreRTS.h"
#undef UnicodeString
#include <list>
#include <map>
#include <string>
#include <time.h>

#include "Common/NameKeyGenerator.h"
#include <vector>
const int MAX_SLOTS = 8;
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
class GameInfo {
public:
  int getNumPlayers() const;
};
class GameSpyStagingRoom : public GameInfo {
public:
  char opaque00[0x428];
  bool hasPassword;
  char opaque429[7];
  unsigned rva430, rva434, rva438;
  char opaque43c[0x14];
  unsigned short ladderPort;
  unsigned short getLadderPort() { return ladderPort; }
  void setLadderPort(unsigned short p) { ladderPort = p; }
  bool getHasPassword() { return hasPassword; }
  AsciiString getLadderIP() const;
  UnicodeString getGameName();
  void setGameName(UnicodeString);
  void setLadderIP(AsciiString);
};
typedef std::map<int, GameSpyStagingRoom *> StagingRoomMap;
class PlayerInfo {
public:
  AsciiString name, baseName, unused;
  int at0C, at10, profileID;
  char tail[28];
};
struct AsciiComparator {
  bool operator()(AsciiString, AsciiString) const;
};
typedef std::map<AsciiString, PlayerInfo, AsciiComparator> PlayerInfoMap;
class GameSpyInfoInterface {
public:
  virtual void slot00() = 0;
  virtual void slot04() = 0;
  virtual void slot08() = 0;
  virtual void slot0C() = 0;
  virtual void slot10() = 0;
  virtual void slot14() = 0;
  virtual void joinGroupRoom(int) = 0;
  virtual void leaveGroupRoom() = 0;
  virtual void slot20() = 0;
  virtual void slot24() = 0;
  virtual void slot28() = 0;
  virtual int getCurrentGroupRoom() = 0;
  virtual void slot30() = 0;
  virtual void slot34() = 0;
  virtual void slot38() = 0;
  virtual void slot3C() = 0;
  virtual void slot40() = 0;
  virtual void slot44() = 0;
  virtual PlayerInfoMap *getPlayerInfoMap() = 0;
  virtual const AsciiString *rva4C(const char *) = 0;
  virtual void slot50() = 0;
  virtual void slot54() = 0;
  virtual void slot58() = 0;
  virtual void slot5C() = 0;
  virtual bool isBuddy(int) = 0;
  virtual void slot64() = 0;
  virtual void slot68() = 0;
  virtual void slot6C() = 0;
  virtual int getLocalProfileID() = 0;
  virtual void slot74() = 0;
  virtual void slot78() = 0;
  virtual void slot7C() = 0;
  virtual void slot80() = 0;
  virtual void slot84() = 0;
  virtual void slot88() = 0;
  virtual void slot8C() = 0;
  virtual void slot90() = 0;
  virtual void clearStagingRoomList() = 0;
  virtual StagingRoomMap *getStagingRoomList() = 0;
  virtual void slot9C() = 0;
  virtual void slotA0() = 0;
  virtual void slotA4() = 0;
  virtual void slotA8() = 0;
  virtual bool rvaAC() = 0;
  virtual void slotB0() = 0;
  virtual void slotB4() = 0;
  virtual void markAsStagingRoomJoiner(int) = 0;
  virtual void slotBC() = 0;
  virtual void slotC0() = 0;
  virtual void slotC4() = 0;
  virtual void slotC8() = 0;
  virtual void slotCC() = 0;
  virtual void slotD0() = 0;
  virtual void slotD4() = 0;
  virtual void slotD8() = 0;
  virtual void slotDC() = 0;
  virtual void slotE0() = 0;
  virtual void slotE4() = 0;
  virtual void slotE8() = 0;
  virtual void slotEC() = 0;
  virtual void slotF0() = 0;
  virtual void slotF4() = 0;
  virtual void sendChat(UnicodeString, bool, GameWindow *) = 0;
};
class GameSpyPeerMessageQueueInterface {
public:
  virtual void slot00() = 0;
  virtual void slot04() = 0;
  virtual void slot08() = 0;
  virtual void slot0C() = 0;
  virtual void slot10() = 0;
  virtual void slot14() = 0;
  virtual void addRequest(const PeerRequest &) = 0;
};
class GameSpyConfigInterface {
public:
  virtual void slot00() = 0;
  virtual void slot04() = 0;
  virtual void slot08() = 0;
  virtual void slot0C() = 0;
  virtual void slot10() = 0;
  virtual void slot14() = 0;
  virtual void slot18() = 0;
  virtual void slot1C() = 0;
  virtual void slot20() = 0;
  virtual void slot24() = 0;
  virtual void slot28() = 0;
  virtual void slot2C() = 0;
  virtual void slot30() = 0;
  virtual void slot34() = 0;
  virtual bool restrictGamesToLobby() = 0;
};
class Rva004FC7C0Client {
public:
  virtual void slot00() = 0;
  virtual void slot04() = 0;
  virtual void slot08() = 0;
  virtual void slot0C() = 0;
  virtual void slot10() = 0;
  virtual void slot14() = 0;
  virtual void slot18() = 0;
  virtual void slot1C() = 0;
  virtual void slot20() = 0;
  virtual void slot24() = 0;
  virtual void slot28() = 0;
  virtual void slot2C() = 0;
  virtual void slot30() = 0;
  virtual void slot34() = 0;
  virtual void slot38() = 0;
  virtual void slot3C() = 0;
  virtual void slot40() = 0;
  virtual void slot44() = 0;
  virtual void slot48() = 0;
  virtual void slot4C() = 0;
  virtual void slot50() = 0;
  virtual void slot54() = 0;
  virtual void slot58() = 0;
  virtual void slot5C() = 0;
  virtual void slot60() = 0;
  virtual void slot64() = 0;
  virtual unsigned int getFrame() = 0;
};
class GameTextInterface {
public:
  virtual void slot00() = 0;
  virtual void slot04() = 0;
  virtual void slot08() = 0;
  virtual void slot0C() = 0;
  virtual void slot10() = 0;
  virtual void slot14() = 0;
  virtual void slot18() = 0;
  virtual void slot1C() = 0;
  virtual void slot20() = 0;
  virtual UnicodeString fetch(const char *, bool * = 0) = 0;
  virtual UnicodeString fetch(AsciiString, bool * = 0) = 0;
};

struct RightClickStruct {
  int mouseX, mouseY, pos;
};
typedef int RCItemType;
class GameSpyRCMenuData {
public:
  AsciiString m_nick;
  int m_id;
  RCItemType m_itemType;
};
struct Rva004FC7C0LayoutView {
  virtual void runInit(void * = 0) = 0;
  int opaque04;
  GameWindow *first;
  GameWindow *getFirstWindow() { return first; }
};
class Rva004FC7C0WindowManager {
public:
  virtual void slot00() = 0;
  virtual void slot04() = 0;
  virtual void slot08() = 0;
  virtual void slot0C() = 0;
  virtual void slot10() = 0;
  virtual void slot14() = 0;
  virtual void slot18() = 0;
  virtual void slot1C() = 0;
  virtual void slot20() = 0;
  virtual void slot24() = 0;
  virtual void slot28() = 0;
  virtual void slot2C() = 0;
  virtual void slot30() = 0;
  virtual void slot34() = 0;
  virtual void slot38() = 0;
  virtual void slot3C() = 0;
  virtual void slot40() = 0;
  virtual void slot44() = 0;
  virtual void slot48() = 0;
  virtual void slot4C() = 0;
  virtual void slot50() = 0;
  virtual void slot54() = 0;
  virtual void slot58() = 0;
  virtual void slot5C() = 0;
  virtual void slot60() = 0;
  virtual void slot64() = 0;
  virtual void slot68() = 0;
  virtual WindowLayout *winCreateLayout(AsciiString) = 0;
  virtual void slot70() = 0;
  virtual void slot74() = 0;
  virtual void slot78() = 0;
  virtual void slot7C() = 0;
  virtual void slot80() = 0;
  virtual void slot84() = 0;
  virtual void slot88() = 0;
  virtual void slot8C() = 0;
  virtual void slot90() = 0;
  virtual void slot94() = 0;
  virtual void slot98() = 0;
  virtual void slot9C() = 0;
  virtual void slotA0() = 0;
  virtual void slotA4() = 0;
  virtual void slotA8() = 0;
  virtual void slotAC() = 0;
  virtual void slotB0() = 0;
  virtual void slotB4() = 0;
  virtual void slotB8() = 0;
  virtual void winSetLoneWindow(GameWindow *) = 0;
  virtual void slotC0() = 0;
  virtual void slotC4() = 0;
  virtual void slotC8() = 0;
  virtual void slotCC() = 0;
  virtual void slotD0() = 0;
  virtual int winSendSystemMsg(GameWindow *, unsigned, unsigned, unsigned) = 0;
  virtual void slotD8() = 0;
  virtual GameWindow *winGetWindowFromId(GameWindow *, int) = 0;
};
extern Rva004FC7C0WindowManager *TheWindowManager;
class Rva004FC7C0Display {
public:
  virtual void slot00() = 0;
  virtual void slot04() = 0;
  virtual void slot08() = 0;
  virtual void slot0C() = 0;
  virtual void slot10() = 0;
  virtual void slot14() = 0;
  virtual void slot18() = 0;
  virtual void slot1C() = 0;
  virtual void slot20() = 0;
  virtual void slot24() = 0;
  virtual void slot28() = 0;
  virtual unsigned int getWidth() = 0;
  virtual unsigned int getHeight() = 0;
};
extern Rva004FC7C0Display *TheDisplay;

extern GameSpyInfoInterface *TheGameSpyInfo;
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
extern GameTextInterface *TheGameText;
class GameClient;
extern GameClient *TheGameClient;
extern GameSpyConfigInterface *TheGameSpyConfig;
extern GameSpyStagingRoom *TheGameSpyGame;
struct Rva004FC7C0Global {
  char opaque00[0xbc8];
  unsigned atBC8, atBCC, atBD0, atBD4;
};
#define TheWritableGlobalData ((Rva004FC7C0Global *)TheWritableGlobalData)
extern const UnicodeString Rva01336E54EmptyUnicode;
int Rva0009B4B0(int, int);

class Shell {
public:
  void pop();
};
extern Shell *TheShell;
class LadderInfo;
class LadderList {
public:
  const LadderInfo *findLadder(const AsciiString &, unsigned short);
};
extern LadderList *TheLadderList;
class PeerResponse {
public:
  ~PeerResponse();
  char opaque00[0x330];
};
extern std::list<PeerResponse> TheLobbyQueuedUTMs;
enum GSOverlayType {
  GSOVERLAY_BUDDY = 2,
  GSOVERLAY_GAMEOPTIONS = 4,
  GSOVERLAY_GAMEPASSWORD = 5
};
void GameSpyOpenOverlay(GSOverlayType);
void GameSpyToggleOverlay(GSOverlayType);
void GSMessageBoxOk(UnicodeString, UnicodeString, void (*)(void) = 0);
void GadgetListBoxGetSelected(GameWindow *, int *);
void *GadgetListBoxGetItemData(GameWindow *, int, int = 0);
void GadgetListBoxSetSelected(GameWindow *, int);
UnicodeString GadgetListBoxGetText(GameWindow *, int, int = 0);
UnicodeString GadgetTextEntryGetText(GameWindow *);
void GadgetTextEntrySetText(GameWindow *, UnicodeString);
void GadgetComboBoxGetSelectedPos(GameWindow *, int *);
void *GadgetComboBoxGetItemData(GameWindow *, int);
void setUnignoreText(WindowLayout *, AsciiString, int);
GameWindow *GetGameListBox();
GameWindow *GetGameInfoListBox();
NameKeyType GetGameListBoxID();
bool HandleSortButton(NameKeyType);
void RefreshGameInfoListBox(GameWindow *, GameWindow *);
void RefreshGameListBoxes();
void PopulateLobbyPlayerListbox();
void ToggleGameListType();
bool handleLobbySlashCommands(UnicodeString);
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
static bool buttonPushed, s_tryingToHostOrJoin;
static char *nextScreen;
static int groupRoomToJoin, gameListRefreshTime, playerListRefreshTime;
static int buttonBackID, buttonRefreshID, buttonHostID, buttonJoinID,
    buttonBuddyID, buttonEmoteID, comboLobbyGroupRoomsID, listboxLobbyPlayersID;
static GameWindow *buttonJoin, *textEntryChat, *listboxLobbyPlayers,
    *comboLobbyGroupRooms;
inline void SetLobbyAttemptHostJoin(bool b) { s_tryingToHostOrJoin = b; }
__forceinline void refreshGameList(bool) {
  if (TheGameSpyInfo->rvaAC()) {
    RefreshGameListBoxes();
    gameListRefreshTime = timeGetTime();
  }
}
__forceinline void refreshPlayerList(bool) {
  PopulateLobbyPlayerListbox();
  playerListRefreshTime = timeGetTime();
}
const unsigned GLM_SELECTED = 0x4014, GLM_DOUBLE_CLICKED = 0x4015,
               GLM_RIGHT_CLICKED = 0x4016, GCM_SELECTED = 0x4025,
               GEM_EDIT_DONE = 0x4030, GBM_SELECTED = 0x4008;
const int ITEM_BUDDY = 0, ITEM_NONBUDDY = 2, COLUMN_PLAYERNAME = 2;
typedef int GPProfile;
WindowMsgHandledType WOLLobbyMenuSystem(GameWindow *window, UnsignedInt msg,
                                        WindowMsgData mData1,
                                        WindowMsgData mData2) {
  UnicodeString txtInput;
  static NameKeyType buttonGameListTypeToggleID = NAMEKEY_INVALID;
  switch (msg) {
  case GWM_CREATE: {
    buttonGameListTypeToggleID =
        NAMEKEY("WOLCustomLobby.wnd:ButtonGameListToggle");
    break;
  }
  case GWM_DESTROY: {
    break;
  }
  case GWM_INPUT_FOCUS: {
    if (mData1 == TRUE)
      *(Bool *)mData2 = TRUE;
    return MSG_HANDLED;
  }
  case GLM_SELECTED: {
    GameWindow *control = (GameWindow *)mData1;
    Int controlID = control->winGetWindowId();
    if (controlID == GetGameListBoxID()) {
      int rowSelected = mData2;
      if (rowSelected >= 0) {
        buttonJoin->winEnable(TRUE);
        static UnsignedInt lastFrame = 0;
        static Int lastID = -1;
        UnsignedInt now = ((Rva004FC7C0Client *)TheGameClient)->getFrame();
        PeerRequest req;
        req.peerRequestType =
            PeerRequest::PEERREQUEST_GETEXTENDEDSTAGINGROOMINFO;
        req.stagingRoom.id =
            (Int)GadgetListBoxGetItemData(control, rowSelected, 0);
        if (lastID != req.stagingRoom.id || now > lastFrame + 60) {
          TheGameSpyPeerMessageQueue->addRequest(req);
        }
        lastID = req.stagingRoom.id;
        lastFrame = now;
      } else {
        buttonJoin->winEnable(FALSE);
      }
      if (GetGameInfoListBox()) {
        RefreshGameInfoListBox(GetGameListBox(), GetGameInfoListBox());
      }
    }
    break;
  }
  case GBM_SELECTED: {
    if (buttonPushed)
      break;
    GameWindow *control = (GameWindow *)mData1;
    Int controlID = control->winGetWindowId();
    if (HandleSortButton((NameKeyType)controlID))
      break;
    if (controlID == buttonBackID) {
      if (s_tryingToHostOrJoin)
        break;
      TheGameSpyInfo->leaveGroupRoom();
      SetLobbyAttemptHostJoin(TRUE);
      buttonPushed = true;
      nextScreen = "Menus/WOLWelcomeMenu.wnd";
      TheShell->pop();
    } else if (controlID == buttonRefreshID) {
      refreshGameList(TRUE);
      refreshPlayerList(TRUE);
    } else if (controlID == buttonHostID) {
      if (s_tryingToHostOrJoin)
        break;
      SetLobbyAttemptHostJoin(TRUE);
      TheLobbyQueuedUTMs.clear();
      groupRoomToJoin = TheGameSpyInfo->getCurrentGroupRoom();
      GameSpyOpenOverlay(GSOVERLAY_GAMEOPTIONS);
    } else if (controlID == buttonJoinID) {
      if (s_tryingToHostOrJoin)
        break;
      TheLobbyQueuedUTMs.clear();
      groupRoomToJoin = TheGameSpyInfo->getCurrentGroupRoom();
      Int selected;
      GadgetListBoxGetSelected(GetGameListBox(), &selected);
      if (selected >= 0) {
        Int selectedID =
            (Int)GadgetListBoxGetItemData(GetGameListBox(), selected);
        if (selectedID > 0) {
          StagingRoomMap *srm = TheGameSpyInfo->getStagingRoomList();
          StagingRoomMap::iterator srmIt = srm->find(selectedID);
          if (srmIt != srm->end()) {
            GameSpyStagingRoom *roomToJoin = srmIt->second;
            unsigned roomCrc;
            bool first = roomToJoin &&
                         ((roomCrc = roomToJoin->rva430),
                          roomCrc == Rva0009B4B0(TheWritableGlobalData->atBD0,
                                                 TheWritableGlobalData->atBD0));
            unsigned roomSecond;
            bool second =
                roomToJoin && ((roomSecond = roomToJoin->rva434),
                               roomSecond == TheWritableGlobalData->atBC8);
            unsigned roomThird;
            bool third =
                roomToJoin && ((roomThird = roomToJoin->rva438),
                               roomThird == TheWritableGlobalData->atBD4);
            if (!first || !second || !third) {
              GSMessageBoxOk(TheGameText->fetch("GUI:JoinFailedDefault"),
                             TheGameText->fetch("GUI:JoinFailedCRCMismatch"));
              break;
            }
            Bool unknownLadder = (roomToJoin->getLadderPort() &&
                                  TheLadderList->findLadder(
                                      roomToJoin->getLadderIP(),
                                      roomToJoin->getLadderPort()) == NULL);
            if (unknownLadder) {
              GSMessageBoxOk(TheGameText->fetch("GUI:JoinFailedDefault"),
                             TheGameText->fetch("GUI:JoinFailedUnknownLadder"));
              break;
            }
            if (roomToJoin->getNumPlayers() == MAX_SLOTS) {
              GSMessageBoxOk(TheGameText->fetch("GUI:JoinFailedDefault"),
                             TheGameText->fetch("GUI:JoinFailedRoomFull"));
              break;
            }
            TheGameSpyInfo->markAsStagingRoomJoiner(selectedID);
            TheGameSpyGame->setGameName(roomToJoin->getGameName());
            TheGameSpyGame->setLadderIP(roomToJoin->getLadderIP());
            TheGameSpyGame->setLadderPort(roomToJoin->getLadderPort());
            SetLobbyAttemptHostJoin(TRUE);
            if (roomToJoin->getHasPassword()) {
              GameSpyOpenOverlay(GSOVERLAY_GAMEPASSWORD);
            } else {
              PeerRequest req;
              req.peerRequestType = PeerRequest::PEERREQUEST_JOINSTAGINGROOM;
              req.text = srmIt->second->getGameName().str();
              req.stagingRoom.id = selectedID;
              req.password = "";
              TheGameSpyPeerMessageQueue->addRequest(req);
            }
          }
        } else {
          GSMessageBoxOk(TheGameText->fetch("GUI:Error"),
                         TheGameText->fetch("GUI:NoGameInfo"), NULL);
        }
      } else {
        GSMessageBoxOk(TheGameText->fetch("GUI:Error"),
                       TheGameText->fetch("GUI:NoGameSelected"), NULL);
      }
    } else if (controlID == buttonBuddyID) {
      GameSpyToggleOverlay(GSOVERLAY_BUDDY);
    } else if (controlID == buttonGameListTypeToggleID) {
      ToggleGameListType();
    } else if (controlID == buttonEmoteID) {
      UnicodeString txtInput;
      txtInput = GadgetTextEntryGetText(textEntryChat);
      GadgetTextEntrySetText(textEntryChat, Rva01336E54EmptyUnicode);
      ((StringBase<unsigned short> *)&txtInput)->trim();
      if (!txtInput.isEmpty()) {
        TheGameSpyInfo->sendChat(txtInput, FALSE, listboxLobbyPlayers);
      }
    }
    break;
  }
  case GCM_SELECTED: {
    if (s_tryingToHostOrJoin)
      break;
    GameWindow *control = (GameWindow *)mData1;
    Int controlID = control->winGetWindowId();
    if (controlID == comboLobbyGroupRoomsID) {
      int rowSelected = -1;
      GadgetComboBoxGetSelectedPos(control, &rowSelected);
      if (rowSelected >= 0) {
        Int groupID;
        groupID =
            (Int)GadgetComboBoxGetItemData(comboLobbyGroupRooms, rowSelected);
        if (groupID && groupID != TheGameSpyInfo->getCurrentGroupRoom()) {
          TheGameSpyInfo->leaveGroupRoom();
          TheGameSpyInfo->joinGroupRoom(groupID);
          if (TheGameSpyConfig->restrictGamesToLobby()) {
            TheGameSpyInfo->clearStagingRoomList();
            RefreshGameListBoxes();
            PeerRequest req;
            req.peerRequestType = PeerRequest::PEERREQUEST_STARTGAMELIST;
            req.gameList.restrictGameList = TRUE;
            TheGameSpyPeerMessageQueue->addRequest(req);
          }
        }
      }
    }
  } break;
  case GLM_DOUBLE_CLICKED: {
    if (buttonPushed)
      break;
    GameWindow *control = (GameWindow *)mData1;
    Int controlID = control->winGetWindowId();
    if (controlID == GetGameListBoxID()) {
      int rowSelected = mData2;
      if (rowSelected >= 0) {
        GadgetListBoxSetSelected(control, rowSelected);
        GameWindow *button =
            TheWindowManager->winGetWindowFromId(window, buttonJoinID);
        TheWindowManager->winSendSystemMsg(window, GBM_SELECTED,
                                           (WindowMsgData)button, buttonJoinID);
      }
    }
    break;
  }
  case GLM_RIGHT_CLICKED: {
    GameWindow *control = (GameWindow *)mData1;
    Int controlID = control->winGetWindowId();
    if (controlID == listboxLobbyPlayersID) {
      RightClickStruct *rc = (RightClickStruct *)mData2;
      WindowLayout *rcLayout = NULL;
      GameWindow *rcMenu;
      if (rc->pos < 0) {
        GadgetListBoxSetSelected(control, -1);
        break;
      }
      GPProfile profileID = 0;
      AsciiString aName;
      aName.translate(
          GadgetListBoxGetText(control, rc->pos, COLUMN_PLAYERNAME));
      const AsciiString *key = TheGameSpyInfo->rva4C(aName.str());
      if (key) {
        PlayerInfoMap::iterator it =
            TheGameSpyInfo->getPlayerInfoMap()->find(*key);
        if (it != TheGameSpyInfo->getPlayerInfoMap()->end())
          profileID = it->second.profileID;
      }
      Bool isBuddy = FALSE;
      if (profileID <= 0)
        rcLayout = TheWindowManager->winCreateLayout(
            AsciiString("Menus/RCNoProfileMenu.wnd"));
      else {
        if (profileID == TheGameSpyInfo->getLocalProfileID()) {
          rcLayout = TheWindowManager->winCreateLayout(
              AsciiString("Menus/RCLocalPlayerMenu.wnd"));
        } else if (TheGameSpyInfo->isBuddy(profileID)) {
          rcLayout = TheWindowManager->winCreateLayout(
              AsciiString("Menus/RCBuddiesMenu.wnd"));
          isBuddy = TRUE;
        } else
          rcLayout = TheWindowManager->winCreateLayout(
              AsciiString("Menus/RCNonBuddiesMenu.wnd"));
      }
      if (!rcLayout)
        break;
      GadgetListBoxSetSelected(control, rc->pos);
      rcMenu = ((Rva004FC7C0LayoutView *)rcLayout)->getFirstWindow();
      ((Rva004FC7C0LayoutView *)rcMenu->winGetLayout())->runInit();
      rcMenu->winBringToTop();
      rcMenu->winHide(FALSE);
      setUnignoreText(rcLayout, aName, profileID);
      ICoord2D rcSize, rcPos;
      rcMenu->winGetSize(&rcSize.x, &rcSize.y);
      rcPos.x = rc->mouseX;
      rcPos.y = rc->mouseY;
      if (rc->mouseX + rcSize.x > TheDisplay->getWidth())
        rcPos.x = TheDisplay->getWidth() - rcSize.x;
      if (rc->mouseY + rcSize.y > TheDisplay->getHeight())
        rcPos.y = TheDisplay->getHeight() - rcSize.y;
      rcMenu->winSetPosition(rcPos.x, rcPos.y);
      GameSpyRCMenuData *rcData = new GameSpyRCMenuData;
      rcData->m_id = profileID;
      rcData->m_nick = aName;
      rcData->m_itemType = (isBuddy) ? ITEM_BUDDY : ITEM_NONBUDDY;
      rcMenu->winSetUserData((void *)rcData);
      TheWindowManager->winSetLoneWindow(rcMenu);
    } else if (controlID == GetGameListBoxID()) {
      RightClickStruct *rc = (RightClickStruct *)mData2;
      WindowLayout *rcLayout = NULL;
      GameWindow *rcMenu;
      if (rc->pos < 0) {
        GadgetListBoxSetSelected(control, -1);
        break;
      }
      Int selectedID = (Int)GadgetListBoxGetItemData(control, rc->pos);
      if (selectedID > 0) {
        StagingRoomMap *srm = TheGameSpyInfo->getStagingRoomList();
        StagingRoomMap::iterator srmIt = srm->find(selectedID);
        if (srmIt != srm->end()) {
          GameSpyStagingRoom *theRoom = srmIt->second;
          if (!theRoom)
            break;
          const LadderInfo *linfo = TheLadderList->findLadder(
              theRoom->getLadderIP(), theRoom->getLadderPort());
          if (linfo) {
            rcLayout = TheWindowManager->winCreateLayout(
                AsciiString("Menus/RCGameDetailsMenu.wnd"));
            if (!rcLayout)
              break;
            GadgetListBoxSetSelected(control, rc->pos);
            rcMenu = ((Rva004FC7C0LayoutView *)rcLayout)->getFirstWindow();
            ((Rva004FC7C0LayoutView *)rcMenu->winGetLayout())->runInit();
            rcMenu->winBringToTop();
            rcMenu->winHide(FALSE);
            rcMenu->winSetPosition(rc->mouseX, rc->mouseY);
            rcMenu->winSetUserData((void *)selectedID);
            TheWindowManager->winSetLoneWindow(rcMenu);
          }
        }
      }
    }
    break;
  }
  case GEM_EDIT_DONE: {
    if (buttonPushed)
      break;
    UnicodeString txtInput;
    txtInput = GadgetTextEntryGetText(textEntryChat);
    GadgetTextEntrySetText(textEntryChat, Rva01336E54EmptyUnicode);
    ((StringBase<unsigned short> *)&txtInput)->trim();
    if (!txtInput.isEmpty()) {
      if (!handleLobbySlashCommands(txtInput)) {
        TheGameSpyInfo->sendChat(txtInput, false, listboxLobbyPlayers);
      }
    }
    break;
  }
  default:
    return MSG_IGNORED;
  }
  return MSG_HANDLED;
}
