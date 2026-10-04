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

	// Unresolved EH reconstruction: this view currently emits an 11-byte
	// cleanup calling global delete, but retail parent RVA 0x008BE5A0 reaches
	// the 15-byte action at 0x00C592E0 through its handler/FuncInfo/unwind map.
	// That action passes size 100 to the 34-byte sized-delete provider at
	// 0x00891650. Its declaring class is not proved; neither a forwarding
	// wrapper nor invented inheritance is an exact repair. Matching the
	// parent body or linking this TU does not verify that cleanup. See
	// targets/game/reverse/identity_evidence/apt_sized_delete_00891650.md.

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
