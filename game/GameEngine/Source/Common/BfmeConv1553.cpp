// Open-BFME5 conversions.

class BfmeStrVOX
{
public:
	void bfmeSetVOX(const BfmeStrVOX &o);
	char *m_bfme00;
};

struct BfmeElemVOX
{
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	BfmeStrVOX m_bfme0c;
};

BfmeElemVOX *bfmeCopyBackVOX(const BfmeElemVOX *first, const BfmeElemVOX *last, BfmeElemVOX *dest)
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
			dest->m_bfme04 = last->m_bfme04;
			dest->m_bfme08 = last->m_bfme08;
			dest->m_bfme0c.bfmeSetVOX(last->m_bfme0c);
		} while (--i);
	}
	return dest;
}
