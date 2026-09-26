// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: STLport vector of four-byte AsciiString elements, two-argument
// resize.  Retail 0x009CD890, 123 bytes.  The fill value is passed by value
// so the body has an EH frame and destroys the parameter on the way out.

template <class T>
class StringBase
{
public:
	void set(const StringBase<T> &other);
	StringBase<T> &operator=(const StringBase<T> &other)
	{
		set(other);
		return *this;
	}

private:
	StringBase(const StringBase<T> &other);
	~StringBase(void);
	T *m_data;

	friend struct Q3SortElem4;
};

struct Q3SortElem4
{
	Q3SortElem4(const Q3SortElem4 &other) : m_base(other.m_base) {}
	~Q3SortElem4(void) {}
	Q3SortElem4 &operator=(const Q3SortElem4 &other)
	{
		m_base = other.m_base;
		return *this;
	}

	StringBase<char> m_base;
};

namespace _STL
{

template <class Type>
class allocator {};

template <class Type, class Allocator>
class vector
{
public:
	typedef unsigned int size_type;
	typedef Type *iterator;

	iterator erase(iterator first, iterator last);
	void _M_fill_insert(iterator position, size_type count, const Type &value);

	void resize(size_type newSize, Type value);

private:
	iterator begin(void) { return m_start; }
	iterator end(void) { return m_finish; }
	size_type size(void) const { return (size_type)(m_finish - m_start); }

	Type *m_start;
	Type *m_finish;
	Type *m_endOfStorage;
};

template <class Type, class Allocator>
void vector<Type, Allocator>::resize(size_type newSize, Type value)
{
	if (newSize < size())
		erase(begin() + newSize, end());
	else
	{
		size_type extra = newSize - size();
		_M_fill_insert(end(), extra, value);
	}
}

template void vector<Q3SortElem4, allocator<Q3SortElem4> >::resize(
	unsigned int, Q3SortElem4);

}
