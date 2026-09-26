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

// Retail 0x002113A0, 424 bytes. Vtable slot 19 is shared by the BodyModule
// families documented in the existing attempt log (including DelayedDeathBody,
// FreeLifeBody, StructureBody and SymbioticStructuresBody). The exact method
// identity remains unproved, so the owner and method retain the body address.
// The optional terrain/view branch uses GlobalData+0xEC8; the partition query
// always runs. Its three temporary filters must die before result iteration.
// Filter and result layouts reuse the verified Rva0025ED50ChargeTargets model:
// vtables 0x01085DD0 / 0x01083B80 / 0x01085DC0; 8-byte result records with
// cursor +0x0C and reference count +0x10. No decompiler names are assumed.
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
    void bfmeApplySpecialModelCondition(Int,const void *,Int);
};

struct Rva002113A0Data { char m_prefix[0x4C]; Real m_range; };
class Rva002113A0Terrain {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual void slot0C(); virtual void slot10(); virtual void slot14();
 virtual Real slot18(Real,Real,void *);
};
class Rva002113A0View {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual void slot0C(); virtual void slot10(); virtual void slot14();
 virtual void slot18(); virtual void slot1C(); virtual void slot20();
 virtual void slot24(); virtual void slot28(); virtual void slot2C();
 virtual void slot30(const Coord3D *,Real,Int,Int);
};
extern Rva002113A0Terrain *TheTerrainLogic;
extern Rva002113A0View *TheTacticalView;
class Rva002113A0Owner {
public:
 void rva002113a0();
 void *m_vptr;
 Rva002113A0Data *m_data;
 Object *m_object;
};
void Rva002113A0Owner::rva002113a0()
{
 Rva002113A0Data *data=m_data;
 if(data->m_range<=0.0f)return;
 Object *object=m_object;
 if(*(const bool *)((const char *)TheWritableGlobalData+0xEC8)) {
  Coord3D position;
  position.x=object->m_position.x;
  position.y=object->m_position.y;
  position.z=object->m_position.z;
  position.z=TheTerrainLogic->slot18(position.x,position.y,0);
  TheTacticalView->slot30(&position,data->m_range,0xFFFF8000,0);
 }
 Rva0025ED50WideResult iterator=ThePartitionManager->iterate(
  &object->m_position,data->m_range,ITER_FASTEST,
  PartitionFilterRelationship(object,1,false).link(
   Rva0025ED50RootFilter().link(&Rva0025ED50ObjectFilter(object))),false);
 Object *other;
 while(iterator.next(other))other->bfmeApplySpecialModelCondition(1,object,10);
}
