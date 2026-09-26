// Open-BFME5 conversions.

extern "C" void *memcpy(void *d, const void *s, unsigned n);
#pragma intrinsic(memcpy)

struct BfmeElemVKN
{
	char m_bfmePad[0xec];
};

class BfmeVecVKN
{
public:
	void bfmePushVKN(const BfmeElemVKN *e);
	void bfmeGrowVKN(BfmeElemVKN *pos, const BfmeElemVKN *e, const BfmeElemVKN **slot, int a, int b);
	int m_bfme00;
	BfmeElemVKN *m_bfme04;
	BfmeElemVKN *m_bfme08;
};

void BfmeVecVKN::bfmePushVKN(const BfmeElemVKN *e)
{
	BfmeElemVKN *cur = m_bfme04;
	if (cur != m_bfme08)
	{
		if (cur)
			memcpy(cur, e, 0xec);
		++m_bfme04;
		return;
	}
	bfmeGrowVKN(cur, e, &e, 1, 1);
}
