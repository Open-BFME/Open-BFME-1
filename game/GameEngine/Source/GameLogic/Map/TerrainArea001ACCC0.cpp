// cl: /O2 /EHsc
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
// Retail 0x001ACCC0 (267 bytes) and 0x001AC3D0 (317 bytes), both ret 8.
// The owning method names remain unknown. The receiver passes unchanged to
// TerrainLogicP48ClearNear::clearNear; the two arguments are a position and
// float radius bits. Integer transport preserves the existing wide-query ABI.
// The 56-byte kind filter has an 8-byte polymorphic prefix and two 24-byte
// masks. Its temporary dies before iteration, restoring PartitionFilter's
// vtable. STLport's end() accessor is required for the retail cursor shape.
template<unsigned N> class BitFlags {
 unsigned words[N/32];
public:
 enum BogusInitType { kInit=0 };
 BitFlags(BogusInitType,int);
};
extern const BitFlags<192> KINDOFMASK_NONE;
class Object;
class PartitionFilter {
public:
 virtual ~PartitionFilter() {}
 virtual bool allow(Object *)=0;
 virtual int getPlayerMask();
 PartitionFilter *m_next;
};
class PartitionFilterAcceptByKindOf:public PartitionFilter {
 BitFlags<192> a,b;
public:
 PartitionFilterAcceptByKindOf(const BitFlags<192>&,const BitFlags<192>&);
 virtual ~PartitionFilterAcceptByKindOf() {}
 virtual bool allow(Object*);
};
extern void j_0002c471();
struct Entry001ACCC0 {Object *object; unsigned unknown04;};
struct Result001ACCC0 {std::vector<Entry001ACCC0> entries; Entry001ACCC0 *current;int references;};
struct BfmeWideResult {
 Result001ACCC0 *value;
 BfmeWideResult();
 BfmeWideResult(const BfmeWideResult&);
 ~BfmeWideResult() {typedef void (__fastcall *Call)(void*);((Call)j_0002c471)(this);}
 Object *next(Object *&object) {
  if(value->current==value->entries.end())return 0;
  object=(value->current++)->object;
  return object;
 }
};
class BfmeWideForwardC {public: BfmeWideResult bfmeForwardWideC(int,int,int,int,int);};
// Retail's global at 0x012ED5B8 is `PartitionManager *ThePartitionManager`
// (game/GameEngine/Source/GameLogic/Object/PartitionManager.cpp defines it).
// Declare it under that exact spelling; the narrow forward-call view is cast in.
class PartitionManager;
extern PartitionManager *ThePartitionManager;
struct BfmePointFC;
class BfmeTaintManager {public: void bfmeApplyCircleWorld(const BfmePointFC*,float,int,bool);};
class TaintManager;
extern TaintManager *TheTaintManager;

class GameLogic {public: void destroyObject(Object*);};
extern GameLogic *TheGameLogic;
class TerrainArea001ACCC0 {
public:
 void clear(const void *position,int radius);
 void clearOne001AC3D0(const void *position,int radius);
};
void TerrainArea001ACCC0::clear(const void *position,int radius) {
 if(!position||!(*reinterpret_cast<BfmeTaintManager **>(&TheTaintManager))||!ThePartitionManager||!TheGameLogic)return;
 BfmeWideResult iterator=((BfmeWideForwardC*)ThePartitionManager)->bfmeForwardWideC((int)position,radius,0,
  (int)&PartitionFilterAcceptByKindOf(BitFlags<192>(BitFlags<192>::kInit,151),KINDOFMASK_NONE),1);
 Object *object;
 while(iterator.next(object)) {
  clearOne001AC3D0((char*)object+0x38,radius);
  TheGameLogic->destroyObject(object);
 }
 clearOne001AC3D0(position,radius);
}



struct BfmePointFC {float x,y;};
struct Coord3D;
class TerrainLogicP48ClearNear {public:void clearNear(const Coord3D*,float);};
// A nontrivial copy constructor plus the float constructor makes the by-value
// visual argument construct directly on the outgoing stack, as retail does.
struct TerrainPoint001AC3D0 {
 float x,y,z; TerrainPoint001AC3D0(float a,float b,float c):x(a),y(b),z(c){}
 TerrainPoint001AC3D0(const TerrainPoint001AC3D0 &p):x(p.x),y(p.y),z(p.z){}
};
class TerrainVisual001AC3D0 {
public:
 virtual void s00();virtual void s01();virtual void s02();virtual void s03();
 virtual void s04();virtual void s05();virtual void s06();virtual void s07();
 virtual void s08();virtual void s09();virtual void s10();virtual void s11();
 virtual void s12();virtual void s13();virtual void s14();virtual void s15();
 virtual void s16();virtual void s17();virtual void s18();virtual void s19();
 virtual void s20();virtual void s21();virtual void s22();virtual void s23();
 virtual void s24();virtual void s25();virtual void s26();virtual void s27();
 virtual void s28();virtual void s29();virtual void s30();virtual void s31();
 virtual void s32();virtual void s33();virtual void s34();
 virtual void notify(TerrainPoint001AC3D0,int);
};
extern TerrainVisual001AC3D0 *TheTerrainVisual;
void TerrainArea001ACCC0::clearOne001AC3D0(const void *position,int radius) {
 if(!position||!(*reinterpret_cast<BfmeTaintManager **>(&TheTaintManager))||!ThePartitionManager||!TheGameLogic)return;
 (*reinterpret_cast<BfmeTaintManager **>(&TheTaintManager))->bfmeApplyCircleWorld((const BfmePointFC*)position,*(float*)&radius,128,true);
 BfmeWideResult iterator=((BfmeWideForwardC*)ThePartitionManager)->bfmeForwardWideC((int)position,radius,0,
  (int)&PartitionFilterAcceptByKindOf(BitFlags<192>(BitFlags<192>::kInit,173),KINDOFMASK_NONE),1);
 Object *object;
 while(iterator.next(object)) TheGameLogic->destroyObject(object);
 ((TerrainLogicP48ClearNear*)this)->clearNear((const Coord3D*)position,*(float*)&radius);
 if(TheTerrainVisual) {
  const float *p=(const float*)position;
  TheTerrainVisual->notify(TerrainPoint001AC3D0(p[0],p[1],p[2]),radius);
 }
}
