// ?allocateScorchBuffers@BaseHeightMapRenderObjClass@@AAEXXZ
// Retail 0x006C9530. BFME selects the scorch-buffer capacities from the
// writable half-height-map setting before constructing the two DX8 buffers.

typedef int Int;
typedef unsigned char Bool;

struct GlobalData
{
	char m_unknown[0xdcd];
	Bool m_useHalfHeightMap;
};

#define TheWritableGlobalData (*(GlobalData **)0x012ED5C8)

class DX8VertexBufferClass
{
public:
	enum UsageType { USAGE_DEFAULT = 0, USAGE_DYNAMIC = 1 };

	DX8VertexBufferClass(unsigned fvf, unsigned short count, UsageType usage,
		unsigned vertex_size);

private:
	char m_body[0x20];
};

class DX8IndexBufferClass
{
public:
	enum UsageType { USAGE_DEFAULT = 0, USAGE_DYNAMIC = 1 };

	DX8IndexBufferClass(unsigned count, UsageType usage);

private:
	char m_body[0x18];
};

class BaseHeightMapRenderObjClass
{
private:
	void allocateScorchBuffers(void);

	char m_beforeBuffers[0x2fd8];
	DX8VertexBufferClass *m_vertexScorch;
	DX8IndexBufferClass *m_indexScorch;
	char m_betweenBuffersAndCounts[4];
	Int m_curNumScorchVertices;
	Int m_curNumScorchIndices;
	Int m_maxScorchVertices;
	Int m_maxScorchIndices;
};

void BaseHeightMapRenderObjClass::allocateScorchBuffers(void)
{
	if (TheWritableGlobalData->m_useHalfHeightMap) {
		m_maxScorchVertices = 0xdac0;
		m_maxScorchIndices = 0x3fffc;
	} else {
		m_maxScorchVertices = 0x36b0;
		m_maxScorchIndices = 0xffff;
	}
	m_vertexScorch = new DX8VertexBufferClass(
		0x142, (unsigned short)m_maxScorchVertices,
		DX8VertexBufferClass::USAGE_DEFAULT, 0);
	m_indexScorch = new DX8IndexBufferClass(
		m_maxScorchIndices, DX8IndexBufferClass::USAGE_DEFAULT);
	m_curNumScorchVertices = 0;
	m_curNumScorchIndices = 0;
}
