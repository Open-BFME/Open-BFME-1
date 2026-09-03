// cl: /DNDEBUG /MD /EHsc
// BFME W3DRoadBuffer teardown at retail 0x0070FAF0.

class RefCounted
{
public:
	virtual void Delete_This() = 0;
	int m_refs;

	void Release_Ref()
	{
		--m_refs;
		if (m_refs == 0)
			Delete_This();
	}
};

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
	~W3DRoadBuffer();

private:
	void *m_roadTypes;
	void *m_roads;
	int m_numRoads;
	unsigned char m_initialized;
	unsigned char m_pad0d[3];
	RefCounted *m_map;
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
	void freeRoadBuffers();
};

W3DRoadBuffer::~W3DRoadBuffer()
{
	freeRoadBuffers();
	if (m_map != 0)
	{
		m_map->Release_Ref();
		*(volatile RefCounted **)&m_map = 0;
	}
}
