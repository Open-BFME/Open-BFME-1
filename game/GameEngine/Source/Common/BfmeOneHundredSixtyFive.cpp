// A record slid up the run until it finds the place where it belongs.

struct BfmeRecAB
{
	int m_bfmeKey;				// 0x0
	int m_bfmeFirst;			// 0x4
	int m_bfmeSecond;			// 0x8
};

void bfmeSlideAB(BfmeRecAB *at, int key, int first, int second)
{
	BfmeRecAB *prev = at - 1;

	while (key < prev->m_bfmeKey)
	{
		*at = *prev;
		at = prev;
		--prev;
	}

	at->m_bfmeKey = key;
	at->m_bfmeFirst = first;
	at->m_bfmeSecond = second;
}
