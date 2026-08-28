// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SlaveWatcherBehavior module ctor.

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

class SlaveWatcherBehaviorIface1 { public: virtual void slot(); };
class SlaveWatcherBehaviorIface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public PB_DeepBase, public SlaveWatcherBehaviorIface1,
    public SlaveWatcherBehaviorIface2
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

class SlaveWatcherBehavior : public UpdateModule
{
public:
    SlaveWatcherBehavior(Thing *, const ModuleData *);

private:
    unsigned int m_f20;
};

// ??0SlaveWatcherBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
SlaveWatcherBehavior::SlaveWatcherBehavior(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData), m_f20(0)
{
    setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}
