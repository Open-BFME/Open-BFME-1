// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringinline
// stlport
// ScriptActions::doLoadAllTransports, retail 0x003014C0 (979 bytes, ret 4).
//
// Identity: ScriptActions::executeAction (0x00303BF0) indexes its jump table
// directly by the action type; arm 52 calls this body twice through its ILT
// thunk.  BFME's table runs one ahead of Zero Hour here (arm 56 is the landed
// doTeamExitAll, ZH TEAM_EXIT_ALL = 55), so arm 52 is TEAM_LOAD_TRANSPORTS
// (ZH 51), and the body is the ZH doLoadAllTransports walk: team members split
// into transports (KINDOF bit 21, ContainModuleInterface::getContainMax) and
// passengers, a PartitionSolver pass, then aiEnter for each pairing.
//
// BFME additions over Zero Hour: a passenger inside a container of KINDOF bit
// 108 is replaced by that container, and duplicate passenger IDs are skipped.
// The ZH `(TransportContain*)obj->getContain()` downcast is what keeps
// retail's add -0x20 / lea +0x20 receiver.  The template is read through the
// OVERRIDE<ThingTemplate>::operator-> shape (explicit NULL return, one level
// of getFinalOverride inlined), which is what gives retail's EDI/ESI colouring.
#define _STLP_NO_EXCEPTIONS 1
#include "StringInline.h"
#include <vector>
#include <hash_map>
#include <utility>

typedef bool Bool;
enum ObjectID { INVALID_ID = 0, FORCE_OBJECTID_TO_LONG_SIZE = 0x7ffffff };
typedef _STL::pair<ObjectID, unsigned int> PairObjectIDAndUInt;
typedef _STL::pair<ObjectID, ObjectID> PairObjectID;
typedef _STL::vector<PairObjectIDAndUInt> EntriesVec;
typedef _STL::vector<PairObjectIDAndUInt> SpacesVec;
typedef _STL::vector<PairObjectID> SolutionVec;
enum SolutionType { PREFER_FAST_SOLUTION = 0, PREFER_CORRECT_SOLUTION = 0x7fffffff };
class PartitionSolver
{
    SolutionType m_howToSolve;
    EntriesVec m_data;
    SpacesVec m_spacesForData;
    SolutionVec m_currentSolution;
    unsigned int m_currentSolutionLeftovers;
    SolutionVec m_bestSolution;
public:
    PartitionSolver(const EntriesVec &, const SpacesVec &, SolutionType);
    ~PartitionSolver();
    void solve();
    const SolutionVec &getSolution() const;
};
class Object;
class Team;

class BfmeStringArgBase
{
    friend class BfmeAsciiStringArg;
private:
    BfmeStringArgBase(const BfmeStringArgBase &);
    ~BfmeStringArgBase();
};

class BfmeAsciiStringArg
{
public:
    BfmeAsciiStringArg(const AsciiString &that)
    {
        ((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
            *(const BfmeStringArgBase *)&that);
    }
    ~BfmeAsciiStringArg();
private:
    char *m_text;
};

class ScriptEngine
{
public:
#define SE_SLOT(n) virtual void slot##n() = 0
    SE_SLOT(00); SE_SLOT(01); SE_SLOT(02); SE_SLOT(03);
    SE_SLOT(04); SE_SLOT(05); SE_SLOT(06); SE_SLOT(07);
    SE_SLOT(08); SE_SLOT(09); SE_SLOT(10); SE_SLOT(11);
    SE_SLOT(12); SE_SLOT(13); SE_SLOT(14); SE_SLOT(15);
    SE_SLOT(16);
#undef SE_SLOT
    virtual Team *getTeamNamed(BfmeAsciiStringArg name, Bool exact = false) = 0;
};
extern ScriptEngine *TheScriptEngine;

class Overridable
{
public:
    virtual ~Overridable();
    const Overridable *getFinalOverride() const;
    Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
    unsigned int isKindOf(unsigned int kind) const
    {
        return m_kindOf[kind >> 5] & (1u << (kind & 31));
    }
private:
    unsigned char m_beforeKindOf[0xc8 - 8];
    unsigned int m_kindOf[6];
};

class ContainModuleInterface
{
public:
#define CO_SLOT(n) virtual void slot##n() = 0
    CO_SLOT(00); CO_SLOT(01); CO_SLOT(02); CO_SLOT(03);
    CO_SLOT(04); CO_SLOT(05); CO_SLOT(06); CO_SLOT(07);
    CO_SLOT(08); CO_SLOT(09); CO_SLOT(10); CO_SLOT(11);
    CO_SLOT(12); CO_SLOT(13); CO_SLOT(14); CO_SLOT(15);
    CO_SLOT(16); CO_SLOT(17); CO_SLOT(18); CO_SLOT(19);
    CO_SLOT(20); CO_SLOT(21); CO_SLOT(22);
#undef CO_SLOT
    virtual unsigned int getContainMax() const = 0;
};

// ZH TransportContain derives from OpenContain, whose primary base occupies
// the first 0x20 bytes; the ContainModuleInterface view sits at +0x20.
class Rva003014C0ContainPrimary
{
public:
    virtual ~Rva003014C0ContainPrimary();
private:
    unsigned char m_pad[0x1c];
};
class TransportContain : public Rva003014C0ContainPrimary, public ContainModuleInterface
{
public:
    virtual unsigned int getContainMax() const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
enum CommandSourceType
{
    CMD_FROM_PLAYER = 0,
    CMD_FROM_SCRIPT,
    CMD_FROM_AI,
    CMD_FROM_DOZER
};

class AICommandInterface
{
public:
    void aiEnter(Object *object, CommandSourceType cmdSource);
};
class AIUpdateInterface
{
    unsigned char m_pad[0x20];
public:
    AICommandInterface m_command;
};

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };
class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
    unsigned char m_carrier[4];
};
class BfmeObjectVtbl { public: virtual void slot0(); };
class BfmeObjectDlinkBase
{
public:
    Object *dlink_next_TeamMemberList() const;
};
class BfmeObjectDlinkPad { public: const ThingTemplate *m_template; unsigned char m_pad[0x60]; };
class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
    public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
    const ThingTemplate *getTemplate() const
    {
        if (!m_template)
            return 0;
        if (m_template->m_nextOverride)
            return (const ThingTemplate *)m_template->m_nextOverride->getFinalOverride();
        return m_template;
    }
    unsigned int isKindOf(unsigned int kind) const
    {
        return getTemplate()->isKindOf(kind);
    }
    ObjectID getID() const { return m_id; }
    ContainModuleInterface *getContain() const { return m_contain; }
    AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
    Object *getObject214() const { return m_object214; }
    int getTransportSlotCount() const;
private:
    unsigned char m_pad070[0x74 - 0x70];
    ObjectID m_id;
    unsigned char m_pad078[0x1fc - 0x78];
    ContainModuleInterface *m_contain;
    unsigned char m_pad200[0x204 - 0x200];
    AIUpdateInterface *m_ai;
    unsigned char m_pad208[0x214 - 0x208];
    Object *m_object214;
};

#define callMemberFunction(object, ptrToMember) ((object).*(ptrToMember))
template<class Type> class DLINK_ITERATOR
{
public:
    typedef Type *(Type::*GetNextFunc)() const;
private:
    Type *m_cur;
    GetNextFunc m_next;
public:
    DLINK_ITERATOR(Type *cur, GetNextFunc next) : m_cur(cur), m_next(next) {}
    void advance() { if (m_cur) m_cur = callMemberFunction(*m_cur, m_next)(); }
    Bool done() const { return m_cur == 0; }
    Type *cur() const { return m_cur; }
};
class Team
{
    void *m_vptr;
    void *m_proto;
    void *m_id;
    Object *m_head;
public:
    DLINK_ITERATOR<Object> iterate_TeamMemberList() const
    { return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList); }
};

typedef _STL::hash_map<int, Object *, _STL::hash<int>, _STL::equal_to<int> > ObjectPtrHash;
class GameLogic
{
    char m_pad[0xb0];
    ObjectPtrHash m_objectHash;
public:
    Object *findObjectByID(ObjectID id)
    {
        if (id == 0) return 0;
        ObjectPtrHash::iterator it = m_objectHash.find((int)id);
        if (it == m_objectHash.end()) return 0;
        return (*it).second;
    }
};
extern GameLogic *TheGameLogic;

class ScriptActions
{
protected:
    void doLoadAllTransports(const AsciiString &name);
};

void ScriptActions::doLoadAllTransports(const AsciiString &name)
{
    Team *team = TheScriptEngine->getTeamNamed(name);
    if (!team) return;
    EntriesVec units;
    SpacesVec transports;
    for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance())
    {
        Object *object = iter.cur();
        if (!object) continue;
        if (object->isKindOf(21))
        {
            ContainModuleInterface *contain = object->getContain();
            if (contain)
                transports.push_back(_STL::make_pair(object->getID(), ((TransportContain *)object->getContain())->getContainMax()));
        }
        else
        {
            Object *container = object->getObject214();
            if (container && container->isKindOf(108))
                object = container;
            PairObjectIDAndUInt entry = _STL::make_pair(object->getID(), object->getTransportSlotCount());
            Bool found = false;
            for (EntriesVec::iterator current = units.begin(); current != units.end(); ++current)
            {
                if (entry.first == current->first)
                {
                    found = true;
                    break;
                }
            }
            if (!found) units.push_back(entry);
        }
    }
    PartitionSolver partition(units, transports, PREFER_FAST_SOLUTION);
    partition.solve();
    SolutionVec solution = partition.getSolution();
    for (int i = 0; i < solution.size(); ++i)
    {
        Object *unit = TheGameLogic->findObjectByID(solution[i].first);
        Object *transport = TheGameLogic->findObjectByID(solution[i].second);
        if (unit && transport)
        {
            AIUpdateInterface *ai = unit->getAIUpdateInterface();
            if (ai)
                ai->m_command.aiEnter(transport, CMD_FROM_SCRIPT);
        }
    }
}

