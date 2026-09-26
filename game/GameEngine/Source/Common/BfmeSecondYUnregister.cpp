// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: bfmeUnregisterY(BfmeSecondY *) -- retail 0x0035ADC0, 92 bytes.
// Byte-identical twin of BfmeSecondZUnregister.cpp (0x0035AC30) over the Y
// element family; only the two destructor targets differ.
//
// The two-member vector destructor at 0x0035B960 (Bfme5TwoMemberVectorDtors.cpp)
// calls this through ILT 0x0002F0EF on its second member. The member is a
// {begin, end} span of 0x14-byte elements; each element owns a singly linked
// chain of nodes at +0x10. Retail pops the vector from the back: drain the
// element's node chain, step end back one element, run the element destructor.
//
// Shape lever: retail keeps a null test on the node before its destructor
// (`test edi,edi ... je`) even though the next-link load happens first. VC7.1
// drops the test from `delete n` once `n` itself has been dereferenced, so the
// next link must be read through the field again (`e->m_bfmeList->m_bfmeNext`)
// rather than through the local. Reading via `n->m_bfmeNext`, a volatile
// reload, a do-while, or an inlined pop-front all fold the test and land 88B.

class BfmeNodeY
{
public:
	~BfmeNodeY(void);					// retail 0x00028EC0 (ILT, +4 adjustor to 0x00354A60)

	BfmeNodeY *m_bfmeNext;					// +0x00
};

class BfmeElementY
{
public:
	~BfmeElementY(void);					// retail 0x0001FD0C (ILT, adjustor to 0x00351980)

	unsigned char m_bfmeHead[0x10];				// +0x00
	BfmeNodeY *m_bfmeList;					// +0x10
};

class BfmeSecondY
{
public:
	BfmeElementY *m_bfmeBegin;				// +0x00
	BfmeElementY *m_bfmeEnd;				// +0x04
};

// ?bfmeUnregisterY@@YAXPAVBfmeSecondY@@@Z
void __cdecl bfmeUnregisterY(BfmeSecondY *second)
{
	while (second->m_bfmeBegin != second->m_bfmeEnd)
	{
		BfmeElementY *e = second->m_bfmeEnd - 1;

		while (e->m_bfmeList)
		{
			BfmeNodeY *n = e->m_bfmeList;

			e->m_bfmeList = e->m_bfmeList->m_bfmeNext;
			delete n;
		}

		--second->m_bfmeEnd;
		second->m_bfmeEnd->~BfmeElementY();
	}
}
