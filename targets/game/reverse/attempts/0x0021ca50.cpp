// ?method@Rva0021CA50@@QAEXXZ
// partial score=1.0 date=2026-10-08
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
class Rva00225960Owner { public: void rva00225960(); };
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
    ((Rva00225960Owner *)this)->rva00225960();
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
        m_objectData.insert(_STL::make_pair(object, entry));
    }
    ((Rva0021B960Owner *)this)->rva0021b960();
    m_records.clear();
}
