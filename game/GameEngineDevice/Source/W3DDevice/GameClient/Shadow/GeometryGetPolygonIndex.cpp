// Retail Geometry::GetPolygonIndex, RVA 007B7FA0, 63 bytes.
// Source: EA GPL-3.0-or-later GeneralsMD W3DVolumetricShadow.cpp.
// Narrow dependency repair for RenderDynamicMeshVolume (007BC270).
// Existing ledger object-symbol already names this exact C++ implementation.
// Retail uses indices at +4, three consecutive WORD loads, and ret 8.
class Geometry {
 void* m_verts;
 unsigned short* m_indices;
public:
 unsigned short* GetPolygonIndex(long polygon, short* indexList) const;
};
unsigned short* Geometry::GetPolygonIndex(long polygon, short* indexList) const
{
 *indexList++ = m_indices[polygon*3];
 *indexList++ = m_indices[polygon*3+1];
 *indexList++ = m_indices[polygon*3+2];
 return &m_indices[polygon];
}
