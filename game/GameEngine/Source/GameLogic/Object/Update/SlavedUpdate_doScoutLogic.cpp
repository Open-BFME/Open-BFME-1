// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// SlavedUpdate::doScoutLogic from the Zero Hour twin; SlavedUpdate.cpp literal line 0x189.
// aiMoveToPosition is visible but not inlined, so VC7.1 knows the target is not retained.

#include <vector>

typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;
typedef bool Bool;

extern const Real BfmeZeroRange;

extern "C" double __cdecl sqrt(double value);
#pragma intrinsic(sqrt)

struct Coord3D
{
    Real x;
    Real y;
    Real z;

    void set(const Coord3D *other)
    {
        x = other->x;
        y = other->y;
        z = other->z;
    }

    void sub(const Coord3D *other)
    {
        x -= other->x;
        y -= other->y;
        z -= other->z;
    }

    void scale(Real value)
    {
        x *= value;
        y *= value;
        z *= value;
    }

    void add(const Coord3D *other)
    {
        x += other->x;
        y += other->y;
        z += other->z;
    }

    void zero()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    void normalize();
};

enum CommandSourceType
{
    CMD_FROM_AI = 2
};

class Object;
class Team;
class Waypoint;
class PolygonTrigger;
class CommandButton;
class Path;

enum AICommandType
{
    AICMD_MOVE_TO_POSITION = 0x00
};

struct DamageInfo
{
    char m_bfme_body[0x5C];
};

class AICommandParms
{
public:
    AICommandParms(AICommandType commandType, CommandSourceType commandSource);

    AICommandType m_cmd;
    CommandSourceType m_cmdSource;
    Coord3D m_pos;
    Object *m_obj;
    Object *m_otherObj;
    const Team *m_team;
    std::vector<Coord3D> m_coords;
    const Waypoint *m_waypoint;
    const PolygonTrigger *m_polygon;
    int m_intValue;
    DamageInfo m_damage;
    const CommandButton *m_commandButton;
    Path *m_path;
};

class AICommandInterface
{
public:
    virtual void aiDoCommand(const AICommandParms *parms);

    __declspec(noinline) void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource)
    {
        AICommandParms parms(AICMD_MOVE_TO_POSITION, cmdSource);
        parms.m_pos = *pos;
        aiDoCommand(&parms);
    }
};

class AIUpdateInterface
{
private:
    unsigned char m_unmodelled[0x20];

public:
    AICommandInterface m_commands;
};

class Object
{
public:
    const Coord3D *getPosition() const
    {
        return &m_position;
    }

    AIUpdateInterface *getAIUpdateInterface() const
    {
        return m_ai;
    }

    Real getDistanceSquared(const Coord3D *position) const
    {
        Real dx = m_position.x - position->x;
        Real dy = m_position.y - position->y;
        Real distance = (Real)sqrt(dx * dx + dy * dy);

        distance -= m_boundingCircleRadius;
        if (distance < BfmeZeroRange)
            distance = 0.0f;
        else
            distance *= distance;
        return distance;
    }

    void setWeaponBonusCondition(Int condition)
    {
        m_weaponBonusCondition |= 1 << condition;
    }

private:
    unsigned char m_unmodelled_000[0x38];
    Coord3D m_position;
    unsigned char m_unmodelled_044[0xbc - 0x44];
    Real m_boundingCircleRadius;
    unsigned char m_unmodelled_0c0[0x204 - 0xc0];
    AIUpdateInterface *m_ai;
    unsigned char m_unmodelled_208[0x2a0 - 0x208];
    UnsignedInt m_weaponBonusCondition;
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
    unsigned char m_unmodelled[0x10];

public:
    Int m_attackRange;
    Int m_attackWanderRange;
    Int m_scoutRange;
    Int m_scoutWanderRange;
    Int m_distToTargetToGrantRangeBonus;
};

class SlavedUpdate
{
public:
    void doScoutLogic(const Coord3D *mastersDestination);

    SlavedUpdateModuleData *getSlavedUpdateModuleData() const
    {
        return *(SlavedUpdateModuleData **)((unsigned char *)this + 4);
    }

    Object *getObject() const
    {
        return *(Object **)((unsigned char *)this + 8);
    }

private:
    unsigned char m_unmodelled_00[4];
    unsigned char m_unmodelled_04[8];
    unsigned char m_unmodelled_0c[0x24 - 0x0c];
    UnsignedInt m_slaver;
    Coord3D m_guardPointOffset;
};

extern Real bfmeCosVNB(Real value);
extern Real bfmeSinVNB(Real value);
extern int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

// ?doScoutLogic@SlavedUpdate@@QAEXPBUCoord3D@@@Z
void SlavedUpdate::doScoutLogic(const Coord3D *mastersDestination)
{
    const SlavedUpdateModuleData *data = getSlavedUpdateModuleData();
    Object *me = getObject();
    Object *master = TheGameLogic->findObjectByID(m_slaver);
    Coord3D scoutPosition;

    Real dist = me->getDistanceSquared(mastersDestination);
    Int scoutRange = data->m_scoutRange;
    if (dist > scoutRange * scoutRange)
    {
        Coord3D vector;
        vector.set(mastersDestination);
        vector.sub(master->getPosition());
        vector.normalize();
        vector.scale(scoutRange);
        scoutPosition.set(master->getPosition());
        scoutPosition.add(&vector);
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
        m_guardPointOffset.x += data->m_scoutWanderRange * bfmeCosVNB(randomDirection);
        m_guardPointOffset.y += data->m_scoutWanderRange * bfmeSinVNB(randomDirection);

        scoutPosition.x += m_guardPointOffset.x;
        scoutPosition.y += m_guardPointOffset.y;
        m_guardPointOffset.z = TheTerrainLogic->getGroundHeight(
            scoutPosition.x, scoutPosition.y, 0);
    }

    AIUpdateInterface *ai = me->getAIUpdateInterface();
    if (ai)
        ai->m_commands.aiMoveToPosition(&scoutPosition, CMD_FROM_AI);
}
