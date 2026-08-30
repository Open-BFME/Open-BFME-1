extern void *(*WideAllocPtr)(unsigned int bytes);
void Gen00897300(void *block);

class BfmeNestedBE
{
public:
	BfmeNestedBE(int kind, unsigned int marker, int value);

	void *operator new(unsigned int bytes)
	{
		char *raw = (char *)WideAllocPtr(bytes + 8);
		char *block = raw + 8;
		Gen00897300(block);
		return block;
	}

	void operator delete(void *block);

	void *m_vtable;
	unsigned int m_flags;
	int m_bfme08;
	char m_padding0c[0x54 - 0x0c];
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
