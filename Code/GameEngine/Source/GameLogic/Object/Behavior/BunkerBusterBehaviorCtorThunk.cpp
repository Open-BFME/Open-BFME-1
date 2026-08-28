// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
    UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class PB_DeepBase
{
public:
    PB_DeepBase(Thing *, const ModuleData *);
    virtual ~PB_DeepBase();

protected:
    void *m_f04;
    Object *m_object;
};

class PB_Iface1
{
public:
    virtual void slot();
};

class PB_Iface2
{
public:
    virtual void slot();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public PB_DeepBase, public PB_Iface1, public PB_Iface2
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

class BunkerBusterBehaviorIface
{
public:
    virtual void slot();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BunkerBusterBehavior.h
class BunkerBusterBehavior : public UpdateModule,
    public BunkerBusterBehaviorIface
{
public:
    BunkerBusterBehavior(Thing *, const ModuleData *);

private:
    void *m_upgradeRequired;
    unsigned int m_victimID;
};

// ??0BunkerBusterBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
BunkerBusterBehavior::BunkerBusterBehavior(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData), m_upgradeRequired(0), m_victimID(0)
{
    setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}
