// ?doScoutLogic@SlavedUpdate@@QAEXPBUCoord3D@@@Z
// partial score=0.82 date=2026-09-11
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// BFME SlavedUpdate scout movement, ported from the Zero Hour twin.

typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;
typedef bool Bool;

extern "C" double sqrt(double value);
#pragma intrinsic(sqrt)

template <typename NUM>
inline NUM sqr(NUM value)
{
    return value * value;
}

struct Coord3D
{
    Real x;
    Real y;
    Real z;

    void add(const Coord3D *other)
    {
        x += other->x;
        y += other->y;
        z += other->z;
    }

    void zero()
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }

    void sub(const Coord3D *other)
    {
        x -= other->x;
        y -= other->y;
        z -= other->z;
    }

    void set(const Coord3D *other)
    {
        x = other->x;
        y = other->y;
        z = other->z;
    }

    void scale(Real scale)
    {
        x *= scale;
        y *= scale;
        z *= scale;
    }

    void normalize();
};

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);
Real bfmeCosVNB(Real value);
Real bfmeSinVNB(Real value);

enum CommandSourceType
{
    COMMAND_SOURCE_AI = 2
};

class AICommandInterface
{
public:
    void aiMoveToPosition(const Coord3D *position, CommandSourceType commandSource);
};

class AIUpdateInterface
{
private:
    unsigned char m_unmodelled[0x20];

public:
    AICommandInterface m_commands;
};

class GeometryInfo
{
public:
    Real getMajorRadius() const
    {
        return m_majorRadius;
    }

private:
    unsigned char m_unmodelled[0x10];
    Real m_majorRadius;
};

class Object
{
public:
    const Coord3D *getPosition() const
    {
        return &m_position;
    }

    const GeometryInfo &getGeometryInfo() const
    {
        return m_geometryInfo;
    }

    AIUpdateInterface *getAIUpdateInterface() const
    {
        return *(AIUpdateInterface **)((unsigned char *)this + 0x204);
    }

private:
    unsigned char m_unmodelled_000[0x38];
    Coord3D m_position;
    Real m_orientation;
    unsigned char m_unmodelled_048[0xac - 0x48];
    GeometryInfo m_geometryInfo;
};

class GameLogic
{
public:
    Object *findObjectByID(Int id);
};

extern GameLogic *TheGameLogic;

class TerrainLogic
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual Real getGroundHeight(Real x, Real y, Int unused);
};

extern TerrainLogic *TheTerrainLogic;

class SlavedUpdateModuleData
{
private:
    unsigned char m_unmodelled[0x18];

public:
    Int m_scoutRange;
    Int m_scoutWanderRange;
};

class SlavedUpdate
{
public:
    void doScoutLogic(const Coord3D *mastersDestination);

    SlavedUpdateModuleData *getSlavedUpdateModuleData() const
    {
        return m_data;
    }

    Object *getObject() const
    {
        return m_object;
    }

private:
    unsigned char m_unmodelled_00[4];
    SlavedUpdateModuleData *m_data;
    Object *m_object;
    unsigned char m_unmodelled_0c[0x24 - 0x0c];
    UnsignedInt m_slaver;
    Coord3D m_guardPointOffset;
};

// ?doScoutLogic@SlavedUpdate@@QAEXPBUCoord3D@@@Z
void SlavedUpdate::doScoutLogic(const Coord3D *mastersDestination)
{
    const SlavedUpdateModuleData *data = getSlavedUpdateModuleData();
    Object *me = getObject();
    Object *master = TheGameLogic->findObjectByID(m_slaver);
    Coord3D scoutPosition;

    Real dx = me->getPosition()->x - mastersDestination->x;
    Real dy = me->getPosition()->y - mastersDestination->y;
    Real dist = (Real)sqrt(dx * dx + dy * dy);
    dist -= me->getGeometryInfo().getMajorRadius();
    if (dist < 0.0f)
        dist = 0.0f;
    else
        dist *= dist;
    Int scoutRange = data->m_scoutRange;
    if (dist > sqr(scoutRange))
    {
        Coord3D vector;
        vector.set(mastersDestination);
        vector.sub(master->getPosition());
        vector.normalize();
        vector.scale(scoutRange);
        scoutPosition.set(master->getPosition());
        scoutPosition.x = scoutPosition.x + vector.x;
        scoutPosition.y = scoutPosition.y + vector.y;
        scoutPosition.z = scoutPosition.z + vector.z;
    }
    else
    {
        scoutPosition.set(mastersDestination);
    }

    if (data->m_scoutWanderRange)
    {
        Real randomDirection = (Real)GetGameLogicRandomValue(
            0,
            6,
            "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\SlavedUpdate.cpp",
            0x189);

        m_guardPointOffset.zero();
        m_guardPointOffset.x +=
            data->m_scoutWanderRange * bfmeCosVNB(randomDirection);
        Real yOffset = m_guardPointOffset.y +=
            data->m_scoutWanderRange * bfmeSinVNB(randomDirection);

        scoutPosition.y += yOffset;
        scoutPosition.x += m_guardPointOffset.x;
        m_guardPointOffset.z = TheTerrainLogic->getGroundHeight(
            scoutPosition.x, scoutPosition.y, 0);
    }

    AIUpdateInterface *ai = me->getAIUpdateInterface();
    if (ai)
        ai->m_commands.aiMoveToPosition(&scoutPosition, COMMAND_SOURCE_AI);
}
