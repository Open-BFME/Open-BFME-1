// Retail 0x0018EDF0, 61 bytes, split by the ledger after the walk with the
// unlink itself claimed as an alias of AssetIterator::First.
//
// The walk carries a POINTER TO A LINK, not a node: eax starts as the address
// of the head global, each step loads through it and then advances by four to
// the next field of what it found, and the final store writes through it. That
// is what makes the loop able to unlink the first element without a special
// case.
//
// The head's first comparison is hoisted out of the loop -- the global is read
// once into a register and compared before the walk begins -- so the null
// check only guards the elements after it.
//
// The dirty flag at 0x012EF418 is the same global 0x0018F2C0 sets bit 0 of.

class BfmeLinkNode
{
public:
	char m_bfmeHead[0x04];
	BfmeLinkNode *m_bfmeNext;					// +0x04
};

extern int TheBfmeDrawableDirtyFlags;					// 0x012EF418
extern BfmeLinkNode *TheBfmeLinkHead;					// 0x012EF41C

// ?Gen_0018edf0@@YAXPAVBfmeLinkNode@@@Z
void Gen_0018edf0(BfmeLinkNode *node)
{
	TheBfmeDrawableDirtyFlags |= 1;

	BfmeLinkNode **link = &TheBfmeLinkHead;

	while (*link != node)
	{
		BfmeLinkNode *current = *link;

		if (!current)
			return;

		link = &current->m_bfmeNext;
	}

	*link = node->m_bfmeNext;

	node->m_bfmeNext = 0;
}
