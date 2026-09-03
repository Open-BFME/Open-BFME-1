// cl: /DNDEBUG /MD /EHsc
// BFME W3DRoadBuffer constructor at retail 0x0070FB70.

class TextureBaseClass
{
public:
	void Release_Ref();
};

class TextureRef
{
public:
	TextureRef() : m_p(0) {}
	~TextureRef()
	{
		if (m_p != 0)
			m_p->Release_Ref();
	}
	TextureBaseClass *m_p;
};

class W3DRoadBuffer
{
public:
	W3DRoadBuffer();

private:
	void *m_roadTypes;
	void *m_roads;
	int m_numRoads;
	unsigned char m_initialized;
	unsigned char m_pad0d[3];
	void *m_map;
	void *m_lights;
	unsigned char m_pad18[0x14];
	int m_curRoadType;
	int m_curUniqueID;
	unsigned char m_pad34[4];
	int m_maxRoadSegments;
	int m_maxRoadVertex;
	int m_maxRoadIndex;
	int m_maxRoadTypes;
	unsigned char m_pad48[8];
	unsigned char m_updateBuffers;
	unsigned char m_secondFlag;
	unsigned char m_pad52[2];
	TextureRef m_texture;

	protected:
	void allocateRoadBuffers();
};

W3DRoadBuffer::W3DRoadBuffer()
	: m_roads(0), m_numRoads(0), m_initialized(0),
	  m_map(0), m_lights(0), m_curRoadType(0), m_curUniqueID(0),
	  m_maxRoadSegments(500), m_maxRoadVertex(1000),
	  m_maxRoadIndex(2000), m_maxRoadTypes(8),
	  m_updateBuffers(1), m_secondFlag(1), m_texture()
{
	allocateRoadBuffers();
}
