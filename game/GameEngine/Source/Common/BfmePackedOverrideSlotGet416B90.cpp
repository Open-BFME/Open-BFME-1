// cl: /O2 /Ob1 /DNDEBUG /MD
//
// Retail 0x00416B90 (50B): sibling of bfmeGoJA @ 0x416AE0. When m_head at
// +0xFC is set, ecx is replaced with the head and control tail-jumps to the
// head's indexed getter at 0x001C3A00 (ILT 0x0004775D). Otherwise the same
// Overridable-chain +0x60 return as GoJA, with an unused stdcall int that
// forces ret 4.

class Overridable
{
public:
	Overridable *getFinalOverride();

	void *m_vtable;
	Overridable *m_nextOverride;
};

class BfmeHead416B90
{
public:
	void *lookup(int index);				///< ILT 0x0004775D -> 0x001C3A00
};

class BfmeHost416B90
{
public:
	void *getSlot(int index);

private:
	int m_pad00;
	Overridable *m_slot;					///< +0x04
	char m_pad08[0xF4];
	BfmeHead416B90 *m_head;					///< +0xFC
};

// ?getSlot@BfmeHost416B90@@QAEPAXH@Z
void *BfmeHost416B90::getSlot(int index)
{
	BfmeHead416B90 *head = m_head;
	if (head)
		return head->lookup(index);
	Overridable *slot = m_slot;
	if (!slot)
		return (void *)0x60;
	Overridable *r = slot;
	if (slot->m_nextOverride)
		r = slot->m_nextOverride->getFinalOverride();
	return (char *)r + 0x60;
}
