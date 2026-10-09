// ?rva001FE970@GettingBuiltBehavior@@QAEXXZ
// partial score=0.9528 date=2026-10-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
#define OBJECT_TU_MEMBERS bool bfmeGetRecentDamageSource(unsigned int *, unsigned int) const;
#include "../../../../game/GameEngine/Source/GameLogic/Object/object.h"
#include "../../../../game/Libraries/Source/WWVegas/WWLib/ascii_string.h"

template <typename T>
__forceinline bool StringBase<T>::isEmpty() const
{
    return !m_data || m_data->length == 0;
}

class GameLogic { public: Object *findObjectByID(int); };
extern GameLogic *TheGameLogic;
class Module;
Module *rva0036BB10FindCastleMemberBehavior(const Object *);
extern void j_0004b015();
class Rva0004B015Carrier { };

class BodyModuleInterface
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual float slot10();
    virtual void slot14();
    virtual float slot18();
};

struct Rva0036BB10ModuleView
{
    char m_pad00[0x14];
    unsigned int m_field14;
    char m_pad18[0xc];
    bool m_field24;
};

struct GettingBuiltBehaviorModuleData
{
    char m_pad00[0x14];
    AsciiString m_workerName;
    char m_pad18[0x14];
    bool m_field2c;
};

class GettingBuiltBehaviorSecondaryInterface
{
public:
    virtual void slot00();
    virtual void slot04(bool);
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual bool slot14();
};

class GettingBuiltBehavior
{
public:
    void *m_vptr;
    const GettingBuiltBehaviorModuleData *m_moduleData;
    Object *m_object;
    char m_pad0c[0x14];
    GettingBuiltBehaviorSecondaryInterface m_secondary;
    unsigned int m_audioHandle;
    float m_field28;
    unsigned int m_field2c;
    bool m_field30, m_field31, m_field32, m_field33, m_field34, m_field35, m_field36;
    void rva001FE970();
};

// ?rva001FE970@GettingBuiltBehavior@@QAEXXZ
void GettingBuiltBehavior::rva001FE970()
{
    Object *object = m_object;
    const GettingBuiltBehaviorModuleData *data = m_moduleData;
    BodyModuleInterface *body = object->m_body;
    if (!body || ((object->m_privateStatus & 1) && !data->m_field2c))
        return;
    // Retail reuses the dead health temporary for the damage-source output.
    union { float health; unsigned int source; } temporary;
    temporary.health = body->slot10();
    if (!(body->slot18() > temporary.health))
        return;
    typedef bool (Rva0004B015Carrier::*AvailableFn)() const;
    union { void (*fn)(); AvailableFn call; } available = { j_0004b015 };
    Module *module = rva0036BB10FindCastleMemberBehavior(m_object);
    Rva0036BB10ModuleView *view = (Rva0036BB10ModuleView *)module;
    if (module && view->m_field14 && !view->m_field24 && ((Rva0004B015Carrier *)module->*available.call)())
        return;
    temporary.source = 0;
    bool recent;
    if (m_field35 || !object->bfmeGetRecentDamageSource(&temporary.source, 4))
        recent = false;
    else
        recent = true;
    if (data->m_workerName.isEmpty())
    {
        if (!recent && !m_secondary.slot14() && !(m_field28 < 0.0f))
            m_secondary.slot04(1);
    }
    else
    {
        Object *builder = TheGameLogic->findObjectByID(object->m_builderID);
        if (!builder || (builder->m_privateStatus & 1))
        {
            if (m_field28 > 0.0f && !recent)
                m_field28 -= 1.0f;
            if (m_field28 <= 0.0f)
                m_secondary.slot04(1);
        }
    }
}
