// ?bfmeFind@Gen_00141220@@QBEPAVBfmeTreeNode@@PBX@Z
// partial score=0.9 date=2026-09-04
// ?bfmeFind@Gen_00141220@@QBEPAVBfmeTreeNode@@PBX@Z
// partial score=0.9 date=2026-09-04
// ?bfmeFind@Gen_00141220@@QBEPAVBfmeTreeNode@@PBX@Z
// partial score=0.9 date=2026-08-25
// Retail 0x00141220, 96 bytes. Two names sit on the address -- both spellings
// of a red-black tree _M_find over a BitFlags key -- and reproducing either
// template mangling exactly is more scaffolding than the bytes justify, so the
// row takes an address-derived name.
//
// The layout falls straight out: header at this+0x00, comparator sub-object at
// this+0x08 (reached with lea, so embedded rather than stored), and nodes with
// parent at +0x04, left at +0x08, right at +0x0C and the value at +0x10.
//
// The comparator is called twice with its arguments in OPPOSITE orders -- the
// node's value against the key in the walk, the key against the node's value
// in the check afterwards -- which is what a strict-weak-ordering find does to
// decide equality without an equality operator.
//
// The walk keeps the last node that did not compare less as its answer, and
// the header doubles as the not-found value.

class BfmeTreeNode
{
public:
	char m_bfmeColour[0x04];					// +0x00
	BfmeTreeNode *m_bfmeParent;					// +0x04
	BfmeTreeNode *m_bfmeLeft;					// +0x08
	BfmeTreeNode *m_bfmeRight;					// +0x0C
	char m_bfmeValue[0x04];						// +0x10
};

class BfmeTreeCompare
{
public:
	bool operator()(const void *left, const void *right) const;	// ILT 0x0000A9A2
};

class Gen_00141220
{
public:
	BfmeTreeNode *bfmeFind(const void *key) const;

private:
	BfmeTreeNode *m_bfmeHeader;					// +0x00
	char m_bfmeMid[0x08 - 0x04];
	BfmeTreeCompare m_bfmeCompare;					// +0x08
};

// ?bfmeFind@Gen_00141220@@QBEPAVBfmeTreeNode@@PBX@Z
BfmeTreeNode *Gen_00141220::bfmeFind(const void *key) const
{
	BfmeTreeNode *header = m_bfmeHeader;
	BfmeTreeNode *found = header;
	BfmeTreeNode *node = header->m_bfmeParent;

	while (node)
	{
		if (!m_bfmeCompare(&node->m_bfmeValue, key))
		{
			found = node;
			node = node->m_bfmeLeft;
		}
		else
		{
			node = node->m_bfmeRight;
		}
	}

	if (found != header && !m_bfmeCompare(key, &found->m_bfmeValue))
		return found;

	return header;
}
