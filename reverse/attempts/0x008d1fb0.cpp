// ?rva008D1FB0@Rva008D1FB0Node@@QAE_NPAU1@@Z
// partial score=0.35 date=2026-09-22
// cl: /DNDEBUG /MD

// Retail 0x008D1FB0, 192 bytes, carved boundary. __thiscall predicate over the
// +0x4C parent chain witnessed by the landed neighbours 0x008D1EE0
// (Rva008D1EE0Chain::contains) and 0x008D20F0 (Rva008D20F0Node::walk), and by
// the 0x008BB720 verdict that records it as "thiscall bool with one pointer
// arg". ret 4 and the al returns confirm that ABI, so the earlier
// identity/ABI blocker on this address is answered: the only thing left is
// codegen shape.
//
// Semantics, read off the retail body: count the receiver's chain length from
// m_next; bail false when the receiver IS the argument or the chain is empty;
// then for level 0..depth inclusive take each side's ancestor that sits `level`
// links below its own root, read the int at +8, and report whether the
// argument's value sorts first. A level deeper than that side's chain yields -1
// (retail's `or reg, -1`).
//
// Not matched: retail keeps this->m_next in EBP for the whole body and the
// argument's first link in its single stack local, re-reading the `other`
// parameter from [esp+0x18] each level. MSVC 7.1 will not CSE either chain head
// out of the loop from this spelling, so it caches `other` in EBP instead and
// reloads both heads per level.
//
// Tried and rejected, all on this exact algorithm:
//   * const vs non-const receivers on the depth helper;
//   * hoisting one or both heads into source locals and threading them through
//     the helper (this then moves out of ECX into EDI and spills, 200-231B);
//   * passing the already-computed depth into the value helper;
//   * writing both walks inline in the loop body instead of in a helper;
//   * a volatile head local, which does put this->m_next in EBP and keeps this
//     in ECX but spills `depth` and costs a second frame slot (199B);
//   * /O2 /Ob2 /G6, /Ox, /Og /Oi /Ot /Oy /Gs /GF /Gy -- no allocation change.

struct Rva008D1FB0Node
{
	unsigned char m_pad00[8];
	int m_value;
	unsigned char m_pad0C[0x4C - 0x0C];
	Rva008D1FB0Node *m_next;

	bool rva008D1FB0(Rva008D1FB0Node *other);
};

static int rva008D1FB0Depth(Rva008D1FB0Node *node)
{
	int depth = 0;
	Rva008D1FB0Node *walk = node->m_next;

	if (walk != 0)
	{
		do
		{
			walk = walk->m_next;
			++depth;
		}
		while (walk != 0);
	}

	return depth;
}

static int rva008D1FB0ValueAt(Rva008D1FB0Node *node, int level)
{
	int depth = rva008D1FB0Depth(node);

	if (level > depth)
		return -1;

	Rva008D1FB0Node *walk = node;

	for (int steps = depth - level; steps != 0; --steps)
		walk = walk->m_next;

	return walk->m_value;
}

bool Rva008D1FB0Node::rva008D1FB0(Rva008D1FB0Node *other)
{
	int depth = rva008D1FB0Depth(this);

	if (this == other)
		return false;

	if (depth == 0)
		return false;

	for (int level = 0; level <= depth; ++level)
	{
		int mine = rva008D1FB0ValueAt(this, level);
		int theirs = rva008D1FB0ValueAt(other, level);

		if (theirs < mine)
			return true;

		if (theirs > mine)
			return false;
	}

	return false;
}
