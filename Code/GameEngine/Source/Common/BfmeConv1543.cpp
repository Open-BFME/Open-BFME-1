// Open-BFME5 conversions.

class BfmeStrVOS
{
public:
	void bfmeSetVOS(const BfmeStrVOS &o);
	char *m_bfme00;
};

struct BfmeElemVOS
{
	char m_bfme00;
	char m_bfmePad01[3];
	BfmeStrVOS m_bfme04;
	int m_bfme08;
};

BfmeElemVOS *bfmeCopyBackVOS(const BfmeElemVOS *first, const BfmeElemVOS *last, BfmeElemVOS *dest)
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
			dest->m_bfme04.bfmeSetVOS(last->m_bfme04);
			dest->m_bfme08 = last->m_bfme08;
		} while (--i);
	}
	return dest;
}
