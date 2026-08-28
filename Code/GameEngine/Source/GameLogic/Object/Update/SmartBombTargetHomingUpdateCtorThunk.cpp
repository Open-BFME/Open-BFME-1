// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift the SmartBombTargetHomingUpdate constructor to clean C++.

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

class SmartBombTargetHomingUpdateIface
{
public:
    virtual void slot();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SmartBombTargetHomingUpdate.h
class SmartBombTargetHomingUpdate : public UpdateModule,
    public SmartBombTargetHomingUpdateIface
{
public:
    SmartBombTargetHomingUpdate(Thing *, const ModuleData *);

private:
    unsigned int m_targetX;
    unsigned int m_targetY;
    unsigned int m_targetZ;
};

// ??0SmartBombTargetHomingUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
SmartBombTargetHomingUpdate::SmartBombTargetHomingUpdate(
    Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData), m_targetX(0), m_targetY(0), m_targetZ(0)
{
    setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}
