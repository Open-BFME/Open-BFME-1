// ?d_002a1f80@@YAXXZ
// partial score=0.994 date=2026-09-27
// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source/GameLogic/Object
// stlport
#include <set>
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
// ObjectStatusBits.h defines a narrower Object without the methods below.
// Its BitFlags representation and kInit constructor are retained here.
template<int N> class BitFlags {
 _STL::bitset<N> bits;
 public: enum Init { kInit }; BitFlags(){} BitFlags(Init,int bit){bits.set(bit);}
};
class Player; class BfmeConditionFlags;
enum DisabledType { Disabled4 = 4 };
class Object; struct Coord3D {float x,y,z;};
class ExitInterface {public:
 virtual void slot00(); virtual void slot04(); virtual void slot08(Object*,int);
 virtual void slot0c();virtual void slot10();virtual void slot14();virtual void slot18();virtual void slot1c();virtual void slot20();virtual void slot24(Coord3D*,bool);
};

class Object { public:
 ExitInterface* getObjectExitInterface()const;
 void clearAndSetModelConditionFlags(const BfmeConditionFlags&, const BfmeConditionFlags&);
 void setStatus(const BitFlags<86>&,bool);
 void setDisabled(DisabledType);
 void setEffectivelyDead(bool);
 Player* getControllingPlayer() const;
};
#define MAKE_OBJECT_STATUS_MASK(k) BitFlags<86>(BitFlags<86>::kInit,k)
struct Rva002A23B0Record {
 unsigned level; int unknown04, unknown08; float unknown0c; bool unknown10;
 Rva002A23B0Record(unsigned v):level(v),unknown04(0),unknown08(0),unknown0c(1.0f),unknown10(false){}
 bool operator<(const Rva002A23B0Record& v)const{return level<v.level;}
};
typedef _STL::set<Rva002A23B0Record> Records;
class BfmeConditionFlags { _STL::bitset<304> bits; public: BfmeConditionFlags(){} };
extern void j_00022bba();
class FXList { public: static void applyFX(const FXList* fx,Object* obj){if (fx && !fx->bfmeIsBlocked()) fx->doFXObj(obj,0);} bool bfmeIsBlocked() const; void doFXObj(const Object*,const Object*)const; };
struct Rva002A30D0Data { char p00[12]; BfmeConditionFlags flags; char p34[0x84-0x34]; FXList* fx; FXList* fx88;FXList* fx8c;unsigned f90,f94,f98,f9c; Records levels; };
class Player; class BfmeConditionFlags;
class Rva000FB2E0Owner {public:int Gen000FB2E0Method(Object*,bool);};
enum UpdateSleepTime { Forever = 0x3fffffff }; class UpdateModule {protected:void setWakeFrame(Object*,UpdateSleepTime);};
struct Rva002A30D0State { char p00[0x28]; unsigned level; };
class Body002A32D0 {public:
 virtual void v00();virtual void v04();virtual void v08();virtual void v0c();virtual void v10();virtual void v14();virtual void v18();virtual void v1c();virtual void v20();virtual void v24();virtual void v28();virtual void v2c();virtual void v30();virtual void v34();virtual void v38();virtual void v3c();virtual void v40();virtual void v44();virtual void v48();virtual void v4c();virtual void v50();virtual void v54(float,int);
};
struct Rva002A30D0Object {char p00[0x38];Coord3D position;char p44[0x200-0x44];Body002A32D0* body;char p204[12];Rva002A30D0State* state;};

class PlayerList {public: char p00[12];Player* local;};
class ControlBar {public: char p00[0x24];bool dirty;};
extern PlayerList* ThePlayerList;extern ControlBar* TheControlBar;
class LevelWake002A1F80:public UpdateModule {public:
 void apply(Object* source);
 void* vptr;Rva002A30D0Data* data;Object* object;char p0c[0x20-12];float f20;char p24[8];int f2c,f30,f34,f38,f3c;bool f40,f41;
};
void LevelWake002A1F80::apply(Object* source){
 Rva002A30D0Data* d=data;
 Object* obj=object;
 Coord3D position;position.x=((Rva002A30D0Object*)source)->position.x;position.y=((Rva002A30D0Object*)source)->position.y;position.z=((Rva002A30D0Object*)source)->position.z;
 ExitInterface* exit=source->getObjectExitInterface();if(exit)exit->slot24(&position,true);
 const FXList* fx;unsigned delay;
 if(f41){obj->clearAndSetModelConditionFlags(BfmeConditionFlags(),*(BfmeConditionFlags*)((char*)d+0x5c));delay=d->f98;fx=d->fx8c;}
 else{obj->clearAndSetModelConditionFlags(BfmeConditionFlags(),*(BfmeConditionFlags*)((char*)d+0x34));delay=d->f94;fx=d->fx88;}
 if(fx&&!fx->bfmeIsBlocked())fx->doFXObj(obj,0);
 f2c=4;
 Records::iterator it=d->levels.find(Rva002A23B0Record(((Rva002A30D0Object*)obj)->state->level));
 Records::iterator end=d->levels.end();
 if(it==end){it=d->levels.find(Rva002A23B0Record(1));if(it==end){setWakeFrame(obj,Forever);return;}}
 f20=it->unknown0c;
 ((Rva002A30D0Object*)obj)->body->v54(f20*100.0f,0);
 f34=-1;f38=-1;
 Player* local=ThePlayerList->local;if(local==obj->getControllingPlayer())TheControlBar->dirty=true;
 setWakeFrame(obj,(UpdateSleepTime)delay);
}



