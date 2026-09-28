// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: RampageBehavior module ctor and its UpdateModule update, reached
// through secondary vtable 0x010A5954 slot 0.

#include "ascii_string.h"

typedef bool Bool;
typedef float Real;

struct Coord3D
{
    Real x;
    Real y;
    Real z;
};
#define BFME_HAVE_COORD3D

class UpgradeTemplate;
class Drawable;
class CountermeasuresBehaviorInterface;

class ModuleData;

enum UpdateSleepTime
{
    UPDATE_SLEEP_NONE = 1,
    UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum CommandSourceType
{
    CMD_FROM_AI = 2
};

enum ObjectPrivateStatusBits
{
    EFFECTIVELY_DEAD = 0x01
};

#define OBJECT_TU_MEMBERS \
    Bool hasUpgrade(const UpgradeTemplate *upgrade) const; \
    Int bfmeHasSignificantPreferredLocomotorHeight() const; \
    void notifyModelConditionChanged(); \
    CountermeasuresBehaviorInterface *getCountermeasuresBehaviorInterface();
#include "../object.h"
#undef OBJECT_TU_MEMBERS

class UpgradeCenter
{
public:
    const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

extern UpgradeCenter *TheUpgradeCenter;

template <class T>
inline const T &maxRef(const T &left, const T &right)
{
    return right > left ? right : left;
}

struct RampageUpgradeRange
{
    AsciiString *m_begin;
    AsciiString *m_end;
};

class RampageBehaviorModuleData
{
private:
    UnsignedByte m_pad00[8];

public:
    RampageUpgradeRange m_upgrades;
    UnsignedInt m_pad10;
    Real m_threshold;
    Int m_frames18;
    Int m_frames1c;
    Int m_condition20;
};

class BodyModuleInterface
{
public:
    virtual void slot00();
    virtual void slot04() = 0;
    virtual void slot08() = 0;
    virtual void slot0c() = 0;
    virtual Real getHealth() const = 0;
    virtual void slot14() = 0;
    virtual Real getMaxHealth() const = 0;
};

class AICommandInterface
{
public:
    virtual void slot00();
    void aiIdle(CommandSourceType source);
    void aiAttackPosition(const Coord3D *position, Int maxShots,
        CommandSourceType source);
};

class AIUpdateInterface
{
private:
    UnsignedByte m_pad00[0x20];

public:
    AICommandInterface m_commands;
};

class CountermeasuresBehaviorInterface
{
public:
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08(Int value) = 0;
};

class Drawable
{
    friend class RampageBehavior;

private:
    void applyPendingModelConditionFlags(Bool immediate);
};

class Rva00203DB0Owner
{
public:
    UnsignedByte ready() const;
};

class Rva001BEF20FieldAddress
{
public:
    char *get();
};

class Gen001C9A10
{
public:
    void handle(Int player);
};

class Gen001C9AC0
{
public:
    void handle(Int player);
};

class BfmeRvaAIView
{
public:
    void setHeldState(Int value, Int source);
};

static void setModelConditionState(Object *object, Int bit)
{
    if ((object->m_modelConditionFlags[bit >> 5] & (1u << (bit & 31))) == 0)
    {
        object->m_modelConditionFlags[bit >> 5] |= 1u << (bit & 31);
        object->notifyModelConditionChanged();
    }
}

class PB_DeepBase
{
public:
    PB_DeepBase(Thing *, const ModuleData *);
    virtual ~PB_DeepBase();

protected:
    void *m_p4;
    Object *m_object;
};

class RampageBehaviorIface1 { public: virtual void slot(); };
class RampageBehaviorIface2 { public: virtual UpdateSleepTime update() = 0; };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public PB_DeepBase, public RampageBehaviorIface1,
    public RampageBehaviorIface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : PB_DeepBase(thing, moduleData), m_f14(0), m_f18(-1), m_f1c(-1) {}

protected:
    void setWakeFrame(Object *, UpdateSleepTime);
    Object *getObject() const { return m_object; }

private:
    unsigned int m_f14;
    int m_f18;
    int m_f1c;
};

class RampageBehavior : public UpdateModule
{
public:
    RampageBehavior(Thing *, const ModuleData *);
    virtual UpdateSleepTime update();

protected:
    const RampageBehaviorModuleData *getRampageBehaviorModuleData() const
        { return static_cast<const RampageBehaviorModuleData *>(m_p4); }

private:
    Real m_healthRatio;
    Int m_rampageFrames;
    Int m_countdownFrames;
};

// ??0RampageBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
RampageBehavior::RampageBehavior(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    m_rampageFrames = 0;
    m_countdownFrames = 0;
    m_healthRatio = 99999.0f;
    setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}

// ?update@RampageBehavior@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime RampageBehavior::update()
{
    Object *object = getObject();
    AIUpdateInterface *ai = object->m_ai;
    BodyModuleInterface *body = object->m_body;
    Drawable *drawable = object->getDrawable();

    if (body == 0 || ai == 0 || drawable == 0)
        return UPDATE_SLEEP_FOREVER;

    const RampageBehaviorModuleData *data = getRampageBehaviorModuleData();
    const AsciiString *upgrade = data->m_upgrades.m_begin;
    while (upgrade != data->m_upgrades.m_end)
    {
        const UpgradeTemplate *upgradeTemplate =
            TheUpgradeCenter->findUpgrade(*upgrade);
        if (!object->hasUpgrade(upgradeTemplate))
            return UPDATE_SLEEP_NONE;
        ++upgrade;
    }

    Real health = body->getHealth();
    Real maxHealth = body->getMaxHealth();
    const Real healthRatio = health / maxRef(maxHealth, 1.0f);

    if (m_rampageFrames > 0)
    {
        if (--m_rampageFrames <= 0 || (object->m_privateStatus & EFFECTIVELY_DEAD) != 0 ||
            (UnsignedByte)object->bfmeHasSignificantPreferredLocomotorHeight() != 0)
        {
            UnsignedInt weaponFlags = *reinterpret_cast<UnsignedInt *>(
                reinterpret_cast<Rva001BEF20FieldAddress *>(object)->get());
            if ((weaponFlags & 0x100) != 0)
                reinterpret_cast<Gen001C9AC0 *>(object)->handle(8);

            if ((object->m_privateStatus & EFFECTIVELY_DEAD) == 0 &&
                (UnsignedByte)object->bfmeHasSignificantPreferredLocomotorHeight() == 0)
            {
                ai->m_commands.aiIdle(CMD_FROM_AI);
            }

            m_countdownFrames = data->m_condition20;
            m_rampageFrames = 0;

            if ((object->m_modelConditionFlags[4] & 0x01000000) != 0)
            {
                object->m_modelConditionFlags[4] &= 0xfeffffff;
                object->notifyModelConditionChanged();
            }
            drawable->applyPendingModelConditionFlags(false);
        }
    }
    else if (healthRatio < data->m_threshold && (object->m_privateStatus & EFFECTIVELY_DEAD) == 0 &&
        (*reinterpret_cast<UnsignedInt *>(
            reinterpret_cast<Rva001BEF20FieldAddress *>(object)->get()) & 0x100) == 0 &&
        health < m_healthRatio && m_countdownFrames == 0)
    {
        if (reinterpret_cast<const Rva00203DB0Owner *>(
                static_cast<PB_DeepBase *>(this))->ready())
        {
            reinterpret_cast<Gen001C9AC0 *>(object)->handle(7);
            reinterpret_cast<Gen001C9A10 *>(object)->handle(8);
            ai->m_commands.aiAttackPosition(&object->m_cachedPos,
                0x0ffffffe, CMD_FROM_AI);
            m_rampageFrames = data->m_frames18;
        }
        else
        {
            setModelConditionState(object, 152);
            reinterpret_cast<BfmeRvaAIView *>(&ai->m_commands)->setHeldState(0, CMD_FROM_AI);
            m_rampageFrames = data->m_frames1c;
        }

        if ((object->m_modelConditionFlags[4] & 0x00400000) != 0)
        {
            object->m_modelConditionFlags[4] &= 0xffbfffff;
            object->notifyModelConditionChanged();
        }
        if ((UnsignedByte)object->m_modelConditionFlags[5] & 4)
        {
            object->m_modelConditionFlags[5] &= ~4;
            object->notifyModelConditionChanged();
        }
        if ((UnsignedByte)object->m_modelConditionFlags[5] & 8)
        {
            object->m_modelConditionFlags[5] &= ~8;
            object->notifyModelConditionChanged();
        }
        if ((UnsignedByte)object->m_modelConditionFlags[5] & 0x10)
        {
            object->m_modelConditionFlags[5] &= ~0x10;
            object->notifyModelConditionChanged();
        }
        if ((UnsignedByte)object->m_modelConditionFlags[5] & 0x20)
        {
            object->m_modelConditionFlags[5] &= ~0x20;
            object->notifyModelConditionChanged();
        }

        CountermeasuresBehaviorInterface *countermeasures =
            object->getCountermeasuresBehaviorInterface();
        if (countermeasures != 0)
            countermeasures->slot08(0);

        drawable->applyPendingModelConditionFlags(false);
    }

    if (m_countdownFrames > 0 && --m_countdownFrames <= 0)
        m_healthRatio = health;

    return UPDATE_SLEEP_NONE;
}
