// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: S4SortElem12::BfmeLess0052E880, retail 0x0052E880, 82 bytes.
// The matched __linear_insert at 0x0052FE90 calls this member through
// S4Cmp00531FA0, so the name is recovered from that caller.  Retail compares
// the integer at +4 first (signed greater-than), then the named object
// pointer at +0: null is less than non-null, and two live objects compare
// through StringBase<char>::compareNoCase on the string sitting at +4.

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

	bool BfmeLess0052E880(const S4SortElem12 &other) const;
};

bool S4SortElem12::BfmeLess0052E880(const S4SortElem12 &other) const
{
	if (m_bfmeKey == other.m_bfmeKey)
	{
		if (m_bfmeObj != 0)
		{
			if (other.m_bfmeObj == 0)
				goto retFalse;
			return m_bfmeObj->m_bfmeName.compareNoCase(
				other.m_bfmeObj->m_bfmeName) < 0;
		}
		if (other.m_bfmeObj == 0)
		{
retFalse:
			return false;
		}
		return true;
	}
	return m_bfmeKey > other.m_bfmeKey;
}
