// ?d_00766aa0@@YAXXZ
// partial score=0.9747069710055521 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad
// Retail 00766AA0: opaque owner retained from independently matched caller 00769C30.
// Bank only: 3386/3386 bytes; 82 concrete differences after 144 relocation bytes.
// The old bank used X/50% classification and an artificial 48-byte frame filler.
// Retail uses Z/2%, both root and validated mesh matrices, and a scalar helper out.
// Narrow model view follows MeshGeometryClass witnesses at +24/+28/+30; the
// current shared header places these fields four bytes later than this body.
// See identity_evidence/00766aa0-geometry-recovery.md for ABI and failed levers.
#include "mesh.h"
#include "meshmdl.h"
#include "ascii_string.h"
#include "coord3d.h"
template <> inline const char *StringBase<char>::str()const{return m_data?m_data->data:"";}
inline void Coord3D::set(float a,float b,float c){x=a;y=b;z=c;}
struct Rva00766AA0Buffer {
 Coord3D point00,point0c;float width18;
 Coord3D point1c,point28,point34,point40;
};
struct Rva00766AA0Model {char pad[0x24];int polygons24;int vertices28;int field2c;ShareBufferClass<Vector3> *vertices30;};
struct Rva00766AA0Object {char pad[8];Matrix3D transform;};
struct Rva00766AA0Drawable {char pad[0xfc];Rva00766AA0Object *object;};
struct Rva00766AA0Data {char pad[0x69];bool flag69;};
class BfmeCalc919G {public:int bfmeCalc919G();};
class AttachmentTransform007629F0 {public:void adjust(Matrix3D &);};
// Same thunk-member ABI witnessed by matched Rva00767B30ObjectDrawLookup.
extern void j_0002e7b7();
class Rva00763AC0Owner {
public:void *rva00763AC0(RenderObjClass *object,float *height){
 typedef void *(Rva00763AC0Owner::*Function)(RenderObjClass *,float *);
 union{void(*raw)();Function member;}fn;fn.raw=j_0002e7b7;
 return (this->*fn.member)(object,height);
}
};
class Rva00766AA0RenderSlots {
public:
 virtual void s00();virtual void s04();virtual void s08();virtual void s0c();virtual void s10();
 virtual RenderObjClass *slot14();
};
#define SLOT(n) virtual void slot##n();
class Rva00766AA0Owner {
public:
 SLOT(00) SLOT(04) SLOT(08) SLOT(0C) SLOT(10) SLOT(14) SLOT(18) SLOT(1C)
 SLOT(20) SLOT(24) SLOT(28) SLOT(2C) SLOT(30) SLOT(34) SLOT(38) SLOT(3C)
 SLOT(40) SLOT(44) SLOT(48) SLOT(4C) SLOT(50) SLOT(54) SLOT(58) SLOT(5C)
 SLOT(60) SLOT(64) SLOT(68) SLOT(6C) SLOT(70) SLOT(74) SLOT(78) SLOT(7C)
 SLOT(80) SLOT(84) SLOT(88) SLOT(8C) SLOT(90) SLOT(94) SLOT(98) SLOT(9C)
 SLOT(A0) SLOT(A4) SLOT(A8) SLOT(AC) SLOT(B0) SLOT(B4)
 virtual RenderObjClass *slotB8();
 Rva00766AA0Data *data04;Rva00766AA0Drawable *drawable08;
 bool forward00769C30(Rva00766AA0Buffer *,AsciiString,void **,void **);
};
#undef SLOT
bool Rva00766AA0Owner::forward00769C30(Rva00766AA0Buffer *result,AsciiString name,void **argument2,void **argument3)
{
 RenderObjClass *renderObject=0;
 RenderObjClass *root=slotB8();
 if(argument2)*argument2=0;
 if(argument3)*argument3=0;
 if(root){
  RenderObjClass *held=root->Get_Sub_Object_By_Name(name.str(),0);
  if(held){
   renderObject=reinterpret_cast<Rva00766AA0RenderSlots*>(held)->slot14();
   if(!renderObject)held->Release_Ref();
  }
 }
 Rva00766AA0Object *object=drawable08->object;
 if(!object){if(renderObject)renderObject->Release_Ref();return false;}
 Matrix3D matrix(true);
 if(data04->flag69){
  const Matrix3D *cached=reinterpret_cast<const Matrix3D*>(reinterpret_cast<BfmeCalc919G*>(drawable08)->bfmeCalc919G());
  matrix.Set_Translation(cached->Get_Translation());
 }else matrix=object->transform;
 reinterpret_cast<AttachmentTransform007629F0*>(this)->adjust(matrix);
 if(root)root->Set_Transform(matrix);
 if(renderObject){
  if(renderObject->Class_ID()==RenderObjClass::CLASSID_MESH){
   if(argument3){renderObject->Add_Ref();*argument3=renderObject;}
   MeshClass *mesh=static_cast<MeshClass*>(renderObject);
   if(argument2 && reinterpret_cast<Rva00766AA0Model*>(mesh->Peek_Model())->polygons24>2){
    float height;renderObject->Add_Ref();
    *argument2=reinterpret_cast<Rva00763AC0Owner*>(this)->rva00763AC0(renderObject,&height);
   }
   if(result){
    Matrix3D world(renderObject->Get_Transform());
    int count=reinterpret_cast<Rva00766AA0Model*>(mesh->Peek_Model())->vertices28;
    Vector3 *vertices=reinterpret_cast<Rva00766AA0Model*>(mesh->Peek_Model())->vertices30->Get_Array();
    float maxZ=vertices[0].Z,minZ=maxZ;
    for(int i=1;i<count;++i){if(vertices[i].Z<minZ)minZ=vertices[i].Z;if(maxZ<vertices[i].Z)maxZ=vertices[i].Z;}
    float band=(maxZ-minZ)*0.02f;
    Vector3 lowA(0,0,0),lowB(0,0,0),highA(0,0,0),highB(0,0,0);
    bool haveLow=false,haveHigh=false;
    for(int j=0;j<count;++j){
     const Vector3 &v=vertices[j];
     if(v.Z<minZ+band){
      if(haveLow){if((lowA-lowB).Length2()<(lowA-v).Length2())lowB=v;}
      else{lowA=lowB=v;haveLow=true;}
     }else if(v.Z>maxZ-band){
      if(haveHigh){if((highA-highB).Length2()<(highA-v).Length2())highB=v;}
      else{highA=highB=v;haveHigh=true;}
     }
    }
    if(!haveLow || !haveHigh)return false;
    for(int k=0;k<count;++k){
     const Vector3 &v=vertices[k];
     if(v.Z<minZ+band){if((lowA-lowB).Length2()<(lowB-v).Length2())lowA=v;}
     else if(v.Z>maxZ-band){if((highA-highB).Length2()<(highA-v).Length2())highB=v;}
    }
    Vector3 low;Matrix3D::Transform_Vector(world,(lowA+lowB)*0.5f,&low);
    Vector3 high;Matrix3D::Transform_Vector(world,(highA+highB)*0.5f,&high);
    float highWidth=(highA-highB).Length(),lowWidth=(lowA-lowB).Length();
    maxZ=(lowWidth+highWidth)*0.5f;
    result->point00.set(high.X,high.Y,high.Z);
    result->point0c.set(low.X,low.Y,low.Z);
    result->width18=maxZ;
    if(reinterpret_cast<Rva00766AA0Model*>(mesh->Peek_Model())->polygons24>2){
     low.X=world[0][0]*lowA.X+world[0][1]*lowA.Y+world[0][2]*lowA.Z+world[0][3];
     low.Y=world[1][0]*lowA.X+world[1][1]*lowA.Y+world[1][2]*lowA.Z+world[1][3];
     low.Z=world[2][0]*lowA.X+world[2][1]*lowA.Y+world[2][2]*lowA.Z+world[2][3];
     result->point34.set((int)low.X,(int)low.Y,(int)low.Z);
     low.X=world[0][0]*lowB.X+world[0][1]*lowB.Y+world[0][2]*lowB.Z+world[0][3];
     low.Y=world[1][0]*lowB.X+world[1][1]*lowB.Y+world[1][2]*lowB.Z+world[1][3];
     low.Z=world[2][0]*lowB.X+world[2][1]*lowB.Y+world[2][2]*lowB.Z+world[2][3];
     result->point40.set((int)low.X,(int)low.Y,(int)low.Z);
     low.X=world[0][0]*highA.X+world[0][1]*highA.Y+world[0][2]*highA.Z+world[0][3];
     low.Y=world[1][0]*highA.X+world[1][1]*highA.Y+world[1][2]*highA.Z+world[1][3];
     low.Z=world[2][0]*highA.X+world[2][1]*highA.Y+world[2][2]*highA.Z+world[2][3];
     result->point1c.set((int)low.X,(int)low.Y,(int)low.Z);
     low.X=world[0][0]*highB.X+world[0][1]*highB.Y+world[0][2]*highB.Z+world[0][3];
     low.Y=world[1][0]*highB.X+world[1][1]*highB.Y+world[1][2]*highB.Z+world[1][3];
     low.Z=world[2][0]*highB.X+world[2][1]*highB.Y+world[2][2]*highB.Z+world[2][3];
     result->point28.set((int)low.X,(int)low.Y,(int)low.Z);
    }else{
     Vector3 direction=low-high;Vector3 side(-direction.Y,direction.X,0);side.Normalize();
     
     result->point1c.x=high.X+(side.X*maxZ*0.5f);
     result->point1c.y=high.Y+(side.Y*maxZ*0.5f);
     result->point1c.z=high.Z+(side.Z*maxZ*0.5f);
     result->point28.x=high.X-(side.X*maxZ*0.5f);
     result->point28.y=high.Y-(side.Y*maxZ*0.5f);
     result->point28.z=high.Z-(side.Z*maxZ*0.5f);
     result->point34.x=low.X+(side.X*maxZ*0.5f);
     result->point34.y=low.Y+(side.Y*maxZ*0.5f);
     result->point34.z=low.Z+(side.Z*maxZ*0.5f);
     result->point40.x=low.X-(side.X*maxZ*0.5f);
     result->point40.y=low.Y-(side.Y*maxZ*0.5f);
     result->point40.z=low.Z-(side.Z*maxZ*0.5f);
    }
   }
   renderObject->Release_Ref();return true;
  }
  renderObject->Release_Ref();
 }
 return false;
}
