// ?update@ProductionUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.210885805763 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringbaseunicode /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include "ascii_string.h"
#include "basetype.h"
#include <bitset>
#include <list>
#include <wchar.h>
template <> inline const char *StringBase<char>::str() const {
  static const char TheNullChr = 0;
  return m_data ? m_data->data : &TheNullChr;
}
template <>
inline const unsigned short *StringBase<unsigned short>::str() const {
  static const unsigned short TheNullChr = 0;
  return m_data ? m_data->data : &TheNullChr;
}
#include "Common/UnicodeString.h"
#include <string.h>
inline UnicodeString::~UnicodeString() {
  ((StringBase<wchar_t> *)this)->releaseBuffer();
}
template <> __declspec(noinline) bool StringBase<char>::isEmpty() const {
  return m_data == 0 || m_data->length == 0;
}
// Full native reconstruction of the independently witnessed ProductionUpdate
// secondary UpdateModuleInterface entry; this receiver is primary object+10.
// Scratch reconstruction, not byte-matched game source. Full 4685-byte retail
// boundary, decoded callees and independently native ctor establish ownership.
// Neutral hidden-return helpers below are actual 0029C410/0029C440 targets;
// no pins are supplied for their local spellings. All fields retain addresses
// unless the ProductionUpdate twin and constructor establish their meaning.
typedef void (*Entry)();
struct Rva0029E330CallOwner {};
struct Rva0029E330ModelConditionView {
  _STL::bitset<320> bits;
};
template <class T, int Offset> __forceinline T &field(void *p) {
  return *(T *)((char *)p + Offset);
}
template <class T, int Offset> __forceinline const T &field(const void *p) {
  return *(const T *)((const char *)p + Offset);
}
template <int Address> __forceinline void *global() {
  return *(void **)Address;
}
__forceinline Entry slot(void *p, int n) { return (*(Entry **)p)[n / 4]; }
template <class R> __forceinline R invoke(void *p, Entry entry) {
  typedef R (Rva0029E330CallOwner::*Method)();
  union {
    Entry raw;
    Method member;
  } f;
  f.raw = entry;
  return (((Rva0029E330CallOwner *)p)->*f.member)();
}
template <class R, class A0>
__forceinline R invoke(void *p, Entry entry, A0 a0) {
  typedef R (Rva0029E330CallOwner::*Method)(A0);
  union {
    Entry raw;
    Method member;
  } f;
  f.raw = entry;
  return (((Rva0029E330CallOwner *)p)->*f.member)(a0);
}
template <class R, class A0, class A1>
__forceinline R invoke(void *p, Entry entry, A0 a0, A1 a1) {
  typedef R (Rva0029E330CallOwner::*Method)(A0, A1);
  union {
    Entry raw;
    Method member;
  } f;
  f.raw = entry;
  return (((Rva0029E330CallOwner *)p)->*f.member)(a0, a1);
}
template <class R, class A0, class A1, class A2>
__forceinline R invoke(void *p, Entry entry, A0 a0, A1 a1, A2 a2) {
  typedef R (Rva0029E330CallOwner::*Method)(A0, A1, A2);
  union {
    Entry raw;
    Method member;
  } f;
  f.raw = entry;
  return (((Rva0029E330CallOwner *)p)->*f.member)(a0, a1, a2);
}
template <class R, class A0, class A1, class A2, class A3>
__forceinline R invoke(void *p, Entry entry, A0 a0, A1 a1, A2 a2, A3 a3) {
  typedef R (Rva0029E330CallOwner::*Method)(A0, A1, A2, A3);
  union {
    Entry raw;
    Method member;
  } f;
  f.raw = entry;
  return (((Rva0029E330CallOwner *)p)->*f.member)(a0, a1, a2, a3);
}
template <class R, class A0, class A1, class A2, class A3, class A4>
__forceinline R invoke(void *p, Entry entry, A0 a0, A1 a1, A2 a2, A3 a3,
                       A4 a4) {
  typedef R (Rva0029E330CallOwner::*Method)(A0, A1, A2, A3, A4);
  union {
    Entry raw;
    Method member;
  } f;
  f.raw = entry;
  return (((Rva0029E330CallOwner *)p)->*f.member)(a0, a1, a2, a3, a4);
}
extern void j_000022bb();
extern void j_00004f1b();
extern void j_000076fd();
extern void j_000077b6();
extern void j_00008337();
extern void j_000084b8();
extern void j_00008b8e();
extern void j_00008e86();
extern void j_000095ed();
extern void j_0000a7a9();
extern void j_0000c752();
extern void j_0000c87e();
extern void j_0000d990();
extern void j_0000da8a();
extern void j_00010096();
extern void j_0001253f();
extern void j_0001362e();
extern void j_00013732();
extern void j_000157f3();
extern void j_0001621b();
extern void j_0001669e();
extern void j_0001697d();
extern void j_00016b67();
extern void j_000196c8();
extern void j_00019a6a();
extern void j_0001a276();
extern void j_0001a97e();
extern void j_0001bfd1();
extern void j_0001c0b2();
extern void j_0001e00b();
extern void j_0001e204();
extern void j_0001f253();
extern void j_0001f753();
extern void j_0001ff91();
extern void j_00020824();
extern void j_0002191d();
extern void j_00022336();
extern void j_00023d4e();
extern void j_00025eeb();
extern void j_000263d2();
extern void j_00026f35();
extern void j_00027fcf();
extern void j_0002852e();
extern void j_00028560();
extern void j_0002abf8();
extern void j_0002ae23();
extern void j_0002b5f3();
extern void j_0002b81e();
extern void j_0002d439();
extern void j_0002f3c4();
extern void j_0002F95A();
extern void j_0002fbb7();
extern void j_00030a1c();
extern void j_0003364a();
extern void j_0003436a();
extern void j_00036953();
extern void j_00037038();
extern void j_0003867c();
extern void j_000399A5();
extern void j_0003a1a7();
extern void j_0003a279();
extern void j_0003aa17();
extern void j_0003ac88();
extern void j_0003acb0();
extern void j_0003add7();
extern void j_0003c06a();
extern void j_0003c772();
extern void j_0003f8d7();
extern void j_00040327();
extern void j_00040863();
extern void j_00043cca();
extern void j_0004494a();
extern void j_0004511a();
extern void j_00046a1f();
extern void j_00047b27();
extern void j_00047ec9();
extern void j_00049fb2();
extern void j_0004a151();
extern void j_0004b01f();

enum ObjectID { INVALID_ID = 0 };
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };
struct AudioEventInfoRef {
  void *value;
};
class AudioEventRTS {
public:
  AudioEventRTS(const AudioEventInfoRef &, ObjectID);
  AudioEventRTS(const AudioEventRTS &);
  virtual ~AudioEventRTS();
  AudioEventRTS &assign(const AudioEventRTS &);
  void setPlayerIndex(int);
  void setObjectID(ObjectID);

private:
  char unknown04[108];
};
struct Rva0029E330Entry {
  virtual void destroy(unsigned);
  int type;
  void *objectTemplate;
  void *upgrade;
  int identifier;
  float percent, rate;
  int frames, quantity, produced, field28, door, field30;
  bool special;
  char pad35[3];
  int field38;
  Rva0029E330Entry *next;
  Rva0029E330Entry *prev;
};
struct Rva0029E330Door {
  unsigned opened, waiting, closed;
  bool hold;
  char pad[3];
};
struct Rva0029E330ListNode {
  Rva0029E330ListNode *next, *prev;
  ObjectID id;
};
class Rva0029C410Value {
public:
  AsciiString value();
};
class Rva0029C440Value {
public:
  AsciiString value(int);
};

class ProductionUpdate {
public:
  virtual UpdateSleepTime update();
};
static const unsigned theOpeningFlags[4] = {21, 25, 29, 33};
static const unsigned theClosingFlags[4] = {22, 26, 30, 34};
static const unsigned theWaitingOpenFlags[4] = {23, 27, 31, 35};
__forceinline void bitSet(unsigned *bits, unsigned bit, bool set = true) {
  if (set)
    bits[bit >> 5] |= 1u << (bit & 31);
  else
    bits[bit >> 5] &= ~(1u << (bit & 31));
}
__forceinline void *player(void *obj) {
  return invoke<void *>(obj, j_00020824);
}
__forceinline void notify(void *obj) { invoke<void>(obj, j_0002191d); }
__forceinline void setModelBit(void *obj, unsigned offset, unsigned mask,
                               bool set) {
  unsigned &bits = *(unsigned *)((char *)obj + offset);
  if (((bits & mask) != 0) != set) {
    if (set)
      bits |= mask;
    else
      bits &= ~mask;
    notify(obj);
  }
}
__forceinline void removeEntry(void *self, Rva0029E330Entry *e) {
  invoke<void>(self, j_0002f3c4, e);
  e->destroy(1);
}
__forceinline void *finalTemplate(void *obj) {
  void *t = field<void *, 4>(obj);
  if (t && field<void *, 4>(t))
    t = invoke<void *>(field<void *, 4>(t), j_000022bb);
  return t;
}
__forceinline void clearFields(unsigned *p) {
  for (int i = 0; i < 10; ++i)
    p[i] = 0;
}

class Player;
class Upgrade;
class UpgradeTemplate;
enum UpgradeStatusType { UPGRADE_STATUS_RVA2 = 2 };
class Rva0029E330PlayerView {
public:
};
class Player {
public:
  Upgrade *addUpgrade(const UpgradeTemplate *, UpgradeStatusType);
};
class ThingTemplate {
public:
  int calcTimeToBuild(const Player *, int) const;
};
enum DisabledType { DISABLED_RVA3 = 3 };
class Object {
public:
  void updateUpgradeModules();
  void setDisabledUntil(DisabledType, unsigned);
};
enum RadarEventType { RADAR_EVENT_RVA2 = 2 };
class Radar {
public:
  void createEvent(const Coord3D *, RadarEventType, float);
};
class Drawable;
class PickAndPlayInfo;
class GameMessage {
public:
  enum Type { RVA_7DA = 0x7da, RVA_7E2 = 0x7e2 };
};
bool pickAndPlayUnitVoiceResponse(const _STL::list<Drawable *> *,
                                  GameMessage::Type, PickAndPlayInfo *);
class Rva0029E330UI {
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
  virtual void s28();
  virtual void s2c();
  virtual void s30();
  virtual void message(UnicodeString, ...);
};
template <int N> class BitFlags {
public:
  enum BogusInitType { kInit = 0 };
  BitFlags(BogusInitType, int);
  unsigned words[(N + 31) / 32];
};
class Rva0029E330Audio {
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
  virtual void slot28();
  virtual void slot2c();
  virtual void slot30();
  virtual void slot34();
  virtual void slot38();
  virtual void slot3c();
  virtual void slot40();
  virtual int add(AudioEventRTS *);
  virtual void slot48();
  virtual void remove(int);
  virtual void slot50();
  virtual void slot54();
  virtual void slot58();
  virtual bool valid(AudioEventRTS *);
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
  virtual void slot90();
  virtual void slot94();
  virtual void slot98();
  virtual void slot9c();
  virtual void slota0();
  virtual void slota4();
  virtual void slota8();
  virtual void slotac();
  virtual bool active(int);
};
class Rva0029E330GameText {
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
  virtual UnicodeString fetch(const char *, bool *);
};
class Rva0029E330ObjectV {
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
  virtual void *drawable();
};
class Rva0029E330Exit {
public:
  virtual void slot00();
  virtual int reserve(void *, void *);
  virtual void exit(void *, int);
  virtual void slot0c();
  virtual void slot10();
  virtual void slot14();
  virtual void slot18();
  virtual void slot1c();
  virtual void slot20();
  virtual void slot24();
  virtual bool position(Coord3D *, float *);
  virtual void complete();
};
class Rva0029E330Script {
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
  virtual void slot90();
  virtual void slot94();
  virtual void notify(int, const AsciiString &, ObjectID);
};
class Rva0029E330Production {
public:
  virtual void slot00();
  virtual void slot04();
  virtual void slot08();
  virtual void slot0c();
  virtual void cancel(void *);
};
class Rva0029E330Contain {
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
  virtual int rva64();
  virtual void *rva68();
};
class Rva0029E330Rebuild {
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
  virtual AsciiString name();
  virtual int count();
};
class Rva0029E330Behavior {
public:
  virtual void slot00();
  virtual void slot04();
  virtual void slot08();
  virtual void *create();
};
class Rva0029E330Create {
public:
  virtual void slot00();
  virtual void onComplete();
};
class Rva0029E330AI {
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
  virtual void slot90();
  virtual void slot94();
  virtual void slot98();
  virtual void slot9c();
  virtual void slota0();
  virtual void slota4();
  virtual void slota8();
  virtual void slotac();
  virtual void slotb0();
  virtual void slotb4();
  virtual void slotb8();
  virtual void slotbc();
  virtual void slotc0();
  virtual void slotc4();
  virtual void slotc8();
  virtual void slotcc();
  virtual void slotd0();
  virtual void slotd4();
  virtual void slotd8();
  virtual void slotdc();
  virtual void slote0();
  virtual void slote4();
  virtual void slote8();
  virtual void slotec();
  virtual void slotf0();
  virtual void slotf4();
  virtual void slotf8();
  virtual void slotfc();
  virtual void slot100();
  virtual void slot104();
  virtual void slot108();
  virtual void slot10c();
  virtual void slot110();
  virtual void slot114();
  virtual void slot118();
  virtual void slot11c();
  virtual void slot120();
  virtual void slot124();
  virtual void slot128();
  virtual void slot12c();
  virtual bool rva130();
};
class Rva0029E330Selected {
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
  virtual void slot90();
  virtual void slot94();
  virtual void slot98();
  virtual void slot9c();
  virtual void slota0();
  virtual void slota4();
  virtual void slota8();
  virtual void slotac();
  virtual void slotb0();
  virtual void slotb4();
  virtual void slotb8();
  virtual void slotbc();
  virtual void slotc0();
  virtual void slotc4();
  virtual void slotc8();
  virtual void slotcc();
  virtual void slotd0();
  virtual void slotd4();
  virtual void slotd8();
  virtual void slotdc();
  virtual void slote0();
  virtual void slote4();
  virtual void slote8();
  virtual void slotec();
  virtual void slotf0();
  virtual void slotf4();
  virtual void slotf8();
  virtual void slotfc();
  virtual void slot100();
  virtual void *selected();
};
UpdateSleepTime ProductionUpdate::update() {
  static int respawnKey =
      invoke<int>(global<0x012ed600>(), j_0003add7, "RespawnUpdate");
  void *self = (char *)this - 0x10;
  void *data = field<void *, -12>(this);
  void *us = field<void *, -8>(this);
  unsigned now = field<unsigned, 0x3c>(global<0x012f0898>());
  void *experience = field<void *, 0x210>(us);
  Rva0029E330Entry *production = invoke<Rva0029E330Entry *>(self, j_000157f3);
  if (player(us)) {
    if (field<bool, 0x3d>(data)) {
      float change = invoke<float>(player(us), j_00043cca,
                                   (AsciiString *)((char *)data + 0x40));
      if (change < 0.0f)
        setModelBit(us, 0x134, 0x800, true);
      else
        setModelBit(us, 0x134, 0x800, false);
    }
    if (field<void *, 0x44>(data)) {
      float change = invoke<float>(player(us), j_00043cca,
                                   (AsciiString *)((char *)data + 0x40));
      if (change < 0.0f && !(field<unsigned char, 0x344>(us) & 1) &&
          !(field<unsigned, 0x90>(us) & 4)) {
        if (!((Rva0029E330Audio *)global<0x012ed668>())
                 ->active(field<int, 0xd4>(this))) {
          AudioEventRTS sound(field<AudioEventInfoRef, 0x44>(data),
                              field<ObjectID, 0x74>(us));
          sound.setPlayerIndex(field<int, 0x24>(player(us)));
          field<int, 0xd4>(this) =
              ((Rva0029E330Audio *)global<0x012ed668>())->add(&sound);
        }
      } else {
        ((Rva0029E330Audio *)global<0x012ed668>())
            ->remove(field<int, 0xd4>(this));
        field<int, 0xd4>(this) = 1;
      }
    }
  }
  if (field<int, 8>(data) > 0)
    invoke<void>(self, j_00037038);
  if (field<unsigned, 0xd0>(this) > 0)
    --field<unsigned, 0xd0>(this);
  if (field<unsigned, 0x28>(this) &&
      now - field<unsigned, 0x28>(this) > field<unsigned, 0x18>(data)) {
    field<unsigned, 0x28>(this) = 0;
    field<unsigned, 0x74>(this) |= 0x200;
    field<unsigned, 0x9c>(this) &= ~0x200;
    field<bool, 0xbc>(this) = true;
  }
  if (field<bool, 0xbc>(this) == true) {
    invoke<void>(us, j_000095ed, (unsigned *)((char *)this + 0x6c),
                 (unsigned *)((char *)this + 0x94));
    clearFields((unsigned *)((char *)this + 0x6c));
    clearFields((unsigned *)((char *)this + 0x94));
    field<bool, 0xbc>(this) = false;
  }
  if (!production)
    return UPDATE_SLEEP_NONE;
  if (field<unsigned, 0x90>(us) & 0x80000)
    return UPDATE_SLEEP_NONE;
  void *owner = player(us);
  if (!owner) {
    removeEntry(self, production);
    return UPDATE_SLEEP_NONE;
  }
  if (production->type == 1 && !field<int, 0xc8>(this) &&
      !(field<unsigned, 0xc0>(this) > 0)) {
    bool allowed = invoke<bool>(owner, j_0001a276, production->objectTemplate);
    unsigned char available = invoke<unsigned char>(
        (char *)owner + 0x30, j_00022336, production->objectTemplate, 1);
    if ((!allowed || !available) && !production->special) {
      if (!available && owner == field<void *, 0xc>(global<0x012ed748>()))
        invoke<bool>(global<0x012f142c>(), j_0002b5f3, 13, (Coord3D *)0);
      return UPDATE_SLEEP_NONE;
    }
  }
  if (production->type == 2 && production->upgrade &&
      field<int, 4>(production->upgrade) == 1 &&
      !invoke<bool>(us, j_000077b6, production->upgrade)) {
    ((Rva0029E330Production *)((char *)this + 0x10))
        ->cancel(production->upgrade);
    return UPDATE_SLEEP_NONE;
  }
  ++production->frames;
  int total;
  switch (production->type) {
  case 1:
    total = ((ThingTemplate *)production->objectTemplate)
                ->calcTimeToBuild((Player *)owner, -1);
    break;
  case 2:
    total = invoke<int>(production->upgrade, j_0002fbb7, owner);
    break;
  case 3:
    total =
        invoke<int>((char *)owner + 0x684, j_00030a1c, production->identifier);
    break;
  default:
    total = 1;
    break;
  }
  if (total < 1)
    total = 1;
  float multiplier = 1.0f;
  if (invoke<bool>(us, j_0002abf8, 12, &multiplier))
    total = (int)((float)total / multiplier);
  float percent = (float)production->frames / (float)total * 100.0f;
  production->percent = percent;
  production->rate = 100.0f / (float)total;
  if (production->type == 3 && ((char *)owner + 0x684)) {
    void *object =
        invoke<void *>((char *)owner + 0x684, j_0000a7a9,
                       production->objectTemplate, production->identifier);
    if (!(invoke<float>((char *)owner + 0x684, j_0001e204, object) >= 1.0f) ||
        field<int, 0xd0>(this))
      return UPDATE_SLEEP_NONE;
  } else if (!(percent >= 100.0f))
    return UPDATE_SLEEP_NONE;
  switch (production->type) {
  case 1:
  case 3: {
    bool isRespawn = production->type == 3;
    void *exitInterface = invoke<void *>(us, j_00023d4e);
    if (exitInterface) {
      int remaining = production->quantity - production->produced;
      for (int item = 0; item < remaining; ++item) {
        int doorIndex = production->door;
        if (doorIndex == -1) {
          doorIndex = ((Rva0029E330Exit *)exitInterface)
                          ->reserve(production->objectTemplate, 0);
          production->door = doorIndex;
        }
        if (doorIndex == -1)
          continue;
        Rva0029E330Door *door =
            (doorIndex >= 0 && doorIndex < 4)
                ? (Rva0029E330Door *)((char *)this + 0x2c + doorIndex * 16)
                : 0;
        if (field<int, 8>(data) > 0 && door) {
          if (!door->opened && !door->waiting && !door->closed) {
            door->opened = now;
            bitSet((unsigned *)((char *)this + 0x94),
                   theOpeningFlags[doorIndex]);
            field<bool, 0xbc>(this) = true;
          } else if (door->waiting)
            door->waiting = now;
          else if (door->closed) {
            door->waiting = now;
            bitSet((unsigned *)((char *)this + 0x6c),
                   theOpeningFlags[doorIndex]);
            bitSet((unsigned *)((char *)this + 0x6c),
                   theClosingFlags[doorIndex]);
            bitSet((unsigned *)((char *)this + 0x94),
                   theOpeningFlags[doorIndex], false);
            bitSet((unsigned *)((char *)this + 0x94),
                   theClosingFlags[doorIndex], false);
            bitSet((unsigned *)((char *)this + 0x94),
                   theWaitingOpenFlags[doorIndex]);
            field<bool, 0xbc>(this) = true;
          }
        }
        if (!field<unsigned, 0x28>(this)) {
          field<unsigned, 0x28>(this) = now;
          field<unsigned, 0x9c>(this) |= 0x200;
          field<bool, 0xbc>(this) = true;
        }
        if (field<int, 8>(data) != 0 && door && !door->waiting)
          continue;
        void *newObject;
        if (!field<int, 0xc8>(this)) {
          Coord3D position = {0, 0, 0};
          float orientation = 0;
          bool hasPosition = ((Rva0029E330Exit *)exitInterface)
                                 ->position(&position, &orientation);
          _STL::bitset<86> creationFlags;
          if (isRespawn) {
            newObject = invoke<void *>((char *)player(us) + 0x684, j_000076fd,
                                       production->identifier, &position);
            if (!newObject) {
              removeEntry(self, production);
              return UPDATE_SLEEP_NONE;
            }
            int sourceId = field<int, 0x370>(newObject);
            if (sourceId == -1)
              sourceId = field<int, 0x370>(us);
            invoke<void>(global<0x012f0898>(), j_0003a279, newObject, sourceId);
          } else {
            if (production->special)
              creationFlags.set(54);
            newObject = invoke<void *>(
                global<0x012ef1d8>(), j_0004494a, production->objectTemplate,
                field<void *, 0x230>(player(us)), &creationFlags, 0u);
            if (!newObject) {
              removeEntry(self, production);
              return UPDATE_SLEEP_NONE;
            }
            invoke<void>(self, j_0001c0b2, newObject);
            if (field<unsigned, 0x34>(data) > 0)
              invoke<void>(newObject, j_0002852e, 0x129,
                           field<int, 0x34>(data));
            field<float, 0x258>(newObject) = (float)production->field28;
            invoke<void>(global<0x012f0898>(), j_0003a279, newObject,
                         field<int, 0x370>(us));
          }
          field<ObjectID, 0xc8>(this) = field<ObjectID, 0x74>(newObject);
          invoke<void>(newObject, j_0000d990, us);
          void *drawable = ((Rva0029E330ObjectV *)newObject)->drawable();
          if (drawable && invoke<int>(newObject, j_0002b81e,
                                      field<int, 0x24>(field<void *, 0xc>(
                                          global<0x012ed748>()))) >= 3)
            invoke<void>(((Rva0029E330ObjectV *)newObject)->drawable(),
                         j_0000c87e, true);
          if (field<bool, 0x3c>(data) && field<void *, 0x210>(newObject) &&
              field<int, 0x28>(experience) >= 3)
            invoke<void>(global<0x012f0888>(), j_0001697d, newObject, 1, false);
          if (experience && !field<bool, 0x30>(data) &&
              invoke<bool>(experience, j_00025eeb)) {
            int value = invoke<int>(production->objectTemplate, j_0000da8a,
                                    (void *)0, -1);
            if (value > 0)
              invoke<void>(experience, j_00010096, (float)value, true, true,
                           true, 0);
          }
          if (hasPosition) {
            void *ai = field<void *, 0x204>(newObject);
            if (ai && ((Rva0029E330AI *)ai)->rva130()) {
              position.z += 500.0f;
              invoke<void>(newObject, j_0001621b, &position, true);
              invoke<void>(newObject, j_000399A5, orientation);
              invoke<void>((char *)ai + 0x20, j_0003436a, &position, 2);
            } else {
              invoke<void>(newObject, j_000399A5, orientation);
              invoke<void>(newObject, j_0001621b, &position, true);
            }
          }
          if (production->field30 != -1) {
            BitFlags<192> mask(BitFlags<192>::kInit, production->field30);
            invoke<void>(newObject, j_00016b67, &mask);
          }
          ((Object *)newObject)->updateUpgradeModules();
          drawable = ((Rva0029E330ObjectV *)newObject)->drawable();
          invoke<void>(drawable, j_0003c772);
          void *newTemplate;
          invoke<void>(drawable, j_0003aa17, true);
          const AudioEventRTS *creationSound =
              invoke<const AudioEventRTS *>(drawable, j_0001bfd1, 98);
          AudioEventRTS sound = *creationSound;
          sound.setObjectID(field<ObjectID, 0xc8>(this));
          sound.setPlayerIndex(field<int, 0x24>(player(us)));
          ((Rva0029E330Audio *)global<0x012ed668>())->add(&sound);
          invoke<void>(player(us), j_00004f1b, us, newObject);
          void **modules = field<void **, 0x1f0>(newObject);
          for (; *modules; ++modules) {
            void *b = (char *)*modules + 12;
            void *create = ((Rva0029E330Behavior *)b)->create();
            if (create)
              ((Rva0029E330Create *)create)->onComplete();
          }
          if (production->quantity ==
              production->quantity - production->produced) {
            _STL::list<Drawable *> selection;
            Drawable *d = (Drawable *)drawable;
            selection.push_back(d);
            pickAndPlayUnitVoiceResponse(&selection, GameMessage::RVA_7DA, 0);
          }
          newTemplate = invoke<void *>(newObject, j_000084b8);
          field<int, 0xc0>(this) =
              (int)(field<float, 0x2f4>(newTemplate) * 5.0f);
          invoke<void>(newObject, j_0002852e, 0xcf, field<int, 0xc0>(this));
          invoke<void>(newObject, j_0002852e, 0x12c, 5);
          ((Object *)newObject)
              ->setDisabledUntil(DISABLED_RVA3, field<unsigned, 0xc0>(this) +
                                                    field<unsigned, 0x3c>(
                                                        global<0x012f0898>()));
          if (!isRespawn) {
            void *d = ((Rva0029E330ObjectV *)newObject)->drawable();
            if (d) {
              invoke<void>(d, j_0001362e, field<int, 0xc0>(this));
              invoke<void>(d, j_0002d439, true);
            }
          }
          AsciiString *begin = field<AsciiString *, 0x2e8>(newTemplate),
                      *end = field<AsciiString *, 0x2ec>(newTemplate);
          if (begin != end) {
            for (AsciiString *p = begin;
                 p != field<AsciiString *, 0x2ec>(newTemplate); ++p) {
              void *t = invoke<void *>(global<0x012ef1d8>(), j_00028560, p);
              if (!t)
                continue;
              void *extra = invoke<void *>(global<0x012ef1d8>(), j_0004494a, t,
                                           field<void *, 0x230>(player(us)),
                                           &creationFlags, 0u);
              invoke<void>(self, j_0001c0b2, extra);
              if (((Rva0029E330Exit *)exitInterface)
                      ->position(&position, &orientation)) {
                invoke<void>(extra, j_0003a1a7, &position);
                invoke<void>(extra, j_000399A5, orientation);
              }
              invoke<void>(((Rva0029E330ObjectV *)extra)->drawable(),
                           j_00008337, true);
              setModelBit(extra, 0x128, 0x8000, true);
              invoke<void>(newObject, j_0002852e, 0x12c, 5);
              ObjectID id = field<ObjectID, 0x74>(extra);
              invoke<void>((char *)this + 0xcc, j_0001e00b, &id);
            }
            field<bool, 0xc4>(this) = false;
          }
          void *respawn = invoke<void *>(newObject, j_0002ae23, respawnKey);
          if (isRespawn && respawn) {
            invoke<void>(respawn, j_00049fb2, us);
            field<int, 0xd0>(this) = 20;
            invoke<void>(newObject, j_0003acb0,
                         field<unsigned, 0x3c>(global<0x012f0898>()) + 20);
          }
        } else {
          newObject = invoke<void *>(global<0x012f0898>(), j_0001f253,
                                     field<int, 0xc8>(this));
          if (!newObject) {
            removeEntry(self, production);
            return UPDATE_SLEEP_NONE;
          }
        }
        void *contain = field<void *, 0x1fc>(newObject);
        if (contain) {
          void *rebuild = ((Rva0029E330Contain *)contain)->rva68();
          if (rebuild) {
            void *t;
            {
              AsciiString name = ((Rva0029E330Rebuild *)rebuild)->name();
              t = invoke<void *>(global<0x012ef1d8>(), j_00028560, &name);
            }
            int quantity = ((Rva0029E330Rebuild *)rebuild)->count();
            if (t) {
              production->objectTemplate = t;
              production->quantity = quantity + 1;
              production->special = true;
              production->field28 = 0;
            }
          }
        }
        if (!field<bool, 0xc4>(this)) {
          float duration = field<float, 0x2f4>(finalTemplate(us));
          Rva0029E330ListNode *head = field<Rva0029E330ListNode *, 0xcc>(this);
          if (head->next != head)
            for (Rva0029E330ListNode *n = head->next;
                 n != field<Rva0029E330ListNode *, 0xcc>(this); n = n->next) {
              void *extra =
                  invoke<void *>(global<0x012f0898>(), j_0001f253, n->id);
              if (extra) {
                invoke<void>(((Rva0029E330ObjectV *)extra)->drawable(),
                             j_00008337, false);
                void *d = ((Rva0029E330ObjectV *)extra)->drawable();
                invoke<void>(d, j_0003c772);
                int frames = (int)(duration * 30.0f);
                invoke<void>(((Rva0029E330ObjectV *)extra)->drawable(),
                             j_00046a1f, frames);
              }
            }
          field<bool, 0xc4>(this) = true;
        }
        if (field<unsigned, 0xc0>(this)) {
          --field<unsigned, 0xc0>(this);
          return UPDATE_SLEEP_NONE;
        }
        setModelBit(newObject, 0x128, 0x8000, false);
        if (field<unsigned, 0x38>(data) > 0)
          invoke<void>(newObject, j_0002852e, 0x5e, field<int, 0x38>(data));
        if (field<unsigned, 0x128>(newObject) & 0x8000)
          invoke<bool>(newObject, j_0003c06a, 3);
        field<int, 0xc8>(this) = 0;
        if (!invoke<void *>(newObject, j_0002ae23, respawnKey))
          ((Rva0029E330Exit *)exitInterface)->exit(newObject, doorIndex);
        ++production->produced;
        production->door = -1;
        if (production->quantity == production->produced) {
          void *producer = invoke<void *>(global<0x012f0898>(), j_0001f253,
                                          field<ObjectID, 0x78>(newObject));
          if (producer && field<void *, 0x1fc>(producer)) {
            void *c = field<void *, 0x1fc>(producer);
            if (((Rva0029E330Contain *)c)->rva64()) {
              _STL::list<Drawable *> selection;
              Drawable *d =
                  (Drawable *)((Rva0029E330ObjectV *)producer)->drawable();
              selection.push_back(d);
              pickAndPlayUnitVoiceResponse(&selection, GameMessage::RVA_7E2, 0);
            }
          }
        }
      }
      if (production->quantity == production->produced) {
        removeEntry(self, production);
        ((Rva0029E330Exit *)exitInterface)->complete();
      }

    } else
      removeEntry(self, production);
    break;
  }
  case 2: {

    void *upgrade = production->upgrade;
    if (experience && !field<bool, 0x30>(data) &&
        invoke<bool>(experience, j_00025eeb)) {
      int value = invoke<int>(upgrade, j_0003f8d7, (void *)0, (void *)0);
      if (value > 0)
        invoke<void>(experience, j_00010096, (float)value, true, true, true, 0);
    }
    invoke<void>((char *)owner + 0x348, j_00047ec9,
                 invoke<int>(upgrade, j_0003f8d7, owner, (void *)0));
    ((Rva0029E330Script *)global<0x012f076c>())
        ->notify(field<int, 0x24>(player(us)), field<AsciiString, 8>(upgrade),
                 field<ObjectID, 0x74>(us));
    if (invoke<bool>(us, j_0001ff91)) {
      UnicodeString msg;
      UnicodeString format = ((Rva0029E330GameText *)global<0x012f147c>())
                                 ->fetch("UPGRADE:UpgradeComplete", 0);
      UnicodeString name =
          ((Rva0029E330GameText *)global<0x012f147c>())
              ->fetch(
                  ((const StringBase<char> &)field<AsciiString, 0x10>(upgrade))
                      .str(),
                  0);
      msg.format(UnicodeString(format.str()), name.str());
      ((Rva0029E330UI *)global<0x012f148c>())->message(msg);
      ((Radar *)global<0x012ef0e4>())
          ->createEvent((Coord3D *)((char *)us + 0x38), RADAR_EVENT_RVA2, 4.0f);
      AudioEventRTS sound = field<AudioEventRTS, 0x28>(upgrade);
      if (((Rva0029E330Audio *)global<0x012ed668>())->valid(&sound)) {
        sound.setObjectID(field<ObjectID, 0x74>(us));
        ((Rva0029E330Audio *)global<0x012ed668>())->add(&sound);
      } else
        invoke<bool>(global<0x012f142c>(), j_0002b5f3, 6, (Coord3D *)0);
      sound.assign(field<AudioEventRTS, 0x98>(upgrade));
      sound.setObjectID(field<ObjectID, 0x74>(us));
      ((Rva0029E330Audio *)global<0x012ed668>())->add(&sound);
    }
    if (!((const StringBase<char> &)((Rva0029C410Value *)data)->value())
             .isEmpty()) {
      void *fx = invoke<void *>(
          global<0x012f144c>(), j_0001669e,
          ((const StringBase<char> &)((Rva0029C410Value *)data)->value())
              .str());
      if (fx) {
        typedef void(__cdecl * F)(void *, void *, void *);
        ((F)j_0001253f)(fx, us, 0);
      }
    }
    if (field<int, 4>(upgrade) == 0)
      ((Player *)owner)
          ->addUpgrade((UpgradeTemplate *)upgrade, UPGRADE_STATUS_RVA2);
    else
      invoke<void>(us, j_0001a97e, upgrade);
    void *selected = ((Rva0029E330Selected *)global<0x012f148c>())->selected();
    void *selectedObject = selected ? field<void *, 0xfc>(selected) : 0;
    if (selectedObject) {
      void *t = invoke<void *>(selectedObject, j_000084b8);
      for (int i = 0; i < 5; ++i) {
        AsciiString name = ((Rva0029C440Value *)t)->value(i);
        if (invoke<void *>(global<0x012ef188>(), j_0002F95A, &name) ==
            upgrade) {
          field<bool, 0x24>(global<0x012f33f8>()) = true;
          break;
        }
      }
    }
    removeEntry(self, production);
    field<int, 0xc8>(this) = 0;
    return UPDATE_SLEEP_NONE;
  }
  }
  return UPDATE_SLEEP_NONE;
}
