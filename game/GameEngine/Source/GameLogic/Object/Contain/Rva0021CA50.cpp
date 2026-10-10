// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source/Common/Thing
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <list>
#include <map>
#include <GameLogicObjectLookup.h>

// ?findObjectByID@GameLogic@@QAEPAVObject@@H@Z present-unmatched
inline Object *GameLogic::findObjectByID(int id)
{
    if (id == 0) return 0;
    ObjectPtrHash::iterator it = m_objHash.find(id);
    if (it == m_objHash.end()) return 0;
    return (*it).second;
}
extern GameLogic *TheGameLogic;
class XferException
{
public:
    XferException(int tag, const char *format, ...);
    XferException(const XferException &that);
    ~XferException();
    char *text;
    int tag;
};
class Object
{
public:
    virtual void slot00();
    unsigned char m_beforeFlags[0x90];
    unsigned int m_flags94;
    unsigned char m_beforeOwner[0x214-0x98];
    Object *m_owner214;
};
// The value copy at 0x0021AAA0 copies key, target and the count/padding word.
// 0x0021B960 reads target at node+0x14 and updates the count byte at node+0x18.
struct ContestableMapEntry
{
    Object *m_object;
    unsigned char m_count;
};
// The load loop reads both object-ID words at list-node +8 and +12.
struct ContestableRecord
{
    int a[2];
};
// The existing unsigned tree binding shares the decoded pointer-value ABI.
struct Rva0021BE20Value { char m_body[8]; };
typedef _STL::pair<const unsigned int, Rva0021BE20Value> Rva0021BE20Pair;
typedef _STL::_Rb_tree<unsigned int, Rva0021BE20Pair,
    _STL::_Select1st<Rva0021BE20Pair>, _STL::less<unsigned int>,
    _STL::allocator<Rva0021BE20Pair> > Rva0021BE20Tree;
namespace _STL
{
template <> Rva0021BE20Tree::iterator
Rva0021BE20Tree::_M_insert(_Rb_tree_node_base *, _Rb_tree_node_base *,
    const Rva0021BE20Pair &, _Rb_tree_node_base *);
}
class Rva00225960Owner { public: void rva00225960(); };
void j_00248c40();
// This member-pointer view preserves ECX across the existing jump body.
union Rva00248C40Call
{
    void (__cdecl *function)();
    void (Rva00225960Owner::*member)();
};
class Rva0021B960Owner { public: void rva0021b960(); };
class Rva0021CA50
{
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20(); virtual void slot21(); virtual void slot22();
    virtual void addOrRemoveObjFromWorld(Object *object, bool add, bool unused);
    void method();
private:
    char m_beforeOwner[4];
    Object *m_owner;
    char m_unreconstructed_00c[0x9bc-0xc];
    _STL::list<Object *> m_contestList;
    _STL::list<int> m_contestListShadow;
    _STL::map<Object *, ContestableMapEntry> m_objectData;
    _STL::list<ContestableRecord> m_records;
};

// ?method@Rva0021CA50@@QAEXXZ
void Rva0021CA50::method()
{
    Rva00248C40Call base;
    base.function = &j_00248c40;
    (((Rva00225960Owner *)this)->*base.member)();
    Object *owner = m_owner;
    if (!m_contestList.empty())
        throw XferException(5, 0);
    for (_STL::list<int>::iterator it = m_contestListShadow.begin(); it != m_contestListShadow.end(); ++it)
    {
        Object *object = TheGameLogic->findObjectByID(*it);
        if (!object)
            throw XferException(5, 0);
        m_contestList.push_back(object);
        if (object->m_flags94 & 0x10000000)
            addOrRemoveObjFromWorld(object, false, false);
        object->m_owner214 = owner;
    }
    m_contestListShadow.clear();
    for (_STL::list<ContestableRecord>::iterator it = m_records.begin(); it != m_records.end(); ++it)
    {
        Object *object = TheGameLogic->findObjectByID(it->a[0]);
        if (!object)
            throw XferException(5, 0);
        Object *target = 0;
        if (it->a[1])
        {
            target = TheGameLogic->findObjectByID(it->a[1]);
            if (!target)
                throw XferException(5, 0);
        }
        ContestableMapEntry entry;
        entry.m_object = target;
        entry.m_count = 0;
        reinterpret_cast<Rva0021BE20Tree *>(&m_objectData)->insert_unique(_STL::make_pair(reinterpret_cast<unsigned int>(object), reinterpret_cast<const Rva0021BE20Value &>(entry)));
    }
    ((Rva0021B960Owner *)this)->rva0021b960();
    m_records.clear();
}
