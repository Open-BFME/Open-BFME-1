// A deque block advance.
//
// The common path just steps the cursor one element on; the comparison it
// takes is against the last element of the block, written as the end pointer
// minus one, which is why the subtraction is by the element width rather than
// by four.
//
// When the block runs out the old one is released -- guarded, because the very
// first advance has none -- the map pointer steps to the next block, and the
// three cursor fields are pointed at it. The block size is six elements, and
// it shows up twice: once as the freed size and once as the offset to the new
// end.

void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

struct BfmeDequeElem { char m_bfmeBytes[0x14]; };

class Gen_008FA900
{
public:
	void bfmeAdvance(void);

private:
	BfmeDequeElem *m_bfmeCur;				// +0x00
	BfmeDequeElem *m_bfmeFirst;				// +0x04
	BfmeDequeElem *m_bfmeLast;				// +0x08
	BfmeDequeElem **m_bfmeNode;				// +0x0C
};

// ?bfmeAdvance@Gen_008FA900@@QAEXXZ
void Gen_008FA900::bfmeAdvance(void)
{
	if (m_bfmeCur != m_bfmeLast - 1)
	{
		m_bfmeCur = m_bfmeCur + 1;
		return;
	}

	if (m_bfmeFirst)
		bfmeDeallocate(m_bfmeFirst, 6 * sizeof(BfmeDequeElem));

	m_bfmeNode = m_bfmeNode + 1;
	m_bfmeFirst = *m_bfmeNode;
	m_bfmeLast = m_bfmeFirst + 6;
	m_bfmeCur = m_bfmeFirst;
}
