// cl: /DNDEBUG /MD /EHsc

typedef unsigned int UnsignedInt;
typedef bool Bool;

class ModuleData;
enum UpdateSleepTime { UPDATE_SLEEP_DUMMY };
enum KindOfType { KINDOF_HULK = 81 };

int GetGameLogicRandomValue(int, int, char *, int);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
    UnsignedInt getFrame() const { return m_frame; }
    int getHulkMaxLifetimeOverride() const { return m_hulkMaxLifetimeOverride; }

private:
    unsigned char m_pad00[0x3c];
    UnsignedInt m_frame;
    unsigned char m_pad40[0x58];
    int m_hulkMaxLifetimeOverride;
};

extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
    virtual ~Overridable();
    const Overridable *getFinalOverride() const
    {
        if (m_nextOverride != 0)
            return m_nextOverride->getFinalOverride();
        return this;
    }

private:
    Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
    Bool isKindOf(KindOfType kind) const
    {
        return (m_kindOf[(UnsignedInt)kind >> 5]
                & (1U << ((UnsignedInt)kind & 31))) != 0;
    }

private:
    unsigned char m_pad08[0xc0];
    UnsignedInt m_kindOf[3];
};

template <class T> class OVERRIDE
{
public:
    const T *operator*() const
    {
        if (m_overridable == 0)
            return 0;
        return (const T *)m_overridable->getFinalOverride();
    }

    operator const T *() const { return operator*(); }

private:
    const T *m_overridable;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
    virtual ~Thing();

    const ThingTemplate *getTemplate() const
    {
        return m_template;
    }

    Bool isKindOf(KindOfType kind) const
    {
        return getTemplate()->isKindOf(kind);
    }

private:
    OVERRIDE<ThingTemplate> m_template;
};

class Object : public Thing {};

class LU_DeepBase
{
public:
    LU_DeepBase(Thing *, const ModuleData *);
    virtual ~LU_DeepBase();

protected:
    const ModuleData *m_moduleData;
    Object *m_object;
};

class LU_Iface1 { public: virtual void slot(); };
class LU_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public LU_DeepBase, public LU_Iface1, public LU_Iface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : LU_DeepBase(thing, moduleData),
          m_nextCallFrameAndPhase(0), m_indexInLogic(-1), m_updateState(-1)
    {
    }

protected:
    void setWakeFrame(Object *, UpdateSleepTime);
    Object *getObject() const { return m_object; }
    const ModuleData *getModuleData() const { return m_moduleData; }

private:
    UnsignedInt m_nextCallFrameAndPhase;
    int m_indexInLogic;
    int m_updateState;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/LifetimeUpdate.h
class LifetimeUpdateModuleData
{
private:
    unsigned char m_pad00[8];

public:
    UnsignedInt m_minFrames;
    UnsignedInt m_maxFrames;
    bool m_startDisabled;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/LifetimeUpdate.h
class LifetimeUpdate : public UpdateModule
{
public:
    LifetimeUpdate(Thing *, const ModuleData *);

private:
    UnsignedInt calcSleepDelay(UnsignedInt, UnsignedInt);
    __forceinline UnsignedInt calcSleepDelayInline(UnsignedInt, UnsignedInt);
    UnsignedInt m_dieFrame;
    UnsignedInt m_birthFrame;
};

// ?calcSleepDelayInline@LifetimeUpdate@@ absent-from-retail
__forceinline UnsignedInt LifetimeUpdate::calcSleepDelayInline(
    UnsignedInt minFrames, UnsignedInt maxFrames)
{
    UnsignedInt delay = GetGameLogicRandomValue(
        minFrames, maxFrames,
        "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\LifetimeUpdate.cpp",
        116);
    if (delay < 1)
        delay = 1;

    UnsignedInt frame = TheGameLogic->getFrame();
    m_birthFrame = frame;
    m_dieFrame = frame + delay;
    return delay;
}

// ??0LifetimeUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
LifetimeUpdate::LifetimeUpdate(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData), m_dieFrame(0), m_birthFrame(0)
{
    const LifetimeUpdateModuleData *data =
        (const LifetimeUpdateModuleData *)getModuleData();

    UnsignedInt delay;
    if (data->m_startDisabled == true)
    {
        setWakeFrame(getObject(), (UpdateSleepTime)0x3fffffff);
    }
    else
    {
        if (getObject()->isKindOf(KINDOF_HULK)
            && TheGameLogic->getHulkMaxLifetimeOverride() != -1)
            delay = calcSleepDelay(TheGameLogic->getHulkMaxLifetimeOverride(),
                                   TheGameLogic->getHulkMaxLifetimeOverride());
        else
            delay = calcSleepDelayInline(data->m_minFrames, data->m_maxFrames);

        setWakeFrame(getObject(), (UpdateSleepTime)delay);
    }
}
