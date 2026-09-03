// cl: /DNDEBUG /MD /EHsc
// readable body of ??1W3DBridgeBuffer@@QAE@XZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DBridgeBuffer.cpp
// W3DBridgeBuffer destructor, retail 0x006D8A80 (169 bytes).
// Body releases the three buffer/material refs at +0/+4/+8. Members then
// run reverse: 200 W3DBridge objects of 0x114 bytes at +0x18, then texture
// Release_Ref at +0xC.

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DBridgeBuffer.h
class W3DBridge
{
public:
	~W3DBridge();
	unsigned char m_bytes[0x114];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DBridgeBuffer.h
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
