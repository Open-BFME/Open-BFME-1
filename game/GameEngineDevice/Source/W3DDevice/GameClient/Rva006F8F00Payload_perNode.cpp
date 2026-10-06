// cl: /DNDEBUG /MD /EHsc
// ?perNode@Rva006F8F00Payload@@QAEXPAX0PAH1@Z
// Retail 0x006F8E60 (121 bytes, thiscall ret 10h), called once per list node
// by Rva006F8F00Owner::updateBuffers (0x006F8F00) through ILT 0x0000D7BA.
// It records the node's first index/vertex, fills its vertices through the
// 0x006F83F0 copier (ILT 0x0000F9BB, skipped without a mesh) and its indices
// through the 0x006F8720 copier (ILT 0x000248A7), both on this object, then
// advances the caller's running counts. Member names follow the banked
// 2026-09-21 attempt (W3DBridge::getIndicesNVertices shape).

class MeshClass;

// 0x006F83F0 (pinned typed view; body still a gen_asm dump).
class Rva006F8700Owner
{
public:
	int rva006F83F0(void *a, int b, void *c, void *p);
};

// 0x006F8720, Rva006F8720GetModelIndices.cpp.
class Rva006F8720MeshBuffer
{
public:
	int getModelIndices(unsigned short *destination_ib, int curIndex, int vertexOffset, MeshClass *pMesh);
};

// Rva006F8700Owner::rva006F8700 (0x006F8700) is this null check in front of
// the copier; retail inlines it here, so the vertex count is loaded before the
// test. A file-static copy keeps the TU from emitting a second COMDAT of it.
static __forceinline int copyVerticesIfMesh(Rva006F8700Owner *owner, void *a, int b, void *c, void *p)
{
	if (p == 0)
		return (0);
	return owner->rva006F83F0(a, b, c, p);
}

class Rva006F8F00Payload
{
public:
	void perNode(void *destination_ib, void *destination_vb, int *curIndexP, int *curVertexP);

private:
	char m_prefix1[0x24];
	MeshClass *m_mesh;		// +0x24
	char m_prefix2[0x38 - 0x28];
	int m_firstIndex;		// +0x38
	int m_numVertex;		// +0x3c
	int m_firstVertex;		// +0x40
	int m_numPolygons;		// +0x44
	char m_pad48[4];
	char m_field4C[4];		// +0x4c, passed by address to the vertex copier
};

// The tail is W3DBridge::getIndicesNVertices's simple branch (ZH
// W3DBridgeBuffer.cpp) without its overflow early-outs.
void Rva006F8F00Payload::perNode(void *destination_ib, void *destination_vb, int *curIndexP, int *curVertexP)
{
	m_firstVertex = *curVertexP;
	m_firstIndex = *curIndexP;
	m_numVertex = 0;
	m_numPolygons = 0;
	int numVertex = copyVerticesIfMesh(reinterpret_cast<Rva006F8700Owner *>(this), destination_vb, *curVertexP, m_field4C, m_mesh);
	int numIndex = reinterpret_cast<Rva006F8720MeshBuffer *>(this)->getModelIndices(
		(unsigned short *)destination_ib, *curIndexP, *curVertexP, m_mesh);
	*curIndexP += numIndex;
	*curVertexP += numVertex;
	m_numVertex += numVertex;
	m_numPolygons += numIndex / 3;
}
