// cl: /O2 /EHsc /MD /Igame/GameEngine/Include/Precompiled /Igame/GameEngine/Source/Common/System
#include "PreRTS.h"
#include "snapshot.h"
// Retail 0x001AEFF0; six stack slots. Terrain records are 0x30 bytes,
// bucket heads at +0x568 and record range at +0x55C/+0x560.
// Caller 0x001AF550 supplies object position, angle bits, GeometryInfo,
// an action object, skip flag, and mode. No semantic method name is asserted.
// GeometryInfo's exact constructor establishes its 0x5C-byte layout: vectors
// at +0x2C/+0x38, followed by six cached words. The implicit destructor calls
// both existing vector destructors and restores Snapshot's vtable.
struct Point001AEFF0 {float x,y,z; float length2()const {return x*x+y*y+z*z;} };
struct Bounds001AEFF0 {Point001AEFF0 lo,hi;};
struct Rva0087DC00Vec {int x,y,z;};
class Rva0087DC00 {public: void get(Rva0087DC00Vec*);};
extern void j_000187d2();
extern void j_0000ac2c();
struct ShapeVector001AEFF0 {
 char bytes[12];
 ~ShapeVector001AEFF0() {typedef void (__fastcall *Call)(void*);((Call)j_0000ac2c)(this);}
};
struct RecordVector001AEFF0 {
 char bytes[12];
 ~RecordVector001AEFF0() {typedef void (__fastcall *Call)(void*);((Call)j_000187d2)(this);}
};
enum GeometryType {GEOMETRY_SPHERE,GEOMETRY_CYLINDER,GEOMETRY_BOX};
class GeometryInfo:public Snapshot {
 char unmodelled04[0x28];
 ShapeVector001AEFF0 shapes;
 RecordVector001AEFF0 records;
 char unmodelled44[0x18];
public:
 GeometryInfo(GeometryType,bool,float,float,float);
 virtual const char *GetSnapshotName();
 virtual void LoadPostProcess();
 virtual void DoXfer(Xfer&);
};
class BfmeSubYR {public:
 char bfmeDoYR(void*,void*,void*,void*,int);
 // Adapt the existing opaque pin to its five-slot thiscall contract. The
 // float argument is transported as bits by the old void-pointer declaration.
 bool intersects(const Point001AEFF0 *p,float angle,GeometryInfo *g,const Point001AEFF0 *other,bool flag) {
  typedef char (BfmeSubYR::*Raw)(void*,void*,void*,void*,int);
  typedef bool (BfmeSubYR::*Typed)(const Point001AEFF0*,float,GeometryInfo*,const Point001AEFF0*,bool);
  union {Raw raw;Typed typed;} call;
  call.raw=&BfmeSubYR::bfmeDoYR;
  return (this->*call.typed)(p,angle,g,other,flag);
 }
};
class BfmeX1035;
class BfmeT1035 {public:void bfmeUse1035(BfmeX1035*,int);};
struct Record001AEFF0 {
 Point001AEFF0 position;
 int key;
 char unmodelled10[8];
 bool flag18;
 char unmodelled19[15];
 int unmodelled28;
 bool flag2c,flag2d;
 short next;
};
class TerrainRecordScan001AEFF0 {
public:
 virtual void s0();virtual void s1();virtual void s2();virtual void s3();
 virtual void s4();virtual void s5();virtual void s6();virtual void s7();
 virtual void s8();virtual void s9();
 virtual void bounds(Bounds001AEFF0*);
 char unmodelled04[0x558];
 Record001AEFF0 *begin,*end,*capacity;
 short buckets[50*50];
 void apply(const Point001AEFF0*,int,GeometryInfo*,BfmeT1035*,bool,int);
};
void TerrainRecordScan001AEFF0::apply(const Point001AEFF0 *position,int angle,
 GeometryInfo *geometry,BfmeT1035 *action,bool skipFlag18,int mode) {
 float radius=*(float*)((char*)geometry+0x10);
 Point001AEFF0 center;
 ((Rva0087DC00*)geometry)->get((Rva0087DC00Vec*)&center);
 center.x+=position->x;center.y+=position->y;center.z+=position->z;
 int count=end-begin;
 if(count==0)return;
 radius+=7.0f;
 Bounds001AEFF0 extent;
 bounds(&extent);
 float x=center.x-radius,y=center.y-radius;
 if(x<extent.lo.x)x=extent.lo.x;
 if(y<extent.lo.y)y=extent.lo.y;
 if(x>extent.hi.x)x=extent.hi.x;
 if(y>extent.hi.y)y=extent.hi.y;
 int minX=fast_float2long_round((float)floor(((x-extent.lo.x)/(extent.hi.x-extent.lo.x))*49.9f));
 int minY=fast_float2long_round((float)floor(((y-extent.lo.y)/(extent.hi.y-extent.lo.y))*49.9f));
 x=center.x+radius;y=center.y+radius;
 if(x<extent.lo.x)x=extent.lo.x;
 if(y<extent.lo.y)y=extent.lo.y;
 if(x>extent.hi.x)x=extent.hi.x;
 if(y>extent.hi.y)y=extent.hi.y;
 int maxX=fast_float2long_round((float)ceil(((x-extent.lo.x)/(extent.hi.x-extent.lo.x))*49.9f));
 int maxY=fast_float2long_round((float)ceil(((y-extent.lo.y)/(extent.hi.y-extent.lo.y))*49.9f));
 for(int i=minX;i<maxX;++i) {
  for(int j=minY;j<maxY;++j) {
   int index=buckets[j*50+i];
   while(index!=-1 && index>=0 && index<count) {
    Record001AEFF0 *base=begin;
    unsigned offset=index*sizeof(Record001AEFF0);
    Record001AEFF0 *record=(Record001AEFF0*)((char*)base+offset);
    if(!record->key) {index=record->next;continue;}
    if(skipFlag18 && base[index].flag18) {index=record->next;continue;}
    if(mode==1) {if(!base[index].flag2c) {index=record->next;continue;}}
    else if(mode==2) {if(!base[index].flag2d) {index=record->next;continue;}}
    Point001AEFF0 delta; delta.x=base[index].position.x; delta.y=base[index].position.y; delta.z=base[index].position.z;
    delta.x-=center.x;delta.y-=center.y;delta.z-=center.z;
    GeometryInfo cylinder(GEOMETRY_CYLINDER,false,20.0f,7.0f,7.0f);
    // Keep the radius on the left to preserve retail's x87 evaluation order.
    // Updating the dead byte offset to an address retains ESI until the push;
    // a fresh pointer temporary changes the call sequence by seven bytes.
    if(radius*radius>delta.length2() &&
       (offset+=(unsigned)begin, ((BfmeSubYR*)geometry)->intersects(position,*(float*)&angle,&cylinder,(const Point001AEFF0*)offset,false)))
     action->bfmeUse1035((BfmeX1035*)record,(int)&center);
    index=record->next;
   }
  }
 }
}
