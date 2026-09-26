// ?atLevel@Rva008D1E70Node@@QAEPAXH@Z
// partial score=0.82 date=2026-09-06
// ?atLevel@Rva008D1E70Node@@QAEPAXH@Z
// Address-derived: walk the m_4c singly-linked chain from this to compute a
// depth, then either return -1 (n beyond depth), this->m_8 (n == depth), or
// walk (depth-n) steps from `this` via m_4c and return that node's m_8.
struct Rva008D1E70Node
{
	unsigned char m_pad0[8];
	void* m_8;
	unsigned char m_padC[0x4c - 0xC];
	Rva008D1E70Node* m_4c;

	void* atLevel(int n);
};

void* Rva008D1E70Node::atLevel(int n)
{
	int depth = 0;
	Rva008D1E70Node* p = m_4c;
	while (p)
	{
		p = p->m_4c;
		++depth;
	}

	if (n > depth)
		return (void*)-1;

	if (depth == n)
		return m_8;

	Rva008D1E70Node* cur = this;
	int steps = depth - n;
	do
	{
		cur = cur->m_4c;
	} while (--steps);
	return cur->m_8;
}
