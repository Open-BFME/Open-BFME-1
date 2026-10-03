// Retail 0x00546E00 (519 bytes). OnlineHome constructor 0x005484E0 binds
// OnlineShell/OnlineHome/tooltipPlayerLevelIcon to ILT 0x000316E2 -> this body.
// PSPlayerStats is returned at vslot 0x90; the retail body reads its +0x178.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "../../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"
#include <string.h>
#pragma intrinsic(strlen)

template <typename T> inline void StringBase<T>::set(const T *s) { set(s, s ? strlen((const char*)s) : 0); }
template <typename T> inline void StringBase<T>::concat(const StringBase<T>& s) {
    concat(s.m_data ? s.m_data->data : (const T*)"", s.m_data ? s.m_data->length : 0);
}
inline UnicodeString::UnicodeString() : m_text(0) {}
inline UnicodeString::UnicodeString(const UnicodeString& s) {
    ((StringBase<unsigned short>*)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short>*)&s);
}
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->StringBase<unsigned short>::~StringBase(); }

class PSPlayerStats {
public:
    ~PSPlayerStats();
    unsigned char bytes[0x1c4];
};
class GameSpyInfo {
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
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3C();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4C();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5C();
    virtual void slot60();
    virtual void slot64();
    virtual void slot68();
    virtual void slot6C();
    virtual void slot70();
    virtual void slot74();
    virtual void slot78();
    virtual void slot7C();
    virtual void slot80();
    virtual void slot84();
    virtual void slot88();
    virtual void slot8C();
    virtual PSPlayerStats getCachedLocalPlayerStats();
};
class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;
// Retail's per-rank APT label tables for the player-level tooltip, indexed by
// rank 0..9.  Neither address is recorded in dir32_addresses.csv, so they keep
// address-derived names; the pointer-to-const-char shape is what the body reads.
extern "C" const char *g_012B78F0[];
extern "C" const char *g_012B78C8[];
class Gen_uw_00025c1b;
int bfmeRankPointsFromStats(Gen_uw_00025c1b*,int);
// RankPointValue.h (SAGE upstream) declares `extern RankPoints
// *TheRankPointValues`; this TU's include environment has no copy of it, so the
// type is declared locally with the m_ranks shape the body reads. The mangled
// name of the pointer is what retail references at 0x012F401C.
struct RankPoints
{
    int m_ranks[10];
};
extern RankPoints *TheRankPointValues;
bool Rva004D8F50(int);
class GameTextInterface {
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
    virtual UnicodeString fetch(const char*,bool* = 0);
    virtual UnicodeString fetch(AsciiString,bool* = 0);
};
extern GameTextInterface *TheGameText;
struct RGBColor;
class Mouse { public: void setCursorTooltip(UnicodeString,int,const RGBColor*,float); };
extern Mouse *TheMouse;
class BfmeAptScreenOnlineHome { public: void tooltipPlayerLevelIcon(void*); };
void BfmeAptScreenOnlineHome::tooltipPlayerLevelIcon(void*) {
    PSPlayerStats stats = reinterpret_cast<GameSpyInfo *>(TheGameSpyInfo)->getCachedLocalPlayerStats();
    int side = *(int*)(stats.bytes + 0x178);
    if(side < 0 || side >= 4) side = 1;
    int points = bfmeRankPointsFromStats((Gen_uw_00025c1b*)&stats,side);
    int rank = 0;
    for(;rank < 10; ++rank) if(points < TheRankPointValues->m_ranks[rank+1]) break;
    AsciiString key("TOOLTIP:");
    AsciiString name;
    if(Rva004D8F50(side)) name.set(g_012B78F0[rank]);
    else name.set(g_012B78C8[rank]);
    key.concat(name);
    UnicodeString level = TheGameText->fetch(key);
    UnicodeString tooltip;
    tooltip.format(TheGameText->fetch("APT:CurrentLevelStringFormat"),level.str());
    TheMouse->setCursorTooltip(tooltip,-1,0,1.0f);
}

