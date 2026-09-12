// cl: /O2 /Ob1 /DNDEBUG /MD /EHsc- /D_STLP_USE_STATIC_LIB
// stlport
// MonsterDockUpdateInterface vtable VA 0x010CA9F0 slot12 -> ILT00036C1E
// -> RVA002CDF70. The constructor installs that table and initializes
// the one-shot docking timer at full-object offsets 0x89 and 0x8C.
// Use BitFlags::set(index,0), not bitset::reset: its inlining retains
// the shared active mask and the two retail flag stores.
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
struct Coord3D { float x,y,z; };
class Matrix3D;
class Gen_00411DD0 { public: void bfmeSet(bool); };
class StructureCollapsePosition { public: float x,y,z; };
class StructureCollapseRetailObject {public: void setPosition(const StructureCollapsePosition&,bool);};
template<int N> class BitFlags {
public:
 enum Init {kInit};
 BitFlags() {}
 unsigned char test(int i) const {return bits.test(i);}
 void set(int i,int value=1) {bits.set(i,value);}
 BitFlags(Init,int a,int b,int c,int d) {bits.set(a);bits.set(b);bits.set(c);bits.set(d);}
 _STL::bitset<N> bits;
};
class Object {
public:
 virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03(); virtual void slot04();
 virtual void slot05(); virtual void slot06(); virtual void slot07(); virtual void slot08(); virtual void slot09();
 virtual Gen_00411DD0 *getDrawable();
 void notifyModelConditionChanged();
 void convertBonePosToWorldPos(const Coord3D*, const Matrix3D*,Coord3D*,Matrix3D*) const;
 int getLayer() const;
 void clearModelConditionFlags(const BitFlags<320>&);
 char pad[0x10c];
 BitFlags<320> flags;
 void clearCondition272() { if(flags.test(272)) {flags.set(272,0);notifyModelConditionChanged();} }
 __forceinline void beginDockingActive() {
  if(flags.test(81) || !flags.test(82)) {
   flags.set(81,0); flags.set(82);
   notifyModelConditionChanged();
  }
 }

};
class Thing { public: void setPosition(const Coord3D*); };
class GameLogic {public:char pad[0x3c]; unsigned int frame;};
extern GameLogic *TheGameLogic;
class TerrainLogic {public:
 virtual void f0();virtual void f1();virtual void f2();virtual void f3();virtual void f4();virtual void f5();virtual void f6();
 virtual float height(float x,float y,int layer,void*,bool)const;
};
extern TerrainLogic *TheTerrainLogic;
struct MonsterDockUpdateModuleData {char pad[0x14];unsigned int delay;};
class MonsterDockUpdate {
public:
 virtual bool action(Object *docker,Object *drone);
 char pad[0x18]; Coord3D exitPosition;
 char pad28[0x41]; bool started;
 unsigned int endFrame;
 Object *getObject() const {return *(Object**)((char*)this-0x18);}
 const MonsterDockUpdateModuleData *getData()const {return *(MonsterDockUpdateModuleData**)((char*)this-0x1c);}
};
bool MonsterDockUpdate::action(Object *docker,Object *drone)
{
 if(!docker)return false;
 if(!started) {
  started=true;
  endFrame=TheGameLogic->frame+getData()->delay;
  getObject()->clearCondition272();
  getObject()->beginDockingActive();
  docker->clearCondition272();
  docker->beginDockingActive();
  return true;
 }
 if(TheGameLogic->frame<endFrame)return true;
 Coord3D position={0,0,0};
 getObject()->convertBonePosToWorldPos(&exitPosition,0,&position,0);
 ((StructureCollapseRetailObject*)docker)->setPosition(*(StructureCollapsePosition*)&position,true);
 // Retail passes the current z as the second terrain coordinate.
 position.z=TheTerrainLogic->height(position.x,position.z,docker->getLayer(),0,true);
 ((Thing*)docker)->setPosition(&position);
 docker->clearModelConditionFlags(BitFlags<320>(BitFlags<320>::kInit,80,81,82,83));
 Gen_00411DD0 *drawable=docker->getDrawable();
 drawable->bfmeSet(false);
 return false;
}
