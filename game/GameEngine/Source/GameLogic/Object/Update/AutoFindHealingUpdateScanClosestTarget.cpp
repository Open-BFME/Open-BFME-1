// ?scanClosestTarget@AutoFindHealingUpdate@@QAEPAVObject@@XZ
// Retail RVA 0x00281640, 286 bytes. The matched update() caller reaches
// this function through ILT 0x00036787 with the primary module pointer.
// BFME returns the existing BfmeWideResult ABI, not the retained ZH
// ObjectIterator. Its descriptor is vector/start/end/capacity plus cursor
// at +0x0c and reference count at +0x10; entries are eight bytes.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Benchmark /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// Include STL before PreRTS/STLTypedefs forces the ZH new allocator.
// Retail releases vector storage with the canonical node allocator.
#define _STLP_USE_STATIC_LIB 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "PreRTS.h"
#include "GameLogic/Module/AutoFindHealingUpdate.h"
#include "GameLogic/Object.h"
#include "GameLogic/ObjectIter.h"
#include "GameLogic/PartitionManager.h"


struct HealingEntry
{
    Object *object;
    unsigned int unknown04;
};
struct HealingResultData
{
    std::vector<HealingEntry> entries;
    HealingEntry *current;
    int references;
};
struct BfmeWideResult
{
    HealingResultData *m_value;
    BfmeWideResult();
    BfmeWideResult(const BfmeWideResult &);
    ~BfmeWideResult()
    {
        if (--m_value->references == 0)
            delete m_value;
    }
    Object *next()
    {
        if (m_value->current == m_value->entries.end())
            return 0;
        return (m_value->current++)->object;
    }
};
class BfmeWideForwardA
{
public:
    BfmeWideResult bfmeForwardWideA(int, int, int, int);
};

// The BFME template bit tested here is byte +0xcc, mask 1. Keep this
// layout local rather than assuming the retained ZH template mask layout.
static bool healingPadKind(const Object *object)
{
    const Overridable *type = *(const Overridable *const *)((const char *)object + 4);
    if (type)
        type = type->getFinalOverride();
    return (*(const unsigned char *)((const char *)type + 0xcc) & 1) != 0;
}

Object *AutoFindHealingUpdate::scanClosestTarget()
{
    const AutoFindHealingUpdateModuleData *data =
        *reinterpret_cast<const AutoFindHealingUpdateModuleData **>(
            reinterpret_cast<char *>(this) + 4);
    Object *me = *reinterpret_cast<Object **>(reinterpret_cast<char *>(this) + 8);
    Object *bestTarget = NULL;
    Real closestDistSqr = 0;
    const Coord3D *position = me->getPosition();
    BfmeWideResult iter = ((BfmeWideForwardA *)ThePartitionManager)->
        bfmeForwardWideA((int)position, *(int *)&data->m_scanRange, 0, 0);
    while (Object *other = iter.next()) {
        if (!healingPadKind(other))
            continue;
        Real dx = position->x - other->getPosition()->x;
        Real dy = position->y - other->getPosition()->y;
        Real distSqr = dx * dx + dy * dy;
        if (bestTarget == NULL || distSqr < closestDistSqr) {
            bestTarget = other;
            closestDistSqr = distSqr;
        }
    }
    return bestTarget;
}
