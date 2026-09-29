// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x00554510, 957 bytes. Recognizes the four OnlineProfile faction
// level-icon tooltip paths and builds the localized rank tooltip. The original
// callback name/owner are unproven; retain the address. ECX is unused and RET 4
// consumes the sole string argument.
// The returned stats object occupies 0x1C4 bytes, matching PSPlayerStats in the
// byte-matched adjacent BfmeOnlineProfileScreenRva00554AA0.cpp. Preserve the
// existing address-derived helper type used by bfmeRankPointsFromStats.
// GameSpy slot 0x90 returns that nontrivial object. GameText fetch slots are
// 0x24 (AsciiString by value) and 0x28 (C string); MSVC reverses overload slots.
// Rank-label tables: good VA 0x012B7AE0, evil VA 0x012B7B08. Limits pointer:
// 0x012F401C. Literal spelling is read from the retail image, including Apt:.
#include "ascii_string.h"
#include <wchar.h>
#include <string.h>
#include "Common/UnicodeString.h"
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->releaseBuffer(); }
template<class T> inline void StringBase<T>::set(const T *s) { set(s,s?strlen((const char*)s):0); }
template<class T> inline void StringBase<T>::concat(const StringBase<T>& s) { int n=s.m_data?s.m_data->length:0; const T* p=s.m_data?s.m_data->data:(const T*)""; concat(p,n); }
class Gen_uw_00025c1b { public: ~Gen_uw_00025c1b(); char field00[0x1c4]; };
int bfmeRankPointsFromStats(Gen_uw_00025c1b*,int);
int bfmeBand(int);
extern "C" int *g_bfmeLimitsDF;
extern const char *RankLabels00554510Good[];
extern const char *RankLabels00554510Evil[];
class GameSpyInfoInterface { public:
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
 virtual void slot28();
 virtual void slot2c();
 virtual void slot30();
 virtual void slot34();
 virtual void slot38();
 virtual void slot3c();
 virtual void slot40();
 virtual void slot44();
 virtual void slot48();
 virtual void slot4c();
 virtual void slot50();
 virtual void slot54();
 virtual void slot58();
 virtual void slot5c();
 virtual void slot60();
 virtual void slot64();
 virtual void slot68();
 virtual void slot6c();
 virtual void slot70();
 virtual void slot74();
 virtual void slot78();
 virtual void slot7c();
 virtual void slot80();
 virtual void slot84();
 virtual void slot88();
 virtual void slot8c();
 virtual Gen_uw_00025c1b stats90();
};
extern GameSpyInfoInterface *TheGameSpyInfo;
class GameTextInterface { public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0c();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1c();
 virtual void slot20();
 virtual UnicodeString fetch(const char*,bool * = 0);
 virtual UnicodeString fetch(AsciiString,bool * = 0);
};
extern GameTextInterface *TheGameText;
struct RGBColor;
class Mouse { public: void setCursorTooltip(UnicodeString,int,const RGBColor*,float); };
extern Mouse *TheMouse;
void __stdcall rankTooltip00554510(const char *name) {
 AsciiString ascii;
 UnicodeString faction;
 Gen_uw_00025c1b stats=TheGameSpyInfo->stats90();
 bool evil=false;
 int rank=0;
 if(strcmp(name,"OnlineShell/OnlineProfile/tooltipPlayerLevelIconGondor")==0) {
  faction=TheGameText->fetch("Apt:Gondor");
  int points=bfmeRankPointsFromStats(&stats,1);
  rank=1;
  while(rank<10 && points>=g_bfmeLimitsDF[rank]) ++rank;
 } else if(strcmp(name,"OnlineShell/OnlineProfile/tooltipPlayerLevelIconRohan")==0) {
  faction=TheGameText->fetch("Apt:Rohan");
  int points=bfmeRankPointsFromStats(&stats,0);
  rank=1;
  while(rank<10 && points>=g_bfmeLimitsDF[rank]) ++rank;
 } else if(strcmp(name,"OnlineShell/OnlineProfile/tooltipPlayerLevelIconIsengard")==0) {
  faction=TheGameText->fetch("Apt:Isengard");
  rank=bfmeBand(bfmeRankPointsFromStats(&stats,3));
  evil=true;
 } else if(strcmp(name,"OnlineShell/OnlineProfile/tooltipPlayerLevelIconMordor")==0) {
  faction=TheGameText->fetch("Apt:Mordor");
  rank=bfmeBand(bfmeRankPointsFromStats(&stats,2));
  evil=true;
 } else return;
 ascii.translate(faction);
 AsciiString key("TOOLTIP:");
 AsciiString label;
 if(evil) label.set(RankLabels00554510Evil[rank]);
 else label.set(RankLabels00554510Good[rank]);
 key.concat(label);
 UnicodeString level=TheGameText->fetch(key);
 UnicodeString tooltip;
 tooltip.format(TheGameText->fetch("APT:CurrentLevelStringFormat"),level.str());
 TheMouse->setCursorTooltip(tooltip,-1,0,1.0f);
}
