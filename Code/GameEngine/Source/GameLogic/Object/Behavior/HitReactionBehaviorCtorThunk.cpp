// cl: /DNDEBUG /MD /EHsc
// The named ModuleFactory entry reaches this constructor through its unique
// 0x28-byte allocation, fixing the two derived words.

class Thing;
class ModuleData;
class Object;
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

class HRB_DeepBase
{
public:
    HRB_DeepBase(Thing *, const ModuleData *);
    virtual ~HRB_DeepBase();

protected:
    const ModuleData *m_moduleData;
    Object *m_object;
};

class HRB_Iface1 { public: virtual void slot(); };
class HRB_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public HRB_DeepBase, public HRB_Iface1, public HRB_Iface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : HRB_DeepBase(thing, moduleData),
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

class HitReactionBehavior : public UpdateModule
{
public:
    HitReactionBehavior(Thing *, const ModuleData *);

private:
    unsigned int m_field20;
    unsigned int m_field24;
};

// ??0HitReactionBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
HitReactionBehavior::HitReactionBehavior(
    Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    m_field20 = 0;
    m_field24 = 0;
    setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}
