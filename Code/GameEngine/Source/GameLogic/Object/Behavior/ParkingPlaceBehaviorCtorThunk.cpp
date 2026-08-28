// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ivendor/stlport
// ModuleFactory reaches this body through ILT 0x0001002D. The 0x60-byte
// allocation and EA constructor source fix its compact BFME layout.

#include <vector>

class Thing;
class ModuleData;
class Object;

class PPB_DeepBase
{
public:
    PPB_DeepBase(Thing *, const ModuleData *);
    virtual ~PPB_DeepBase();

protected:
    const ModuleData *m_moduleData;
    Object *m_object;
};

class PPB_Iface1 { public: virtual void slot(); };
class PPB_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public PPB_DeepBase, public PPB_Iface1, public PPB_Iface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : PPB_DeepBase(thing, moduleData),
          m_nextCallFrameAndPhase(0), m_indexInLogic(-1), m_updateState(-1)
    {
    }

private:
    unsigned int m_nextCallFrameAndPhase;
    int m_indexInLogic;
    int m_updateState;
};

class PPB_DieInterface
{
public:
    virtual void slot();
};

class PPB_InterfaceState
{
public:
    PPB_InterfaceState() : m_state(0) {}

private:
    unsigned int m_state;
};

class PPB_Coord3D
{
public:
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ParkingPlaceBehavior.h
class ParkingPlaceBehavior : public UpdateModule,
                             public PPB_DieInterface,
                             public PPB_InterfaceState
{
public:
    ParkingPlaceBehavior(Thing *, const ModuleData *);
    virtual ~ParkingPlaceBehavior();

private:
    std::vector<unsigned int> m_spaces;
    std::vector<unsigned int> m_runways;
    std::vector<unsigned int> m_healing;
    float m_field4c;
    float m_field50;
    PPB_Coord3D m_rallyPoint;
};

// ??0ParkingPlaceBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
ParkingPlaceBehavior::ParkingPlaceBehavior(
    Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    m_rallyPoint.zero();
    m_field4c = 1.0f;
    m_field50 = 1.0f;
}
