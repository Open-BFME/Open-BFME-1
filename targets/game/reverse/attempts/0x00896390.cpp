// ?release@BfmeTracker4310@@QAEXVBfmeRefHolder@@@Z
// partial score=0.715 date=2026-11-01
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// (method name "release" kept from the earlier bank for the name gate; the body adds unless present)
// BfmeTracker4310::rva00896390, retail 0x00896390 (214 bytes, ret 4): add a
// counted Apt object to the tracker's handle vector at +4 unless the same
// object is already there; the by-value handle is released on both paths.
// Its only caller is bfmeRva00896470 (Rva00896470RefHolderSubmit.cpp) on the
// tracker singleton. The Open BFME 2 donor AptLinker::rva006D1450 in
// Code/GameEngine/Source/Common/Bfme5ThirtyFour.cpp (45afcff3) is the same
// operation (its caller Rva006D1520 is the donor of bfmeRva00896470); the
// append is Gen_00896320::append (Gen00896320Append.cpp), inlined here.

extern void (__cdecl *TheBfmeFree)(void *p, unsigned int bytes);	// data_rows 0x01337830

class BfmeDropObjectA
{
public:
	~BfmeDropObjectA(void);

	void operator delete(void *p, unsigned int bytes) { TheBfmeFree(p, bytes); }

private:
	char m_bfmePad[0x18];
};

class BfmeRefHolder
{
public:
	BfmeRefHolder(const BfmeRefHolder &other) : m_obj(other.m_obj)
	{
		if (m_obj) ++*(int *)m_obj;
	}

	~BfmeRefHolder()
	{
		BfmeDropObjectA *r = m_obj;
		if (r && --*(int *)r == 0)
			delete m_obj;
	}

	BfmeDropObjectA *m_obj;
};

extern "C" void __cdecl __identifier("?d_008961e0@@YAXXZ")();

class Gen_00896320
{
public:
	void append(void **source)
	{
		BfmeDropObjectA **end = &m_begin[m_count];
		BfmeDropObjectA **next = (BfmeDropObjectA **)source + 1;
		BfmeDropObjectA **begin = (BfmeDropObjectA **)source;
		helper(&begin, &next, &end);
	}
	void helper(void *a0, void *a1, void *a2)
	{
		// retail 0x008961E0 is still the gen-dump row ?d_008961e0@@YAXXZ
		union { void (__cdecl *symbol)(); void (Gen_00896320::*member)(void *, void *, void *); } c;
		c.symbol = &__identifier("?d_008961e0@@YAXXZ");
		(this->*c.member)(a0, a1, a2);
	}

	bool contains(BfmeDropObjectA *value)
	{
		BfmeDropObjectA **entry = m_begin;
		if (entry != entry + m_count)
		{
			do
			{
				if (*entry == value)
					return true;
				++entry;
			}
			while (entry != m_begin + m_count);
		}
		return false;
	}
	unsigned m_count;
	int m_capacity;
	BfmeDropObjectA **volatile m_begin;
};

class BfmeTracker4310
{
public:
	void release(BfmeRefHolder object);

private:
	void *m_chain;						// +0x00
	Gen_00896320 m_entries;					// +0x04
};

// ?release@BfmeTracker4310@@QAEXVBfmeRefHolder@@@Z
void BfmeTracker4310::release(BfmeRefHolder object)
{
	if (m_entries.contains(object.m_obj))
		return;
	m_entries.append((void **)&object);
}




