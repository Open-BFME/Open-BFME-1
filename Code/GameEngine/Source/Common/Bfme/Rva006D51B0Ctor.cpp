// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// Retail 0x006D51B0. The owner stores a ref-counted 0x3c-byte texture, whose
// shared base constructor is retail 0x0090CF90 (250B). That base is the same
// GenBase009EB7D0-derived shape Code/GameEngine/Source/Common/
// BfmeThreeHundredThirtyEight.cpp already carries for BfmeThingSJ (m_bfme14,
// StringClass m_bfmeName, Gen_00920A20 m_bfmeData, m_bfme30/34/38): here the
// four trailing fields are default (0, StringClass(""), Gen_00920A20(0), 0,
// mip, 0) and the body additionally heap-allocates a Rva0090C2F0Inner (the
// 0x48-byte object Code/GameEngine/Source/Common/Rva0090C2F0Go.cpp's go()
// method already operates on) and calls go(width,height,mip,pool,
// renderTarget,reducible,0) on it before returning. m_refBits is
// GenBase009EB7D0's own m_flags dword (offset+4) reused as a [refcount:16]
// field by every caller in this family.

#include "wwstring.h"

class GenBase009EB7D0
{
public:
	GenBase009EB7D0();
	virtual ~GenBase009EB7D0();
	virtual void handle();

	unsigned int m_refBits;
	unsigned int m_zero08;
	unsigned int m_zero0c;
	unsigned int m_zero10;
};

class Gen_00920A20
{
public:
	Gen_00920A20(int mode);

	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
	int m_bfmeD;
	int m_bfmeE;
};

// The heap-allocated inner object retail's texture-base ctor constructs
// in-place (operator new(0x48) + raw field stores, inlined here rather than
// called out of line): same layout as Rva0090C2F0Go.cpp's Rva0090C2F0Inner,
// with a constructor added for this TU's own inline use.
class Rva0090C2F0Inner
{
public:
	Rva0090C2F0Inner()
	{
		m_04 = 0;
		m_08 = 0;
		m_0C = 0;
		m_10 = 0;
		m_14 = 0;
		m_18 = 0;
		m_1C = 0;
		m_20 = 0;
		m_24 = 1;
		m_28 = 1;
		m_2C = 1;
		m_30 = 1;
		m_34 = 0;
		m_38 = 0;
		m_3C = 0;
		m_40 = 2;
		m_44 = 0;
	}

	virtual void handle();
	void go(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7);

private:
	char m_04;
	void *m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	int m_3C;
	int m_40;
	int m_44;
};

class Rva006D51B0TextureBase : public GenBase009EB7D0
{
public:
	Rva006D51B0TextureBase(unsigned, unsigned, unsigned, unsigned, unsigned, unsigned);
	virtual ~Rva006D51B0TextureBase();
	void Release_Ref(void);

	Rva0090C2F0Inner *m_bfme14;
	StringClass m_bfmeName;
	Gen_00920A20 m_bfmeData;
	int m_bfme30;
	unsigned m_bfme34;
	int m_bfme38;
};

// ??0Rva006D51B0TextureBase@@QAE@IIIIII@Z
Rva006D51B0TextureBase::Rva006D51B0TextureBase(unsigned width, unsigned height,
	unsigned mip, unsigned pool, unsigned renderTarget, unsigned reducible)
	: GenBase009EB7D0(),
	  m_bfme14(0),
	  m_bfmeName(0, false),
	  m_bfmeData(0),
	  m_bfme30(0),
	  m_bfme34(mip),
	  m_bfme38(0)
{
	m_bfme14 = new Rva0090C2F0Inner();
	m_bfme14->go(width, height, mip, pool, renderTarget, reducible, 0);
}

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
