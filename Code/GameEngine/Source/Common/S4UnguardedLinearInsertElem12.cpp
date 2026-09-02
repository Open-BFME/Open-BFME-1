// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__unguarded_linear_insert over S4SortElem12, retail
// 0x0052F110, 109 bytes.  The comparison is the same BfmeLess0052E880 the
// matched linear_insert at 0x0052FE90 already names: key descending, then
// the pointed-to StringBase at +4.

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

void bfmeUnguardedLinearInsertElem12(S4SortElem12 *last, S4SortElem12 val)
{
	S4SortElem12 *next = last;
	--next;
	while (bfmeLessVal(val, *next))
	{
		*last = *next;
		last = next;
		--next;
	}
	*last = val;
}
