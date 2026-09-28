// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/gamewindow /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// BfmeAptScreenQuickMatchMenu::saveQuickMatchOptions, retail 0x005063E0, 663 bytes.
// Derived from WOLQuickMatchMenu.cpp; Copyright 2025 Electronic Arts Inc.,
// GPL-3.0-or-later.
//
// Identity: the Zero Hour static saveQuickMatchOptions (WOLQuickMatchMenu.cpp:616)
// turned into a member of the BFME quick-match screen. The two matched callers
// call it where Zero Hour does: WOLQuickMatchMenuShutdown (0x00507E10) when the
// engine is not quitting, and the system handler (0x0050A470) on `this`
// (identity_evidence/0050a470-quickmatch-system.md names that class). The body
// is the Zero Hour one, statement for statement, on that handler's gadget
// layout.
//
// Boundary: the generator split this function into a 34-byte prologue row at
// 0x005063E0 and a 629-byte continuation at 0x00506402. The split falls at
// +0x22, the `push esi` in the middle of the prologue's register saves: the
// continuation has no prologue or entry of its own, the `jne` at +0x25 that
// skips the body while isInInit is set lands on the shared epilogue at +0x24E,
// and the single ret is at +0x25E.
// Derived from WOLQuickMatchMenu.cpp; Copyright 2025 Electronic Arts Inc.,
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

#include "GameNetwork/GameSpy/GSConfig.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
// Only the file name is read; retail adds 0x50 to the item data (ZH MapMetaData::m_fileName).
class MapMetaData {
public:
  char m_unmodelled[0x50];
  AsciiString m_fileName;
};

// AsciiString::TheEmptyString; the WWLib string model has no static member for it.
extern const AsciiString Rva01336E50EmptyString;

class BfmeAptScreenQuickMatchMenu {
public:
  void saveQuickMatchOptions();

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

// BFME's max takes and returns references and compares with `>` (the same
// template matched ConnectionManager.cpp and ThingTemplateCalcTimeToBuild.cpp
// restate); Zero Hour's BaseType.h macro compiles to a branchless select.
template <class T> inline const T &maxRef(const T &a, const T &b) { return a > b ? a : b; }

// ?saveQuickMatchOptions@BfmeAptScreenQuickMatchMenu@@QAEXXZ
void BfmeAptScreenQuickMatchMenu::saveQuickMatchOptions()
{
  if (rva012F4809)
    return;
  QuickMatchPreferences pref;

  std::list<AsciiString> maps = TheGameSpyConfig->getQMMaps();

  Int index;
  Int selected;
  GadgetComboBoxGetSelectedPos(m_ladder, &selected);
  index = (Int)GadgetComboBoxGetItemData(m_ladder, selected);
  const LadderInfo *li = TheLadderList->findLadderByIndex(index);
  Int numPlayers = 0;

  if (li) {
    pref.setLastLadder(li->address, li->port);
    numPlayers = li->playersPerTeam * 2;

    pref.write();
  } else {
    pref.setLastLadder(Rva01336E50EmptyString, 0);
    GadgetComboBoxGetSelectedPos(m_numPlayers, &selected);
    if (selected < 0)
      selected = 0;
    numPlayers = (selected + 1) * 2;
  }

  if (!li || !li->randomMaps) {
    Int row = 0;
    Int entries = GadgetListBoxGetNumEntries(m_mapSelect);
    while (row < entries) {
      const MapMetaData *md =
          (const MapMetaData *)GadgetListBoxGetItemData(m_mapSelect, row, 1);
      if (md)
        pref.setMapSelected(md->m_fileName,
                            (Bool)GadgetListBoxGetItemData(m_mapSelect, row));
      row++;
    }
  }

  UnicodeString u;
  AsciiString a;

  GadgetComboBoxGetSelectedPos(m_numPlayers, &selected);
  pref.setNumPlayers(selected);
  GadgetComboBoxGetSelectedPos(m_maxPing, &selected);
  pref.setMaxPing(selected);

  Int item;
  GadgetComboBoxGetSelectedPos(m_side, &selected);
  item = (Int)GadgetComboBoxGetItemData(m_side, selected);
  pref.setSide(maxRef(0, item));
  GadgetComboBoxGetSelectedPos(m_color, &selected);
  pref.setColor(maxRef(0, selected));

  GadgetComboBoxGetSelectedPos(m_maxDisconnects, &selected);
  pref.setMaxDisconnects(selected);

  pref.write();
}
