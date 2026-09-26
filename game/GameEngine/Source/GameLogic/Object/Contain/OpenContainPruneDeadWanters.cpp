// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x00224560. OpenContain::pruneDeadWanters.
// The update caller reaches this body through OpenContain::update.
// GameLogic::findObjectByID uses the matched hash_map layout at this+0xB4.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <map>

typedef int ObjectID;

class Object
{
public:
    bool isEffectivelyDead() const
    {
        return (m_privateStatus & 1) != 0;
    }

private:
    unsigned char m_padding00[0x344];
    unsigned char m_privateStatus;
};

typedef _STL::hash_map<ObjectID, Object *> ObjectPtrHash;

class GameLogic
{
public:
    Object *findObjectByID(ObjectID id)
    {
        if (id == 0)
            return 0;

        ObjectPtrHash::iterator it = m_objHash.find(id);
        if (it == m_objHash.end())
            return 0;

        return (*it).second;
    }

private:
    unsigned char m_padding00[0xb0];
    ObjectPtrHash m_objHash;
};

extern GameLogic *TheGameLogic;

enum ObjectEnterExitType
{
    ObjectEnterExitTypeValue
};

typedef _STL::pair<const ObjectID, ObjectEnterExitType> ObjectEnterExitPair;
typedef _STL::_Rb_tree<ObjectID, ObjectEnterExitPair,
    _STL::_Select1st<ObjectEnterExitPair>, _STL::less<ObjectID>,
    _STL::allocator<ObjectEnterExitPair> > ObjectEnterExitTree;

struct ObjectEnterExitMap
{
    typedef ObjectEnterExitTree::iterator iterator;

    iterator begin()
    {
        return m_tree.begin();
    }

    iterator end()
    {
        return m_tree.end();
    }

    ObjectEnterExitTree m_tree;
};

class OpenContain
{
public:
    void pruneDeadWanters();

private:
    unsigned char m_padding00[0x58];
    ObjectEnterExitMap m_objectEnterExitInfo;
};

void OpenContain::pruneDeadWanters()
{
    for (ObjectEnterExitMap::iterator it = m_objectEnterExitInfo.begin();
        it != m_objectEnterExitInfo.end(); )
    {
        ObjectID id = (*it).first;
        Object *obj = TheGameLogic->findObjectByID(id);
        if (obj == 0 || obj->isEffectivelyDead())
        {
            ObjectEnterExitMap::iterator tmp = it;
            ++it;
            m_objectEnterExitInfo.m_tree.erase(tmp);
        }
        else
        {
            ++it;
        }
    }
}
