// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Igame/Libraries/Source/WWVegas/WWLib /D_STLP_USE_STATIC_LIB
// stlport
// Native reconstruction of the complete 9420-byte OnlineProfile method.
// Address-derived method identity; matched ctor00557C00 calls ILT00032849.
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

namespace _STL {
typedef pair<const int, unsigned int> ProfilePair;
typedef _Rb_tree<int, ProfilePair, _Select1st<ProfilePair>, less<int>, allocator<ProfilePair> >
    ProfileTree;
template <>
template <>
__forceinline _Rb_tree_node<ProfilePair> *ProfileTree::_M_find<int>(const int &key) const {
    _Link_type y = this->_M_header._M_data;
    _Link_type x = _M_root();
    while (x != 0) {
        if (!_M_key_compare(_S_key(x), key)) {
            y = x;
            x = _S_left(x);
        } else
            x = _S_right(x);
    }
    if (y == this->_M_header._M_data || _M_key_compare(key, _S_key(y)))
        y = this->_M_header._M_data;
    return y;
}
template <> template <> __forceinline ProfileTree::iterator ProfileTree::find<int>(const int &key) {
    return iterator(_M_find(key));
}
template <>
__forceinline map<int, unsigned int>::iterator map<int, unsigned int>::find(const int &key) {
    return _M_t.find(key);
}
} // namespace _STL

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
class UserPreferences {
  public:
    virtual ~UserPreferences();
    virtual bool write();
    std::map<AsciiString, AsciiString> preferences;
    AsciiString filename;
};
class QuickMatchPreferences : public UserPreferences {
  public:
    QuickMatchPreferences();
    virtual ~QuickMatchPreferences();
};
typedef char PrefSize[sizeof(QuickMatchPreferences) == 20 ? 1 : -1];
class GameTextInterface {
  public:
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual UnicodeString fetch(const char *, bool * = 0);
};
class GameSpyInfoInterface {
  public:
#define SLOT(n) virtual void s##n();
    SLOT(00)
    SLOT(04) SLOT(08) SLOT(0c) SLOT(10) SLOT(14) SLOT(18) SLOT(1c) SLOT(20) SLOT(24) SLOT(28)
        SLOT(2c) SLOT(30) SLOT(34) SLOT(38) SLOT(3c) SLOT(40) SLOT(44) SLOT(48) SLOT(4c) SLOT(50)
            SLOT(54) SLOT(58) SLOT(5c) SLOT(60) SLOT(64) virtual AsciiString getLocalName();
    SLOT(6c)
    SLOT(70) SLOT(74) SLOT(78) SLOT(7c) SLOT(80) SLOT(84) SLOT(88) SLOT(8c) virtual PSPlayerStats
        rva90();
#undef SLOT
};
class WindowManager {
  public:
    void bfme_setAptText(const AsciiString &, const UnicodeString &);
};
extern WindowManager *g_theWindowManager;
extern GameTextInterface *TheGameText;
extern GameSpyInfoInterface *TheGameSpyInfo;
extern "C" int *g_bfmeLimitsDF;
extern int g_bfmePeerReqE4, g_bfmePeerReqE8;
extern const char *g_bfmeOnlineProfileImageLevelIconA;
extern const char *g_bfmeOnlineProfileImageLevelIconB;
extern const char *g_bfmeOnlineProfileImageLevelIconC;
extern const char *g_bfmeOnlineProfileImageLevelIconD;
extern void j_0003cc54();
extern void j_00022976();
extern void j_0000132f();
extern void j_000136a1();
extern void j_0001681a();
template <class M> __forceinline M retailMethod(void (*raw)()) {
    union {
        void (*entry)();
        M method;
    } f;
    f.entry = raw;
    return f.method;
}
struct Rva0055CD80Owner {
    void call() {
        typedef void (Rva0055CD80Owner::*M)();
        (this->*retailMethod<M>(j_0003cc54))();
    }
};
struct Rva0046C770Owner {};
struct _SYSTEMTIME {
    unsigned short wYear, wMonth, wDayOfWeek, wDay, wHour, wMinute, wSecond, wMilliseconds;
};
UnicodeString getUnicodeDateBuffer(_SYSTEMTIME);
static __forceinline void setText(const char *name, const UnicodeString &source) {
    AsciiString key(name);
    UnicodeString text(source);
    g_theWindowManager->bfme_setAptText(key, text);
}
static __forceinline void setNumber(UnicodeString &text, const char *key, int value) {
    text.format(UnicodeString(L"%d"), value);
    setText(key, text);
}
static __forceinline int total(const PerGeneralMap &map) {
    int result = 0;
    for (PerGeneralMap::const_iterator i = map.begin(); i != map.end(); ++i)
        result += i->second;
    return result;
}
static __forceinline unsigned int count(PerGeneralMap &map, int key) {
    PerGeneralMap::iterator i = map.find(key);
    unsigned result = 0;
    if (i != map.end())
        result = i->second;
    return result;
}
// The last three searches are out of line in retail through ILT0002EFCD.
// Its 71-byte tree-find body returns a one-pointer native iterator, ret8.
class Rva005466C0Tree {
  public:
    __declspec(noinline) PerGeneralMap::iterator find(const int &key);
};
PerGeneralMap::iterator Rva005466C0Tree::find(const int &key) {
    return ((PerGeneralMap *)this)->find(key);
}
static __forceinline unsigned int countTail(PerGeneralMap &map, int key) {
    PerGeneralMap::iterator i = ((Rva005466C0Tree *)&map)->find(key);
    unsigned result = 0;
    if (i != map.end())
        result = i->second;
    return result;
}
static __forceinline int rank(PSPlayerStats &stats, int side) {
    int points = ((int(__cdecl *)(PSPlayerStats *, int))j_00022976)(&stats, side);
    int result = 1;
    while (result < 10 && points >= g_bfmeLimitsDF[result])
        ++result;
    return result;
}
static __forceinline void level(UnicodeString &text, PSPlayerStats &stats, int side,
                                const char *key) {
    text.format(TheGameText->fetch("APT:CurrentLevelNumFormat"), rank(stats, side));
    setText(key, text);
}
static __forceinline void icon(PSPlayerStats &stats, int side, const char *const &name) {
    void *image = ((void *(__cdecl *)(int, int))j_000136a1)(rank(stats, side), side);
    typedef void (Rva0046C770Owner::*M)(const AsciiString &, void *);
    (((Rva0046C770Owner *)g_theWindowManager)->*retailMethod<M>(j_0001681a))(AsciiString(name),
                                                                             image);
}
static __forceinline void nextLevel(UnicodeString &text, PSPlayerStats &stats, int side,
                                    const char *key) {
    int points = ((int(__cdecl *)(PSPlayerStats, int))j_0000132f)(stats, side);
    if (points == 1)
        text.format(TheGameText->fetch("APT:NextLevelNumFormatForOnePoint"), 1);
    else
        text.format(TheGameText->fetch("APT:NextLevelNumFormat"), points);
    setText(key, text);
}
static __forceinline void streak(UnicodeString &text, PSPlayerStats &stats, int side,
                                 const UnicodeString &win, const UnicodeString &loss,
                                 const char *label, const char *number) {
    unsigned value = 0;
    PerGeneralMap::iterator i = stats.currentLossStreaks.find(side);
    if (i != stats.currentLossStreaks.end())
        value = i->second;
    if (value) {
        text.format(TheGameText->fetch("APT:CurrentStreakStrFormat"), loss.str());
        setText(label, text);
    } else {
        i = stats.currentWinStreaks.find(side);
        if (i != stats.currentWinStreaks.end())
            value = i->second;
        text.format(TheGameText->fetch("APT:CurrentStreakStrFormat"), win.str());
        setText(label, text);
    }
    setNumber(text, number, value);
}
template <class T> __forceinline const T &profileMin(const T &a, const T &b) {
    return a < b ? a : b;
}
class BfmeOnlineProfileScreen {
  public:
    void rva00554AA0();

  private:
    char field00[0x34];
    Rva0055CD80Owner *field34;
    int field38;
};
void BfmeOnlineProfileScreen::rva00554AA0() {
    field34->call();
    QuickMatchPreferences prefs;
    UnicodeString text;
    AsciiString sideName;
    UnicodeString gondor = TheGameText->fetch("Apt:Gondor");
    UnicodeString rohan = TheGameText->fetch("Apt:Rohan");
    UnicodeString isengard = TheGameText->fetch("Apt:Isengard");
    UnicodeString mordor = TheGameText->fetch("Apt:Mordor");
    UnicodeString win = TheGameText->fetch("Apt:Win");
    UnicodeString loss = TheGameText->fetch("Apt:Loss");
    AsciiString name = TheGameSpyInfo->getLocalName();
    PSPlayerStats stats = TheGameSpyInfo->rva90();
    int year = 0, month = 0, day = 0;
    if (sscanf(stats.dateCreated.c_str(), "%d/%d/%d", &month, &day, &year) == 3) {
        _SYSTEMTIME date;
        memset(&date, 0, sizeof(date));
        date.wDay = day;
        date.wMonth = month;
        date.wYear = year;
        text = getUnicodeDateBuffer(date);
    } else
        text.translate(AsciiString(stats.dateCreated.c_str()));
    setText("APT:ProfileCreatedNum", text);
    text.translate(name);
    setText("APT:PlayerNameNum", text);
    setNumber(text, "APT:OverallCareerWinsNum", total(stats.wins));
    setNumber(text, "APT:OverallCareerLossesNum", total(stats.losses));
    setNumber(text, "APT:CurrentWinStreakProfileNum", stats.winsInARow);
    setNumber(text, "APT:BestWinStreakProfileNum", stats.maxWinsInARow);
    setNumber(text, "APT:CurrentLossStreakProfileNum", stats.lossesInARow);
    setNumber(text, "APT:WorstLossStreakNum", stats.maxLossesInARow);
    unsigned most = 0;
    int favorite = 0;
    for (PerGeneralMap::iterator i = stats.games.begin(); i != stats.games.end(); ++i) {
        if (i->second > most) {
            most = i->second;
            favorite = i->first;
        }
    }
    if (!most)
        text = gondor;
    else
        switch (favorite) {
        case 1:
            text = gondor;
            break;
        case 3:
            text = isengard;
            break;
        case 0:
            text = rohan;
            break;
        case 2:
            text = mordor;
            break;
        }
    setText("APT:FavoriteSideNum", text);
    setNumber(text, "APT:CareerLadderGames1vs1Num", stats.gamesOn1_1_Ladder);
    setNumber(text, "APT:CareerLadderGames2vs2Num", stats.gamesOn2_2_Ladder);
    if (g_bfmePeerReqE4 > 0) {
        if (stats.best1v1LadderRank > 0)
            stats.best1v1LadderRank = profileMin(g_bfmePeerReqE4, stats.best1v1LadderRank);
        else
            stats.best1v1LadderRank = g_bfmePeerReqE4;
    }
    if (stats.best1v1LadderRank == -1)
        g_theWindowManager->bfme_setAptText(AsciiString("APT:HighestRankANum"),
                                            UnicodeString(L"--"));
    else
        setNumber(text, "APT:HighestRankANum", stats.best1v1LadderRank);
    if (g_bfmePeerReqE8 > 0) {
        if (stats.best2v2LadderRank > 0)
            stats.best2v2LadderRank = profileMin(g_bfmePeerReqE8, stats.best2v2LadderRank);
        else
            stats.best2v2LadderRank = g_bfmePeerReqE8;
    }
    if (stats.best2v2LadderRank == -1)
        g_theWindowManager->bfme_setAptText(AsciiString("APT:HighestRankBNum"),
                                            UnicodeString(L"--"));
    else
        setNumber(text, "APT:HighestRankBNum", stats.best2v2LadderRank);
    prefs.UserPreferences::write();
    text.format(UnicodeString(L"In Progress"));
    setText("APT:CareerDisconnectsNum", text);
    sideName.translate(gondor);
    level(text, stats, 1, "APT:CurrentLevelA");
    sideName.translate(rohan);
    level(text, stats, 0, "APT:CurrentLevelB");
    sideName.translate(isengard);
    level(text, stats, 3, "APT:CurrentLevelC");
    sideName.translate(mordor);
    level(text, stats, 2, "APT:CurrentLevelD");
    icon(stats, 1, g_bfmeOnlineProfileImageLevelIconA);
    icon(stats, 0, g_bfmeOnlineProfileImageLevelIconB);
    icon(stats, 3, g_bfmeOnlineProfileImageLevelIconC);
    icon(stats, 2, g_bfmeOnlineProfileImageLevelIconD);
    sideName.translate(gondor);
    nextLevel(text, stats, 1, "APT:NextLevelA");
    sideName.translate(rohan);
    nextLevel(text, stats, 0, "APT:NextLevelB");
    sideName.translate(isengard);
    nextLevel(text, stats, 3, "APT:NextLevelC");
    sideName.translate(mordor);
    nextLevel(text, stats, 2, "APT:NextLevelD");
    sideName.translate(gondor);
    setNumber(text, "APT:WinsANum", count(stats.wins, 1));
    sideName.translate(rohan);
    setNumber(text, "APT:WinsBNum", count(stats.wins, 0));
    sideName.translate(isengard);
    setNumber(text, "APT:WinsCNum", count(stats.wins, 3));
    sideName.translate(mordor);
    setNumber(text, "APT:WinsDNum", count(stats.wins, 2));
    setNumber(text, "APT:LossesANum", count(stats.losses, 1));
    setNumber(text, "APT:LossesBNum", count(stats.losses, 0));
    setNumber(text, "APT:LossesCNum", count(stats.losses, 3));
    setNumber(text, "APT:LossesDNum", count(stats.losses, 2));
    streak(text, stats, 1, win, loss, "APT:CurrentStreakA", "APT:CurrentStreakANum");
    streak(text, stats, 0, win, loss, "APT:CurrentStreakB", "APT:CurrentStreakBNum");
    streak(text, stats, 3, win, loss, "APT:CurrentStreakC", "APT:CurrentStreakCNum");
    streak(text, stats, 2, win, loss, "APT:CurrentStreakD", "APT:CurrentStreakDNum");
    setNumber(text, "APT:BestWinStreakANum", count(stats.bestWinStreaks, 1));
    setNumber(text, "APT:BestWinStreakBNum", countTail(stats.bestWinStreaks, 0));
    setNumber(text, "APT:BestWinStreakCNum", countTail(stats.bestWinStreaks, 3));
    setNumber(text, "APT:BestWinStreakDNum", countTail(stats.bestWinStreaks, 2));
}
