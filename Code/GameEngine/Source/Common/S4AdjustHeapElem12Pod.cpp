// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport __adjust_heap over S4SortElem12 (pointer-key-int),
// retail 0x005300E0, 221 bytes.  The sift-down comparison is the same
// BfmeLess0052E880 the matched linear_insert names; copies are three dwords.

template <class T>
class StringBase
{
public:
	int compareNoCase(const StringBase<T> &other) const;
};

struct S4Named0052E880
{
	int m_bfmeUnused;
	StringBase<char> m_bfmeName;
};

struct S4SortElem12
{
	S4Named0052E880 *m_bfmeObj;
	int m_bfmeKey;
	int m_bfmeThird;
};

static bool bfmeLessVal(const S4SortElem12 &left, const S4SortElem12 &right)
{
	if (left.m_bfmeKey == right.m_bfmeKey)
	{
		if (left.m_bfmeObj != 0)
		{
			if (right.m_bfmeObj == 0)
				goto retFalse;
			return left.m_bfmeObj->m_bfmeName.compareNoCase(
				right.m_bfmeObj->m_bfmeName) < 0;
		}
		if (right.m_bfmeObj == 0)
		{
retFalse:
			return false;
		}
		return true;
	}
	return left.m_bfmeKey > right.m_bfmeKey;
}

void bfmePushHeap005300E0(S4SortElem12 *first, int holeIndex, int topIndex,
	S4SortElem12 val, void *comp);

void bfmeAdjustHeap005300E0(S4SortElem12 *first, int holeIndex, int len,
	S4SortElem12 val, void *comp)
{
	int topIndex = holeIndex;
	int secondChild = 2 * holeIndex + 2;
	while (secondChild < len)
	{
		if (bfmeLessVal(first[secondChild], first[secondChild - 1]))
			secondChild--;
		first[holeIndex] = first[secondChild];
		holeIndex = secondChild;
		secondChild = 2 * (secondChild + 1);
	}
	if (secondChild == len)
	{
		first[holeIndex] = first[secondChild - 1];
		holeIndex = secondChild - 1;
	}
	bfmePushHeap005300E0(first, holeIndex, topIndex, val, comp);
}
