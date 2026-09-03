// cl: /DNDEBUG /MD /EHsc
// readable body of ??1W3DBridge@@QAE@XZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DBridgeBuffer.cpp
// W3DBridge destructor, retail 0x006D88A0 (94 bytes).
//
// Body calls clearBridge (ILT 0x0002C1F6 -> 0x006D7680). Members then run in
// reverse declaration order: AsciiString at +0x108 (releaseBuffer 0x00887940)
// then the texture pointer at +0x34 (TextureClass::Release_Ref 0x009EB7A0).

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DBridgeBuffer.h
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
