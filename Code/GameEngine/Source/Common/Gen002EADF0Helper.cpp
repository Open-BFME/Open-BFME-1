// cl: /DNDEBUG /MD /EHsc

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
	StringBase<T> &operator=(const StringBase<T> &other)
	{
		set(other);
		return *this;
	}

private:
	StringBase(const StringBase<T> &other);
	~StringBase();
	void set(const StringBase<T> &other);
	friend struct S4SortElem20;
};

class BfmeSortElem20Tail
{
public:
	BfmeSortElem20Tail(const BfmeSortElem20Tail &other);
	~BfmeSortElem20Tail();
	BfmeSortElem20Tail &operator=(const BfmeSortElem20Tail &other)
	{
		set(other);
		return *this;
	}

	void set(const BfmeSortElem20Tail &other);

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
};

namespace _STL
{

// ?__adjust_heap absent-from-retail
template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
	Distance len, Tp val, Compare comp);

}

void gen002EADF0Helper(void *a, S4SortElem20 *p, S4SortElem20 *q,
	S4SortElem20 val, void *c, int zero)
{
	S4SortElem20 *source = (S4SortElem20 *)a;
	q->m_bfmeName = source->m_bfmeName;
	q->m_bfmeFlag = source->m_bfmeFlag;
	q->m_bfmeTail.set(source->m_bfmeTail);
	_STL::__adjust_heap((S4SortElem20 *)a, 0,
		(int)(((char *)p - (char *)a) / 20), val,
		*(S4Cmp002EB8E0 *)&c);
}
