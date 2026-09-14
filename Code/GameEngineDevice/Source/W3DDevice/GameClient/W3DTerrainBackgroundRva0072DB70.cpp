// cl: /DNDEBUG /MD
//
// Retail 0x0072DB70. Neighbour of doTesselatedUpdate at 0x0072C7F0 and
// constructor at 0x00729AE0. Vertex-buffer lock path uses the matched
// WriteLockClass ctor/dtor; false path calls doTesselatedUpdate.

class VertexBufferClass
{
public:
	class WriteLockClass
	{
		VertexBufferClass *m_vertexBuffer;
		void *m_vertices;

	public:
		WriteLockClass(VertexBufferClass *vertex_buffer, int flags);
		~WriteLockClass();
		void *Get_Vertex_Array() { return m_vertices; }
	};
};

class WorldHeightMap;

struct IRegion2D
{
	int lo_x;
	int lo_y;
	int hi_x;
	int hi_y;
};

class W3DTerrainBackground
{
public:
	void rva0072DB70(unsigned char lockPath, int value);
	void doTesselatedUpdate(const IRegion2D &partialRange, WorldHeightMap *htMap, bool doTextures);

private:
	unsigned char m_pad00[0x1c];
	VertexBufferClass *m_vertexTerrain;
	unsigned char m_pad20[0x18];
	int m_curNumTerrainVertices;
	unsigned char m_pad3C[4];
	int m_xOrigin;
	int m_yOrigin;
	int m_width;
	WorldHeightMap *m_map;
};

// ?rva0072DB70@W3DTerrainBackground@@QAEXEH@Z
void W3DTerrainBackground::rva0072DB70(unsigned char lockPath, int value)
{
	if (lockPath)
	{
		if (m_curNumTerrainVertices > 0)
		{
			VertexBufferClass::WriteLockClass lock(m_vertexTerrain, 0);
			int count = m_curNumTerrainVertices;
			int i = 0;
			if (count > 0)
			{
				unsigned char *p = (unsigned char *)lock.Get_Vertex_Array() + 8;
				do
				{
					// Reload value from the stack each iteration so EDX is
					// shared with the count load; a hoisted copy steals EDI.
					*(int *)p = *(volatile int *)&value;
					p += 0x20;
					++i;
				} while (i < m_curNumTerrainVertices);
			}
		}
	}
	else
	{
		IRegion2D range;
		range.lo_x = 0;
		range.lo_y = 0;
		range.hi_x = m_xOrigin + m_width;
		range.hi_y = m_yOrigin + m_width;
		doTesselatedUpdate(range, m_map, false);
	}
}
