// ?updateCenter@HeightMapRenderObjClass@@UAEXPAVCameraClass@@PAV?$RefMultiListIterator@VRenderObjClass@@@@@Z
// partial score=0.9138104838709677 date=2026-09-23
// cl: /DNDEBUG /MD /EHs-c- /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib
#include "vector3.h"
// Identity: ctor RVA006D1C80 installs VA0111DC88; slot135 routes
// through ILT RVA000155DC to this body. Ret8 at RVA006D31BD: 1984 bytes.
// BFME ABI views: Zero Hour's terrain class has a different extent.
class RenderObjClass { public: Vector3 Get_Position() const; };
class CameraClass : public RenderObjClass {};
template<class T> class RefMultiListIterator;
class BaseHeightMapRenderObjClass { public: virtual void updateCenter(CameraClass*,RefMultiListIterator<RenderObjClass>*); };
class Rva007287E0StateReset { public: int setAndClear(unsigned char*); };
class Rva0072EA60 { public: void apply(int,int,int,int,bool); };
class W3DTerrainBackground {
public:
 int field_00; char pad04[0x30]; int field_34; char pad38[0x1c]; float field_54; char pad58[0x6c];
 void updateCenter(CameraClass*);
};
struct Rva006D2A00State { int value; unsigned char changed; char pad5[3]; };
struct Rva006D2A00Map { char pad[0x120e8]; int field_120e8,field_120ec; };
struct Rva006D2A00Global { char pad[0xecc]; int field_ecc; };
extern bool Rva00EF08A0;
extern Rva006D2A00Global *Rva00EED5C8;
extern int Rva00EF8018,Rva00EF8010,Rva00EF8014;
class HeightMapRenderObjClass {
public:
 char pad0[0x2ff0]; Rva006D2A00Map *field_2ff4; char pad2ff8[0x11]; bool field_3009;
 char pad300a[0xca]; Rva006D2A00State *field_30d4; W3DTerrainBackground *field_30d8;
 int field_30dc,field_30e0,field_30e4,field_30e8,field_30ec,field_30f0,field_30f4;
 bool field_30f8; char pad30f9[3]; int field_30fc; float field_3100; bool field_3104; char pad3105[3];
 Vector3 field_3108; char pad3114[0x64]; int field_3178;
 virtual void updateCenter(CameraClass*,RefMultiListIterator<RenderObjClass>*);
};
// Primary vptr is followed by 0x2ff0 bytes, placing the map pointer at +0x2ff4.
void HeightMapRenderObjClass::updateCenter(CameraClass *camera,RefMultiListIterator<RenderObjClass>*lights) {
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
 for(i=0;i<field_30e0;i++) for(j=0;j<field_30e4;j++) {
  W3DTerrainBackground *tile=field_30d8+j*field_30e0+i;
  int index=j*field_30e0+i,down=(j+1)*field_30e0+i,up=(j-1)*field_30e0+i;
  int top=0,right=0,bottom=0,left=0;
  bool changed;
  if(i==0) {
   if(j==0) {
    bottom=field_30d4[down].value;right=field_30d4[index+1].value;
    changed=field_30d4[down].changed||field_30d4[index+1].changed;
   } else if(j==field_30e4-1) {
    top=field_30d4[up].value;right=field_30d4[index+1].value;
    changed=field_30d4[index+1].changed||field_30d4[up].changed;
   } else {
    bottom=field_30d4[down].value;top=field_30d4[up].value;right=field_30d4[index+1].value;
    changed=field_30d4[down].changed||field_30d4[index+1].changed||field_30d4[up].changed;
   }
  } else if(i==field_30e0-1) {
   if(j==0) {
    left=field_30d4[index-1].value;bottom=field_30d4[down].value;
    changed=field_30d4[index-1].changed||field_30d4[down].changed;
   } else if(j==field_30e4-1) {
    left=field_30d4[index-1].value;top=field_30d4[up].value;
    changed=field_30d4[index-1].changed||field_30d4[up].changed;
   } else {
    left=field_30d4[index-1].value;bottom=field_30d4[down].value;top=field_30d4[up].value;
    changed=field_30d4[index-1].changed||field_30d4[down].changed||field_30d4[up].changed;
   }
  } else {
   if(j==0) {
    left=field_30d4[index-1].value;right=field_30d4[index+1].value;bottom=field_30d4[down].value;
    changed=field_30d4[index-1].changed||field_30d4[down].changed||field_30d4[index+1].changed;
   } else if(j==field_30e4-1) {
    left=field_30d4[index-1].value;top=field_30d4[up].value;right=field_30d4[index+1].value;
    changed=field_30d4[index-1].changed||field_30d4[index+1].changed||field_30d4[up].changed;
   } else {
    left=field_30d4[index-1].value;right=field_30d4[index+1].value;bottom=field_30d4[down].value;top=field_30d4[up].value;
    changed=field_30d4[index-1].changed||field_30d4[down].changed||field_30d4[index+1].changed||field_30d4[up].changed;
   }
  }
  ((Rva0072EA60*)tile)->apply(left,bottom,right,top,changed);
 }
 if(field_30f8) {
  int y=field_2ff4->field_120ec,x=field_2ff4->field_120e8/16;
  if((x+1)*(y/16+1)<field_30dc) {
   int target=y*x/16;
   field_30fc=target;
   float low=0.0f,high=500.0f;
   for(;;) {
    int count=0,visible=0;
    W3DTerrainBackground *tile=field_30d8;
    for(int n=field_30dc;n>0;n--,tile++) if(tile->field_00!=2) {
     visible++; if(tile->field_54<high)count++;
    }
    if(visible<target) {field_30fc=field_30dc;break;}
    if(count>=target)break;
    low=high;high+=high;
   }
   if(field_30fc<field_30dc) {
    field_3100=low;
    for(int pass=20;pass>0;pass--) {
     float mid=(high+low)*0.5f;
     int count=0;
     W3DTerrainBackground *tile=field_30d8;
     for(int n=field_30dc;n>0;n--,tile++) if(tile->field_00!=2 && tile->field_54<mid)count++;
     if(count==field_30fc) {field_3100=mid;break;}
     if(count>field_30fc) high=mid; else {low=mid;field_3100=mid;}
    }
   }
  } else field_30fc=field_30dc;
 }
 if(culled!=Rva00EF8018 || t4!=Rva00EF8014 || t2!=Rva00EF8010) {
  Rva00EF8018=culled;Rva00EF8010=t2;Rva00EF8014=t4;
 }
 field_3178=3;
}

