// ?doLoadAllTransports@ScriptActions@@IAEXABVAsciiString@@@Z
// partial score=0.83 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringinline
// stlport
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

class AICommandInterface
{
public:
    void aiEnter(Object *object, int source);
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
class BfmeObjectDlinkPad { public: unsigned char m_pad[0x64]; };
class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
    public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
    unsigned int isKindOf(unsigned int kind) const
    {
        const ThingTemplate *value = *(const ThingTemplate * const *)((const char *)this + 4);
        if (!value)
            value = 0;
        else if (value->m_nextOverride)
            value = (const ThingTemplate *)value->m_nextOverride->getFinalOverride();
        return value->isKindOf(kind);
    }
    ObjectID getID() const { return *(const ObjectID *)((const char *)this + 0x74); }
    ContainModuleInterface *getContain() const
    { return *(ContainModuleInterface * const *)((const char *)this + 0x1fc); }
    AIUpdateInterface *getAIUpdateInterface() const
    { return *(AIUpdateInterface * const *)((const char *)this + 0x204); }
    Object *getContainedBy() const
    { return *(Object * const *)((const char *)this + 0x214); }
    int getTransportSlotCount() const;
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
                transports.push_back(_STL::make_pair(object->getID(), contain->getContainMax()));
        }
        else
        {
            Object *container = object->getContainedBy();
            if (container && container->isKindOf(108))
                object = container;
            PairObjectIDAndUInt entry(object->getID(), object->getTransportSlotCount());
            EntriesVec::iterator current = units.begin();
            for (; current != units.end(); ++current)
                if (current->first == entry.first) break;
            if (current == units.end()) units.push_back(entry);
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
                ai->m_command.aiEnter(transport, 1);
        }
    }
}
