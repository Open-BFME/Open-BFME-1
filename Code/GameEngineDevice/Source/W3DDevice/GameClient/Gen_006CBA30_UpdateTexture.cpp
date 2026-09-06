// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x006CBA30, 223 bytes. Near twin of the one-argument texture-name
// refresh at 0x006D0150 (Gen_006D0150_UpdateTexture.cpp): same
// BFMEGetWaterTrackTexture/ShroudTexture/Release_Ref shape, but the string
// type is UnicodeString (call target 0xc87c90, ?set@UnicodeString ...) not
// AsciiString, the fields sit at +0x3058/+0x3074/+0x3084 instead of
// +0x3064/+0x3078/+0x3088, and there is no name->compare() gate: this body
// always re-sets and re-fetches the texture. Identity is not recovered.

typedef bool Bool;

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

class UnicodeString
{
public:
	void set(const UnicodeString &other);
	~UnicodeString(void);

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

static inline void Gen006CBA30AssignTexture(
	TextureClass *&destination,
	const BFMEWaterTrackTextureHandle &texture)
{
	if (texture.m_texture)
		++*(unsigned short *)((char *)texture.m_texture + 4);
	if (destination)
		destination->Release_Ref();
	destination = texture.m_texture;
}

class Gen006CBA30Owner
{
public:
	void updateTexture(UnicodeString textureName);

private:
	char m_padding00[0x3058];
	ShroudTexture m_texture;
	char m_padding306c[0x3074 - 0x3058 - 0x14];
	UnicodeString m_textureName;
	char m_padding3078[0x3084 - 0x3078];
	UnicodeString m_defaultTextureName;
};

void Gen006CBA30Owner::updateTexture(UnicodeString textureName)
{
	if (textureName.m_data == 0 ||
		*(unsigned short *)((char *)textureName.m_data + 4) == 0)
	{
		textureName.set(m_defaultTextureName);
	}

	m_textureName.set(textureName);

	const char *text;
	if (m_textureName.m_data)
		text = m_textureName.m_data + 8;
	else
		text = (const char *)0x0107388b;

	Gen006CBA30AssignTexture(
		m_texture.m_texture,
		BFMEGetWaterTrackTexture((char *)text, 0, 0));
	m_texture.getFilter()->m(1);
}
