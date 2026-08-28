// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class PB_DeepBase
{
public:
    PB_DeepBase(Thing *, const ModuleData *);
    virtual ~PB_DeepBase();

private:
    void *m_unmodelled04;
    void *m_unmodelled08;
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
        : PB_DeepBase(thing, moduleData), m_nextCallFrame(0), m_moduleIndex(-1), m_wakeFrame(-1)
    {
    }

private:
    unsigned int m_nextCallFrame;
    int m_moduleIndex;
    int m_wakeFrame;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class SlavedUpdateInterface
{
public:
    virtual void slot();
};

struct SlavedGuardPointOffset
{
    SlavedGuardPointOffset() : x(0), y(0), z(0) {}

    unsigned int x;
    unsigned int y;
    unsigned int z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SlavedUpdate.h
class SlavedUpdate : public UpdateModule, public SlavedUpdateInterface
{
public:
    SlavedUpdate(Thing *, const ModuleData *);

private:
    unsigned int m_slaver;
    SlavedGuardPointOffset m_guardPointOffset;
    int m_framesToWait;
    int m_repairState;
    bool m_repairing;
    unsigned int m_unmodelled40;
};

// ??0SlavedUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
SlavedUpdate::SlavedUpdate(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData),
      m_slaver(0),
      m_guardPointOffset(),
      m_framesToWait(0),
      m_repairState(0),
      m_repairing(false),
      m_unmodelled40(0)
{
}
