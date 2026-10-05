// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
// stlport
// Retail 0x0027B000 (738 bytes): search concentric sample circles and return
// the first point outside every accepted object's combined radius.
// ABI: float + input Coord3D* + output Coord3D* + six-word mask; ret 0x24.
// Independently witnessed by DeathFlight001FFFC0.cpp at its call through 42B9A.
// Radius and angle bounds are inclusive (x87 AH mask 0x41), not strict.
// The actual non-retaining filter constructor is visible below and separately
// byte-probed at 0x000C3DD0 (102B); this permits reuse of incoming mask storage.
// The filter temporary dies immediately after iterator construction.
// /GX retains unwind state across the external C sinf/cosf calls; /EHsc
// incorrectly assumes those calls cannot throw and removes retail state 2.
// Coordinate copies are explicit to preserve the native aggregate lifetime.

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include <bitset>
struct Coord3D { float x,y,z; void set(const Coord3D *a) { x=a->x; y=a->y; z=a->z; } };
enum IterOrderType {};
template<int N> class BitFlags { public: _STL::bitset<N> bits; };
extern const BitFlags<192> KINDOFMASK_NONE;




class Object;
class PartitionFilter {
public:
 PartitionFilter():m_next(0) {}
 virtual ~PartitionFilter() {}
 virtual bool allow(Object*)=0;
 virtual int getPlayerMask();
 PartitionFilter *m_next;
};
extern "C" float __cdecl sinf(float value);
extern "C" float __cdecl cosf(float value);


class Object
{
public:
	char m_pad00[0x38];
	Coord3D m_position;
	char m_pad44[0xC0 - 0x44];
	float getRadius() const { return m_bfmeRadius; }
 float m_bfmeRadius;
};

typedef BitFlags<192> BfmeSweepKindOfMask;

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	__declspec(noinline) PartitionFilterAcceptByKindOf(
		const BfmeSweepKindOfMask &mustBeSet,
		const BfmeSweepKindOfMask &mustBeClear) : m_mustBeSet(mustBeSet),m_mustBeClear(mustBeClear) {}
 virtual ~PartitionFilterAcceptByKindOf() {}
 virtual bool allow(Object*);
 BfmeSweepKindOfMask m_mustBeSet;
 BfmeSweepKindOfMask m_mustBeClear;
};

struct Rva0027B000Entry
{
	Object *object;
	unsigned distanceBits;
};

struct Rva009F39F0Payload
{
	_STL::vector<Rva0027B000Entry> entries;
	Rva0027B000Entry *current;
	int references;
};

struct BfmeWideResult
{
	Rva009F39F0Payload *value;
	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &that);
	~BfmeWideResult() { if(--value->references==0) delete value; }
 void first() { value->current=value->entries.begin(); }
 Object *next() {
  if(value->current==value->entries.end()) return 0;
  return (value->current++)->object;
 }
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(int,int,int,int,int);
};

class PartitionManager;
extern PartitionManager *ThePartitionManager;


class AIUpdateInterface {
public:
 char pad[8]; Object *m_object;
 bool findClearPosition0027B000(float maxRadius,const Coord3D *center,Coord3D *out,BfmeSweepKindOfMask flags);
};
bool AIUpdateInterface::findClearPosition0027B000(float maxRadius,const Coord3D *center,Coord3D *out,BfmeSweepKindOfMask flags)
{
 Object *object=m_object;
 if(!object) return false;
 float limit;
 if(10.0f>object->getRadius()) limit=10.0f; else limit=object->m_bfmeRadius;
	BfmeWideResult iterator=(*reinterpret_cast<BfmeWideForwardC **>(&ThePartitionManager))->bfmeForwardWideC((int)center,*(int*)&maxRadius,0,
	 (int)&PartitionFilterAcceptByKindOf(flags,*(const BfmeSweepKindOfMask*)&KINDOFMASK_NONE),1);
 for(float radius=limit; radius<=maxRadius; radius+=limit) {
  float step=1.0f/limit;
  float circumference = radius * 6.2831855f;
  float samples=circumference*step;
  float spacing=6.2831855f/samples;
  for(float angle=-3.1415927f; angle<=3.1415927f; angle+=spacing) {
   Coord3D pos; pos.x=center->x; pos.y=center->y; pos.z=center->z;
   pos.x += sinf(angle)*radius;
   pos.y += cosf(angle)*radius;
   iterator.first();
   Object *other;
   while((other=iterator.next())!=0) {
    float need=other->getRadius()+limit;
    float needSq=need*need;
    float dx=other->m_position.x-pos.x;
    float dy=other->m_position.y-pos.y;
    if(dx*dx+dy*dy<needSq) break;
   }
   if(!other) { *out=pos; return true; }
  }
 }
 return false;
}
