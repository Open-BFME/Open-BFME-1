// ?doAttackLogic@SlavedUpdate@@QAEXPBVObject@@@Z
// partial score=0.72 date=2026-09-17
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB

// Open-BFME: SlavedUpdate::doAttackLogic, based on the Zero Hour twin and
// the BFME retail inlined boundary-distance calculation.

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
    unsigned char m_unmodelled_018[0x20 - 0x18];
    Int m_distToTargetToGrantRangeBonus;
};

class SlavedUpdate
{
public:
    void doAttackLogic(const Object *target);

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

// ?doAttackLogic@SlavedUpdate@@QAEXPBVObject@@@Z
void SlavedUpdate::doAttackLogic(const Object *target)
{
    const SlavedUpdateModuleData *data = getSlavedUpdateModuleData();
    Object *me = getObject();
    Object *master = TheGameLogic->findObjectByID(m_slaver);
    Coord3D attackPosition;

    const Coord3D *targetPos = target->getPosition();
    Real dist = me->getDistanceSquared(targetPos);
    Int attackRange = data->m_attackRange;
    if (dist > attackRange * attackRange)
    {
        Coord3D vector;
        vector.set(targetPos);
        vector.sub(master->getPosition());
        vector.normalize();
        vector.scale(attackRange);
        attackPosition.set(master->getPosition());
        attackPosition.add(&vector);
    }
    else
    {
        attackPosition.set(targetPos);
    }

    if (data->m_attackWanderRange)
    {
        Real randomDirection = (Real)GetGameLogicRandomValue(
            0,
            6,
            "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\SlavedUpdate.cpp",
            0x14a);

        m_guardPointOffset.zero();
        m_guardPointOffset.x += data->m_attackWanderRange * bfmeCosVNB(randomDirection);
        m_guardPointOffset.y += data->m_attackWanderRange * bfmeSinVNB(randomDirection);

        attackPosition.x += m_guardPointOffset.x;
        attackPosition.y += m_guardPointOffset.y;
        m_guardPointOffset.z = TheTerrainLogic->getGroundHeight(
            attackPosition.x, attackPosition.y, 0);
    }

    AIUpdateInterface *ai = me->getAIUpdateInterface();
    if (ai)
        ai->m_commands.aiMoveToPosition(&attackPosition, CMD_FROM_AI);

    if (dist < data->m_distToTargetToGrantRangeBonus *
        data->m_distToTargetToGrantRangeBonus)
        master->setWeaponBonusCondition(6);
}
