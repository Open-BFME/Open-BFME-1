// ?getPlanesChecked@Rva00925030Geometry@@QAEPAVVector4@@_N@Z
class Vector4;
class MeshGeometryClass {
public:
	virtual void s0(); virtual void s1(); virtual void s2();
	virtual void onPlanes(Vector4* planes);
protected:
	Vector4* get_planes(bool create);
	char m_pad[0x18 - 4];
	unsigned int m_flags;
};
struct Rva00925030Geometry : MeshGeometryClass {
	Vector4* getPlanesChecked(bool create);
};
Vector4* Rva00925030Geometry::getPlanesChecked(bool create)
{
	Vector4* planes = get_planes(create);
	if (planes && (m_flags & 2))
		onPlanes(planes);
	return planes;
}
