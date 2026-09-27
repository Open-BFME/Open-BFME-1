// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_VOLUMETRIC_DELETE_LAYOUT /Iinputs/reference/shims/volumetricshadow /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// Native BFME RenderDynamicMeshVolume, RVA 007BC270, 1269 bytes.
// Ported from EA GPL-3.0-or-later GeneralsMD W3DVolumetricShadow.cpp.
// Identity: matched RenderVolume (007BD9C0) dispatches here for dynamic volumes.
// The ZH twin independently identifies geometry counts, buffer rings and drawing.
// BFME adds stencil bits from owner+34, retained release-build diagnostics,
// and device calls with separate base-vertex and stream-offset arguments.
// Layout observed in retail: owner render object +70; geometry table +80 with
// 160 entries per light; Geometry vertices +0 and active polygon/vertex counts
// +10/+14. Geometry::GetPolygonIndex is the named ZH twin of body 007B7FA0:
// it writes indices[polygon*3..+2] then returns indices+polygon; ILT 0000C563.
// Matrix4/Matrix3D inlines preserve the native construction/transpose copies.
// All unknown interface slots and object prefixes remain opaque.
#define Matrix4x4 Matrix4
#include "matrix4.h"
#include "shader.h"
#include <string.h>
struct ShadowBuffer007BC270 {
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0c();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1c();
 virtual void slot20();
 virtual void slot24();
 virtual void slot28();
 virtual int __stdcall Lock(unsigned offset,unsigned size,unsigned char** out,unsigned flags);
 virtual int __stdcall Unlock();
};
struct ShadowDevice007BC270 {
 virtual void slot000();
 virtual void slot004();
 virtual void slot008();
 virtual void slot00c();
 virtual void slot010();
 virtual void slot014();
 virtual void slot018();
 virtual void slot01c();
 virtual void slot020();
 virtual void slot024();
 virtual void slot028();
 virtual void slot02c();
 virtual void slot030();
 virtual void slot034();
 virtual void slot038();
 virtual void slot03c();
 virtual void slot040();
 virtual void slot044();
 virtual void slot048();
 virtual void slot04c();
 virtual void slot050();
 virtual void slot054();
 virtual void slot058();
 virtual void slot05c();
 virtual void slot060();
 virtual void slot064();
 virtual void slot068();
 virtual void slot06c();
 virtual void slot070();
 virtual void slot074();
 virtual void slot078();
 virtual void slot07c();
 virtual void slot080();
 virtual void slot084();
 virtual void slot088();
 virtual void slot08c();
 virtual void slot090();
 virtual void slot094();
 virtual void slot098();
 virtual void slot09c();
 virtual void slot0a0();
 virtual void slot0a4();
 virtual void slot0a8();
 virtual void slot0ac();
 virtual int __stdcall SetTransform(unsigned,const void*);
 virtual void slot0b4();
 virtual void slot0b8();
 virtual void slot0bc();
 virtual void slot0c0();
 virtual void slot0c4();
 virtual void slot0c8();
 virtual void slot0cc();
 virtual void slot0d0();
 virtual void slot0d4();
 virtual void slot0d8();
 virtual void slot0dc();
 virtual void slot0e0();
 virtual int __stdcall SetRenderState(unsigned,unsigned);
 virtual void slot0e8();
 virtual void slot0ec();
 virtual void slot0f0();
 virtual void slot0f4();
 virtual void slot0f8();
 virtual void slot0fc();
 virtual void slot100();
 virtual void slot104();
 virtual void slot108();
 virtual void slot10c();
 virtual void slot110();
 virtual void slot114();
 virtual void slot118();
 virtual void slot11c();
 virtual void slot120();
 virtual void slot124();
 virtual void slot128();
 virtual void slot12c();
 virtual void slot130();
 virtual void slot134();
 virtual void slot138();
 virtual void slot13c();
 virtual void slot140();
 virtual void slot144();
 virtual int __stdcall DrawIndexedPrimitive(unsigned,int,unsigned,unsigned,unsigned,unsigned);
 virtual void slot14c();
 virtual void slot150();
 virtual void slot154();
 virtual void slot158();
 virtual void slot15c();
 virtual void slot160();
 virtual void slot164();
 virtual void slot168();
 virtual void slot16c();
 virtual void slot170();
 virtual void slot174();
 virtual void slot178();
 virtual void slot17c();
 virtual void slot180();
 virtual void slot184();
 virtual void slot188();
 virtual void slot18c();
 virtual int __stdcall SetStreamSource(unsigned,ShadowBuffer007BC270*,unsigned,unsigned);
 virtual void slot194();
 virtual void slot198();
 virtual void slot19c();
 virtual int __stdcall SetIndices(ShadowBuffer007BC270*);
};
extern ShadowDevice007BC270* device01340534;
extern ShadowBuffer007BC270* shadowVertexBufferD3D;
extern ShadowBuffer007BC270* shadowIndexBufferD3D;
extern ShadowBuffer007BC270* lastActiveVertexBuffer;
extern int nShadowVertsInBuf,nShadowStartBatchVertex,nShadowIndicesInBuf,nShadowStartBatchIndex;
extern int SHADOW_VERTEX_SIZE,SHADOW_INDEX_SIZE;
struct W3DShadowManager { char pad[8]; int m_stencilShadowMask; int getStencilShadowMask(){return m_stencilShadowMask;} };
extern W3DShadowManager* TheW3DShadowManager;
class DX8Wrapper { public: static bool _EnableTriangleDraw; };
namespace Debug_Statistics { void Record_DX8_Polys_And_Vertices(int,int,const ShaderClass&); }
class ShadowLog007BC270 {
public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0c();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1c();
 virtual void slot20();
 virtual void slot24();
 virtual void slot28();
 virtual void slot2c();
 virtual void slot30();
 virtual ShadowLog007BC270* number(int);
 virtual ShadowLog007BC270* text(const char*);
 virtual void slot3c();
 virtual void slot40();
 virtual void slot44();
 virtual void slot48();
 virtual void end(int);
};
class ShadowDebug007BC270 { public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0c();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1c();
 virtual void slot20();
 virtual void slot24();
 virtual void slot28();
 virtual void slot2c();
 virtual void slot30();
 virtual void slot34();
 virtual void slot38();
 virtual void slot3c();
 virtual void slot40();
 virtual void slot44();
 virtual void slot48();
 virtual void slot4c();
 virtual void slot50();
 virtual void slot54();
 virtual void slot58();
 virtual void slot5c();
 virtual void begin();
 virtual void slot64();
 virtual void slot68();
 virtual ShadowLog007BC270* stream(int,int);
};
extern ShadowDebug007BC270* debug01336E5C;
bool _bfme_debugReportingEnabled();
void _bfme_debugRecordCallsite(int);
class RenderObjClass { public:
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual void slot0c(); virtual void slot10(); virtual void slot14();
 virtual const char* Get_Name() const;
};
struct Geometry {
 Vector3* m_verts;
 unsigned short* m_indices;
 int m_numPolygon,m_numVertex,m_numActivePolygon,m_numActiveVertex;
 unsigned short* GetPolygonIndex(long,short*) const;
 Vector3* GetVertex(int i){return &m_verts[i];}
 int GetNumActiveVertex(){return m_numActiveVertex;}
 int GetNumActivePolygon(){return m_numActivePolygon;}
};
class W3DVolumetricShadow {
protected:
 void RenderDynamicMeshVolume(int,int,const Matrix3D*);
 char pad00[0x34]; int bitsAt0034; char pad38[0x38];
 RenderObjClass* m_robj; char pad74[0xc];
 Geometry* m_shadowVolume[1][160];
};
void W3DVolumetricShadow::RenderDynamicMeshVolume(int meshIndex,int lightIndex,const Matrix3D* meshXform)
{
 Geometry* geometry;
 int numVerts,numPolys,numIndex;
 Vector3* pvVertices;
 unsigned short* pvIndices;
 ShadowDevice007BC270* m_pDev=device01340534;
 if(!m_pDev) return;
 int playerColor=(bitsAt0034>>7)&7;
 if(playerColor) {
  unsigned mask=TheW3DShadowManager->getStencilShadowMask();
  unsigned stencil=playerColor<<4;
  m_pDev->SetRenderState(58,((((stencil<<8)|stencil)<<8|stencil)<<8)|mask|stencil);
  m_pDev->SetRenderState(57,stencil);
 }
 geometry=m_shadowVolume[lightIndex][meshIndex];
 numVerts=geometry->GetNumActiveVertex();
 numPolys=geometry->GetNumActivePolygon();
 numIndex=numPolys*3;
 if(numVerts==0 || numPolys==0) return;
 if(numVerts>SHADOW_VERTEX_SIZE) {
  if(_bfme_debugReportingEnabled()) {
   _bfme_debugRecordCallsite(1);
   debug01336E5C->begin();
   debug01336E5C->stream(0,0)->text("Shadow geometry for ")->text(m_robj->Get_Name())->text(" has too many vertices (")->number(numVerts)->text(" with a limit of ")->number(SHADOW_VERTEX_SIZE)->text("). Either reduce the geometric complexity or have engineering increase SHADOW_VERTEX_SIZE. Unless this is fixed the given object will not have a volumetric shadow. [mh]")->end(2);
  }
  return;
 }
 if(numIndex>SHADOW_INDEX_SIZE) {
  if(_bfme_debugReportingEnabled()) {
   _bfme_debugRecordCallsite(1);
   debug01336E5C->begin();
   debug01336E5C->stream(0,0)->text("Shadow geometry for ")->text(m_robj->Get_Name())->text(" has too many indices (")->number(numIndex)->text(" with a limit of ")->number(SHADOW_INDEX_SIZE)->text("). Either reduce the geometric complexity or have engineering increase SHADOW_INDEX_SIZE. Unless this is fixed the given object will not have a volumetric shadow. [mh]")->end(2);
  }
  return;
 }
 if(nShadowVertsInBuf>SHADOW_VERTEX_SIZE-numVerts) {
  if(shadowVertexBufferD3D->Lock(0,numVerts*sizeof(Vector3),(unsigned char**)&pvVertices,0x2000)!=0)return;
  nShadowVertsInBuf=0; nShadowStartBatchVertex=0;
 } else {
  if(shadowVertexBufferD3D->Lock(nShadowVertsInBuf*sizeof(Vector3),numVerts*sizeof(Vector3),(unsigned char**)&pvVertices,0x1000)!=0)return;
 }
 if(pvVertices) memcpy(pvVertices,geometry->GetVertex(0),numVerts*sizeof(Vector3));
 shadowVertexBufferD3D->Unlock();
 if(nShadowIndicesInBuf>SHADOW_INDEX_SIZE-numIndex) {
  if(shadowIndexBufferD3D->Lock(0,numIndex*sizeof(short),(unsigned char**)&pvIndices,0x2000)!=0)return;
  nShadowIndicesInBuf=0; nShadowStartBatchIndex=0;
 } else {
  if(shadowIndexBufferD3D->Lock(nShadowIndicesInBuf*sizeof(short),numIndex*sizeof(short),(unsigned char**)&pvIndices,0x1000)!=0)return;
 }
 if(pvIndices) memcpy(pvIndices,geometry->GetPolygonIndex(0,(short*)pvIndices),numPolys*3*sizeof(short));
 shadowIndexBufferD3D->Unlock();
 m_pDev->SetIndices(shadowIndexBufferD3D);
 Matrix4 mWorld(*meshXform);
 m_pDev->SetTransform(256,&mWorld.Transpose());
 if(shadowVertexBufferD3D!=lastActiveVertexBuffer) {
  m_pDev->SetStreamSource(0,shadowVertexBufferD3D,0,sizeof(Vector3));
  lastActiveVertexBuffer=shadowVertexBufferD3D;
 }
 if(DX8Wrapper::_EnableTriangleDraw) {
  Debug_Statistics::Record_DX8_Polys_And_Vertices(numPolys,numVerts,ShaderClass::_PresetOpaqueShader);
  m_pDev->DrawIndexedPrimitive(4,nShadowStartBatchVertex,0,numVerts,nShadowStartBatchIndex,numPolys);
 }
 if(playerColor) {
  m_pDev->SetRenderState(58,TheW3DShadowManager->getStencilShadowMask());
  m_pDev->SetRenderState(57,0x80808080);
 }
 nShadowVertsInBuf+=numVerts; nShadowStartBatchVertex=nShadowVertsInBuf;
 nShadowIndicesInBuf+=numIndex; nShadowStartBatchIndex=nShadowIndicesInBuf;
}
