// cl: /DNDEBUG /MD /EHsc
// ModuleFactory's 0x48-byte allocation and the adjacent RubbleRiseUpdate
// helpers fix this BFME-specific layout.

class Thing;
class ModuleData;
class Object;
enum UpdateSleepTime { UPDATE_SLEEP_FOREVER = 0x3fffffff };

class RRU_DeepBase
{
public:
    RRU_DeepBase(Thing *, const ModuleData *);
    virtual ~RRU_DeepBase();

protected:
    const ModuleData *m_moduleData;
    Object *m_object;
};

class RRU_Iface1 { public: virtual void slot(); };
class RRU_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public RRU_DeepBase, public RRU_Iface1, public RRU_Iface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : RRU_DeepBase(thing, moduleData),
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

class DieModuleInterface { public: virtual void onDie(); };

class RRU_State
{
public:
    __forceinline RRU_State()
    {
        m_field00 = 0;
        m_field08 = 0;
        m_field0c = 0;
        m_field04 = 0;
        m_field10 = 0;
        m_field14 = 0;
        m_field18 = 0;
        m_field1c = 0;
        m_field20 = 0;
    }

private:
    unsigned int m_field00;
    unsigned int m_field04;
    unsigned int m_field08;
    unsigned int m_field0c;
    unsigned int m_field10;
    unsigned int m_field14;
    unsigned int m_field18;
    unsigned int m_field1c;
    unsigned int m_field20;
};

class RubbleRiseUpdate : public UpdateModule, public DieModuleInterface
{
public:
    RubbleRiseUpdate(Thing *, const ModuleData *);

private:
    RRU_State m_state;
};

// ??0RubbleRiseUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
RubbleRiseUpdate::RubbleRiseUpdate(
    Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}
