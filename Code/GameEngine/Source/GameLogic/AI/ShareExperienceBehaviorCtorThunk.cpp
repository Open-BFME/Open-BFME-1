// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
    UPDATE_SLEEP_DUMMY
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

class ShareExperienceBehaviorIface1
{
public:
    virtual void slot();
};

class ShareExperienceBehaviorIface2
{
public:
    virtual void slot();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public PB_DeepBase,
    public ShareExperienceBehaviorIface1,
    public ShareExperienceBehaviorIface2
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

class ShareExperienceBehaviorInterface
{
public:
    virtual void slot();
};

class ShareExperienceBehavior : public UpdateModule,
    public ShareExperienceBehaviorInterface
{
public:
    ShareExperienceBehavior(Thing *, const ModuleData *);
};

// ??0ShareExperienceBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
ShareExperienceBehavior::ShareExperienceBehavior(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    setWakeFrame(getObject(), (UpdateSleepTime)0x3fffffff);
}
