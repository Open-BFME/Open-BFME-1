// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// Retail 006F8A60; existing pin and matched caller Rva006F9900AddElement.cpp
// prove the receiver and bool init ABI. The exact underlying class identity
// remains the established BaseHeightMapFloorElement address-view identity.
// Executable body: 786 bytes through RET at 006F8D71. Its two-byte padding
// and five-entry switch table at 006F8D74 also match through 006F8D87.
// MeshGeometryClass VertexCount +28 and Vertex +30 are name_oracle witnesses;
// current native headers differ at these two offsets, so retain the retail view.
// Gen_0092F0A0 and Gen_005D2040 retain existing landed callee spellings.
// Their one-pointer texture handles use a 16-bit refcount and native release.
#include "ascii_string.h"
#include "mesh.h"
#include "meshmdl.h"
#include "matinfo.h"
#include "texture.h"
#include "sphere.h"
// Canonical string storage; these are the inlines witnessed in 006F8A60.
template <> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }
template <> inline int StringBase<char>::getLength() const { return m_data ? m_data->length : 0; }
template <> inline void StringBase<char>::clear() { releaseBuffer(); }
template <> inline void StringBase<char>::concat(const StringBase<char> &s) { concat(s.str(),s.getLength()); }
struct BfmeR1025;
char bfmeGo1025F(BfmeR1025 *);
RenderObjClass *Create_Render_Obj(const char *);
class Gen_005D2040 {
public:
 TextureBaseClass *p;
 Gen_005D2040 &operator=(const Gen_005D2040 &);
 ~Gen_005D2040() { if (p) p->Release_Ref(); }
};
class BfmeHandleCX : public Gen_005D2040 {};
class Gen_0092F0A0 { public: BfmeHandleCX bfmeGet(int) const; };
class BaseHeightMapFloorElement {
public:
 bool init006F8A60();
};
bool BaseHeightMapFloorElement::init006F8A60()
{
 TextureBaseClass *&texture = *(TextureBaseClass **)((char *)this+0x20);
 MeshClass *&mesh = *(MeshClass **)((char *)this+0x24);
 if (texture) { texture->Release_Ref(); texture=0; }
 if (mesh) { mesh->Release_Ref(); mesh=0; }
 AsciiString suffix;
 AsciiString filename;
 if (*((char *)this+0x7d)) {
  switch (*(int *)(*(char **)0x012ED5AC+0x16c4)) {
  case 0: case 1: suffix="L"; break;
  case 2: suffix="M"; break;
  case 3: case 4: suffix.clear(); break;
  }
 }
 AsciiString &name=*(AsciiString *)((char *)this+0x88);
 filename=name;
 filename.concat(suffix);
 if (!bfmeGo1025F((BfmeR1025 *)&filename)) filename=name;
 RenderObjClass *obj=Create_Render_Obj(filename.str());
 if (obj) {
  Vector3 offset(0,0,0);
  if (obj->Class_ID()==25) {
   RenderObjClass *parent=obj;
   obj=obj->Get_Sub_Object(0);
   Matrix3D boneMatrix=obj->Get_Bone_Transform(0);
   offset=boneMatrix.Get_Translation();
   parent->Release_Ref();
  }
  *(Vector3 *)((char *)this+0x2c)=offset;
  if (obj->Class_ID()==0) mesh=(MeshClass *)obj->_bfme_ro_v3();
  if (mesh==0) { obj->Release_Ref(); return false; }
  char *model = (char *)mesh->Peek_Model();
  int count=*(int *)(model+0x28);
  Vector3 *vertices=*(Vector3 **)(*(char **)(model+0x30)+0xc);
  SphereClass sphere(vertices,count);
  sphere.Center+=offset;
  *(SphereClass *)this=sphere;
  *(SphereClass *)((char *)this+0x10)=sphere;
  Matrix3D &matrix=*(Matrix3D *)((char *)this+0x4c);
  matrix.Make_Identity();
  matrix.Set_Translation(offset);
  *(Vector3 *)((char *)this+0x2c)=offset;
  MaterialInfoClass *info=mesh->Get_Material_Info();
  if (info) {
   if (*(int *)((char *)info+0x30)>0) {
    *(Gen_005D2040 *)&texture=((Gen_0092F0A0 *)info)->bfmeGet(0);
   }
   info->Release_Ref();
  }
  return true;
 }
 return false;
}
