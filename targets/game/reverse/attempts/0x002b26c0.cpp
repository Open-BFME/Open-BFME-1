// ?method@Rva002B26C0Owner@@QAEXXZ
// partial score=0.254 date=2026-10-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/bfmekindof /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "PreRTS.h"
#include "Common/BitFlags.h"
#include "Common/KindOf.h"


class Object;

typedef BitFlags<192> Rva00260180KindOfMask;
typedef BitFlags<86> Rva00260180ObjectStatusMask;
typedef char Rva00260180StatusMaskSizeCheck[
	(sizeof(Rva00260180ObjectStatusMask) == 12) ? 1 : -1];

// Retail sets bit 5 of the second 32-bit word: BitFlags' absolute index 37.


class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	virtual Int getPlayerMask();
	PartitionFilter *link(PartitionFilter *next);

	PartitionFilter *m_next;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	__declspec(noinline) PartitionFilterAcceptByKindOf(
		const Rva00260180KindOfMask &mustSet,
		const Rva00260180KindOfMask &mustClear)
		: m_mustSet(mustSet), m_mustClear(mustClear) {}
	virtual ~PartitionFilterAcceptByKindOf() {}
	virtual Bool allow(Object *);

	Rva00260180KindOfMask m_mustSet;
	Rva00260180KindOfMask m_mustClear;
};

class PartitionFilterRejectByObjectStatus : public PartitionFilter
{
public:
	PartitionFilterRejectByObjectStatus(
		const Rva00260180ObjectStatusMask &mustSet,
		const Rva00260180ObjectStatusMask &mustClear)
		: m_mustSet(mustSet), m_mustClear(mustClear) {}
	virtual ~PartitionFilterRejectByObjectStatus() {}
	virtual Bool allow(Object *);

	Rva00260180ObjectStatusMask m_mustSet;
	Rva00260180ObjectStatusMask m_mustClear;
};

class Rva00260180SelfFilter : public PartitionFilter
{
public:
	Rva00260180SelfFilter(Object *object) : m_object(object) {}
	virtual ~Rva00260180SelfFilter() {}
	virtual Bool allow(Object *);

	Object *m_object;
};

class Rva0025ED50ObjectFilter : public PartitionFilter
{
public:
	Rva0025ED50ObjectFilter(Object *object) : m_object(object) {}
	virtual ~Rva0025ED50ObjectFilter() {}
	virtual Bool allow(Object *);

	Object *m_object;
};

class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual ~Rva0025ED50RootFilter() {}
	virtual Bool allow(Object *);
};


class Rva000FBDC0Filter : public PartitionFilter {
public:
    Rva000FBDC0Filter() {}
    virtual ~Rva000FBDC0Filter() {}
    virtual Bool allow(Object *);
};
struct Rva002B26C0Entry { Object *object; int value; };
struct Rva002B26C0Data {
    std::vector<Rva002B26C0Entry> entries;
    Rva002B26C0Entry *current;
    int references;
};
struct BfmeWideResult {
    Rva002B26C0Data *value;
    BfmeWideResult();
    BfmeWideResult(const BfmeWideResult &);
    ~BfmeWideResult() { if (--value->references == 0) delete value; }
    unsigned size() const { return value->entries.size(); }
    Object *next() const {
        if (value->current == value->entries.end()) return 0;
        Object *object = value->current->object;
        ++value->current;
        return object;
    }
};
class BfmeWideForwardC {
public:
    BfmeWideResult bfmeForwardWideC(int,float,int,int,int);
};
class PartitionManager;
extern PartitionManager *ThePartitionManager;
class BfmePosTP;
class BfmeHostTP { public: void bfmeSetPositionTP(const BfmePosTP *,bool); };
class BfmeA1057 { public: void bfmeGo1057A(int); };
class Gen_001BEC20 { public: int bfmeScale() const; };
class Rva00027BC9Object { public: void getPosition(Coord3D *); };
class LocomotorSet;
class Pathfinder {
public:
    int getLayer(const Coord3D *);
    bool Rva003DF250(Object *,Coord3D *);
    bool adjustDestination(Object *,const LocomotorSet &,Coord3D *,const Coord3D *);
};
class AI;
extern AI *TheAI;
struct Rva002B26C0AI { char rva00[12]; Pathfinder *rva0c; };
class Object {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0c(); virtual void slot10(); virtual void slot14();
    virtual void slot18(); virtual void slot1c(); virtual void slot20();
    virtual void slot24(); virtual BfmeA1057 *slot28();
    char rva00000004[0x38-4];
    Coord3D rva00000038;
    char rva00000044[0xbc-0x44];
    float rva000000bc;
    char rva000000c0[0x204-0xc0];
    char *rva00000204;
};
class Rva002B26C0Owner {
public:
    void method();
    char rva00000000[8];
    Object *rva00000008;
};
void Rva002B26C0Owner::method()
{
    Object *object = rva00000008;
    float radius = object->rva000000bc;
    Coord3D center;
    ((Rva00027BC9Object *)object)->getPosition(&center);
    center.z = object->rva00000038.z;
    BfmeWideResult result = ((BfmeWideForwardC *)ThePartitionManager)->bfmeForwardWideC(
        (int)&center, radius, 0,
        (int)Rva00260180SelfFilter(object)
          .link(&Rva0025ED50RootFilter())
          ->link(&Rva000FBDC0Filter())
          ->link(&PartitionFilterRejectByObjectStatus(
             Rva00260180ObjectStatusMask(Rva00260180ObjectStatusMask::kInit,26),
             Rva00260180ObjectStatusMask()))
          ->link(&Rva0025ED50ObjectFilter(object))
          ->link(&PartitionFilterAcceptByKindOf(
            Rva00260180KindOfMask(Rva00260180KindOfMask::kInit,2),
            *reinterpret_cast<const Rva00260180KindOfMask *>(&KINDOFMASK_NONE))), 2);
    if (result.size() > 0) {
        Object *other;
        while ((other = result.next()) != 0) {
            if (((Gen_001BEC20 *)other)->bfmeScale() != 1) continue;
            Pathfinder *pathfinder = ((Rva002B26C0AI *)TheAI)->rva0c;
            Coord3D position;
            position.x = other->rva00000038.x;
            position.y = other->rva00000038.y;
            position.z = other->rva00000038.z;
            if (pathfinder->getLayer(&position) == 1 &&
                pathfinder->Rva003DF250(other,&position)) continue;
            Coord3D destination;
            destination.x = position.x + (center.x - object->rva00000038.x) * 0.5f;
            destination.y = position.y + (center.y - object->rva00000038.y) * 0.5f;
            destination.z = position.z;
            pathfinder->adjustDestination(other,
              *(const LocomotorSet *)(other->rva00000204+0x1a8),&destination,0);
            ((BfmeHostTP *)other)->bfmeSetPositionTP((const BfmePosTP *)&destination,true);
            if (other->slot28()) other->slot28()->bfmeGo1057A(10);
        }
    }
}
