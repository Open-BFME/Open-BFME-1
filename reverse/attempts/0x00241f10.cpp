// ?d_00241f10@@YAXXZ
// partial score=0.42 date=2026-09-23
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWMath
#define _STLP_USE_STATIC_LIB 1
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1

#include <list>
#include <map>
#include "coord.h"

typedef float Real;

class Object;
class Weapon;
class WeaponSlotType;

template<int N>
class AIUpdateSlots : public AIUpdateSlots<N - 1> {
public:
    virtual void unused(char (*)[N]) = 0;
};

template<>
class AIUpdateSlots<0> {
public:
    virtual void unused(char (*)[0]) = 0;
};

class AIUpdateInterface : public AIUpdateSlots<99> {
public:
    virtual bool blocksFormationRefresh() = 0;
};

class Overridable {
public:
    const Overridable *getFinalOverride() const;
    void *m_vtable;
    Overridable *m_override;
    char pad008[0xcc - 0x08];
    unsigned int flagsCC;
    char padD0[4];
    unsigned int flagsD4;
};

#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")

class ByteField {
public:
    unsigned char get() const;
};

class Weapon {
public:
    virtual void slot00() = 0;
    ByteField *m_field;
    Real getAttackRange(const Object *target) const;
};

class Object {
public:
    virtual void slot00() = 0;
    Overridable *m_template;
    char pad008[0x38 - 0x08];
    Coord3D m_position;
    char pad044[0x74 - 0x44];
    int m_id;
    char pad078[0x90 - 0x78];
    unsigned int flags90;
    char pad094[0x204 - 0x94];
    AIUpdateInterface *m_ai;
    char pad208[0x214 - 0x208];
    void *field214;
};

class AICommandInterface {
public:
    void aiIdle(int source);
    void aiAttackObject(Object *target, int maxShots, int source);
};

class Pathfinder {
public:
    void removeGoal(Object *object);
};

class AI {
public:
    char pad000[12];
    Pathfinder *pathfinder;
};

extern AI *TheAI;

class Rva001CBDC0Receiver {
public:
    void clear(int value);
};

class Rva00241F10RefreshHook {
public:
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08() = 0;
    virtual void slot0c() = 0;
    virtual void refresh(int value) = 0;
};

class Rva00241F10Lookup {
public:
    std::map<void *, int> entries;
};

class Rva00241F10View {
public:
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08() = 0;
    virtual void slot0c() = 0;
    virtual void slot10(int value) = 0;
    char pad004[0x34 - 0x04];
    Rva00241F10RefreshHook *refreshHook;
    char pad038[4];
    std::map<int, int> memberIndices;
    unsigned char *memberSlots;

    void update(Object *target);
};

extern void j_00015d02();
extern void j_00024d70();
extern void j_00028f74();
extern void j_0002e631();
extern void j_00031a7f();
extern void j_0003f544();
extern void j_00041dad();
extern void j_00044774();
extern void j_0004c37();
extern void j_000d3b9();
extern void j_000e4a8();
extern void j_0001f000();
extern void j_0002edcf();

typedef void (Pathfinder::*RemoveGoalCall)(Object *);
typedef void (AICommandInterface::*IdleCall)(int);
typedef void (AICommandInterface::*AttackCall)(Object *, int, int);
typedef Weapon *(Object::*CurrentWeaponCall)(WeaponSlotType *);
typedef unsigned char (ByteField::*ByteGetCall)() const;
typedef Real (Weapon::*AttackRangeCall)(const Object *) const;
typedef void *(Object::*OpaqueObjectCall)() const;
typedef bool (__cdecl *TargetPredicateCall)(void *, void *);
typedef char (__stdcall *CurrentTargetCall)(void *, void *);
typedef void (*RawCall)();

template<class T>
static T memberCall(RawCall raw) {
    union {
        RawCall raw;
        T member;
    } call;
    call.raw = raw;
    return call.member;
}

class TargetContainer {
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
    virtual void slot24() = 0;
    virtual void slot28() = 0;
    virtual void slot2c() = 0;
    virtual void slot30() = 0;
    virtual void slot34() = 0;
    virtual void slot38() = 0;
    virtual void slot3c() = 0;
    virtual void slot40() = 0;
    virtual void slot44() = 0;
    virtual Object *select(int mode, const Coord3D *position, Real range) = 0;
};

void Rva00241F10View::update(Object *target) {
    Object *owner = *(Object **)((char *)this - 0xdc);
    Overridable *ownerTemplate = owner->m_template;
    if (ownerTemplate != 0 && ownerTemplate->m_override != 0) {
        ownerTemplate = (Overridable *)ownerTemplate->m_override->getFinalOverride();
    }
    if ((ownerTemplate->flagsD4 & 0x400000) != 0) {
        Weapon *weapon = (owner->*memberCall<CurrentWeaponCall>(j_00031a7f))((WeaponSlotType *)0);
        if (weapon == 0) {
            return;
        }
        if ((weapon->m_field->*memberCall<ByteGetCall>(j_00028f74))() != 0) {
            return;
        }
    }

    if (*(int *)((char *)*(Object **)((char *)this - 0xdc) + 0x9c) >= 0) {
        (TheAI->pathfinder->*memberCall<RemoveGoalCall>(j_00015d02))(
            *(Object **)((char *)this - 0xdc));
    }
    if (refreshHook != 0) {
        ((Rva00241F10View *)this)->slot10(0);
    }

    Rva00241F10Lookup *targetLookup = (Rva00241F10Lookup *)
        ((char *)(*(void **)((char *)this - 0xe0)) + 0x250);

    Object *source = (Object *)target->field214;
    Overridable *targetTemplate = target->m_template;
    if (targetTemplate != 0 && targetTemplate->m_override != 0) {
        targetTemplate = (Overridable *)targetTemplate->m_override->getFinalOverride();
        if ((targetTemplate->flagsD4 & 0x100000) != 0) {
            source = target;
        }
    }

    typedef std::list<Object *> MemberList;
    MemberList &members = *(MemberList *)((char *)this - 0xac);
    for (MemberList::iterator it = members.begin(); it != members.end(); ++it) {
        Object *member = *it;
        std::map<int, int>::iterator index = memberIndices.find(member->m_id);
        if (index == memberIndices.end()) {
            continue;
        }
        AIUpdateInterface *ai = member->m_ai;
        if (ai == 0 || ai->blocksFormationRefresh()) {
            continue;
        }
        Weapon *weapon = (member->*memberCall<CurrentWeaponCall>(j_00031a7f))((WeaponSlotType *)0);
        if (weapon == 0) {
            continue;
        }
        weapon = (member->*memberCall<CurrentWeaponCall>(j_00031a7f))((WeaponSlotType *)0);
        if (weapon != 0 && (weapon->m_field->*memberCall<ByteGetCall>(j_00028f74))() != 0) {
            if (ai->blocksFormationRefresh()) {
                (((AICommandInterface *)((char *)ai + 0x20))->*memberCall<IdleCall>(j_00024d70))(2);
            }
            if ((member->flags90 & 0x10000000) == 0) {
                (((Rva001CBDC0Receiver *)member)->*memberCall<void (Rva001CBDC0Receiver::*)(int)>(j_000e4a8))(0);
            }
            continue;
        }

        unsigned char *slot = memberSlots + index->second * 16;
        if (targetLookup->entries.find((void *)*(void **)slot) == targetLookup->entries.end()) {
            continue;
        }
        Object *candidate = target;
        if (memberCall<CurrentTargetCall>(j_0003f544)((void *)ai, (void *)target)) {
            continue;
        }
        TargetContainer *container = 0;
        if (source != 0) {
            container = (TargetContainer *)(source->*memberCall<OpaqueObjectCall>(j_000d3b9))();
        }
        Real range = 0.0f;
        if (container != 0 && weapon != 0) {
            range = (weapon->*memberCall<AttackRangeCall>(j_0002e631))(source);
            candidate = container->select(0, &member->m_position, range);
        }
        if (candidate != 0 && memberCall<TargetPredicateCall>(j_0004c37)((void *)member, (void *)candidate)) {
            (((AICommandInterface *)((char *)ai + 0x20))->*memberCall<AttackCall>(j_0002edcf))(candidate, 0x7fffffff, 2);
        }
    }
}
