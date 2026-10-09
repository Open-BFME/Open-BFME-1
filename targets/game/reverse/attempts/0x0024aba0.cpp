// ?d_0024aba0@@YAXXZ
// partial score=0.975 date=2026-10-09
// Evidence: targets/game/reverse/identity_evidence/0024aba0-native-transfer.md
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source/GameLogic/Object /Igame/GameEngine/Source/Common/System
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include "object.h"
#include "xfer.h"
#include <list>
#include <map>

typedef Xfer Rva0024ABA0Target;
typedef Xfer::Version Rva0024ABA0Pair;
typedef std::list<Object *> Rva0024ABA0List;
typedef std::list<int> Rva0024ABA0ValueList;
struct Rva00226FA0Less : std::less<int> {};
typedef std::map<int, int, Rva00226FA0Less> Rva0024ABA0Map;

class BfmeSeedTarget;
class Gen_0024B870 { public: void bfmeSeed(BfmeSeedTarget *target); };
class MidVirtualSlot90Receiver;
Xfer &Rva0010C3C0(MidVirtualSlot90Receiver *target, void *context);
class GameLogic { public: void destroyObject(Object *object); };
extern GameLogic *TheBfmeGameLogic;

class Rva0024ABA0
{
public:
    // ?seed@Rva0024ABA0@@QAEXPAVXfer@@@Z absent-from-retail
    void seed(Rva0024ABA0Target *target)
    {
        ((Gen_0024B870 *)this)->bfmeSeed((BfmeSeedTarget *)target);
    }
    void method(Rva0024ABA0Target *target);
    char m_unmodelled000[0xec];
    Rva0024ABA0List m_listA;
    unsigned int m_valueF0;
    bool m_valueF4;
    unsigned char m_unmodelledF5[3];
    Rva0024ABA0Map m_map;
    Rva0024ABA0ValueList m_listB;
};

// ?method@Rva0024ABA0@@QAEXPAVXfer@@@Z
void Rva0024ABA0::method(Rva0024ABA0Target *target)
{
    seed(target);
    if (target->IsLightCRC())
        return;
    Rva0024ABA0Pair version;
    version.data[0] = 1;
    version.data[1] = 1;
    *target == version;
    if (target->IsStoring())
    {
        *target == m_valueF0;
        for (Rva0024ABA0List::iterator it = m_listA.begin(); it != m_listA.end(); ++it)
        {
            int objectID = (*it)->m_id;
            Rva0010C3C0((MidVirtualSlot90Receiver *)target, &objectID);
        }
    }
    else
    {
        if (!m_listA.empty())
        {
            m_valueF0 = 0;
            for (Rva0024ABA0List::iterator it = m_listA.begin(); it != m_listA.end(); )
            {
                Object *object = *it;
                it = m_listA.erase(it);
                TheBfmeGameLogic->destroyObject(object);
            }
            m_listA.clear();
        }
        *target == m_valueF0;
        for (unsigned int i = 0; i < m_valueF0; ++i)
        {
            int objectID;
            Rva0010C3C0((MidVirtualSlot90Receiver *)target, &objectID);
            m_listB.push_back(objectID);
        }
    }
    *target == m_valueF4;
    int count;
    if (target->IsStoring())
    {
        count = m_map.size();
        *target == count;
        for (Rva0024ABA0Map::iterator it = m_map.begin(); it != m_map.end(); ++it)
        {
            std::pair<int, int> values = *it;
            Rva0010C3C0((MidVirtualSlot90Receiver *)target, &values.first);
            *target == values.second;
        }
    }
    else
    {
        *target == count;
        for (int i = 0; i < count; ++i)
        {
            int key;
            Rva0010C3C0((MidVirtualSlot90Receiver *)target, &key);
            int value;
            *target == value;
            m_map[key] = value;
        }
    }
}
