// ?rva0072DB70@W3DTerrainBackground@@QAEX_NI@Z
// partial score=0.88 date=2026-09-12
// Retail RVA 0x0072DB70. Calls matched WriteLockClass ctor/dtor and
// W3DTerrainBackground::doTesselatedUpdate, so this is that class.
// cl: /DNDEBUG /MD /EHsc-

class WorldHeightMap;

struct ICoord2D
{
	int x;
	int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

class VertexBufferClass
{
public:
	class WriteLockClass
	{
	public:
		WriteLockClass(VertexBufferClass *vertex_buffer, int flags);
		~WriteLockClass();
		void *Get_Vertex_Array() { return Vertices; }

	private:
		VertexBufferClass *VertexBuffer;
		void *Vertices;
	};
};

class W3DTerrainBackground
{
public:
	void rva0072DB70(bool flag, unsigned int value);
	void doTesselatedUpdate(const IRegion2D &partialRange, WorldHeightMap *htMap, bool doTextures);

private:
	unsigned char m_pad00[0x1C];
	VertexBufferClass *m_vertexTerrain;
	unsigned char m_pad20[0x18];
	int m_curNumTerrainVertices;
	unsigned char m_pad3C[4];
	int m_xOrigin;
	int m_yOrigin;
	int m_width;
	WorldHeightMap *m_map;
};

// ?rva0072DB70@W3DTerrainBackground@@QAEX_NI@Z
void W3DTerrainBackground::rva0072DB70(bool flag, unsigned int value)
{
	if (flag)
	{
		if (m_curNumTerrainVertices <= 0)
			return;

		VertexBufferClass::WriteLockClass lock(m_vertexTerrain, 0);
		int n = m_curNumTerrainVertices;
		int i = 0;
		if (n > 0)
		{
			unsigned *p = (unsigned *)((char *)lock.Get_Vertex_Array() + 8);
			do
			{
				*p = value;
				p += 8;
				++i;
			} while (i < m_curNumTerrainVertices);
		}
	}
	else
	{
		IRegion2D region;
		region.hi.x = m_xOrigin + m_width;
		region.lo.x = 0;
		region.lo.y = 0;
		region.hi.y = m_yOrigin + m_width;
		doTesselatedUpdate(region, m_map, false);
	}
}
