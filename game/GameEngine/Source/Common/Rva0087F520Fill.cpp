// cl: /O2 /Ob0 /G6

struct BfmeTailF5
{
	void copyFrom(const BfmeTailF5 *src);
};

struct BfmeElemF5
{
	int m_00;
	int m_04;
	int m_08;
	BfmeTailF5 m_0C;
};

BfmeElemF5 *bfmeFillF5(BfmeElemF5 *dest, unsigned n, const BfmeElemF5 *src)
{
	unsigned k = n;
	BfmeElemF5 *d = dest;
	if (k > 0)
	{
		unsigned m = k;
		do
		{
			if (d)
			{
				d->m_00 = src->m_00;
				d->m_04 = src->m_04;
				d->m_08 = src->m_08;
				d->m_0C.copyFrom(&src->m_0C);
			}
			++d;
		} while (--m);
	}
	return d;
}
