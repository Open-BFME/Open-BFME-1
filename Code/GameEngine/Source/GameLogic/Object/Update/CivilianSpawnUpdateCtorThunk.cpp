// cl: /DNDEBUG /MD /EHsc

class Thing;
class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
private:
    unsigned char m_pad[8];

public:
    unsigned int m_spawnDelay;
};

int __cdecl GetGameLogicRandomValue(int, int, char *, int);

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
    const ModuleData *m_moduleData;
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
        : PB_DeepBase(thing, moduleData),
          m_nextCallFrameAndPhase(0),
          m_indexInLogic(-1),
          m_indexInUpdate(-1)
    {
    }

protected:
    unsigned int m_nextCallFrameAndPhase;
    int m_indexInLogic;
    int m_indexInUpdate;
};

class CivilianSpawnUpdate : public UpdateModule
{
public:
    CivilianSpawnUpdate(Thing *, const ModuleData *);

private:
    unsigned int m_spawnFrame;
};

// ??0CivilianSpawnUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
CivilianSpawnUpdate::CivilianSpawnUpdate(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData), m_spawnFrame(0)
{
    m_spawnFrame = GetGameLogicRandomValue(
        m_moduleData->m_spawnDelay / 2,
        m_moduleData->m_spawnDelay,
        "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\CivilianSpawnUpdate.cpp",
        61);
}
