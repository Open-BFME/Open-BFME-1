// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/gamewindow /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Native BFME quick-match gadget initializer, 005091F0 / 1890 bytes.
// Derived from WOLQuickMatchMenu.cpp; Copyright 2025 Electronic Arts Inc.,
// GPL-3.0-or-later. Identity, ABI, and layout evidence:
// targets/game/reverse/identity_evidence/005091f0-quickmatch-init.md.
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
#define UnicodeString Rva005091F0HeaderUnicodeString
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

#include "GameClient/GadgetStaticText.h"
#include "GameClient/GameText.h"
#include "GameClient/GameWindowTransitions.h"
#include "GameClient/Shell.h"
class BfmeAptScreenQuickMatchMenu {
public:
  void populateQuickMatchMapSelectListbox(QuickMatchPreferences &);
  void rva005091F0InitGadgets();

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

class GameSpyInfoInterface {
public:
  virtual void slot00();
  virtual void slot01();
  virtual void slot02();
  virtual void slot03();
  virtual void slot04();
  virtual void slot05();
  virtual void slot06();
  virtual void slot07();
  virtual void slot08();
  virtual void slot09();
  virtual void slot10();
  virtual void slot11();
  virtual void slot12();
  virtual void slot13();
  virtual void slot14();
  virtual void slot15();
  virtual void slot16();
  virtual void slot17();
  virtual void slot18();
  virtual void slot19();
  virtual void slot20();
  virtual void slot21();
  virtual void slot22();
  virtual void slot23();
  virtual void slot24();
  virtual void slot25();
  virtual AsciiString getLocalName();
  virtual void slot27();
  virtual void slot28();
  virtual void slot29();
  virtual void slot30();
  virtual void slot31();
  virtual void slot32();
  virtual void slot33();
  virtual void slot34();
  virtual void slot35();
  virtual void slot36();
  virtual void slot37();
  virtual void slot38();
  virtual void slot39();
  virtual void slot40();
  virtual void slot41();
  virtual void slot42();
  virtual void slot43();
  virtual void slot44();
  virtual void slot45();
  virtual void slot46();
  virtual void slot47();
  virtual void slot48();
  virtual void slot49();
  virtual void slot50();
  virtual void slot51();
  virtual void slot52();
  virtual void slot53();
  virtual void slot54();
  virtual void slot55();
  virtual void slot56();
  virtual void registerTextWindow(GameWindow *window);
};

extern GameSpyInfoInterface *TheGameSpyInfo;

// upstream layout:
// reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/GSConfig.h
class GameSpyConfigInterface {
public:
  virtual void slot00();
  virtual void slot01();
  virtual void slot02();
  virtual int getPingTimeoutInMs();
};

extern GameSpyConfigInterface *TheGameSpyConfig;

class GameSpyStagingRoom {
public:
  virtual void slot00();
  virtual void slot01();
  virtual void reset();
};

extern GameSpyStagingRoom *TheGameSpyGame;

extern void j_00017567();
class Rva00477DA0WindowLookup {};
typedef GameWindow *(Rva00477DA0WindowLookup::*Rva00477DA0Method)(NameKeyType);
__forceinline Rva00477DA0Method rva00477DA0Method() {
  union {
    void (*raw)();
    Rva00477DA0Method member;
  } f;
  f.raw = j_00017567;
  return f.member;
}

// Existing legacy contract at 00508C80: singleton receiver, no stack args.
// The historical panel label is not asserted as this menu's owning identity.
class BfmeQuickMatchLadderPanel {
public:
  void populateLadderList();
};

extern BfmeQuickMatchLadderPanel *TheQuickMatchLadderPanel;

class BfmeQuickMatchProgressBody {
public:
  void update();
};
extern void j_0002716a();
class Rva00505570UpdateStartButton {
public:
  __forceinline void update() {
    typedef void (Rva00505570UpdateStartButton::*Method)();
    union {
      void (*raw)();
      Method member;
    } f;
    f.raw = j_0002716a;
    (this->*f.member)();
  }
};

extern int GameSpyColor[];
enum { GSCOLOR_DEFAULT = 0 };
enum { MAX_DISCONNECTS_COUNT = 5 };
static Int MAX_DISCONNECTS[MAX_DISCONNECTS_COUNT] = {0, 5, 10, 25, 50};
static bool isInQuickMatchInit = false;
static const Image *quickMatchSelectedImage = 0;
static const Image *quickMatchUnselectedImage = 0;
static Int quickMatchMaxPingEntries = 0;
static Int quickMatchMaxPoints = 100;
extern Int quickMatchMinPoints;

void UpdateLocalPlayerStats();
static GameWindow *aptButtonBuddies = 0;
extern void j_00035701();
class Rva005082D0Owner {};
typedef void (Rva005082D0Owner::*Rva005082D0Method)(int, const LadderInfo *);
__forceinline Rva005082D0Method rva005082D0Method() {
  union {
    void (*raw)();
    Rva005082D0Method member;
  } f;
  f.raw = j_00035701;
  return f.member;
}
extern void j_000269b8();
class Rva00505DB0Owner {};
typedef void (Rva00505DB0Owner::*Rva00505DB0Method)(QuickMatchPreferences &);
__forceinline Rva00505DB0Method rva00505DB0Method() {
  union {
    void (*raw)();
    Rva00505DB0Method member;
  } f;
  f.raw = j_000269b8;
  return f.member;
}

void BfmeAptScreenQuickMatchMenu::rva005091F0InitGadgets() {
  Rva00477DA0WindowLookup *lookup = (Rva00477DA0WindowLookup *)this;

  static NameKeyType buttonBuddiesID = NAMEKEY_INVALID;
  buttonBuddiesID =
      TheNameKeyGenerator->nameToKey("WOLQuickMatchMenu.wnd:ButtonBuddies");
  aptButtonBuddies = TheWindowManager->winGetWindowFromId(0, buttonBuddiesID);
  if (aptButtonBuddies)
    aptButtonBuddies->winHide(true);

  m_parentOptions = (lookup->*rva00477DA0Method())(m_parentOptionsKey);
  m_maxPing = (lookup->*rva00477DA0Method())(m_maxPingKey);
  m_start = (lookup->*rva00477DA0Method())(m_startKey);
  m_back = (lookup->*rva00477DA0Method())(m_backKey);
  m_mapSelect = (lookup->*rva00477DA0Method())(m_mapSelectKey);
  m_numPlayers = (lookup->*rva00477DA0Method())(m_numPlayersKey);
  m_ladder = (lookup->*rva00477DA0Method())(m_ladderKey);
  m_maxDisconnects =
      (lookup->*rva00477DA0Method())(m_maxDisconnectsKey);
  m_side = (lookup->*rva00477DA0Method())(m_sideKey);
  m_color = (lookup->*rva00477DA0Method())(m_colorKey);
  m_personalInfo = (lookup->*rva00477DA0Method())(m_personalInfoKey);
  m_parentProgress =
      (lookup->*rva00477DA0Method())(m_parentProgressKey);
  m_quickMatchList =
      (lookup->*rva00477DA0Method())(m_quickMatchListKey);
  m_stop = (lookup->*rva00477DA0Method())(m_stopKey);
  m_widen = (lookup->*rva00477DA0Method())(m_widenKey);
  m_parentStats = (lookup->*rva00477DA0Method())(m_parentStatsKey);

  TheGameSpyInfo->registerTextWindow(m_quickMatchList);

  if (TheLadderList->getStandardLadders()->size() == 0 &&
      TheLadderList->getSpecialLadders()->size() == 0 &&
      TheLadderList->getLocalLadders()->size() == 0) {
    m_ladder->winEnable(false);
  }

  GameWindow *staticTextTitle =
      (lookup->*rva00477DA0Method())(TheNameKeyGenerator->nameToKey(
          "WOLQuickMatchMenu.wnd:StaticTextTitle"));
  if (staticTextTitle) {
    UnicodeString tmp;
    tmp.format(TheGameText->fetch("GUI:QuickMatchTitle"),
               TheGameSpyInfo->getLocalName().str());
    GadgetStaticTextSetText(staticTextTitle, tmp);
  }

  m_start->winHide(false);
  GadgetListBoxReset(m_quickMatchList);
  TheWindowManager->winSetFocus((GameWindow *)this);

  quickMatchSelectedImage = TheMappedImageCollection->findImageByName(
      AsciiString("CustomMatch_selected"));
  quickMatchUnselectedImage = TheMappedImageCollection->findImageByName(
      AsciiString("CustomMatch_deselected"));

  QuickMatchPreferences pref;
  UnicodeString s;
  quickMatchMaxPoints = pref.getMaxPoints();
  quickMatchMinPoints = pref.getMinPoints();

  Color c = GameSpyColor[GSCOLOR_DEFAULT];
  GadgetComboBoxReset(m_numPlayers);
  Int i;
  for (i = 1; i < 5; ++i) {
    s.format(TheGameText->fetch("GUI:PlayersVersusPlayers"), i, i);
    GadgetComboBoxAddEntry(m_numPlayers, s, c);
  }
  int playerPosition = pref.getNumPlayers();
  GadgetComboBoxSetSelectedPos(m_numPlayers, std::max(playerPosition, 0),
                               false);

  // Suppress disconnect-selection callbacks while entries are replaced.
  m_rva220 = true;
  GadgetComboBoxReset(m_maxDisconnects);
  GadgetComboBoxAddEntry(m_maxDisconnects, TheGameText->fetch("GUI:Any"), c);
  for (i = 1; i < MAX_DISCONNECTS_COUNT; ++i) {
    s.format(L"%d", MAX_DISCONNECTS[i]);
    GadgetComboBoxAddEntry(m_maxDisconnects, s, c);
  }
  int disconnectPosition = pref.getMaxDisconnects();
  m_rva224 = std::max(disconnectPosition, 0);
  GadgetComboBoxSetSelectedPos(m_maxDisconnects, m_rva224, false);
  m_rva220 = false;
  m_rva218 = true;

  GadgetComboBoxReset(m_maxPing);
  quickMatchMaxPingEntries = (TheGameSpyConfig->getPingTimeoutInMs() - 1) / 100;
  quickMatchMaxPingEntries++;
  for (i = 1; i < quickMatchMaxPingEntries; ++i) {
    s.format(TheGameText->fetch("GUI:TimeInMilliseconds"), i * 100);
    GadgetComboBoxAddEntry(m_maxPing, s, c);
  }
  GadgetComboBoxAddEntry(m_maxPing, TheGameText->fetch("GUI:ANY"), c);
  m_rva21C = pref.getMaxPing();
  if (m_rva21C < 0)
    m_rva21C = 0;
  if (m_rva21C >= quickMatchMaxPingEntries)
    m_rva21C = quickMatchMaxPingEntries - 1;
  GadgetComboBoxSetSelectedPos(m_maxPing, m_rva21C, false);

  m_rva218 = false;
  (((Rva00505DB0Owner *)this)->*rva00505DB0Method())(pref);

  Int selected;
  GadgetComboBoxGetSelectedPos(m_ladder, &selected);
  Int index = (Int)GadgetComboBoxGetItemData(m_ladder, selected);
  const LadderInfo *li = TheLadderList->findLadderByIndex(index);
  (((Rva005082D0Owner *)this)->*rva005082D0Method())(pref.getSide(), li);

  if (TheQuickMatchLadderPanel)
    TheQuickMatchLadderPanel->populateLadderList();
  TheShell->showShellMap(true);
  TheGameSpyGame->reset();

  GadgetListBoxReset(m_mapSelect);
  populateQuickMatchMapSelectListbox(pref);
  UpdateLocalPlayerStats();
  ((Rva00505570UpdateStartButton *)this)->update();

  TheTransitionHandler->setGroup(AsciiString("WOLQuickMatchMenuFade"));
  m_currentMatchingLevel =
      (lookup->*rva00477DA0Method())(m_currentMatchingLevelKey);
  ((BfmeQuickMatchProgressBody *)this)->update();
  m_parentStats->winHide(true);
  m_parentProgress->winHide(true);
  m_quickMatchList->winHide(true);
  m_stop->winHide(true);
  m_widen->winHide(true);
  isInQuickMatchInit = false;
}
