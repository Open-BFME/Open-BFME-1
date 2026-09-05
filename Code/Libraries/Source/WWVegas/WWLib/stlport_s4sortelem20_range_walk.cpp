// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: gen002EB330, retail 0x002EB330, 290 bytes. The body carried only
// a machine byte-dump row. Walks [first, last) of the same twenty-byte
// string-keyed S4SortElem20 used by the neighbouring unguarded_partition and
// insertion-sort bodies. When *cur is less than *key it forwards a by-value
// copy through gen002EADF0Helper; the range is then handed to the already
// landed 20-byte shrink loop at 0x002EB010.

extern "C" int memcmp(const void *left, const void *right, unsigned int count);
#pragma intrinsic(memcmp)

template <class T>
class StringBase
{
private:
	struct Header
	{
		int m_bfmeRefCount;
		unsigned short m_bfmeLength;
		unsigned short m_bfmeCapacity;
		T m_bfmeData[1];
	};

	Header *m_bfmeHeader;

public:
	StringBase(const StringBase<T> &other);
	~StringBase();

	int compare(const StringBase<T> &other) const
	{
		const int length = other.m_bfmeHeader ? other.m_bfmeHeader->m_bfmeLength : 0;
		const char *data = other.m_bfmeHeader ? (const char *)&other.m_bfmeHeader->m_bfmeData[0] : "";
		const int myLength = m_bfmeHeader ? m_bfmeHeader->m_bfmeLength : 0;
		const char *myData = m_bfmeHeader ? (const char *)&m_bfmeHeader->m_bfmeData[0] : "";
		int result = memcmp(myData, data, myLength < length ? myLength : length);
		if (result == 0)
			result = myLength - length;
		return result;
	}

	friend struct S4SortElem20;
};

class BfmeSortElem20Tail
{
public:
	BfmeSortElem20Tail(const BfmeSortElem20Tail &other);
	~BfmeSortElem20Tail();

private:
	int m_bfmeBody[3];
};

struct S4SortElem20
{
	StringBase<char> m_bfmeName;
	char m_bfmeFlag;
	BfmeSortElem20Tail m_bfmeTail;
};

struct S4Cmp002EB8E0
{
	int m_bfmeSlot;

	bool operator()(const S4SortElem20 &left,
		const S4SortElem20 &right) const
	{
		return left.m_bfmeName.compare(right.m_bfmeName) < 0;
	}
};

void gen002EACD0(void *a, void *b, void *c, int z0, int z1);
void gen002EADF0Helper(void *a, S4SortElem20 *p, S4SortElem20 *q,
	S4SortElem20 val, void *c, int zero);
void rva002EB010(S4SortElem20 *first, S4SortElem20 *last, void *extra);

void gen002EB330(S4SortElem20 *key, S4SortElem20 *first,
	S4SortElem20 *last, int, void *extra)
{
	S4Cmp002EB8E0 comp = {0};
	gen002EACD0(key, first, extra, 0, 0);
	S4SortElem20 *cur = first;
	if (cur < last)
	{
		do
		{
			if (comp(*cur, *key))
				gen002EADF0Helper(key, first, cur, *cur, extra, 0);
			++cur;
		}
		while (cur < last);
		cur = first;
	}
	rva002EB010(key, cur, extra);
}
