// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// BFME SlavedUpdate repair-position movement, based on the Zero Hour twin.

typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;
typedef bool Bool;

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
};

enum WeaponSlotType
{
    WEAPON_SLOT_CURRENT = 0
};

enum CommandSourceType
{
    COMMAND_SOURCE_AI = 2
};

enum LocomotorSetType
{
    LOCOMOTORSET_PANIC = 4
};

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);
Real GetGameLogicRandomValueReal(Real lo, Real hi, char *file, int line);
Real bfmeCosVNB(Real value);
Real bfmeSinVNB(Real value);

class Object;

class GameLogic
{
public:
    Object *findObjectByID(Int id);
};

extern GameLogic *TheGameLogic;

class AICommandInterface
{
public:
    void aiMoveToPosition(const Coord3D *position, CommandSourceType commandSource);
};

class Locomotor
{
public:
    enum LocoFlag
    {
        PRECISE_Z_POS = 3,
        ULTRA_ACCURATE = 6
    };

    void setFlag(LocoFlag flag, Bool value)
    {
        if (value)
            m_flags |= 1 << flag;
        else
            m_flags &= ~(1 << flag);
    }

    void setUsePreciseZPos(Bool value)
    {
        setFlag(PRECISE_Z_POS, value);
    }

    void setUltraAccurate(Bool value)
    {
        setFlag(ULTRA_ACCURATE, value);
    }

private:
    unsigned char m_unmodelled[0x40];
    UnsignedInt m_flags;
};

class AIUpdateInterface
{
public:
    virtual void reserved000();
    virtual void reserved001();
    virtual void reserved002();
    virtual void reserved003();
    virtual void reserved004();
    virtual void reserved005();
    virtual void reserved006();
    virtual void reserved007();
    virtual void reserved008();
    virtual void reserved009();
    virtual void reserved010();
    virtual void reserved011();
    virtual void reserved012();
    virtual void reserved013();
    virtual void reserved014();
    virtual void reserved015();
    virtual void reserved016();
    virtual void reserved017();
    virtual void reserved018();
    virtual void reserved019();
    virtual void reserved020();
    virtual void reserved021();
    virtual void reserved022();
    virtual void reserved023();
    virtual void reserved024();
    virtual void reserved025();
    virtual void reserved026();
    virtual void reserved027();
    virtual void reserved028();
    virtual void reserved029();
    virtual void reserved030();
    virtual void reserved031();
    virtual void reserved032();
    virtual void reserved033();
    virtual void reserved034();
    virtual void reserved035();
    virtual void reserved036();
    virtual void reserved037();
    virtual void reserved038();
    virtual void reserved039();
    virtual void reserved040();
    virtual void reserved041();
    virtual void reserved042();
    virtual void reserved043();
    virtual void reserved044();
    virtual void reserved045();
    virtual void reserved046();
    virtual void reserved047();
    virtual void reserved048();
    virtual void reserved049();
    virtual void reserved050();
    virtual void reserved051();
    virtual void reserved052();
    virtual void reserved053();
    virtual void reserved054();
    virtual void reserved055();
    virtual void reserved056();
    virtual void reserved057();
    virtual void reserved058();
    virtual void reserved059();
    virtual void reserved060();
    virtual void reserved061();
    virtual void reserved062();
    virtual void reserved063();
    virtual void reserved064();
    virtual void reserved065();
    virtual void reserved066();
    virtual void reserved067();
    virtual void reserved068();
    virtual void reserved069();
    virtual void reserved070();
    virtual void reserved071();
    virtual void reserved072();
    virtual void reserved073();
    virtual void reserved074();
    virtual void reserved075();
    virtual void reserved076();
    virtual void reserved077();
    virtual void reserved078();
    virtual void reserved079();
    virtual void reserved080();
    virtual void reserved081();
    virtual void reserved082();
    virtual void reserved083();
    virtual void reserved084();
    virtual void reserved085();
    virtual void reserved086();
    virtual void reserved087();
    virtual void reserved088();
    virtual void reserved089();
    virtual void reserved090();
    virtual void reserved091();
    virtual void reserved092();
    virtual void reserved093();
    virtual void reserved094();
    virtual void reserved095();
    virtual void reserved096();
    virtual void reserved097();
    virtual void reserved098();
    virtual void reserved099();
    virtual void reserved100();
    virtual void reserved101();
    virtual void reserved102();
    virtual void reserved103();
    virtual void reserved104();
    virtual void reserved105();
    virtual void reserved106();
    virtual void reserved107();
    virtual void reserved108();
    virtual void reserved109();
    virtual void reserved110();
    virtual void reserved111();
    virtual void reserved112();
    virtual void reserved113();
    virtual void reserved114();
    virtual void reserved115();
    virtual void reserved116();
    virtual void reserved117();
    virtual void reserved118();
    virtual void reserved119();
    virtual void reserved120();
    virtual void reserved121();
    virtual void reserved122();
    virtual void reserved123();
    virtual void reserved124();
    virtual void reserved125();
    virtual void reserved126();
    virtual Bool chooseLocomotorSet(LocomotorSetType set);

    Locomotor *getCurLocomotor()
    {
        return *(Locomotor **)((unsigned char *)this + 0x1cc);
    }

private:
    unsigned char m_unmodelled[0x1c];

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
    unsigned char m_unmodelled[0x24];

public:
    Int m_repairRange;
    Real m_repairMinAltitude;
    Real m_repairMaxAltitude;
};

class SlavedUpdate
{
public:
    void moveToNewRepairSpot();

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
    SlavedUpdateModuleData *m_data;
    Object *m_object;
    unsigned char m_unmodelled_0c[0x24 - 0x0c];
    UnsignedInt m_slaver;
    Coord3D m_guardPointOffset;
};

class Object
{
private:
    unsigned char m_unmodelled[0x38];

public:
    Coord3D m_position;

    AIUpdateInterface *getAIUpdateInterface() const
    {
        return *(AIUpdateInterface **)((unsigned char *)this + 0x204);
    }

    const Coord3D *getPosition() const
    {
        return &m_position;
    }
};

// ?moveToNewRepairSpot@SlavedUpdate@@QAEXXZ
void SlavedUpdate::moveToNewRepairSpot()
{
    const SlavedUpdateModuleData *data = getSlavedUpdateModuleData();
    Object *me = getObject();
    Object *master = TheGameLogic->findObjectByID(m_slaver);

    if (data->m_repairRange)
    {
        Real randomDirection = (Real)GetGameLogicRandomValue(
            0,
            6,
            "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\SlavedUpdate.cpp",
            0x2b9);

        m_guardPointOffset.set(master->getPosition());
        m_guardPointOffset.x += data->m_repairRange * bfmeCosVNB(randomDirection);
        m_guardPointOffset.y += data->m_repairRange * bfmeSinVNB(randomDirection);
        m_guardPointOffset.z = TheTerrainLogic->getGroundHeight(
            m_guardPointOffset.x, m_guardPointOffset.y, 0);

        Real altitude = GetGameLogicRandomValueReal(
            data->m_repairMinAltitude,
            data->m_repairMaxAltitude,
            "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\SlavedUpdate.cpp",
            0x2be);
        m_guardPointOffset.z += altitude;

        AIUpdateInterface *ai = me->getAIUpdateInterface();
        if (ai)
        {
            ai->chooseLocomotorSet(LOCOMOTORSET_PANIC);
            ai->getCurLocomotor()->setUltraAccurate(true);
            ai->m_commands.aiMoveToPosition(
                &m_guardPointOffset, COMMAND_SOURCE_AI);

            Locomotor *locomotor = ai->getCurLocomotor();
            if (locomotor)
                locomotor->setUsePreciseZPos(true);
        }
    }
}
