// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Native BFME GameInfo::adjustSlotsForMap at 00620B00 (1308 bytes).
// Derived from GameInfo.cpp, Copyright 2025 Electronic Arts Inc., GPL-3.0-or-later.
// Evidence: targets/game/reverse/identity_evidence/00620b00-gameinfo-adjust-slots.md.
#define __PLACEMENT_VEC_NEW_INLINE
#define _STLP_NO_EXCEPTIONS 1
#include "ascii_string.h"
#include "unicode_string.h"
inline UnicodeString::UnicodeString() { m_text = 0; }
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
extern const UnicodeString Rva01336E54EmptyUnicode;
typedef int Int;
enum { MAX_SLOTS = 8 };
enum SlotState {
  SLOT_OPEN,
  SLOT_CLOSED,
  SLOT_EASY_AI,
  SLOT_MED_AI,
  SLOT_BRUTAL_AI,
  SLOT_PLAYER
};
// setState at 0061F210 copies IP and the complete port/padding word to +30/+34.
struct GameSlotConnectInfo {
  GameSlotConnectInfo() : m_ip(0), m_port(0) {}
  unsigned int m_ip;
  unsigned short m_port;
  char m_padding[2];
};
class GameTextInterface {
public:
  virtual void slot00();
  virtual void slot04();
  virtual void slot08();
  virtual void slot0c();
  virtual void slot10();
  virtual void slot14();
  virtual void slot18();
  virtual void slot1c();
  virtual void slot20();
  virtual void slot24();
  virtual UnicodeString fetch(const char *, bool * = 0);
};
extern GameTextInterface *TheGameText;
// Scoped BFME layout: the older GameInfo reference shim places IP/NAT
// incorrectly.
class GameSlot {
public:
  GameSlot();
  GameSlot(const GameSlot &);
  // Implicit destruction releases both native string members without re-seating
  // the vptr.
  virtual void reset();
  void setState(SlotState state, UnicodeString name,
                const GameSlotConnectInfo *connectInfo) {
    if (!(isAI() && (state == SLOT_EASY_AI || state == SLOT_MED_AI ||
                     state == SLOT_BRUTAL_AI))) {
      m_color = -1;
      m_startPos = -1;
      m_playerTemplate = -1;
      m_teamNumber = -1;
    }
    if (state == SLOT_PLAYER) {
      reset();
      m_state = state;
      m_name = name;
    } else {
      m_state = state;
      m_isAccepted = true;
      m_hasMap = true;
      switch (state) {
      case SLOT_OPEN:
        m_name = TheGameText->fetch("GUI:Open");
        break;
      case SLOT_EASY_AI:
        m_name = TheGameText->fetch("GUI:EasyAI");
        break;
      case SLOT_MED_AI:
        m_name = TheGameText->fetch("GUI:MediumAI");
        break;
      case SLOT_BRUTAL_AI:
        m_name = TheGameText->fetch("GUI:HardAI");
        break;
      default:
        m_name = TheGameText->fetch("GUI:Closed");
        break;
      }
    }
    m_connectInfo = *connectInfo;
  }
  bool isOccupied() const { return m_state == SLOT_PLAYER || isAI(); }
  bool isAI() const {
    return m_state == SLOT_EASY_AI || m_state == SLOT_MED_AI ||
           m_state == SLOT_BRUTAL_AI;
  }

private:
  SlotState m_state;
  bool m_isAccepted, m_hasMap, m_isMuted;
  int m_color, m_startPos, m_playerTemplate, m_teamNumber;
  int m_origColor, m_origStartPos, m_origPlayerTemplate;
  UnicodeString m_name;
  AsciiString m_slotNameKeyText;
  GameSlotConnectInfo m_connectInfo;
  int m_nat;
  unsigned int m_lastFrameInGame;
  bool m_disconnected;
};
typedef char GameSlotSizeCheck[sizeof(GameSlot) == 0x44 ? 1 : -1];

inline GameSlot::GameSlot() { reset(); }
inline void GameSlot::reset() {
  m_state = SLOT_CLOSED;
  m_isAccepted = false;
  m_hasMap = true;
  m_color = -1;
  m_startPos = -1;
  m_playerTemplate = -1;
  m_teamNumber = -1;
  m_nat = 1;
  m_lastFrameInGame = 0;
  m_disconnected = false;
  GameSlotConnectInfo empty;
  m_connectInfo = empty;
  m_isMuted = false;
  m_origPlayerTemplate = -1;
  m_origStartPos = -1;
  m_origColor = -1;
  m_slotNameKeyText.clear();
}
template <> inline void StringBase<char>::clear() { releaseBuffer(); }
class MapMetaData {
public:
  char m_unrecovered00[0x20];
  int m_numPlayers;
};
class MapCache {
public:
  const MapMetaData *findMap(AsciiString name);
};
extern MapCache *TheMapCache;
class GameInfo {
public:
  virtual void adjustSlotsForMap();
  void setSlot(int, GameSlot);
  // This always-false bounds condition is present in the original getSlot
  // helper.
  GameSlot *getSlot(int i) {
    if (m_slots == 0)
      return 0;
    if (i < 0 && i >= 8)
      return 0;
    return m_slots[i];
  }

private:
  char m_unrecovered04[0x10];
  GameSlot *m_slots[8];
  unsigned int m_localIP;
  int m_bfme38;
  AsciiString m_mapName;
};
void GameInfo::adjustSlotsForMap() {
  const MapMetaData *md = TheMapCache->findMap(m_mapName);
  if (md != NULL) {
    Int numPlayers = md->m_numPlayers;
    Int numPlayerSlots = 0;

    for (Int i = 0; i < MAX_SLOTS; ++i) {
      GameSlot *tempSlot = getSlot(i);
      if (tempSlot->isOccupied())
        ++numPlayerSlots;
    }

    for (i = 0; i < MAX_SLOTS; ++i) {
      GameSlot *slot = getSlot(i);
      if (numPlayers > numPlayerSlots) {
        if (!(slot->isOccupied())) {
          GameSlot newSlot;
          GameSlotConnectInfo connectInfo;
          connectInfo.m_port = 0;
          newSlot.setState(SLOT_OPEN, Rva01336E54EmptyUnicode, &connectInfo);
          setSlot(i, newSlot);
          ++numPlayerSlots;
        }
      } else {
        if (!(slot->isOccupied())) {
          GameSlot newSlot;
          GameSlotConnectInfo connectInfo;
          connectInfo.m_port = 0;
          newSlot.setState(SLOT_CLOSED, Rva01336E54EmptyUnicode, &connectInfo);
          setSlot(i, newSlot);
        }
      }
    }
  }
}
