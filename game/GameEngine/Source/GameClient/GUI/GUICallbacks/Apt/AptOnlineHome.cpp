// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Igame/Libraries/Source/WWVegas/WWLib /D_STLP_USE_STATIC_LIB
// stlport
// OnlineHome 0x00547730: address-derived member called by matched constructor.
// Stats offsets follow the landed OnlineProfile body and retail accesses.
// Complete extent: VA 00947730 through RET 00948212. The constructor at
// RVA 005484E0 establishes this member; +34 is its existing context field.
// Rva005466C0Tree::find returns a native iterator via a hidden result pointer.
// The faction-rate helper at RVA 00545DE0 takes (int* counts, int category)
// and returns float in ST0, as independently decoded from its full 345 bytes.
// GhidraSQL was requested but timed out; complete CFG checked from retail bytes.
#define _STLP_NO_EXCEPTIONS 1
#include "ascii_string.h"
#include <stdio.h>
#include <string.h>
#include <wchar.h>
template <> inline const unsigned short *StringBase<unsigned short>::str() const {
    static const unsigned short TheNullChr = 0;
    return m_data ? m_data->data : &TheNullChr;
}
#include "Common/UnicodeString.h"
#include <algorithm>
#include <map>
#include <string>
inline UnicodeString::~UnicodeString() { ((StringBase<wchar_t> *)this)->releaseBuffer(); }
typedef int Int;
typedef float Real;
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

typedef char PSSize[sizeof(PSPlayerStats) == 0x1c4 ? 1 : -1];

template <class T> inline StringBase<T>::~StringBase() { releaseBuffer(); }
template <> inline unsigned short StringBase<unsigned short>::getCharAt(int i) const {
 return m_data ? m_data->data[i] : 0;
}
class GameTextInterface {
public:
 virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
 virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
 virtual void s20(); virtual void s24();
 virtual UnicodeString fetch(const char*, bool* = 0);
};
class GameSpyInfo {
public:
#define SLOT(n) virtual void s##n();
 SLOT(00) SLOT(04) SLOT(08) SLOT(0c) SLOT(10) SLOT(14) SLOT(18) SLOT(1c)
 SLOT(20) SLOT(24) SLOT(28) SLOT(2c) SLOT(30) SLOT(34) SLOT(38) SLOT(3c)
 SLOT(40) SLOT(44) SLOT(48) SLOT(4c) SLOT(50) SLOT(54) SLOT(58) SLOT(5c)
 SLOT(60) SLOT(64) virtual AsciiString getLocalName();
 SLOT(6c) SLOT(70) SLOT(74) SLOT(78) SLOT(7c) SLOT(80) SLOT(84) SLOT(88) SLOT(8c)
 virtual PSPlayerStats rva90();
#undef SLOT
};
class WindowManager {public: void bfme_setAptText(const AsciiString&,const UnicodeString&);};
extern GameSpyInfo *TheGameSpyInfo;
extern WindowManager *g_theWindowManager;
extern GameTextInterface *TheGameText;
extern int g_bfmePeerReqE4, g_bfmePeerReqE8;
extern const char *g_onlineHomeGadgetsImageLevelIconMain;
extern unsigned int g_012F4A10[8];
extern unsigned int g_012F4A30[8];
extern unsigned int g_012F4A50[8];
extern unsigned int g_012F4A70[8];
class GlobalLanguageData;
extern GlobalLanguageData *TheGlobalLanguageData;
extern void j_0003cc54();
extern void j_00022976();
extern void j_00008b9d();
extern void j_000136a1();
extern void j_0001681a();
extern void j_0000bbcc();
extern void j_00047974();
template<class M> __forceinline M retailMethod(void (*raw)()) {
 union { void (*entry)(); M method; } f; f.entry=raw; return f.method;
}
struct Rva0055CD80Owner {
 void call() {typedef void (Rva0055CD80Owner::*M)(); (this->*retailMethod<M>(j_0003cc54))();}
};
struct Rva0046C770Owner {};
class Rva005466C0Tree { public: PerGeneralMap::iterator find(const int&); };
UnicodeString bfmeOnlineHomeRankText(int);
struct HomeSystemTime { unsigned short field[8]; };
struct HomeTimeZone { long bias; unsigned short standardName[32]; HomeSystemTime standardDate;
 long standardBias; unsigned short daylightName[32]; HomeSystemTime daylightDate; long daylightBias; };
extern "C" __declspec(dllimport) unsigned long __stdcall GetTimeZoneInformation(HomeTimeZone*);
extern "C" __declspec(dllimport) int __stdcall WideCharToMultiByte(unsigned,unsigned long,const unsigned short*,int,char*,int,const char*,int*);
static __forceinline void setText(const char *key,const UnicodeString& text) {
 g_theWindowManager->bfme_setAptText(AsciiString(key),text);
}
class BfmeAptScreenOnlineHome {
 char field00[0x34]; Rva0055CD80Owner *field34;
public: void rva00547730();
};
void BfmeAptScreenOnlineHome::rva00547730() {
 if(TheGameSpyInfo) {
  field34->call();
  UnicodeString text;
  AsciiString name=TheGameSpyInfo->getLocalName();
  PSPlayerStats stats=TheGameSpyInfo->rva90();
  int rank1=g_bfmePeerReqE4,rank2=g_bfmePeerReqE8;
  UnicodeString rankText1=bfmeOnlineHomeRankText(rank1);
  UnicodeString rankText2=bfmeOnlineHomeRankText(rank2);
  setText("APT:RankNum",rankText1);
  setText("APT:RankNum2",rankText2);
  UnicodeString player;
  player.translate(name);
  text.format(TheGameText->fetch("APT:PlayerHistory"),player.str());
  setText("APT:PlayerHistory",text);
  int side=stats.lastSide;
  if(side<0 || side>=4) side=1;
  int level=((int(__cdecl*)(int))j_00008b9d)(((int(__cdecl*)(PSPlayerStats*,int))j_00022976)(&stats,side));
  text.format(TheGameText->fetch("APT:CurrentLevelNumFormat"),level);
  setText("APT:CurrentLevelNum",text);
  void *image=((void*(__cdecl*)(int,int))j_000136a1)(level,side);
  typedef void (Rva0046C770Owner::*ImageM)(const AsciiString&,void*);
  (((Rva0046C770Owner*)g_theWindowManager)->*retailMethod<ImageM>(j_0001681a))(AsciiString(g_onlineHomeGadgetsImageLevelIconMain),image);
  switch(side) {
   case 3: text=TheGameText->fetch("Apt:IsengardCaps"); break;
   case 0: text=TheGameText->fetch("Apt:RohanCaps"); break;
   case 2: text=TheGameText->fetch("Apt:MordorCaps"); break;
   default: text=TheGameText->fetch("Apt:GondorCaps"); break;
  }
  setText("APT:SideType",text);
  unsigned current=0;
  {
   int key=side;
   PerGeneralMap::iterator i=((Rva005466C0Tree*)&stats.currentWinStreaks)->find(key);
   if(i != stats.currentWinStreaks.end() && i->second > current) current=i->second;
  }
  text.format(UnicodeString(L"%d"),current);
  setText("APT:CurrentWinStreakNum",text);
  unsigned best=0;
  {
   int key=side;
   PerGeneralMap::iterator i=((Rva005466C0Tree*)&stats.bestWinStreaks)->find(key);
   if(i != stats.bestWinStreaks.end() && i->second > best) best=i->second;
  }
  text.format(UnicodeString(L"%d"),best);
  setText("APT:BestWinStreakNum",text);
  unsigned losses=0;
  unsigned wins=0;
  {
   int key=side;
   PerGeneralMap::iterator i=((Rva005466C0Tree*)&stats.wins)->find(key);
   if(i != stats.wins.end() && i->second > wins) wins=i->second;
  }
  {
   int key=side;
   PerGeneralMap::iterator i=((Rva005466C0Tree*)&stats.losses)->find(key);
   if(i != stats.losses.end() && i->second > losses) losses=i->second;
  }
  text.format(UnicodeString(L"%d/%d"),wins,losses);
  setText("APT:CareerWinLossNum",text);
  text.format(UnicodeString(L"In Progress"));
  setText("APT:LadderType",text);
  setText("APT:ClanType",text);
  HomeTimeZone zone;
  unsigned long zoneResult=GetTimeZoneInformation(&zone);
  UnicodeString zoneText;
  char buffer[512];
  if(zoneResult==0xffffffff) zoneText.format(UnicodeString::TheEmptyString);
  else if(zoneResult==2) {
   WideCharToMultiByte(0,0,zone.daylightName,-1,buffer,512,0,0);
   zoneText.translate(AsciiString(buffer));
  } else {
   WideCharToMultiByte(0,0,zone.standardName,-1,buffer,512,0,0);
   zoneText.translate(AsciiString(buffer));
  }
  UnicodeString token,initials;
  while(((StringBase<unsigned short>*)&zoneText)->nextToken((StringBase<unsigned short>*)&token,L" ")) {
   unsigned short c=token.getCharAt(0);
   ((StringBase<unsigned short>*)&initials)->concat(&c,1);
  }
  setText("APT:TimeZone",initials);
  j_0000bbcc();
  int gondor=(int)(((float(__cdecl*)(int*,int))j_00047974)((int*)g_012F4A10,3)*100.0f+0.5f);
  int rohan=(int)(((float(__cdecl*)(int*,int))j_00047974)((int*)g_012F4A30,3)*100.0f+0.5f);
  int isengard=(int)(((float(__cdecl*)(int*,int))j_00047974)((int*)g_012F4A50,3)*100.0f+0.5f);
  int mordor=(int)(((float(__cdecl*)(int*,int))j_00047974)((int*)g_012F4A70,3)*100.0f+0.5f);
  int total=gondor+rohan+isengard+mordor;
  if(total>0) gondor=10000-(rohan+isengard+mordor);
  UnicodeString decimal(L".");
  void *language=TheGlobalLanguageData;
  if(language) decimal.translate(*(AsciiString*)((char*)language+8));
  UnicodeString percent;
  percent.format(UnicodeString(L"%d%s%02d%%"),gondor/100,decimal.str(),gondor%100);
  setText("APT:GondorPercentNum",percent);
  percent.format(UnicodeString(L"%d%s%02d%%"),rohan/100,decimal.str(),rohan%100);
  setText("APT:RohanPercentNum",percent);
  percent.format(UnicodeString(L"%d%s%02d%%"),isengard/100,decimal.str(),isengard%100);
  setText("APT:IsengardPercentNum",percent);
  percent.format(UnicodeString(L"%d%s%02d%%"),mordor/100,decimal.str(),mordor%100);
  setText("APT:MordorPercentNum",percent);
 }
}
