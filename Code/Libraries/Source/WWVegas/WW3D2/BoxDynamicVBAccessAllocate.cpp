// cl: /DNDEBUG /MD /EHsc
//
// BoxDynamicVBAccessClass allocate helpers. Reloc names are swapped vs
// Generals: bfmeAllocateDynamic is the sorting-array path (retail 0x0091F040,
// 274B) and bfmeAllocateSorting is the DX8 per-slot path (retail 0x0091F5B0,
// 384B). The matched ctor at 0x0091F730 calls them that way (type==2 ->
// sorting helper). Vendored DX8/Sorting VB classes are 4 bytes short of the
// retail 0x20 allocation, so this TU uses standalone views.

class BfmeDynamicVertexBuffer
{
public:
	virtual void Delete_This(void);
	int m_bfmeNumRefs;

	void Add_Ref(void)
	{
		++m_bfmeNumRefs;
	}

	void Release_Ref(void)
	{
		--m_bfmeNumRefs;
		if (m_bfmeNumRefs == 0)
			Delete_This();
	}
};

class SortingVertexBufferClass : public BfmeDynamicVertexBuffer
{
public:
	SortingVertexBufferClass(unsigned short count);

private:
	unsigned char m_bfmeRest[0x18];
};

class BfmeDX8VertexBuffer : public BfmeDynamicVertexBuffer
{
public:
	enum UsageType { USAGE_DEFAULT = 0, USAGE_DYNAMIC = 1 };

	BfmeDX8VertexBuffer(unsigned fvf, unsigned short count, UsageType usage, unsigned unused);

	int m_bfme08;
	int m_bfme0C;
	int m_bfme10;
	int m_bfme14;
	unsigned char m_startFlag;
	unsigned char m_bfmePad[7];
};

extern bool BfmeDynamicSortingVertexArrayInUse;
extern unsigned short BfmeDynamicSortingVertexArrayOffset;
extern unsigned short BfmeDynamicSortingVertexArraySize;
extern SortingVertexBufferClass *BfmeDynamicSortingVertexArray;

extern bool BfmeDynamicDX8VertexBufferInUse[21];
extern unsigned short BfmeDynamicDX8VertexBufferOffset[21];
extern unsigned short BfmeDynamicDX8VertexBufferSize[21];
extern BfmeDX8VertexBuffer *BfmeDynamicDX8VertexBuffer[21];
extern unsigned BfmeDynamicFVFTable[21];
extern unsigned char *BfmeCurrentCaps;

class BoxDynamicVBAccessClass
{
	void *m_unused;
	unsigned m_type;
	int m_index;
	int m_start;
	unsigned short m_vertexCount;
	unsigned short m_vertexBufferOffset;
	BfmeDynamicVertexBuffer *m_vertexBuffer;

	void bfmeAllocateDynamic();
	void bfmeAllocateSorting();
};

void BoxDynamicVBAccessClass::bfmeAllocateDynamic()
{
	unsigned new_count;
	unsigned short offset = BfmeDynamicSortingVertexArrayOffset;
	new_count = (unsigned)m_vertexCount + (unsigned)offset;
	SortingVertexBufferClass *buffer = BfmeDynamicSortingVertexArray;
	BfmeDynamicSortingVertexArrayInUse = 1;
	if (new_count > (unsigned)BfmeDynamicSortingVertexArraySize)
	{
		if (buffer != 0)
		{
			buffer->Release_Ref();
			buffer = 0;
			BfmeDynamicSortingVertexArray = 0;
		}
		BfmeDynamicSortingVertexArraySize = (unsigned short)new_count;
		if ((unsigned short)new_count < 0x1388)
			BfmeDynamicSortingVertexArraySize = 0x1388;
	}
	if (buffer == 0)
	{
		buffer = new SortingVertexBufferClass(BfmeDynamicSortingVertexArraySize);
		offset = 0;
		BfmeDynamicSortingVertexArray = buffer;
		BfmeDynamicSortingVertexArrayOffset = offset;
	}
	if (buffer != 0)
		buffer->Add_Ref();
	if (m_vertexBuffer != 0)
		m_vertexBuffer->Release_Ref();
	m_vertexBuffer = buffer;
	m_vertexBufferOffset = offset;
}

void BoxDynamicVBAccessClass::bfmeAllocateSorting()
{
	BfmeDynamicDX8VertexBufferInUse[m_index] = 1;
	if (m_vertexCount > BfmeDynamicDX8VertexBufferSize[m_index])
	{
		BfmeDX8VertexBuffer *buffer = BfmeDynamicDX8VertexBuffer[m_index];
		if (buffer != 0)
		{
			buffer->Release_Ref();
			BfmeDynamicDX8VertexBuffer[m_index] = 0;
		}
		BfmeDynamicDX8VertexBufferSize[m_index] = m_vertexCount;
		if (BfmeDynamicDX8VertexBufferSize[m_index] < 0x1388)
			BfmeDynamicDX8VertexBufferSize[m_index] = 0x1388;
	}
	if (BfmeDynamicDX8VertexBuffer[m_index] == 0)
	{
		BfmeDX8VertexBuffer::UsageType usage = BfmeDX8VertexBuffer::USAGE_DYNAMIC;
		if (BfmeCurrentCaps[0x13b])
			usage = (BfmeDX8VertexBuffer::UsageType)5;
		BfmeDynamicDX8VertexBuffer[m_index] = new BfmeDX8VertexBuffer(
			BfmeDynamicFVFTable[m_index],
			BfmeDynamicDX8VertexBufferSize[m_index],
			usage,
			0);
		BfmeDynamicDX8VertexBufferOffset[m_index] = 0;
	}
	BfmeDynamicDX8VertexBuffer[m_index]->m_startFlag = (unsigned char)(m_start != 0);
	if ((unsigned)m_vertexCount + BfmeDynamicDX8VertexBufferOffset[m_index] > BfmeDynamicDX8VertexBufferSize[m_index])
		BfmeDynamicDX8VertexBufferOffset[m_index] = 0;
	if (BfmeDynamicDX8VertexBuffer[m_index] != 0)
		BfmeDynamicDX8VertexBuffer[m_index]->Add_Ref();
	if (m_vertexBuffer != 0)
		m_vertexBuffer->Release_Ref();
	m_vertexBuffer = BfmeDynamicDX8VertexBuffer[m_index];
	m_vertexBufferOffset = BfmeDynamicDX8VertexBufferOffset[m_index];
}
