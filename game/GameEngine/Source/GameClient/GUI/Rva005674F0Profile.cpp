// RVA 0x005674F0, 5762 native bytes. The owner retains its address because
// no semantic class identity is established. See docs/analysis/profile_stats_005674f0.md.
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"
#include "unicode_string.h"
inline UnicodeString::UnicodeString()
{
    m_text = 0;
}
inline UnicodeString::UnicodeString(const wchar_t *s)
{
    ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(s);
}
inline UnicodeString::UnicodeString(const UnicodeString &s)
{
    ((StringBase<unsigned short> *)this)
        ->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&s);
}
inline UnicodeString::~UnicodeString()
{
    ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::~StringBase();
}
inline UnicodeString &UnicodeString::operator=(const UnicodeString &s)
{
    ((StringBase<unsigned short> *)this)->set(*(const StringBase<unsigned short> *)&s);
    return *this;
}
extern const UnicodeString BFMEUnicodeEmptyString;
#pragma comment(                                                                                   \
    linker,                                                                                        \
    "/alternatename:?BFMEUnicodeEmptyString@@3VUnicodeString@@B=?TheEmptyString@UnicodeString@@2V1@B")
class Rva005672C0Map
{
  public:
    Rva005672C0Map &operator=(const Rva005672C0Map &other);

    char field00[8];
};

class Rva005673A0Vec
{
  public:
    Rva005673A0Vec &operator=(const Rva005673A0Vec &other);

  private:
    void *m_head;
};

// The copied argument is 24-byte SkirmishPreferences: its matched complete
// destructor is the final call, and the caller invokes its copy constructor.
// The receiver holds the same bounded view after a four-byte prefix.
// The string at +10 has no member-name witness here; getUserName queries the map.
class SkirmishPreferences
{
  public:
    virtual ~SkirmishPreferences();

    UnicodeString getUserName();

  public:
    Rva005672C0Map m_map;
    char m_unmodelled_0c[4];
    UnicodeString field10;
    Rva005673A0Vec field14;
};

class GameTextInterface
{
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
    virtual UnicodeString fetch(const char *label, bool *exists = 0);
};

class WindowManager
{
  public:
    void bfme_setAptText(const AsciiString &name, const UnicodeString &text);
};

extern GameTextInterface *TheGameText;
extern WindowManager *g_theWindowManager;
extern "C" __declspec(dllimport) unsigned int __cdecl bfmeLenVGI(const unsigned short *text);

class SkirmishBattleHonors
{
  public:
    SkirmishBattleHonors(UnicodeString userName);
    virtual ~SkirmishBattleHonors();

    AsciiString getProfileCreatedDate();
    int rva0009c6f0() const;
    int getLosses() const;
    int getOverallWinStreak() const;
    int getOverallBestWinStreak() const;
    int getOverallWorstLossStreak() const;
    UnicodeString getFavoriteSideName();

    int getWins(AsciiString side) const;
    int getLosses(AsciiString side) const;
    int getWinStreak(AsciiString side) const;
    int getLossStreak(AsciiString side) const;
    int getBestWinStreak(AsciiString side) const;

    Rva005672C0Map m_map;
    char m_unmodelled_0c[4];
    UnicodeString field10;
    char field14[40];
};

class Rva005674F0Profile
{
  public:
    void apply(SkirmishPreferences value);

  private:
    char m_unmodelled_prefix[4];
    SkirmishPreferences m_preferences;
};

static __forceinline void rva005674F0SetText(const char *name, const UnicodeString &source)
{
    AsciiString variableName(name);
    UnicodeString text(source);
    g_theWindowManager->bfme_setAptText(variableName, text);
}
static __forceinline void rva005674F0SetNumber(UnicodeString &text, const char *name, int value)
{
    text.format(UnicodeString(L"%d"), value);
    rva005674F0SetText(name, text);
}
static __forceinline void rva005674F0SetStreakText(UnicodeString &text, const char *name,
                                                   const UnicodeString &kind)
{
    text.format(TheGameText->fetch("APT:CurrentStreakStrFormat"), kind.str());
    rva005674F0SetText(name, text);
}
static __forceinline void rva005674F0SetFaction(SkirmishBattleHonors &honors, AsciiString &side,
                                                UnicodeString &text, const UnicodeString &winFormat,
                                                const UnicodeString &lossFormat,
                                                const char *winsName, const char *lossesName,
                                                const char *streakName, const char *streakNumName,
                                                const char *bestName)
{
    rva005674F0SetNumber(text, winsName, honors.getWins(side));
    rva005674F0SetNumber(text, lossesName, honors.getLosses(side));
    if (honors.getLossStreak(side) != 0)
    {
        rva005674F0SetStreakText(text, streakName, lossFormat);
        rva005674F0SetNumber(text, streakNumName, honors.getLossStreak(side));
    }
    else
    {
        rva005674F0SetStreakText(text, streakName, winFormat);
        rva005674F0SetNumber(text, streakNumName, honors.getWinStreak(side));
    }
    rva005674F0SetNumber(text, bestName, honors.getBestWinStreak(side));
}

// Formats the copied profile into the 37 witnessed APT statistic fields.
void Rva005674F0Profile::apply(SkirmishPreferences value)
{
    Rva005672C0Map &currentMap = m_preferences.m_map;
    currentMap = value.m_map;
    UnicodeString &currentName = m_preferences.field10;
    currentName = value.field10;
    m_preferences.field14 = value.field14;

    SkirmishBattleHonors honors(((SkirmishPreferences *)&value)->getUserName());
    UnicodeString text;
    AsciiString currentSide;
    AsciiString sideA("Gondor");
    AsciiString sideB("Rohan");
    AsciiString sideD("Isengard");
    AsciiString sideC("Mordor");
    UnicodeString winFormat = TheGameText->fetch("Apt:Win");
    UnicodeString lossFormat = TheGameText->fetch("Apt:Loss");

    {

        text.translate(honors.getProfileCreatedDate());
        rva005674F0SetText("APT:ProfileCreatedNum", text);
    }
    rva005674F0SetNumber(text, "APT:OverallCareerWinsNum", honors.rva0009c6f0());
    rva005674F0SetNumber(text, "APT:OverallCareerLossesNum", honors.getLosses());
    rva005674F0SetNumber(text, "APT:CurrentWinStreakNum", honors.getOverallWinStreak());
    rva005674F0SetNumber(text, "APT:BestWinStreakNum", honors.getOverallBestWinStreak());
    rva005674F0SetNumber(text, "APT:WorstLossStreakNum", honors.getOverallWorstLossStreak());

    {

        text.format(((SkirmishPreferences *)&value)->getUserName());
        rva005674F0SetText("APT:PlayerNameNum", text);
    }

    {

        text = honors.getFavoriteSideName();
        if (text.compare(BFMEUnicodeEmptyString) != 0)
            ;
        else
        {
            static const unsigned short emptyFavorite[] = {'-', '-', 0};
            ((StringBase<unsigned short> *)&text)->concat(emptyFavorite, bfmeLenVGI(emptyFavorite));
        }
        rva005674F0SetText("APT:FavoriteSideNum", text);
    }

    rva005674F0SetNumber(text, "APT:TotalGamesPlayedNum", honors.getLosses() + honors.rva0009c6f0());

    currentSide = sideA;
    rva005674F0SetFaction(honors, currentSide, text, winFormat, lossFormat, "APT:WinsANum",
                          "APT:LossesANum", "APT:CurrentStreakA", "APT:CurrentStreakANum",
                          "APT:BestWinStreakANum");
    currentSide = sideB;
    rva005674F0SetFaction(honors, currentSide, text, winFormat, lossFormat, "APT:WinsBNum",
                          "APT:LossesBNum", "APT:CurrentStreakB", "APT:CurrentStreakBNum",
                          "APT:BestWinStreakBNum");
    currentSide = sideD;
    rva005674F0SetFaction(honors, currentSide, text, winFormat, lossFormat, "APT:WinsCNum",
                          "APT:LossesCNum", "APT:CurrentStreakC", "APT:CurrentStreakCNum",
                          "APT:BestWinStreakCNum");
    currentSide = sideC;
    rva005674F0SetFaction(honors, currentSide, text, winFormat, lossFormat, "APT:WinsDNum",
                          "APT:LossesDNum", "APT:CurrentStreakD", "APT:CurrentStreakDNum",
                          "APT:BestWinStreakDNum");
}
