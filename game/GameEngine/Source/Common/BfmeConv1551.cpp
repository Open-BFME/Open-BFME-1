// Open-BFME5 conversions.

class BfmeStrAVOW
{
public:
	void bfmeSetAVOW(const BfmeStrAVOW &o);
	char *m_bfme00;
};

class BfmeStrBVOW
{
public:
	void bfmeSetBVOW(const BfmeStrBVOW &o);
	char *m_bfme00;
};

struct BfmeElemVOW
{
	BfmeStrAVOW m_bfme00;
	BfmeStrBVOW m_bfme04;
	char m_bfmePad08[8];
};

BfmeElemVOW *bfmeCopyBackVOW(const BfmeElemVOW *first, const BfmeElemVOW *last, BfmeElemVOW *dest)
{
	int n = last - first;

	if (n > 0)
	{
		int i = n;

		do
		{
			--last;
			--dest;
			dest->m_bfme00.bfmeSetAVOW(last->m_bfme00);
			dest->m_bfme04.bfmeSetBVOW(last->m_bfme04);
		} while (--i);
	}
	return dest;
}
