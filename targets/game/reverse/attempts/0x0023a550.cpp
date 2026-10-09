// ?rva0023a550@Rva0023A550HordeContain@@QAE_NPAUCoord3D@@@Z
// partial score=0.7467 date=2026-10-09
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc /Igame/GameEngine/Source /Igame/Libraries/Include/Lib
// stlport
// HordeContain secondary-interface slot 128; semantic method name is unknown.
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>
#include <set>
#include <hash_map>
#include <Coord3D.h>
#define BFME_HAVE_COORD3D
#include "GameLogic/Object/object.h"
#include "Common/Thing/GameLogicObjectLookup.h"

struct BfmeLinearCoord3D;
class BFMERopeDrawableGetPositionShim
{
public:
    const BfmeLinearCoord3D *getPositionLinear() const;
};

struct BfmeMemberIndexNode
{
    unsigned int m_color;
    BfmeMemberIndexNode *m_parent;
    BfmeMemberIndexNode *m_next;
    BfmeMemberIndexNode *m_right;
    unsigned int m_key;
};


extern GameLogic *TheGameLogic;

class Rva0023A550HordeContain
{
public:
    bool rva0023a550(Coord3D *position);
private:
    _STL::list<Object *> &memberList() const
    {
        return *(_STL::list<Object *> *)((char *)this - 0xac);
    }
    char m_head[0x30];
    _STL::set<ObjectID> m_memberIndex;
};

// ?rva0023a550@Rva0023A550HordeContain@@QAE_NPAUCoord3D@@@Z
bool Rva0023A550HordeContain::rva0023a550(Coord3D *position)
{
    position->x = 0.0f;
    position->y = 0.0f;
    position->z = 0.0f;
    _STL::list<Object *>::iterator node = memberList().begin();
    float count = 0.0f;
    while (node != memberList().end())
    {
        Object *object = *node;
        if (object && object->getDrawable())
        {
            const Coord3D *p = (const Coord3D *)((const BFMERopeDrawableGetPositionShim *)object->getDrawable())->getPositionLinear();
            position->x += p->x;
            position->y += p->y;
            position->z += p->z;
            count += 1.0f;
        }
        ++node;
    }
    _STL::set<ObjectID>::const_iterator entry = m_memberIndex.begin();
    while (entry != m_memberIndex.end())
    {
        ObjectID key = *entry;
        if (key)
        {
            ObjectPtrHash &hash = *(ObjectPtrHash *)((char *)TheGameLogic + 0xb0);
            ObjectPtrHash::iterator found = hash.find((int)key);
            Object *object = found != hash.end() ? found->second : 0;
            if (object && object->getDrawable())
            {
                const Coord3D *p = (const Coord3D *)((const BFMERopeDrawableGetPositionShim *)object->getDrawable())->getPositionLinear();
                position->x += p->x;
                position->y += p->y;
                position->z += p->z;
                count += 1.0f;
            }
        }
        ++entry;
    }
    if (count == 0.0f)
        return false;
    float scale = 1.0f / count;
    position->x *= scale;
    position->y *= scale;
    position->z *= scale;
    return true;
}
