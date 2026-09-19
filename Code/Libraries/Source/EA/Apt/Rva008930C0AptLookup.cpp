// cl: /EHsc
// Address-derived Apt lookup and creation helper at retail RVA 0x008930C0.

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

	__forceinline void setLookupFlags()
	{
		m_flags.bits = (m_flags.bits & 0xffffc07f) | 0x40;
	}

	struct Flags
	{
		unsigned int bits;
	} m_flags;
	int m_bfme08;
	char m_padding0c[0x54 - 0x0c];
	BfmeNestedBE *m_bfme54;
	BfmeNestedBE *m_bfme58;
	char m_padding5c[0x64 - 0x5c];
};

class BfmeQuery1279
{
public:
	BfmeNestedBE *m_root;
	void bfmeInsert1279(int value, BfmeNestedBE *node);
};

extern void d_008bd230(void);

struct Rva008930C0Holder
{
	char m_prefix[0x122c];
	BfmeQuery1279 *m_query;
};

extern Rva008930C0Holder *g_bfmeHolderBU;

BfmeNestedBE *Rva008930C0AptLookup(int value)
{
	if (g_bfmeHolderBU)
	{
		if (g_bfmeHolderBU->m_query)
		{
			BfmeNestedBE *node = g_bfmeHolderBU->m_query->m_root;
			if (node)
			{
				do
				{
					if (node->m_bfme08 == value)
						return node;
					node = node->m_bfme58;
				} while (node);
			}

			BfmeNestedBE *newNode = new BfmeNestedBE(0x13, 0, 0);
			newNode->setLookupFlags();
			typedef void (BfmeQuery1279::*InsertFn)(int, BfmeNestedBE *);
			union
			{
				void (*raw)(void);
				InsertFn member;
			} fn;
			fn.raw = d_008bd230;
			(g_bfmeHolderBU->m_query->*fn.member)(value, newNode);
			return newNode;
		}
	}
	return 0;
}
