// ?updateBuffers@Rva006F8F00Owner@@QAEXXZ
// partial score=0.3 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /MD /EHsc

typedef int Int;
typedef unsigned short UnsignedShort;

void W3DRadarResetLock(void);

// dx8indexbuffer.cpp / dx8vertexbuffer.cpp: WriteLockClass(Buffer*, int flags)
// RAII lock objects; only their construction/destruction call shape matters
// here, so the class bodies stay opaque address-derived shims.
class IndexBufferClass;
class VertexBufferClass;

class Rva006F8F00IndexLock
{
public:
	Rva006F8F00IndexLock(IndexBufferClass *buffer, int flags);
	~Rva006F8F00IndexLock();

	void *m_array;

private:
	unsigned char m_raw[4];
};

class Rva006F8F00VertexLock
{
public:
	Rva006F8F00VertexLock(VertexBufferClass *buffer, int flags);
	~Rva006F8F00VertexLock();

public:
	void *m_array;

private:
	unsigned char m_raw[4];
};

extern "C" char __cdecl bfmeUnlock1179(void);

class Rva006F8F00Payload
{
public:
	void perNode(int *outIdx, int *outVtx, void *indexArray, void *vertexArray);
};

struct Rva006F8F00Node
{
	Rva006F8F00Node *next;
	unsigned char m_pad4[4];
	Rva006F8F00Payload *payload;
};

class Rva006F8F00Owner
{
public:
	void updateBuffers();

private:
	unsigned char m_pad0[4];
	VertexBufferClass *m_vertexBuffer;			// +4
	IndexBufferClass *m_indexBuffer;			// +8
	unsigned char m_pad0c[8];
	Int m_curVtx;						// +0x14
	Int m_curIdx;						// +0x18
	unsigned char m_pad1c[4];
	Rva006F8F00Node *m_listHead;				// +0x20 (self-referential sentinel address)
	void *m_guard24;					// +0x24
	unsigned char m_guard28;				// +0x28
};

void Rva006F8F00Owner::updateBuffers()
{
	if (m_indexBuffer == 0)
		return;
	if (m_vertexBuffer == 0)
		return;
	if (m_guard28 == 0)
		return;
	if (m_guard24 == 0)
		return;

	m_curVtx = 0;
	m_curIdx = 0;

	W3DRadarResetLock();

	Rva006F8F00IndexLock lockIdx(m_indexBuffer, 0x2000);
	Rva006F8F00VertexLock lockVtx(m_vertexBuffer, 0x2000);

	Rva006F8F00Node *sentinel = (Rva006F8F00Node *)&m_listHead;
	for (Rva006F8F00Node *node = m_listHead; node != sentinel; node = node->next)
	{
		node->payload->perNode(&m_curVtx, &m_curIdx, lockIdx.m_array, lockVtx.m_array);
	}

	bfmeUnlock1179();
}
