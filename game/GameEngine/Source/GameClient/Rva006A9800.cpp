// cl: /DNDEBUG /MD
// Retail 0x006A9800, 216 bytes, __thiscall (no explicit ret imm -- ends in a
// tail jmp through a function-pointer global, consistent with this being a
// destructor/cleanup method whose last action forwards to a base handler).
// Walks the +0xb44/+0xb48 (base pointer/count) array of 0x40-byte elements
// twice: once calling a cached global callback (+0x13596C0) on each
// non-null element+4 pointer, then clearing element+0, testing element+0xc
// and calling the pinned closeProvider thunk on the element's address when
// set. Releases a +0xb4c handle through another global callback (+0x1359614)
// when it is not -1, clears three "TED" sub-owners, clears +0x618, calls an
// opaque no-arg cleanup through +0x13595EC, then tail-calls +0x13596A8.
//
// No named caller and no vtable slot prove a real class or method name, so
// this keeps the address token.

typedef int Int;

typedef void (__stdcall *Rva006A9800Stdcall1)(void *arg);
typedef void (__stdcall *Rva006A9800Stdcall2)(Int arg);

extern Rva006A9800Stdcall1 g_Rva13596C0;
extern Rva006A9800Stdcall2 g_Rva1359614;

typedef void (__stdcall *Rva006A9800FastFn)();
extern Rva006A9800FastFn g_Rva13595EC;
extern Rva006A9800FastFn g_Rva13596A8;

class BfmeThingTED
{
public:
	void bfmeOneTED(Int arg);
	void bfmeTwoTED();
	void bfmeThreeTED();
};

class Rva0069AB70Owner
{
public:
	void closeProvider();
};

class Rva006A9800Elem
{
public:
	void clearFlag0() { *(unsigned char *)this = 0; }
	void *ptrAt4() const { return *(void **)((char *)this + 4); }
	unsigned char flagAtC() const { return *(unsigned char *)((char *)this + 0xc); }
};

class Rva006A9800This
{
public:
	void rva006A9800();

	Int countAtB48() const { return *(Int *)((char *)this + 0xb48); }
	char *arrayBaseAtB44() const { return *(char **)((char *)this + 0xb44); }
	Int handleAtB4C() const { return *(Int *)((char *)this + 0xb4c); }
	void clearHandleAtB4C() { *(Int *)((char *)this + 0xb4c) = -1; }
	void clearField618() { *(Int *)((char *)this + 0x618) = 0; }

	Rva006A9800Elem *elemAt(Int i) const
	{
		return (Rva006A9800Elem *)(arrayBaseAtB44() + i * 0x40);
	}

	// Retail calls the ILT thunk at 0x0003B741 (-> retail 0x006A5080, still
	// an unnamed dump) as this->rvaElemClose(elem); pinned in symbols.csv
	// rather than inventing a semantic name for an unmatched body.
	void rvaElemClose(Rva006A9800Elem *elem);
};

void Rva006A9800This::rva006A9800()
{
	Int i = 0;
	if (countAtB48() > 0)
	{
		Rva006A9800Stdcall1 cb = g_Rva13596C0;
		do
		{
			void *p = elemAt(i)->ptrAt4();
			if (p)
				cb(p);
			++i;
		} while (i < countAtB48());
	}

	Int handle = handleAtB4C();
	if (handle != -1)
	{
		g_Rva1359614(handle);
		clearHandleAtB4C();
	}

	i = 0;
	if (countAtB48() > 0)
	{
		do
		{
			elemAt(i)->clearFlag0();
			if (elemAt(i)->flagAtC())
				rvaElemClose(elemAt(i));
			++i;
		} while (i < countAtB48());
	}

	((BfmeThingTED *)this)->bfmeOneTED(7);
	((BfmeThingTED *)this)->bfmeTwoTED();
	((BfmeThingTED *)this)->bfmeThreeTED();
	clearField618();
	((Rva0069AB70Owner *)this)->closeProvider();
	g_Rva13595EC();
	g_Rva13596A8();
}
