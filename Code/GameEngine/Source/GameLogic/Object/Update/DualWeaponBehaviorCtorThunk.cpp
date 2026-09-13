// cl: /DNDEBUG /MD /EHsc
// The named ModuleFactory entry reaches this constructor through its unique
// 0x28-byte allocation, fixing the compact derived state.

class Thing;
class ModuleData;
class Object;
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

class DWB_DeepBase
{
public:
    DWB_DeepBase(Thing *, const ModuleData *);
    virtual ~DWB_DeepBase();

protected:
    const ModuleData *m_moduleData;
    Object *m_object;
};

class DWB_Iface1 { public: virtual void slot(); };
class DWB_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public DWB_DeepBase, public DWB_Iface1, public DWB_Iface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : DWB_DeepBase(thing, moduleData),
          m_indexInLogic(-1), m_updateState(-1),
          m_nextCallFrameAndPhase(0)
    {
    }

protected:
    void setWakeFrame(Object *, UpdateSleepTime);
    Object *getObject() const { return m_object; }

private:
    unsigned int m_nextCallFrameAndPhase;
    int m_indexInLogic;
    int m_updateState;
};

class DualWeaponBehavior : public UpdateModule
{
public:
    DualWeaponBehavior(Thing *, const ModuleData *);

private:
    bool m_field20;
    unsigned int m_field24;
};

// ??0DualWeaponBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
DualWeaponBehavior::DualWeaponBehavior(
    Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    m_field20 = false;
    m_field24 = 0;
    setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}
