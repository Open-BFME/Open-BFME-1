// Retail 0x008D1E70: 61 bytes; address-derived borrowed node view.
// Independent physical ABI: ECX receiver, one signed stack word, RET 4.
// Follows the link at +0x4C to count depth, then returns a word at +8
// or the all-ones sentinel. Pointer spelling describes word transport;
// native owner, declared field/return types and lifetime are unproven.
// This view is independent of nearby address views and has no constructors.
// Boundary: INT3 ends at 0x008D1E6F; RET 4 ends at 0x008D1EAD;
// INT3 padding 0x008D1EAD..AF precedes the next body at 0x008D1EB0.
// Source lever: merge the final field load; decrement the existing depth
// before following each link rather than materializing a second steps local.
struct Rva008D1E70Node
{
	unsigned char m_pad0[8];
	void* m_8;
	unsigned char m_padC[0x4c - 0xC];
	Rva008D1E70Node* m_4c;

	void* rva008D1E70(int n);
};

void* Rva008D1E70Node::rva008D1E70(int n)
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
    Rva008D1E70Node* cur = this;
    if (depth != n) {
        depth -= n;
        do { --depth; cur = cur->m_4c; } while (depth);
    }
    return cur->m_8;
}
