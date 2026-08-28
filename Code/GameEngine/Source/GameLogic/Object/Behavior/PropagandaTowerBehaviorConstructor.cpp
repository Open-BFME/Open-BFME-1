// cl: /DNDEBUG /MD /EHsc
// readable body of ??0PropagandaTowerBehavior@@: Code/GameEngine/Source/GameLogic/Object/Behavior/PropagandaTowerBehavior.cpp

// The retail BFME UpdateModule prefix has three interface vptrs before the
// PropagandaTowerBehavior interface.  Keep that verified view local to this
// constructor; the shared ZH declaration has a different base layout.
class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
    UPDATE_SLEEP_NONE = 1
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

class PB_Iface1 { public: virtual void slot(); };
class PB_Iface2 { public: virtual void slot(); };

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

class PropagandaTowerBehaviorIface
{
public:
    virtual void slot();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PropagandaTowerBehavior.h
class PropagandaTowerBehavior : public UpdateModule,
    public PropagandaTowerBehaviorIface
{
public:
    PropagandaTowerBehavior(Thing *, const ModuleData *);

private:
    unsigned int m_lastScanFrame;
    void *m_insideList;
    const void *m_upgradeRequired;
};

// ??0PropagandaTowerBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
PropagandaTowerBehavior::PropagandaTowerBehavior(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData),
      m_lastScanFrame(0),
      m_insideList(0),
      m_upgradeRequired(0)
{
    setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}
