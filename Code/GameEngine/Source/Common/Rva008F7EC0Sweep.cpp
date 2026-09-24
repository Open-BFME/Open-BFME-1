// cl: /O2

// ?method@Rva008F7EC0@@QAEXXZ
//
// Callers span BfmeThingCDE::bfmeDtorCDE, ShroudManagerImpl008FBA40::configure
// and BfmeSinkB::bfmeAccept, so the receiver layout is shared rather than
// owned by any one of them; the address token stands in for an unproven
// class. Walks the m_1c/m_20 array the BfmeThingCDE-shaped initializeArray
// (0x008F7E20) allocates and unlinks each still-registered element from its
// owning cell's intrusive doubly-linked list, stopping at the first already
// -cleared slot.

class Element
{
public:
	void *m_cell;
	void *m_04;
	Element **m_pprev;
	Element *m_next;
};

class Rva008F7EC0
{
public:
	void method();

	unsigned char m_pad00[0x1c];
	Element *m_1c;
	int m_20;
};

void Rva008F7EC0::method()
{
	Element *end = m_1c + m_20;
	Element *p = m_1c;
	for (; p != end; ++p)
	{
		if (p->m_cell == 0)
			return;
		p->m_cell = 0;
		if (p->m_next)
			p->m_next->m_pprev = p->m_pprev;
		*p->m_pprev = p->m_next;
	}
}
