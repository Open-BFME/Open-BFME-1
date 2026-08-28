// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME5: lift the CheckpointUpdate ICF constructor to clean C++.

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

class CP_Iface1
{
public:
    virtual void slot();
};

class CP_Iface2
{
public:
    virtual void slot();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public PB_DeepBase, public CP_Iface1, public CP_Iface2
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

class CheckpointUpdateInterface
{
public:
    virtual void slot();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CheckpointUpdate.h
class CheckpointUpdate : public UpdateModule, public CheckpointUpdateInterface
{
public:
    CheckpointUpdate(Thing *, const ModuleData *);

private:
    unsigned int m_allyNear;
    unsigned int m_enemyNear;
};

// ??0CheckpointUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
CheckpointUpdate::CheckpointUpdate(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData), m_allyNear(0), m_enemyNear(0)
{
    setWakeFrame(getObject(), (UpdateSleepTime)0x3fffffff);
}
