// Two runs of numbers compared for sameness, and two labels merged into the
// lower of the pair everywhere they appear.

struct BfmeRunAA
{
	const int *m_bfmeBegin;			// 0x0
	const int *m_bfmeEnd;			// 0x4
};

int bfmeSameAA(const BfmeRunAA *left, const BfmeRunAA *right)
{
	const int *end = left->m_bfmeEnd;
	const int *begin = left->m_bfmeBegin;
	const int *other = right->m_bfmeBegin;

	if (right->m_bfmeEnd - other != end - begin)
		return 0;

	while (begin != end)
	{
		if (*begin != *other)
			return 0;

		++begin;
		++other;
	}

	return 1;
}

void bfmeMergeAC(int left, int right, unsigned short *labels, int count)
{
	int two = labels[left];
	int one = labels[right];

	if (one == two)
		return;

	int low = (one < two) ? one : two;

	for (int i = 0; i < count; ++i)
	{
		int here = labels[i];

		if (here == one || here == two)
			labels[i] = (unsigned short)low;
	}
}
