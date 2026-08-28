// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ivendor/stlport
// ModuleFactory reaches this body through the named BoneFXUpdate constructor
// ILT at 0x0000264E, whose jump target is the retail body at 0x00288C50.

#include <vector>

class Thing;
class ModuleData;
class Object;

enum ParticleSystemID
{
    INVALID_PARTICLE_SYSTEM_ID = 0
};

class BFU_DeepBase
{
public:
    BFU_DeepBase(Thing *, const ModuleData *);
    virtual ~BFU_DeepBase();

protected:
    const ModuleData *m_moduleData;
    Object *m_object;
};

class BFU_Iface1 { public: virtual void slot(); };
class BFU_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public BFU_DeepBase, public BFU_Iface1, public BFU_Iface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : BFU_DeepBase(thing, moduleData),
          m_nextCallFrameAndPhase(0), m_indexInLogic(-1), m_updateState(-1)
    {
    }

private:
    unsigned int m_nextCallFrameAndPhase;
    int m_indexInLogic;
    int m_updateState;
};

class BFU_Coord3D
{
public:
    BFU_Coord3D();
    ~BFU_Coord3D();

    void zero()
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }

private:
    float x;
    float y;
    float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BoneFXUpdate.h
class BoneFXUpdate : public UpdateModule
{
public:
    BoneFXUpdate(Thing *, const ModuleData *);
    virtual ~BoneFXUpdate();

private:
    std::vector<ParticleSystemID> m_particleSystemIDs;
    int m_nextFXFrame[4][8];
    int m_nextOCLFrame[4][8];
    int m_nextParticleSystemFrame[4][8];
    BFU_Coord3D m_FXBonePositions[4][8];
    BFU_Coord3D m_OCLBonePositions[4][8];
    BFU_Coord3D m_PSBonePositions[4][8];
    int m_curBodyState;
    bool m_bonesResolved[4];
    bool m_active;
};

// ??0BoneFXUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
BoneFXUpdate::BoneFXUpdate(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            m_nextFXFrame[i][j] = -1;
            m_nextOCLFrame[i][j] = -1;
            m_nextParticleSystemFrame[i][j] = -1;
            m_FXBonePositions[i][j].zero();
            m_OCLBonePositions[i][j].zero();
            m_PSBonePositions[i][j].zero();
        }
        m_bonesResolved[i] = false;
    }
    m_particleSystemIDs.clear();
    m_active = false;
    m_curBodyState = 0;
}
