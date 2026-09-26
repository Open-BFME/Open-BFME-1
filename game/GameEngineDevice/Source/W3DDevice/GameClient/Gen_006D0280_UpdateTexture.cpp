// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// The companion terrain texture slot at retail 0x006D0280 has the same
// refresh body as 0x006D0150, with a four-byte layout shift.

class TextureClass
{
public:
	void Release_Ref(void);
};

class Gen_00920a60
{
public:
	void m(int value);
};

class ShroudFilter : public Gen_00920a60
{
};

class ShroudTexture
{
public:
	ShroudFilter *getFilter(void);

	TextureClass *m_texture;
	char m_padding04[0x10];
};

class AsciiString
{
public:
	void set(const AsciiString &other);
	int compare(const AsciiString &other) const;
	~AsciiString(void);

	char *m_data;
};

class BFMEWaterTrackTextureHandle
{
public:
	TextureClass *m_texture;

	~BFMEWaterTrackTextureHandle(void)
	{
		if (m_texture)
			m_texture->Release_Ref();
	}
};

extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(
	char *name, int mipCount, int format);

static inline void Gen006D0280AssignTexture(
	TextureClass *&destination,
	const BFMEWaterTrackTextureHandle &texture)
{
	if (texture.m_texture)
		++*(unsigned short *)((char *)texture.m_texture + 4);
	if (destination)
		destination->Release_Ref();
	destination = texture.m_texture;
}

class Gen006D0280Owner
{
public:
	void updateTexture(AsciiString textureName);

private:
	char m_padding00[0x3068];
	ShroudTexture m_texture;
	AsciiString m_textureName;
	char m_padding3080[0xc];
	AsciiString m_defaultTextureName;
};

void Gen006D0280Owner::updateTexture(AsciiString textureName)
{
	if (textureName.m_data == 0 ||
		*(unsigned short *)((char *)textureName.m_data + 4) == 0)
	{
		textureName.set(m_defaultTextureName);
	}

	AsciiString *name = &m_textureName;
	if (textureName.compare(*name) != 0)
	{
		name->set(textureName);

		const char *text;
		if (name->m_data)
			text = name->m_data + 8;
		else
			text = (const char *)0x0107388b;

		Gen006D0280AssignTexture(
			m_texture.m_texture,
			BFMEGetWaterTrackTexture((char *)text, 0, 0));
		m_texture.getFilter()->m(1);
	}
}
