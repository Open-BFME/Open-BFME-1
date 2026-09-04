// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB

typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;
typedef bool Bool;

struct Coord3D
{
    Real x;
    Real y;
    Real z;

    void zero()
    {
        x = 0;
        y = 0;
        z = 0;
    }
};

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);
Real bfmeCosVNB(Real value);
Real bfmeSinVNB(Real value);

enum WeaponSlotType
{
    WEAPON_SLOT_CURRENT = 0
};

class Weapon
{
private:
    unsigned char m_unmodelled[0x34];

public:
    Int m_maxShotsToFire;
};

class Object
{
public:
    class AIUpdateInterface *getAIUpdateInterface() const
    {
        return *(class AIUpdateInterface **)((unsigned char *)this + 0x204);
    }

    Weapon *getCurrentWeapon(WeaponSlotType *slot);
};

enum CommandSourceType
{
    COMMAND_SOURCE_2 = 2
};

class AICommandInterface
{
public:
    void aiAttackMoveToPosition(const Coord3D *position, Int maxShotsToFire,
        CommandSourceType commandSource);
};

class AIUpdateInterface
{
private:
    unsigned char m_unmodelled[0x20];

public:
    AICommandInterface m_commands;
};

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
    unsigned char m_unmodelled[0x0c];

public:
    Int m_guardWanderRange;
};

class SlavedUpdate
{
public:
    void doGuardLogic(Coord3D *pinnedPosition);
    Object *getObject() const
    {
        return *(Object **)((unsigned char *)this + 8);
    }
    SlavedUpdateModuleData *getSlavedUpdateModuleData() const
    {
        return *(SlavedUpdateModuleData **)((unsigned char *)this + 4);
    }

private:
    unsigned char m_unmodelled_00[4];
    unsigned char m_unmodelled_04[8];
    unsigned char m_unmodelled_0c[0x24 - 0x0c];
    UnsignedInt m_slaver;
    Coord3D m_guardPointOffset;
};

// ?doGuardLogic@SlavedUpdate@@QAEXPAUCoord3D@@@Z
void SlavedUpdate::doGuardLogic(Coord3D *pinnedPosition)
{
    SlavedUpdateModuleData *data = getSlavedUpdateModuleData();
    Object *me = getObject();

    if (data->m_guardWanderRange)
    {
        Real randomDirection = (Real)GetGameLogicRandomValue(
            0,
            6,
            "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\SlavedUpdate.cpp",
            0x1a7);

        m_guardPointOffset.zero();
        m_guardPointOffset.x += bfmeCosVNB(randomDirection) * data->m_guardWanderRange;
        m_guardPointOffset.y += bfmeSinVNB(randomDirection) * data->m_guardWanderRange;

        pinnedPosition->x += m_guardPointOffset.x;
        pinnedPosition->y += m_guardPointOffset.y;
        m_guardPointOffset.z = TheTerrainLogic->getGroundHeight(
            pinnedPosition->x, pinnedPosition->y, 0);
    }

    Int maxShotsToFire = 0;
    AIUpdateInterface *ai = me->getAIUpdateInterface();
    if (ai)
    {
        Weapon *weapon = getObject()->getCurrentWeapon(0);
        if (weapon)
            maxShotsToFire = weapon->m_maxShotsToFire;

        ai->m_commands.aiAttackMoveToPosition(
            pinnedPosition, maxShotsToFire, COMMAND_SOURCE_2);
    }
}
