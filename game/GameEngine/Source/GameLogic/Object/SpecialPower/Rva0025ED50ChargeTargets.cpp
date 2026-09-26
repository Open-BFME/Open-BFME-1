// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include <list>
#include "PreRTS.h"
#include "Common/GameType.h"
#include "GameLogic/ObjectIter.h"

// Retail RVA 0x0025ED50 is 355 bytes, through the final ret at +0x162.
// The owner is established by the 230-byte matched Rva0025EF90Owner::applyCharge at 0x25EF90,
// which calls this existing typed body at +0x20.
// BFME filters differ from the retained ZH header: virtual destructor, allow,
// getPlayerMask, then next at +4. Vtable targets were independently decoded:
// base C83B5C; object filter C85DD0; root filter C83B80; relationship C85DC0.
// The first two retain address names; the relationship table names its methods.
// Temporary filters die at the end of the iterator-initialization expression,
// before enumeration. VC7.1 permits the address of the class temporary here.
class Object;

class PartitionFilter {
public:
    PartitionFilter() : m_next(0) {}
    virtual ~PartitionFilter() {}
    virtual Bool allow(Object *) = 0;
    virtual int getPlayerMask();

    PartitionFilter *link(PartitionFilter *next);

    PartitionFilter *m_next;
};

class Rva0025ED50ObjectFilter : public PartitionFilter {
public:
    explicit Rva0025ED50ObjectFilter(Object *object)
        : m_object(object) {}
    virtual ~Rva0025ED50ObjectFilter() {}
    virtual Bool allow(Object *);

    Object *m_object;
};

class PartitionFilterRelationship : public PartitionFilter {
public:
    PartitionFilterRelationship(Object *object, Int mode, Bool match)
        : m_obj(object), m_flags(mode), m_match(match) {}
    virtual ~PartitionFilterRelationship() {}
    virtual Bool allow(Object *);
    virtual int getPlayerMask();

    Object *m_obj;
    Int m_flags;
    Bool m_match;
};

class Rva0025ED50RootFilter : public PartitionFilter {
public:
    Rva0025ED50RootFilter() {}
    virtual ~Rva0025ED50RootFilter() {}
    virtual Bool allow(Object *);
};

struct Rva0025ED50Entry {
    Object *object;
    UnsignedInt unknown04;
};

struct Rva0025ED50ResultData {
    std::vector<Rva0025ED50Entry> entries;
    Rva0025ED50Entry *current;
    Int references;
};

struct Rva0025ED50WideResult {
    Rva0025ED50ResultData *value;

    Rva0025ED50WideResult();
    Rva0025ED50WideResult(const Rva0025ED50WideResult &);
    ~Rva0025ED50WideResult()
    {
        if (--value->references == 0)
            delete value;
    }

    Object *next(Object *&object)
    {
        if (value->current == value->entries.end())
            return 0;
        object = (value->current++)->object;
        return object;
    }
};

// The BFME body at 0x009F2960 has a 4-byte hidden return object followed by
// (position, range, order, filter-head, flag).  Its original semantic
// method name is not asserted by this address-labelled PartitionManager view.
class PartitionManager {
public:
    Rva0025ED50WideResult iterate(const Coord3D *, Real, IterOrderType,
                                  PartitionFilter *, Bool);
};

extern PartitionManager *ThePartitionManager;

class Object {
public:
    unsigned char m_00_to_38[0x38];
    Coord3D m_position;
    unsigned char m_44_to_74[0x30];
    ObjectID m_id;
};

struct Rva0025ED50Data {
    unsigned char m_00_to_254[0x254];
    Real m_range254;
};

class Rva0025EF90Owner {
public:
    void callAt0025ED50();

    unsigned char m_00_to_04[0x04];
    Rva0025ED50Data *m_data;
    Object *m_object;
    unsigned char m_0c_to_e8[0xdc];
    _STL::list<ObjectID> m_ids;
};

typedef char Rva0025ED50ListSizeCheck[
    (sizeof(_STL::list<ObjectID>) == 4) ? 1 : -1];

void Rva0025EF90Owner::callAt0025ED50()
{
    Object *object = m_object;
    Rva0025ED50Data *data = m_data;

    Rva0025ED50WideResult iterator = ThePartitionManager->iterate(
        &object->m_position, data->m_range254, ITER_FASTEST,
        PartitionFilterRelationship(object, 4, false).link(
            Rva0025ED50RootFilter().link(&Rva0025ED50ObjectFilter(object))), true);

    Object *other;
    while (iterator.next(other)) {
        if (other == object)
            continue;
        // Snapshot before allocation, as retail does; a reference into Object
        // makes the compiler reload after allocating and changes the register map.
        ObjectID id=other->m_id;
        m_ids.push_back(id);
    }
}
