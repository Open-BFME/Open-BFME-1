// ?loadTreesInVertexAndIndexBuffers@Rva0071DF10@@IAEXPAV?$RefMultiListIterator@VRenderObjClass@@@@@Z
// partial score=0.82 date=2026-09-18
// ?loadTreesInVertexAndIndexBuffers@Rva0071DF10@@IAEXPAV?$RefMultiListIterator@VRenderObjClass@@@@@Z
// stlport
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// Retail 0x0071DF10.  The owner is the BFME shrub-buffer twin: the adjacent
// W3DShrubBuffer methods prove the class and the 0xA4 record/type layout.  The
// method spelling remains address-qualified until a direct caller or vtable
// slot names it.

#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#include "W3DDevice/GameClient/W3DTreeBuffer.h"
#include "WW3D2/Matinfo.h"
#include "WW3D2/Mesh.h"
#include "WW3D2/MeshMdl.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef float Real;

class BfmeC998
{
public:
	void bfmeGo998C(int value);
};

// The BFME mesh model's material/geometry view is witnessed by the retail
// loads at +0x24, +0x28, +0x2C, +0x30 and +0x9C.  Keep the unknown holders
// opaque; their +0x0C array member is the only part this body proves.
struct Rva0071DF10ArrayHolder
{
	unsigned char m_pad00[0x0c];
	void *m_array;
};

struct Rva0071DF10MaterialDescription
{
	unsigned char m_pad00[0x0c];
	Rva0071DF10ArrayHolder *m_uv;
	unsigned char m_pad10[0x4c - 0x10];
	Rva0071DF10ArrayHolder *m_color;
};

struct Rva0071DF10PolygonBuffer
{
	unsigned char m_pad00[0x0c];
	const TriIndex *m_array;
};

struct Rva0071DF10VertexBuffer
{
	unsigned char m_pad00[0x0c];
	Vector3 *m_array;
};

struct Rva0071DF10MeshModel
{
	unsigned char m_pad00[0x24];
	Int m_polygonCount;
	Int m_vertexCount;
	Rva0071DF10PolygonBuffer *m_polygonBuffer;
	Rva0071DF10VertexBuffer *m_vertexBuffer;
	unsigned char m_pad34[0x9c - 0x34];
	Rva0071DF10MaterialDescription *m_materialDescription;

	Int Get_Polygon_Count(void) const { return m_polygonCount; }
	Int Get_Vertex_Count(void) const { return m_vertexCount; }
	const TriIndex *Get_Polygon_Array(void) const
	{
		return m_polygonBuffer->m_array;
	}
	Vector3 *Get_Vertex_Array(void) const
	{
		return m_vertexBuffer->m_array;
	}
	const Vector2 *Get_UV_Array_By_Index(Int index) const
	{
		(void)index;
		if (m_materialDescription == 0 || m_materialDescription->m_uv == 0)
			return 0;
		return (const Vector2 *)m_materialDescription->m_uv->m_array;
	}
	const UnsignedInt *Get_Color_Array(Int index, bool create) const
	{
		(void)index;
		(void)create;
		if (m_materialDescription == 0 || m_materialDescription->m_color == 0)
			return 0;
		return (const UnsignedInt *)m_materialDescription->m_color->m_array;
	}
	const Vector3 *Get_Vertex_Normal_Array(void) const
	{
		union
		{
			void (BfmeC998::*void_function)(int);
			const Vector3 *(BfmeC998::*normal_function)(int);
		} function;
		function.void_function = &BfmeC998::bfmeGo998C;
		return (((BfmeC998 *)this)->*function.normal_function)(0);
	}
};

struct Rva0071DF10ShrubRecord
{
	Vector3 m_location;
	Real m_scale;
	Matrix3D m_matrix;
	Int m_type;
	UnsignedByte m_visible;
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

struct Rva0071DF10TreeType
{
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

class Rva0071DF10GlobCC0
{
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
	virtual void slot34(Real *value);
};

extern void j_0000e9fd(void);
extern void j_00027a43(void);

class Rva0071DF10
{
protected:
	void loadTreesInVertexAndIndexBuffers(RefRenderObjListIterator *pDynamicLightsIterator);

private:
	void *m_objectVtable;
	DX8VertexBufferClass *m_vertexTree[20];
	DX8IndexBufferClass *m_indexTree[20];
	unsigned char m_pad00a4[0x14a8 - 0xa4];
	Int m_curNumTreeVertices[20];
	Int m_curNumTreeIndices[20];
	Rva0071DF10ShrubRecord m_trees[12000];
	Int m_numTrees;
	UnsignedByte m_anythingChanged;
	UnsignedByte m_anyPushChanged;
	UnsignedByte m_updateAllKeys;
	UnsignedByte m_initialized;
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

typedef UnsignedInt (Rva0071DF10::*Rva0071DF10LightingOperation)(
	const Vector3 *, const void *, const Vector3 *, UnsignedInt, Real) const;

void Rva0071DF10::loadTreesInVertexAndIndexBuffers(
	RefRenderObjListIterator *pDynamicLightsIterator)
{
	if (!m_indexTree[0] || !m_vertexTree[0] || !m_initialized)
		return;
	if (!m_anythingChanged)
		return;

	Real lightingScale = 1.0f;
	char *globalData = *(char **)0x012ed5c8;
	if (globalData != 0) {
		if (*(UnsignedByte *)(globalData + 0xdbc) != 0 &&
			*(Int *)((char *)this + 0xa4) == 0)
			lightingScale = 2.0f;
		lightingScale *= *(Real *)(globalData + 0x1220);
	}

	Rva0071DF10GlobCC0 *globCC0 = *(Rva0071DF10GlobCC0 **)0x012f1104;
	if (globCC0 != 0 && globCC0->slot28()) {
		Real value;
		(*(Rva0071DF10GlobCC0 **)0x012f1104)->slot34(&value);
		lightingScale *= *(Real *)0x01075334 - value;
	}

	globalData = *(char **)0x012ed5c8;
	Int timeOfDay = *(Int *)(globalData + 0x218);
	const void *objectLighting = globalData + 0x4ac + timeOfDay * 0x6c;
	Int curTree = 0;
	Int bNdx;
	Int *curNumTreeVertices = m_curNumTreeVertices;
	Int *curNumTreeIndices = curNumTreeVertices + 20;
	for (bNdx = 0; bNdx < m_numBuffers; bNdx++) {
		curNumTreeVertices[bNdx] = 0;
		curNumTreeIndices[bNdx] = 0;
		if (curTree >= m_numTrees)
			break;

		VertexFormatXYZNDUV1 *vb;
		UnsignedShort *ib;
		DX8IndexBufferClass::WriteLockClass lockIdxBuffer(m_indexTree[bNdx], 0);
		DX8VertexBufferClass::WriteLockClass lockVtxBuffer(m_vertexTree[bNdx], 0);
		vb = (VertexFormatXYZNDUV1 *)lockVtxBuffer.Get_Vertex_Array();
		ib = lockIdxBuffer.Get_Index_Array();

		Vector2 lookAtVector(m_cameraLookAtVector.X, m_cameraLookAtVector.Y);
		lookAtVector.Normalize();
		UnsignedShort *curIb = ib;
		VertexFormatXYZNDUV1 *curVb = vb;

		for (; curTree < m_numTrees; curTree += m_globalBufferCount) {
			Int type = m_trees[curTree].m_type;
			if (type < 0 || !m_trees[curTree].m_visible ||
				m_trees[curTree].m_state88 != 0 ||
				m_trees[curTree].m_stateA0 >= 4 ||
				m_trees[curTree].m_stateA0 <= 0)
				continue;

			Real scale = m_trees[curTree].m_scale;
			Vector3 loc = m_trees[curTree].m_location;
			if (m_treeTypes[type].m_mesh == 0)
				continue;

			bool doVertexLighting = true;
			Vector3 emissive(0.0f, 0.0f, 0.0f);
			MaterialInfoClass *matInfo = m_treeTypes[type].m_mesh->Get_Material_Info();
			if (matInfo) {
				VertexMaterialClass *vertMat = matInfo->Peek_Vertex_Material(0);
				if (vertMat)
					vertMat->Get_Emissive(&emissive);
			}
			REF_PTR_RELEASE(matInfo);

			Int startVertex = curNumTreeVertices[bNdx];
			m_trees[curTree].m_firstIndex = startVertex;
			m_trees[curTree].m_bufferNdx = bNdx;

			Int numVertex = ((Rva0071DF10MeshModel *)*(void **)(
				(char *)m_treeTypes[type].m_mesh + 0xc8))->m_vertexCount;
			Vector3 *pVert = ((Rva0071DF10MeshModel *)*(void **)(
				(char *)m_treeTypes[type].m_mesh + 0xc8))->m_vertexBuffer->m_array;
			if (curNumTreeVertices[bNdx] + numVertex + 2 >= 0x7530)
				break;

			Int numIndex = ((Rva0071DF10MeshModel *)*(void **)(
				(char *)m_treeTypes[type].m_mesh + 0xc8))->m_polygonCount;
			const TriIndex *pPoly = ((Rva0071DF10MeshModel *)*(void **)(
				(char *)m_treeTypes[type].m_mesh + 0xc8))->m_polygonBuffer->m_array;
			if (curNumTreeIndices[bNdx] + 3 * numIndex + 6 >= 0xea60)
				break;

			const Vector2 *uvs = 0;
			Rva0071DF10MeshModel *model = ((Rva0071DF10MeshModel *)*(void **)(
				(char *)m_treeTypes[type].m_mesh + 0xc8));
			if (model->m_materialDescription != 0 &&
				model->m_materialDescription->m_uv != 0)
				uvs = (const Vector2 *)model->m_materialDescription->m_uv->m_array;
			union
			{
				void (BfmeC998::*void_function)(int);
				const Vector3 *(BfmeC998::*normal_function)(int);
			} normalFunction;
			normalFunction.void_function = &BfmeC998::bfmeGo998C;
			const Vector3 *normals =
				(((BfmeC998 *)model)->*normalFunction.normal_function)(0);
			const UnsignedInt *vecDiffuse = 0;
			if (model->m_materialDescription != 0 &&
				model->m_materialDescription->m_color != 0)
				vecDiffuse = (const UnsignedInt *)
					model->m_materialDescription->m_color->m_array;
			UnsignedInt diffuse = 0;
			if (normals == 0) {
				doVertexLighting = false;
				Vector3 normal(0.0f, 0.0f, 1.0f);
				union
				{
					void (*function)(void);
					Rva0071DF10LightingOperation member;
				} lightingFunction;
				lightingFunction.function = j_0000e9fd;
				diffuse = (this->*lightingFunction.member)(&normal,
					objectLighting, &emissive, 0xffffffff, lightingScale);
			}

			Int i;
			Real Uscale = m_treeTypes[type].m_uScale;
			Real Vscale = m_treeTypes[type].m_vScale;
			Real UOffset = m_treeTypes[type].m_uOffset;
			Real VOffset = m_treeTypes[type].m_vOffset;
			for (i = 0; i < numVertex; i++) {
				if (curNumTreeVertices[bNdx] >= 0x7530)
					break;

				Real U = uvs[i].U;
				Real V = uvs[i].V;
				if (U > 1.0f) U = 1.0f;
				if (U < 0.0f) U = 0.0f;
				if (V > 1.0f) V = 1.0f;
				if (V < 0.0f) V = 0.0f;
				curVb->u1 = U * Uscale + UOffset;
				curVb->v1 = V * Vscale + VOffset;

				Vector3 vLoc = pVert[i];
				vLoc.X += m_treeTypes[type].m_offset.X;
				vLoc.Y += m_treeTypes[type].m_offset.Y;
				vLoc.Z += m_treeTypes[type].m_offset.Z;
				Matrix3D::Transform_Vector(m_trees[curTree].m_matrix, vLoc, &vLoc);
				vLoc *= scale;
				if (m_trees[curTree].m_pushAside > 0.0f) {
					Real movement = *(Real *)((char *)m_treeTypes[type].m_data + 0x18);
					vLoc.X += pVert[i].Z * m_trees[curTree].m_pushAside *
						m_trees[curTree].m_pushAsideCos * movement;
					vLoc.Y += pVert[i].Z * m_trees[curTree].m_pushAside *
						m_trees[curTree].m_pushAsideSin * movement;
				}
				vLoc.X += loc.X;
				vLoc.Y += loc.Y;
				vLoc.Z += loc.Z;

				curVb->x = vLoc.X;
				curVb->y = vLoc.Y;
				curVb->z = vLoc.Z;
				curVb->nx = (Real)m_trees[curTree].m_swayType;
				curVb->ny = *(Real *)((char *)m_treeTypes[type].m_data + 0x1c) *
					m_trees[curTree].m_pushAside;
				curVb->ny = *(Real *)0x01075334 - curVb->ny;
				curVb->nz = loc.Z;

				if (doVertexLighting) {
					Vector3 normal(0.0f, 0.0f, 1.0f);
					if (normals) {
						normal.X = normals[i].X * m_trees[curTree].m_matrix[0][0] +
							normals[i].Y * m_trees[curTree].m_matrix[0][1] +
							normals[i].Z * m_trees[curTree].m_matrix[0][2];
						normal.Y = normals[i].X * m_trees[curTree].m_matrix[1][0] +
							normals[i].Y * m_trees[curTree].m_matrix[1][1] +
							normals[i].Z * m_trees[curTree].m_matrix[1][2];
						normal.Z = normals[i].X * m_trees[curTree].m_matrix[2][0] +
							normals[i].Y * m_trees[curTree].m_matrix[2][1] +
							normals[i].Z * m_trees[curTree].m_matrix[2][2];
					}
					UnsignedInt vertexDiffuse = vecDiffuse ? vecDiffuse[i] : 0xffffffff;
					union
					{
						void (*function)(void);
						Rva0071DF10LightingOperation member;
					} lightingFunction;
					lightingFunction.function = j_0000e9fd;
					curVb->diffuse = (this->*lightingFunction.member)(&normal,
						objectLighting, &emissive, vertexDiffuse, lightingScale);
				} else {
					curVb->diffuse = diffuse;
				}
				++curVb;
				++curNumTreeVertices[bNdx];
			}

			try {
				for (i = 0; i < numIndex; i++) {
					if (curNumTreeIndices[bNdx] + 4 > 0xea60)
						break;
					*curIb++ = startVertex + pPoly[i].I;
					*curIb++ = startVertex + pPoly[i].J;
					*curIb++ = startVertex + pPoly[i].K;
					curNumTreeIndices[bNdx] += 3;
				}
				IndexBufferExceptionFunc();
			} catch (...) {
				IndexBufferExceptionFunc();
			}
		}
	}
}
