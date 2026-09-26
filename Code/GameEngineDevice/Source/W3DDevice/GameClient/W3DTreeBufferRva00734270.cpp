// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib
// W3DTreeBuffer method at retail 0x00734270: Zero Hour's updateVertexBuffer with the tree transform,
// a per-tree alpha fade and a tree index step.
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

struct Rva00734270VertexBuffer
{
	unsigned char m_head[0x0c];
	Vector3 *m_array;
};

struct Rva00734270Model
{
	unsigned char m_head[0x28];
	Int m_vertexCount;
	unsigned char m_gap002c[4];
	Rva00734270VertexBuffer *m_vertexBuffer;

	Int Get_Vertex_Count(void) const { return m_vertexCount; }
	Vector3 *Get_Vertex_Array(void) const { return m_vertexBuffer->m_array; }
};

class MeshClass
{
public:
	Rva00734270Model *Peek_Model(void) const { return m_model; }

private:
	unsigned char m_head[0xc8];
	Rva00734270Model *m_model;
};

struct Rva00734270Data
{
	unsigned char m_head[0x58];
	Int m_alphaStep;
};

struct Rva00734270TreeType
{
	MeshClass *m_mesh;
	Vector3 m_offset;
	unsigned char m_unreconstructed_10[0x10];
	const Rva00734270Data *m_data;
	unsigned char m_unreconstructed_24[0x5c - 0x24];
};

struct Rva00734270Tree
{
	Vector3 location;
	Real scale;
	Matrix3D transform;
	Int treeType;
	Bool visible;
	unsigned char m_unreconstructed_45[0x64 - 0x45];
	Int firstIndex;
	Int bufferNdx;
	unsigned char m_unreconstructed_6c[0x80 - 0x6c];
	Int m_toppleState;
	unsigned char m_unreconstructed_84[0x90 - 0x84];
	Matrix3D m_mtx;
	unsigned char m_unreconstructed_c0[0xc8 - 0xc0];
	Int m_fieldC8;
	unsigned char m_unreconstructed_cc[0xe0 - 0xcc];
	Int m_alpha;
	Int m_targetAlpha;
};

class W3DTreeBuffer
{
public:
	void rva00734270(void);

private:
	void *m_vtable;
	VertexBufferClass *m_vertexTree[20];
	void *m_indexTree[20];
	unsigned char m_unreconstructed_0000a4[0x160 - 0xa4];
	Int m_curNumTreeIndices[20];
	Rva00734270Tree m_trees[12000];
	Int m_numTrees;
	Bool m_anythingChanged;
	Bool m_anyPushChanged;
	Bool m_updateAllKeys;
	Bool m_initialized;
	unsigned char m_unreconstructed_2a7cb8[4];
	Rva00734270TreeType m_treeTypes[64];
	unsigned char m_unreconstructed_2a93bc[0x2a9900 - 0x2a93bc];
	Int m_treeIndexStep;
	unsigned char m_unreconstructed_2a9904[4];
	Int m_numBuffers;
	Bool m_anyAlphaChanged;
	Bool m_useSmallBuffers;
};

// ?rva00734270@W3DTreeBuffer@@QAEXXZ
void W3DTreeBuffer::rva00734270(void)
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
			Int alpha = m_trees[curTree].m_alpha;
			if (m_trees[curTree].m_toppleState == 0 && alpha == m_trees[curTree].m_targetAlpha) {
				continue;
			}
			if (m_trees[curTree].m_toppleState != 0) {
				m_anyPushChanged = true;
			}
			if (!m_useSmallBuffers && alpha != m_trees[curTree].m_targetAlpha) {
				m_anyAlphaChanged = true;
				Int targetAlpha = m_trees[curTree].m_targetAlpha;
				if (alpha > targetAlpha) {
					alpha -= m_treeTypes[type].m_data->m_alphaStep;
					if (alpha < targetAlpha) {
						alpha = targetAlpha;
					}
				} else {
					alpha += m_treeTypes[type].m_data->m_alphaStep;
					if (alpha > targetAlpha) {
						alpha = targetAlpha;
					}
				}
				m_trees[curTree].m_alpha = alpha;
			}
			if (!m_trees[curTree].visible) continue;
			if (m_trees[curTree].m_fieldC8) continue;
			Real scale = m_trees[curTree].scale;
			Vector3 loc = m_trees[curTree].location;
			if (m_treeTypes[type].m_mesh == 0) {
				type = 0;
			}

			Int startVertex = m_trees[curTree].firstIndex;
			curVb = vb + startVertex;
			Int i;
			Int numVertex = m_treeTypes[type].m_mesh->Peek_Model()->Get_Vertex_Count();
			Vector3 *pVert = m_treeTypes[type].m_mesh->Peek_Model()->Get_Vertex_Array();

			for (i = 0; i < numVertex; i++) {
				Vector3 vert = pVert[i];
				vert += m_treeTypes[type].m_offset;
				Vector3 vLoc;
				Matrix3D::Transform_Vector(m_trees[curTree].transform, vert, &vLoc);
				vLoc *= scale;

				if (m_trees[curTree].m_toppleState != 0) {
					m_trees[curTree].m_mtx.Transform_Vector(m_trees[curTree].m_mtx, vLoc, &vLoc);
				} else {
					vLoc.X += loc.X;
					vLoc.Y += loc.Y;
					vLoc.Z += loc.Z;
				}

				curVb->x = vLoc.X;
				curVb->y = vLoc.Y;
				curVb->z = vLoc.Z;
				curVb->diffuse = (curVb->diffuse & 0x00ffffff) | (alpha << 24);
				curVb->ny = 1.0f;
				curVb++;
			}
		}
	}
}
