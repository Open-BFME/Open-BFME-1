// cl: /O2 /Ob1

struct BfmeElemF4;

// The string member's copy constructor, retail 0x00887B60 (callees.py).
template <class T>
class StringBase
{
	friend struct BfmeElemF4;
	StringBase(const StringBase &other);
	T *m_data;
};

inline void *operator new(unsigned int, void *where) { return where; }

struct BfmeElemF4
{
	int m_00;
	int m_04;
	int m_08;
	StringBase<char> m_0C;
};

BfmeElemF4 *bfmeCopyF4(BfmeElemF4 *first, BfmeElemF4 *last, BfmeElemF4 *dest)
{
	BfmeElemF4 *d = dest;
	while (first != last)
	{
		new (d) BfmeElemF4(*first);
		first++;
		d++;
	}
	return d;
}
