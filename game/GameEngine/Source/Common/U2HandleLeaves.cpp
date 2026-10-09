// Three unrelated-looking leaves that share one habit: each one turns a test
// into 0 / -1 or 0 / 1 with the carry flag rather than a branch.
//
// 0x00831F50 (16 bytes) -- a cdecl free function that calls the SECOND virtual
// (slot 4) on its only argument and returns that argument.  `this` is set from
// the argument, the vptr is read at offset 0, and eax is reloaded from the
// argument afterwards, so the return value is the object and not whatever the
// virtual returned.
//
// 0x008499F0 used to sit here. It is slot 4 of the stdio_streambuf_base vtable
// at VA 0x0112FBDC, so it is sync, and the import it calls is MSVCR71 fflush.
// It now comes from
// game/Libraries/Source/WWVegas/WWLib/stlport_stdio_streambuf_sync.cpp.
//
// 0x00845250 (48 bytes) -- a cdecl comparison of two objects: each is given a
// chance to refresh itself (a member call guarded by its own +0 word being
// non-null), and then the two bytes at +6 are compared.  `sub / neg / sbb /
// inc` is `a == b` as a 0 / 1 int, which is why the result is an int and not a
// bool.  The refresh member is one function called on both objects, so both
// arguments have the same type.
//
// Identity is not recovered; every name is derived from an address.

struct Rva00831F50Object
{
	virtual void v0();
	virtual void release();
};

Rva00831F50Object *Rva00831F50Release(Rva00831F50Object *p)
{
	p->release();
	return p;
}

// The two refresh calls reach the matched wide iterator helper at
// 0x00833D90. Its private const member must remain an out-of-line call.
struct Rva00845250Node;
int Rva00845250Equal(Rva00845250Node *a, Rva00845250Node *b);
namespace _STL
{
template <class C> class char_traits;
template <class C, class Traits> class istreambuf_iterator
{
	void _M_getc() const;
	friend int ::Rva00845250Equal(Rva00845250Node *, Rva00845250Node *);
};
}

struct Rva00845250Node
{
	void *m_source;
	char m_pad[2];
	char m_kind;

};

int Rva00845250Equal(Rva00845250Node *a, Rva00845250Node *b)
{
	if (a->m_source != 0)
		reinterpret_cast<const _STL::istreambuf_iterator<unsigned short, _STL::char_traits<unsigned short> > *>(a)->_M_getc();
	if (b->m_source != 0)
		reinterpret_cast<const _STL::istreambuf_iterator<unsigned short, _STL::char_traits<unsigned short> > *>(b)->_M_getc();
	return a->m_kind == b->m_kind;
}

// 0x008442E0 used to sit here. It is slot 1 of the collate<char> vtable at VA
// 0x0112EAD4, so it is do_compare, and the callee it forwards to is the narrow
// __lexicographical_compare_3way at 0x00844230. It now comes from
// game/Libraries/Source/WWVegas/WWLib/stlport_collate_narrow_compare.cpp.

// 0x00809500 (27 bytes) -- a lookup whose result is used only if it is
// non-null.  The lookup takes ONE argument and cleans it itself, so it is
// __stdcall and not the cdecl a plain free function would be; the second call
// takes the same argument but puts the lookup's result in ecx, so that one is a
// __thiscall member on the object just found.  The wrapper's own argument is
// passed on unchanged to both.
struct Rva00809500Entry
{
	char m_body[4];
};

struct Rva00809500Sink
{
	void accept(Rva00809500Entry *entry);
};

// 0x00809010 is a thiscall member of Rva00809010Finder (its matched body
// dereferences this+0x18), and the ledger's five callers prove that name.
// Retail enters the call with ecx untouched, so `this` is already in place.
class Rva00809010Finder
{
public:
	Rva00809500Sink *find(Rva00809500Entry *entry);
};

struct Rva00809500Owner
{
	void give(Rva00809500Entry *entry);
};

void Rva00809500Owner::give(Rva00809500Entry *entry)
{
	Rva00809500Sink *sink = reinterpret_cast<Rva00809010Finder *>(this)->find(entry);
	if (sink != 0)
		sink->accept(entry);
}
