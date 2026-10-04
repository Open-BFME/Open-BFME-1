// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Source/GameLogic/Object
// AI::findClosestRepulsor, retail RVA 0x0014B090, 154 bytes.
// Evidence: targets/game/reverse/identity_evidence/0014b090-ai-repulsor.md.
// Identity: five typed callers recorded in reverse/reloc_names.csv name this
// method through ILT 0x0002BDB4; the guard reads TAiData::m_enableRepulsors.
// The Repulsor vtable at VA 0x01095704 names the matched allow body at
// RVA 0x001DDB10 through ILT 0x0001CC6F. Its self pointer is at +8.
// The address-named filter constructor at 0x001DCBB0 returns this and stores
// the input object's controlling player at +8 and the byte argument at +12.
// PartitionFilter::link (0x009F2AE0) appends next at +4 and returns the head;
// the four-argument manager wrapper at 0x009F26A0 returns the Object result.
//
// Both filters must be full-expression temporaries. This preserves the first
// constructor's return pointer for link and keeps both filters alive through
// the query, reproducing the two EH states without an extra address LEA.
// Object and Thing use their canonical layout header. The subsystem manifest
// has only a registration-only AI stub, not a declaration of this method.

typedef bool Bool;
#define THING_TU_MEMBERS const Coord3D *getPosition() const { return (const Coord3D *)m_cachedPos; }
#include "object.h"
#undef THING_TU_MEMBERS

class TAiData {
public:
    unsigned char m_padding[0x64];
    Bool m_enableRepulsors;
};
class AI {
public:
    TAiData *getAiData() { return *(TAiData **)((char *)this + 0x14); }
    Object *findClosestRepulsor(const Object *, Real);
};
class PartitionFilter {
public:
    PartitionFilter() : m_next(0) {}
    virtual ~PartitionFilter() {}
    virtual Bool allow(Object *) = 0;
    virtual Int getPlayerMask();
    PartitionFilter *link(PartitionFilter *next);
    PartitionFilter *m_next;
};
class Rva001DCBB0Filter : public PartitionFilter {
public:
    Rva001DCBB0Filter(Object *, unsigned char);
    virtual Bool allow(Object *);
    unsigned char m_storage[8];
};
class PartitionFilterRepulsor : public PartitionFilter {
public:
    PartitionFilterRepulsor(const Object *object) : m_self(object) {}
protected:
    virtual Bool allow(Object *);
private:
    const Object *m_self;
};
class PartitionManager {
public:
    Object *getClosestObject(const Coord3D *, Real, int, PartitionFilter *);
};
extern PartitionManager *ThePartitionManager;
Object *AI::findClosestRepulsor(const Object *me, Real range) {
    if (!getAiData()->m_enableRepulsors) return 0;
    return ThePartitionManager->getClosestObject(me->getPosition(), range, 1,
        PartitionFilterRepulsor(me).link(&Rva001DCBB0Filter((Object *)me, 0)));
}
