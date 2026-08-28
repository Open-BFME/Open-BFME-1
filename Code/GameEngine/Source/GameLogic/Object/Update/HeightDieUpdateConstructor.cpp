// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// EA's Generals source supplies the member semantics; BFME's ModuleFactory
// allocation proves that the same layout ends at 0x34 here.

class Thing;
class ModuleData;

class HDU_DeepBase
{
public:
    HDU_DeepBase(Thing *, const ModuleData *);
    virtual ~HDU_DeepBase();

protected:
    const ModuleData *m_moduleData;
    void *m_object;
};

class HDU_Iface1 { public: virtual void slot(); };
class HDU_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public HDU_DeepBase, public HDU_Iface1, public HDU_Iface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : HDU_DeepBase(thing, moduleData),
          m_indexInLogic(-1), m_updateState(-1),
          m_nextCallFrameAndPhase(0)
    {
    }

private:
    unsigned int m_nextCallFrameAndPhase;
    int m_indexInLogic;
    int m_updateState;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
    float x;
    float y;
    float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HeightDieUpdate.h
class HeightDieUpdate : public UpdateModule
{
public:
    HeightDieUpdate(Thing *, const ModuleData *);

private:
    bool m_hasDied;
    bool m_particlesDestroyed;
    Coord3D m_lastPosition;
    unsigned int m_earliestDeathFrame;
};

// ??0HeightDieUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
HeightDieUpdate::HeightDieUpdate(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    m_hasDied = false;
    m_particlesDestroyed = false;
    m_lastPosition.x = -1.0f;
    m_lastPosition.y = -1.0f;
    m_lastPosition.z = -1.0f;
    m_earliestDeathFrame = (unsigned int)-1;
}
