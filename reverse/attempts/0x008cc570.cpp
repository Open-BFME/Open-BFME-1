// ?rva8CC570LookupValue@@YAPAVRva8CC570Value@@PAV1@PAXPAURva8CC570Name@@@Z
// partial score=0.94 date=2026-09-02
// ?rva8CC570LookupValue@@YAPAVRva8CC570Value@@PAV1@PAXPAURva8CC570Name@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable Apt named-value lookup, retail 0x008CC570 (280 bytes).

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

class Rva8CC570Value
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
	bool acceptsLookup()
	{
		return slot9();
	}
};

void rva8C6320PrepareLookup(Rva8CC570Value *fallback, void *scope,
	Rva8CC570Name *name, Rva8CC570Name *&updatedName, Rva8CC570String *key);
Rva8CC570Value *__stdcall rva89C290Lookup(Rva8CC570String &key, void *scope);

Rva8CC570Value *rva8CC570LookupValue(Rva8CC570Value *fallback, void *scope,
	Rva8CC570Name *name)
{
	Rva8CC570Value *result;
	Rva8CC570String key;
	if (name->m_string->m_length == 0)
		return fallback;

	rva8C6320PrepareLookup(fallback, scope, name, name, &key);
	Rva8CC570Name *resolvedName = name;
	if (resolvedName != 0)
	{
		result = rva89C290Lookup(key, scope);
		if (result != 0 && result->acceptsLookup())
			return result;
	}
	return 0;
}
