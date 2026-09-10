// ?rva006EE3F0@W3DDisplay@@UAEEPAURva006EE3F0Descriptor@@HHHHHH@Z
// partial score=0.84 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Retail 0x006EE3F0 is the complete 240-byte body reached through slot 23
// (+0x5c) of the W3DDisplay vtable at 0x0111EDD0.  The constructor at
// 0x006EF850 stores that vtable, and its slot-23 incremental-link thunk at
// 0x00018B47 routes to this body.  The method remains address-derived: the
// vtable and constructor prove the W3DDisplay owner, but no source-level
// spelling for this slot is established.
//
// The three local ABI views below follow the retail call sites.  The existing
// FontLibrary::getFont alias is independently pinned to ILT 0x0000ABC3, whose
// target is the already-proven BFME font-library body.  The product constructor
// and destructor are TU-local address-derived views, routed explicitly to the
// existing ILTs 0x00026AFD -> 0x004354F0 and 0x0000D33C -> 0x00835780;
// their ECX/stack argument layouts are proven by the calls in this body and
// the target constructor's ret 0x1c boundary.  These routes do not add pins.

typedef int Int;
typedef float Real;
typedef unsigned char Bool;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class GameFont;

class AsciiString
{
private:
	void *m_data;
};

class FontLibrary
{
public:
	GameFont *getFont(AsciiString *name, Real pointSize, Bool bold);
};

extern FontLibrary *TheFontLibrary;

class Rva006EE3F0Product
{
public:
	Rva006EE3F0Product(GameFont *font, Int arg2, Int arg3, Int arg4,
		Int arg5, Int arg6, Int arg7);
	~Rva006EE3F0Product(void);

private:
	unsigned char m_unreconstructed[0x6c];
};

// ABI proof: the retail call loads ECX with the new 0x6c-byte object and
// pushes one GameFont pointer followed by six DWORD arguments; the target
// boundary returns with ret 0x1c.  The destructor call uses only ECX and is
// followed by the retail operator-delete call in the caller.
#pragma comment(linker, "/alternatename:??0Rva006EE3F0Product@@QAE@PAVGameFont@@HHHHHH@Z=?j_00026afd@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva006EE3F0Product@@QAE@XZ=?j_0000d33c@@YAXXZ")

struct Rva006EE3F0Entry
{
	unsigned char m_unreconstructed[0x20];
	unsigned char m_displayed;
};

struct Rva006EE3F0Descriptor
{
	unsigned char m_padding00[0x0c];
	AsciiString m_name;
	Int m_pointSize;
	unsigned char *m_begin;
	unsigned char *m_end;

	Int Count(void) const
	{
		return (Int)((m_end - m_begin) >> 2);
	}

	Rva006EE3F0Entry *operator[](Int index) const
	{
		return reinterpret_cast<Rva006EE3F0Entry **>(m_begin)[index];
	}
};

class W3DDisplay
{
public:
	virtual Bool rva006EE3F0(Rva006EE3F0Descriptor *descriptor, Int arg2, Int arg3, Int arg4,
		Int arg5, Int arg6, Int arg7);

private:
	unsigned char m_padding04[0x184 - 4];
	Rva006EE3F0Descriptor *m_descriptor;
	Rva006EE3F0Product *m_product;
};

// ?rva006EE3F0@W3DDisplay@@UAE_NPAXHHHHHH@Z
Bool W3DDisplay::rva006EE3F0(Rva006EE3F0Descriptor *descriptor, Int arg2, Int arg3, Int arg4,
	Int arg5, Int arg6, Int arg7)
{
	if (m_product != 0)
	{
		delete m_product;
		m_product = 0;
	}

	m_descriptor = descriptor;
	Int pointSize = descriptor->m_pointSize;
	GameFont *font = TheFontLibrary->getFont(&descriptor->m_name,
		(Real)pointSize, 0);
	m_product = new Rva006EE3F0Product(font, arg2, arg3, arg4, arg5, arg6,
		arg7);
	_ReadWriteBarrier();

	for (Int index = 0; index < m_descriptor->Count(); ++index)
	{
		Rva006EE3F0Entry *entry = (*m_descriptor)[index];
		entry->m_displayed = 0;
	}

	return 1;
}
