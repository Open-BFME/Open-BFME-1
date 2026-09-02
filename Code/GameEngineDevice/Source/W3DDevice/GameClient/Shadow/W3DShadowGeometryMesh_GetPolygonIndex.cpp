// Open-BFME: W3DShadowGeometryMesh::GetPolygonIndex, retail 0x007BA200, 72 bytes.
//
// ZH twin: remap a triangle's three indices through m_parentVerts. BFME keeps
// the polygon array behind a pointer at this+0 (items at that+0xC) and the
// parent-vertex table at this+0x20, which is re-read for each corner.

struct TriIndex
{
	unsigned short I;
	unsigned short J;
	unsigned short K;
};

struct PolygonHolder
{
	unsigned char m_pad[0x0C];
	const TriIndex *m_polygons;
};

class W3DShadowGeometryMesh
{
public:
	void GetPolygonIndex(long dwPolyId, short *psIndexList) const;

private:
	PolygonHolder *m_holder;
	unsigned char m_pad[0x1C];
	unsigned short *m_parentVerts;
};

void W3DShadowGeometryMesh::GetPolygonIndex(long dwPolyId, short *psIndexList) const
{
	const TriIndex *polyi = &m_holder->m_polygons[dwPolyId];
	*psIndexList++ = m_parentVerts[polyi->I];
	*psIndexList++ = m_parentVerts[polyi->J];
	*psIndexList++ = m_parentVerts[polyi->K];
}
