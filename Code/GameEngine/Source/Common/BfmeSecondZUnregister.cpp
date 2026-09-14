// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: bfmeUnregister(BfmeSecondZ *) -- retail 0x0035AC30, 92 bytes.
//
// The two-member vector destructor at 0x0035B8A0 (Bfme5TwoMemberVectorDtors.cpp)
// calls this through ILT 0x00035328 on its second member. The member is a
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

class BfmeNodeZ
{
public:
	~BfmeNodeZ(void);					// retail 0x00042A32 (ILT)

	BfmeNodeZ *m_bfmeNext;					// +0x00
};

class BfmeElementZ
{
public:
	~BfmeElementZ(void);					// retail 0x0004884C (ILT)

	unsigned char m_bfmeHead[0x10];				// +0x00
	BfmeNodeZ *m_bfmeList;					// +0x10
};

class BfmeSecondZ
{
public:
	BfmeElementZ *m_bfmeBegin;				// +0x00
	BfmeElementZ *m_bfmeEnd;				// +0x04
};

// ?bfmeUnregister@@YAXPAVBfmeSecondZ@@@Z
void __cdecl bfmeUnregister(BfmeSecondZ *second)
{
	while (second->m_bfmeBegin != second->m_bfmeEnd)
	{
		BfmeElementZ *e = second->m_bfmeEnd - 1;

		while (e->m_bfmeList)
		{
			BfmeNodeZ *n = e->m_bfmeList;

			e->m_bfmeList = e->m_bfmeList->m_bfmeNext;
			delete n;
		}

		--second->m_bfmeEnd;
		second->m_bfmeEnd->~BfmeElementZ();
	}
}
