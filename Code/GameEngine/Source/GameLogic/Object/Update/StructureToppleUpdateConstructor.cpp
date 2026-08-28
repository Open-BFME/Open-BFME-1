// cl: /DNDEBUG /MD /EHsc
// readable body of ??0StructureToppleUpdate@@QAE@PAVThing@@PBVModuleData@@@Z: Code/GameEngine/Source/GameLogic/Object/Update/StructureToppleUpdate.cpp

class Thing;
class ModuleData;
class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord2D
{
    float x;
    float y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
    float x;
    float y;
    float z;

    void zero()
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Geometry.h
class GeometryInfo
{
public:
    float getMaxHeightAbovePosition() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
    const GeometryInfo& getGeometryInfo() const
    {
        return *(const GeometryInfo *)((const char *)this + 0xAC);
    }
};

enum UpdateSleepTime
{
    UPDATE_SLEEP_FOREVER = 0x3fffffff
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

class PB_Iface1 { public: virtual void slot(); };
class PB_Iface2 { public: virtual void slot(); };

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

class StructureToppleUpdateIface
{
public:
    virtual void slot();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StructureToppleUpdate.h
class StructureToppleUpdate : public UpdateModule,
    public StructureToppleUpdateIface
{
public:
    StructureToppleUpdate(Thing *, const ModuleData *);

private:
    unsigned int m_toppleFrame;
    Coord2D m_toppleDirection;
    int m_toppleState;
    float m_toppleVelocity;
    float m_accumulatedAngle;
    float m_structuralIntegrity;
    float m_lastCrushedLocation;
    int m_nextBurstFrame;
    Coord3D m_delayBurstLocation;
    float m_buildingHeight;
};

// ??0StructureToppleUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
StructureToppleUpdate::StructureToppleUpdate(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    m_delayBurstLocation.zero();
    m_structuralIntegrity = 0.0f;
    m_toppleDirection.x = m_toppleDirection.y = 0;
    m_toppleFrame = 0;
    m_toppleState = 0;
    m_toppleVelocity = 0.0f;
    m_accumulatedAngle = 0.001f;
    m_lastCrushedLocation = 0.0f;
    m_nextBurstFrame = -1;
    setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
    Object *building = getObject();
    m_buildingHeight = building->getGeometryInfo().getMaxHeightAbovePosition();
}
