// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: RampageBehavior module ctor.

class Thing;
class ModuleData;
class Object;
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

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
class RampageBehaviorIface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
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

private:
    float m_f20;
    unsigned int m_f24;
    unsigned int m_f28;
};

// ??0RampageBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
RampageBehavior::RampageBehavior(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    m_f24 = 0;
    m_f28 = 0;
    m_f20 = 99999.0f;
    setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}
