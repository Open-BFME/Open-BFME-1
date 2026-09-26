// Open-BFME5 conversions.

extern "C" void *memset(void *d, int c, unsigned n);
#pragma intrinsic(memset)

class BfmePoolVLR
{
public:
	virtual void bfmeSlot0VLR();
	virtual void bfmeSlot1VLR();
	virtual void *bfmeNewVLR(int n, int f);
	virtual void bfmeDelVLR(void *p, int f);
};

BfmePoolVLR *bfmeGetPoolVLR();

class BfmeBufVLR
{
public:
	void bfmeSetSizeVLR(int size);
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	char *m_bfme0c;
	volatile int m_bfme10;
};

void BfmeBufVLR::bfmeSetSizeVLR(int size)
{
	if (m_bfme0c != 0)
	{
		bfmeGetPoolVLR()->bfmeDelVLR(m_bfme0c, 0);
		m_bfme0c = 0;
		m_bfme10 = 0;
	}
	m_bfme10 = (size & ~7) + 0x80;
	m_bfme0c = (char *)bfmeGetPoolVLR()->bfmeNewVLR(m_bfme10, 0);
	memset(m_bfme0c, 0, m_bfme10);
}
