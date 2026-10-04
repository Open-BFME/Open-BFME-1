// cl: /DNDEBUG /MD /EHsc
// Retail 0x0090DBC0 (150 bytes). The six-argument initializer allocates a
// ref-counted 0x3c-byte texture, replaces the current reference, and marks
// the new texture as owned by this holder. The constructor at 0x006D6050 and
// the near-twin constructor at 0x006D5280 establish the same layout.

class TextureBaseClass
{
public:
	void Release_Ref(void);
};

class Rva006D51B0TextureBase
{
public:
	Rva006D51B0TextureBase(unsigned, unsigned, unsigned, unsigned, unsigned, unsigned);
	virtual ~Rva006D51B0TextureBase();

	unsigned m_refBits;
	char m_body[0x34];
};

// The base body is Rva006D51B0Ctor.cpp's
// ??0Rva006D51B0TextureBase@@QAE@IIIIII@Z (retail 0x0090CF90); the local
// declaration below spells that name directly, so no alias is needed.

class Rva006D6050
{
public:
	void init(unsigned, unsigned, unsigned, unsigned, unsigned, unsigned);

private:
	Rva006D51B0TextureBase *m_texture;
};

void Rva006D6050::init(unsigned width, unsigned height, unsigned format,
	unsigned mipLevels, unsigned pool, unsigned renderTarget)
{
	Rva006D51B0TextureBase *texture = new Rva006D51B0TextureBase(
		width, height, format, mipLevels, pool, renderTarget);
	if (texture) {
		++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(texture) + 4);
		if (m_texture)
			reinterpret_cast<TextureBaseClass *>(m_texture)->Release_Ref();
		m_texture = texture;
		texture->m_refBits |= 0x01000000;
	}
}
