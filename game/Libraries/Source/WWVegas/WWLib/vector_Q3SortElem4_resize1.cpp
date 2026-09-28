// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: the one-argument resize of the same STLport vector of four-byte
// string elements as vector_Q3SortElem4_resize.cpp.  Retail 0x009CD960, 28
// bytes, emitted just after the two-argument resize at 0x009CD890, which it
// calls with a default-constructed (null) element, the way STLport's
// resize(n) forwards to resize(n, _Tp()).  Nothing in the image calls it.
//
// The two-argument form is only declared here so the call stays out of line,
// as it is in retail.

template <class T>
class StringBase
{
public:
	StringBase(void) : m_data(0) {}

private:
	StringBase(const StringBase<T> &other);
	~StringBase(void);
	T *m_data;

	friend struct Q3SortElem4;
};

struct Q3SortElem4
{
	Q3SortElem4(void) {}
	Q3SortElem4(const Q3SortElem4 &other) : m_base(other.m_base) {}
	~Q3SortElem4(void) {}

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

	void resize(size_type newSize, Type value);
	void resize(size_type newSize) { resize(newSize, Type()); }

private:
	Type *m_start;
	Type *m_finish;
	Type *m_endOfStorage;
};

template void vector<Q3SortElem4, allocator<Q3SortElem4> >::resize(unsigned int);

}
