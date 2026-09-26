// cl: /DNDEBUG /MD /EHsc
// Reconstructed from the canonical W3D shadow mesh source and the BFME
// terrain-shadow layout.  The pool and normal-builder declarations preserve
// the retail helper ABIs; the body is ordinary C++ rather than a lifted dump.

extern void *__cdecl operator new[]( unsigned int size );
extern void __cdecl operator delete[]( void *pointer ) throw();

class Vector3
{
public:
	float X;
	float Y;
	float Z;
	Vector3();
};

struct ShadowPool
{
	bool allocate( int count, int flags );
	char m_prefix[4];
	Vector3 *buffer;
	int available;
};

// Retail 0x01306F54 / 0x01306F64. The ctor at 0x007BB520 names these
// ShadowPoolB / ShadowPoolBLimit; ShadowPoolA lives at 0x01306F3C.
extern ShadowPool ShadowPoolB;
extern int ShadowPoolBLimit;

class W3DShadowGeometryMesh
{
public:
	virtual ~W3DShadowGeometryMesh();
	void buildPolygonNormals();

protected:
	Vector3 *buildPolygonNormal( long polygonIndex, Vector3 *normal ) const throw();

private:
	char m_beforeNormals[0x0c];
	Vector3 *m_polygonNormals;
	char m_beforePolygonCount[0x08];
	int m_numPolygons;
	char m_beforeTerrainFlag[0x10];
	unsigned char m_terrainShadow;
};

// ?buildPolygonNormals@W3DShadowGeometryMesh@@QAEXXZ
void W3DShadowGeometryMesh::buildPolygonNormals()
{
	if (!m_polygonNormals)
	{
		Vector3 *tempVec;
		if (m_terrainShadow)
		{
			if (ShadowPoolB.available < m_numPolygons &&
				ShadowPoolB.allocate( m_numPolygons, 0 ) &&
				ShadowPoolB.available < ShadowPoolBLimit)
				ShadowPoolBLimit = ShadowPoolB.available;
			tempVec = ShadowPoolB.buffer;
		}
		else
		{
			tempVec = new Vector3[m_numPolygons];
		}

		for (int i = 0; i < m_numPolygons; ++i)
			buildPolygonNormal( i, &tempVec[i] );
		m_polygonNormals = tempVec;
	}
}
