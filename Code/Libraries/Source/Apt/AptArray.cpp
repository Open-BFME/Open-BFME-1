// cl: /O2 /DNDEBUG /MD

#include <cstring>

extern void *(*WideAllocPtr)(unsigned int bytes);
extern void (*WideFreePtr)(void *block);

class BfmeN1242
{
public:
	void bfmeReserve1242(int n);

	char m_bfmePad00[0x20];
	void **m_bfme20;
	int m_bfme24;
};

void BfmeN1242::bfmeReserve1242(int n)
{
	int cap = m_bfme24;
	int bits = 0;
	if (cap >= n)
		return;

	int t = n - 1;
	if (t)
	{
		do
		{
			t >>= 1;
			++bits;
		} while (t);
	}

	int grow = 1 << bits;
	if (grow < 8)
		grow = 8;

	unsigned int bytes = (unsigned int)grow * 4;
	void *block = WideAllocPtr(bytes);
	memset(block, 0, bytes);

	if (m_bfme20)
	{
		memcpy(block, m_bfme20, (unsigned int)m_bfme24 * 4);
		WideFreePtr(m_bfme20);
		m_bfme20 = 0;
	}

	m_bfme24 = grow;
	m_bfme20 = (void **)block;
}
