// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

// Open-BFME: near-twin of ??0Rva006D5280 (0x006D5280, Rva006D5280Ctor.cpp);
// same ref-counted 0x3c-byte owner shape (default-init the holder to null,
// allocate+init the owned object, release the old one, install, addref),
// but the owned object here is a BfmeThingSJ-derived object (base ctor is
// the already-matched bfmeBaseSJ helper at 0x0090E3D0) instead of a
// TextureBase, the installed vtable is 0x010F5DD8, and two extra flag
// words (m_bfme30, m_bfme38) are forced to 1 after the vtable store.

#include "wwstring.h"

class GenBase009EB7D0
{
public:
	GenBase009EB7D0();
	virtual ~GenBase009EB7D0();
	virtual void handle();

	unsigned int m_flags;
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

class BfmeThingSJ : public GenBase009EB7D0
{
public:
	__declspec(noinline) void bfmeBaseSJ(int what);
	BfmeThingSJ(int what);
	virtual void handle();

	int m_bfme14;
	StringClass m_bfmeName;
	Gen_00920A20 m_bfmeData;
	int m_bfme30;
	int m_bfme34;
	int m_bfme38;
};

// Release_Ref is reused byte-for-byte across many unrelated ref-counted
// classes (matched ledger callee 0x009EB7A0); declare only the method we
// call, as R1GuardedReleaseHelpers.cpp does for the same address.
class TextureClass
{
public:
	void Release_Ref();
};

// Raw 0x3c-byte body: bfmeBaseSJ is called as a plain (non-constructing)
// member helper -- calling the real BfmeThingSJ(int) constructor instead
// would run GenBase009EB7D0's own ctor and install its vtable, which the
// body does not do (the vtable store below is the only vtable write).
class Rva0044F4D0Texture
{
public:
	Rva0044F4D0Texture(int what);

	char m_body[0x3c];
};

Rva0044F4D0Texture::Rva0044F4D0Texture(int what)
{
	BfmeThingSJ *self = reinterpret_cast<BfmeThingSJ *>(this);
	self->bfmeBaseSJ(what);
	*reinterpret_cast<unsigned *>(this) = 0x010F5DD8;
	self->m_bfme30 = 1;
	self->m_bfme38 = 1;
}

class Rva0044F4D0Holder
{
public:
	Rva0044F4D0Holder(void) : m_ptr(0) {}
	~Rva0044F4D0Holder(void)
	{
		if (m_ptr)
			reinterpret_cast<TextureClass *>(m_ptr)->Release_Ref();
	}

	Rva0044F4D0Texture *m_ptr;
};

class Rva0044F4D0
{
public:
	Rva0044F4D0(int what);

private:
	Rva0044F4D0Holder m_holder;
};

// ??0Rva0044F4D0@@QAE@H@Z
Rva0044F4D0::Rva0044F4D0(int what)
{
	Rva0044F4D0Texture *texture = new Rva0044F4D0Texture(what);
	if (texture) {
		++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(texture) + 4);
		if (m_holder.m_ptr)
			reinterpret_cast<TextureClass *>(m_holder.m_ptr)->Release_Ref();
		m_holder.m_ptr = texture;
		*reinterpret_cast<unsigned *>(reinterpret_cast<char *>(texture) + 4) |= 0x01000000;
	}
}
