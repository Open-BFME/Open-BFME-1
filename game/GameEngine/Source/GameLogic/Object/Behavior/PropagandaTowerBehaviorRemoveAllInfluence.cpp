// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// The primary vtable slot 11 removes the tracked effects before deleting the list.
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

class Object;
class PropagandaTowerBehaviorModuleData;
typedef int ObjectID;
typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>,
    _STL::equal_to<ObjectID> > ObjectPtrHash;

class Rva00203570Logic
{
public:
    Object *find(ObjectID id)
    {
        if (id == 0)
            return 0;
        ObjectPtrHash::iterator found = m_objects.find(id);
        if (found == m_objects.end())
            return 0;
        return found->second;
    }
private:
    unsigned char m_prefix[0xb0];
    ObjectPtrHash m_objects;
};

class Rva00203570Tracker
{
public:
    virtual ~Rva00203570Tracker();
    ObjectID objectID;
    Rva00203570Tracker *next;
};

class PropagandaTowerBehavior
{
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02();
    virtual void slot03(); virtual void slot04(); virtual void slot05();
    virtual void slot06(); virtual void slot07(); virtual void slot08();
    virtual void slot09(); virtual void slot10();
protected:
    virtual void removeAllInfluence();
    virtual void doScan();
    virtual void effectLogic(Object *, bool,
        const PropagandaTowerBehaviorModuleData *);
private:
    const PropagandaTowerBehaviorModuleData *m_moduleData;
    unsigned char m_prefix08[0x20];
    Rva00203570Tracker *m_insideList;
};

#define TheLogic (*(Rva00203570Logic **)0x012F0898)

void PropagandaTowerBehavior::removeAllInfluence()
{
    Rva00203570Tracker *current = m_insideList;
    if (current)
    {
        Rva00203570Logic *logic = TheLogic;
        do
        {
            Object *object = logic->find(current->objectID);
            if (object)
            {
                effectLogic(object, false, m_moduleData);
                logic = TheLogic;
            }
            current = current->next;
        } while (current);
    }
    while (m_insideList)
    {
        Rva00203570Tracker *next = m_insideList->next;
        delete m_insideList;
        m_insideList = next;
    }
}
