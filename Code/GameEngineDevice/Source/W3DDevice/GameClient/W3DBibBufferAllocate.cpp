// cl: /DNDEBUG /MD /EHsc
// W3DBibBuffer::allocateBibBuffers, retail RVA 0x006D69D0 (205 bytes).
// Called by the matched constructor at RVA 0x006D73C0 via ILT 0x00024D66.
// BFME first releases existing buffers, then allocates the retail 0x20-byte
// vertex buffer (FVF 0x142) and 0x18-byte index buffer. Constructor ABI views
// follow RoadTypeLoadTexture.cpp; buffer references use a 32-bit count at +4.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DBibBuffer.h

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

class BfmeDX8VertexBuffer : public RefCountClass
{
public:
	enum UsageType { USAGE_DEFAULT, USAGE_DYNAMIC };
	BfmeDX8VertexBuffer(unsigned fvf, unsigned short count, UsageType usage, unsigned size);
	char m_storage[0x18];
};

class DX8IndexBufferClass : public RefCountClass
{
public:
	enum UsageType { USAGE_DEFAULT, USAGE_DYNAMIC };
	DX8IndexBufferClass(unsigned count, UsageType usage);
	char m_storage[0x10];
};

class W3DBibBuffer
{
public:
	BfmeDX8VertexBuffer *m_vertexBib;
	int m_vertexBibSize;
	DX8IndexBufferClass *m_indexBib;
	int m_indexBibSize;
	void *m_bibTexture;
	void *m_highlightBibTexture;
	int m_curNumBibVertices;
	int m_curNumBibIndices;

protected:
	void allocateBibBuffers();
};

void W3DBibBuffer::allocateBibBuffers()
{
	if (m_vertexBib || m_indexBib)
	{
		if (m_vertexBib)
		{
			m_vertexBib->Release_Ref();
			m_vertexBib = 0;
		}
		if (m_indexBib)
		{
			m_indexBib->Release_Ref();
			m_indexBib = 0;
		}
	}

	m_vertexBib = new BfmeDX8VertexBuffer(0x142,
		(unsigned short)(m_vertexBibSize + 4), BfmeDX8VertexBuffer::USAGE_DYNAMIC, 0);
	m_indexBib = new DX8IndexBufferClass(m_indexBibSize + 4,
		DX8IndexBufferClass::USAGE_DYNAMIC);
	m_curNumBibVertices = 0;
	m_curNumBibIndices = 0;
}
