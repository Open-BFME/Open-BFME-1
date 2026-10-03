// Retail's two calls out of this body reach the p20-deque producer at
// 0x008FBCB0 and the queue send at 0x008FA070; both bodies are in the ledger,
// so the call sites carry their DEFINING names. A private stand-in queue class
// left the object referencing two names nothing defines.
class Rva008FBCB0P20Queue
{
public:
	void append(int a, int b, int c, int d);
};

// The 0x008FA070 body is BfmeOwnerXO's: six arguments, the first two pointers.
class BfmeOwnerXO
{
public:
	void bfmeSendXO(void *a1, void *a2, int a3, int a4, void *a5, unsigned int a6);
};

class BfmeHostXO
{
public:
	void bfmeFlushXO();

	Rva008FBCB0P20Queue *m_bfme00XO;
	unsigned char m_bfmeHeadXO[0xb4 - 4];
	int m_bfmeB4XO;
	int m_bfmeB8XO;
	int m_bfmeBCXO;
	int m_bfmeC0XO;
	int m_bfmeAXO[2];
	unsigned int m_bfmeCXO[2];
	unsigned int m_bfmeBXO[2];
};

void BfmeHostXO::bfmeFlushXO()
{
	if (m_bfmeBCXO >= 0)
	{
		m_bfme00XO->append(m_bfmeB4XO, m_bfmeB8XO, m_bfmeBCXO, m_bfmeC0XO);

		m_bfmeBCXO = -1;
	}

	unsigned int i;

	for (i = 0; i < 2; i++)
	{
		int a = m_bfmeAXO[i];

		if (a < 0)
			continue;

		unsigned int b = m_bfmeBXO[i];

		if (b <= 0)
			continue;

		// Both calls land on the same receiver at +0x00.
		BfmeOwnerXO *owner = reinterpret_cast<BfmeOwnerXO *>(m_bfme00XO);
		owner->bfmeSendXO((void *)m_bfmeB4XO, (void *)m_bfmeB8XO, a, i, (void *)-(int)b, m_bfmeCXO[i]);

		m_bfmeAXO[i] = -1;
	}
}
