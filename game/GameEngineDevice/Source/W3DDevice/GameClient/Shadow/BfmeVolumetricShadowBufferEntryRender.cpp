// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWDebug

#include "vector3.h"

struct BfmeShadowTriIndex
{
	unsigned short I;
	unsigned short J;
	unsigned short K;
};

struct BfmeShadowTriBuffer
{
	unsigned char m_pad[0xc];
	BfmeShadowTriIndex *m_data;
};

struct BfmeShadowMeshModel
{
	unsigned char m_beforeFlags[0x18];
	unsigned int m_flags;
	unsigned char m_betweenFlagsAndPolyCount[8];
	int m_polyCount;
	int m_vertexCount;
	BfmeShadowTriBuffer *m_poly;
};

class BfmeShadowMesh
{
public:
	virtual void v00();

	unsigned char m_beforeModel[0xc4];
	BfmeShadowMeshModel *m_model;
};

struct BfmeShadowEdge
{
	unsigned short m_vertex0;
	unsigned short m_pad02;
	unsigned short m_vertex1;
	unsigned short m_pad06;
};

struct BfmeShadowBufferEntry
{
	BfmeShadowMesh *m_mesh;
	Vector3 *m_allocation0;
	unsigned char *m_allocation1;
	BfmeShadowEdge *m_allocation2;
	unsigned int m_reserved10;
	unsigned char m_reserved14;

	void render(Vector3 *vertex, unsigned short vertexBase, unsigned short *index,
		const Vector3 &offset);
};

// Same thiscall ABI (four dwords, ret 0x10) as the erased declaration in
// BfmeVolumetricShadowBufferOwnerRender.cpp, which reaches this body through ILT 0x0003D253.
void BfmeShadowBufferEntry::render(Vector3 *vertex, unsigned short vertexBase,
	unsigned short *index, const Vector3 &offset)
{
	Vector3 dir = offset;
	dir.Normalize();
	dir *= 0.1f;
	int count = m_mesh->m_model->m_vertexCount;
	int i, j;
	for (i = 0; i < count; ++i)
		*vertex++ = m_allocation0[i] + dir;
	for (j = 0; j < count; ++j)
		*vertex++ = m_allocation0[j] + offset;

	BfmeShadowEdge *edge = m_allocation2;
	for (int e = m_reserved10; e > 0; --e, ++edge, index += 6)
	{
		index[0] = (unsigned short)(edge->m_vertex0 + count) + vertexBase;
		index[1] = edge->m_vertex1 + vertexBase;
		index[2] = edge->m_vertex0 + vertexBase;
		index[3] = edge->m_vertex1 + vertexBase;
		index[4] = (unsigned short)(edge->m_vertex0 + count) + vertexBase;
		index[5] = (unsigned short)(edge->m_vertex1 + count) + vertexBase;
	}

	unsigned char *front = m_allocation1;
	BfmeShadowTriIndex *tri = m_mesh->m_model->m_poly->m_data;
	int polyCount = m_mesh->m_model->m_polyCount;
	for (int t = 0; t < polyCount; ++t, index += 3, ++front, ++tri)
	{
		if (*front)
		{
			index[0] = tri->I + vertexBase;
			index[1] = tri->J + vertexBase;
			index[2] = tri->K + vertexBase;
		}
		else
		{
			index[0] = vertexBase + count + tri->I;
			index[1] = (unsigned short)(tri->J + count) + vertexBase;
			index[2] = (unsigned short)(tri->K + count) + vertexBase;
		}
	}
}
