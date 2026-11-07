// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
#include "../../../../Libraries/Source/WWVegas/WW3D2/texturefilter.h"
// The companion terrain texture slot at retail 0x006D0280 has the same
// refresh body as 0x006D0150, with a four-byte layout shift.

class TextureClass
{
public:
	void Release_Ref(void);
};

class ShroudFilter
{
};

class ShroudTexture
{
public:
	ShroudFilter *getFilter(void);

	TextureClass *m_texture;
	char m_padding04[0x10];
};


// Retail inlines this wrapper into StringBase<char> directly; declare just the
// StringBase<char> members it reaches (see build/whatif/wrapfix.py).
template <class T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;
public:
	void set(const StringBase<T> &other);
private:
	void releaseBuffer();
};
class AsciiString
{
public:
	int compare(const AsciiString &other) const;
	~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

	char *m_data;
};

class TextureBaseClass { public: void Release_Ref(); };

class BFMEWaterTrackTextureHandle
{
public:
	TextureClass *m_texture;

	~BFMEWaterTrackTextureHandle(void)
	{
		if (m_texture)
			((TextureBaseClass *)m_texture)->Release_Ref();
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
		((StringBase<char> *)&textureName)->set(*(const StringBase<char> *)&m_defaultTextureName);
	}

	AsciiString *name = &m_textureName;
	if (textureName.compare(*name) != 0)
	{
		((StringBase<char> *)name)->set(*(const StringBase<char> *)&textureName);

		const char *text;
		if (name->m_data)
			text = name->m_data + 8;
		else
			text = "";

		Gen006D0280AssignTexture(
			m_texture.m_texture,
			BFMEGetWaterTrackTexture((char *)text, 0, 0));
		reinterpret_cast<TextureFilterClass *>(m_texture.getFilter())->Set_Mip_Mapping(TextureFilterClass::FILTER_TYPE_FAST);
	}
}
