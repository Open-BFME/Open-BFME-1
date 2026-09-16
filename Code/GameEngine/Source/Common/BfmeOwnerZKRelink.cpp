// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail RVA 0x0035DCF0. The body walks a singly linked list to find the slot
// that points at one node and then forwards to BfmeOwnerZK::bfmeMoveZK at
// 0x0035D940, which is what places it on that class.

class BfmeKeyZK;

struct BfmeNodeZK
{
	BfmeNodeZK *m_bfmeNextZK;
};

struct BfmeHeadZK
{
	int m_bfmePadZK;
	BfmeNodeZK *m_bfmeFirstZK;
};

class BfmeOwnerZK
{
public:
	void bfmeRelinkZK(BfmeKeyZK *key, BfmeHeadZK *list, BfmeNodeZK *node,
		BfmeHeadZK *fallback, BfmeNodeZK **where);
	void bfmeMoveZK(BfmeKeyZK *key, BfmeNodeZK **from, BfmeNodeZK **to);
};

void BfmeOwnerZK::bfmeRelinkZK(BfmeKeyZK *key, BfmeHeadZK *list, BfmeNodeZK *node,
	BfmeHeadZK *fallback, BfmeNodeZK **where)
{
	BfmeNodeZK **slot = &list->m_bfmeFirstZK;

	while (*slot != node)
	{
		if (*slot == 0)
			return;

		slot = &(*slot)->m_bfmeNextZK;
	}

	bfmeMoveZK(key, slot, where != 0 ? where : &fallback->m_bfmeFirstZK);
}
