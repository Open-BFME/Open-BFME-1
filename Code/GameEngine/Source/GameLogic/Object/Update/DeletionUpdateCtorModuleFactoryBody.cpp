// cl: /DNDEBUG /MD /EHsc
// ModuleFactory reaches this constructor body through ILT 0x00016C52. The
// explicit retail layout keeps this per-TU copy independent of the reference
// header's Zero Hour offsets.

class Thing;
class ModuleData;
class Object;
enum UpdateSleepTime { UPDATE_SLEEP_DUMMY };

int GetGameLogicRandomValue(int, int, char *, int);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
    unsigned int getFrame() const { return m_frame; }

private:
    unsigned char m_pad[0x3c];
    unsigned int m_frame;
};

extern GameLogic *TheGameLogic;

class DU_DeepBase
{
public:
    DU_DeepBase(Thing *, const ModuleData *);
    virtual ~DU_DeepBase();

protected:
    const ModuleData *m_moduleData;
    Object *m_object;
};

class DU_Iface1 { public: virtual void slot(); };
class DU_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public DU_DeepBase, public DU_Iface1, public DU_Iface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : DU_DeepBase(thing, moduleData), m_f14(0), m_f18(-1), m_f1c(-1) {}

protected:
    void setWakeFrame(Object *, UpdateSleepTime);
    Object *getObject() const { return m_object; }
    const ModuleData *getModuleData() const { return m_moduleData; }

private:
    unsigned int m_f14;
    int m_f18;
    int m_f1c;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DeletionUpdate.h
class DeletionUpdateModuleData
{
private:
    unsigned char m_pad[8];

public:
    unsigned int m_minFrames;
    unsigned int m_maxFrames;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DeletionUpdate.h
class DeletionUpdate : public UpdateModule
{
public:
    DeletionUpdate(Thing *, const ModuleData *);

private:
    __forceinline unsigned int calcSleepDelay(unsigned int minFrames,
                                               unsigned int maxFrames);
    unsigned int m_dieFrame;
};

__forceinline unsigned int DeletionUpdate::calcSleepDelay(
    unsigned int minFrames, unsigned int maxFrames)
{
    unsigned int delay = GetGameLogicRandomValue(
        minFrames, maxFrames,
        "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\DeletionUpdate.cpp",
        55);
    if (delay < 1)
        delay = 1;
    m_dieFrame = TheGameLogic->getFrame() + delay;
    return delay;
}

// ??0DeletionUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
DeletionUpdate::DeletionUpdate(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData), m_dieFrame(0)
{
    const DeletionUpdateModuleData *data =
        (const DeletionUpdateModuleData *)getModuleData();
    unsigned int delay = calcSleepDelay(data->m_minFrames, data->m_maxFrames);
    setWakeFrame(getObject(), (UpdateSleepTime)delay);
}
