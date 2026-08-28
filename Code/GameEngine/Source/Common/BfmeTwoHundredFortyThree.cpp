// A counted run of triples copied across, each of the three words in turn, with
// the advanced destination handed back.

struct BfmeVecOA
{
	int m_bfmeAcross;			// 0x0
	int m_bfmeUp;				// 0x4
	int m_bfmeAlong;			// 0x8
};

BfmeVecOA *bfmeCopyOA(const BfmeVecOA *first, const BfmeVecOA *last, BfmeVecOA *out)
{
	int count = (int)(last - first);

	while (count > 0)
	{
		out->m_bfmeAcross = first->m_bfmeAcross;
		out->m_bfmeUp = first->m_bfmeUp;
		out->m_bfmeAlong = first->m_bfmeAlong;

		++first;
		++out;
		--count;
	}

	return out;
}
