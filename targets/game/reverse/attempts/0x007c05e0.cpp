// ?copy@BfmeShadowBufferEntry@@QAEIPAXG0PAG@Z
// partial score=0.51 date=2026-09-28
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug
// ?copy@BfmeShadowBufferEntry@@QAEIPAXG0PAG@Z partial score=0.51 date=2026-09-28 (shape 0.986; residue is register allocation only)

#include "vector3.h"

struct BfmeShadowMeshModel
{
	unsigned char m_beforeVertexCount[0x28];
	int m_vertexCount;
};

struct BfmeShadowMesh
{
	unsigned char m_beforeModel[0xc8];
	BfmeShadowMeshModel *m_model;
};

struct Rva007C05E0EdgePair
{
	int m_first;
	int m_second;
};

struct BfmeShadowBufferEntry
{
	BfmeShadowMesh *m_mesh;
	Vector3 *m_allocation0;
	void *m_allocation1;
	Rva007C05E0EdgePair *m_allocation2;
	int m_reserved10;
	unsigned char m_reserved14;

	unsigned int copy(void *a, unsigned short b, void *c, unsigned short *d);
};

unsigned int BfmeShadowBufferEntry::copy(void *a, unsigned short b, void *c, unsigned short *d)
{
	int vertexCount = m_mesh->m_model->m_vertexCount;
	int doubled = vertexCount * 2;
	const Vector3 &offset = *(const Vector3 *)d;
	int i;
	int n;
	if (doubled < m_reserved10 * 4) {
		Vector3 *dst = (Vector3 *)a;
		for (i = 0; i < vertexCount; i++)
			*dst++ = m_allocation0[i];
		for (i = 0; i < vertexCount; i++)
			*dst++ = m_allocation0[i] + offset;
		Rva007C05E0EdgePair *edge = m_allocation2;
		unsigned short *index = (unsigned short *)c;
		n = m_reserved10;
		for (i = 0; i < n; i++) {
			index[0] = edge->m_first + vertexCount + b;
			index[1] = edge->m_second + b;
			index[2] = edge->m_first + b;
			index[3] = edge->m_second + b;
			index[4] = edge->m_first + vertexCount + b;
			index[5] = edge->m_second + vertexCount + b;
			index += 6;
			edge++;
		}
		return doubled;
	}

	Vector3 *dst = (Vector3 *)a;
	Rva007C05E0EdgePair *edge = m_allocation2;
	n = m_reserved10;
	for (i = n; i > 0; i--) {
		dst[0] = m_allocation0[edge->m_first];
		dst[1] = m_allocation0[edge->m_second];
		dst[2] = m_allocation0[edge->m_first] + offset;
		dst[3] = m_allocation0[edge->m_second] + offset;
		dst += 4;
		edge++;
	}
	unsigned int pair = b | (b << 16);
	unsigned int *index = (unsigned int *)c;
	n = m_reserved10;
	for (i = 0; i < n; i++) {
		index[0] = pair + 0x10002;
		index[1] = pair + 0x10000;
		index[2] = pair + 0x30002;
		index += 3;
		pair += 0x40004;
	}
	return m_reserved10 * 4;
}
