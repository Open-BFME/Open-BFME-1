// ?rva8CC570Resolve@@YAPAVRva8CCCE0Value@@PAX00@Z
// partial score=0.94 date=2026-09-03
// ?rva8CC570Resolve@@YAPAVRva8CCCE0Value@@PAX00@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Readable Apt value resolver at retail 0x008CC570 (280 bytes).

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
Rva8CCCE0Value *__stdcall rva89C290Lookup(Rva8CC570String const &key,
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
	Rva8CCCE0Value *result = 0;
	if (resolvedName != 0)
	{
		result = rva89C290Lookup(key, scope);
		if (result != 0 && result->acceptsLookup())
			return result;
	}
	return 0;
}
