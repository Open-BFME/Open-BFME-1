// ?render@BfmeShadowBufferEntry@@QAEXPAXG0PAG@Z
// partial score=0.99 date=2026-09-28
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

	void render(void *vertex, unsigned short vertexBase, void *index,
		unsigned short *scratch);
};

void BfmeShadowBufferEntry::render(void *vertex, unsigned short vertexBase,
	void *index, unsigned short *scratch)
{
	const Vector3 &offset = *(const Vector3 *)scratch;
	Vector3 dir = offset;
	dir.Normalize();
	dir *= 0.1f;

	int count = m_mesh->m_model->m_vertexCount;
	Vector3 *out = (Vector3 *)vertex;
	int i;
	for (i = 0; i < count; i++)
		*out++ = dir + m_allocation0[i];
	for (i = 0; i < count; i++)
		*out++ = m_allocation0[i] + offset;

	BfmeShadowEdge *edge = m_allocation2;
	unsigned short *&ib = (unsigned short *&)index;
	for (i = (int)m_reserved10; i > 0; i--)
	{
		ib[0] = edge->m_vertex0 + count + vertexBase;
		ib[1] = edge->m_vertex1 + vertexBase;
		ib[2] = edge->m_vertex0 + vertexBase;
		ib[3] = edge->m_vertex1 + vertexBase;
		ib[4] = edge->m_vertex0 + count + vertexBase;
		ib[5] = edge->m_vertex1 + count + vertexBase;
		edge++;
		ib += 6;
	}

	BfmeShadowTriIndex *tri = m_mesh->m_model->m_poly->m_data;
	unsigned char *front = m_allocation1;
	for (i = m_mesh->m_model->m_polyCount; i > 0; i--)
	{
		if (*front)
		{
			ib[0] = tri->I + vertexBase;
			ib[1] = tri->J + vertexBase;
			ib[2] = tri->K + vertexBase;
		}
		else
		{
			ib[0] = tri->I + count + vertexBase;
			ib[1] = tri->J + count + vertexBase;
			ib[2] = tri->K + count + vertexBase;
		}
		ib += 3;
		front++;
		tri++;
	}
}
