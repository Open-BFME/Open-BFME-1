// A record taken out of whatever list it is in and hooked onto the front of the
// one the caller names, unless it has already been moved once. Each record
// holds the slot that points at it as well as the record after it, so the
// unhooking needs no search.

struct BfmeNodeNO
{
	unsigned char m_bfmeHead[0x24];		// 0x00
	unsigned int m_bfmeFlags;		// 0x24
	unsigned char m_bfmeGap[4];		// 0x28
	BfmeNodeNO *m_bfmeNext;			// 0x2c
	BfmeNodeNO **m_bfmeBack;		// 0x30
};

class BfmeThingNO
{
public:
	void bfmeMoveNO(BfmeNodeNO **head);

private:
	BfmeNodeNO *m_bfmeSelf;			// 0x0
};

void BfmeThingNO::bfmeMoveNO(BfmeNodeNO **head)
{
	if ((m_bfmeSelf->m_bfmeFlags & 0x10) != 0)
		return;

	m_bfmeSelf->m_bfmeFlags |= 0x10;

	BfmeNodeNO *self = m_bfmeSelf;

	BfmeNodeNO **back = self->m_bfmeBack;

	if (back != 0)
	{
		*back = self->m_bfmeNext;

		BfmeNodeNO *after = self->m_bfmeNext;

		if (after != 0)
			after->m_bfmeBack = self->m_bfmeBack;

		self->m_bfmeBack = 0;
		self->m_bfmeNext = 0;
	}

	self->m_bfmeBack = head;

	BfmeNodeNO *first = *head;

	self->m_bfmeNext = first;

	if (first != 0)
		first->m_bfmeBack = &self->m_bfmeNext;

	*head = self;
}
