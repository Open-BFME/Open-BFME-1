// ?_bfme_populateSinglePlayer@BfmeAptScreenScoreScreen@@QAEXXZ
// partial score=0.518605332552007 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Igame/Libraries/Source/WWVegas/WWLib /D_STLP_USE_STATIC_LIB
// stlport
// Complete native ScoreScreen single-player population; NOT byte matched.
// Retail00575B70..005768C5 is3413B. Matched opener reaches ILT0003D08C.
// Follow-up GPT-6: full3413B; frame50 exactly; 1643 masked differences,
// positional agreement1770/3413=.518605332552, separate from .979 normalized
// instruction shape. A genuine named __copy result fixes the bit-vector
// frame/return lifetime. Extern global012F1028 is TheLivingWorldLogic;
// TheCampaignManager is independently pinned at a different012F4CB0 slot.
// Canonical body definitions independently reproduce the already-owned33B
// GameLogic wrapper,158B numbered lookup,49B score record getter and112B list
// append. They add no coverage. Five main dependency spellings still need
// supported resolver ownership before landing; no speculative pins were added.
// See identity_evidence/00575b70-score-single-player.md for full provenance,
// value-return/callee proofs and the bounded unsuccessful lifetime variants.
#define _STLP_NO_EXCEPTIONS 1
#include "ascii_string.h"
#include <wchar.h>
template <>
inline void StringBase<unsigned short>::set(const unsigned short *s) {
  set(s, wcslen(s));
}
template <> inline int StringBase<unsigned short>::getLength() const {
  return m_data ? m_data->length : 0;
}
template <>
inline const unsigned short *StringBase<unsigned short>::str() const {
  static const unsigned short TheNullChr = 0;
  return m_data ? m_data->data : &TheNullChr;
}
#include "Common/UnicodeString.h"
#include <algorithm>
#include <list>
#include <vector>
namespace _STL {
template <> __forceinline void vector<bool>::clear() {
  iterator last = end();
  iterator result = __copy(last, end(), begin(), random_access_iterator_tag(),
                           (ptrdiff_t *)0);
  this->_M_finish = result;
}
} // namespace _STL
inline UnicodeString::~UnicodeString() {
  ((StringBase<wchar_t> *)this)->releaseBuffer();
}
extern void j_00028560();
extern void j_00047e38();
extern void j_0002bf0d();
extern void j_0001681a();
extern void j_000045d4();
extern void j_0003cb37();
extern void j_0000a2db();
template <class M> __forceinline M retailMethod(void (*raw)()) {
  union {
    void (*entry)();
    M method;
  } f;
  f.entry = raw;
  return f.method;
}
struct LivingWorldArmy {
  char field00[0x0c];
  int field0c;
  char field10[0x29];
  bool field39;
  char field3a[2];
  int field3c;
  int field40;
  int field44;
  char field48[4];
  AsciiString field4c;
  char field50[0x28];
  UnicodeString field78;
  char field7c[0x38];

  AsciiString getName() const;
};
struct LivingWorldPlayerArmy {
  char field00[0x30];
  _STL::vector<LivingWorldArmy> field30;
};
typedef _STL::vector<LivingWorldPlayerArmy *> ArmyVector;
extern void j_00031507();
class Rva00364E70Owner {
public:
  ArmyVector collect() {
    typedef ArmyVector (Rva00364E70Owner::*M)();
    return (this->*retailMethod<M>(j_00031507))();
  }
};
class GameLogic {
public:
  __declspec(noinline) ArmyVector rva00388BE0();
  char pad[0x170];
  Rva00364E70Owner field170;
};
ArmyVector GameLogic::rva00388BE0() { return field170.collect(); }
class BfmeThingFactory {};
class Image;
struct Rva00575B70Template {
  char field00[0xd0];
  unsigned int fieldd0;
  char fieldd4[0x3fc];
  int field4d0;
  const Image *portrait() const {
    typedef const Image *(Rva00575B70Template::*M)() const;
    return (this->*retailMethod<M>(j_00047e38))();
  }
};
struct S4SortElem12 {
  int m_bfmeKey;
  union {
    int m_bfmeFirst;
    bool flag;
  };
  const Image *m_bfmeSecond;
};
struct S4Cmp00574DF0 {
  void *m_bfmeState;
  bool operator()(const S4SortElem12 &a, const S4SortElem12 &b) const {
    return a.m_bfmeKey < b.m_bfmeKey;
  }
};
struct Rva000E95A0Value {
  UnicodeString field00;
  int field04, field08;
};
class ScoreKeeper {
public:
  int getTotalUnitsDestroyed();
  int getTotalBuildingsDestroyed();
  int getTimeTakenScore();
  int countMissionObjectives(int *);
  int calculateScore();
  int getVictoryType();
};
class Rva000E95A0Owner {
public:
  __declspec(noinline) Rva000E95A0Value value();
  char field00[0x2e8];
  Rva000E95A0Value field2e8;
};
Rva000E95A0Value Rva000E95A0Owner::value() { return field2e8; }
class Rva000E92B0Owner {
public:
  void setWideString(UnicodeString);
};
class Rva003C0E60Owner {
public:
  __declspec(noinline) void insert(Rva000E95A0Value);
  char field00[0xc0];
  _STL::list<Rva000E95A0Value> fieldc0;
};
void Rva003C0E60Owner::insert(Rva000E95A0Value value) {
  fieldc0.push_back(value);
}
class LivingWorldRegionManager {};
class CampaignManager {
public:
  char field00[0x28];
  LivingWorldRegionManager *field28;
  int field2c;
  AsciiString field30;
  unsigned char isMissionObjectiveEligible(int);
  unsigned char isMissionObjectiveIndexed(int);
  unsigned char isMissionObjectiveComplete(int);
  AsciiString rva003BF580(int);
};
class Rva003BDF70Owner {
public:
  int combinedSpanCount();
};
extern void j_00047992();
class Rva00573580Lookup {
public:
  __declspec(noinline) AsciiString number(int);
  AsciiString lookup(AsciiString key) {
    typedef AsciiString (Rva00573580Lookup::*M)(AsciiString);
    return (this->*retailMethod<M>(j_00047992))(key);
  }
};
AsciiString Rva00573580Lookup::number(int n) {
  AsciiString key;
  key.format(AsciiString("%d"), n);
  return lookup(key);
}
struct Rva00575B70Region {
  char field00[0x10];
  AsciiString field10;
  char field14[0x64];
  int field78, field7c, field80;
  const Image *image() const {
    typedef const Image *(Rva00575B70Region::*M)() const;
    return (this->*retailMethod<M>(j_0000a2db))();
  }
};
class WindowManager {
public:
  void bfme_setAptText(const AsciiString &, const UnicodeString &);
  __forceinline void image(const AsciiString &key, const Image *image) {
    typedef void (WindowManager::*M)(const AsciiString &, const Image *);
    (this->*retailMethod<M>(j_0001681a))(key, image);
  }
};
class GameTextInterface {
public:
  virtual void slot00() = 0;
  virtual void slot04() = 0;
  virtual void slot08() = 0;
  virtual void slot0c() = 0;
  virtual void slot10() = 0;
  virtual void slot14() = 0;
  virtual void slot18() = 0;
  virtual void slot1c() = 0;
  virtual void slot20() = 0;
  virtual UnicodeString fetch(AsciiString, bool *) = 0;
};
struct PlayerListView {
  char field00[0xc];
  char *field0c;
};
struct GlobalDataView {
  char field00[0x1224];
  int field1224, field1228, field122c, field1230, field1234, field1238,
      field123c;
  int field1240, field1244, field1248, field124c, field1250;
};
extern PlayerListView *ThePlayers;
extern GlobalDataView *TheWritableGlobalData;
extern CampaignManager *TheLivingWorldLogic;
extern GameLogic *TheGameLogic;
extern BfmeThingFactory *TheThingFactory;
extern WindowManager *g_theWindowManager;
extern GameTextInterface *TheGameText;
class BfmeAptScreenScoreScreen {
public:
  void _bfme_populateSinglePlayer();
  void _bfme_setScoreRegionBonus(int *, const AsciiString &, int);
  __forceinline void rva00573C20(int group, int kind, int value) {
    typedef void (BfmeAptScreenScoreScreen::*M)(int, int, int);
    (this->*retailMethod<M>(j_0003cb37))(group, kind, value);
  }
  char field00[0x25c];
  int field25c;
  char field260[0x18];
  int field278, field27c, field280, field284, field288, field28c, field290;
  int field294[21];
  _STL::vector<bool> field2e8;
  int field2fc;
  AsciiString field300;
  int field304;
  unsigned char field308[8];
};
#define SCORE(N) (*(int *)(score + (N)))
void BfmeAptScreenScoreScreen::_bfme_populateSinglePlayer() {
  field25c = 0;
  char *player = 0;
  if (ThePlayers)
    player = ThePlayers->field0c;
  char *score = 0;
  if (player)
    score = player + 0x348;
  if (!score)
    return;
  ScoreKeeper *keeper = (ScoreKeeper *)score;
  field294[0] = SCORE(0x8c);
  int *battle = field294 + 1;
  *battle = TheWritableGlobalData->field1224;
  field294[3] = keeper->getTotalUnitsDestroyed();
  field294[4] = TheWritableGlobalData->field1228;
  field294[6] = SCORE(0x114);
  field294[7] = TheWritableGlobalData->field122c;
  field294[18] = keeper->getTotalBuildingsDestroyed();
  field294[19] = TheWritableGlobalData->field1230;
  field294[9] = SCORE(0x124);
  field294[10] = TheWritableGlobalData->field1244;
  field294[12] = SCORE(4);
  field294[13] = TheWritableGlobalData->field1240;
  field294[15] = keeper->getTimeTakenScore();
  field294[16] = 1;
  field278 = 0;
  int left = 7;
  do {
    battle[1] = battle[-1] * battle[0];
    field278 += battle[1];
    battle += 3;
  } while (--left);
  if (!TheLivingWorldLogic)
    return;
  field304 = 0;
  for (int objective = 0;
       objective <
       ((Rva003BDF70Owner *)TheLivingWorldLogic)->combinedSpanCount();
       ++objective) {
    if (!TheLivingWorldLogic->isMissionObjectiveEligible(objective))
      continue;
    if (!TheLivingWorldLogic->isMissionObjectiveIndexed(objective))
      continue;
    field308[field304] =
        TheLivingWorldLogic->isMissionObjectiveComplete(objective);
    AsciiString key;
    key.format(AsciiString("APT:objective%d"), field304 + 1);
    g_theWindowManager->bfme_setAptText(
        key,
        TheGameText->fetch(TheLivingWorldLogic->rva003BF580(objective), 0));
    ++field304;
  }
  field27c =
      keeper->countMissionObjectives(0) * TheWritableGlobalData->field123c;
  if (!TheGameLogic || !TheThingFactory)
    return;
  _STL::vector<S4SortElem12> heroes;
  ArmyVector armies = TheGameLogic->rva00388BE0();
  for (unsigned i = 0; i < armies.size(); ++i) {
    LivingWorldPlayerArmy *army = armies[i];
    if (!army)
      return;
    _STL::vector<LivingWorldArmy> &records = army->field30;
    for (unsigned j = 0; j < records.size(); ++j) {
      typedef const Rva00575B70Template *(BfmeThingFactory::*M)(
          const AsciiString &);
      const Rva00575B70Template *object =
          (TheThingFactory->*retailMethod<M>(j_00028560))(records[j].getName());
      if (object && (object->fieldd0 & 0x02000000)) {
        S4SortElem12 hero;
        hero.m_bfmeKey = object->field4d0;
        hero.flag = records[j].field39;
        hero.m_bfmeSecond = object->portrait();
        heroes.push_back(hero);
      }
    }
  }
  S4Cmp00574DF0 cmp;
  if (heroes.begin() != heroes.end()) {
    _STL::__introsort_loop(heroes.begin(), heroes.end(), (S4SortElem12 *)0,
                           _STL::__lg(heroes.end() - heroes.begin()) * 2, cmp);
    if (heroes.end() - heroes.begin() > 16) {
      _STL::__insertion_sort(heroes.begin(), heroes.begin() + 16, cmp);
      _STL::__unguarded_insertion_sort(heroes.begin() + 16, heroes.end(), cmp);
    } else
      _STL::__insertion_sort(heroes.begin(), heroes.end(), cmp);
  }
  field2e8.clear();
  unsigned upgrades = 0;
  for (unsigned index = 0; index < heroes.size(); ++index) {
    S4SortElem12 *hero = &heroes[index];
    AsciiString key;
    key.format(
        AsciiString(
            "SubMenus/HeroVeterancy/HeroSelection/HeroSelection%d/icon/Image"),
        field2e8.size() + 1);
    g_theWindowManager->image(key, hero->m_bfmeSecond);
    if (hero->flag)
      ++upgrades;
    field2e8.push_back(hero->flag);
  }
  SCORE(0x11c) = upgrades;
  field280 = TheWritableGlobalData->field1234 * upgrades;
  UnicodeString numberText;
  UnicodeString combined;
  numberText.translate(
      ((Rva00573580Lookup *)this)->number(TheWritableGlobalData->field1234));
  combined.set(L"x ");
  ((StringBase<wchar_t> *)&combined)
      ->concat(numberText.str(), numberText.getLength());
  g_theWindowManager->bfme_setAptText(AsciiString("APT:HeroPointsIncrement"),
                                      combined);
  field2fc = SCORE(0x120);
  field284 = TheWritableGlobalData->field1238 * field2fc;
  numberText.translate(
      ((Rva00573580Lookup *)this)->number(TheWritableGlobalData->field1238));
  combined.set(L"x ");
  ((StringBase<wchar_t> *)&combined)
      ->concat(numberText.str(), numberText.getLength());
  g_theWindowManager->bfme_setAptText(AsciiString("APT:UnitPointsIncrement"),
                                      combined);
  field300 = *(AsciiString *)(player + 0x28);
  field288 = 0;
  CampaignManager *campaign = TheLivingWorldLogic;
  if (!campaign)
    return;
  AsciiString regionName = campaign->field30;
  typedef Rva00575B70Region *(LivingWorldRegionManager::*RegionM)(
      const AsciiString &);
  Rva00575B70Region *region =
      (TheLivingWorldLogic->field28->*retailMethod<RegionM>(j_0002bf0d))(
          regionName);
  if (!region)
    return;
  typedef void (ScoreKeeper::*SetM)(int, int, int);
  (keeper->*retailMethod<SetM>(j_000045d4))(region->field78, region->field7c,
                                            region->field80);
  int value = SCORE(0x12c);
  rva00573C20(0, 0, value);
  rva00573C20(0, 1, TheWritableGlobalData->field1248);
  int product = TheWritableGlobalData->field1248 * value;
  rva00573C20(0, 2, product);
  field288 += product;
  value = SCORE(0x134);
  rva00573C20(1, 0, value);
  rva00573C20(1, 1, TheWritableGlobalData->field1250);
  product = TheWritableGlobalData->field1250 * value;
  rva00573C20(1, 2, product);
  field288 += product;
  value = SCORE(0x130);
  rva00573C20(2, 0, value);
  rva00573C20(2, 1, TheWritableGlobalData->field124c);
  product = TheWritableGlobalData->field124c * value;
  rva00573C20(2, 2, product);
  field288 += product;
  field28c = keeper->calculateScore();
  field290 = keeper->getVictoryType();
  {
    AsciiString key("APT:ScoreMapName");
    g_theWindowManager->bfme_setAptText(key,
                                        TheGameText->fetch(region->field10, 0));
  }
  ((Rva000E92B0Owner *)score)
      ->setWideString(TheGameText->fetch(region->field10, 0));
  ((Rva003C0E60Owner *)TheLivingWorldLogic)
      ->insert(((Rva000E95A0Owner *)score)->value());
  int regionIndex = 1;
  {
    AsciiString key("LW:RegionBonusArmy");
    _bfme_setScoreRegionBonus(&regionIndex, key, SCORE(0x12c));
  }
  {
    AsciiString key("LW:RegionLegendaryBonus");
    _bfme_setScoreRegionBonus(&regionIndex, key, SCORE(0x134));
  }
  {
    AsciiString key("LW:RegionBonusResource");
    _bfme_setScoreRegionBonus(&regionIndex, key, SCORE(0x130));
  }
  for (int i = regionIndex; i <= 3; ++i) {
    AsciiString empty("");
    AsciiString key;
    key.format(AsciiString("APT:ScoreRegionBonus%d"), i);
    g_theWindowManager->bfme_setAptText(key, UnicodeString(L""));
  }
  {
    AsciiString key("Result/Infos/ScoreMap/Picture/Image");
    g_theWindowManager->image(key, region->image());
  }
  {
    AsciiString key(
        "SubMenus/TerritoryBonus/TerritoryMap/TerritoryMap/Picture/Image");
    g_theWindowManager->image(key, region->image());
  }
}
