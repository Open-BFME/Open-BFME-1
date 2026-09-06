// ?findAndInvoke@Gen00736AF0Owner@@QAE_NHH@Z
// partial score=0.91 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
//
// Address-derived reconstruction of the fixed-array find-and-invoke at 0x00736AF0.
// Near-twin of Rva00720BB0LookupDispatch (same owning tree-record table shape).
// Field offsets/types confirmed exact: m_fieldB (item+0x7C) is UNSIGNED (retail
// compares it with `cmp mem,0; ja`, not `test;jne`) and the loop cursor is a
// char* anchored on &item->m_fieldB (retail's `lea eax,[ecx+0x284]` == this+0x208
// (m_items) + 0x7C), incremented by sizeof(Item)=0xE8 per iteration -- not an
// index-based m_items[index] recompute, which anchors the LEA on the wrong field
// (m_fieldC) instead. Residual 8/89 non-reloc bytes: retail computes the
// `test esi,esi; jle` empty-count guard BEFORE the `lea eax,[ecx+0x284]` cursor
// init; every guard/order variant tried (separate `if(count<=0)return false`,
// ternary-guarded init, do-while, comma-order swap) either reproduces this exact
// swap or regresses to a second prologue/epilogue (ebx pushed late, +13 bytes).
// Needs a lever for sinking a loop-invariant pointer init below its own shared
// entry guard without MSVC 7.1 duplicating the ebx/esi save.

class Gen00736AF0Item
{
public:
	int m_fieldA;			// 0x00
	char m_pad04[0x70 - 0x04];
	int m_fieldC;			// 0x70
	char m_pad74[0x7C - 0x74];
	unsigned int m_fieldB;	// 0x7C
	char m_pad80[0xE8 - 0x80];
};

class Gen00736AF0Owner
{
public:
	bool findAndInvoke(int fieldAValue, int value);
	void invokeAt(int index, int value);

private:
	char m_pad00[0x208];
	Gen00736AF0Item m_items[1];
	char m_padAfterItems[0x2A7CB0 - 0x208 - sizeof(Gen00736AF0Item)];
	int m_itemCount;		// 0x2A7CB0
};

bool Gen00736AF0Owner::findAndInvoke(int fieldAValue, int value)
{
	if (fieldAValue == 0)
		return false;

	int count = m_itemCount;
	int index;
	char *pB;
	for (index = 0, pB = (char *)m_items + 0x7C; index < count; ++index, pB += sizeof(Gen00736AF0Item))
	{
		if (*(int *)(pB - 0x7C) != fieldAValue)
			continue;
		if (*(unsigned int *)pB > 0)
			continue;
		if (*(int *)(pB - 0xC) == 0)
		{
			invokeAt(index, value);
			return true;
		}
	}
	return false;
}
