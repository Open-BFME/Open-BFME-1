// cl: /DNDEBUG /MD /EHsc

class VertexBufferClass
{
public:
	class WriteLockClass
	{
		unsigned char m_storage[ 8 ];

	public:
		WriteLockClass(VertexBufferClass *buffer, int flags);
	};
};

class IndexBufferClass
{
public:
	class WriteLockClass
	{
		unsigned char m_storage[ 8 ];

	public:
		WriteLockClass(IndexBufferClass *buffer, int flags);
	};
};

class BfmeVolumetricShadowBufferLocks
{
	VertexBufferClass *m_vertexBuffer;
	IndexBufferClass *m_indexBuffer;
	unsigned int m_unreconstructed_008;
	VertexBufferClass::WriteLockClass *m_vertexLock;
	IndexBufferClass::WriteLockClass *m_indexLock;
	int m_vertexCapacity;
	int m_indexCapacity;

public:
	void lockBuffers();
};

void BfmeVolumetricShadowBufferLocks::lockBuffers()
{
	m_vertexLock = new VertexBufferClass::WriteLockClass(m_vertexBuffer, 0x2800);
	m_indexLock = new IndexBufferClass::WriteLockClass(m_indexBuffer, 0x2800);
	m_vertexCapacity = 30000;
	m_indexCapacity = 30000;
}
