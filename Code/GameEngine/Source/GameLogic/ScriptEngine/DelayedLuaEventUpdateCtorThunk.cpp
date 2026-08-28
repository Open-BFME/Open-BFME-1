// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
    UPDATE_SLEEP_DUMMY
};

class DelayedLuaEventUpdateBase
{
public:
    DelayedLuaEventUpdateBase(Thing *, const ModuleData *);
    virtual ~DelayedLuaEventUpdateBase();

protected:
    void *m_f04;
    Object *m_object;
};

class DelayedLuaEventUpdateInterface1
{
public:
    virtual void slot();
};

class DelayedLuaEventUpdateInterface2
{
public:
    virtual void slot();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public DelayedLuaEventUpdateBase,
                     public DelayedLuaEventUpdateInterface1,
                     public DelayedLuaEventUpdateInterface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : DelayedLuaEventUpdateBase(thing, moduleData),
          m_nextCallFrameAndPhase(0), m_indexInLogic(-1), m_updateState(-1)
    {
    }

protected:
    void setWakeFrameViaThunk(Object *, UpdateSleepTime);
    Object *getObject() const { return m_object; }

private:
    unsigned int m_nextCallFrameAndPhase;
    int m_indexInLogic;
    int m_updateState;
};

class DelayedLuaEventList
{
public:
    DelayedLuaEventList();
    ~DelayedLuaEventList();

private:
    unsigned char m_data[0x4c];
};

class DelayedLuaEventUpdate : public UpdateModule
{
public:
    DelayedLuaEventUpdate(Thing *, const ModuleData *);

private:
    unsigned int m_f20;
    DelayedLuaEventList m_events;
    unsigned int m_f70;
    bool m_f74;
    bool m_f75;
};

// ??0DelayedLuaEventUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
DelayedLuaEventUpdate::DelayedLuaEventUpdate(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData), m_events()
{
    setWakeFrameViaThunk(getObject(), (UpdateSleepTime)0x3fffffff);
    m_f20 = 0;
    m_f70 = 0;
    m_f74 = false;
    m_f75 = false;
}
