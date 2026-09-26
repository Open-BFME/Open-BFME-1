// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
//
// BFME's road-buffer destructor at retail RVA 0x006DEA80. The matching
// constructor at 0x006DED60 lays out the two resource references, ten road
// references, and ten road sets used below.

class Rva006DED60RoadResource
{
public:
	virtual void Delete_This();

	void Release_Ref()
	{
		--m_refCount;
		if (m_refCount == 0)
			Delete_This();
	}

private:
	int m_refCount;
};

class Rva006DED60RoadRef
{
public:
	~Rva006DED60RoadRef();

	Rva006DED60RoadResource *m_resource;
	unsigned int m_name;
	unsigned char m_flag;
};

class Rva006DED60RoadSet
{
public:
	~Rva006DED60RoadSet();

private:
	unsigned int m_data[3];
};

static void release(Rva006DED60RoadResource *&resource)
{
	if (resource != 0)
	{
		resource->Release_Ref();
		resource = 0;
	}
}

class Rva006DED60RoadBuffer
{
public:
	~Rva006DED60RoadBuffer();

private:
	Rva006DED60RoadResource *m_vertexBuffer;
	Rva006DED60RoadResource *m_indexBuffer;
	int m_numRoads;
	int m_initializedRoads;
	int m_maxRoadVertices;
	int m_maxRoadIndices;
	Rva006DED60RoadRef m_roadRefs[10];
	unsigned int m_padding90;
	Rva006DED60RoadSet m_roadSets[10];
	unsigned char m_initialized;
};

Rva006DED60RoadBuffer::~Rva006DED60RoadBuffer()
{
	release(m_vertexBuffer);
	release(m_indexBuffer);
	for (int i = 0; i < 10; ++i)
		release(m_roadRefs[i].m_resource);
}
