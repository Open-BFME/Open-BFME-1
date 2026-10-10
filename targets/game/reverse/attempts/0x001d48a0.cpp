// ?d_001d48a0@@YAXXZ
// partial score=0.5634 date=2026-10-10
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /I. /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// BFME Object snapshot receiver. Offsets are relative to Object+0x60.
#define _STLP_NO_EXCEPTIONS 1
#include "ascii_string.h"
#include <list>
#include <vector>
#include <utility>
#define _OPERATOR_NEW_DEFINED_
#include "game/Libraries/Source/WWVegas/WWMath/matrix3d.h"
#include "game/GameEngine/Source/Common/System/xfer.h"

struct __declspec(align(4)) Rva001D48A0Version
{
    unsigned char format, version;
};

class Rva001D48A0XferView
{
public:
    virtual void slot00();
    virtual bool IsLoading() const;
    virtual bool IsStoring() const;
    virtual bool IsCRC() const;
    virtual bool IsLightCRC() const;
    virtual void beginBlock(const char *);
    virtual void endBlock();
    virtual void skipBlock(const char *);
    virtual void slot20();
    virtual void slot24();
    virtual Rva001D48A0XferView &version(Rva001D48A0Version *);
    virtual void slot2c();
    virtual Rva001D48A0XferView &snapshot(void *);
    virtual void slot34();
    virtual void slot38();
    virtual void slot3c();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual Rva001D48A0XferView &integerCoord2(void *);
    virtual Rva001D48A0XferView &realCoord2(void *);
    virtual void slot54();
    virtual void slot58();
    virtual Rva001D48A0XferView &integerCoord3(void *);
    virtual Rva001D48A0XferView &realCoord3(void *);
    virtual void slot64();
    virtual Rva001D48A0XferView &text(AsciiString *);
    virtual Rva001D48A0XferView &real(float *);
    virtual void slot70();
    virtual Rva001D48A0XferView &unsignedInteger(unsigned int *);
    virtual Rva001D48A0XferView &integer(int *);
    virtual Rva001D48A0XferView &unsignedShort(unsigned short *);
    virtual void slot80();
    virtual Rva001D48A0XferView &unsignedByte(unsigned char *);
    virtual Rva001D48A0XferView &signedByte(signed char *);
    virtual Rva001D48A0XferView &boolean(bool *);
};

template<class T> __forceinline T &rva001D48A0Field(void *base, int offset)
{
    return *reinterpret_cast<T *>(reinterpret_cast<char *>(base) + offset);
}
template<class R, class A> struct Rva001D48A0Member
{
    R method(A);
};
template<class R, class A> __forceinline R rva001D48A0Call(void (*fn)(), void *self, A arg)
{
    typedef Rva001D48A0Member<R, A> Receiver;
    typedef R (Receiver::*Member)(A);
    union { void (*fn)(); Member member; } call = { fn };
    return (reinterpret_cast<Receiver *>(self)->*call.member)(arg);
}
template<class R> struct Rva001D48A0Member0 { R method(); };
template<class R> __forceinline R rva001D48A0Call0(void (*fn)(), void *self)
{
    typedef Rva001D48A0Member0<R> Receiver;
    typedef R (Receiver::*Member)();
    union { void (*fn)(); Member member; } call = { fn };
    return (reinterpret_cast<Receiver *>(self)->*call.member)();
}

void j_00031656();
void j_00033fcd();
void j_000361ce();
void j_0000335f();
void j_00020176();
void j_0003c8e9();
void j_00009b01();
void j_0000e570();
void j_00005a7e();
void j_00035a0d();
void j_00026dd7();
void j_00044c2e();
void j_0002c566();
void j_00008e72();
void j_000251e4();
void j_00049945();
void j_00044ce7();
void j_0002fc1b();
void j_0003fbcf();
void j_0000b81b();
void j_0003f75b();
void j_00009025();

class MidVirtualSlot90Receiver;
Xfer &Rva0010C3C0(MidVirtualSlot90Receiver *, void *);
void Rva0010C3E0(MidVirtualSlot90Receiver *, void *);
void Rva0010BF60(MidVirtualSlot90Receiver *, void *);
void Rva0010BE60(MidVirtualSlot90Receiver *, void *);
void BfmeParticleSystemXferMatrix(Xfer &, void *);
void xferBlob_0010CC40(Xfer *, void *);

class Overridable
{
public:
    const Overridable *getFinalOverride() const;
};
struct Rva001D48A0Override
{
    void *vtable;
    const Overridable *next;
};
__forceinline const Rva001D48A0Override *rva001D48A0Final(const Rva001D48A0Override *value)
{
    if (value && value->next)
        return reinterpret_cast<const Rva001D48A0Override *>(value->next->getFinalOverride());
    return value;
}

class Rva001D48A0VirtualView
{
public:
#define R48_SLOT(n) virtual void slot##n();
    R48_SLOT(00) R48_SLOT(04) R48_SLOT(08) R48_SLOT(0c)
    virtual float real10();
    R48_SLOT(14) R48_SLOT(18) R48_SLOT(1c)
    virtual bool boolean20();
    R48_SLOT(24)
    virtual Rva001D48A0VirtualView *pointer28();
    R48_SLOT(2c) R48_SLOT(30)
    virtual void invoke34();
    R48_SLOT(38) R48_SLOT(3c) R48_SLOT(40) R48_SLOT(44) R48_SLOT(48) R48_SLOT(4c)
    R48_SLOT(50) R48_SLOT(54) R48_SLOT(58) R48_SLOT(5c) R48_SLOT(60) R48_SLOT(64) R48_SLOT(68)
    virtual float real6c();
#undef R48_SLOT
};
class Rva001D48A0Terrain
{
public:
#define R48_TERRAIN(n) virtual void slot##n();
    R48_TERRAIN(00) R48_TERRAIN(01) R48_TERRAIN(02) R48_TERRAIN(03) R48_TERRAIN(04)
    R48_TERRAIN(05) R48_TERRAIN(06) R48_TERRAIN(07) R48_TERRAIN(08) R48_TERRAIN(09)
    R48_TERRAIN(10) R48_TERRAIN(11) R48_TERRAIN(12) R48_TERRAIN(13) R48_TERRAIN(14)
    R48_TERRAIN(15) R48_TERRAIN(16) R48_TERRAIN(17) R48_TERRAIN(18) R48_TERRAIN(19)
    R48_TERRAIN(20) R48_TERRAIN(21) R48_TERRAIN(22) R48_TERRAIN(23) R48_TERRAIN(24)
    R48_TERRAIN(25) R48_TERRAIN(26) R48_TERRAIN(27) R48_TERRAIN(28) R48_TERRAIN(29)
    R48_TERRAIN(30) R48_TERRAIN(31) R48_TERRAIN(32) R48_TERRAIN(33) R48_TERRAIN(34) R48_TERRAIN(35)
#undef R48_TERRAIN
    virtual void *findTrigger(AsciiString name);
};
enum NameKeyType { Rva001D48A0InvalidKey = 0 };
class NameKeyGenerator
{
public:
    AsciiString keyToName(NameKeyType);
    NameKeyType nameToKey(const char *);
};
class Rva001C2DC0
{
public:
    AsciiString method() const;
};

extern void *TheGameLogic;
class TeamFactory;
class Radar;
extern TeamFactory *TheTeamFactory;
extern Radar *TheRadar;
extern void *TheAI;
extern void *TheTerrainLogic;
extern NameKeyGenerator *g_theNameKeyGenerator;

__forceinline void rva001D48A0SetID(void *owner, unsigned int id)
{
    if (rva001D48A0Field<unsigned int>(owner, 0x74) == id)
        return;
    if (rva001D48A0Field<unsigned int>(owner, 0x74))
        rva001D48A0Call<void, void *>(j_00031656, TheGameLogic, owner);
    rva001D48A0Field<unsigned int>(owner, 0x74) = id;
    if (id)
        rva001D48A0Call<void, void *>(j_00033fcd, TheGameLogic, owner);
}
__forceinline unsigned int rva001D48A0StateID(void *ai)
{
    void *machine = rva001D48A0Field<void *>(ai, 0x30);
    void *state = rva001D48A0Field<void *>(machine, 0x1c);
    if (state) return rva001D48A0Field<unsigned int>(state, 4);
    return 999999;
}
__forceinline void *rva001D48A0Goal(void *ai)
{
    return rva001D48A0Call0<void *>(j_0000e570, rva001D48A0Field<void *>(ai, 0x30));
}
__forceinline unsigned int rva001D48A0GoalID(void *ai)
{
    if (rva001D48A0Goal(ai))
        return rva001D48A0Field<unsigned int>(rva001D48A0Goal(ai), 0x74);
    return 0;
}
__forceinline unsigned int rva001D48A0TeamID(void *team)
{
    if (team) return rva001D48A0Field<unsigned int>(team, 8);
    return 0;
}

struct Rva001D48A0Exception { char *text; int tag; };
extern "C" Rva001D48A0Exception *__cdecl bfmeFormatText(Rva001D48A0Exception *, int, const char *, ...);
extern int g_guardTargetTypeThrowInfo;
extern "C" void __stdcall _CxxThrowException(void *, _ThrowInfo *);
__declspec(noreturn) __forceinline void rva001D48A0Throw(Rva001D48A0Exception &error, int tag)
{
    bfmeFormatText(&error, tag, 0);
    _CxxThrowException(&error, reinterpret_cast<_ThrowInfo *>(&g_guardTargetTypeThrowInfo));
}

extern "C" const void *__identifier("??_7DamageInfo@@6B@")[];

class DamageInfoInput
{
public:
    virtual void rva001D48A0Transfer(Xfer *);
    unsigned int m_04;
    unsigned short m_08;
    int m_0c, m_10, m_14;
    float m_18;
    bool m_1c, m_1d;
    float m_20;
    unsigned int m_24;
    unsigned int m_28;
    float m_2c, m_30, m_34, m_38, m_3c, m_40, m_44;
    DamageInfoInput()
    {
        m_04 = 0; m_08 = 0; m_0c = 0x16; m_10 = 0xf; m_14 = 0;
        m_18 = 0.0f; m_1c = false; m_1d = true; m_20 = 0.0f; m_24 = 0; m_28 = 0;
        m_2c = 0.0f; m_30 = 0.0f; m_34 = 0.0f; m_38 = 0.0f;
        m_3c = 0.0f; m_40 = 0.0f; m_44 = 1.0f;
    }
};
class DamageInfoOutput
{
public:
    virtual void rva001D48A0Transfer(Xfer *);
    float actual, clipped;
    bool noEffect;
    DamageInfoOutput() : actual(0.0f), clipped(0.0f), noEffect(false) {}
};
struct Rva001D28F0Element
{
    void *vtable;
    DamageInfoInput input;
    DamageInfoOutput output;
    Rva001D28F0Element() : vtable((void *)__identifier("??_7DamageInfo@@6B@")) {}
    Rva001D28F0Element(const Rva001D28F0Element &other) : vtable((void *)__identifier("??_7DamageInfo@@6B@")), input(other.input), output(other.output) {}
};
struct Rva001D48A0DamageVirtual { virtual void transfer(Xfer *); };
namespace _STL
{
// ??$__copy@PAURva001D28F0Element@@PAU1@H@_STL@@YAPAURva001D28F0Element@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z absent-from-retail
template<> __forceinline Rva001D28F0Element *__copy<Rva001D28F0Element *, Rva001D28F0Element *, int>(
    Rva001D28F0Element *first, Rva001D28F0Element *last, Rva001D28F0Element *result,
    const random_access_iterator_tag &tag, int *distance)
{
    typedef Rva001D28F0Element *(__cdecl *Copy)(Rva001D28F0Element *, Rva001D28F0Element *,
                                            Rva001D28F0Element *, const random_access_iterator_tag &, int *);
    union { void (*fn)(); Copy copy; } call = { j_00009025 };
    return call.copy(first, last, result, tag, distance);
}
}
struct Rva001D48A0TriggerInfo
{
    void *trigger;
    signed char entered, exited, inside;
};
struct Rva001D48A0Coord3 { float x, y, z; };
struct Rva001D48A0StatePosition
{
    unsigned char m_beforePosition[0x24];
    Rva001D48A0Coord3 m_position;
    const Rva001D48A0Coord3 *getPosition() const { return &m_position; }
};
typedef Matrix3D Rva001D48A0Matrix;

class Rva001D48A0
{
public:
    void method(Xfer *xfer);
    template<class T> __forceinline T &field(int offset) { return rva001D48A0Field<T>(this, offset); }
};

// ?method@Rva001D48A0@@QAEXPAVXfer@@@Z
void Rva001D48A0::method(Xfer *xfer)
{
    Rva001D48A0XferView *receiver = reinterpret_cast<Rva001D48A0XferView *>(xfer);
    MidVirtualSlot90Receiver *typed = reinterpret_cast<MidVirtualSlot90Receiver *>(xfer);
    Rva001D48A0Version version = { 1, 11 };
    receiver->version(&version);
    receiver->text(&field<AsciiString>(0x1e8));
    bool nonLightCRC = !receiver->IsLightCRC();
    const Rva001D48A0Override *objectTemplate = rva001D48A0Final(field<Rva001D48A0Override *>(-0x5c));
    AsciiString templateName(rva001D48A0Field<AsciiString>(const_cast<Rva001D48A0Override *>(objectTemplate), 0x20));
    receiver->text(&templateName);
    unsigned int id = field<unsigned int>(0x14);
    Rva0010C3C0(typed, &id);
    void *owner = reinterpret_cast<char *>(this) - 0x60;
    rva001D48A0SetID(owner, id);
    if (!receiver->IsLightCRC())
    {
        Rva001D48A0Matrix matrix = field<Rva001D48A0Matrix>(-0x58);
        BfmeParticleSystemXferMatrix(*xfer, &matrix);
        if (receiver->IsLoading())
            rva001D48A0Call<void, const Rva001D48A0Matrix *>(j_000361ce, owner, &matrix);
    }
    receiver->unsignedByte(&field<unsigned char>(0x2e4));
    if (nonLightCRC)
        xferBlob_0010CC40(xfer, &field<unsigned int>(0x1c4));
    else
        rva001D48A0Call<void, Xfer *>(j_0000335f, &field<unsigned int>(0x1c4), xfer);
    receiver->snapshot(field<void *>(0x1b0));
    receiver->unsignedInteger(&field<unsigned int>(0x240));
    if (receiver->IsLightCRC())
    {
        Rva001D48A0VirtualView *body = field<Rva001D48A0VirtualView *>(0x1a0);
        float health = body->real10();
        receiver->real(&health);
        float maxHealth = field<Rva001D48A0VirtualView *>(0x1a0)->real6c();
        receiver->real(&maxHealth);
        Rva0010C3C0(typed, &field<unsigned int>(0x18));
        Rva0010C3C0(typed, &field<unsigned int>(0x1c));
        receiver->integerCoord3(&field<int>(0x2a4));
        receiver->integerCoord2(&field<int>(0x3c));
        receiver->integerCoord2(&field<int>(0x44));
        receiver->text(&field<AsciiString>(0x1e0));
        void *ai = field<void *>(0x1a4);
        if (ai)
        {
            AsciiString name = reinterpret_cast<Rva001C2DC0 *>(ai)->method();
            receiver->text(&name);
            unsigned int stateId = rva001D48A0StateID(ai);
            receiver->unsignedInteger(&stateId);
            unsigned int target = rva001D48A0GoalID(ai);
            Rva0010C3C0(typed, &target);
            Rva001D48A0StatePosition *machine = rva001D48A0Field<Rva001D48A0StatePosition *>(ai, 0x30);
            Rva001D48A0Coord3 coord;
            const Rva001D48A0Coord3 *position = machine->getPosition();
            if (position) coord = *machine->getPosition();
            else { coord.x = 0.0f; coord.y = 0.0f; coord.z = 0.0f; }
            receiver->realCoord3(&coord);
        }
        for (int i = 0; i < 4; ++i)
        {
            void *weapon = rva001D48A0Call<void *, int>(j_0003c8e9, &field<unsigned int>(0x204), i);
            if (weapon) receiver->snapshot(weapon);
        }
        return;
    }
    void *team = field<void *>(0x1dc);
    unsigned int teamId = rva001D48A0TeamID(team);
    receiver->unsignedInteger(&teamId);
    Rva0010C3C0(typed, &field<unsigned int>(0x18));
    Rva0010C3C0(typed, &field<unsigned int>(0x1c));
    Rva001D48A0VirtualView *draw = reinterpret_cast<Rva001D48A0VirtualView *>(owner)->pointer28();
    unsigned int drawableId = draw ? rva001D48A0Call0<unsigned int>(j_00009b01, draw) : 0;
    if (!receiver->IsCRC()) Rva0010C3E0(typed, &drawableId);
    if (receiver->IsLoading())
    {
        if (!draw)
        {
            Rva001D48A0Exception error;
            rva001D48A0Throw(error, 0);
        }
        rva001D48A0Call<void, unsigned int>(j_00005a7e, draw, drawableId);
    }
    receiver->text(&field<AsciiString>(0x24));
    rva001D48A0Call<void, Xfer *>(j_00035a0d, &field<unsigned int>(0x30), xfer);
    receiver->integerCoord2(&field<int>(0x3c));
    receiver->integerCoord2(&field<int>(0x44));
    rva001D48A0Call<void, Xfer *>(j_00026dd7, &field<unsigned int>(0xb0), xfer);
    receiver->unsignedByte(&field<unsigned char>(0x2e3));
    receiver->unsignedInteger(&field<unsigned int>(0x30c));
    if (receiver->IsLoading())
    {
        team = rva001D48A0Call<void *, unsigned int>(j_00044c2e, TheTeamFactory, teamId);
        if (!team)
        {
            Rva001D48A0Exception error;
            rva001D48A0Throw(error, 5);
        }
        struct Restore { void method(void *, bool); };
        typedef void (Restore::*Fn)(void *, bool);
        union { void (*fn)(); Fn member; } call = { j_0002c566 };
        (reinterpret_cast<Restore *>(owner)->*call.member)(team, true);
    }
    receiver->snapshot(&field<unsigned int>(0x4c));
    receiver->real(&field<float>(0x134));
    receiver->real(&field<float>(0x138));
    receiver->real(&field<float>(0x13c));
    rva001D48A0Call<void, Xfer *>(j_00008e72, &field<unsigned int>(0x144), xfer);
    receiver->boolean(&field<bool>(0x2e7));
    for (int i = 0; i < 11; ++i)
        receiver->unsignedInteger(&field<unsigned int>(0x148 + i * 4));
    if (receiver->IsLoading() && field<void *>(0x1ac))
        rva001D48A0Call<void, void *>(j_000251e4, TheRadar, owner);
    if (receiver->IsStoring())
    {
        void *container = field<void *>(0x1b4);
        if (container)
            field<unsigned int>(0x1b8) = rva001D48A0Field<unsigned int>(container, 0x74);
        else
            field<unsigned int>(0x1b8) = 0;
    }
    Rva0010C3C0(typed, &field<unsigned int>(0x1b8));
    receiver->unsignedInteger(&field<unsigned int>(0x1bc));
    receiver->real(&field<float>(0x1c0));
    receiver->text(&field<AsciiString>(0x1e0));
    receiver->integer(&field<int>(0x1e4));
    receiver->realCoord3(&field<float>(0x1ec));
    receiver->realCoord3(&field<float>(0x248));
    Rva0010C3C0(typed, &field<unsigned int>(0x254));
    typedef _STL::pair<int, AsciiString> MissingTrigger;
    _STL::list<MissingTrigger> &missingTriggers = field<_STL::list<MissingTrigger> >(0x2b0);
    rva001D48A0Call0<void>(j_00049945, &missingTriggers);
    receiver->signedByte(&field<signed char>(0x2e6));
    receiver->unsignedInteger(&field<unsigned int>(0x2a0));
    receiver->integerCoord3(&field<int>(0x2a4));
    if (field<signed char>(0x2e6) < 0 || field<signed char>(0x2e6) > 5)
    {
        Rva001D48A0Exception error;
        rva001D48A0Throw(error, 5);
    }
    for (int i = 0; i < field<signed char>(0x2e6); ++i)
    {
        AsciiString triggerName;
        Rva001D48A0TriggerInfo &trigger = field<Rva001D48A0TriggerInfo>(0x278 + i * 8);
        if (trigger.trigger) triggerName = rva001D48A0Field<AsciiString>(trigger.trigger, 8);
        receiver->text(&triggerName);
        if (receiver->IsLoading())
            trigger.trigger = reinterpret_cast<Rva001D48A0Terrain *>(TheTerrainLogic)->findTrigger(triggerName);
        receiver->signedByte(&trigger.entered);
        receiver->signedByte(&trigger.exited);
        receiver->signedByte(&trigger.inside);
        if (!trigger.trigger)
            missingTriggers.push_back(_STL::make_pair(i, triggerName));
    }
    Rva0010BF60(typed, &field<unsigned int>(0x2b4));
    Rva0010BF60(typed, &field<unsigned int>(0x2b8));
    receiver->boolean(&field<bool>(0x2e0));
    receiver->unsignedInteger(&field<unsigned int>(0x2d0));
    Rva0010BE60(typed, &field<unsigned int>(0x2bc));
    if (field<unsigned int>(0x2bc)) receiver->realCoord2(&field<float>(0x2c0));
    unsigned short moduleCount = 0;
    for (void **b = field<void **>(0x190); *b; ++b) ++moduleCount;
    receiver->unsignedShort(&moduleCount);
    AsciiString moduleIdentifier;
    if (receiver->IsStoring())
    {
        for (void **b = field<void **>(0x190); *b; ++b)
        {
            void *module = *b;
            void *moduleData = rva001D48A0Field<void *>(module, 4);
            moduleIdentifier = g_theNameKeyGenerator->keyToName(rva001D48A0Field<NameKeyType>(moduleData, 4));
            receiver->text(&moduleIdentifier);
            receiver->beginBlock("BehaviorModule");
            receiver->snapshot(module);
            receiver->endBlock();
        }
    }
    else
    {
        AsciiString otherModuleIdentifier;
        for (unsigned short i = 0; i < moduleCount; ++i)
        {
            receiver->text(&moduleIdentifier);
            NameKeyType key = g_theNameKeyGenerator->nameToKey(moduleIdentifier.str());
            void *module = 0;
            for (void **b = field<void **>(0x190); b && *b; ++b)
            {
                void *moduleData = rva001D48A0Field<void *>(*b, 4);
                if (key == rva001D48A0Field<NameKeyType>(moduleData, 4)) { module = *b; break; }
            }
            if (!module) receiver->skipBlock("BehaviorModule");
            else
            {
                receiver->beginBlock("BehaviorModule");
                receiver->snapshot(module);
                receiver->endBlock();
            }
        }
    }
    Rva0010C3C0(typed, &field<unsigned int>(0x270));
    receiver->unsignedInteger(&field<unsigned int>(0x274));
    receiver->snapshot(field<void *>(0x188));
    rva001D48A0Call<void, Xfer *>(j_00044ce7, &field<unsigned int>(0x23c), xfer);
    for (int i = 0; i < 4; ++i) receiver->signedByte(&field<signed char>(0x244 + i));
    receiver->snapshot(&field<unsigned int>(0x204));
    rva001D48A0Call<void, Xfer *>(j_0002fc1b, &field<unsigned int>(0x260), xfer);
    receiver->text(&field<AsciiString>(0x2c8));
    if (version.version >= 11) receiver->text(&field<AsciiString>(0x2cc));
    receiver->boolean(&field<bool>(0x2e1));
    receiver->boolean(&field<bool>(0x2e2));
    receiver->boolean(&field<bool>(0x2e8));
    if (!receiver->IsCRC()) receiver->unsignedInteger(&field<unsigned int>(0x2d4));
    _STL::vector<Rva001D28F0Element> &damage = field<_STL::vector<Rva001D28F0Element> >(0x2ec);
    if (receiver->IsStoring())
    {
        unsigned int count = damage.size();
        receiver->unsignedInteger(&count);
        for (_STL::vector<Rva001D28F0Element>::iterator i = damage.begin(); i != damage.end(); ++i)
            reinterpret_cast<Rva001D48A0DamageVirtual *>(&*i)->transfer(xfer);
    }
    else
    {
        damage.clear();
        unsigned int count;
        receiver->unsignedInteger(&count);
        for (unsigned int i = 0; i < count; ++i)
        {
            Rva001D28F0Element item;
            rva001D48A0Call<void, Xfer *>(j_0003f75b, &item, xfer);
            damage.push_back(item);
        }
    }
    receiver->unsignedInteger(&field<unsigned int>(0x2fc));
    receiver->real(&field<float>(0x2f8));
    Rva0010C3C0(typed, &field<unsigned int>(0x300));
    receiver->boolean(&field<bool>(0x30a));
    receiver->unsignedByte(&field<unsigned char>(0x2e5));
    if (!receiver->IsCRC())
    {
        receiver->integer(&field<int>(0x310));
        if (version.version < 10)
        {
            int oldValue;
            receiver->integer(&oldValue);
            AsciiString oldName;
            receiver->text(&oldName);
        }
        if (version.version >= 7)
            rva001D48A0Call<void, Xfer *>(j_0003fbcf, &field<unsigned int>(0x314), xfer);
        else if (version.version >= 6)
        {
            receiver->integer(&field<int>(0x318));
            receiver->integer(&field<int>(0x31c));
            receiver->integer(&field<int>(0x320));
        }
    }
    receiver->boolean(&field<bool>(0x33c));
    receiver->boolean(&field<bool>(0x130));
    receiver->boolean(&field<bool>(0x308));
    receiver->integer(&field<int>(0x338));
    receiver->real(&field<float>(0x140));
    receiver->real(&field<float>(0x12c));
    if (receiver->IsLoading())
    {
        Rva001D48A0VirtualView *drawable = reinterpret_cast<Rva001D48A0VirtualView *>(owner)->pointer28();
        if (drawable) drawable->invoke34();
    }
    if (version.version >= 2) receiver->unsignedInteger(&field<unsigned int>(0x2d8));
    if (version.version >= 3) receiver->unsignedInteger(&field<unsigned int>(0x2dc));
    if (version.version >= 4) receiver->boolean(&field<bool>(0x348));
    receiver->unsignedInteger(&field<unsigned int>(0x34c));
    if (version.version >= 5) Rva0010C3C0(typed, &field<unsigned int>(0x340));
    if (version.version >= 8) Rva0010C3C0(typed, &field<unsigned int>(0x344));
    if (version.version >= 9) receiver->real(&field<float>(0x1f8));
    if (receiver->IsLoading())
    {
        objectTemplate = rva001D48A0Final(field<Rva001D48A0Override *>(-0x5c));
        if (rva001D48A0Field<unsigned int>(const_cast<Rva001D48A0Override *>(objectTemplate), 0xcc) & 0x08000000)
        {
            if (!(field<unsigned char>(0x2e4) & 1) || (field<Rva001D48A0VirtualView *>(0x1a0) && !field<Rva001D48A0VirtualView *>(0x1a0)->boolean20()))
                rva001D48A0Call<void, void *>(j_0000b81b, rva001D48A0Field<void *>(TheAI, 0xc), owner);
        }
    }
}
