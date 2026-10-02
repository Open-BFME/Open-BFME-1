// The rank thresholds are the first member of the shared rank-point table,
// retail 0x012F401C (TheRankPointValues).
struct RankPoints
{
	int m_ranks[11];
};

extern RankPoints *TheRankPointValues;			// retail 0x012F401C

// ?bfmeBandChecked@@YAHH@Z
int __cdecl bfmeBandChecked(int value)
{
	int *limit = TheRankPointValues->m_ranks;
	int index = 0;

	if (limit) {
		while (index < 9 && value >= limit[index + 1])
			++index;
	}

	return index + 1;
}
