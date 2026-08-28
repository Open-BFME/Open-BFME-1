// cl: /DNDEBUG /MD /EHsc
// The named ModuleFactory entry reaches this constructor through its unique
// 0x20-byte allocation, leaving no derived state beyond UpdateModule.

class Thing;
class ModuleData;
class Object;
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

class SESU_DeepBase
{
public:
    SESU_DeepBase(Thing *, const ModuleData *);
    virtual ~SESU_DeepBase();

protected:
    const ModuleData *m_moduleData;
    Object *m_object;
};

class SESU_Iface1 { public: virtual void slot(); };
class SESU_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public SESU_DeepBase, public SESU_Iface1, public SESU_Iface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : SESU_DeepBase(thing, moduleData),
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

class SpecialEnemySenseUpdate : public UpdateModule
{
public:
    SpecialEnemySenseUpdate(Thing *, const ModuleData *);
};

// ??0SpecialEnemySenseUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
SpecialEnemySenseUpdate::SpecialEnemySenseUpdate(
    Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}
