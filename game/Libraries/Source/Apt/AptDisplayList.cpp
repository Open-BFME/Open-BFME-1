extern void *(*Rva008C5D70Alloc)(unsigned int bytes);
// Defining name at 0x00897300: void __cdecl bfmePush(BfmeItemDX *), defined in
// game/GameEngine/Source/Common/Bfme5FiftyFour.cpp.
class BfmeItemDX;
void __cdecl bfmePush(BfmeItemDX *item);

class BfmeNestedBE
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

	// No class operator delete.  BfmeNestedBE's constructor is out-of-line and
	// may throw, so every `new BfmeNestedBE(...)` site grows an 11-byte SEH
	// cleanup funclet (mov eax,[ebp-0x10]; push eax; call <free>; pop ecx; ret).
	// A whole-image scan of retail finds 1126 funclets of exactly that shape and
	// every one of them calls 0x00881EB0, which the ledger holds as the single
	// matched global operator delete ??3@YAXPAX@Z
	// (game/Libraries/Source/WWVegas/WWLib/mem_ops.cpp).  No funclet of that shape
	// calls any class-specific delete anywhere in the image, so retail's
	// BfmeNestedBE has none and the cleanup must reach the global one.  Declaring
	// one here only made this TU reference an undefined ??3BfmeNestedBE@@SAXPAX@Z.

	unsigned int m_flags;
	int m_bfme08;
	char m_padding0c[0x50 - 0x0c];
	int m_bfme50;
	int m_bfme54;
	int m_bfme58;
	char m_padding5c[0x64 - 0x5c];
};

class BfmeQuery1279
{
public:
	void bfmeQuery1279(void *value, int zero, void **other, void **result);
	BfmeNestedBE *bfmeCreate1284(void *value, int kind, int marker);
};

BfmeNestedBE *BfmeQuery1279::bfmeCreate1284(void *value, int kind, int marker)
{
	int originalMarker;
	BfmeNestedBE *node = new BfmeNestedBE(kind, (originalMarker = marker), 0);
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
