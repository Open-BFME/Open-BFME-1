// ?rva008CB260AppendToken@@YAXPAURva008CB260Target@@PAURva008CB260Reader@@@Z
// partial score=0.8 date=2026-09-06
// ?rva008CB260AppendToken@@YAXPAURva008CB260Target@@PAURva008CB260Reader@@@Z
// Address-derived reconstruction: read one char from *reader->m_pos (post-
// incrementing the cursor), look it up through the already-dumped helper at
// 0x008A11E0 (cdecl, one int arg, returns a node pointer), append the node to
// target's array/count pair, then either return (if bit 30 of the node's
// flags word is set) or tail-dispatch the node's first virtual function.
struct Rva008CB260Reader
{
	char* m_pos;
};

struct Rva008CB260Node
{
	virtual void invoke();
	unsigned m_flagsLow : 30;
	unsigned m_kind : 2;
};

struct Rva008CB260Target
{
	int m_count;
	void* m_pad4;
	Rva008CB260Node** m_items;
};

extern void d_008a11e0();

void rva008CB260AppendToken(Rva008CB260Target* target, Rva008CB260Reader* reader)
{
	typedef Rva008CB260Node* (__cdecl *LookupFunction)(int);

	char c = *reader->m_pos;
	reader->m_pos = reader->m_pos + 1;

	Rva008CB260Node* node = reinterpret_cast<LookupFunction>(d_008a11e0)(c);

	target->m_items[target->m_count] = node;
	target->m_count = target->m_count + 1;

	if (node->m_kind & 1)
		return;

	node->invoke();
}
