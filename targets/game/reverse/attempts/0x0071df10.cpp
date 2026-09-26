// ?rva0071DF10@W3DShrubBuffer@@QAEXPAX@Z
// partial score=0.6401785714285714 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/shims/sweep
// Native shrub vertex/index loader at RVA 0x0071DF10; target size 2239.
// See targets/game/reverse/identity_evidence/0071df10.md for independent
// boundary, layout, callee contracts, corrected behavior and remaining residue.
// This bank emits 2240 bytes and is NOT a matched conversion.
// Keep the opaque method spelling: the matched renderer proves its owner,
// while no independently named caller proves an original method spelling.
#include "dx8indexbuffer.h"
#include "dx8vertexbuffer.h"
#include "matrix3d.h"
#include "sphere.h"
#include "vector2.h"
#include "vertmaterial.h"
typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
class GlobalData {
public:
  struct TerrainLighting {
    float ambient[3], diffuse[3], direction[3];
  };
  char p0[0x218];
  int timeOfDay;
  char p21c[0x4ac - 0x21c];
  TerrainLighting objectLighting[4][3];
  char p65c[0xdbc - 0x65c];
  bool fieldDBC;
  char pDBD[0x1220 - 0xdbd];
  float field1220;
};
extern GlobalData *TheWritableGlobalData;
extern float g_bfmeDefaultBU;

class RenderObjClass;
template <class T> class RefMultiListIterator;
typedef RefMultiListIterator<RenderObjClass> RefRenderObjListIterator;
template <int N> class Rva0071DF10Slots : public Rva0071DF10Slots<N - 1> {
public:
  virtual void slot(char (*)[N]) = 0;
};
template <> class Rva0071DF10Slots<0> {};
template <class T> struct Rva0071DF10Buffer {
  char m_head[0xc];
  T *m_array;
};
struct TriIndex {
  unsigned short I, J, K;
};
struct Rva0071DF10MatDesc {
  char m_pad00[0xc];
  Rva0071DF10Buffer<Vector2> *m_uv[8];
  char m_pad2c[0x4c - 0x2c];
  Rva0071DF10Buffer<unsigned> *m_color[2];
  __forceinline const Vector2 *Get_UV_Array_By_Index(int i) const {
    return m_uv[i] ? m_uv[i]->m_array : 0;
  }
  __forceinline const unsigned *Get_Color_Array(int i, bool) const {
    return m_color[i] ? m_color[i]->m_array : 0;
  }
};
struct Rva009272E0Mesh {
  char m_pad00[0x24];
  Int m_polygons, m_vertices;
  Rva0071DF10Buffer<TriIndex> *m_polygonArray;
  Rva0071DF10Buffer<Vector3> *m_vertexArray;
  char m_pad34[0x9c - 0x34];
  Rva0071DF10MatDesc *m_matDesc;
  Int Get_Vertex_Count() const { return m_vertices; }
  Int Get_Polygon_Count() const { return m_polygons; }
  Vector3 *Get_Vertex_Array() const { return m_vertexArray->m_array; }
  const TriIndex *Get_Polygon_Array() const {
    return m_polygonArray->m_array;
  }
  __forceinline const Vector2 *Get_UV_Array_By_Index(int i) const {
    return m_matDesc->Get_UV_Array_By_Index(i);
  }
  __forceinline const unsigned *Get_Color_Array(int i, bool create) const {
    return m_matDesc->Get_Color_Array(i, create);
  }
  const Vector3 *rva009272e0(int);
};
class MaterialInfoClass {
public:
  virtual void Delete_This() = 0;
  Int m_refCount;
  char m_pad08[4];
  VertexMaterialClass **m_materials;
  VertexMaterialClass *Peek_Vertex_Material(int i) const {
    return m_materials[i];
  }
  void Release_Ref() {
    if (--m_refCount == 0)
      Delete_This();
  }
};
class MeshClass : public Rva0071DF10Slots<84> {
public:
  virtual MaterialInfoClass *Get_Material_Info() = 0; // slot +0x150
  char m_pad04[0xc8 - 4];
  Rva009272E0Mesh *m_model;
  Rva009272E0Mesh *Peek_Model() const { return m_model; }
};
struct Rva0071DF10ShrubRecord {
  Vector3 m_location;
  Real m_scale;
  Matrix3D m_matrix;
  Int m_type;
  Bool m_visible;
  UnsignedByte m_pad0045[0x5c - 0x45];
  Int m_matchingKey;
  Real m_pushAside;
  Real m_pushAsideDelta;
  Real m_pushAsideSin;
  Real m_pushAsideCos;
  Int m_pushAsideSource;
  UnsignedInt m_lastFrameUpdated;
  Int m_nextInPartition;
  Int m_swayType;
  Int m_firstIndex;
  Int m_bufferNdx;
  Int m_state88;
  Int m_state8c;
  Int m_state90;
  Int m_sinkFrames;
  void *m_toppleObject;
  void *m_pushAsideObject;
  Int m_stateA0;
};

struct Rva0071DF10TreeType {
  MeshClass *m_mesh;
  Vector3 m_offset;
  SphereClass m_bounds;
  const void *m_data;
  Real m_uScale;
  Real m_vScale;
  unsigned char m_pad002c[8];
  Real m_uOffset;
  Real m_vOffset;
  unsigned char m_pad003c[8];
  UnsignedByte m_doShadow;
  UnsignedByte m_pad0045[3];
  unsigned char m_tail[0x5c - 0x48];
};

class Rva0071DF10GlobCC0 {
public:
  virtual void slot00(void);
  virtual void slot04(void);
  virtual void slot08(void);
  virtual void slot0c(void);
  virtual void slot10(void);
  virtual void slot14(void);
  virtual void slot18(void);
  virtual void slot1c(void);
  virtual void slot20(void);
  virtual void slot24(void);
  virtual bool slot28(void);
  virtual void slot2c(void);
  virtual void slot30(void);
  virtual void slot34(Vector3 *value);
};

extern Rva0071DF10GlobCC0 *g_bfmeGlobCC0;

class W3DShrubBuffer {
public:
  void rva0071DF10(void *pDynamicLightsIterator);

protected:
  UnsignedInt doLighting(const Vector3 *, const GlobalData::TerrainLighting *,
                         const Vector3 *, UnsignedInt, Real) const;

private:
  void *m_objectVtable;
  VertexBufferClass *m_vertexTree[20];
  IndexBufferClass *m_indexTree[20];
  unsigned char m_pad00a4[0x14a8 - 0xa4];
  Int m_curNumTreeVertices[20];
  Int m_curNumTreeIndices[20];
  Rva0071DF10ShrubRecord m_trees[12000];
  Int m_numTrees;
  Bool m_anythingChanged;
  UnsignedByte m_anyPushChanged;
  UnsignedByte m_updateAllKeys;
  Bool m_initialized;
  UnsignedByte m_isTerrainPass;
  UnsignedByte m_needToUpdateTexture;
  UnsignedByte m_pad1e1cd2[2];
  Rva0071DF10TreeType m_treeTypes[64];
  Int m_numTreeTypes;
  Vector3 m_cameraLookAtVector;
  unsigned char m_pad1e33e4[0x1e3918 - 0x1e33e4];
  Int m_numBuffers;
  unsigned char m_pad1e391c[4];
  Int m_globalBufferCount;
};

void W3DShrubBuffer::rva0071DF10(void *pDynamicLightsIterator) {
  if (!m_indexTree[0] || !m_vertexTree[0] || !m_initialized)
    return;
  if (!m_anythingChanged)
    return;

  Real lightingScale = 1.0f;
  GlobalData *globalData = TheWritableGlobalData;
  if (globalData != 0) {
    if (globalData->fieldDBC != 0 && *(Int *)((char *)this + 0xa4) == 0)
      lightingScale = 2.0f;
    lightingScale *= globalData->field1220;
  }

  Rva0071DF10GlobCC0 *globCC0 = g_bfmeGlobCC0;
  if (globCC0 != 0 && globCC0->slot28()) {
    Vector3 value;
    (g_bfmeGlobCC0)->slot34(&value);
    lightingScale *= g_bfmeDefaultBU - value.X;
  }

  Int curTree = 0;
  const GlobalData::TerrainLighting *objectLighting =
      TheWritableGlobalData->objectLighting[TheWritableGlobalData->timeOfDay];
  Int bNdx;
  for (bNdx = 0; bNdx < m_numBuffers; bNdx++) {
    m_curNumTreeVertices[bNdx] = 0;
    m_curNumTreeIndices[bNdx] = 0;
    if (curTree >= m_numTrees)
      break;

    VertexFormatXYZNDUV1 *vb;
    UnsignedShort *ib;
    IndexBufferClass::WriteLockClass lockIdxBuffer(m_indexTree[bNdx], 0);
    VertexBufferClass::WriteLockClass lockVtxBuffer(m_vertexTree[bNdx], 0);
    vb = (VertexFormatXYZNDUV1 *)lockVtxBuffer.Get_Vertex_Array();
    ib = lockIdxBuffer.Get_Index_Array();

    Vector2 lookAtVector(m_cameraLookAtVector.X, m_cameraLookAtVector.Y);
    lookAtVector.Normalize();
    UnsignedShort *curIb = ib;
    VertexFormatXYZNDUV1 *curVb = vb;

    for (; curTree < m_numTrees; curTree += m_globalBufferCount) {
      Int type = m_trees[curTree].m_type;
      if (type < 0 || !m_trees[curTree].m_visible ||
          m_trees[curTree].m_state88 != 0 || m_trees[curTree].m_stateA0 >= 4 ||
          m_trees[curTree].m_stateA0 <= 0)
        continue;

      Real scale = m_trees[curTree].m_scale;
      Vector3 loc = m_trees[curTree].m_location;
      if (m_treeTypes[type].m_mesh == 0)
        continue;

      bool doVertexLighting = true;
      Vector3 emissive(0.0f, 0.0f, 0.0f);
      MaterialInfoClass *matInfo =
          m_treeTypes[type].m_mesh->Get_Material_Info();
      if (matInfo) {
        VertexMaterialClass *vertMat = matInfo->Peek_Vertex_Material(0);
        if (vertMat)
          vertMat->Get_Emissive(&emissive);
      }
      if (matInfo) {
        matInfo->Release_Ref();
        matInfo = 0;
      }

      Int startVertex = m_curNumTreeVertices[bNdx];
      m_trees[curTree].m_firstIndex = startVertex;
      m_trees[curTree].m_bufferNdx = bNdx;

      Int numVertex =
          m_treeTypes[type].m_mesh->Peek_Model()->Get_Vertex_Count();
      Vector3 *pVert =
          m_treeTypes[type].m_mesh->Peek_Model()->Get_Vertex_Array();
      if (numVertex + m_curNumTreeVertices[bNdx] + 2 >= 0x7530)
        break;

      Int numIndex =
          m_treeTypes[type].m_mesh->Peek_Model()->Get_Polygon_Count();
      const TriIndex *pPoly =
          m_treeTypes[type].m_mesh->Peek_Model()->Get_Polygon_Array();
      if (m_curNumTreeIndices[bNdx] + 3 * numIndex + 6 >= 0xea60)
        break;

      const Vector2 *uvs =
          m_treeTypes[type].m_mesh->Peek_Model()->Get_UV_Array_By_Index(0);
      const Vector3 *normals =
          m_treeTypes[type].m_mesh->Peek_Model()->rva009272e0(0);
      const unsigned *vecDiffuse =
          m_treeTypes[type].m_mesh->Peek_Model()->Get_Color_Array(0, false);
      UnsignedInt diffuse = 0;
      if (normals == 0) {
        doVertexLighting = false;
        Vector3 normal(0.0f, 0.0f, 1.0f);

        diffuse = doLighting(&normal, objectLighting, &emissive, 0xffffffff,
                             lightingScale);
      }

      Int i;
      Real Uscale = m_treeTypes[type].m_uScale;
      Real Vscale = m_treeTypes[type].m_vScale;
      Real UOffset = m_treeTypes[type].m_uOffset;
      Real VOffset = m_treeTypes[type].m_vOffset;
      for (i = 0; i < numVertex; i++) {
        if (m_curNumTreeVertices[bNdx] >= 0x7530)
          break;

        Real U = uvs[i].U;
        Real V = uvs[i].V;
        if (U > 1.0f)
          U = 1.0f;
        if (U < 0.0f)
          U = 0.0f;
        if (V > 1.0f)
          V = 1.0f;
        if (V < 0.0f)
          V = 0.0f;
        curVb->u1 = U * Uscale + UOffset;
        curVb->v1 = V * Vscale + VOffset;

        Vector3 offsetVertex = pVert[i];
        offsetVertex.X += m_treeTypes[type].m_offset.X;
        offsetVertex.Y += m_treeTypes[type].m_offset.Y;
        offsetVertex.Z += m_treeTypes[type].m_offset.Z;
        Vector3 vLoc;
        Matrix3D::Transform_Vector(m_trees[curTree].m_matrix, offsetVertex,
                                   &vLoc);
        vLoc *= scale;
        if (m_trees[curTree].m_pushAside > 0.0f) {

          vLoc.X += pVert[i].Z * m_trees[curTree].m_pushAside *
                    m_trees[curTree].m_pushAsideCos *
                    *(Real *)((char *)m_treeTypes[type].m_data + 0x18);
          vLoc.Y += pVert[i].Z * m_trees[curTree].m_pushAside *
                    m_trees[curTree].m_pushAsideSin *
                    *(Real *)((char *)m_treeTypes[type].m_data + 0x18);
        }
        vLoc.X += loc.X;
        vLoc.Y += loc.Y;
        vLoc.Z += loc.Z;

        curVb->x = vLoc.X;
        curVb->y = vLoc.Y;
        curVb->z = vLoc.Z;
        curVb->nx = *(const bool *)((char *)m_treeTypes[m_trees[curTree].m_type]
                                        .m_data +
                                    0x54)
                        ? 0
                        : m_trees[curTree].m_swayType;
        curVb->ny = *(Real *)((char *)m_treeTypes[type].m_data + 0x1c) *
                    m_trees[curTree].m_pushAside;
        curVb->nz = loc.Z;
        curVb->ny = g_bfmeDefaultBU - curVb->ny;

        if (doVertexLighting) {
          Vector3 normal;
          Matrix3D::Transform_Vector(m_trees[curTree].m_matrix, normals[i],
                                     &normal);
          UnsignedInt vertexDiffuse = vecDiffuse ? vecDiffuse[i] : 0xffffffff;

          curVb->diffuse = doLighting(&normal, objectLighting, &emissive,
                                      vertexDiffuse, lightingScale);
        } else {
          curVb->diffuse = diffuse;
        }
        ++curVb;
        ++m_curNumTreeVertices[bNdx];
      }

      {
        for (i = 0; i < numIndex; i++) {
          if (m_curNumTreeIndices[bNdx] + 4 > 0xea60)
            break;
          *curIb++ = startVertex + pPoly[i].I;
          *curIb++ = startVertex + pPoly[i].J;
          *curIb++ = startVertex + pPoly[i].K;
          m_curNumTreeIndices[bNdx] += 3;
        }
      }
    }
  }
}
