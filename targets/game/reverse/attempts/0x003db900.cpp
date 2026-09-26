// ?bfmeCostZF@BfmeHostZF@@QAEHPAPAUBfmePtZF@@0@Z
// partial score=0.60 date=2026-09-09
#include <stdlib.h>

struct BfmePtZF
{
	unsigned short m_bfme00ZF;
	unsigned short m_bfme02ZF;
	unsigned short m_bfme04ZF;
};

struct BfmeNodeZF
{
	int m_bfme00ZF;
	int m_bfme04ZF;
	int m_bfme08ZF;
};

class BfmeHostZF
{
public:
	int bfmeCostZF(BfmePtZF **a, BfmePtZF **b);

	unsigned char m_bfmeHeadZF[0x2470c];
	BfmeNodeZF *m_bfme2470CZF;
	BfmeNodeZF *m_bfme24710ZF;
};

int BfmeHostZF::bfmeCostZF(BfmePtZF **a, BfmePtZF **b)
{
	BfmePtZF *p = *a;

	int x = p->m_bfme00ZF;
	int y = p->m_bfme04ZF;

	BfmeNodeZF *end = m_bfme24710ZF;
	BfmeNodeZF *beg = m_bfme2470CZF;

	int acc = 0;

	while (end != beg)
	{
		end--;

		int dx = abs(x - end->m_bfme04ZF);
		int dy = abs(y - end->m_bfme08ZF);

		if (dx > dy)
			acc = (acc + 5 * dx + 2 * dy) * 2;
		else
			acc = (acc + 2 * dx + 5 * dy) * 2;

		x = end->m_bfme04ZF;
		y = end->m_bfme08ZF;

		acc += 0x578;
	}

	BfmePtZF *q = *b;

	int fx = abs(x - q->m_bfme00ZF);
	int fy = abs(y - q->m_bfme04ZF);

	if (fx > fy)
		return acc + 10 * fx + 4 * fy;

	return acc + 4 * fx + 10 * fy;
}
