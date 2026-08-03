// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: W3DBufferManager::getNextVertexBuffer

class W3DBufferManager
{
public:
	struct W3DVertexBuffer
	{
		char pad[0x10];
		W3DVertexBuffer *next;
	};

	enum VBM_FVF_TYPES
	{
		VBM_FVF_INVALID = 0
	};

	W3DVertexBuffer *getNextVertexBuffer(W3DVertexBuffer *buffer, VBM_FVF_TYPES type);

private:
	char m_pad[0x9000];
	W3DVertexBuffer *m_heads[1];
};

// ?getNextVertexBuffer@W3DBufferManager@@QAEPAUW3DVertexBuffer@1@PAU21@W4VBM_FVF_TYPES@1@@Z
W3DBufferManager::W3DVertexBuffer *W3DBufferManager::getNextVertexBuffer(
	W3DVertexBuffer *buffer, VBM_FVF_TYPES type)
{
	if (!buffer)
		return m_heads[type];
	return buffer->next;
}