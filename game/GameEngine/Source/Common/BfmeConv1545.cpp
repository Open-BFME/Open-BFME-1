// Open-BFME5 conversions.

class BfmeStrVOT
{
public:
	void bfmeSetVOT(const BfmeStrVOT &o);
	char *m_bfme00;
};

struct BfmeElemVOT
{
	int m_bfme00;
	BfmeStrVOT m_bfme04;
	char m_bfme08;
	char m_bfmePad09[3];
};

BfmeElemVOT *bfmeCopyBackVOT(const BfmeElemVOT *first, const BfmeElemVOT *last, BfmeElemVOT *dest)
{
	int n = last - first;

	if (n > 0)
	{
		int i = n;

		do
		{
			--last;
			--dest;
			dest->m_bfme00 = last->m_bfme00;
			dest->m_bfme04.bfmeSetVOT(last->m_bfme04);
			dest->m_bfme08 = last->m_bfme08;
		} while (--i);
	}
	return dest;
}
