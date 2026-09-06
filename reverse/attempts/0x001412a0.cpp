// ?bfmeFind@Gen_001412A0@@QBEPAVBfmeTreeNode@@PBX@Z
// partial score=0.9 date=2026-09-05
// Retail 0x001412A0, 96 bytes. Twin of 0x00141220 (same dump d_00140de0.asm,
// same node/tree/compare layout) over a WeaponTemplateSet BitFlags<50>
// comparator (ILT 0x00010B1D) instead of ArmorTemplateSet.
//
// Compiles to 87B, same wall as 0x00141220's stash: retail keeps `this`
// resident in ebp for the whole function and recomputes `lea ecx,[ebp+8]`
// (the &m_bfmeCompare sub-object address) fresh at BOTH call sites (loop body
// and post-loop check). Our compiler instead loads header via ecx directly
// and hoists &m_bfmeCompare once into ebp since both call sites need the same
// address -- a CSE retail's compiler did not perform. Register-declaration
// order (header/node/found) does not change this; verified swapping it is a
// no-op on the emitted bytes. Needs a lever to defeat the (this+8) address
// CSE across the early-exit branch without changing the two call sites'
// relative order.

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
	bool operator()(const void *left, const void *right) const;	// ILT 0x00010B1D
};

class Gen_001412A0
{
public:
	BfmeTreeNode *bfmeFind(const void *key) const;

private:
	BfmeTreeNode *m_bfmeHeader;					// +0x00
	char m_bfmeMid[0x08 - 0x04];
	BfmeTreeCompare m_bfmeCompare;					// +0x08
};

// ?bfmeFind@Gen_001412A0@@QBEPAVBfmeTreeNode@@PBX@Z
BfmeTreeNode *Gen_001412A0::bfmeFind(const void *key) const
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
