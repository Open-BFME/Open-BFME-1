// ?loadTreesInVertexAndIndexBuffers@W3DTreeBuffer@@IAEXPAV?$RefMultiListIterator@VRenderObjClass@@@@@Z
// partial score=0.9540334855403348 date=2026-09-25
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWSaveLoad /Ireference/shims/sweep
// BFME tree vertex/index loading, RVA 0x00734CB0, full decoded size 3285.
// Derived from EA GeneralsMD W3DTreeBuffer.cpp, with retail-only layouts and
// per-tree transforms. Work in progress: all unfamiliar fields retain offsets.
// Capstone decodes [0x00734CB0,0x00735985); ret 4 at +0xCD2, then INT3.
// Native buffer-lock RAII matches the frame, unwind transitions and call order.
// Complete-object trees: +0x1B0, stride 0xE8, 12000 slots; types: +0x2A7CBC,
// stride 0x5C. This agrees with the landed BFME tree-buffer siblings.
// Remaining mismatch: x87 commutative term ordering in Normalize/postMul/
// Translate/Transform_Vector, plus light-color store scheduling. No asm shaping.
// Unpinned helpers are deliberately address-qualified: 0x009272E0 returns the
// normal-array pointer in EAX with ret 4; existing void bfmeGo998C is insufficient.
// 0x00732700 (via ILT 0x00032B0F) consumes four float-triple pointers, a packed
// diffuse color and integer alpha; ret 24 returns packed ARGB. It computes
// abs normal/light dot products, scales colors and clamps channels to 255.
// The exact original overload spelling of that lighting helper is unproved.
#include "matrix3d.h"
#include "vector2.h"
#include "dx8indexbuffer.h"
#include "dx8vertexbuffer.h"
#include "vertmaterial.h"

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned int UnsignedInt;
class RenderObjClass;
template<class T> class RefMultiListIterator;
typedef RefMultiListIterator<RenderObjClass> RefRenderObjListIterator;
struct Rva00734CB0Color { Real red,green,blue; };
struct Rva00734CB0Light {
    Rva00734CB0Color ambient,diffuse;
    struct { Real x,y,z; } lightPos;
};
class GlobalData {
public:
    char m_pad00[0x218];
    Int m_timeOfDay;
    char m_pad21c[0x4ac-0x21c];
    Rva00734CB0Light m_terrainObjectsLighting[4][3];
    char m_pad65c[0xdbc-0x65c];
    Bool m_field0dbc;
};
extern GlobalData *TheWritableGlobalData;
template<int N> class Rva00734CB0Slots : public Rva00734CB0Slots<N-1> {
public: virtual void slot(char (*)[N])=0;
};
template<> class Rva00734CB0Slots<0> {};
class BfmeGlobCC0 : public Rva00734CB0Slots<10> {
public:
    virtual Bool slot28()=0;
    virtual void slot2c()=0;
    virtual void slot30()=0;
    virtual void slot34(Vector3*)=0;
};
extern BfmeGlobCC0 *g_bfmeGlobCC0;
template<class T> inline const T& rvaMax(const T&a,const T&b) { return a>b?a:b; }
template<class T> struct Rva00734CB0Buffer { char m_head[0xc]; T *m_array; };
struct Rva00734CB0TriIndex { unsigned short I,J,K; };
struct Rva00734CB0MatDesc {
    char m_pad00[0xc];
    Rva00734CB0Buffer<Vector2> *m_uv[8];
    char m_pad2c[0x4c-0x2c];
    Rva00734CB0Buffer<unsigned> *m_color[2];
    const Vector2 *Get_UV_Array_By_Index(int i) const { return m_uv[i] ? m_uv[i]->m_array : 0; }
    const unsigned *Get_Color_Array(int i, bool) const { return m_color[i] ? m_color[i]->m_array : 0; }
};
struct Rva009272E0Mesh {
    char m_pad00[0x24];
    Int m_polygons,m_vertices;
    Rva00734CB0Buffer<Rva00734CB0TriIndex> *m_polygonArray;
    Rva00734CB0Buffer<Vector3> *m_vertexArray;
    char m_pad34[0x9c-0x34];
    Rva00734CB0MatDesc *m_matDesc;
    Int Get_Vertex_Count() const { return m_vertices; }
    Int Get_Polygon_Count() const { return m_polygons; }
    Vector3 *Get_Vertex_Array() const { return m_vertexArray->m_array; }
    const Rva00734CB0TriIndex *Get_Polygon_Array() const { return m_polygonArray->m_array; }
    const Vector2 *Get_UV_Array_By_Index(int i) const { return m_matDesc->Get_UV_Array_By_Index(i); }
    const unsigned *Get_Color_Array(int i,bool create) const { return m_matDesc->Get_Color_Array(i,create); }
    const Vector3 *rva009272e0(int);
};
class Rva00734CB0MaterialInfo {
public:
    virtual void Delete_This()=0;
    Int m_refCount;
    char m_pad08[4];
    VertexMaterialClass **m_materials;
    VertexMaterialClass *Peek_Vertex_Material(int i) const { return m_materials[i]; }
    void Release_Ref() { if (--m_refCount==0) Delete_This(); }
};
class Rva00734CB0MeshClass : public Rva00734CB0Slots<84> {
public:
    virtual Rva00734CB0MaterialInfo *Get_Material_Info()=0; // slot +0x150
    char m_pad04[0xc8-4];
    Rva009272E0Mesh *m_model;
    Rva009272E0Mesh *Peek_Model() const { return m_model; }
};
struct Rva00734CB0TypeData { char m_pad00[0x54]; Bool m_field54; };
struct Rva00734CB0Type {
    Rva00734CB0MeshClass *m_mesh;
    Vector3 m_offset;
    char m_pad10[0x10];
    Rva00734CB0TypeData *m_data;
    Real m_uScale,m_vScale;
    char m_pad2c[8];
    Real m_uOffset,m_vOffset;
    char m_pad3c[0x20];
};
struct Rva00734CB0Tree {
    Vector3 location;
    Real scale;
    Matrix3D rotation;
    Int treeType;
    Bool visible;
    char m_pad45[0x60-0x45];
    Int swayType,firstIndex,bufferNdx;
    char m_pad6c[0x80-0x6c];
    Int toppleState;
    char m_pad84[0xc];
    Matrix3D toppleMatrix;
    char m_padc0[8];
    Int m_fieldc8;
    char m_padcc[0x14];
    UnsignedInt alpha;
    Int m_fielde4;
};
class W3DTreeBuffer {
protected:
    void loadTreesInVertexAndIndexBuffers(RefRenderObjListIterator*);
public:
    UnsignedInt rva00732700(const Vector3*,const Vector3*,const Vector3*,const Vector3*,UnsignedInt,UnsignedInt) const;
private:
    char m_pad00[4];
    VertexBufferClass *m_vertexTree[20];
    IndexBufferClass *m_indexTree[20];
    Int m_fielda4;
    char m_pada8[0x110-0xa8];
    Int m_curNumTreeVertices[20];
    Int m_curNumTreeIndices[20];
    Rva00734CB0Tree m_trees[12000];
    Int m_numTrees;
    Bool m_anythingChanged;
    char m_pad2a7cb5[2];
    Bool m_initialized;
    char m_pad2a7cb8[4];
    Rva00734CB0Type m_treeTypes[64];
    Int m_numTreeTypes;
    Vector3 m_cameraLookAtVector;
    char m_pad2a93cc[0x2a9900-0x2a93cc];
    Int m_treeIndexStep;
    void *m_treeTexture;
    Int m_bufferCount;
};
void W3DTreeBuffer::loadTreesInVertexAndIndexBuffers(RefRenderObjListIterator *pDynamicLightsIterator)
{
    if (!m_indexTree[0] || !m_vertexTree[0] || !m_initialized) return;
    if (!m_anythingChanged) return;
    Real lightScale=1.0f;
    if (TheWritableGlobalData && TheWritableGlobalData->m_field0dbc && !m_fielda4) lightScale=2.0f;
    if (g_bfmeGlobCC0 && g_bfmeGlobCC0->slot28()) {
        Vector3 factor;
        g_bfmeGlobCC0->slot34(&factor);
        lightScale *= 1.0f-factor.X;
    }
    Int curTree=0;
    const Rva00734CB0Light *objectLighting=TheWritableGlobalData->m_terrainObjectsLighting[TheWritableGlobalData->m_timeOfDay];
    Vector3 lightRay[3];
    Rva00734CB0Color lightDiffuse[3];
    for (Int i=0;i<3;++i) {
        Vector3 lightDirection(objectLighting[i].lightPos.x,objectLighting[i].lightPos.y,objectLighting[i].lightPos.z);
        Real lightLength2 = lightDirection.X * lightDirection.X;
        lightLength2 += lightDirection.Y * lightDirection.Y;
        lightLength2 += lightDirection.Z * lightDirection.Z;
        if (lightLength2 != 0.0f) {
            Real inverseLength = WWMath::Inv_Sqrt(lightLength2);
            lightDirection.X *= inverseLength;
            lightDirection.Y *= inverseLength;
            lightDirection.Z *= inverseLength;
        }
        lightRay[i]=Vector3(-lightDirection.X,-lightDirection.Y,-lightDirection.Z);
        lightDiffuse[i].red=rvaMax(lightScale*objectLighting[i].diffuse.red,0.0f);
        lightDiffuse[i].blue=rvaMax(lightScale*objectLighting[i].diffuse.blue,0.0f);
        lightDiffuse[i].green=rvaMax(lightScale*objectLighting[i].diffuse.green,0.0f);
    }
    for (Int bNdx=0;bNdx<m_bufferCount;++bNdx) {
        m_curNumTreeVertices[bNdx]=0;
        m_curNumTreeIndices[bNdx]=0;
        if (curTree>=m_numTrees) break;
        IndexBufferClass::WriteLockClass lockIdxBuffer(m_indexTree[bNdx],0x2000);
        VertexBufferClass::WriteLockClass lockVtxBuffer(m_vertexTree[bNdx],0x2000);
        VertexFormatXYZNDUV1 *vb=(VertexFormatXYZNDUV1*)lockVtxBuffer.Get_Vertex_Array();
        unsigned short *ib=lockIdxBuffer.Get_Index_Array();
        Vector2 lookAtVector(m_cameraLookAtVector.X,m_cameraLookAtVector.Y);
        lookAtVector.Normalize();
        unsigned short *curIb=ib;
        VertexFormatXYZNDUV1 *curVb=vb;
        for (;curTree<m_numTrees;curTree+=m_treeIndexStep) {
            Int type=m_trees[curTree].treeType;
            if (type<0) continue;
            if (!m_trees[curTree].visible) continue;
            if (m_trees[curTree].m_fieldc8) continue;
            Real scale=m_trees[curTree].scale;
            Vector3 loc=m_trees[curTree].location;
            if (!m_treeTypes[type].m_mesh) continue;
            Matrix3D transform;
            if (m_trees[curTree].toppleState!=0) transform=m_trees[curTree].toppleMatrix;
            else transform.Set(loc);
            transform.Scale(scale);
            transform.postMul(m_trees[curTree].rotation);
            transform.Translate(m_treeTypes[type].m_offset);
            Bool doVertexLighting=true;
            Vector3 emissive(0.0f,0.0f,0.0f);
            Rva00734CB0MaterialInfo *matInfo=m_treeTypes[type].m_mesh->Get_Material_Info();
            if (matInfo) {
                VertexMaterialClass *vertMat=matInfo->Peek_Vertex_Material(0);
                if (vertMat) vertMat->Get_Emissive(&emissive);
            }
            if (matInfo) { matInfo->Release_Ref(); matInfo=0; }
            Int startVertex=m_curNumTreeVertices[bNdx];
            m_trees[curTree].firstIndex=startVertex;
            m_trees[curTree].bufferNdx=bNdx;
            Int numVertex=m_treeTypes[type].m_mesh->Peek_Model()->Get_Vertex_Count();
            Vector3 *pVert=m_treeTypes[type].m_mesh->Peek_Model()->Get_Vertex_Array();
            if (m_curNumTreeVertices[bNdx]+numVertex+2>=30000) break;
            Int numIndex=m_treeTypes[type].m_mesh->Peek_Model()->Get_Polygon_Count();
            const Rva00734CB0TriIndex *pPoly=m_treeTypes[type].m_mesh->Peek_Model()->Get_Polygon_Array();
            if (m_curNumTreeIndices[bNdx]+3*numIndex+6>=60000) break;
            const Vector2 *uvs=m_treeTypes[type].m_mesh->Peek_Model()->Get_UV_Array_By_Index(0);
            const Vector3 *normals=m_treeTypes[type].m_mesh->Peek_Model()->rva009272e0(0);
            const unsigned *vecDiffuse=m_treeTypes[type].m_mesh->Peek_Model()->Get_Color_Array(0,false);
            UnsignedInt diffuse=0;
            Vector3 shade;
            shade.X=objectLighting[0].ambient.red+emissive.X;
            shade.Y=objectLighting[0].ambient.green+emissive.Y;
            shade.Z=objectLighting[0].ambient.blue+emissive.Z;
            if (normals==0) {
                doVertexLighting=false;
                Vector3 normal(0.0f,0.0f,1.0f);
                diffuse=rva00732700(&normal,&shade,lightRay,(const Vector3*)lightDiffuse,0xffffffff,m_trees[curTree].alpha);
            }
            Real Uscale=m_treeTypes[type].m_uScale;
            Real Vscale=m_treeTypes[type].m_vScale;
            Real UOffset=m_treeTypes[type].m_uOffset;
            Real VOffset=m_treeTypes[type].m_vOffset;
            for (Int i=0;i<numVertex;++i) {
                if (m_curNumTreeVertices[bNdx]>=30000) break;
                Matrix3D::Transform_Vector(transform,pVert[i],(Vector3*)&curVb->x);
                curVb->nx=m_treeTypes[m_trees[curTree].treeType].m_data->m_field54 ? 0 : m_trees[curTree].swayType;
                curVb->ny=1.0f;
                curVb->nz=loc.Z;
                if (doVertexLighting) {
                    Vector3 normal;
                    Matrix3D::Transform_Vector(m_trees[curTree].rotation,normals[i],&normal);
                    UnsignedInt vertexDiffuse=vecDiffuse ? vecDiffuse[i] : 0xffffffff;
                    curVb->diffuse=rva00732700(&normal,&shade,lightRay,(const Vector3*)lightDiffuse,vertexDiffuse,m_trees[curTree].alpha);
                } else curVb->diffuse=diffuse;
                Real U=uvs[i].U;
                Real V=uvs[i].V;
                if (U>1.0f) U=1.0f;
                if (U<0.0f) U=0.0f;
                if (V>1.0f) V=1.0f;
                if (V<0.0f) V=0.0f;
                curVb->u1=U*Uscale+UOffset;
                curVb->v1=V*Vscale+VOffset;
                ++curVb;
                ++m_curNumTreeVertices[bNdx];
            }
            for (Int i=0;i<numIndex;++i) {
                if (m_curNumTreeIndices[bNdx]+4>60000) break;
                *curIb++=startVertex+pPoly[i].I;
                *curIb++=startVertex+pPoly[i].J;
                *curIb++=startVertex+pPoly[i].K;
                m_curNumTreeIndices[bNdx]+=3;
            }
        }
    }
}
