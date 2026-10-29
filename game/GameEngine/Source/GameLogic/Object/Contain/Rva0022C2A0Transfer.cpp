// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source/GameLogic/Object /Igame/GameEngine/Source/Common/System
// stlport

// Retail 0x0022C2A0 (559 bytes, thiscall, Xfer* argument, ret 4). Slot +0C of the
// primary vtable 0x010AD088 that the SiegeEngineContain constructor (0x0022BC50)
// installs reaches it through ILT 0x00016027. It is the field-for-field twin of
// Rva0024ABA0::method (0x0024ABA0, HordeSiegeEngineContain) with every field eight
// bytes lower and Gen_0022CD40::bfmeSeed as the leading call: it transfers the
// version, the +E4 object list (as ObjectIDs), the +E8 count, the +EC flag and the
// +F0 int map. The EA method name is not proven (identity_evidence/
// 0022c2a0-masm-codegen-blocker.md), so the class and method keep opaque names.
//
// Frame shape (the former MASM blocker): one function-scope objectID shared by both
// list loops wins the dead Xfer argument slot; the map count is a separate local in
// each branch; the save loop copies key and value into two locals so the load loop's
// key and value share their slots; the two-byte version sits in a four-byte wrapper.
#define _STLP_NO_EXCEPTIONS 1
#include "object.h"
#include "xfer.h"
#include <list>
#include <map>

typedef Xfer Rva0022C2A0Target;
typedef Xfer::Version Rva0022C2A0Pair;
struct Rva0022C2A0Pair44 { Rva0022C2A0Pair p; unsigned char pad[2]; };
typedef std::list<Object *> Rva0022C2A0List;
typedef std::list<int> Rva0022C2A0ValueList;
struct Rva00226FA0Less : std::less<int> {};
typedef std::map<int, int, Rva00226FA0Less> Rva0022C2A0Map;

class BfmeSeedTarget;
class Gen_0022CD40 { public: void bfmeSeed(BfmeSeedTarget *target); };
class MidVirtualSlot90Receiver;
Xfer &Rva0010C3C0(MidVirtualSlot90Receiver *target, void *context);
class GameLogic { public: void destroyObject(Object *object); };
// Retail 0x012F0898 is ?TheGameLogic@@3PAVGameLogic@@A (data_rows.csv,
// GameLogic.cpp); TheBfmeGameLogic was only a pin nothing defines.
extern GameLogic *TheGameLogic;
#define TheBfmeGameLogic TheGameLogic

class Rva0022C2A0
{
public:
    // ?seed@Rva0022C2A0@@QAEXPAVXfer@@@Z absent-from-retail
    void seed(Rva0022C2A0Target *target)
    {
        ((Gen_0022CD40 *)this)->bfmeSeed((BfmeSeedTarget *)target);
    }
    void method(Rva0022C2A0Target *target);
    char m_unmodelled000[0xe4];
    Rva0022C2A0List m_listA;
    unsigned int m_valueE8;
    bool m_valueEC;
    unsigned char m_unmodelledED[3];
    Rva0022C2A0Map m_map;
    Rva0022C2A0ValueList m_listB;
};

// ?method@Rva0022C2A0@@QAEXPAVXfer@@@Z
void Rva0022C2A0::method(Rva0022C2A0Target *target)
{
    seed(target);
    if (target->IsLightCRC())
        return;
    Rva0022C2A0Pair44 versionStorage;
    Rva0022C2A0Pair &version = versionStorage.p;
    version.data[0] = 1;
    version.data[1] = 1;
    *target == version;
    int objectID;
    if (target->IsStoring())
    {
        *target == m_valueE8;
        for (Rva0022C2A0List::iterator it = m_listA.begin(); it != m_listA.end(); ++it)
        {
            objectID = (*it)->m_id;
            Rva0010C3C0((MidVirtualSlot90Receiver *)target, &objectID);
        }
    }
    else
    {
        if (!m_listA.empty())
        {
            m_valueE8 = 0;
            for (Rva0022C2A0List::iterator it = m_listA.begin(); it != m_listA.end(); )
            {
                Object *object = *it;
                it = m_listA.erase(it);
                TheBfmeGameLogic->destroyObject(object);
            }
            m_listA.clear();
        }
        *target == m_valueE8;
        for (unsigned int i = 0; i < m_valueE8; ++i)
        {
            Rva0010C3C0((MidVirtualSlot90Receiver *)target, &objectID);
            m_listB.push_back(objectID);
        }
    }
    *target == m_valueEC;
    if (target->IsStoring())
    {
        int count = m_map.size();
        *target == count;
        for (Rva0022C2A0Map::iterator it = m_map.begin(); it != m_map.end(); ++it)
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
