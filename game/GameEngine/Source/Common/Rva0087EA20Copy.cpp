// cl: /O2 /Ob0 /G6

struct BfmeTailA2
{
	char *m_p;
	void copyFrom(const BfmeTailA2 *src);
};

struct BfmeCoordA2
{
	int m_x;
	int m_y;
	int m_z;
};

struct BfmeElemA2
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	BfmeCoordA2 m_10;
	BfmeTailA2 m_1C;
	char m_20;
	char m_pad[3];
};

BfmeElemA2 *bfmeCopyA2(BfmeElemA2 *first, BfmeElemA2 *last, BfmeElemA2 *dest)
{
	int n = last - first;
	if (n > 0)
	{
		int m = n;
		do
		{
			dest->m_00 = first->m_00;
			dest->m_04 = first->m_04;
			dest->m_08 = first->m_08;
			dest->m_0C = first->m_0C;
			dest->m_10 = first->m_10;
			dest->m_1C.copyFrom(&first->m_1C);
			dest->m_20 = first->m_20;
			++first;
			++dest;
		} while (--m);
	}
	return dest;
}
