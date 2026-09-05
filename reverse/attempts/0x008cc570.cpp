// ?rva8CC570Resolve@@YAPAVRva8CCCE0Value@@PAX00@Z
// partial score=0.94 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Readable Apt value resolver at retail 0x008CC570 (280 bytes).
//
// Bytes +0x00 through +0x89 match retail exactly. Two things remain.
//
// The body is one byte short, all of it in the first inlined destructor. Retail
// loads the release table into ECX and then pushes the block:
//   mov ecx,[0x1337a30] / push eax / call [ecx+4]
// This source pushes the block first, which frees EAX and lets MSVC take the
// one-byte-shorter `a1` encoding:
//   push eax / mov eax,[0x1337a30] / call [eax+4]
// The second copy of the destructor is already the right length, because MSVC
// picks EDX there and retail picks ECX.
//
// From +0x89 the tail is a register rotation, retail ECX/EDX/EAX against this
// source's EAX/ECX/EDX, on the `name` reload, the key `lea`, and the vtable
// load before the accept call. Every branch displacement then differs by one
// because of the missing byte.
//
// Tried on 2026-09-05 without moving either, all measured against this file as
// the control: hoisting the release function pointer into a local inside the
// guard, hoisting the table pointer into a local, hoisting the pointer above
// the decrement, declaring the table volatile, declaring its elements volatile,
// declaring it const, declaring it as an array of function pointers, declaring
// it __stdcall, calling through *(table + 1), calling with the member instead
// of the local, folding the decrement into the if, casting the argument to
// void *, a second local for the argument, an early return instead of the
// guard, dropping the resolvedName and result locals, typing result as
// Rva8CCCE0Value *, splitting the two result tests into nested ifs, and an
// early return for the null name.

struct Rva8CC570StringBlock
{
	unsigned short m_refs;
	unsigned short m_length;
};

extern Rva8CC570StringBlock g_bfmeDefaultString1284;
extern void (__cdecl **Rva01337A30ReleaseTable)(void *);

class Rva8CC570String
{
public:
	Rva8CC570String()
	{
		m_block = &g_bfmeDefaultString1284;
		++g_bfmeDefaultString1284.m_refs;
	}
	~Rva8CC570String()
	{
		Rva8CC570StringBlock *block = m_block;
		--block->m_refs;
		if (block->m_refs == 0)
			Rva01337A30ReleaseTable[1](block);
	}

private:
	Rva8CC570StringBlock *m_block;
};

struct Rva8CC570Name
{
	Rva8CC570StringBlock *m_string;
};

class Rva8CCCE0Value
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual bool slot9();

	unsigned m_flags;
	char m_gap[0x18];
	Rva8CCCE0Value *m_indirect;
	bool acceptsLookup()
	{
		return slot9();
	}
};

void rva8C6320PrepareLookup(Rva8CCCE0Value *fallback, void *scope,
	Rva8CC570Name *name, Rva8CC570Name *&updatedName, Rva8CC570String *key);
void *__stdcall rva89C290Lookup(Rva8CC570String const &key,
	void *scope);

Rva8CCCE0Value *rva8CC570Resolve(void *fallback, void *scope, void *data)
{
	Rva8CC570Name *&name = *(Rva8CC570Name **)&data;
	Rva8CC570String key;
	if (name->m_string->m_length == 0)
		return (Rva8CCCE0Value *)fallback;

	rva8C6320PrepareLookup((Rva8CCCE0Value *)fallback, scope,
		name, name, &key);
	Rva8CC570Name const *resolvedName = name;
	void *result = 0;
	if (resolvedName != 0)
	{
		result = rva89C290Lookup(key, scope);
		if (result != 0 && ((Rva8CCCE0Value *)result)->acceptsLookup())
			return (Rva8CCCE0Value *)result;
	}
	return 0;
}
