// ?_bfme_updateProfileDisplay@BfmeAptScreenSkirmish@@QAEXXZ
// partial score=0.9573 date=2026-10-03
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /FAsc /Fa/tmp/bfmeProfileDisplay.cod
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
  ((StringBase<unsigned short> *)this)
      ->StringBase<unsigned short>::~StringBase();
}
inline UnicodeString &UnicodeString::operator=(const UnicodeString &s) {
  ((StringBase<unsigned short> *)this)
      ->set(*(const StringBase<unsigned short> *)&s);
  return *this;
}
extern const UnicodeString BFMEUnicodeEmptyString;
#pragma comment(                                                               \
    linker,                                                                    \
    "/alternatename:?BFMEUnicodeEmptyString@@3VUnicodeString@@B=?TheEmptyString@UnicodeString@@2V1@B")

#include <stdlib.h>
class GameTextInterface {
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
  virtual UnicodeString fetch(const char *, bool * = 0);
};
class WindowManager {
public:
  void bfme_setAptText(const AsciiString &, const UnicodeString &);
  void *_bfme_callAptFunction(unsigned, const char *, int, const char *,
                              const char *, const char *, const char *,
                              const char *);
};
extern GameTextInterface *TheGameText;
extern const char *Rva012B8054ProfileIconName;
extern WindowManager *g_theWindowManager;
class BfmeA1024 {
public:
  void bfmeGo1024A(int, int);
};
inline void rva0046c790(const AsciiString &name, const AsciiString &icon) {
  ((BfmeA1024 *)g_theWindowManager)->bfmeGo1024A((int)&name, (int)&icon);
}
inline void callAptFunction(unsigned level, const char *name, int count,
                            const char *a, const char *b, const char *c,
                            const char *d, const char *e) {
  g_theWindowManager->_bfme_callAptFunction(level, name, count, a, b, c, d, e);
}
class SkirmishPreferences {
public:
  bool unidentified_00017AF8();
  UnicodeString getUserName();
  char field00[24];
};
class SkirmishBattleHonors {
public:
  AsciiString getProfileCreatedDate();
  int getWins(AsciiString) const;
  int getLosses(AsciiString) const;
  int getWinStreak(AsciiString) const;
  int getBestWinStreak(AsciiString) const;
  float getTimePlayed(AsciiString) const;
  UnicodeString rva0009c4b0(float);
  int getRank(AsciiString) const;
  int getPointsToNextRank(AsciiString, int) const;
  int getRankWidth(AsciiString, int) const;
};
// RVA 0009C4B0 is already owned by bfmeTimePlayedAM (205 B).
// Its current stdcall/UnicodeStringAM ledger spelling does not describe
// this caller's witnessed ECX receiver + hidden UnicodeString return.
// A narrowly reviewed ownership/signature repair is required on landing;
// do not invent a semantic method name or treat this as an absent body.
class GameSlot {
public:
  char field00[0x14];
  int field14;
};
class GameInfo {
public:
  GameSlot *getSlot(int);
};
extern GameInfo *g_bfmeCurrentCB;
class PlayerTemplate {
public:
  char field00[8];
  AsciiString field08;
};
class PlayerTemplateStore {
public:
  const PlayerTemplate *getNthPlayerTemplate(int) const;
};
extern PlayerTemplateStore *ThePlayerTemplateStore;
class BfmeAptScreenSkirmish {
public:
  void _bfme_updateProfileDisplay();
  void tooltipPlayerLevelIcon(AsciiString, void *);
  char field00[0x250];
  unsigned field250;
  char field254[0x3ac - 0x254];
  SkirmishPreferences preferences;
  SkirmishBattleHonors honors;
};
inline const int &rva0057a470Clamp(const int &value, const int &low,
                                   const int &high) {
  const int &a = value < low ? low : value;
  return a < high ? a : high;
}
static __forceinline void setText(const char *name,
                                  const UnicodeString &source) {
  AsciiString key(name);
  UnicodeString copy(source);
  g_theWindowManager->bfme_setAptText(key, copy);
}
void BfmeAptScreenSkirmish::_bfme_updateProfileDisplay() {
  UnicodeString text;
  UnicodeString dash;
  char fallbackMovie[16];
  char factionMovie[16];
  dash.format(TheGameText->fetch("APT:DashDash"));
  int faction;
  if (!preferences.unidentified_00017AF8()) {
    text.format(dash);
    setText("APT:SkirmishProfileCreatedNum", text);
    setText("APT:PlayerNameNum", text);
    setText("APT:TotalCareerWinsNum", text);
    setText("APT:TotalCareerLossesNum", text);
    setText("APT:TotalCareerGamesNum", text);
    setText("APT:CurrentWinStreakNumA", text);
    setText("APT:BestWinStreakNumA", text);
    setText("APT:TotalTimePlayedNum", text);
    setText("APT:CurFactionNameStr", text);
    setText("APT:NextWinsNumber", text);
    text.format(TheGameText->fetch("APT:CurrentLevelFormat"), dash.str());
    setText("APT:CurrentLevelFormat", text);
  } else if (!g_bfmeCurrentCB ||
             (faction = g_bfmeCurrentCB->getSlot(0)->field14) == -1 ||
             faction == -2) {
    AsciiString created = honors.getProfileCreatedDate();
    text.translate(created);
    setText("APT:SkirmishProfileCreatedNum", text);
    text.format(preferences.getUserName());
    setText("APT:PlayerNameNum", text);
    text.format(dash);
    setText("APT:TotalCareerWinsNum", text);
    setText("APT:TotalCareerLossesNum", text);
    setText("APT:TotalCareerGamesNum", text);
    setText("APT:CurrentWinStreakNumA", text);
    setText("APT:BestWinStreakNumA", text);
    setText("APT:TotalTimePlayedNum", text);
    setText("APT:CurFactionNameStr", text);
    setText("APT:NextWinsNumber", text);
    text.format(TheGameText->fetch("APT:CurrentLevelFormat"), dash.str());
    setText("APT:CurrentLevelFormat", text);
    _itoa(0, fallbackMovie, 10);
    callAptFunction(field250, "ShowSkirmishMovie", 1, fallbackMovie, 0, 0, 0,
                    0);
    rva0046c790(AsciiString(Rva012B8054ProfileIconName),
                AsciiString("AptRankIcon0"));
    callAptFunction(field250, "SetProgressBar", 1, "0", 0, 0, 0, 0);
  } else {
    AsciiString side =
        ThePlayerTemplateStore->getNthPlayerTemplate(faction)->field08;
    AsciiString created = honors.getProfileCreatedDate();
    text.translate(created);
    setText("APT:SkirmishProfileCreatedNum", text);
    text.format(preferences.getUserName());
    setText("APT:PlayerNameNum", text);
    text.format(UnicodeString(L"%d"), honors.getWins(side));
    setText("APT:TotalCareerWinsNum", text);
    text.format(UnicodeString(L"%d"), honors.getLosses(side));
    setText("APT:TotalCareerLossesNum", text);
    text.format(UnicodeString(L"%d"),
                honors.getWins(side) + honors.getLosses(side));
    setText("APT:TotalCareerGamesNum", text);
    text.format(UnicodeString(L"%d"), honors.getWinStreak(side));
    setText("APT:CurrentWinStreakNumA", text);
    text.format(UnicodeString(L"%d"), honors.getBestWinStreak(side));
    setText("APT:BestWinStreakNumA", text);
    text.format(honors.rva0009c4b0(honors.getTimePlayed(side)));
    setText("APT:TotalTimePlayedNum", text);
    text.translate(side);
    if (faction == 4) {
      text.format(TheGameText->fetch("APT:GondorCaps"));
      setText("APT:CurFactionNameStr", text);
    } else if (faction == 3) {
      text.format(TheGameText->fetch("APT:RohanCaps"));
      setText("APT:CurFactionNameStr", text);
    } else if (faction == 5) {
      text.format(TheGameText->fetch("APT:IsengardCaps"));
      setText("APT:CurFactionNameStr", text);
    } else if (faction == 6) {
      text.format(TheGameText->fetch("APT:MordorCaps"));
      setText("APT:CurFactionNameStr", text);
    }
    _itoa(faction, factionMovie, 10);
    callAptFunction(field250, "ShowSkirmishMovie", 1, factionMovie, 0, 0, 0, 0);
    int rank = honors.getRank(side);
    text.format(TheGameText->fetch("APT:CurrentLevelNumFormat"), rank);
    setText("APT:CurrentLevelFormat", text);
    int points = honors.getPointsToNextRank(side, rank);
    if (points == 1)
      text.format(TheGameText->fetch("APT:WinsNumFormatForOnePoint"), points);
    else
      text.format(TheGameText->fetch("APT:WinsNumFormat"), points);
    setText("APT:NextWinsNumber", text);
    int width = honors.getRankWidth(side, rank);
    int remaining = honors.getPointsToNextRank(side, rank);
    int denominator = honors.getRankWidth(side, rank);
    int percent =
        (int)((float)(width - remaining) / (float)denominator * 100.0f);
    percent = rva0057a470Clamp(percent, 0, 100);
    char progress[256];
    _itoa(percent, progress, 10);
    callAptFunction(field250, "SetProgressBar", 1, progress, 0, 0, 0, 0);
    tooltipPlayerLevelIcon(side, (void *)Rva012B8054ProfileIconName);
  }
}
