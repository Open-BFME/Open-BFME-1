// ?update@Rva002A5500@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.31 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Retail update body at 0x002A5500; BFME layout views follow landed neighbors.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef int ObjectID;
typedef float Real;
typedef bool Bool;

enum UpdateSleepTime
{
    UPDATE_SLEEP_NONE = 1
};

enum RepairStates
{
    REPAIRSTATE_NONE = 0
};

enum PathfindLayerEnum
{
    PATHFIND_LAYER_DEFAULT = 0
};

enum Relationship
{
    RELATIONSHIP_ALLIES = 2
};

struct Coord3D
{
    Real x;
    Real y;
    Real z;
};

class Object;
class Team;
class AIUpdateInterface;
class Locomotor;

class GameLogic
{
public:
    Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;
extern const Real BfmeZeroRange;

class ModuleBase
{
public:
    virtual ~ModuleBase();

protected:
    void *m_moduleData;
    Object *m_object;
};

class BehaviorModuleInterface
{
public:
    virtual void behaviorAnchor();
};

class UpdateModuleInterface
{
public:
    virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public ModuleBase, public BehaviorModuleInterface,
    public UpdateModuleInterface
{
private:
    UnsignedInt m_nextCallFrame;
    Int m_moduleIndex;
    Int m_wakeFrame;
};

class SlavedUpdateInterface
{
public:
    virtual void slavedUpdateAnchor();
};

class UpdateModuleDataBase
{
public:
    virtual ~UpdateModuleDataBase();

private:
    UnsignedInt m_unmodelled04;
};

class SlavedUpdateModuleData : public UpdateModuleDataBase
{
public:
    Int m_guardMaxRange;
    Int m_guardWanderRange;
    Int m_attackRange;
    Int m_attackWanderRange;
    Int m_scoutRange;
    Int m_scoutWanderRange;
    Int m_distToTargetToGrantRangeBonus;
    Int m_repairRange;
    Real m_repairMinAltitude;
    Real m_repairMaxAltitude;
    Real m_repairRatePerSecond;
    Int m_repairWhenHealthBelowPercentage;
    Int m_minReadyFrames;
    Int m_maxReadyFrames;
    Int m_minWeldFrames;
    Int m_maxWeldFrames;
    unsigned char m_weldingStrings[8];
    unsigned char m_stayOnSameLayerAsMaster;
};

class BodyModuleInterface
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual Real getHealth();
    virtual void slot05();
    virtual Real getMaxHealth();
};

class PathNode
{
public:
    unsigned char m_beforePosition[0x0c];
    Coord3D m_position;
};

class Path
{
public:
    unsigned char m_beforeLastNode[8];
    PathNode *m_lastNode;
};

class AIUpdateInterface
{
public:
#define AI_SLOT(n) virtual void slot##n();
    AI_SLOT(000) AI_SLOT(001) AI_SLOT(002) AI_SLOT(003)
    AI_SLOT(004) AI_SLOT(005) AI_SLOT(006) AI_SLOT(007)
    AI_SLOT(008) AI_SLOT(009) AI_SLOT(010) AI_SLOT(011)
    AI_SLOT(012) AI_SLOT(013) AI_SLOT(014) AI_SLOT(015)
    AI_SLOT(016) AI_SLOT(017) AI_SLOT(018) AI_SLOT(019)
    AI_SLOT(020) AI_SLOT(021) AI_SLOT(022) AI_SLOT(023)
    AI_SLOT(024) AI_SLOT(025) AI_SLOT(026) AI_SLOT(027)
    AI_SLOT(028) AI_SLOT(029) AI_SLOT(030) AI_SLOT(031)
    AI_SLOT(032) AI_SLOT(033) AI_SLOT(034) AI_SLOT(035)
    AI_SLOT(036) AI_SLOT(037) AI_SLOT(038) AI_SLOT(039)
    AI_SLOT(040) AI_SLOT(041) AI_SLOT(042) AI_SLOT(043)
    AI_SLOT(044) AI_SLOT(045) AI_SLOT(046) AI_SLOT(047)
    AI_SLOT(048) AI_SLOT(049) AI_SLOT(050) AI_SLOT(051)
    AI_SLOT(052) AI_SLOT(053) AI_SLOT(054) AI_SLOT(055)
    AI_SLOT(056) AI_SLOT(057) AI_SLOT(058) AI_SLOT(059)
    AI_SLOT(060) AI_SLOT(061) AI_SLOT(062) AI_SLOT(063)
    AI_SLOT(064) AI_SLOT(065) AI_SLOT(066) AI_SLOT(067)
    AI_SLOT(068) AI_SLOT(069) AI_SLOT(070) AI_SLOT(071)
    AI_SLOT(072) AI_SLOT(073) AI_SLOT(074) AI_SLOT(075)
    AI_SLOT(076) AI_SLOT(077) AI_SLOT(078) AI_SLOT(079)
    AI_SLOT(080) AI_SLOT(081) AI_SLOT(082) AI_SLOT(083)
    AI_SLOT(084) AI_SLOT(085) AI_SLOT(086) AI_SLOT(087)
    AI_SLOT(088) AI_SLOT(089) AI_SLOT(090) AI_SLOT(091)
    AI_SLOT(092) AI_SLOT(093) AI_SLOT(094) AI_SLOT(095)
    virtual Bool isIdle();
#undef AI_SLOT

    Object *getCurrentVictim() const;

    unsigned char m_beforePath[0x13c];
    Path *m_path;
    unsigned char m_beforeLocomotor[0x88];
    Locomotor *m_locomotor;
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

class Team
{
public:
    Relationship getRelationship(const Team *other) const;
};

class Object
{
public:
    void defect(Team *team, UnsignedInt detectionTime);
    PathfindLayerEnum getLayer() const;
    void setLayer(PathfindLayerEnum layer);
    void clearWeaponBonusCondition(Int condition);
    AIUpdateInterface *getAIUpdateInterface() const
    {
        return *reinterpret_cast<AIUpdateInterface *const *>(
            reinterpret_cast<const unsigned char *>(this) + 0x204);
    }
    BodyModuleInterface *getBodyModule() const
    {
        return *reinterpret_cast<BodyModuleInterface *const *>(
            reinterpret_cast<const unsigned char *>(this) + 0x200);
    }
    Team *getTeam() const
    {
        return *reinterpret_cast<Team *const *>(
            reinterpret_cast<const unsigned char *>(this) + 0x23c);
    }
    const Coord3D *getPosition() const
    {
        return reinterpret_cast<const Coord3D *>(
            reinterpret_cast<const unsigned char *>(this) + 0x38);
    }
};

struct BFMEObjectFields
{
    unsigned char m_beforePosition[0x38];
    Coord3D m_position;
    unsigned char m_beforeBody[0x200 - 0x44];
    BodyModuleInterface *m_body;
    AIUpdateInterface *m_ai;
    unsigned char m_beforeTeam[0x23c - 0x208];
    Team *m_team;
    unsigned char m_beforePrivateStatus[0x344 - 0x240];
    unsigned char m_privateStatus;
};

struct BfmePt951
{
    Real x;
    Real y;
};

class BfmeGap951
{
public:
    Real bfmeGapB951(const BfmePt951 *other) const;
};

struct BfmeVec3EJ
{
    Real x;
    Real y;
    Real z;
};

class Gen_000E5A50
{
public:
    Real bfmeDistanceSquared(const BfmeVec3EJ *point) const;
};

class Gen_000E5A90
{
public:
    Real bfmeDistanceSquared(const Gen_000E5A90 *other) const;
};

class Rva000C8950
{
public:
    Rva000C8950 *clear(UnsignedInt bit);
};

class Gen_001BEC20
{
public:
    Int bfmeScale() const;
};

class Rva002A5500 : public UpdateModule, public SlavedUpdateInterface
{
public:
    virtual UpdateSleepTime update();
    const SlavedUpdateModuleData *getSlavedUpdateModuleData() const
    {
        return static_cast<const SlavedUpdateModuleData *>(m_moduleData);
    }
    Object *getObject() const { return m_object; }
    void doRepairLogic();
    void endRepair();
    void doAttackLogic(const Object *target);
    void doScoutLogic(const Coord3D *destination);
    void doGuardLogic(Coord3D *position);
    void stopSlavedEffects();

private:
    ObjectID m_slaver;
    Coord3D m_guardPointOffset;
    Int m_framesToWait;
    RepairStates m_repairState;
    Bool m_repairing;
    unsigned char m_padding3D[3];
    ObjectID m_version2ObjectID;
};

#pragma comment(linker, "/alternatename:?findObjectByID@GameLogic@@QAEPAVObject@@H@Z=?j_0001f253@@YAXXZ")
#pragma comment(linker, "/alternatename:?getRelationship@Team@@QBE?AW4Relationship@@PBV1@@Z=?j_0000cc2a@@YAXXZ")
#pragma comment(linker, "/alternatename:?defect@Object@@QAEXPAVTeam@@I@Z=?j_00002d06@@YAXXZ")
#pragma comment(linker, "/alternatename:?getLayer@Object@@QBEHXZ=?j_0003a391@@YAXXZ")
#pragma comment(linker, "/alternatename:?setLayer@Object@@QAEXW4PathfindLayerEnum@@@Z=?j_00035e0e@@YAXXZ")
#pragma comment(linker, "/alternatename:?clearWeaponBonusCondition@Object@@QAEXH@Z=?j_0000eaed@@YAXXZ")
#pragma comment(linker, "/alternatename:?getCurrentVictim@AIUpdateInterface@@QBEPAVObject@@XZ=?j_000261a2@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeGapB951@BfmeGap951@@QBEMPBUBfmePt951@@@Z=?j_000158b1@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeDistanceSquared@Gen_000E5A50@@QBEMPBVBfmeVec3EJ@@@Z=?j_00008a26@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeDistanceSquared@Gen_000E5A90@@QBEMPBV1@@Z=?j_0002e7fd@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeScale@Gen_001BEC20@@QBEHXZ=?j_0003a391@@YAXXZ")
#pragma comment(linker, "/alternatename:?doRepairLogic@Rva002A5500@@QAEXXZ=?j_0003ff6c@@YAXXZ")
#pragma comment(linker, "/alternatename:?endRepair@Rva002A5500@@QAEXXZ=?j_000053c6@@YAXXZ")
#pragma comment(linker, "/alternatename:?doAttackLogic@Rva002A5500@@QAEXPBVObject@@@Z=?j_00017b2f@@YAXXZ")
#pragma comment(linker, "/alternatename:?doScoutLogic@Rva002A5500@@QAEXPBUCoord3D@@@Z=?j_00002680@@YAXXZ")
#pragma comment(linker, "/alternatename:?doGuardLogic@Rva002A5500@@QAEXPAUCoord3D@@@Z=?j_00007761@@YAXXZ")
#pragma comment(linker, "/alternatename:?stopSlavedEffects@Rva002A5500@@AAEXXZ=?j_000432b1@@YAXXZ")

// ?update@Rva002A5500@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime Rva002A5500::update()
{
    if (m_framesToWait > 0)
        --m_framesToWait;

    if (m_repairState == REPAIRSTATE_NONE)
    {
        if (m_framesToWait > 0)
            return UPDATE_SLEEP_NONE;
        m_framesToWait = 1;
    }

    ObjectID slaver = m_slaver;
    if (slaver == 0)
        return UPDATE_SLEEP_NONE;

    const SlavedUpdateModuleData *data = getSlavedUpdateModuleData();
    Object *me = getObject();
    if (!me)
        return UPDATE_SLEEP_NONE;

    AIUpdateInterface *myAI = me->getAIUpdateInterface();
    if (!myAI)
        return UPDATE_SLEEP_NONE;

    Locomotor *locomotor = myAI->m_locomotor;
    if (!locomotor)
        return UPDATE_SLEEP_NONE;

    if (m_version2ObjectID)
    {
        Object *version2Object = TheGameLogic->findObjectByID(m_version2ObjectID);
        if (version2Object &&
            (reinterpret_cast<BFMEObjectFields *>(version2Object)->m_privateStatus & 1))
            m_version2ObjectID = 0;
    }

    Object *master = TheGameLogic->findObjectByID(slaver);
    if (!master || (reinterpret_cast<BFMEObjectFields *>(master)->m_privateStatus & 1))
    {
        stopSlavedEffects();
        return UPDATE_SLEEP_NONE;
    }

    Team *masterTeam = master->getTeam();
    Team *myTeam = me->getTeam();
    if (masterTeam->getRelationship(myTeam) != RELATIONSHIP_ALLIES)
        me->defect(masterTeam, 0);

    if (data->m_stayOnSameLayerAsMaster)
        me->setLayer(master->getLayer());

    master->clearWeaponBonusCondition(6);

    Object *target = 0;
    AIUpdateInterface *masterAI = master->getAIUpdateInterface();
    if (masterAI)
        target = masterAI->getCurrentVictim();

    Int healthPercentage = 100;
    if (data->m_repairRatePerSecond > BfmeZeroRange)
    {
        BodyModuleInterface *body = master->getBodyModule();
        if (body)
        {
            Real health = body->getHealth();
            Real maxHealth = body->getMaxHealth();
            healthPercentage = (Int)(health / maxHealth *
                *reinterpret_cast<const Real *>(0x0107FAC4));
        }
    }

    if (healthPercentage <= data->m_repairWhenHealthBelowPercentage)
    {
        doRepairLogic();
        return UPDATE_SLEEP_NONE;
    }

    if (data->m_attackRange && target)
    {
        endRepair();
        doAttackLogic(target);
        return UPDATE_SLEEP_NONE;
    }

    if (data->m_scoutRange)
    {
        if (masterAI->m_path)
        {
            PathNode *lastNode = masterAI->m_path->m_lastNode;
            const BfmePt951 *destination =
                reinterpret_cast<const BfmePt951 *>(&lastNode->m_position);
            Real distance =
                reinterpret_cast<const BfmeGap951 *>(master)->bfmeGapB951(destination);
            Real range = (Real)data->m_guardMaxRange *
                *reinterpret_cast<const Real *>(0x0107533C);
            if (distance > range * range)
            {
                endRepair();
                doScoutLogic(&lastNode->m_position);
                return UPDATE_SLEEP_NONE;
            }
        }
    }

    if (healthPercentage < 100)
    {
        doRepairLogic();
        return UPDATE_SLEEP_NONE;
    }

    Coord3D pinnedPosition = *master->getPosition();
    pinnedPosition.x += m_guardPointOffset.x;
    pinnedPosition.y += m_guardPointOffset.y;
    m_guardPointOffset.z = TheTerrainLogic->getGroundHeight(
        pinnedPosition.x, pinnedPosition.y, 0);

    if (data->m_guardMaxRange)
    {
        if (myAI->isIdle() &&
            reinterpret_cast<const Gen_000E5A50 *>(myAI)->bfmeDistanceSquared(
                reinterpret_cast<const BfmeVec3EJ *>(&pinnedPosition)) >
                *reinterpret_cast<const Real *>(0x012B20E0))
        {
            endRepair();
            doGuardLogic(&pinnedPosition);
        }
        else if (reinterpret_cast<const Gen_000E5A90 *>(myAI)->bfmeDistanceSquared(
                     reinterpret_cast<const Gen_000E5A90 *>(master)) >
                 data->m_guardMaxRange * data->m_guardMaxRange)
        {
            endRepair();
            doGuardLogic(&pinnedPosition);
        }
    }

    return UPDATE_SLEEP_NONE;
}
