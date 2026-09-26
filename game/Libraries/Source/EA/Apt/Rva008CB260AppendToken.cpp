// Retail 0x008CB260 (60 bytes), address-derived identity: read one char from *reader->m_pos (post-
// incrementing the cursor), look it up through the already-dumped helper at
// 0x008A11E0 (cdecl, one int arg, returns a node pointer), append the node to
// target's array/count pair, then either return (if bit 30 of the node's
// flags word is set) or tail-dispatch the node's first virtual function.
// The narrow flag local preserves retail's shift/test instruction pair.
struct Rva008CB260Reader
{
	char* m_pos;
};

struct Rva008CB260Node
{
	virtual void invoke();
	unsigned int m_flags;
};

struct Rva008CB260Target
{
	int m_count;
	void* m_pad4;
	Rva008CB260Node** m_items;
};

class AptInteger { public: static AptInteger* Create(int value); };

void rva008CB260AppendToken(Rva008CB260Target* target, Rva008CB260Reader* reader)
{
	char c = *reader->m_pos;
	reader->m_pos = reader->m_pos + 1;

	Rva008CB260Node* node = (Rva008CB260Node*)AptInteger::Create(c);

	target->m_items[target->m_count] = node;
	target->m_count = target->m_count + 1;

	unsigned char flags = (unsigned char)(node->m_flags >> 30);
	if (flags & 1)
		return;

	node->invoke();
}
