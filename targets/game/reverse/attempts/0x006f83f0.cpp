// ?d_006f83f0@@YAXXZ
// partial score=0.8463 date=2026-09-27
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// 006F83F0 mesh vertex transform and terrain lighting. Existing typed pin
// and the 006F8700 wrapper establish the preserved address-derived ABI.
// MeshModelClass CurMatDesc +9c is confirmed by name_oracle.
// Owner offsets are witnessed by this body; owner identity remains unknown.
#define Matrix4x4 Matrix4  // BFME renamed it
#include "W3DDevice/GameClient/W3DBridgeBuffer.h"
#include <stdio.h>
#include <string.h>
#include "W3DDevice/GameClient/W3DAssetManager.h"
#include <texture.h>
#include "common/GlobalData.h"
#include "common/RandomValue.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "GameClient/TerrainRoads.h"
#include "GameLogic/Damage.h"
#include "GameLogic/Module/BodyModule.h"
#include "W3DDevice/GameLogic/W3DTerrainLogic.h"
#include "W3DDevice/GameClient/TerrainTex.h"
#include "W3DDevice/GameClient/HeightMap.h"
#include "W3DDevice/GameClient/W3DDynamicLight.h"
#include "W3DDevice/GameClient/Module/W3DModelDraw.h"
#include "W3DDevice/GameClient/W3DShaderManager.h"
#include "W3DDevice/GameClient/W3DShroud.h"
#include "WW3D2/Camera.h"
#include "WW3D2/DX8Wrapper.h"
#include "WW3D2/DX8Renderer.h"
#include "WW3D2/Mesh.h"
#include "WW3D2/MeshMdl.h"
#include "WW3D2/Scene.h"


#include "WW3D2/matinfo.h"
class Rva006F7DA0TreeBuffer {
public:
 static unsigned __stdcall doLighting(const GlobalData::TerrainLighting *, const Vector3 *, unsigned, float, unsigned);
};
// Existing typed pin at 006F8700 proves this four-argument ABI. Fields below
// are address-based views witnessed by the instructions at 006F83F0.
static __forceinline void transform006F83F0(const Matrix3D &A, const Vector3 &in, Vector3 *out) {
 Vector3 tmp; const Vector3 *v;
 if (out == &in) { tmp=in; v=&tmp; } else v=&in;
 out->X = A[0][0]*v->X + (*(volatile const float *)&A[0][1])*v->Y + A[0][2]*v->Z + A[0][3];
 out->Y = (*(volatile const float *)&A[1][0])*v->X + (*(volatile const float *)&A[1][1])*v->Y + (*(volatile const float *)&A[1][2])*v->Z + A[1][3];
 out->Z = A[2][0]*v->X + (*(volatile const float *)&A[2][1])*v->Y + A[2][2]*v->Z + A[2][3];
}
static __forceinline MeshMatDescClass *peekCurMatDesc006F83F0(MeshModelClass *model) { return *(MeshMatDescClass **)((char *)model+0x9c); }
class Rva006F8700Owner {
public:
 int rva006F83F0(void *, int, void *, void *);
 char padding00[0x28];
 char *field28;
 Vector3 field2c;
 char padding38[0x48];
 float field80;
};
int Rva006F8700Owner::rva006F83F0(void *destination, int curVertex, void *matrix, void *mesh)
{
 MeshClass *pMesh = (MeshClass *)mesh;
 if (pMesh == 0) return 0;
 char *provider = field28;
 float alpha;
 if (provider && *(volatile float *)(provider+0xb4) * *(float *)(provider+0xb0) != 1.0f)
  alpha = *(volatile float *)(provider+0xb4) * *(float *)(provider+0xb0);
 else alpha = field80;
 if (alpha < 0.0f) alpha = 0.0f;
 else if (alpha > 1.0f) alpha = 1.0f;
 unsigned alphaByte = (unsigned)(alpha * 255.0);
 char *global = *(char **)0x012ED5C8;
 const GlobalData::TerrainLighting *lighting = (const GlobalData::TerrainLighting *)(global+0x224+*(int *)(global+0x218)*0x6c);
 int count = pMesh->Peek_Model()->Get_Vertex_Count();
 Vector3 *vertices = pMesh->Peek_Model()->Get_Vertex_Array();
 if (curVertex + count + 2 >= 15000) return 0;
 Vector3 emissive(0,0,0);
 MaterialInfoClass *info = pMesh->Get_Material_Info();
 if (info) {
  VertexMaterialClass *material = info->Peek_Vertex_Material(0);
  if (material) material->Get_Emissive(&emissive);
  info->Release_Ref();
 }
 const Vector2 *uvs = (*(MeshMatDescClass **)((char *)pMesh->Peek_Model()+0x9c))->Get_UV_Array_By_Index(0,false);
 VertexFormatXYZNDUV1 *out = (VertexFormatXYZNDUV1 *)destination + curVertex;
 unsigned *colors = (*(MeshMatDescClass **)((char *)pMesh->Peek_Model()+0x9c))->Get_Color_Array(0,false);
 for (int i=0; i<count; ++i) {
  out->u1=uvs[i].U; out->v1=uvs[i].V;
  Vector3 vertex;
  transform006F83F0(*(const Matrix3D *)matrix, vertices[i], &vertex);
  Vector3 loc = vertex + field2c;
  out->x=loc.X; out->y=loc.Y; out->z=loc.Z;
  out->diffuse=Rva006F7DA0TreeBuffer::doLighting(lighting,&emissive,colors ? colors[i] : 0xffffffff,1.0f,alphaByte);
  ++out;
 }
 return count;
}

