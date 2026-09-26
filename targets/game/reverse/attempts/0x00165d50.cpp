// ?queueSupplyTruck@AIPlayer@@IAEXXZ
// partial score=0.9957136733819117 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/objectdlink /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
// AIPlayer::queueSupplyTruck, retail RVA 0x00165D50, complete extent 2333B.
// Original algorithm: Zero Hour AIPlayer.cpp; BFME-specific layouts and calls
// are established by AIPlayerIsSupplySourceAttacked.cpp, AIPlayerFindSupplyCenter.cpp,
// AIPlayerCheckReadyTeams.cpp, and native AIPlayer_findFactory.cpp.
// The four-slot WorkOrder/TeamInQueue tables are verified independently:
// destructor, loadPostProcess, crc(Xfer*), xfer(Xfer*). Native MAKE_DLINK member
// constructors are necessary for TeamInQueue's table-store scheduling.
// Native STLport bitset/list/hash_map and the existing ObjectDlinkPmf.h express
// the actual container and virtual-base member-pointer operations.
// Current near match: 2333/2333B, ten masked-byte differences in the availableCash
// multiplication (+0x376..+0x389). Retail loads GlobalData's box value first;
// MSVC loads warehouse boxes first. The corresponding DIR32 global load moves
// by six bytes, so this is not a valid strict byte match. All 26 direct call
// relocations resolve to the expected 17 targets with no unresolved symbols.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>
#include <bitset>
#include "ObjectDlinkPmf.h"
#include "string_base.h"
template <> inline int StringBase<char>::getLength() const
{
    return m_data ? m_data->length : 0;
}
template <> inline const char *StringBase<char>::str() const
{
    return m_data ? m_data->data : "";
}
template <> inline void StringBase<char>::concat(const StringBase<char> &s)
{
    concat(s.str(), s.getLength());
}
#include "ascii_string.h"
#include "basetype.h"
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int ObjectID;
#define callMemberFunction(object, ptrToMember) ((object).*(ptrToMember))
#define NULL 0
#define CMD_FROM_PLAYER 0
#define KINDOF_HARVESTER 16
#define KINDOF_REBUILD_HOLE 38
#define KINDOF_SUPPLY_SOURCE 85
#define FROM_BOUNDINGSPHERE_2D 1
#define SUPPLY_CENTER_CLOSE_DIST 200.0f
#define newInstance(T) new (T::GLUE) T
#define DEBUG_LOG(x)
template <class OBJCLASS>
// upstream layout:
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
class DLINK_ITERATOR
{
  public:
    typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;

  private:
    OBJCLASS *m_cur;
    GetNextFunc m_getNextFunc;

  public:
    DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc)
    {
    }

    void advance()
    {
        if (m_cur)
            m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
    }

    Bool done() const
    {
        return m_cur == 0;
    }

    OBJCLASS *cur() const
    {
        return m_cur;
    }
};

class Team;
class Player;
class BuildListInfo;
class WorkOrder;
enum Relationship
{
    ENEMIES = 0
};
enum NameKeyType
{
    NAMEKEY_INVALID = 0
};
class Overridable
{
  public:
    const Overridable *getFinalOverride() const;
    void *m_vtable;
    Overridable *m_nextOverride;
};
class ThingTemplate : public Overridable
{
  public:
    char p08[0x20 - 8];
    AsciiString m_name;
    char p24[0xc8 - 0x24];
    std::bitset<192> m_kind;
    char pe0[0x38c - 0xe0];
    const ThingTemplate *m_next;
    bool isKindOf(int bit) const
    {
        return m_kind.test(bit);
    }
    const AsciiString &getName() const
    {
        return m_name;
    }
    const ThingTemplate *friend_getNextTemplate() const
    {
        return m_next;
    }
};
class SupplyTruckAIInterface
{
  public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual bool isCurrentlyFerryingSupplies() const;
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual bool isForcedIntoWantingState() const;
    virtual void slot13();
    virtual void slot14();
    virtual ObjectID getPreferredDockID() const;
};
enum CommandSourceType
{
    FROM_PLAYER = 0
};
class AICommandInterface
{
  public:
    void aiDock(Object *, CommandSourceType);
};
class AIUpdateInterface
{
  public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual void slot51();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56();
    virtual void slot57();
    virtual void slot58();
    virtual void slot59();
    virtual void slot60();
    virtual void slot61();
    virtual void slot62();
    virtual void slot63();
    virtual void slot64();
    virtual void slot65();
    virtual void slot66();
    virtual void slot67();
    virtual void slot68();
    virtual void slot69();
    virtual void slot70();
    virtual void slot71();
    virtual void slot72();
    virtual void slot73();
    virtual void slot74();
    virtual void slot75();
    virtual void slot76();
    virtual void slot77();
    virtual void slot78();
    virtual void slot79();
    virtual void slot80();
    virtual SupplyTruckAIInterface *getSupplyTruckAIInterface();
    void aiDock(Object *o, int c)
    {
        ((AICommandInterface *)((char *)this + 0x20))->aiDock(o, (CommandSourceType)c);
    }
};
class SupplyWarehouseDockUpdate
{
  public:
    char p[0x88];
    int m_boxesStored;
    int getBoxesStored() const
    {
        return m_boxesStored;
    }
};
class Module;
extern void j_0002ae23();
class Rva001BEE60Object
{
  public:
    Module *findModule(NameKeyType key) const
    {
        typedef Module *(Rva001BEE60Object::*Fn)(NameKeyType) const;
        union
        {
            void (*raw)();
            Fn member;
        } f;
        f.raw = j_0002ae23;
        return (this->*f.member)(key);
    }
};
class QueueObjectView
{
  public:
    void *v;
    const ThingTemplate *m_template;
    char p08[0x38 - 8];
    Coord3D m_position;
    char p44[0x74 - 0x44];
    ObjectID m_id;
    char p78[0xbc - 0x78];
    float m_radius;
    char pc0[0x204 - 0xc0];
    AIUpdateInterface *m_ai;
    char p208[0x23c - 0x208];
    Team *m_team;
    const ThingTemplate *getTemplate() const
    {
        const ThingTemplate *d = m_template;
        const ThingTemplate *f;
        if (d == 0)
            f = d;
        else
            f = (const ThingTemplate *)(d->m_nextOverride ? d->m_nextOverride->getFinalOverride()
                                                          : d);
        return f;
    }
    bool isKindOf(int bit) const
    {
        return getTemplate()->isKindOf(bit);
    }
    AIUpdateInterface *getAI() const
    {
        return m_ai;
    }
    ObjectID getID() const
    {
        return m_id;
    }
    const Coord3D *getPosition() const
    {
        return &m_position;
    }
    Team *getTeam() const
    {
        return m_team;
    }
    float getBoundingCircleRadius() const
    {
        return m_radius;
    }
    SupplyWarehouseDockUpdate *findUpdateModule(NameKeyType key)
    {
        return (SupplyWarehouseDockUpdate *)((Rva001BEE60Object *)this)->findModule(key);
    }
};
static QueueObjectView *view(Object *o)
{
    return (QueueObjectView *)o;
}
class Team
{
  public:
    Team *_bfme_nextInInstanceList() const;

    void *m_vptr;
    class TeamPrototype *m_proto;
    void *m_id;
    Object *m_head; // +0x0C

    const AsciiString &getName() const;
    DLINK_ITERATOR<Object> iterate_TeamMemberList() const
    {
        return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
    }
};

// upstream layout:
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
  public:
    DLINK_ITERATOR<Team> iterate_TeamInstanceList()
    {
        return DLINK_ITERATOR<Team>(m_teamInstanceList, Team::_bfme_nextInInstanceList);
    }

    char p00[0x14];
    AsciiString m_name;
    char p18[0x274 - 0x18];
    Team *m_teamInstanceList; // +0x274
};

extern const AsciiString Rva01336E50EmptyString;
const AsciiString &Team::getName() const
{
    if (!m_proto)
        return Rva01336E50EmptyString;
    return m_proto->m_name;
}
class BuildListInfo
{
  public:
    char p00[0x2c];
    BuildListInfo *m_next;
    char p30[0x48 - 0x30];
    ObjectID m_objectID;
    char p4c[0x7c - 0x4c];
    bool m_supplyBuilding;
    int m_desiredGatherers, m_currentGatherers;
    BuildListInfo *getNext() const
    {
        return m_next;
    }
    bool isSupplyBuilding() const
    {
        return m_supplyBuilding;
    }
    int getDesiredGatherers() const
    {
        return m_desiredGatherers;
    }
    int getCurrentGatherers() const
    {
        return m_currentGatherers;
    }
    void setCurrentGatherers(int n)
    {
        m_currentGatherers = n;
    }
    ObjectID getObjectID() const
    {
        return m_objectID;
    }
};
class Player
{
  public:
    typedef std::list<TeamPrototype *> PlayerTeamList;
    char p00[0x1c0];
    BuildListInfo *m_buildList;
    char p1c4[0x230 - 0x1c4];
    Team *m_defaultTeam;
    char p234[0x288 - 0x234];
    PlayerTeamList m_playerTeamPrototypes;
    char p28c[8];
    bool m_canBuildUnits;
    const PlayerTeamList *getPlayerTeams() const
    {
        return &m_playerTeamPrototypes;
    }
    BuildListInfo *getBuildList() const
    {
        return m_buildList;
    }
    Team *getDefaultTeam() const
    {
        return m_defaultTeam;
    }
    bool getCanBuildUnits() const
    {
        return m_canBuildUnits;
    }
    void setCanBuildUnits(bool b)
    {
        m_canBuildUnits = b;
    }
    Relationship getRelationship(const Team *) const;
};
typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>, _STL::equal_to<ObjectID> >
    ObjectPtrHash;

// upstream layout:
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
  public:
    UnsignedInt getFrame(void) const
    {
        return m_frame;
    }
    Object *findObjectByID(ObjectID id)
    {
        if (id == 0)
            return NULL;
        ObjectPtrHash::iterator it = m_objHash.find(id);
        if (it == m_objHash.end())
            return NULL;
        return (*it).second;
    }

  private:
    char m_unmodelled000[0x3c];
    UnsignedInt m_frame; // +0x3C
    char m_unmodelled040[0xb0 - 0x40];
    ObjectPtrHash m_objHash; // buckets at +0xB4
};

extern GameLogic *TheGameLogic;

class NameKeyGenerator
{
  public:
    NameKeyType nameToKey(const char *name);
};

class GlobalData
{
  public:
    unsigned char m_pad[0xB24];
    Int m_baseValuePerSupplyBox;
};

struct KindOfMaskType
{
    enum BogusInitType
    {
        kInit = 0
    };
    std::bitset<192> bits;
    KindOfMaskType()
    {
    }
    KindOfMaskType(BogusInitType, int bit)
    {
        bits.set(bit);
    }
};

extern const KindOfMaskType KINDOFMASK_NONE;

class PartitionFilter
{
  public:
    PartitionFilter() : m_next(0)
    {
    }
    virtual ~PartitionFilter()
    {
    }
    PartitionFilter *link(PartitionFilter *next);
    PartitionFilter *m_next;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
  public:
    PartitionFilterAcceptByKindOf(const KindOfMaskType &mustBeSet,
                                  const KindOfMaskType &mustBeClear)
        : m_mustBeSet(mustBeSet), m_mustBeClear(mustBeClear)
    {
    }

    KindOfMaskType m_mustBeSet;
    KindOfMaskType m_mustBeClear;
};

class PartitionFilterPlayer : public PartitionFilter
{
  public:
    PartitionFilterPlayer(Player *player, Bool match) : m_player(player), m_match(match)
    {
    }

    Player *m_player;
    Bool m_match;
};

class PartitionFilterOnMap : public PartitionFilter
{
  public:
    PartitionFilterOnMap()
    {
    }
};

class PartitionManager
{
  public:
    Object *getClosestObject(const Coord3D *searchPosition, Real radius, Int from,
                             PartitionFilter *filters);
};

extern GameLogic *TheGameLogic;
extern NameKeyGenerator *TheNameKeyGenerator;
extern GlobalData *TheWritableGlobalData;
extern PartitionManager *ThePartitionManager;

class Xfer;

class WorkOrder
{
  public:
    enum Magic
    {
        GLUE
    };
    void *operator new(unsigned n, Magic)
    {
        return ::operator new(n);
    }

  protected:
    virtual ~WorkOrder();
    virtual void loadPostProcess();
    virtual void crc(Xfer *);
    virtual void xfer(Xfer *);

  public:
    const ThingTemplate *m_thing;
    ObjectID m_factoryID;
    WorkOrder *m_next;
    int m_numCompleted, m_numRequired;
    bool m_required, m_isResourceGatherer;
    WorkOrder() : m_thing(0), m_factoryID(0), m_next(0), m_numCompleted(0), m_numRequired(1)
    {
        m_isResourceGatherer = false;
    }
};
class TeamInQueue
{
  public:
    enum Magic
    {
        GLUE
    };
    void *operator new(unsigned n, Magic)
    {
        return ::operator new(n);
    }

  protected:
    virtual ~TeamInQueue();
    virtual void loadPostProcess();
    virtual void crc(Xfer *);
    virtual void xfer(Xfer *);

  public:
    struct BuildLinks
    {
        TeamInQueue *prev, *next;
        BuildLinks() : prev(0), next(0)
        {
        }
        ~BuildLinks()
        {
        }
    };
    struct ReadyLinks
    {
        TeamInQueue *prev, *next;
        ReadyLinks() : prev(0), next(0)
        {
        }
        ~ReadyLinks()
        {
        }
    };
    BuildLinks m_buildLinks;
    ReadyLinks m_readyLinks;
    WorkOrder *m_workOrders;
    bool m_priorityBuild;
    Team *m_team;
    TeamInQueue *m_nextTeamInQueue;
    unsigned m_frameStarted;
    bool m_sentToStartLocation, m_stopQueueing, m_reinforcement;
    ObjectID m_reinforcementID;
    TeamInQueue()
        : m_workOrders(0), m_team(0), m_nextTeamInQueue(0), m_frameStarted(0), m_reinforcementID(0)
    {
        m_priorityBuild = false;
        m_sentToStartLocation = false;
        m_stopQueueing = false;
        m_reinforcement = false;
    }
    TeamInQueue *next();
    bool isInList(TeamInQueue *const *head) const
    {
        return *head == this || m_buildLinks.prev || m_buildLinks.next;
    }
    void prepend(TeamInQueue **head)
    {
        m_buildLinks.next = *head;
        if (*head)
            (*head)->m_buildLinks.prev = this;
        *head = this;
    }
};
class ScriptEngine
{
  public:
    void AppendDebugMessage(const AsciiString &, bool);
};
extern ScriptEngine *TheScriptEngine;
class ThingFactory
{
  public:
    char p00[8];
    const ThingTemplate *m_first;
    const ThingTemplate *firstTemplate()
    {
        return m_first;
    }
};
extern ThingFactory *TheThingFactory;
class AIPlayer
{
  public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual bool startTraining(WorkOrder *, bool, AsciiString);
    TeamInQueue *m_buildQueue, *m_readyQueue;
    Player *m_player;
    char p10[0x24 - 0x10];
    unsigned m_teamDelay;
    void prependTo_TeamBuildQueue(TeamInQueue *o)
    {
        if (!o->isInList(&m_buildQueue))
            o->prepend(&m_buildQueue);
    }

  protected:
    Object *findFactory(const ThingTemplate *, bool, int *);

  protected:
    void checkForSupplyCenter(BuildListInfo *, Object *);
    void queueSupplyTruck();
};
void AIPlayer::queueSupplyTruck(void)
{
    Bool truckInQueue = false;
    for (TeamInQueue *queued = m_buildQueue; queued; queued = queued->next())
    {
        TeamInQueue *team = queued;
        WorkOrder *order;
        for (order = team->m_workOrders; order; order = order->m_next)
        {
            // GLA dozers (workers) are also resource gatherers, so make sure it isn't a worker.
            // jba.
            if (order->m_isResourceGatherer)
            {
                truckInQueue = true;
            }
        }
    }

    if (truckInQueue)
    {
        return; // already building a supply truck.
    }
    Int totalHarvesters = 0;

    // See how many harvesters we have servicing this supply src.
    // Scan my units.
    Player::PlayerTeamList::const_iterator it;
    for (it = m_player->getPlayerTeams()->begin(); it != m_player->getPlayerTeams()->end(); ++it)
    {
        for (DLINK_ITERATOR<Team> iter = (*it)->iterate_TeamInstanceList(); !iter.done();
             iter.advance())
        {
            Team *team = iter.cur();
            if (!team)
            {
                continue;
            }
            for (DLINK_ITERATOR<Object> objIter = team->iterate_TeamMemberList(); !objIter.done();
                 objIter.advance())
            {
                Object *obj = objIter.cur();
                if (!obj)
                    continue;
                if (!view(obj)->isKindOf(KINDOF_HARVESTER))
                    continue;
                if (!view(obj)->getAI())
                    continue;

                SupplyTruckAIInterface *supplyTruckAI =
                    view(obj)->getAI()->getSupplyTruckAIInterface();
                if (supplyTruckAI)
                {
                    totalHarvesters++;
                }
            }
        }
    }

    /* Find the info building this. */
    for (BuildListInfo *info = m_player->getBuildList(); info; info = info->getNext())
    {
        if (info->isSupplyBuilding() == false)
            continue;
        Int desiredGatherers = info->getDesiredGatherers();
        Int curGatherers = info->getCurrentGatherers();

        if (curGatherers >= desiredGatherers)
        {
            // Check & see if any have died.
            Object *supplyCenter = TheGameLogic->findObjectByID(info->getObjectID());
            // Check for supplies.
            if (supplyCenter)
            {
                if (view(supplyCenter)->isKindOf(KINDOF_REBUILD_HOLE))
                {
                    continue; // don't consider rebuild holes.
                }
                // Make sure we have a supplies near it.
                Coord3D center;
                center.x = view(supplyCenter)->getPosition()->x;
                center.y = view(supplyCenter)->getPosition()->y;
                center.z = view(supplyCenter)->getPosition()->z;
                Real radius =
                    SUPPLY_CENTER_CLOSE_DIST + view(supplyCenter)->getBoundingCircleRadius();

                Object *supplySource;
                {
                    PartitionFilterOnMap filterMapStatus;
                    PartitionFilterPlayer f2(m_player, false);
                    PartitionFilterAcceptByKindOf f1(KindOfMaskType(KindOfMaskType::kInit, 85),
                                                     KINDOFMASK_NONE);
                    PartitionFilter *filters = f1.link(f2.link(&filterMapStatus));
                    supplySource =
                        ThePartitionManager->getClosestObject(&center, radius, 1, filters);
                }
                if (!supplySource)
                {
                    // No supplies.
                    continue;
                }
                static const NameKeyType key_warehouseUpdate =
                    TheNameKeyGenerator->nameToKey("SupplyWarehouseDockUpdate");
                SupplyWarehouseDockUpdate *warehouseModule =
                    (SupplyWarehouseDockUpdate *)view(supplySource)
                        ->findUpdateModule(key_warehouseUpdate);
                if (warehouseModule)
                {
                    Int availableCash = TheWritableGlobalData->m_baseValuePerSupplyBox *
                                        warehouseModule->getBoxesStored();
                    if (availableCash <= 0)
                        continue;
                    if (m_player->getRelationship(view(supplySource)->getTeam()) == ENEMIES)
                    {
                        continue;
                    }
                }
                // Ok, it has supplies available near it.
                checkForSupplyCenter(info, supplyCenter);
                Int curGatherers = 0;
                // See how many harvesters we have servicing this supply src.
                // Scan my units.
                Player::PlayerTeamList::const_iterator it;
                for (it = m_player->getPlayerTeams()->begin();
                     it != m_player->getPlayerTeams()->end(); ++it)
                {
                    for (DLINK_ITERATOR<Team> iter = (*it)->iterate_TeamInstanceList();
                         !iter.done(); iter.advance())
                    {
                        Team *team = iter.cur();
                        if (!team)
                        {
                            continue;
                        }
                        for (DLINK_ITERATOR<Object> objIter = team->iterate_TeamMemberList();
                             !objIter.done(); objIter.advance())
                        {
                            Object *obj = objIter.cur();
                            if (!obj)
                                continue;
                            if (!view(obj)->isKindOf(KINDOF_HARVESTER))
                                continue;
                            if (!view(obj)->getAI())
                                continue;

                            SupplyTruckAIInterface *supplyTruckAI =
                                view(obj)->getAI()->getSupplyTruckAIInterface();
                            if (supplyTruckAI)
                            {
                                ObjectID dock = supplyTruckAI->getPreferredDockID();
                                if (dock == view(supplyCenter)->getID())
                                {
                                    curGatherers++;
                                    if (!supplyTruckAI->isCurrentlyFerryingSupplies())
                                    {
                                        // Note - although this is the ai, we are sending in
                                        // CMD_FROM_PLAYER. This causes the dock object to stick in
                                        // the docking interface. The supply truck ai issues dock
                                        // commands, and they become confused. Thus, player.  jba.
                                        // ;(
                                        view(obj)->getAI()->aiDock(supplyCenter, CMD_FROM_PLAYER);
                                    }
                                }
                            }
                        }
                    }
                }
                // DEBUG_LOG(("Expected %d harvesters, found %d, need %d\n",
                // info->getDesiredGatherers(), 	curGatherers,
                //info->getDesiredGatherers()-curGatherers) );
                info->setCurrentGatherers(curGatherers);
            }
        }
        else
        {
            /* See if we have any "loose" harvesters (cause my supply center got nuked.) */
            Player::PlayerTeamList::const_iterator it;
            for (it = m_player->getPlayerTeams()->begin(); it != m_player->getPlayerTeams()->end();
                 ++it)
            {
                for (DLINK_ITERATOR<Team> iter = (*it)->iterate_TeamInstanceList(); !iter.done();
                     iter.advance())
                {
                    Team *team = iter.cur();
                    if (!team)
                        continue;
                    for (DLINK_ITERATOR<Object> objIter = team->iterate_TeamMemberList();
                         !objIter.done(); objIter.advance())
                    {
                        Object *obj = objIter.cur();
                        if (!obj)
                            continue;
                        if (!view(obj)->isKindOf(KINDOF_HARVESTER))
                            continue;
                        if (!view(obj)->getAI())
                            continue;

                        SupplyTruckAIInterface *supplyTruckAI =
                            view(obj)->getAI()->getSupplyTruckAIInterface();
                        if (supplyTruckAI)
                        {
                            ObjectID dock = supplyTruckAI->getPreferredDockID();
                            if (TheGameLogic->findObjectByID(dock) != NULL)
                                continue;
                            if (supplyTruckAI->isCurrentlyFerryingSupplies() ||
                                supplyTruckAI->isForcedIntoWantingState())
                            {
                                // This thinks he is a gatherer, but doesn't have a preferred dock
                                // id.
                                Object *center = TheGameLogic->findObjectByID(info->getObjectID());
                                if (center)
                                {
                                    info->setCurrentGatherers(info->getCurrentGatherers() + 1);
                                    // Note - although this is the ai, we are sending in
                                    // CMD_FROM_PLAYER. This causes the dock object to stick in the
                                    // docking interface. The supply truck ai issues dock commands,
                                    // and they become confused. Thus, player.  jba.  ;(
                                    view(obj)->getAI()->aiDock(center, CMD_FROM_PLAYER);
                                    DEBUG_LOG(("Re-attaching supply truck to supply center.\n"));
                                    return;
                                }
                            }
                        }
                    }
                }
            }
            if (totalHarvesters >= desiredGatherers * 3)
            {
                continue; // we got lotsa gatherers.
            }
            Bool canBuildUnits = m_player->getCanBuildUnits();
            // If we need a supply truck thingy, turn on unit building for a moment.
            m_player->setCanBuildUnits(true);
            const ThingTemplate *tTemplate = TheThingFactory->firstTemplate();
            while (tTemplate)
            {
                Bool isSupplyTruck = tTemplate->isKindOf(KINDOF_HARVESTER);
                ;
                if (isSupplyTruck)
                {
                    Object *factory = findFactory(tTemplate, false, 0);
                    if (factory)
                    {
                        // we can build one.
                        WorkOrder *order = newInstance(WorkOrder);
                        order->m_thing = tTemplate;
                        order->m_factoryID = 0;
                        order->m_numRequired = 1;
                        order->m_required = true;
                        order->m_isResourceGatherer = true;
                        // prepend to head of list
                        order->m_next = NULL;
                        TeamInQueue *team = newInstance(TeamInQueue);
                        // Put in front of queue.
                        prependTo_TeamBuildQueue(team);
                        team->m_priorityBuild = true;
                        team->m_workOrders = order;
                        team->m_frameStarted = TheGameLogic->getFrame();
                        // Stick it on the default team
                        team->m_team = m_player->getDefaultTeam();
                        AsciiString teamName = "Supply truck - building one at the ";
                        const AsciiString &factoryName = view(factory)->getTemplate()->getName();
                        teamName.concat(factoryName);
                        TheScriptEngine->AppendDebugMessage(teamName, false);
                        m_teamDelay = 0;
                        if (info->getCurrentGatherers() == -1)
                        {
                            // First one is automatic. jba.
                            order->m_factoryID = view(factory)->getID();
                            info->setCurrentGatherers(0);
                        }
                        else
                        {
                            startTraining(order, team->m_priorityBuild, team->m_team->getName());
                        }
                        break;
                    }
                }
                tTemplate = tTemplate->friend_getNextTemplate();
            }
            m_player->setCanBuildUnits(canBuildUnits);
        }
    }
}
