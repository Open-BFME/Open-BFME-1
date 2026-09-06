// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: near-twin of ??0Rva006D51B0 (0x006D51B0, Rva006D51B0Ctor.cpp); same
// ref-counted 0x3c-byte texture owner, but width is a caller-supplied third
// parameter here instead of the twin's constant 0x800.

class Rva006D5280TextureBase
{
public:
	Rva006D5280TextureBase(unsigned, unsigned, unsigned, unsigned, unsigned, unsigned);
	virtual ~Rva006D5280TextureBase();
	void Release_Ref(void);

	unsigned m_refBits;
	char m_body[0x34];
};

#pragma comment(linker, "/alternatename:??0Rva006D5280TextureBase@@QAE@IIIIII@Z=?d_0090cf90@@YAXXZ")

class Rva006D5280Texture : public Rva006D5280TextureBase
{
public:
	Rva006D5280Texture(unsigned width, unsigned height, unsigned mip,
		unsigned pool, unsigned renderTarget, unsigned reducible)
		: Rva006D5280TextureBase(width, height, mip, pool, renderTarget, reducible)
	{
		*reinterpret_cast<unsigned *>(this) = 0x0111dfb0;
	}
};

class Rva006D5280TextureRef
{
public:
	Rva006D5280TextureRef(void) : m_ptr(0) {}
	~Rva006D5280TextureRef(void)
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	Rva006D5280TextureBase *m_ptr;
};

class Rva006D5280
{
public:
	Rva006D5280(unsigned, unsigned, unsigned);

private:
	Rva006D5280TextureRef m_texture;
};

// ?d_006d5280@@YAXXZ
Rva006D5280::Rva006D5280(unsigned a, unsigned b, unsigned c)
{
	Rva006D5280TextureBase *texture = new Rva006D5280Texture(b, a, c, 3, 1, 0);
	if (texture) {
		++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(texture) + 4);
		if (m_texture.m_ptr)
			m_texture.m_ptr->Release_Ref();
		m_texture.m_ptr = texture;
		texture->m_refBits |= 0x01000000;
	}
}
