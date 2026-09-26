// cl: /Od /Ob1 /DNDEBUG /MD
// STLport-style string range replace at retail 0x008312E0 that handles a source range inside the string.
// The inline helpers are defined so /Ob1 reserves retail's frame slots, including those of calls it declines to inline.

#include <string.h>

namespace _STL
{
template <class CharT>
class char_traits;

template <>
class char_traits<char>
{
public:
	static void assign(char &destination, const char &source);
};
}

struct Rva008312E0InputTag
{
};

struct Rva008312E0Tag : public Rva008312E0InputTag
{
};

struct Rva008312E0FalseType
{
};

template <class _RandomAccessIterator>
inline int __distance(const _RandomAccessIterator &__first,
	const _RandomAccessIterator &__last, const Rva008312E0Tag &)
{
	return __last - __first;
}

template <class _InputIterator>
inline int distance(const _InputIterator &__first, const _InputIterator &__last)
{
	return __distance(__first, __last, Rva008312E0Tag());
}

template <class _RandomAccessIterator, class _Distance>
inline void __advance(_RandomAccessIterator &__i, _Distance __n, const Rva008312E0Tag &)
{
	__i += __n;
}

template <class _InputIterator, class _Distance>
inline void advance(_InputIterator &__i, _Distance __n)
{
	__advance(__i, __n, Rva008312E0Tag());
}

class Rva008312E0String
{
public:
	Rva008312E0String &bfmeReplaceAliasedRange(char *first, char *last,
		char *sourceFirst, char *sourceLast, const Rva008312E0Tag &tag);

	// Out of line in retail (thunk 0x00007C1B); the body mirrors STLport's erase.
	char *erase(char *__first, char *__last)
	{
		if (__first != __last)
		{
			move(__first, __last, (m_finish - __last) + 1);
			char *__new_finish = m_finish - (__last - __first);
			m_finish = __new_finish;
		}
		return __first;
	}

	// Forward-iterator insert at retail 0x008300B0.
	void insertRange(char *position, char *first, char *last, const Rva008312E0Tag &tag);

	// Out of line in retail at 0x00830CC0: the plain forward-iterator replace.
	Rva008312E0String &replaceBase(char *__first, char *__last, char *__f,
		char *__l, const Rva008312E0Tag &)
	{
		int __n = distance(__f, __l);
		const int __len = __last - __first;
		if (__len >= __n)
		{
			copyRange(__f, __l, __first);
			erase(__first + __n, __last);
		}
		else
		{
			char *__m = __f;
			advance(__m, __len);
			copyRange(__f, __m, __first);
			insert(__last, __m, __l);
		}
		return *this;
	}

	char *begin() { return m_start; }
	bool inside(const char *s) const { const char *p = s; return p >= m_start && p < m_finish; }
	void copyRange(char *first, char *last, char *result)
	{
		for ( ; first != last; ++first, ++result)
			_STL::char_traits<char>::assign(*result, *first);
	}
	void insertDispatch(char *position, char *first, char *last, const Rva008312E0FalseType &)
	{
		insertRange(position, first, last, Rva008312E0Tag());
	}
	void insert(char *position, char *first, char *last)
	{
		insertDispatch(position, first, last, Rva008312E0FalseType());
	}
	static char *move(char *s1, const char *s2, size_t n)
	{
		return n == 0 ? s1 : (char *)memmove(s1, s2, n);
	}

	char *m_start;
	char *m_finish;
};

Rva008312E0String &Rva008312E0String::bfmeReplaceAliasedRange(char *first, char *last,
	char *sourceFirst, char *sourceLast, const Rva008312E0Tag &tag)
{
	if (inside(sourceFirst))
	{
		int __n = sourceLast - sourceFirst;
		const int __len = last - first;
		if (__len >= __n)
		{
			copyRange(sourceFirst, sourceLast, first);
			erase(first + __n, last);
		}
		else
		{
			char *__m = sourceFirst + __len;
			if (sourceLast <= first || sourceFirst >= last)
			{
				copyRange(sourceFirst, __m, first);
				insert(last, __m, sourceLast);
			}
			else
			{
				// Offsets survive a reallocation inside insert.
				const int __off_dest = first - begin();
				const int __off_src = sourceFirst - begin();
				insert(last, __m, sourceLast);
				move(begin() + __off_dest, begin() + __off_src, __n);
			}
		}
		return *this;
	}
	else
		return replaceBase(first, last, sourceFirst, sourceLast, Rva008312E0Tag());
}
