// ?_bfme_sendStartQuickMatchRequest@BfmeAptScreenOnlineQuickMatch@@QAEXXZ
// partial score=0.8241 date=2026-10-01
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/gamewindow /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// BfmeAptScreenOnlineQuickMatch::_bfme_sendStartQuickMatchRequest, retail
// 0x0055B200 / 1552 bytes. The matched OnlineQuickMatch update slot at
// 0x0055B9A0 calls it; its GetGameClientRandomValue file literal names
// GUICallbacks\Apt\AptOnlineQuickMatch.cpp. The body is the APT port of the
// matched QuickMatch menu request at 0x00509B30 (WOLQuickMatchMenuRequest.cpp):
// a type-0x10 PeerRequest filled from the gadgets, then ladder-rank point bands.
#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#define ASCIISTRING_H
#define UNICODESTRING_H
#include "ascii_string.h"
#include "unicode_string.h"

inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::UnicodeString(const wchar_t *s) {
  ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(s);
}
inline UnicodeString::UnicodeString(const UnicodeString &s) {
  ((StringBase<unsigned short> *)this)
      ->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&s);
}
inline UnicodeString::~UnicodeString() {
  ((StringBase<unsigned short> *)this)->releaseBuffer();
}
inline UnicodeString &UnicodeString::operator=(const UnicodeString &s) {
  ((StringBase<unsigned short> *)this)->set(*(const StringBase<unsigned short> *)&s);
  return *this;
}

// The legacy window header embeds its own UnicodeString in unused inline
// accessors. Give that header-only view a distinct name while preserving the
// canonical native strings used by this body.
#undef UNICODESTRING_H
#define UnicodeString Rva0055B200HeaderUnicodeString
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
#include "Common/LadderPreferences.h"
#include <time.h>
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

class PeerRequest {
public:
  int peerRequestType;
  std::string nick;
  std::wstring text;
  std::string password, email, id, options, ladderIP, hostPingStr, gameOptsMapName;
  std::string gameOptsPlayerNames[8];
  std::vector<bool> qmMaps;
  union {
    struct {
      int minPointPercentage, maxPointPercentage, points, widenTime, ladderID;
      unsigned ladderPassCRC;
      int maxPing, maxDiscons, discons;
      char pings[17];
      int numPlayers, botID, roomID, side, color, NAT;
      unsigned rva134, rva138, rva13C;
    } QM;
    char extent[176];
  };
  PeerRequest();
  ~PeerRequest();
};
typedef char RequestSize[sizeof(PeerRequest) == 0x194 ? 1 : -1];
typedef char StatsSize[sizeof(PSPlayerStats) == 0x1c4 ? 1 : -1];
class GameSpyInfoInterface {
public:
  virtual void slot0();
  virtual void slot1();
  virtual void slot2();
  virtual void slot3();
  virtual void slot4();
  virtual void slot5();
  virtual void slot6();
  virtual void slot7();
  virtual void slot8();
  virtual void slot9();
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
  virtual void slot26();
  virtual void slot27();
  virtual int getLocalProfileID();
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
  virtual void slot57();
  virtual void slot58();
  virtual void slot59();
  virtual void slot60();
  virtual void slot61();
  virtual void slot62();
  virtual void slot63();
  virtual void slot64();
  virtual void slot65();
  virtual void slot66();
  virtual void slot67();
  virtual void slot68();
  virtual const AsciiString &getPingString();
};
extern GameSpyInfoInterface *TheGameSpyInfo;
class GameSpyConfigInterface {
public:
  virtual void slot0();
  virtual void slot1();
  virtual void slot2();
  virtual int getPingTimeoutInMs();
  virtual void slot4();
  virtual void slot5();
  virtual void slot6();
  virtual int getQMBotID();
  virtual int getQMChannel();
};
extern GameSpyConfigInterface *TheGameSpyConfig;
class GameSpyPSMessageQueueInterface {
public:
  virtual void slot0();
  virtual void slot1();
  virtual void slot2();
  virtual void slot3();
  virtual void slot4();
  virtual void slot5();
  virtual void slot6();
  virtual void slot7();
  virtual void slot8();
  virtual PSPlayerStats findPlayerStatsByID(int);
};
extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;
class GameSpyPeerMessageQueueInterface {
public:
  virtual void slot0();
  virtual void slot1();
  virtual void slot2();
  virtual void slot3();
  virtual void slot4();
  virtual void slot5();
  virtual void addRequest(const PeerRequest &);
};
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
int CalculateRank(const PSPlayerStats &);
class Rva000E1410PlayerTemplate {
public:
  char prefix[8];
  AsciiString side;
  char remainder[0x124 - 12];
};
class Rva000E1410Store {
public:
  char prefix[8];
  Rva000E1410PlayerTemplate *begin, *end, *capacity;
  const Rva000E1410PlayerTemplate *getNthPlayerTemplate(int) const;
};
extern Rva000E1410Store *ThePlayerTemplateStore;
int Rva0009B4B0(int a, int b);
struct Rva0055B200GlobalData {
  char prefix[0xbc8];
  unsigned rvaBC8, rvaBCC, rvaBD0, rvaBD4;
};
#define BFME_QM_GLOBAL_DATA ((const Rva0055B200GlobalData *)TheWritableGlobalData)
extern int g_bfmePeerReqE4, g_bfmePeerReqE8;
extern unsigned int g_bfme012F73D0, g_bfme012F73D4;
static int s_bfmeMaxPingEntries = 0;

class BfmeC1040 {
public:
  int bfmeGo1040C();
};
class BfmeThingCCH {
public:
  int bfmeGoCCH(void *what);
};

class BfmeAptScreenOnlineQuickMatch {
public:
  void _bfme_sendStartQuickMatchRequest();
  void rva0055AE10PopulateRequest(PeerRequest *request);

private:
  unsigned char m_beforePreferences[0x40];
  unsigned char m_preferences[0x1C];
  GameWindow *m_color;
  GameWindow *m_numPlayers;
  GameWindow *m_side;
  GameWindow *m_connectionSpeed;
  GameWindow *m_ladder;
  GameWindow *m_slot70;
  GameWindow *m_slot74;
  int m_slot78;
};



void BfmeAptScreenOnlineQuickMatch::_bfme_sendStartQuickMatchRequest() {
  PeerRequest req;
  req.peerRequestType = 16;
  rva0055AE10PopulateRequest(&req);
  UnicodeString u;
  AsciiString a;
  req.QM.maxPointPercentage = 100;
  req.QM.minPointPercentage = 0;
  req.QM.widenTime = 0;
  req.QM.maxDiscons = 0x7fffffff;
  int val;
  GadgetComboBoxGetSelectedPos(m_connectionSpeed, &val);
  if (val < 0)
    val = 0;
  if (val >= s_bfmeMaxPingEntries - 1)
    req.QM.maxPing = TheGameSpyConfig->getPingTimeoutInMs();
  else
    req.QM.maxPing = (val + 1) * 100;
  req.QM.maxPing = req.QM.maxPing * 255 / TheGameSpyConfig->getPingTimeoutInMs();
  PSPlayerStats stats = TheGameSpyPSMessageQueue->findPlayerStatsByID(
      TheGameSpyInfo->getLocalProfileID());
  req.QM.points = CalculateRank(stats);
  int ladderIndex, index, selected;
  GadgetComboBoxGetSelectedPos(m_ladder, &selected);
  ladderIndex = (int)GadgetComboBoxGetItemData(m_ladder, selected);
  const LadderInfo *ladderInfo = 0;
  if (ladderIndex < 0)
    ladderIndex = 0;
  if (ladderIndex) {
    ladderInfo = TheLadderList->findLadderByIndex(ladderIndex);
    if (!ladderInfo)
      ladderIndex = 0;
  }
  req.QM.ladderID = ladderIndex;
  req.QM.ladderPassCRC = 0;
  index = -1;
  GadgetComboBoxGetSelectedPos(m_side, &selected);
  if (selected >= 0)
    index = (int)GadgetComboBoxGetItemData(m_side, selected);
  req.QM.side = index;
  if (ladderInfo && ladderInfo->randomFactions) {
    int sideNum = GetGameClientRandomValue(
        0, ladderInfo->validFactions.size() - 1,
        (char *)"F:"
                "\\bfme\\Code\\gameengine\\Source\\GameClient\\Gui\\GUICallbacks\\Apt"
                "\\AptOnlineQuickMatch.cpp",
        0x2c0);
    std::list<AsciiString>::const_iterator cit = ladderInfo->validFactions.begin();
    while (sideNum) {
      ++cit;
      --sideNum;
    }
    if (cit != ladderInfo->validFactions.end()) {
      int numPlayerTemplates =
          ThePlayerTemplateStore->end - ThePlayerTemplateStore->begin;
      AsciiString sideStr = *cit;
      for (int c = 0; c < numPlayerTemplates; ++c) {
        const Rva000E1410PlayerTemplate *fac =
            ThePlayerTemplateStore->getNthPlayerTemplate(c);
        if (fac && fac->side.compare(sideStr) == 0) {
          req.QM.side = c;
          break;
        }
      }
    }
  }
  req.QM.color = ((BfmeThingCCH *)&m_color)
                     ->bfmeGoCCH((void *)((BfmeC1040 *)&m_color)->bfmeGo1040C());
  OptionPreferences natPref;
  req.QM.NAT = natPref.getFirewallBehavior();
  if (ladderIndex)
    req.QM.numPlayers = ladderInfo ? ladderInfo->playersPerTeam * 2 : 2;
  else {
    GadgetComboBoxGetSelectedPos(m_numPlayers, &val);
    if (val < 0)
      val = 0;
    req.QM.numPlayers = (val + 1) * 2;
  }
  struct QuickMatchOne { int value; } one = { 1 };
  switch (req.QM.numPlayers) {
  case 2:
    m_slot78 = one.value;
    break;
  case 4:
    m_slot78 = 2;
    break;
  default:
    m_slot78 = 0;
    break;
  }
  req.QM.discons = 10000;
  strncpy(req.QM.pings, TheGameSpyInfo->getPingString().str(), 17);
  req.QM.pings[16] = 0;
  req.QM.botID = TheGameSpyConfig->getQMBotID();
  req.QM.roomID = TheGameSpyConfig->getQMChannel();
  int crc = BFME_QM_GLOBAL_DATA->rvaBD0;
  req.QM.rva134 = Rva0009B4B0(crc, crc);
  req.QM.rva138 = BFME_QM_GLOBAL_DATA->rvaBC8;
  req.QM.rva13C = BFME_QM_GLOBAL_DATA->rvaBD4;
  unsigned int rankCount;
  if (m_slot78 == one.value) {
    req.QM.points = g_bfmePeerReqE4;
    rankCount = g_bfme012F73D0;
  } else if (m_slot78 == 2) {
    req.QM.points = g_bfmePeerReqE8;
    rankCount = g_bfme012F73D4;
  } else {
    req.QM.points = -1;
    rankCount = 0;
  }
  if (req.QM.points <= 0)
    req.QM.points = -1;
  req.QM.minPointPercentage = one.value;
  int center = 0x7fffffff;
  if (rankCount)
    center = rankCount;
  req.QM.maxPointPercentage = center;
  if (req.QM.points > 0)
    center = req.QM.points;
  double spread = rankCount * 0.125;
  int lo = center - (int)ceil(spread);
  req.QM.minPointPercentage = std::max(lo, one.value);
  req.QM.maxPointPercentage =
      std::min(center + (int)floor(spread), req.QM.maxPointPercentage);
  TheGameSpyPeerMessageQueue->addRequest(req);
  if (ladderIndex > 0) {
    LadderPreferences ladPref;
    ladPref.loadProfile(TheGameSpyInfo->getLocalProfileID());
    LadderPref p;
    p.lastPlayDate = time(0);
    p.address = ladderInfo->address;
    p.port = ladderInfo->port;
    p.name = ladderInfo->name;
    ladPref.addRecentLadder(p);
    ladPref.write();
  }
}
