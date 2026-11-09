// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: near-twin of ??0Rva006D51B0 (0x006D51B0, Rva006D51B0Ctor.cpp); same
// ref-counted 0x3c-byte texture owner, but width is a caller-supplied third
// parameter here instead of the twin's constant 0x800.

// The shared 0x3c-byte base body is the real retail constructor owned by
// Rva006D51B0Ctor.cpp (??0Rva006D51B0TextureBase@@QAE@IIIIII@Z, retail
// 0x0090CF90); this near-twin's derived texture calls that name directly, so
// this TU only declares it and never defines a copy of its own.
class Rva006D51B0TextureBase
{
public:
	Rva006D51B0TextureBase(unsigned, unsigned, unsigned, unsigned, unsigned, unsigned);
	virtual ~Rva006D51B0TextureBase();

	unsigned m_refBits;
	char m_body[0x34];
};

// Retail releases through 0x009EB7A0, which TextureBaseReleaseRefThunk.cpp
// owns as TextureBaseClass::Release_Ref; the ref-counted object is only ever
// seen here through that leaf.
class TextureBaseClass
{
public:
	void Release_Ref(void);
};

extern "C" char __identifier("?bfmeGo1035G@BfmeG1035@@QAEPADXZ");
extern "C" char __identifier("?bfmeMakeGR@BfmeHostGR@@QAEXXZ");
extern "C" char __identifier("?rva0090c570@Rva0090C570Outer@@QAEXXZ");
extern "C" char __identifier("?bfmeGo937B@BfmeThing937B@@QAEXXZ");
void j_000213d7();
void Rva0090C5F0Noop();
void Rva0090C600Noop();
extern "C" char __identifier("?bfmeGo911E@BfmeThing911E@@QAEXXZ");
extern "C" char __identifier("?bfmeAdvanceStages@BfmeFlagStageSequence@@QAEIXZ");
void j_00045c37();
extern "C" char __identifier("?ready@Rva009EB940Receiver@@QAE_NXZ");
extern "C" char __identifier("?method@Rva009EB8A0@@QAEXXZ");
extern "C" char __identifier("?bfmeGo1024E@BfmeE1024@@QAEXXZ");
void j_0000d413();
extern "C" char __identifier("?bytes@Rva0090C5C0TextureBytes@@QBEIXZ");
void j_0001d408();
void j_00009a9d();

// Retail VA 0x0111DFB0: seventeen function slots (vtable_lookup.py), the vftable
// installed by the constructors at 0x006D51B0 and 0x006D5280 and by 0x006D4620.
void *g_BfmeVftZQ[17] = {
	reinterpret_cast<void *>(&__identifier("?bfmeGo1035G@BfmeG1035@@QAEPADXZ")),
	reinterpret_cast<void *>(&__identifier("?bfmeMakeGR@BfmeHostGR@@QAEXXZ")),
	reinterpret_cast<void *>(&__identifier("?rva0090c570@Rva0090C570Outer@@QAEXXZ")),
	reinterpret_cast<void *>(&__identifier("?bfmeGo937B@BfmeThing937B@@QAEXXZ")),
	reinterpret_cast<void *>(&j_000213d7),
	reinterpret_cast<void *>(&Rva0090C5F0Noop),
	reinterpret_cast<void *>(&Rva0090C600Noop),
	reinterpret_cast<void *>(&__identifier("?bfmeGo911E@BfmeThing911E@@QAEXXZ")),
	reinterpret_cast<void *>(&__identifier("?bfmeAdvanceStages@BfmeFlagStageSequence@@QAEIXZ")),
	reinterpret_cast<void *>(&j_00045c37),
	reinterpret_cast<void *>(&__identifier("?ready@Rva009EB940Receiver@@QAE_NXZ")),
	reinterpret_cast<void *>(&__identifier("?method@Rva009EB8A0@@QAEXXZ")),
	reinterpret_cast<void *>(&__identifier("?bfmeGo1024E@BfmeE1024@@QAEXXZ")),
	reinterpret_cast<void *>(&j_0000d413),
	reinterpret_cast<void *>(&__identifier("?bytes@Rva0090C5C0TextureBytes@@QBEIXZ")),
	reinterpret_cast<void *>(&j_0001d408),
	reinterpret_cast<void *>(&j_00009a9d),
};

class Rva006D5280Texture : public Rva006D51B0TextureBase
{
public:
	Rva006D5280Texture(unsigned width, unsigned height, unsigned mip,
		unsigned pool, unsigned renderTarget, unsigned reducible)
		: Rva006D51B0TextureBase(width, height, mip, pool, renderTarget, reducible)
	{
		*reinterpret_cast<unsigned *>(this) = reinterpret_cast<unsigned>(g_BfmeVftZQ);
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

	TextureBaseClass *m_ptr;
};

class Rva006D5280
{
public:
	Rva006D5280(unsigned, unsigned, unsigned);

private:
	Rva006D5280TextureRef m_texture;
};

// ??0Rva006D5280@@QAE@III@Z
Rva006D5280::Rva006D5280(unsigned a, unsigned b, unsigned c)
{
	Rva006D51B0TextureBase *texture = new Rva006D5280Texture(b, a, c, 3, 1, 0);
	if (texture) {
		++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(texture) + 4);
		if (m_texture.m_ptr)
			m_texture.m_ptr->Release_Ref();
		m_texture.m_ptr = reinterpret_cast<TextureBaseClass *>(texture);
		texture->m_refBits |= 0x01000000;
	}
}
