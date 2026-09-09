// cl: /DNDEBUG /MD /EHsc
// STLport 4.5.3 algorithm reconstruction; external helper declarations keep
// the independently compiled retail partition and partial-sort specializations.
//
// Retail 0x005331E0 is the STLport introsort loop over the proven twelve-byte
// S4 record family.  The neighbouring linear-insert, partial-sort, heap, and
// unguarded-partition bodies establish the record fields and comparator: a
// pointer at +0, a signed key at +4, a third dword at +8, and the named object
// comparison through StringBase<char>::compareNoCase.  This TU keeps the
// owner address-derived; the family evidence does not prove a higher-level
// game class for this COMDAT.

template <class T>
class StringBase
{
public:
	int compareNoCase(const StringBase<T> &other) const;

private:
	void *m_bfmeData;
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

struct S4Cmp00531FA0
{
	void *m_bfmeState;

	bool operator()(const S4SortElem12 &left,
		const S4SortElem12 &right) const
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
};



namespace _STL {

template <class RandomAccessIter, class Tp, class Compare>
RandomAccessIter __unguarded_partition(RandomAccessIter, RandomAccessIter,
    Tp, Compare);
template <class RandomAccessIter, class Tp, class Compare>
void __partial_sort(RandomAccessIter, RandomAccessIter, RandomAccessIter,
    Tp *, Compare);

#if defined(_MSC_VER)
__forceinline
#endif
static const S4SortElem12 &median00531fa0(const S4SortElem12 &a,
    const S4SortElem12 &b, const S4SortElem12 &c, S4Cmp00531FA0 comp)
{
    if (comp(a, b))
    {
        if (comp(b, c)) return b;
        if (comp(a, c)) return c;
        return a;
    }
    if (comp(a, c)) return a;
    if (comp(b, c)) return c;
    return b;
}

template <class RandomAccessIter, class Tp, class Size, class Compare>
void __introsort_loop(RandomAccessIter first, RandomAccessIter last, Tp *,
    Size depth_limit, Compare comp)
{
    while (last - first > 16)
    {
        if (depth_limit == 0)
        {
            __partial_sort(first, last, last, (Tp *)0, comp);
            return;
        }
        --depth_limit;
        RandomAccessIter cut = __unguarded_partition(first, last,
            Tp(median00531fa0(*first, *(first + (last - first) / 2),
                *(last - 1), comp)), comp);
        __introsort_loop(cut, last, (Tp *)0, depth_limit, comp);
        last = cut;
    }
}

template void __introsort_loop<S4SortElem12 *, S4SortElem12, int, S4Cmp00531FA0>(
    S4SortElem12 *, S4SortElem12 *, S4SortElem12 *, int, S4Cmp00531FA0);
}
