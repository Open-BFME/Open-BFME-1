// ?removeTreesAndPropsForConstruction@BaseHeightMapRenderObjClass@@QAEXPBUCoord3D@@ABVGeometryInfo@@M@Z
// partial score=0.99 date=2026-09-02
// ?removeTreesAndPropsForConstruction@BaseHeightMapRenderObjClass@@QAEXPBUCoord3D@@ABVGeometryInfo@@M@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: clean C++ terrain construction-clearing dispatch.

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

class BaseHeightMapRenderObjClass
{
public:
	void removeTreesAndPropsForConstruction(const Coord3D *pos, const GeometryInfo &geom, float angle);
private:
	char m_pad[0x3098];
	W3DTreeBuffer *m_treeBuffer;
	W3DPropBuffer *m_propBuffer;
};

void BaseHeightMapRenderObjClass::removeTreesAndPropsForConstruction(
	const Coord3D *pos, const GeometryInfo &geom, float angle)
{
	if (m_treeBuffer)
		m_treeBuffer->removeTreesForConstruction(pos, geom, angle);
	if (m_propBuffer)
		m_propBuffer->removePropsForConstruction(pos, geom, angle);
}
