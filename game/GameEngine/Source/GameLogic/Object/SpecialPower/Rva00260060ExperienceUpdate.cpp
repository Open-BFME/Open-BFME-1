// cl: /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport

#include "Common/GameMemory.h"
#include "Common/Overridable.h"
#include "Common/KindOf.h"

// Address-labelled ABI reconstruction for retail RVA 0x00260060, 222 bytes, ending RET 4 at 0x0026013B.
// Object+0x1FC is m_contain; ContainModule.h establishes the callback ABI.
// A missing template skips only override resolution: retail still reads +0xD4.
// The original owner identity is deliberately not asserted.
class Object;
class ExperienceTracker;

typedef void (__cdecl *ContainIterateFunc)(Object *, void *);

// Only the retail virtual position is claimed.  Slots 0..62 are deliberately
// unnamed; iterateContained is the observed slot 63 (vtable byte offset 0xfc).
class Rva00260060ContainView {
#define RVA00260060_UNUSED_SLOT(N) virtual void rvaSlot##N();
    RVA00260060_UNUSED_SLOT(00)
    RVA00260060_UNUSED_SLOT(01)
    RVA00260060_UNUSED_SLOT(02)
    RVA00260060_UNUSED_SLOT(03)
    RVA00260060_UNUSED_SLOT(04)
    RVA00260060_UNUSED_SLOT(05)
    RVA00260060_UNUSED_SLOT(06)
    RVA00260060_UNUSED_SLOT(07)
    RVA00260060_UNUSED_SLOT(08)
    RVA00260060_UNUSED_SLOT(09)
    RVA00260060_UNUSED_SLOT(10)
    RVA00260060_UNUSED_SLOT(11)
    RVA00260060_UNUSED_SLOT(12)
    RVA00260060_UNUSED_SLOT(13)
    RVA00260060_UNUSED_SLOT(14)
    RVA00260060_UNUSED_SLOT(15)
    RVA00260060_UNUSED_SLOT(16)
    RVA00260060_UNUSED_SLOT(17)
    RVA00260060_UNUSED_SLOT(18)
    RVA00260060_UNUSED_SLOT(19)
    RVA00260060_UNUSED_SLOT(20)
    RVA00260060_UNUSED_SLOT(21)
    RVA00260060_UNUSED_SLOT(22)
    RVA00260060_UNUSED_SLOT(23)
    RVA00260060_UNUSED_SLOT(24)
    RVA00260060_UNUSED_SLOT(25)
    RVA00260060_UNUSED_SLOT(26)
    RVA00260060_UNUSED_SLOT(27)
    RVA00260060_UNUSED_SLOT(28)
    RVA00260060_UNUSED_SLOT(29)
    RVA00260060_UNUSED_SLOT(30)
    RVA00260060_UNUSED_SLOT(31)
    RVA00260060_UNUSED_SLOT(32)
    RVA00260060_UNUSED_SLOT(33)
    RVA00260060_UNUSED_SLOT(34)
    RVA00260060_UNUSED_SLOT(35)
    RVA00260060_UNUSED_SLOT(36)
    RVA00260060_UNUSED_SLOT(37)
    RVA00260060_UNUSED_SLOT(38)
    RVA00260060_UNUSED_SLOT(39)
    RVA00260060_UNUSED_SLOT(40)
    RVA00260060_UNUSED_SLOT(41)
    RVA00260060_UNUSED_SLOT(42)
    RVA00260060_UNUSED_SLOT(43)
    RVA00260060_UNUSED_SLOT(44)
    RVA00260060_UNUSED_SLOT(45)
    RVA00260060_UNUSED_SLOT(46)
    RVA00260060_UNUSED_SLOT(47)
    RVA00260060_UNUSED_SLOT(48)
    RVA00260060_UNUSED_SLOT(49)
    RVA00260060_UNUSED_SLOT(50)
    RVA00260060_UNUSED_SLOT(51)
    RVA00260060_UNUSED_SLOT(52)
    RVA00260060_UNUSED_SLOT(53)
    RVA00260060_UNUSED_SLOT(54)
    RVA00260060_UNUSED_SLOT(55)
    RVA00260060_UNUSED_SLOT(56)
    RVA00260060_UNUSED_SLOT(57)
    RVA00260060_UNUSED_SLOT(58)
    RVA00260060_UNUSED_SLOT(59)
    RVA00260060_UNUSED_SLOT(60)
    RVA00260060_UNUSED_SLOT(61)
    RVA00260060_UNUSED_SLOT(62)
#undef RVA00260060_UNUSED_SLOT
public:
    virtual void iterateContained(ContainIterateFunc, void *, Bool);
};

class GameLogic {
public:
    Object *findObjectByID(int);
};

extern GameLogic *TheBfmeGameLogic;

// This is the canonical Overridable base: getNextOverride() is the inline
// const +4 load.  The retail target at ILT 0x22bb is an out-of-line call, so it
// uses this existing declaration-only const view rather than the recursive
// canonical inline getFinalOverride().
class BfmeControlBarOverridable {
public:
    const BfmeControlBarOverridable *getFinalOverride() const;
};

class ThingTemplate : public Overridable {
};

class Thing {
public:
    void *m_vtable;
    ThingTemplate *m_template;

    ThingTemplate *getTemplate() const { return m_template; }
    Bool isKindOf(KindOfType) const;
};

class FXList {
public:
    static void doFXObj(const FXList *, const Object *, const Object *);
};

extern void __cdecl containedFXAt0025FD80(Object *, void *);

class Object : public Thing {
public:
    unsigned char m_08_to_78[0x70];
    int m_producerID;
    unsigned char m_7c_to_1fc[0x180];
    void *m_contain;
    unsigned char m_200_to_210[0x10];
    ExperienceTracker *m_experienceTracker;
};

// The canonical ZH ExperienceTracker header has the wrong BFME ABI here;
// retain only this declaration-only BFME method view, without parameter names.
class ExperienceTracker {
public:
    Bool isAcceptingExperiencePoints() const;
    void addExperiencePoints(Real, Bool, Bool, Bool, Bool);
    Bool gainExpForLevel(Int, Bool, Bool);
};

struct Rva00260060Data {
    unsigned char m_00_to_254[0x254];
    Int m_word254;
    Int m_word258;
    unsigned char m_25c_to_264[0x08];
    FXList *m_fxList;
};

class Rva00260060Owner {
public:
    void update(Object *);

    void *m_vtable;
    Rva00260060Data *m_data;
};

void Rva00260060Owner::update(Object *object)
{
    Object *producer = TheBfmeGameLogic->findObjectByID(object->m_producerID);
    if (producer != 0) {
        ThingTemplate *thingTemplate = producer->getTemplate();
        if (thingTemplate != 0) {
            const Overridable *nextOverride =
                thingTemplate->getNextOverride();
            if (nextOverride != 0)
                thingTemplate = const_cast<ThingTemplate *>(
                    reinterpret_cast<const ThingTemplate *>(
                        reinterpret_cast<const BfmeControlBarOverridable *>(
                            nextOverride)->getFinalOverride()));
        }
        if ((*reinterpret_cast<const unsigned int *>(
                 reinterpret_cast<const unsigned char *>(thingTemplate) + 0xd4)
             & 0x1000u) != 0)
            goto finish;
    }

    {
        ExperienceTracker *tracker = object->m_experienceTracker;
        if (tracker == 0 || !tracker->isAcceptingExperiencePoints())
            goto finish;

        Rva00260060Data *data = m_data;
        Int experience = data->m_word258;
        if (experience > 0) {
            object->m_experienceTracker->addExperiencePoints(
                static_cast<Real>(experience), true, true, true, false);
        } else {
            object->m_experienceTracker->gainExpForLevel(
                data->m_word254, true, false);
        }

        FXList *fxList = data->m_fxList;
        if (fxList == 0)
            return;

        if (object->isKindOf(static_cast<KindOfType>(0x6c))) {
            reinterpret_cast<Rva00260060ContainView *>(object->m_contain)
                ->iterateContained(containedFXAt0025FD80, data, true);
        } else {
            FXList::doFXObj(fxList, object, 0);
        }
    }
    return;

finish:
    return;
}
