// cl: /DNDEBUG /MD /EHsc
// W3DBridge destructor, retail 0x006D88A0 (94 bytes).
//
// Body calls clearBridge (ILT 0x0002C1F6 -> 0x006D7680). Members then run in
// reverse declaration order: AsciiString at +0x108 (releaseBuffer 0x00887940)
// then the texture pointer at +0x34 (TextureClass::Release_Ref 0x009EB7A0).

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

class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

class W3DBridge
{
public:
	void clearBridge(void);
	~W3DBridge(void);

private:
	unsigned char m_unmodelled_000[0x34];
	TextureRef m_bridgeTexture;
	unsigned char m_unmodelled_038[0x108 - 0x38];
	AsciiString m_templateName;
};

W3DBridge::~W3DBridge(void)
{
	clearBridge();
}
