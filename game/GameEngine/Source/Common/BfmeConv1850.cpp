struct BfmeNodeXQ
{
	BfmeNodeXQ *m_bfmeNextXQ;
};

struct BfmeSlotXQ
{
	unsigned char m_bfmePadXQ[0x10];
	BfmeNodeXQ *m_bfmeHeadXQ;
};

class BfmeOwnerXQ
{
public:
	int bfmeMoveXQ(int from, void *key);
	int bfmeMoveXQ(BfmeOwnerXQ *source, int from);

	int bfmeFindXQ(void *key);
	void bfmeTouchXQ(int index);

	unsigned char m_bfmeHeadXQ[0xc];
	BfmeSlotXQ *m_bfmeTableXQ;
};

int BfmeOwnerXQ::bfmeMoveXQ(int from, void *key)
{
	int to = bfmeFindXQ(key);

	if (to == -1)
		return from;

	BfmeSlotXQ *src = &m_bfmeTableXQ[from];
	BfmeNodeXQ *node = src->m_bfmeHeadXQ;

	src->m_bfmeHeadXQ = node->m_bfmeNextXQ;

	BfmeSlotXQ *dst = &m_bfmeTableXQ[to];

	node->m_bfmeNextXQ = dst->m_bfmeHeadXQ;
	dst->m_bfmeHeadXQ = node;

	bfmeTouchXQ(from);

	return to;
}

int BfmeOwnerXQ::bfmeMoveXQ(BfmeOwnerXQ *source, int from)
{
	BfmeSlotXQ *src = &source->m_bfmeTableXQ[from];
	int to = bfmeFindXQ(&src->m_bfmePadXQ[8]);

	if (to == -1)
		return to;

	BfmeSlotXQ *dst = &m_bfmeTableXQ[to];
	BfmeNodeXQ *node = src->m_bfmeHeadXQ;
	src->m_bfmeHeadXQ = node->m_bfmeNextXQ;

	node->m_bfmeNextXQ = dst->m_bfmeHeadXQ;
	dst->m_bfmeHeadXQ = node;

	source->bfmeTouchXQ(from);

	return to;
}
