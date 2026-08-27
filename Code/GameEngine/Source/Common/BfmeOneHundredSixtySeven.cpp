// The same comparison of two runs of numbers, written out a second time for a
// second caller.

struct BfmeRunAH
{
	const int *m_bfmeBegin;			// 0x0
	const int *m_bfmeEnd;			// 0x4
};

int bfmeSameAH(const BfmeRunAH *left, const BfmeRunAH *right)
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
