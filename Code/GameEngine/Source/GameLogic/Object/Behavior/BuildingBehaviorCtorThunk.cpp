// cl: /DNDEBUG /MD /EHsc
// The named ModuleFactory entry reaches this constructor through its unique
// 0x24-byte allocation, fixing the two bytes of derived state.

class Thing;
class ModuleData;
class Object;
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

class BB_DeepBase
{
public:
    BB_DeepBase(Thing *, const ModuleData *);
    virtual ~BB_DeepBase();

protected:
    const ModuleData *m_moduleData;
    Object *m_object;
};

class BB_Iface1 { public: virtual void slot(); };
class BB_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public BB_DeepBase, public BB_Iface1, public BB_Iface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : BB_DeepBase(thing, moduleData),
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

class BuildingBehavior : public UpdateModule
{
public:
    BuildingBehavior(Thing *, const ModuleData *);

private:
    bool m_field20;
    bool m_field21;
};

// ??0BuildingBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
BuildingBehavior::BuildingBehavior(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    m_field20 = false;
    m_field21 = true;
    setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}
