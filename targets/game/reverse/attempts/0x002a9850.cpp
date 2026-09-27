// ?triggerAbilityEffect@SpecialAbilityUpdate@@IAEXXZ
// partial score=0.2445673646779929 date=2026-09-26
// cl: /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// Complete native reconstruction, NOT byte-matched. Full extent 002A9850..002AA233
// is2531B: executable switch arms end +963 then alignment,9 pointers and91-byte
// secondary switch table; old2403B lift excluded its128-byte table region.
// Identity: ZH SpecialAbilityUpdate::triggerAbilityEffect starts XP/skill−1 fallback,
// trigger audio and power switch with secondary weapon lock/aiAttackObject.
// Native DominateEnemy and LevelGrant slot15 callers reach ILT3FA30 with live
// primary this and no arguments. ZH header declares protected nonvirtual void().
// Real WeaponSetSpecialAbilityUpdate dtor26DCB0/32 and deleting26DDD0 independently
// refute the old WeaponSetSpecialAbilityUpdate destructor claim at this address.
// BFME additions reconstructed from fresh read-only Ghidra and full retail:
// cost subtraction, trigger count, looping audio, grab/capture/disguise/Lua arms.
// Independent ActiveBody evidence: ctor211A50 installs VA010A7718 atthis+10;
// slots70/74/78/7C reach20E820/20E850/20E860/20E870. FieldParse00CA7AA8 names
// GrabObject+2C,GrabFX+38,GrabDamage+3C,GrabOffset+40. Last getter copies TWO
// DWORDS,returns EAX=hidden buffer,RET4; native Rva0020E870PairAccessor.cpp
// independently proves8-byte Coord2D value return, not3D out-parameter.
// Model-condition flags start Object+110; touched118/11C are words2/3 of320bits.
// Measurement:2519/2531 bytes,1900 masked positional differences,619 equal
// positions =>score0.244567364678;104 relocs; frame164 vs168; zero unresolved
// in strict resolver. Normalized instruction shape0.931 is NOT a byte score.
// Visible genuine StringBase<char>::isEmpty reproduces22/22B and removes two
// extra EH states. That existing helper adds ZERO coverage. Native matrix,
// coordinate/string headers, real STLport bitsets, virtual declarations, original
// getters, value-return offset, effects expression and typed XP/skill calls used.
// Finite lifetime/order/const/CPU/size variants plateau; remaining prefix/register
// lifetime and grab-position frame/x87 schedule need new evidence. No asm,
// volatile, invented pins, throw specifications, or unused padding locals added.
// stlport
#define __PLACEMENT_VEC_NEW_INLINE
#include <bitset>
#include "basetype.h"
enum SpecialPowerType;
#include "ascii_string.h"
template <class T> __declspec(noinline) bool StringBase<T>::isEmpty() const
{
    return m_data == 0 || m_data->length == 0;
}
#include <math.h>
#pragma intrinsic(sin, cos)
// Retail 002A9850 full2531 bytes including switch tables. Protected nonvirtual
// SpecialAbilityUpdate::triggerAbilityEffect, independently identified by ZH
// XP/skill/audio/ability sequence and native derived special-power callers.
// Address-qualified access and call views below do not claim unproven identities.
typedef void (*Entry)();
struct Rva002A9850CallOwner
{
};
struct Rva002A9850ModelConditionView
{
    _STL::bitset<320> bits;
};
template <class T, int Offset> __forceinline T &field(void *p)
{
    return *(T *)((char *)p + Offset);
}
template <class T, int Offset> __forceinline const T &field(const void *p)
{
    return *(const T *)((const char *)p + Offset);
}
template <int Address> __forceinline void *global()
{
    return *(void **)Address;
}
__forceinline Entry slot(void *p, int n)
{
    return (*(Entry **)p)[n / 4];
}
template <class R> __forceinline R invoke(void *p, Entry entry)
{
    typedef R (Rva002A9850CallOwner::*Method)();
    union {
        Entry raw;
        Method member;
    } f;
    f.raw = entry;
    return (((Rva002A9850CallOwner *)p)->*f.member)();
}
template <class R, class A0> __forceinline R invoke(void *p, Entry entry, A0 a0)
{
    typedef R (Rva002A9850CallOwner::*Method)(A0);
    union {
        Entry raw;
        Method member;
    } f;
    f.raw = entry;
    return (((Rva002A9850CallOwner *)p)->*f.member)(a0);
}
template <class R, class A0, class A1> __forceinline R invoke(void *p, Entry entry, A0 a0, A1 a1)
{
    typedef R (Rva002A9850CallOwner::*Method)(A0, A1);
    union {
        Entry raw;
        Method member;
    } f;
    f.raw = entry;
    return (((Rva002A9850CallOwner *)p)->*f.member)(a0, a1);
}
template <class R, class A0, class A1, class A2>
__forceinline R invoke(void *p, Entry entry, A0 a0, A1 a1, A2 a2)
{
    typedef R (Rva002A9850CallOwner::*Method)(A0, A1, A2);
    union {
        Entry raw;
        Method member;
    } f;
    f.raw = entry;
    return (((Rva002A9850CallOwner *)p)->*f.member)(a0, a1, a2);
}
template <class R, class A0, class A1, class A2, class A3>
__forceinline R invoke(void *p, Entry entry, A0 a0, A1 a1, A2 a2, A3 a3)
{
    typedef R (Rva002A9850CallOwner::*Method)(A0, A1, A2, A3);
    union {
        Entry raw;
        Method member;
    } f;
    f.raw = entry;
    return (((Rva002A9850CallOwner *)p)->*f.member)(a0, a1, a2, a3);
}
template <class R, class A0, class A1, class A2, class A3, class A4>
__forceinline R invoke(void *p, Entry entry, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4)
{
    typedef R (Rva002A9850CallOwner::*Method)(A0, A1, A2, A3, A4);
    union {
        Entry raw;
        Method member;
    } f;
    f.raw = entry;
    return (((Rva002A9850CallOwner *)p)->*f.member)(a0, a1, a2, a3, a4);
}
extern void j_00001a73();
extern void j_00001a7d();
extern void j_00002d06();
extern void j_0000d990();
extern void j_0001593d();
extern void j_00017512();
extern void j_0001ff91();
extern void j_0002191d();
extern void j_000226ab();
extern void j_000283ee();
extern void j_00028560();
extern void j_0002ae23();
extern void j_0002b5f3();
extern void j_0002edcf();
extern void j_0003251f();
extern void j_00034ca2();
extern void j_00037a56();
extern void j_0003ab20();
extern void j_0003add7();
extern void j_0003b5b1();
extern void j_0003c8e9();
extern void j_0003eebe();
extern void j_0004027d();
extern void j_00040a3e();
extern void j_00040dc2();
extern void j_0004494a();
extern void j_00048c61();

enum ObjectID
{
    INVALID_ID = 0
};
struct AudioEventInfoRef
{
    void *ptr;
};
class AudioEventRTS
{
  public:
    AudioEventRTS(const AudioEventRTS &);
    AudioEventRTS(const AudioEventInfoRef &, ObjectID);
    virtual ~AudioEventRTS();
    void setObjectID(ObjectID);

  private:
    char m_unrecovered04[108];
};
class DamageInfo
{
  public:
    DamageInfo();
    char m_unrecovered00[92];
};
class Rva000EDC40
{
  public:
    ~Rva000EDC40();
};
class DelayedLuaEventList
{
  public:
    DelayedLuaEventList();
    ~DelayedLuaEventList()
    {
        ((Rva000EDC40 *)this)->~Rva000EDC40();
    }
    char m_unrecovered00[76];
};
#include "matrix3d.h"
class Rva002A9850V40
{
  public:
    virtual void rvaSlot00();
    virtual void rvaSlot04();
    virtual void rvaSlot08();
    virtual void rvaSlot0C();
    virtual void rvaSlot10();
    virtual void rvaSlot14();
    virtual void rvaSlot18();
    virtual void rvaSlot1C();
    virtual void rvaSlot20();
    virtual void rvaSlot24();
    virtual void rvaSlot28();
    virtual void rvaSlot2C();
    virtual void rvaSlot30();
    virtual void rvaSlot34();
    virtual void rvaSlot38();
    virtual void rvaSlot3C();
    virtual void call();
};
class Rva002A9850V44
{
  public:
    virtual void rvaSlot00();
    virtual void rvaSlot04();
    virtual void rvaSlot08();
    virtual void rvaSlot0C();
    virtual void rvaSlot10();
    virtual void rvaSlot14();
    virtual void rvaSlot18();
    virtual void rvaSlot1C();
    virtual void rvaSlot20();
    virtual void rvaSlot24();
    virtual void rvaSlot28();
    virtual void rvaSlot2C();
    virtual void rvaSlot30();
    virtual void rvaSlot34();
    virtual void rvaSlot38();
    virtual void rvaSlot3C();
    virtual void rvaSlot40();
    virtual int call(AudioEventRTS *);
};
class Rva002A9850VB0
{
  public:
    virtual void rvaSlot00();
    virtual void rvaSlot04();
    virtual void rvaSlot08();
    virtual void rvaSlot0C();
    virtual void rvaSlot10();
    virtual void rvaSlot14();
    virtual void rvaSlot18();
    virtual void rvaSlot1C();
    virtual void rvaSlot20();
    virtual void rvaSlot24();
    virtual void rvaSlot28();
    virtual void rvaSlot2C();
    virtual void rvaSlot30();
    virtual void rvaSlot34();
    virtual void rvaSlot38();
    virtual void rvaSlot3C();
    virtual void rvaSlot40();
    virtual void rvaSlot44();
    virtual void rvaSlot48();
    virtual void rvaSlot4C();
    virtual void rvaSlot50();
    virtual void rvaSlot54();
    virtual void rvaSlot58();
    virtual void rvaSlot5C();
    virtual void rvaSlot60();
    virtual void rvaSlot64();
    virtual void rvaSlot68();
    virtual void rvaSlot6C();
    virtual void rvaSlot70();
    virtual void rvaSlot74();
    virtual void rvaSlot78();
    virtual void rvaSlot7C();
    virtual void rvaSlot80();
    virtual void rvaSlot84();
    virtual void rvaSlot88();
    virtual void rvaSlot8C();
    virtual void rvaSlot90();
    virtual void rvaSlot94();
    virtual void rvaSlot98();
    virtual void rvaSlot9C();
    virtual void rvaSlotA0();
    virtual void rvaSlotA4();
    virtual void rvaSlotA8();
    virtual void rvaSlotAC();
    virtual bool call(int);
};
class Rva002A9850V70
{
  public:
    virtual void rvaSlot00();
    virtual void rvaSlot04();
    virtual void rvaSlot08();
    virtual void rvaSlot0C();
    virtual void rvaSlot10();
    virtual void rvaSlot14();
    virtual void rvaSlot18();
    virtual void rvaSlot1C();
    virtual void rvaSlot20();
    virtual void rvaSlot24();
    virtual void rvaSlot28();
    virtual void rvaSlot2C();
    virtual void rvaSlot30();
    virtual void rvaSlot34();
    virtual void rvaSlot38();
    virtual void rvaSlot3C();
    virtual void rvaSlot40();
    virtual void rvaSlot44();
    virtual void rvaSlot48();
    virtual void rvaSlot4C();
    virtual void rvaSlot50();
    virtual void rvaSlot54();
    virtual void rvaSlot58();
    virtual void rvaSlot5C();
    virtual void rvaSlot60();
    virtual void rvaSlot64();
    virtual void rvaSlot68();
    virtual void rvaSlot6C();
    virtual AsciiString call() const;
};
class Rva002A9850V88
{
  public:
    virtual void rvaSlot00();
    virtual void rvaSlot04();
    virtual void rvaSlot08();
    virtual void rvaSlot0C();
    virtual void rvaSlot10();
    virtual void rvaSlot14();
    virtual void rvaSlot18();
    virtual void rvaSlot1C();
    virtual void rvaSlot20();
    virtual void rvaSlot24();
    virtual void rvaSlot28();
    virtual void rvaSlot2C();
    virtual void rvaSlot30();
    virtual void rvaSlot34();
    virtual void rvaSlot38();
    virtual void rvaSlot3C();
    virtual void rvaSlot40();
    virtual void rvaSlot44();
    virtual void rvaSlot48();
    virtual void rvaSlot4C();
    virtual void rvaSlot50();
    virtual void rvaSlot54();
    virtual void rvaSlot58();
    virtual void rvaSlot5C();
    virtual void rvaSlot60();
    virtual void rvaSlot64();
    virtual void rvaSlot68();
    virtual void rvaSlot6C();
    virtual void rvaSlot70();
    virtual void rvaSlot74();
    virtual void rvaSlot78();
    virtual void rvaSlot7C();
    virtual void rvaSlot80();
    virtual void rvaSlot84();
    virtual void call(void *);
};
class Rva002A9850V78
{
  public:
    virtual void rvaSlot00();
    virtual void rvaSlot04();
    virtual void rvaSlot08();
    virtual void rvaSlot0C();
    virtual void rvaSlot10();
    virtual void rvaSlot14();
    virtual void rvaSlot18();
    virtual void rvaSlot1C();
    virtual void rvaSlot20();
    virtual void rvaSlot24();
    virtual void rvaSlot28();
    virtual void rvaSlot2C();
    virtual void rvaSlot30();
    virtual void rvaSlot34();
    virtual void rvaSlot38();
    virtual void rvaSlot3C();
    virtual void rvaSlot40();
    virtual void rvaSlot44();
    virtual void rvaSlot48();
    virtual void rvaSlot4C();
    virtual void rvaSlot50();
    virtual void rvaSlot54();
    virtual void rvaSlot58();
    virtual void rvaSlot5C();
    virtual void rvaSlot60();
    virtual void rvaSlot64();
    virtual void rvaSlot68();
    virtual void rvaSlot6C();
    virtual void rvaSlot70();
    virtual void rvaSlot74();
    virtual float call() const;
};
class Rva002A9850V38
{
  public:
    virtual void rvaSlot00();
    virtual void rvaSlot04();
    virtual void rvaSlot08();
    virtual void rvaSlot0C();
    virtual void rvaSlot10();
    virtual void rvaSlot14();
    virtual void rvaSlot18();
    virtual void rvaSlot1C();
    virtual void rvaSlot20();
    virtual void rvaSlot24();
    virtual void rvaSlot28();
    virtual void rvaSlot2C();
    virtual void rvaSlot30();
    virtual void rvaSlot34();
    virtual void call(DamageInfo *);
};
class Rva002A9850V7C
{
  public:
    virtual void rvaSlot00();
    virtual void rvaSlot04();
    virtual void rvaSlot08();
    virtual void rvaSlot0C();
    virtual void rvaSlot10();
    virtual void rvaSlot14();
    virtual void rvaSlot18();
    virtual void rvaSlot1C();
    virtual void rvaSlot20();
    virtual void rvaSlot24();
    virtual void rvaSlot28();
    virtual void rvaSlot2C();
    virtual void rvaSlot30();
    virtual void rvaSlot34();
    virtual void rvaSlot38();
    virtual void rvaSlot3C();
    virtual void rvaSlot40();
    virtual void rvaSlot44();
    virtual void rvaSlot48();
    virtual void rvaSlot4C();
    virtual void rvaSlot50();
    virtual void rvaSlot54();
    virtual void rvaSlot58();
    virtual void rvaSlot5C();
    virtual void rvaSlot60();
    virtual void rvaSlot64();
    virtual void rvaSlot68();
    virtual void rvaSlot6C();
    virtual void rvaSlot70();
    virtual void rvaSlot74();
    virtual void rvaSlot78();
    virtual Coord2D call() const;
};
class Rva002A9850V28
{
  public:
    virtual void rvaSlot00();
    virtual void rvaSlot04();
    virtual void rvaSlot08();
    virtual void rvaSlot0C();
    virtual void rvaSlot10();
    virtual void rvaSlot14();
    virtual void rvaSlot18();
    virtual void rvaSlot1C();
    virtual void rvaSlot20();
    virtual void rvaSlot24();
    virtual void *call();
};
class Rva002A9850V74
{
  public:
    virtual void rvaSlot00();
    virtual void rvaSlot04();
    virtual void rvaSlot08();
    virtual void rvaSlot0C();
    virtual void rvaSlot10();
    virtual void rvaSlot14();
    virtual void rvaSlot18();
    virtual void rvaSlot1C();
    virtual void rvaSlot20();
    virtual void rvaSlot24();
    virtual void rvaSlot28();
    virtual void rvaSlot2C();
    virtual void rvaSlot30();
    virtual void rvaSlot34();
    virtual void rvaSlot38();
    virtual void rvaSlot3C();
    virtual void rvaSlot40();
    virtual void rvaSlot44();
    virtual void rvaSlot48();
    virtual void rvaSlot4C();
    virtual void rvaSlot50();
    virtual void rvaSlot54();
    virtual void rvaSlot58();
    virtual void rvaSlot5C();
    virtual void rvaSlot60();
    virtual void rvaSlot64();
    virtual void rvaSlot68();
    virtual void rvaSlot6C();
    virtual void rvaSlot70();
    virtual void *call();
};
class Rva002A9850V84
{
  public:
    virtual void rvaSlot00();
    virtual void rvaSlot04();
    virtual void rvaSlot08();
    virtual void rvaSlot0C();
    virtual void rvaSlot10();
    virtual void rvaSlot14();
    virtual void rvaSlot18();
    virtual void rvaSlot1C();
    virtual void rvaSlot20();
    virtual void rvaSlot24();
    virtual void rvaSlot28();
    virtual void rvaSlot2C();
    virtual void rvaSlot30();
    virtual void rvaSlot34();
    virtual void rvaSlot38();
    virtual void rvaSlot3C();
    virtual void rvaSlot40();
    virtual void rvaSlot44();
    virtual void rvaSlot48();
    virtual void rvaSlot4C();
    virtual void rvaSlot50();
    virtual void rvaSlot54();
    virtual void rvaSlot58();
    virtual void rvaSlot5C();
    virtual void rvaSlot60();
    virtual void rvaSlot64();
    virtual void rvaSlot68();
    virtual void rvaSlot6C();
    virtual void rvaSlot70();
    virtual void rvaSlot74();
    virtual void rvaSlot78();
    virtual void rvaSlot7C();
    virtual void rvaSlot80();
    virtual bool call(void *, bool);
};
class Rva002A9850V90
{
  public:
    virtual void rvaSlot00();
    virtual void rvaSlot04();
    virtual void rvaSlot08();
    virtual void rvaSlot0C();
    virtual void rvaSlot10();
    virtual void rvaSlot14();
    virtual void rvaSlot18();
    virtual void rvaSlot1C();
    virtual void rvaSlot20();
    virtual void rvaSlot24();
    virtual void rvaSlot28();
    virtual void rvaSlot2C();
    virtual void rvaSlot30();
    virtual void rvaSlot34();
    virtual void rvaSlot38();
    virtual void rvaSlot3C();
    virtual void rvaSlot40();
    virtual void rvaSlot44();
    virtual void rvaSlot48();
    virtual void rvaSlot4C();
    virtual void rvaSlot50();
    virtual void rvaSlot54();
    virtual void rvaSlot58();
    virtual void rvaSlot5C();
    virtual void rvaSlot60();
    virtual void rvaSlot64();
    virtual void rvaSlot68();
    virtual void rvaSlot6C();
    virtual void rvaSlot70();
    virtual void rvaSlot74();
    virtual void rvaSlot78();
    virtual void rvaSlot7C();
    virtual void rvaSlot80();
    virtual void rvaSlot84();
    virtual void rvaSlot88();
    virtual void rvaSlot8C();
    virtual void call(void *, bool);
};
class Rva002A9850V08
{
  public:
    virtual void rvaSlot00();
    virtual void rvaSlot04();
    virtual bool call();
};
class Rva002A9850V94
{
  public:
    virtual void rvaSlot00();
    virtual void rvaSlot04();
    virtual void rvaSlot08();
    virtual void rvaSlot0C();
    virtual void rvaSlot10();
    virtual void rvaSlot14();
    virtual void rvaSlot18();
    virtual void rvaSlot1C();
    virtual void rvaSlot20();
    virtual void rvaSlot24();
    virtual void rvaSlot28();
    virtual void rvaSlot2C();
    virtual void rvaSlot30();
    virtual void rvaSlot34();
    virtual void rvaSlot38();
    virtual void rvaSlot3C();
    virtual void rvaSlot40();
    virtual void rvaSlot44();
    virtual void rvaSlot48();
    virtual void rvaSlot4C();
    virtual void rvaSlot50();
    virtual void rvaSlot54();
    virtual void rvaSlot58();
    virtual void rvaSlot5C();
    virtual void rvaSlot60();
    virtual void rvaSlot64();
    virtual void rvaSlot68();
    virtual void rvaSlot6C();
    virtual void rvaSlot70();
    virtual void rvaSlot74();
    virtual void rvaSlot78();
    virtual void rvaSlot7C();
    virtual void rvaSlot80();
    virtual void rvaSlot84();
    virtual void rvaSlot88();
    virtual void rvaSlot8C();
    virtual void rvaSlot90();
    virtual void call(bool);
};
class ExperienceTracker
{
  public:
    void addExperiencePoints(float, bool, bool, bool, bool);
};
class Player
{
  public:
    bool addSkillPoints(float, bool);
};
class Object;
class GameLogic
{
  public:
    Object *findObjectByID(ObjectID);
};
extern GameLogic *TheBfmeGameLogic;
class Overridable
{
  public:
    virtual ~Overridable();
    Overridable *friend_getFinalOverride()
    {
        if (m_nextOverride)
            return m_nextOverride->friend_getFinalOverride();
        return this;
    }
    const Overridable *friend_getFinalOverride() const
    {
        if (m_nextOverride)
            return m_nextOverride->friend_getFinalOverride();
        return this;
    }
    Overridable *m_nextOverride;
};
class SpecialPowerTemplate : public Overridable
{
  public:
    SpecialPowerType getSpecialPowerType() const
    {
        return ((const SpecialPowerTemplate *)friend_getFinalOverride())->m_type;
    }
    int cost() const
    {
        return ((const SpecialPowerTemplate *)friend_getFinalOverride())->m_rva20;
    }
    char m_rva08[12];
    SpecialPowerType m_type;
    char m_rva18[8];
    int m_rva20;
};
class SpecialPowerModuleInterface;
enum DisabledType
{
    DISABLED_RVA3 = 3
};
class Object
{
  public:
    void setDisabledUntil(DisabledType, unsigned);
    SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *) const;
    Player *getControllingPlayer() const;
    char m_rva00[8];
    Matrix3D m_rva08;
    Coord3D m_position;
    char m_rva44[0x30];
    ObjectID m_id;
    char m_rva78[0x98];
    Rva002A9850ModelConditionView m_modelConditionFlags;
    char m_rva138[0xC4];
    void *m_contain;
    void *m_body;
    void *m_ai;
    char m_rva208[8];
    ExperienceTracker *m_xp;
    Object *m_containedBy;
    char m_rva218[0x24];
    void *m_team;
};
class Rva002A9850Status
{
  public:
    unsigned words[3];
    Rva002A9850Status()
    {
        words[0] = 0;
        words[1] = 0;
        words[2] = 0;
    }
};
class BfmeOwnerBR
{
  public:
    void bfmeGo939B(int, Object *, DelayedLuaEventList *);
};
class SpecialAbilityUpdateModuleData
{
  public:
    char m_rva000[0x158];
    AudioEventRTS m_triggerSound;
    char m_rva1C8[12];
    AudioEventInfoRef m_rva1D4;
    const SpecialPowerTemplate *m_specialPowerTemplate;
    char m_rva1DC[12];
    AsciiString m_rva1E8;
    char m_rva1EC[20];
    int m_awardXPForTriggering;
    int m_skillPointsForTriggering;
    int m_rva208;
    char m_rva20C[36];
    int m_rva230;
    unsigned m_rva234;
    char m_rva238[16];
    bool m_loseStealthOnTrigger;
};
class SpecialAbilityUpdate
{
  protected:
    void triggerAbilityEffect();
    Object *getObject() const
    {
        return m_object;
    }
    const SpecialAbilityUpdateModuleData *getSpecialAbilityUpdateModuleData() const
    {
        return m_moduleData;
    }
    void *m_rva000;
    const SpecialAbilityUpdateModuleData *m_moduleData;
    Object *m_object;
    char m_rva00C[24];
    int m_rva024;
    char m_rva028[124];
    int m_rva0A4;
    char m_rva0A8[4];
    ObjectID m_targetID;
    Coord3D m_targetPos;
    char m_rva0BC[35];
    bool m_rva0DF;
};
__forceinline void *finalOverride(void *p)
{
    void *q = field<void *, 4>(p);
    if (q)
    {
        void *r = field<void *, 4>(q);
        if (r)
            return invoke<void *>(r, j_00048c61);
        return q;
    }
    return p;
}
__forceinline void clearModelConditionAt118(void *p, int bit)
{
    Rva002A9850ModelConditionView *flags = (Rva002A9850ModelConditionView *)((char *)p + 0x110);
    if (flags->bits.test(bit + 64))
    {
        flags->bits.reset(bit + 64);
        invoke<void>(p, j_0002191d);
    }
}
__forceinline void setModelConditionAt118(void *p, int bit)
{
    Rva002A9850ModelConditionView *flags = (Rva002A9850ModelConditionView *)((char *)p + 0x110);
    if (!flags->bits.test(bit + 64))
    {
        flags->bits.set(bit + 64);
        invoke<void>(p, j_0002191d);
    }
}
void SpecialAbilityUpdate::triggerAbilityEffect()
{
    const SpecialAbilityUpdateModuleData *data = getSpecialAbilityUpdateModuleData();
    Object *const object = getObject();
    const SpecialPowerTemplate *power = data->m_specialPowerTemplate;
    void *target = TheBfmeGameLogic->findObjectByID(m_targetID);
    void *module = ((Object *)object)->getSpecialPowerModule(data->m_specialPowerTemplate);
    if (module)
        ((Rva002A9850V40 *)module)->call();
    ++m_rva024;
    if (data->m_awardXPForTriggering)
    {
        void *xp = object->m_xp;
        if (xp)
            ((ExperienceTracker *)xp)
                ->addExperiencePoints((float)data->m_awardXPForTriggering, true, true, true, false);
    }
    int skill = data->m_skillPointsForTriggering != -1 ? data->m_skillPointsForTriggering
                                                       : data->m_awardXPForTriggering;
    if (skill > 0)
    {
        void *player = ((Object *)object)->getControllingPlayer();
        if (player)
            ((Player *)player)->addSkillPoints((float)skill, false);
    }
    if (global<0x012f0ff8>())
    {
        void *player = ((Object *)object)->getControllingPlayer();
        if (player)
            invoke<void>(player, j_00001a73, power->cost());
    }
    AudioEventRTS sound = data->m_triggerSound;
    sound.setObjectID(object->m_id);
    ((Rva002A9850V44 *)global<0x012ed668>())->call(&sound);
    if (data->m_rva1D4.ptr && !((Rva002A9850VB0 *)global<0x012ed668>())->call(m_rva0A4))
    {
        AudioEventRTS loop(data->m_rva1D4, object->m_id);
        m_rva0A4 = ((Rva002A9850V44 *)global<0x012ed668>())->call(&loop);
    }
    switch (power->getSpecialPowerType())
    {
    case 0x27:
    case 0x28:
        if (m_rva024 == 1)
        {
            void *contain = object->m_contain;
            if (contain)
            {
                if (!target)
                {
                    if (!invoke<int>(global<0x012ef4cc>(), j_000226ab, &m_targetPos, 5.0f, true,
                                     true))
                        break;
                    target = invoke<void *>(global<0x012ef4cc>(), j_00034ca2, &m_targetPos);
                    if (!target)
                        break;
                    m_targetID = field<ObjectID, 0x74>(target);
                }
                bool special = false;
                if (invoke<bool>(target, j_0003251f, 0x83) &&
                    invoke<int>((void *)power, j_00040a3e) == 0x28)
                    special = true;
                if ((invoke<bool>(target, j_0003251f, 0x87) &&
                     invoke<int>((void *)power, j_00040a3e) == 0x27) ||
                    special)
                {
                    if (!field<void *, 0x200>(target))
                        return;
                    void *body = field<void *, 0x200>(target);
                    if (!((Rva002A9850V70 *)body)->call().isEmpty())
                    {
                        body = field<void *, 0x200>(target);
                        void *model = invoke<void *>(global<0x012ef1d8>(), j_00028560,
                                                     &((Rva002A9850V70 *)body)->call());
                        Rva002A9850Status status;
                        void *created = invoke<void *>(global<0x012ef1d8>(), j_0004494a, model,
                                                       (void *)0, &status, 0);
                        if (created)
                        {
                            invoke<void>(created, j_0000d990, object);
                            ((Rva002A9850V88 *)contain)->call(created);
                        }
                    }
                    DamageInfo damage;
                    field<int, 0x10>(&damage) = 5;
                    field<int, 0x18>(&damage) = 1;
                    field<int, 8>(&damage) = 0;
                    body = field<void *, 0x200>(target);
                    field<float, 0x1c>(&damage) = ((Rva002A9850V78 *)body)->call();
                    field<int, 0x14>(&damage) = 7;
                    ((Rva002A9850V38 *)target)->call(&damage);
                    Coord3D initial;
                    initial.x = getObject()->m_position.x;
                    initial.y = getObject()->m_position.y;
                    initial.z = getObject()->m_position.z;
                    body = field<void *, 0x200>(target);
                    Coord2D offset = ((Rva002A9850V7C *)body)->call();
                    float angle = getObject()->m_rva08.Get_Z_Rotation();
                    float s = (float)sin(angle), c = (float)cos(angle);
                    Coord2D rotated;
                    rotated.x = offset.x * c - offset.y * s;
                    rotated.y = offset.x * s + offset.y * c;
                    Coord3D pos;
                    pos.z = initial.z;
                    pos.x = initial.x + rotated.x;
                    pos.y = initial.y + rotated.y;
                    body = field<void *, 0x200>(target);
                    typedef void(__cdecl * Fn)(void *, const Coord3D *, void *, float,
                                               const Coord3D *);
                    ((Fn)j_0001593d)(
                        ((Rva002A9850V74 *)body)->call(), &pos,
                        invoke<void *>(((Rva002A9850V28 *)getObject())->call(), j_00017512), 100.0f,
                        &pos);
                }
                else if (((Rva002A9850V84 *)contain)->call(target, true))
                {
                    void *held = field<void *, 0x214>(target);
                    if (held)
                    {
                        void *old = field<void *, 0x1fc>(held);
                        if (old)
                            ((Rva002A9850V90 *)old)->call(target, true);
                    }
                    ((Rva002A9850V88 *)contain)->call(target);
                    if (invoke<bool>(target, j_0003251f, 0x62))
                        setModelConditionAt118(target, 30);
                }
            }
            break;
        }
        if (m_rva024 == 2)
        {
            if (!target)
                break;
            if (invoke<bool>(target, j_0003251f, 6))
                setModelConditionAt118(target, 26);
            else if (invoke<bool>(target, j_0003251f, 0x62))
            {
                void *contain = object->m_contain;
                if (contain)
                    ((Rva002A9850V90 *)contain)->call(target, false);
                clearModelConditionAt118(getObject(), 30);
                clearModelConditionAt118(target, 30);
                int rva208 = data->m_rva208;
                if (rva208)
                {
                    if (rva208 == 1)
                        clearModelConditionAt118(getObject(), 32);
                    else if (rva208 == 2)
                        clearModelConditionAt118(getObject(), 33);
                    else if (rva208 == 3)
                        clearModelConditionAt118(getObject(), 34);
                }
                m_rva0DF = true;
            }
        }
    case 0x15:
        if (target && invoke<void *>((char *)object + 0x264, j_0003c8e9, 1))
        {
            invoke<void>(object, j_0003eebe, 1, 1);
            void *ai = object->m_ai;
            if (ai)
                invoke<void>((char *)ai + 0x20, j_0002edcf, target, 0x7fffffff, 2);
        }
        break;
    case 0x2b: {
        void *ai = object->m_ai;
        if (ai && target)
        {
            invoke<void>(object, j_0003eebe, 0, 1);
            if (invoke<void *>((char *)object + 0x264, j_0003c8e9, 0))
                invoke<void>((char *)ai + 0x20, j_0002edcf, target, 0x7fffffff, 2);
        }
        break;
    }
    case 0x66: {
        static int key = invoke<int>(global<0x012ed600>(), j_0003add7, "AutoHealBehavior");
        void *update = invoke<void *>(object, j_0002ae23, key);
        if (update)
            invoke<void>(update, j_00001a7d);
        break;
    }
    case 0x6f: {
        DelayedLuaEventList events;
        field<int, 0x10>(&events) = object->m_id;
        field<int, 0x18>(&events) = 3;
        ((BfmeOwnerBR *)global<0x012f060c>())->bfmeGo939B(8, object, &events);
        break;
    }
    case 0x6b:
        if (invoke<bool>(object, j_0003ab20, 0x10b))
        {
            static int key = invoke<int>(global<0x012ed600>(), j_0003add7, "SpecialDisguiseUpdate");
            void *update = invoke<void *>(object, j_0002ae23, key);
            if (update)
                invoke<void>(update, j_0003b5b1, false);
        }
        break;
    case 0x1a:
    case 0x1d: {
        if (!target || field<void *, 0x23c>(target) == object->m_team)
            return;
        void *contain = field<void *, 0x1fc>(target);
        if (contain && ((Rva002A9850V08 *)contain)->call())
            ((Rva002A9850V94 *)contain)->call(true);
        else
        {
            if (invoke<bool>(target, j_0001ff91))
                invoke<void>(global<0x012f142c>(), j_0002b5f3, 0x10, (void *)0);
            void *player = ((Object *)object)->getControllingPlayer();
            invoke<void>(target, j_00002d06, field<void *, 0x230>(player), 1);
            void *powerModule = invoke<void *>(this, j_000283ee);
            if (powerModule && invoke<int>((void *)power, j_00040a3e) == 0x1a)
                ((Rva002A9850V40 *)powerModule)->call();
        }
        break;
    }
    case 0x20: {
        static int key = invoke<int>(global<0x012ed600>(), j_0003add7, "StealthUpdate");
        if (target)
        {
            void *update = invoke<void *>(object, j_0002ae23, key);
            if (update)
                invoke<void>(update, j_0004027d, target);
        }
        break;
    }
    }
    if (data->m_loseStealthOnTrigger)
    {
        static int key = invoke<int>(global<0x012ed600>(), j_0003add7, "StealthUpdate");
        void *update = invoke<void *>(object, j_0002ae23, key);
        if (update)
            invoke<void>(update, j_00040dc2, 0, true);
    }
    if (data->m_rva234 > 0)
        ((Object *)object)
            ->setDisabledUntil(DISABLED_RVA3,
                               field<unsigned, 0x3c>(global<0x012f0898>()) + data->m_rva234);
    if (field<void *, 0>(&data->m_rva1E8) &&
        field<unsigned short, 4>(field<void *, 0>(&data->m_rva1E8)))
        invoke<void>(object, j_00037a56, &data->m_rva1E8, data->m_rva230);
}
