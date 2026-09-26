// cl: /DNDEBUG /MD /EHsc
//
// The three-argument constructor at retail 0x006DB100, a complete carved
// extent.
//
// WHAT THE BYTES SHOW.  `this` in ecx, `ret 0xC`, `this` returned in eax: a
// __thiscall constructor taking three dwords, of which only the first (an
// element count) and the third (an alignment) are read.  It stores 1 at +4
// BEFORE the vftable store at +0, which a derived class's own member never
// does -- that is an inlined base constructor running ahead of the derived
// vptr -- so the class has a four-byte non-polymorphic base at +4 whose
// constructor sets that flag.
//
// The allocation is `operator new[]` in both arms.  With a zero alignment it
// asks for count*4 and the aligned pointer IS the raw one; otherwise it asks
// for alignment + count*4 and rounds the raw pointer up with
// `(raw + alignment - 1) & ~(alignment - 1)`, re-reading the alignment from
// the member rather than the argument.  The raw pointer is stored at +8 on
// both paths, the usable one at +0xC.
//
// THE fs:[0] FRAME IS THE BASE'S DESTRUCTOR.  Without a user-declared
// destructor on that base the same body compiles to 94 bytes with no unwind
// registration at all; declaring one restores the frame, the saved `this` slot
// and both unwind-state stores, and makes all 139 bytes exact.
//
// IDENTITY IS NOT RECOVERED.  Every name here is derived from the address.

void *__cdecl operator new[](unsigned int);
void __cdecl operator delete[](void *);

class Rva006DB100Base
{
public:
	Rva006DB100Base()
	{
		m_flag = 1;
	}

	~Rva006DB100Base();

	int m_flag;
};

class Rva006DB100Buffer : public Rva006DB100Base
{
public:
	Rva006DB100Buffer(int count, int spare, unsigned int alignment);
	virtual void s0();

	void *m_raw;
	void *m_aligned;
	int m_count;
	unsigned int m_alignment;
};

// ??0Rva006DB100Buffer@@QAE@HHI@Z
Rva006DB100Buffer::Rva006DB100Buffer(int count, int spare, unsigned int alignment)
{
	m_count = count;
	m_alignment = alignment;

	char *raw;
	if (alignment == 0)
	{
		raw = new char[count * 4];
		m_aligned = raw;
	}
	else
	{
		raw = new char[alignment + count * 4];
		m_aligned = (void *)(((unsigned int)raw + m_alignment - 1) & ~(m_alignment - 1));
	}

	m_raw = raw;
}
