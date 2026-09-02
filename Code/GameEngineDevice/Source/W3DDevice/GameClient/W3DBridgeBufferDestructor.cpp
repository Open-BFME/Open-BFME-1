// cl: /DNDEBUG /MD /EHsc
// W3DBridgeBuffer destructor, retail 0x006D8A80 (169 bytes).
// Body releases the three buffer/material refs at +0/+4/+8. Members then
// run reverse: 200 W3DBridge objects of 0x114 bytes at +0x18, then texture
// Release_Ref at +0xC.

typedef int Int;

class RefCountClass
{
public:
	virtual void Delete_This(void) = 0;

	void Release_Ref(void)
	{
		if (--NumRefs == 0)
			Delete_This();
	}

	Int NumRefs;
};

class TextureClass
{
public:
	void Release_Ref(void);
};

class TextureRef
{
public:
	~TextureRef()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	TextureClass *m_ptr;
};

class W3DBridge
{
public:
	~W3DBridge();
	unsigned char m_bytes[0x114];
};

class W3DBridgeBuffer
{
public:
	~W3DBridgeBuffer();

private:
	RefCountClass *m_vertexBridge;
	RefCountClass *m_indexBridge;
	RefCountClass *m_vertexMaterial;
	TextureRef m_bridgeTexture;
	Int m_curNumBridgeVertices;
	Int m_curNumBridgeIndices;
	W3DBridge m_bridges[200];
};

W3DBridgeBuffer::~W3DBridgeBuffer()
{
	if (m_vertexBridge)
	{
		m_vertexBridge->Release_Ref();
		m_vertexBridge = 0;
	}
	if (m_indexBridge)
	{
		m_indexBridge->Release_Ref();
		m_indexBridge = 0;
	}
	if (m_vertexMaterial)
	{
		m_vertexMaterial->Release_Ref();
		m_vertexMaterial = 0;
	}
}
