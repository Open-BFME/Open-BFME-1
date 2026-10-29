// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source/GameLogic/Object /Igame/GameEngine/Source/Common/System
// stlport

// Retail 0x0024ABA0 (559 bytes, thiscall, Xfer* argument, ret 4). Primary-vtable slot
// +0C of the table that the HordeSiegeEngineContain constructor (0x0024A560) installs
// reaches it through ILT 0x0003E99B, and the Snapshot transfer caller 0x009D6410 passes
// the Xfer in its one stack argument. It transfers the version, the +EC object list
// (as ObjectIDs), the +F0 count, the +F4 flag and the +F8 int map. The EA method name
// is not proven, so the class and method keep opaque names. Evidence:
// targets/game/reverse/identity_evidence/0024aba0-native-transfer.md.
//
// Frame shape: one function-scope objectID shared by both list loops wins the dead Xfer
// argument slot; the map count is a separate local in each branch; the save loop copies
// key and value into two locals so the load loop's key and value share their slots;
// the two-byte version sits in a four-byte wrapper so it keeps frame slot -16.
#define _STLP_NO_EXCEPTIONS 1
#include "object.h"
#include "xfer.h"
#include <list>
#include <map>

typedef Xfer Rva0024ABA0Target;
typedef Xfer::Version Rva0024ABA0Pair;
struct Rva0024ABA0Pair44 { Rva0024ABA0Pair p; unsigned char pad[2]; };
typedef std::list<Object *> Rva0024ABA0List;
typedef std::list<int> Rva0024ABA0ValueList;
struct Rva00226FA0Less : std::less<int> {};
typedef std::map<int, int, Rva00226FA0Less> Rva0024ABA0Map;

class BfmeSeedTarget;
class Gen_0024B870 { public: void bfmeSeed(BfmeSeedTarget *target); };
class MidVirtualSlot90Receiver;
Xfer &Rva0010C3C0(MidVirtualSlot90Receiver *target, void *context);
class GameLogic { public: void destroyObject(Object *object); };
// Retail 0x012F0898 is ?TheGameLogic@@3PAVGameLogic@@A (data_rows.csv,
// GameLogic.cpp); TheBfmeGameLogic was only a pin nothing defines.
extern GameLogic *TheGameLogic;
#define TheBfmeGameLogic TheGameLogic

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
    Rva0024ABA0Pair44 versionStorage;
    Rva0024ABA0Pair &version = versionStorage.p;
    version.data[0] = 1;
    version.data[1] = 1;
    *target == version;
    int objectID;
    if (target->IsStoring())
    {
        *target == m_valueF0;
        for (Rva0024ABA0List::iterator it = m_listA.begin(); it != m_listA.end(); ++it)
        {
            objectID = (*it)->m_id;
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
            Rva0010C3C0((MidVirtualSlot90Receiver *)target, &objectID);
            m_listB.push_back(objectID);
        }
    }
    *target == m_valueF4;
    if (target->IsStoring())
    {
        int count = m_map.size();
        *target == count;
        for (Rva0024ABA0Map::iterator it = m_map.begin(); it != m_map.end(); ++it)
        {
            int key = it->first;
            int value = it->second;
            Rva0010C3C0((MidVirtualSlot90Receiver *)target, &key);
            *target == value;
        }
    }
    else
    {
        int count;
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
