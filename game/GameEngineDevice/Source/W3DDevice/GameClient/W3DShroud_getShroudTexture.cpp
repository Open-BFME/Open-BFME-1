// W3DShroud::getShroudTexture, retail 0x006D2630: Zero Hour's inline accessor
// out of line, returning the counted destination-texture handle by value.

class TextureObject
{
public:
	int m_head;							// +0x00
	unsigned short m_refs;				// +0x04
};

class TextureHandle
{
public:
	TextureHandle(void)
	{
		m_object = 0;
	}

	TextureHandle(const TextureHandle &other)
	{
		TextureObject *object = other.m_object;

		m_object = object;

		if (object)
			++object->m_refs;
	}

	~TextureHandle(void)
	{
		if (m_object)
			--m_object->m_refs;
	}

	TextureObject *m_object;			// +0x00
};

class W3DShroud
{
public:
	TextureHandle getShroudTexture(void);

private:
	char m_bfmeHead[0x1C];					// +0x00
	TextureHandle m_dstTexture;			// +0x1C
};

// ?getShroudTexture@W3DShroud@@QAE?AVTextureHandle@@XZ
TextureHandle W3DShroud::getShroudTexture(void)
{
	return m_dstTexture;
}
