// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc 
// Retail 0x00896470, 142 bytes: submits a by-value ref-counted handle to the
// tracker singleton at 0x013377F8, then - when the flag at 0x013377DC is set -
// hands the object's string at +4 to the builder reached through the receiver
// at 0x013377F0.
// The tracker callee 0x00896390 is defined below. The builder callee
// 0x00895790 is still a machine dump, so it keeps the dump name the ledger
// gives its body and is bound to the ABI view this call site proves through
// the function-pointer/member-pointer union idiom Rva00896060Owner.cpp uses;
// no new symbols.csv pin is invented here.
//
// 0x00896390 shape notes (BFME 1 retail facts): the search re-reads the vector
// base at the back-edge and computes the guard's end separately from the
// loop's, so begin()/end() go through a two-pointer range temporary and the
// loop sits directly in the body; both sides of the compare read the handle
// through get(), which is what puts the searched pointer in ESI and count*4
// in EDI; the release reads the new count through a helper (dec/cmp on
// memory). docs/shape_levers.md has the measured table. The range temporary
// follows the Open-BFME-2 donor lead recorded for 0x00892FD0.
// Identity stays address-derived: no owning class name survives, and only the
// 0x00896540 / 0x008965B0 dump callers reach this body.

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
	BfmeRefHolder(BfmeDropObjectA *obj) : m_obj(obj)
	{
		if (obj)
			++*(int *)obj;
	}

	BfmeRefHolder(const BfmeRefHolder &other) : m_obj(other.m_obj)
	{
		if (m_obj) ++*(int *)m_obj;
	}

	~BfmeRefHolder()
	{
		if (m_obj && decrement((unsigned *)m_obj) == 0)
			delete m_obj;
	}

	BfmeDropObjectA *get() const { return m_obj; }

private:
	static unsigned decrement(unsigned *count) { return --*count; }

public:
	BfmeDropObjectA *m_obj;
};

extern "C" void __cdecl __identifier("?d_008961e0@@YAXXZ")();

// The handle vector at tracker+4: count +0, capacity +4, data +8 (layout from
// the matched Gen_00896320::append / rva00896100 in Gen00896320Append.cpp).
class Gen_00896320
{
public:
	struct Range
	{
		BfmeRefHolder *m_first;
		BfmeRefHolder *m_last;
		Range(BfmeRefHolder *first, BfmeRefHolder *last) : m_first(first), m_last(last) {}
		BfmeRefHolder *begin() const { return m_first; }
		BfmeRefHolder *end() const { return m_last; }
	};
	Range range() { return Range(m_begin, m_begin + m_count); }
	BfmeRefHolder *begin() { return range().begin(); }
	BfmeRefHolder *end() { return range().end(); }

	// retail 0x008961E0 (still the gen-dump row ?d_008961e0@@YAXXZ): range
	// insert taking its three iterators by reference.
	void insert(const BfmeRefHolder *const &first, const BfmeRefHolder *const &last, BfmeRefHolder *const &position)
	{
		union { void (__cdecl *symbol)(); void (Gen_00896320::*member)(void *, void *, void *); } c;
		c.symbol = &__identifier("?d_008961e0@@YAXXZ");
		(this->*c.member)((void *)&first, (void *)&last, (void *)&position);
	}
	void push_back(const BfmeRefHolder &value) { insert(&value, &value + 1, end()); }

private:
	unsigned m_count;
	int m_capacity;
	BfmeRefHolder *m_begin;
};

class BfmeTracker4310
{
public:
	void rva00896390(BfmeRefHolder object);

private:
	void *m_00;
	Gen_00896320 m_04;
};

class BfmeStrVKI;

class Gen_uw_00893e70
{
};

extern BfmeTracker4310 *g_bfmeTracker4310;
extern int g_bfme1017I;
extern Gen_uw_00893e70 *g_rva013377F0;

extern void d_00895790();

typedef void (Gen_uw_00893e70::*Build893E70Call)(const BfmeStrVKI &, int, int, int);
__forceinline Build893E70Call Rva00895790Binding()
{
	union { void (*raw)(); Build893E70Call member; } fn;
	fn.raw = d_00895790;
	return fn.member;
}

// Retail 0x00896390, 214 bytes, ret 4: add the handle to the tracker's vector
// unless the same object is already in it. The by-value handle is released on
// both paths.
void BfmeTracker4310::rva00896390(BfmeRefHolder object)
{
	for (BfmeRefHolder *it = m_04.begin(); it != m_04.end(); ++it)
		if (it->get() == object.get())
			return;
	m_04.push_back(object);
}

// ?bfmeRva00896470@@YAXVBfmeRefHolder@@@Z
void __cdecl bfmeRva00896470(BfmeRefHolder obj)
{
	g_bfmeTracker4310->rva00896390(obj);

	if (g_bfme1017I)
	{
		const BfmeStrVKI *string = (const BfmeStrVKI *)((char *)obj.m_obj + 4);
		(g_rva013377F0->*Rva00895790Binding())(*string, 1, 3, 2);
	}
}
