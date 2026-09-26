// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib
// W3DShrubBuffer method at retail 0x0071D5E0: Zero Hour's updateVertexBuffer with the record transform
// in place of the sine and cosine rotation and a tree index step.
#include "vector3.h"
#include "matrix3d.h"

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;

class VertexBufferClass
{
public:
	class WriteLockClass
	{
	public:
		WriteLockClass(VertexBufferClass *vertexBuffer, int flags);
		~WriteLockClass();
		void *Get_Vertex_Array(void) { return m_vertices; }

	private:
		VertexBufferClass *m_vertexBuffer;
		void *m_vertices;
	};
};

struct VertexFormatXYZNDUV1
{
	float x, y, z;
	float nx, ny, nz;
	UnsignedInt diffuse;
	float u1, v1;
};

struct Rva0071D5E0VertexBuffer
{
	unsigned char m_head[0x0c];
	Vector3 *m_array;
};

struct Rva0071D5E0Model
{
	unsigned char m_head[0x28];
	Int m_vertexCount;
	unsigned char m_gap002c[4];
	Rva0071D5E0VertexBuffer *m_vertexBuffer;

	Int Get_Vertex_Count(void) const { return m_vertexCount; }
	Vector3 *Get_Vertex_Array(void) const { return m_vertexBuffer->m_array; }
};

class MeshClass
{
public:
	Rva0071D5E0Model *Peek_Model(void) const { return m_model; }

private:
	unsigned char m_head[0xc8];
	Rva0071D5E0Model *m_model;
};

struct Rva0071D5E0Data
{
	unsigned char m_head[0x18];
	Real m_maxOutwardMovement;
	Real m_darkening;
};

struct Rva0071D5E0TreeType
{
	MeshClass *m_mesh;
	Vector3 m_offset;
	unsigned char m_unreconstructed_10[0x10];
	const Rva0071D5E0Data *m_data;
	unsigned char m_unreconstructed_24[0x5c - 0x24];
};

struct Rva0071D5E0Tree
{
	Vector3 location;
	Real scale;
	Matrix3D transform;
	Int treeType;
	Bool visible;
	unsigned char m_unreconstructed_45[0x60 - 0x45];
	Real pushAside;
	Real pushAsideDelta;
	Real pushAsideSin;
	Real pushAsideCos;
	unsigned char m_unreconstructed_70[0x80 - 0x70];
	Int firstIndex;
	Int bufferNdx;
	Int m_field88;
	unsigned char m_unreconstructed_8c[0xa0 - 0x8c];
	Int m_fieldA0;
};

class W3DShrubBuffer
{
public:
	void rva0071D5E0(void);

private:
	void *m_vtable;
	VertexBufferClass *m_vertexTree[20];
	void *m_indexTree[20];
	unsigned char m_unreconstructed_0000a4[0x14f8 - 0xa4];
	Int m_curNumTreeIndices[20];
	Rva0071D5E0Tree m_trees[12000];
	Int m_numTrees;
	Bool m_anythingChanged;
	Bool m_anyPushChanged;
	Bool m_updateAllKeys;
	Bool m_initialized;
	unsigned char m_unreconstructed_1e1cd0[4];
	Rva0071D5E0TreeType m_treeTypes[64];
	unsigned char m_unreconstructed_1e33d4[0x1e3918 - 0x1e33d4];
	Int m_numBuffers;
	unsigned char m_unreconstructed_1e391c[4];
	Int m_treeIndexStep;
};

// ?rva0071D5E0@W3DShrubBuffer@@QAEXXZ
void W3DShrubBuffer::rva0071D5E0(void)
{
	if (!m_indexTree[0] || !m_vertexTree[0] || !m_initialized) {
		return;
	}
	Int bNdx;
	for (bNdx = 0; bNdx < m_numBuffers; bNdx++) {
		if (m_curNumTreeIndices[bNdx] == 0) {
			break;
		}
		VertexFormatXYZNDUV1 *vb;
		VertexBufferClass::WriteLockClass lockVtxBuffer(m_vertexTree[bNdx], 0);
		vb = (VertexFormatXYZNDUV1 *)lockVtxBuffer.Get_Vertex_Array();

		VertexFormatXYZNDUV1 *curVb;

		Int curTree;
		for (curTree = 0; curTree < m_numTrees; curTree += m_treeIndexStep) {
			if (m_trees[curTree].bufferNdx != bNdx) {
				continue;
			}
			Int type = m_trees[curTree].treeType;
			if (type < 0) {
				continue;
			}
			if (m_trees[curTree].pushAsideDelta == 0.0f) {
				continue;
			}
			m_anyPushChanged = true;
			if (!m_trees[curTree].visible) continue;
			if (m_trees[curTree].m_field88) continue;
			if (m_trees[curTree].m_fieldA0 >= 4 || m_trees[curTree].m_fieldA0 <= 0) continue;
			Real scale = m_trees[curTree].scale;
			Vector3 loc = m_trees[curTree].location;
			if (m_treeTypes[type].m_mesh == 0) {
				type = 0;
			}

			curVb = vb + m_trees[curTree].firstIndex;
			Int i;
			Int numVertex = m_treeTypes[type].m_mesh->Peek_Model()->Get_Vertex_Count();
			Vector3 *pVert = m_treeTypes[type].m_mesh->Peek_Model()->Get_Vertex_Array();

			for (i = 0; i < numVertex; i++) {
				Real x = pVert[i].X;
				Real y = pVert[i].Y;
				Real z = pVert[i].Z;
				Vector3 vert(x, y, z);
				vert += m_treeTypes[type].m_offset;
				Vector3 vLoc;
				Matrix3D::Transform_Vector(m_trees[curTree].transform, vert, &vLoc);
				vLoc *= scale;

				if (m_trees[curTree].pushAside > 0.0f) {
					vLoc.X += pVert[i].Z * m_trees[curTree].pushAside * m_trees[curTree].pushAsideCos * m_treeTypes[type].m_data->m_maxOutwardMovement;
					vLoc.Y += pVert[i].Z * m_trees[curTree].pushAside * m_trees[curTree].pushAsideSin * m_treeTypes[type].m_data->m_maxOutwardMovement;
				}
				vLoc.X += loc.X;
				vLoc.Y += loc.Y;
				vLoc.Z += loc.Z;

				curVb->x = vLoc.X;
				curVb->y = vLoc.Y;
				curVb->z = vLoc.Z;
				curVb->ny = 1.0f - m_treeTypes[type].m_data->m_darkening * m_trees[curTree].pushAside;
				curVb++;
			}
		}
	}
}
