// cl: /DNDEBUG /MD /EHsc
// Retail 0x0090DBC0 (150 bytes). The six-argument initializer allocates a
// ref-counted 0x3c-byte texture, replaces the current reference, and marks
// the new texture as owned by this holder. The constructor at 0x006D6050 and
// the near-twin constructor at 0x006D5280 establish the same layout.

class Rva006D6050TextureBase
{
public:
	Rva006D6050TextureBase(unsigned, unsigned, unsigned, unsigned, unsigned, unsigned);
	virtual ~Rva006D6050TextureBase();
	void Release_Ref(void);

	unsigned m_refBits;
	char m_body[0x34];
};

#pragma comment(linker, "/alternatename:??0Rva006D6050TextureBase@@QAE@IIIIII@Z=?d_0090cf90@@YAXXZ")

class Rva006D6050
{
public:
	void init(unsigned, unsigned, unsigned, unsigned, unsigned, unsigned);

private:
	Rva006D6050TextureBase *m_texture;
};

void Rva006D6050::init(unsigned width, unsigned height, unsigned format,
	unsigned mipLevels, unsigned pool, unsigned renderTarget)
{
	Rva006D6050TextureBase *texture = new Rva006D6050TextureBase(
		width, height, format, mipLevels, pool, renderTarget);
	if (texture) {
		++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(texture) + 4);
		if (m_texture)
			m_texture->Release_Ref();
		m_texture = texture;
		texture->m_refBits |= 0x01000000;
	}
}
