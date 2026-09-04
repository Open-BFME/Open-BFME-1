// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// Open-BFME5: BaseHeightMapRenderObjClass construction clearing, retail 0x006C88E0, 61 bytes.

struct Coord3D;
class GeometryInfo;

class W3DTreeBuffer
{
public:
	void removeTreesForConstruction(const Coord3D *pos, const GeometryInfo &geom, float angle);
};

class W3DPropBuffer
{
public:
	void removePropsForConstruction(const Coord3D *pos, const GeometryInfo &geom, float angle);
};

// This view names the older BFME construction-clearing body separately from
// the 18-byte prop-only method retained in BaseHeightMap.cpp at 0x006C8930.
class BfmeBaseHeightMapRenderObjClass
{
public:
	void removeTreesAndPropsForConstruction(const Coord3D *pos, const GeometryInfo &geom, float angle);

private:
	char m_pad[0x3098];
	W3DTreeBuffer *m_treeBuffer;
	W3DPropBuffer *m_propBuffer;
};

void BfmeBaseHeightMapRenderObjClass::removeTreesAndPropsForConstruction(
	const Coord3D *pos, const GeometryInfo &geom, float angle)
{
	if (m_treeBuffer)
		m_treeBuffer->removeTreesForConstruction(pos, geom, angle);
	if (m_propBuffer)
		m_propBuffer->removePropsForConstruction(pos, geom, angle);
}
