// ?d_008be5a0@@YAXXZ
// partial score=0.92 date=2026-08-30
extern void *(*WideAllocPtr)(unsigned int bytes);
void Gen00897300(void *block);

class BfmeNestedBE
{
public:
	BfmeNestedBE(int kind, unsigned int marker, int value);
	virtual void bfmeLinked1284();

	void *operator new(unsigned int bytes)
	{
		char *raw = (char *)WideAllocPtr(bytes + 8);
		char *block = raw + 8;
		Gen00897300(block);
		return block;
	}

	void operator delete(void *block);

	unsigned int m_flags;
	int m_bfme08;
	char m_padding0c[0x50 - 0x0c];
	int m_bfme50;
	int m_bfme54;
	int m_bfme58;
	char m_padding5c[0x64 - 0x5c];
};

class BfmeThingBE
{
public:
	BfmeThingBE();

private:
	BfmeNestedBE *m_nested;
};

BfmeThingBE::BfmeThingBE()
{
	m_nested = new BfmeNestedBE(0x1b, 0xbaadf00d, 0);
	m_nested->m_flags &= ~0x8000;
	m_nested->m_flags = (m_nested->m_flags & 0xffffc07f) | 0x40;
	m_nested->m_bfme08 = -1;
	m_nested->m_bfme58 = 0;
	m_nested->m_bfme54 = 0;
}

class BfmeQuery1279
{
public:
	void bfmeQuery1279(void *value, int zero, void **other, void **result);
	BfmeNestedBE *bfmeCreate1284(void *value, int kind, int marker);
};

BfmeNestedBE *BfmeQuery1279::bfmeCreate1284(void *value, int kind, int marker)
{
	BfmeNestedBE *node = new BfmeNestedBE(kind, marker, 0);
	int originalMarker = marker;
	bfmeQuery1279(value, 0, (void **)&marker, (void **)&kind);
	BfmeNestedBE *anchor = (BfmeNestedBE *)marker;
	node->m_bfme50 = originalMarker;
	node->m_bfme08 = (int)value;
	node->m_bfme58 = anchor->m_bfme58;
	node->m_bfme54 = (int)anchor;
	node->bfmeLinked1284();
	if (node->m_bfme58)
		((BfmeNestedBE *)node->m_bfme58)->m_bfme54 = (int)node;
	((BfmeNestedBE *)node->m_bfme54)->m_bfme58 = (int)node;
	return node;
}
