// cl: /DNDEBUG /MD /EHsc
//
// BFME's road buffer constructor at retail RVA 0x006DED60. The BaseHeightMap
// constructor allocates this 0x110-byte object for its road buffer, and the
// reset path calls the matching road-buffer cleanup at 0x00706E60.

// stlport
#include <set>

class Rva006DED60RoadRef
{
public:
	Rva006DED60RoadRef();
	~Rva006DED60RoadRef();

	unsigned int m_first;
	unsigned int m_second;
	unsigned char m_flag;
};

typedef _STL::_Rb_tree<int, int, _STL::_Identity<int>, _STL::less<int>, _STL::allocator<int> > Rva006DED60RoadSet;

class RefCountClass
{
public:
	virtual void Delete_This();
	int NumRefs;

	void Release_Ref()
	{
		if (--NumRefs == 0)
			Delete_This();
	}
};

class DX8VertexBufferClass : public RefCountClass
{
public:
	enum UsageType { USAGE_DEFAULT, USAGE_DYNAMIC };
	DX8VertexBufferClass(unsigned fvf, unsigned short count, UsageType usage, unsigned size);

private:
	char m_storage[0x18];
};

class DX8IndexBufferClass : public RefCountClass
{
public:
	enum UsageType { USAGE_DEFAULT, USAGE_DYNAMIC };
	DX8IndexBufferClass(unsigned count, UsageType usage);

private:
	char m_storage[0x10];
};

class Rva006DED60RoadBuffer
{
public:
	Rva006DED60RoadBuffer();

	void rva006DEB70();
	void allocateRoadBuffers();

private:
	DX8VertexBufferClass *m_vertexBuffer;
	DX8IndexBufferClass *m_indexBuffer;
	int m_numRoads;
	int m_initializedRoads;
	int m_maxRoadVertices;
	int m_maxRoadIndices;
	Rva006DED60RoadRef m_roadRefs[10];
	unsigned int m_padding90;
	Rva006DED60RoadSet m_roadSets[10];
	unsigned char m_initialized;
};

Rva006DED60RoadBuffer::Rva006DED60RoadBuffer()
{
	m_initialized = 0;
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_numRoads = 0;
	m_initializedRoads = 0;
	m_maxRoadIndices = 0xea60;
	m_maxRoadVertices = 0x7530;

	for (int i = 0; i < 10; ++i)
		m_roadRefs[i].m_first = 0;

	rva006DEB70();
	allocateRoadBuffers();
	m_initialized = 1;
}

// ?allocateRoadBuffers@Rva006DED60RoadBuffer@@QAEXXZ
// Retail 0x006DAD80, reached through the pinned ILT 0x0040566E from the
// constructor above and from BaseHeightMapRenderObjClass::ReAcquireResources.
// Same shape as W3DBibBuffer::allocateBibBuffers: release both buffers, then a
// dynamic 0x142-FVF vertex buffer of 30000+4 and an index buffer of 60000+4.
void Rva006DED60RoadBuffer::allocateRoadBuffers()
{
	if (m_vertexBuffer || m_indexBuffer)
	{
		if (m_vertexBuffer)
		{
			m_vertexBuffer->Release_Ref();
			m_vertexBuffer = 0;
		}
		if (m_indexBuffer)
		{
			m_indexBuffer->Release_Ref();
			m_indexBuffer = 0;
		}
	}

	m_vertexBuffer = new DX8VertexBufferClass(0x142, 0x7530 + 4,
		DX8VertexBufferClass::USAGE_DYNAMIC, 0);
	m_indexBuffer = new DX8IndexBufferClass(0xea60 + 4,
		DX8IndexBufferClass::USAGE_DYNAMIC);
	m_numRoads = 0;
	m_initializedRoads = 0;
	m_maxRoadIndices = 0xea60;
	m_maxRoadVertices = 0x7530;
}
