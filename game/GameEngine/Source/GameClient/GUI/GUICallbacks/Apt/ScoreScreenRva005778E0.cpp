// Retail 005778E0..00577F47; owner and callee evidence:
// targets/game/reverse/identity_evidence/005778e0-score-rows.md
// targets/game/reverse/identity_evidence/005778e0-edx-binding.md
// ?rva005778E0@BfmeAptScreenScoreScreen@@QAE_NXZ
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Igame/Libraries/Source/WWVegas/WWLib /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include "ascii_string.h"
#include <wchar.h>
template <> inline bool StringBase<unsigned short>::isNotEmpty() const {
  return m_data != 0 && m_data->length != 0;
}
#include "Common/UnicodeString.h"
#include <vector>

extern void j_00028560();
extern void j_00047e38();
extern void j_0002bf0d();

template <class Method> __forceinline Method retailMethod(void (*raw)()) {
  union {
    void (*entry)();
    Method method;
  } f;
  f.entry = raw;
  return f.method;
}
inline UnicodeString::~UnicodeString() {
  ((StringBase<wchar_t> *)this)->releaseBuffer();
}
class GameWindow;
class Image;
struct LivingWorldPlayerArmy;
typedef _STL::vector<LivingWorldPlayerArmy *> ArmyVector;
class GameLogic {
public:
  ArmyVector rva00388BE0();
};
class BfmeThingFactory {};
extern GameLogic *TheGameLogic;
extern BfmeThingFactory *TheThingFactory;
extern int g_color12B7FC8;

struct LivingWorldArmy {
  char field00[0x0c];
  int field0c;
  char field10[0x2c];
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
struct Rva005778E0Template {
  char field00[0x0c];
  UnicodeString field0c;
  const Image *portrait() const {
    typedef const Image *(Rva005778E0Template::*Method)() const;
    return (this->*retailMethod<Method>(j_00047e38))();
  }
};
struct ScoreRowSortValue {
  ScoreRowSortValue(LivingWorldArmy *r, const Rva005778E0Template *o)
      : record(r), object(o) {}
  LivingWorldArmy *record;
  const Rva005778E0Template *object;
};
void _bfme_sortScoreRows(ScoreRowSortValue *, ScoreRowSortValue *);

class LivingWorldRegionManager {};
struct Rva005778E0Region {
  char field00[0x10];
  AsciiString field10;
};
class Rva005778E0CampaignView {
public:
  char field00[0x28];
  LivingWorldRegionManager *field28;
};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
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
extern GameTextInterface *TheGameText;
void GadgetListBoxReset(GameWindow *);
int GadgetListBoxGetNumColumns(GameWindow *);
void GadgetListBoxSetColumnWidths(GameWindow *, int, int *);
int GadgetListBoxAddEntryText(GameWindow *, UnicodeString, int, int, int, bool);
int GadgetListBoxAddEntryImage(GameWindow *, const Image *, int, int, int, int,
                               bool, int);
void GadgetListBoxSetItemData(GameWindow *, void *, int, int);
void GadgetListBoxSetTopVisibleEntry(GameWindow *, int);

class Rva00573580Lookup {
public:
  AsciiString number(int);
};

class BfmeAptScreenScoreScreen {
public:
  bool rva005778E0();
  char field00[0x310];
  GameWindow *m_persistentUnitsListBox;
};

bool BfmeAptScreenScoreScreen::rva005778E0() {
  if (!TheGameLogic || !TheThingFactory || !m_persistentUnitsListBox)
    return false;
  _STL::vector<ScoreRowSortValue> rows;
  ArmyVector armies = TheGameLogic->rva00388BE0();
  for (unsigned i = 0; i < armies.size(); ++i) {
    LivingWorldPlayerArmy *army = armies[i];
    if (!army)
      return false;
    _STL::vector<LivingWorldArmy> &records = army->field30;
    for (unsigned j = 0; j < records.size(); ++j) {
      typedef const Rva005778E0Template *(BfmeThingFactory::*FindMethod)(
          const AsciiString &);
      const Rva005778E0Template *object =
          (TheThingFactory->*retailMethod<FindMethod>(j_00028560))(
              records[j].getName());
      if (object) {
        ScoreRowSortValue row(&records[j], object);
        rows.push_back(row);
      }
    }
  }
  if (rows.size() == 0)
    return false;
  _bfme_sortScoreRows(rows.begin(), rows.end());
  GadgetListBoxReset(m_persistentUnitsListBox);
  if (GadgetListBoxGetNumColumns(m_persistentUnitsListBox) < 7) {
    int widths[7] = {10, 25, 17, 13, 13, 12, 8};
    GadgetListBoxSetColumnWidths(m_persistentUnitsListBox, 7, widths);
  }
  const int color = g_color12B7FC8;
  for (_STL::vector<ScoreRowSortValue>::iterator i = rows.begin();
       i != rows.end(); ++i) {
    const Rva005778E0Template *object = i->object;
    LivingWorldArmy *record = i->record;
    UnicodeString text;
    if (record->field78.isNotEmpty())
      text = record->field78;
    else
      text = object->field0c;
    int row = GadgetListBoxAddEntryText(m_persistentUnitsListBox, text, color, -1, 1, true);
    const Image *portrait = object->portrait();
    if (portrait) {
      GameWindow *listBox = m_persistentUnitsListBox;
      GadgetListBoxAddEntryImage(listBox, portrait, row, 0, 40, 40, true, -1);
    }
    const AsciiString &regionName = record->field4c;
    // ILT 0002BF0D reaches the native thiscall lookup at 003C8A50.
    // ECX is the receiver and the name is its sole stack argument (ret 4).
    // Incoming EDX is unused. Carrying the already loaded campaign in that
    // caller-saved register preserves retail's load; it adds no argument
    // to the target's contract and emits no extra instruction.
    typedef Rva005778E0Region *(__fastcall *RegionAdapter)(
        LivingWorldRegionManager *, LivingWorldLogic *, const AsciiString &);
    Rva005778E0Region *region = reinterpret_cast<RegionAdapter>(j_0002bf0d)(
        reinterpret_cast<Rva005778E0CampaignView *>(TheLivingWorldLogic)->field28,
        TheLivingWorldLogic, regionName);
    if (region)
      GadgetListBoxAddEntryText(m_persistentUnitsListBox,
                                TheGameText->fetch(region->field10, 0), color,
                                row, 2, true);
    int number0c = record->field0c;
    text.translate(
        reinterpret_cast<Rva00573580Lookup *>(this)->number(number0c));
    GadgetListBoxAddEntryText(m_persistentUnitsListBox, text, color, row, 3, true);
    int number3c = record->field3c;
    text.translate(
        reinterpret_cast<Rva00573580Lookup *>(this)->number(number3c));
    GadgetListBoxAddEntryText(m_persistentUnitsListBox, text, color, row, 4, true);
    int number40 = record->field40;
    text.translate(
        reinterpret_cast<Rva00573580Lookup *>(this)->number(number40));
    GadgetListBoxAddEntryText(m_persistentUnitsListBox, text, color, row, 5, true);
    int number44 = record->field44;
    text.translate(
        reinterpret_cast<Rva00573580Lookup *>(this)->number(number44));
    GadgetListBoxAddEntryText(m_persistentUnitsListBox, text, color, row, 6, true);
    GadgetListBoxSetItemData(m_persistentUnitsListBox, record, row, 0);
  }
  GadgetListBoxSetTopVisibleEntry(m_persistentUnitsListBox, 0);
  return true;
}
