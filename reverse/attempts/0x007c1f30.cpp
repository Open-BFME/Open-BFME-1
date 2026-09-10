// ?fill@BfmeShadowBufferEntry@@QAEXPAE@Z
// partial score=0.85 date=2026-09-10
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

typedef float Real;

extern const Real BfmeZeroRange;

struct BfmeShadowVector3
{
	Real x, y, z;
};

struct BfmeShadowIndexTriple
{
	unsigned short i0, i1, i2;
};

struct BfmeShadowIndexResource
{
	unsigned char m_unreconstructed_00[0xc];
	BfmeShadowIndexTriple *m_indices;
};

struct BfmeShadowMeshGeometry
{
	unsigned char m_unreconstructed_00[0x24];
	int m_numPolygon;
	unsigned char m_unreconstructed_28[0x2c - 0x28];
	BfmeShadowIndexResource *m_lock;
};

struct BfmeShadowMesh
{
	unsigned char m_unreconstructed_00[0xc8];
	BfmeShadowMeshGeometry *m_geometry;
};

struct BfmeShadowBufferEntry
{
	BfmeShadowMesh *m_mesh;
	BfmeShadowVector3 *m_vertices;
	unsigned char *m_flags;
	void *m_allocation2;
	unsigned int m_reserved10;
	unsigned char m_reserved14;

	void fill(unsigned char *value);
};

void BfmeShadowBufferEntry::fill(unsigned char *value)
{
	const BfmeShadowVector3 *lightDir = (const BfmeShadowVector3 *)value;
	BfmeShadowMeshGeometry *geometry = m_mesh->m_geometry;
	BfmeShadowIndexTriple *tri = geometry->m_lock->m_indices;
	int count = geometry->m_numPolygon;
	unsigned char *out = m_flags;

	for (; count > 0; --count, ++tri, ++out)
	{
		BfmeShadowVector3 *verts = m_vertices;
		const BfmeShadowVector3 *pv0 = &verts[tri->i0];
		const BfmeShadowVector3 *pv2 = &verts[tri->i2];
		const BfmeShadowVector3 *pv1 = &verts[tri->i1];

		Real v1x = pv1->x;
		Real v1y = pv1->y;
		Real v1z = pv1->z;

		Real e2x = v1x - pv0->x;
		Real e2y = v1y - pv0->y;
		Real e2z = v1z - pv0->z;
		Real e1x = v1x - pv2->x;
		Real e1y = v1y - pv2->y;
		Real e1z = v1z - pv2->z;

		Real cx = e1y * e2z - e1z * e2y;
		Real cy = e1z * e2x - e1x * e2z;
		Real cz = e1x * e2y - e1y * e2x;

		Real dot = cx * lightDir->x + cy * lightDir->y + cz * lightDir->z;

		*out = (unsigned char)(dot < BfmeZeroRange);
	}
}
