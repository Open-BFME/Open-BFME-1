// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x009291F0 is an indexed refcounting getter: it loads the table at
// this+8, fetches slot[i], add-refs through the halfword at +4 when non-null,
// and returns the reloaded slot. IDENTITY IS NOT RECOVERED: the owner keeps
// its address token; the sibling MatBufferClass::Get_Element at 0x00739780
// reads its array at +0x0C, so this +8-table body cannot share that identity.
struct Rva009291F0Table
{
	void *m_slots[1];
};

class Rva009291F0Box
{
public:
	void *getBuf(int i);
	int m_pad0;
	int m_pad4;
	Rva009291F0Table *m_table;
};

void *Rva009291F0Box::getBuf(int i)
{
	void *b = m_table->m_slots[i];
	if (b)
		++*(int *)((char *)b + 4);
	return m_table->m_slots[i];
}
