// ?rvaGetIndicesNVertices@Rva006F8E60Bridge@@QAEXPAGPAXPAH2@Z
// partial score=0.55 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc

// Retail 0x006F8E60, 121 bytes, __thiscall (ret 0x10, 4 explicit stack args).
// Structurally this is W3DBridge::getIndicesNVertices's "simple" branch
// (reference/CnC_Generals_Zero_Hour/GeneralsMD/.../W3DBridgeBuffer.cpp,
// around line 524-541): the tail arithmetic
//   *curIndexP += numIndex; *curVertexP += numVertex;
//   m_numVertex += numVertex; m_numPolygons += numIndex/3;
// matches the reference verbatim (imul by the signed-divide-by-3 magic
// constant 0x55555556 with the standard sign correction), and the second
// call is the ALREADY-LANDED Rva006F8720MeshBuffer::getModelIndices
// (Rva006F8720GetModelIndices.cpp) called with (destination_ib, *curIndexP,
// *curVertexP, mesh) exactly matching its real signature. The first call is
// the ALREADY-PINNED Rva006F8700Owner::rva006F83F0 (reverse/symbols.csv:
// ?rva006F83F0@Rva006F8700Owner@@QAEHPAXH00@Z, still a dump body) called
// with (destination_vb, *curVertexP, &this+0x4c, mesh).
//
// Unlike the reference source, this variant explicitly skips the first
// (vertices) call when the mesh pointer at this+0x24 is null, but always
// makes the second (indices) call regardless (getModelIndices itself
// returns 0 for a null mesh) -- and it has no vertex/index-overflow early
// returns, so this is a simplified/inlined sibling rather than a literal
// port of getIndicesNVertices. No caller or vtable evidence proves the
// owning class name or matches the real W3DBridge layout (a prior attempt
// tried W3DBridge's own offsets and they did not fit), so the class stays
// address-derived.

class MeshClass;

class Rva006F8700Owner
{
public:
	int rva006F83F0(void *a, int b, void *c, void *p);
};

class Rva006F8720MeshBuffer
{
public:
	int getModelIndices(unsigned short *destination_ib, int curIndex, int vertexOffset, MeshClass *pMesh);
};

class Rva006F8E60Bridge
{
public:
	void rvaGetIndicesNVertices(unsigned short *destination_ib, void *destination_vb,
			int *curIndexP, int *curVertexP);

private:
	char m_prefix1[0x24];
	void *m_mesh;             // +0x24
	char m_prefix2[0x38 - 0x28];
	int m_firstIndex;         // +0x38
	int m_numVertex;          // +0x3c
	int m_firstVertex;        // +0x40
	int m_numPolygons;        // +0x44
};

// ?rvaGetIndicesNVertices@Rva006F8E60Bridge@@QAEXPAGPAXPAH1@Z
void Rva006F8E60Bridge::rvaGetIndicesNVertices(unsigned short *destination_ib, void *destination_vb,
		int *curIndexP, int *curVertexP)
{
	m_firstVertex = *curVertexP;
	m_firstIndex = *curIndexP;
	m_numVertex = 0;
	m_numPolygons = 0;

	int numVertex = 0;
	if (m_mesh != 0)
	{
		numVertex = ((Rva006F8700Owner *)this)->rva006F83F0(destination_vb, *curVertexP, (char *)this + 0x4c, m_mesh);
	}

	int numIndex = ((Rva006F8720MeshBuffer *)this)->getModelIndices(destination_ib, *curIndexP, *curVertexP, (MeshClass *)m_mesh);

	*curIndexP += numIndex;
	*curVertexP += numVertex;
	m_numVertex += numVertex;
	m_numPolygons += numIndex / 3;
}
