// cl: /DNDEBUG /MD /EHs-c- /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// FlatHeightMapRenderObjClass::updateCenter, retail 0x006D2A00 (1984 B). ilt_oracle confirms this
// exact decoration at 0x006D2A00. Handoff:
// targets/game/reverse/attempt_support/20261111-006d2a00-neighbor-budget.md
// Neighbor pass and distance-budget search follow the BFME 2 donor FlatHeightMapUpdateCenter.cpp (open-bfme-2 2bac16a6): separate neighbor indices, chained zero, do-while budget reread.
#include "vector3.h"
// Retail VA0111DC88 slot135 routes through ILT RVA000155DC to this body.
// The address-derived BFME view preserves the decoded member offsets.
class RenderObjClass { public: Vector3 Get_Position() const; };
class CameraClass : public RenderObjClass {};
template<class T> class RefMultiListIterator;
class BaseHeightMapRenderObjClass { public: virtual void updateCenter(CameraClass*,RefMultiListIterator<RenderObjClass>*); };
class Rva007287E0StateReset { public: int setAndClear(unsigned char*); };
class Rva0072EA60 { public: void apply(int,int,int,int,bool); };
extern void j_00031de0();
union Rva006D2A00NeighborCall { void (*f)(); void (Rva0072EA60::*m)(int,int,int,int,bool); };
class W3DTerrainBackground {
public:
 int field_00; char pad04[0x30]; int field_34; char pad38[0x1c]; float field_54; char pad58[0x6c];
 void updateCenter(CameraClass*);
};
struct Rva006D2A00State { int value; unsigned char changed; char pad5[3]; };
struct Rva006D2A00Map { char pad[0x120e8]; int field_120e8,field_120ec; };
struct Rva006D2A00Global { char pad[0xecc]; int field_ecc; };
extern bool Rva012F08A0;
extern void *Rva012ED5C8;
#define Rva00EF08A0 Rva012F08A0
#define Rva00EED5C8 ((Rva006D2A00Global*)Rva012ED5C8)
extern int g_Va012F8018,g_Va012F8010,g_Va012F8014;
class FlatHeightMapRenderObjClass {
public:
 char pad0[0x2ff0]; Rva006D2A00Map *field_2ff4; char pad2ff8[0x11]; bool field_3009;
 char pad300a[0xca]; Rva006D2A00State *field_30d4; W3DTerrainBackground *field_30d8;
 int field_30dc,field_30e0,field_30e4,field_30e8,field_30ec,field_30f0,field_30f4;
 bool field_30f8; char pad30f9[3]; int field_30fc; float field_3100; bool field_3104; char pad3105[3];
 Vector3 field_3108; char pad3114[0x64]; int field_3178;
 virtual void updateCenter(CameraClass*,RefMultiListIterator<RenderObjClass>*);
};
// Primary vptr is followed by 0x2ff0 bytes, placing the map pointer at +0x2ff4.
void FlatHeightMapRenderObjClass::updateCenter(CameraClass *camera,RefMultiListIterator<RenderObjClass>*lights) {
 if(Rva00EF08A0) { ((BaseHeightMapRenderObjClass*)this)->BaseHeightMapRenderObjClass::updateCenter(camera,lights); return; }
 Vector3 old=field_3108;
 field_3108=camera->Get_Position();
 if((old-field_3108).Length2()>400.0f || Rva00EED5C8->field_ecc) field_3104=true;
 ((BaseHeightMapRenderObjClass*)this)->BaseHeightMapRenderObjClass::updateCenter(camera,lights);
 field_3009=false;
 field_30f0=0; field_30f4=0;
 field_30e8=field_30e0*16; field_30ec=field_30e4*16;
 int i,j,culled=0,t2=0,t4=0;
 for(i=0;i<field_30e0;i++) for(j=0;j<field_30e4;j++) {
  W3DTerrainBackground *tile=field_30d8+j*field_30e0+i;
  tile->updateCenter(camera);
  unsigned char changed;
  field_30d4[j*field_30e0+i].value=((Rva007287E0StateReset*)tile)->setAndClear(&changed);
  field_30d4[j*field_30e0+i].changed=changed;
  if(tile->field_00==2) culled++;
  else {
   if(field_30f0<i*16+16) field_30f0=i*16+16;
   if(field_30f4<j*16+16) field_30f4=j*16+16;
   if(field_30e8>i*16) field_30e8=i*16;
   if(field_30ec>j*16) field_30ec=j*16;
  }
  int tx=tile->field_34;
  if(tx==4)t4++; else if(tx==2)t2++;
 }
 for(i=0;i<field_30e0;i++) {
  for(j=0;j<field_30e4;j++) {
   W3DTerrainBackground *tile=field_30d8+j*field_30e0+i;
   int leftIdx=j*field_30e0+i-1;
   int downIdx=(j+1)*field_30e0+i;
   int rightIdx=j*field_30e0+i+1;
   int upIdx=(j-1)*field_30e0+i;
   int left,bottom,right,top;
   left=bottom=right=top=0;
   bool changed=false;
   if(i==0) {
    if(j==0) {
     bottom=field_30d4[downIdx].value; right=field_30d4[rightIdx].value;
     changed=field_30d4[downIdx].changed||field_30d4[rightIdx].changed;
    } else if(j==field_30e4-1) {
     right=field_30d4[rightIdx].value; top=field_30d4[upIdx].value;
     changed=field_30d4[rightIdx].changed||field_30d4[upIdx].changed;
    } else {
     bottom=field_30d4[downIdx].value; right=field_30d4[rightIdx].value; top=field_30d4[upIdx].value;
     changed=field_30d4[downIdx].changed||field_30d4[rightIdx].changed||field_30d4[upIdx].changed;
    }
   } else if(i==field_30e0-1) {
    if(j==0) {
     left=field_30d4[leftIdx].value; bottom=field_30d4[downIdx].value;
     changed=field_30d4[leftIdx].changed||field_30d4[downIdx].changed;
    } else if(j==field_30e4-1) {
     left=field_30d4[leftIdx].value; top=field_30d4[upIdx].value;
     changed=field_30d4[leftIdx].changed||field_30d4[upIdx].changed;
    } else {
     left=field_30d4[leftIdx].value; bottom=field_30d4[downIdx].value; top=field_30d4[upIdx].value;
     changed=field_30d4[leftIdx].changed||field_30d4[downIdx].changed||field_30d4[upIdx].changed;
    }
   } else {
    if(j==0) {
     left=field_30d4[leftIdx].value; bottom=field_30d4[downIdx].value; right=field_30d4[rightIdx].value;
     changed=field_30d4[leftIdx].changed||field_30d4[downIdx].changed||field_30d4[rightIdx].changed;
    } else if(j==field_30e4-1) {
     left=field_30d4[leftIdx].value; right=field_30d4[rightIdx].value; top=field_30d4[upIdx].value;
     changed=field_30d4[leftIdx].changed||field_30d4[rightIdx].changed||field_30d4[upIdx].changed;
    } else {
     left=field_30d4[leftIdx].value; bottom=field_30d4[downIdx].value; right=field_30d4[rightIdx].value; top=field_30d4[upIdx].value;
     changed=field_30d4[leftIdx].changed||field_30d4[downIdx].changed||field_30d4[rightIdx].changed||field_30d4[upIdx].changed;
    }
   }
   Rva006D2A00NeighborCall call;call.f=&j_00031de0;
   (((Rva0072EA60*)tile)->*call.m)(left,bottom,right,top,changed);
  }
 }
 if(field_30f8) {
  int target=(field_2ff4->field_120e8/16)*field_2ff4->field_120ec/16;
  int needed=(field_2ff4->field_120e8/16+1)*(field_2ff4->field_120ec/16+1);
  if(needed<field_30dc) {
   field_30fc=target;
   float low=0.0f,high=500.0f;
   int count=0,visible=0;
   do {
    W3DTerrainBackground *tile=field_30d8;
    count=0; visible=0;
    for(int n=field_30dc;n>0;n--) {
     if(tile->field_00!=2) { visible++; if(tile->field_54<high) count++; }
     tile++;
    }
    if(visible<field_30fc) { field_30fc=field_30dc; break; }
    if(count<field_30fc) { low=high; high*=2.0f; }
   } while(count<field_30fc);
   if(field_30fc<field_30dc) {
    field_3100=low;
    for(int pass=0;pass<20;pass++) {
     count=0;
     float mid=(low+high)/2.0f;
     W3DTerrainBackground *tile=field_30d8;
     for(int n=field_30dc;n>0;n--) {
      if(tile->field_00!=2 && tile->field_54<mid) count++;
      tile++;
     }
     if(count==field_30fc) { field_3100=mid; break; }
     if(count>field_30fc) high=mid;
     else { low=mid; field_3100=mid; }
    }
   }
  } else field_30fc=field_30dc;
 }
 if(culled!=g_Va012F8018 || t4!=g_Va012F8014 || t2!=g_Va012F8010) {
  g_Va012F8018=culled;g_Va012F8010=t2;g_Va012F8014=t4;
 }
 field_3178=3;
}

