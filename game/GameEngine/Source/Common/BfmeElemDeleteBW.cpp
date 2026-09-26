// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the vector deleting destructor at retail 0x00892CD0, 111 bytes.
// The element destructor is inline, so the scalar branch expands it while the
// array branch still needs the out-of-line copy for the iterator.

int bfmeCheckBW(void *block);

void bfmeFreeBW(void *block);

class BfmeElemBW
{
public:
	~BfmeElemBW(void)
	{
		if (m_bfmeBlockBW != 0 && bfmeCheckBW(m_bfmeBlockBW) == 0)
			bfmeFreeBW(m_bfmeBlockBW);
	}

	__declspec(dllimport) static void operator delete(void *block, unsigned int size);

	__declspec(dllimport) static void operator delete[](void *block);

	void *m_bfmeBlockBW;
};

void bfmeDeleteArrayBW(BfmeElemBW *items)
{
	delete[] items;
}
