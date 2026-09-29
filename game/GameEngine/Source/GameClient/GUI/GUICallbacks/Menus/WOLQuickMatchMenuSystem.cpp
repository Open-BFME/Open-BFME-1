// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/gamewindow /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Native BFME quick-match system handler, 0050A470 / 1177 bytes.
// Derived from WOLQuickMatchMenu.cpp; Copyright 2025 Electronic Arts Inc.,
// GPL-3.0-or-later. Identity, ABI, and layout evidence:
// targets/game/reverse/identity_evidence/0050a470-quickmatch-system.md.
#define _STLP_NO_EXCEPTIONS 1
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
#define UnicodeString Rva0050A470HeaderUnicodeString
#include "GameClient/GameWindow.h"

#include "PreRTS.h"
#undef UnicodeString
#include "Common/QuickmatchPreferences.h"
#include "PreRTS.h"

#include "GameClient/Gadget.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/Image.h"
#include "GameNetwork/GameSpy/LadderDefs.h"
const int GSCOLOR_MAP_SELECTED = 25;
const int GSCOLOR_MAP_UNSELECTED = 26;
#include "GameNetwork/GameSpyOverlay.h"

static Bool rva012F4801ButtonPushed;
static bool rva012F4814, rva012F4809;
static Int rva012F47F8BuddiesId;
class Image;
extern const Image *rva012F480CSelectedImage, *rva012F4810UnselectedImage;

class Gen_00505530 {
public:
  void bfmeSet(void *, int);
};
class Gen_00505550 {
public:
  void bfmeSet(void *, int);
};
class PeerRequest {
public:
  PeerRequest();
  ~PeerRequest();
  int peerRequestType;
  char m_bfmeBody[0x190];
};

class GameSpyPeerMessageQueueInterface {
public:
  virtual ~GameSpyPeerMessageQueueInterface() {}
  virtual void startThread();
  virtual void endThread();
  virtual int isThreadRunning();
  virtual int isConnected();
  virtual int isConnecting();
  virtual void addRequest(const PeerRequest &request);
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
extern Color GameSpyColor[];

class BfmeAptScreenQuickMatchMenu {
public:
  void populateQuickMatchMapSelectListbox(QuickMatchPreferences &);
  WindowMsgHandledType system(UnsignedInt msg, WindowMsgData mData1,
                              WindowMsgData mData2);

private:
  char m_unmodelled[0x218];
  bool m_rva218;
  char m_pad219[3];
  int m_rva21C;
  bool m_rva220;
  char m_pad221[3];
  int m_rva224;
  NameKeyType m_parentOptionsKey;
  GameWindow *m_parentOptions;
  NameKeyType m_maxPingKey;
  GameWindow *m_maxPing;
  NameKeyType m_numPlayersKey;
  GameWindow *m_numPlayers;
  NameKeyType m_ladderKey;
  GameWindow *m_ladder;
  NameKeyType m_maxDisconnectsKey;
  GameWindow *m_maxDisconnects;
  NameKeyType m_sideKey;
  GameWindow *m_side;
  NameKeyType m_colorKey;
  GameWindow *m_color;
  NameKeyType m_backKey;
  GameWindow *m_back;
  NameKeyType m_startKey;
  GameWindow *m_start;
  NameKeyType m_currentMatchingLevelKey;
  GameWindow *m_currentMatchingLevel;
  NameKeyType m_personalInfoKey;
  GameWindow *m_personalInfo;
  NameKeyType m_mapSelectKey;
  GameWindow *m_mapSelect;
  NameKeyType m_parentProgressKey;
  GameWindow *m_parentProgress;
  NameKeyType m_quickMatchListKey;
  GameWindow *m_quickMatchList;
  NameKeyType m_widenKey;
  GameWindow *m_widen;
  NameKeyType m_stopKey;
  GameWindow *m_stop;
  NameKeyType m_parentStatsKey;
  GameWindow *m_parentStats;
};

extern void j_00031e0d();
class Rva005063E0SaveOptions {
public:
  __forceinline void saveQuickMatchOptions() {
    typedef void (Rva005063E0SaveOptions::*Method)();
    union {
      void (*raw)();
      Method member;
    } f;
    f.raw = j_00031e0d;
    (this->*f.member)();
  }
};

extern void j_00035701();
class Rva005082D0PopulateSide {};
typedef void (Rva005082D0PopulateSide::*Rva005082D0Method)(int,
                                                           const LadderInfo *);
__forceinline Rva005082D0Method rva005082D0Method() {
  union {
    void (*raw)();
    Rva005082D0Method member;
  } f;
  f.raw = j_00035701;
  return f.member;
}

extern void j_00021864();
class Rva005053C0GetLadderInfo {
public:
  __forceinline const LadderInfo *getLadderInfo() {
    typedef const LadderInfo *(Rva005053C0GetLadderInfo::*Method)();
    union {
      void (*raw)();
      Method member;
    } f;
    f.raw = j_00021864;
    return (this->*f.member)();
  }
};

extern void j_0002716a();
class Rva00505570UpdateStartButton {
public:
  __forceinline void updateStartButton() {
    typedef void (Rva00505570UpdateStartButton::*Method)();
    union {
      void (*raw)();
      Method member;
    } f;
    f.raw = j_0002716a;
    (this->*f.member)();
  }
};

extern void j_0002aab8();
class Rva00509B30StartRequest {
public:
  __forceinline void sendStartQuickMatchRequest(GameWindow *control) {
    typedef void (Rva00509B30StartRequest::*Method)(GameWindow *);
    union {
      void (*raw)();
      Method member;
    } f;
    f.raw = j_0002aab8;
    (this->*f.member)(control);
  }
};

class BfmeQuickMatchStopBody {
public:
  void stop();
};

extern void j_0001dda9();
class BfmeQuickMatchHideOptionsGadgetsBody {
public:
  __forceinline void showInfo(GameWindow *control) {
    typedef void (BfmeQuickMatchHideOptionsGadgetsBody::*Method)(GameWindow *);
    union {
      void (*raw)();
      Method member;
    } f;
    f.raw = j_0001dda9;
    (this->*f.member)(control);
  }
};

class Rva505C80WindowVisibilityThunk {
public:
  void updateAt00505B40();
};

void PopulateQMLadderComboBox();

class Image;

// Incoming ECX owns the gadgets; only message/data1/data2 are on the stack.
WindowMsgHandledType BfmeAptScreenQuickMatchMenu::system(UnsignedInt msg,
                                                         WindowMsgData mData1,
                                                         WindowMsgData mData2) {
  UnicodeString txtInput;

  switch (msg) {
  case GWM_CREATE:
    break;
  case GWM_DESTROY:
    break;

  case GWM_INPUT_FOCUS:
    if (mData1 == TRUE)
      *(Bool *)mData2 = TRUE;
    return MSG_HANDLED;

  case 0x4025:
    if (rva012F4801ButtonPushed)
      break;

    {
      GameWindow *control = (GameWindow *)mData1;
      Int controlID = control->winGetWindowId();
      Int pos = -1;
      GadgetComboBoxGetSelectedPos(control, &pos);
      ((Rva005063E0SaveOptions *)this)->saveQuickMatchOptions();

      if (controlID == m_ladderKey && !rva012F4814) {
        if (pos >= 0) {
          QuickMatchPreferences pref;
          Int ladderID = (Int)GadgetComboBoxGetItemData(control, pos);
          if (ladderID == 0) {
            int playerPosition = pref.getNumPlayers() / 2 - 1;
            GadgetComboBoxSetSelectedPos(m_numPlayers,
                                         (std::max)(playerPosition, 0), FALSE);
            m_numPlayers->winEnable(TRUE);
            (((Rva005082D0PopulateSide *)this)->*rva005082D0Method())(
                pref.getSide(), (const LadderInfo *)0);
          } else if (ladderID > 0) {
            const LadderInfo *li = TheLadderList->findLadderByIndex(ladderID);
            if (li)
              GadgetComboBoxSetSelectedPos(m_numPlayers, li->playersPerTeam - 1,
                                           FALSE);
            else
              GadgetComboBoxSetSelectedPos(m_numPlayers, 0, FALSE);
            m_numPlayers->winEnable(FALSE);
            (((Rva005082D0PopulateSide *)this)->*rva005082D0Method())(
                pref.getSide(), li);
          } else {
            PopulateQMLadderComboBox();
            GameSpyOpenOverlay(GSOVERLAY_LADDERSELECT);
          }
        }
      }

      else if (controlID == m_maxPingKey && !m_rva218) {
        ((Gen_00505550 *)this)->bfmeSet(control, pos);
      } else if (controlID == m_maxDisconnectsKey && !m_rva220) {
        ((Gen_00505530 *)this)->bfmeSet(control, pos);
      }

      if (!rva012F4809) {
        QuickMatchPreferences pref;
        populateQuickMatchMapSelectListbox(pref);
        ((Rva00505570UpdateStartButton *)this)->updateStartButton();
      }
    }
    break;

  case GBM_SELECTED:
    if (rva012F4801ButtonPushed)
      break;

    {
      GameWindow *control = (GameWindow *)mData1;
      Int controlID = control->winGetWindowId();

      if (controlID == m_stopKey)
        ((BfmeQuickMatchStopBody *)this)->stop();
      else if (controlID == m_personalInfoKey)
        ((BfmeQuickMatchHideOptionsGadgetsBody *)this)->showInfo(control);
      else if (controlID == m_widenKey) {
        PeerRequest req;
        req.peerRequestType = 0x11;
        TheGameSpyPeerMessageQueue->addRequest(req);
        m_widen->winEnable(FALSE);
      } else if (controlID == m_startKey)
        ((Rva00509B30StartRequest *)this)->sendStartQuickMatchRequest(control);
      else if (controlID == rva012F47F8BuddiesId)
        GameSpyToggleOverlay(GSOVERLAY_BUDDY);
      else if (controlID == m_backKey)
        ((Rva505C80WindowVisibilityThunk *)this)->updateAt00505B40();
    }
    break;

  case 0x4014: {
    GameWindow *control = (GameWindow *)mData1;
    Int controlID = control->winGetWindowId();
    Int selected = (Int)mData2;

    if (controlID == m_mapSelectKey) {
      const LadderInfo *li =
          ((Rva005053C0GetLadderInfo *)this)->getLadderInfo();
      if (selected >= 0 && (!li || !li->randomMaps)) {
        Bool wasSelected = (Bool)GadgetListBoxGetItemData(control, selected, 0);
        GadgetListBoxSetItemData(control, (void *)(!wasSelected), selected, 0);
        Int width = 10;
        Int height = 10;
        const Image *img = (!wasSelected) ? rva012F480CSelectedImage
                                          : rva012F4810UnselectedImage;
        if (img) {
          int imageWidth = img->getImageWidth();
          width =
              (std::min)(imageWidth, GadgetListBoxGetColumnWidth(control, 0));
          height = width;
        }
        GadgetListBoxAddEntryImage(control, img, selected, 0, height, width,
                                   TRUE, -1);
        GadgetListBoxAddEntryText(
            control, GadgetListBoxGetText(control, selected, 1),
            GameSpyColor[(wasSelected) ? GSCOLOR_MAP_UNSELECTED
                                       : GSCOLOR_MAP_SELECTED],
            selected, 1);
      }
      if (selected >= 0)
        GadgetListBoxSetSelected(control, -1);
    }
    ((Rva00505570UpdateStartButton *)this)->updateStartButton();
  } break;

  case 0x4030:
    break;

  default:
    return MSG_IGNORED;
  }

  return MSG_HANDLED;
}
