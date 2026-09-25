// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Retail 0x006A5570, 109 bytes, __thiscall, no args.
// Sweeps the +0xB44 table of 0x40-byte elements (count at +0xB48) and hands
// each element whose byte +0 is clear and byte +0xC is set to the pinned
// ILT 0x0003B741 (-> retail 0x006A5080) when its +4 handle is null or
// bfmeStatusDXD(handle) != 4.  The same owner/element layout and the same
// callee are used by the landed 0x006A9800 body, so this shares its
// address-derived class names; 0x006A5080 re-tests the identical predicate.
// No caller, vtable slot or string proves a semantic name.

typedef int Int;
typedef bool Bool;

extern "C" __declspec(dllimport) Int __stdcall bfmeStatusDXD(void *handle);

class Rva006A9800Elem
{
public:
	unsigned char byte_0;
	unsigned char pad_1[3];
	void *ptr_4;
	unsigned char pad_8[4];
	unsigned char byte_C;
	unsigned char pad_D[0x33];
};

class Rva006A9800This
{
public:
	void vtableSlot(); // declared, never defined/called; not a vtable claim
	void rva006A5570();
	void rvaElemClose(Rva006A9800Elem *elem);

private:
	char pad_0[0xb44];
	Rva006A9800Elem *m_elemsB44;
	Int m_countB48;
};

void Rva006A9800This::rva006A5570()
{
	for (Int i = 0; i < m_countB48; ++i)
	{
		Rva006A9800Elem *e = &m_elemsB44[i];
		if (!e->byte_0 && e->byte_C)
		{
			Bool done = true;
			if (e->ptr_4)
				done = bfmeStatusDXD(e->ptr_4) != 4;
			if (done)
				rvaElemClose(&m_elemsB44[i]);
		}
	}
}
