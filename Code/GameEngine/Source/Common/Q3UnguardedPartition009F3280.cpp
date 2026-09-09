// cl: /DNDEBUG /MD /EHsc

// The ascending twin of the adjacent Q3SortElem8 partition at 0x009F3300.
// Gen009F3DC0 calls this body directly from its median/partition path.

struct Q3SortElem8
{
	int m_a;
	float m_b;
};

struct Q3SortCompare
{
	void *m_state;

	bool operator()(const Q3SortElem8 &left,
		const Q3SortElem8 &right) const
	{
		return left.m_b < right.m_b;
	}
};

Q3SortElem8 *Gen009F3280(Q3SortElem8 *first, Q3SortElem8 *last,
	Q3SortElem8 value, Q3SortCompare comp)
{
	while (true)
	{
		while (comp(*first, value))
			++first;
		--last;
		while (comp(value, *last))
			--last;
		if (!(first < last))
			return first;
		Q3SortElem8 temporary = *first;
		*first = *last;
		*last = temporary;
		++first;
	}
}
