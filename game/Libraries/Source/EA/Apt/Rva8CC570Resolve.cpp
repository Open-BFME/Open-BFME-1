// ?rva8CC570Resolve@@YAPAVRva8CCCE0Value@@PAX00@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Apt value resolver at retail 0x008CC570 (280 bytes).
// The lookup consumes a string view and replaces its output with a node.
// Retail 0x008C6320 scans the input block text at +8 and writes argument 4;
// only the resulting node is passed to BfmeNode1220::bfmeTest1220.

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

class BfmeNode1220
{
	public:
	int bfmeTest1220(int *value, int zero);
	void *m_vptr;
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
};

extern void d_008c6320();
typedef void (__cdecl *Rva8CC570PrepareLookup)(Rva8CCCE0Value *, void *,
	Rva8CC570Name *, void *&, Rva8CC570String *);

Rva8CCCE0Value *rva8CC570Resolve(void *fallback, void *scope, void *data)
{
	void *&lookupResult = data;
	Rva8CC570Name *inputName = (Rva8CC570Name *)data;
	Rva8CC570String key;
	if (inputName->m_string->m_length == 0)
		return (Rva8CCCE0Value *)fallback;

	((Rva8CC570PrepareLookup)d_008c6320)((Rva8CCCE0Value *)fallback, scope,
		inputName, lookupResult, &key);
	BfmeNode1220 *resolvedName = (BfmeNode1220 *)lookupResult;
	if (resolvedName != 0)
	{
		Rva8CCCE0Value *result = (Rva8CCCE0Value *)resolvedName->bfmeTest1220(
			(int *)&key, (int)scope);
		if (result != 0 && result->slot9())
			return result;
	}
	return 0;
}
