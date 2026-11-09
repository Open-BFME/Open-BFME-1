// cl: /EHsc
// Address-derived Apt lookup and creation helper at retail RVA 0x008930C0.

extern void *(*Rva008C5D70Alloc)(unsigned int bytes);
// Defining name at 0x00897300: void __cdecl bfmePush(BfmeItemDX *), defined in
// game/GameEngine/Source/Common/Bfme5FiftyFour.cpp.
class BfmeItemDX;
void __cdecl bfmePush(BfmeItemDX *item);

// Retail's cleanup funclet for the creation below calls the sized, headered
// class operator delete at 0x00891650 (tools/eh_info.py 0x008930C0: push 0x64
// / push block / call 0x00C91650), defined in HeaderedDeleteOperators.cpp.
class Rva00891650HeaderedDelete
{
public:
	static void operator delete(void *storage, unsigned int size);
};

class BfmeNestedBE : public Rva00891650HeaderedDelete
{
public:
	BfmeNestedBE(int kind, unsigned int marker, int value);
	virtual void bfmeLinked1284();

	void *operator new(unsigned int bytes)
	{
		char *raw = (char *)Rva008C5D70Alloc(bytes + 8);
		char *block = raw + 8;
		bfmePush((BfmeItemDX *)block);
		return block;
	}

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
	BfmeNestedBE *m_prev;
	BfmeNestedBE *m_next;
	char m_padding5c[0x64 - 0x5c];
};

class BfmeQuery1279
{
public:
	BfmeNestedBE *m_root;
	void bfmeQuery1279(void *value, int zero, void **other, void **result);
	BfmeNestedBE *bfmeInsert1279(int value, BfmeNestedBE *node);
};

BfmeNestedBE *BfmeQuery1279::bfmeInsert1279(int value, BfmeNestedBE *node)
{
	void *previousValue;
	void *other;
	bfmeQuery1279((void *)value, 0, &previousValue, &other);
	BfmeNestedBE *previous = (BfmeNestedBE *)previousValue;
	node->m_next = previous->m_next;
	node->m_prev = previous;
	node->bfmeLinked1284();
	if (node->m_next)
		node->m_next->m_prev = node;
	node->m_prev->m_next = node;
	node->m_bfme08 = value;
	return node;
}

// Layout stand-in for the retail singleton at 0x013377D8; the defining
// spelling is BfmePicker1284.cpp's BfmePickWorld1284 (struct -> ?PAU).
struct BfmePickWorld1284
{
	char m_prefix[0x122c];
	BfmeQuery1279 *m_query;
};

extern BfmePickWorld1284 *g_bfmeHolderBU;

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
					node = node->m_next;
				} while (node);
			}

			BfmeNestedBE *newNode = new BfmeNestedBE(0x13, 0, 0);
			newNode->setLookupFlags();
			g_bfmeHolderBU->m_query->bfmeInsert1279(value, newNode);
			return newNode;
		}
	}
	return 0;
}
