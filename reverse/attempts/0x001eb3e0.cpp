// ?d_001eb3e0@@YAXXZ
// partial score=0.7 date=2026-09-02
// cl: /O2

struct BfmeSlotWS
{
	int m_v0;
	int m_v1;
	int m_v2;
	int m_v3;
	int m_v4;
	int m_v5;
};

class BfmeResetWS
{
public:
	void reset();

private:
	int m_unused00;
	int m_at04;
	int m_at08[4];
	int m_at18[4];
	BfmeSlotWS m_a[4];
	BfmeSlotWS m_b[4];
	unsigned char m_e8;
	unsigned char m_e9;
};

void BfmeResetWS::reset()
{
	m_e8 = 0;
	m_e9 = 0;
	m_at04 = 0;
	int *neg = m_at18;
	BfmeSlotWS *b = m_b;
	int n = 4;
	do
	{
		neg[-4] = 0;
		*neg = -1;
		int *a = (int *)((char *)b - 0x60);
		a[0] = 0;
		a[1] = 0;
		a[2] = 0;
		a[3] = 0;
		a[4] = 0;
		a[5] = 0;
		b->m_v0 = 0;
		b->m_v1 = 0;
		b->m_v2 = 0;
		b->m_v3 = 0;
		b->m_v4 = 0;
		b->m_v5 = 0;
		++neg;
		++b;
		--n;
	}
	while (n);
}
