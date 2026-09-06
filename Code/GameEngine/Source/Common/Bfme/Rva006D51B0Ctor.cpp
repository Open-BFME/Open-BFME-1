// cl: /DNDEBUG /MD /EHsc
// Retail 0x006D51B0. The owner stores a ref-counted 0x3c-byte texture.

class Rva006D51B0TextureBase
{
public:
	Rva006D51B0TextureBase(unsigned, unsigned, unsigned, unsigned, unsigned, unsigned);
	virtual ~Rva006D51B0TextureBase();
	void Release_Ref(void);

	unsigned m_refBits;
	char m_body[0x34];
};

#pragma comment(linker, "/alternatename:??0Rva006D51B0TextureBase@@QAE@IIIIII@Z=?d_0090cf90@@YAXXZ")

class Rva006D51B0Texture : public Rva006D51B0TextureBase
{
public:
	Rva006D51B0Texture(unsigned width, unsigned height, unsigned mip,
		unsigned pool, unsigned renderTarget, unsigned reducible)
		: Rva006D51B0TextureBase(width, height, mip, pool, renderTarget, reducible)
	{
		*reinterpret_cast<unsigned *>(this) = 0x0111dfb0;
	}
};

class Rva006D51B0TextureRef
{
public:
	Rva006D51B0TextureRef(void) : m_ptr(0) {}
	~Rva006D51B0TextureRef(void)
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	Rva006D51B0TextureBase *m_ptr;
};

class Rva006D51B0
{
public:
	Rva006D51B0(unsigned, unsigned);

private:
	Rva006D51B0TextureRef m_texture;
};

Rva006D51B0::Rva006D51B0(unsigned a, unsigned b)
{
	Rva006D51B0TextureBase *texture = new Rva006D51B0Texture(0x800, a, b, 3, 1, 0);
	if (texture) {
		++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(texture) + 4);
		if (m_texture.m_ptr)
			m_texture.m_ptr->Release_Ref();
		m_texture.m_ptr = texture;
		texture->m_refBits |= 0x01000000;
	}
}
