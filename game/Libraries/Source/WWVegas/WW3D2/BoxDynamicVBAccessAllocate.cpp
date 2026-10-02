// cl: /DNDEBUG /MD /EHsc
//
// BoxDynamicVBAccessClass DX8 per-slot allocator at retail RVA 0091F5B0
// (384 bytes). The matched constructor at RVA 0091F730 calls this when
// type == 2; the sorting-array path is owned by
// BoxDynamicVBAccess_AllocateSorting.cpp at RVA 0091F040.
// The reference vertex-buffer layout is four bytes shorter than the retail
// 0x20-byte allocation, so this TU retains its standalone ABI views.

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

extern bool BfmeDynamicDX8VertexBufferInUse[];
extern unsigned short BfmeDynamicDX8VertexBufferOffset[];
extern unsigned short BfmeDynamicDX8VertexBufferSize[];
extern BfmeDX8VertexBuffer *BfmeDynamicDX8VertexBuffer[];
extern const unsigned BfmeDynamicFVFTable[];
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

	void bfmeAllocateSorting();
};

// The sorting-array path at RVA 0091F040 is owned by
// BoxDynamicVBAccess_AllocateSorting.cpp.

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
