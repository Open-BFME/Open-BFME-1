// cl: /Od /Ob1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport-style const char range replace at retail 0x008314E0 that handles a source range inside the string.
// Inline helpers are defined so /Ob1 reserves retail's frame slots, including those of calls it declines to inline.

#include <string.h>
#include <memory>

#pragma intrinsic(memcpy)

struct BfmeRangeInputTag
{
};

struct BfmeRangeTag : public BfmeRangeInputTag
{
};

struct BfmeRangeFalseType
{
};

template <class _RandomAccessIterator>
inline int __distance(const _RandomAccessIterator &__first,
	const _RandomAccessIterator &__last, const BfmeRangeTag &)
{
	return __last - __first;
}

template <class _InputIterator>
inline int distance(const _InputIterator &__first, const _InputIterator &__last)
{
	return __distance(__first, __last, BfmeRangeTag());
}

template <class _RandomAccessIterator, class _Distance>
inline void __advance(_RandomAccessIterator &__i, _Distance __n, const BfmeRangeTag &)
{
	__i += __n;
}

template <class _InputIterator, class _Distance>
inline void advance(_InputIterator &__i, _Distance __n)
{
	__advance(__i, __n, BfmeRangeTag());
}

struct BfmeRangeTrueType
{
};

template <class _Tp>
inline _Tp *bfmeValueType(const _Tp *, const BfmeRangeTrueType &)
{
	return (_Tp *)0;
}

template <class _ForwardIterator>
inline void bfmeDestroyAux(_ForwardIterator, _ForwardIterator, const BfmeRangeTrueType &)
{
}

template <class _ForwardIterator, class _Tp>
inline void bfmeDestroyTyped(_ForwardIterator __first, _ForwardIterator __last, _Tp *)
{
	bfmeDestroyAux(__first, __last, BfmeRangeTrueType());
}

template <class _ForwardIterator>
inline void bfmeDestroy(_ForwardIterator __first, _ForwardIterator __last)
{
	bfmeDestroyTyped(__first, __last, bfmeValueType(__first, BfmeRangeTrueType()));
}

class Rva008314E0String
{
public:
	Rva008314E0String &replaceRange(char *first, char *last,
		char *sourceFirst, char *sourceLast, const BfmeRangeTag &tag);

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

	// Forward-iterator insert, out of line in retail at 0x00830410; this body models the slots it reserves.
	void insertRange(char *__position, char *__first, char *__last, const BfmeRangeTag &)
	{
		if (__first != __last)
		{
			int __n = distance(__first, __last);
			if (m_endOfStorage - m_finish >= __n + 1)
			{
				const int __elems_after = m_finish - __position;
				char *__old_finish = m_finish;
				if (__elems_after >= __n)
				{
					_STL::uninitialized_copy((m_finish - __n) + 1, m_finish + 1, m_finish + 1);
					m_finish += __n;
					move(__position + __n, __position, (__elems_after - __n) + 1);
					copyIter(__first, __last, __position);
				}
				else
				{
					char *__mid = __first;
					advance(__mid, __elems_after + 1);
					uninitializedCopyFwd(__mid, __last, m_finish + 1);
					m_finish += __n - __elems_after;
					_STL::uninitialized_copy(__position, __old_finish + 1, m_finish);
					m_finish += __elems_after;
					copyIter(__first, __mid, __position);
				}
			}
			else
			{
				const unsigned int __old_size = size();
				const unsigned int __len = __old_size + maxOf(__old_size, (unsigned int)__n) + 1;
				char *__new_start = allocate(__len);
				char *__new_finish = __new_start;
				__new_finish = _STL::uninitialized_copy(m_start, __position, __new_start);
				__new_finish = uninitializedCopyFwd(__first, __last, __new_finish);
				__new_finish = _STL::uninitialized_copy(__position, m_finish, __new_finish);
				constructNull(__new_finish);
				bfmeDestroy(m_start, m_finish + 1);
				deallocateBlock();
				m_start = __new_start;
				m_finish = __new_finish;
				m_endOfStorage = __new_start + __len;
			}
		}
	}
	unsigned int size() const { return m_finish - m_start; }
	template <class _InputIter>
	static void copyIter(_InputIter __first, _InputIter __last, char *__result)
	{
		move(__result, __first, __last - __first);
	}
	static char *uninitializedCopyFwd(const char *first, const char *last, char *result);
	static char *allocateLarge(unsigned int n);
	static char *allocateNode(unsigned int n);
	static char *allocate(unsigned int n)
	{
		return n != 0 ? (n > 128 ? allocateLarge(n) : allocateNode(n)) : 0;
	}
	static const unsigned int &maxOf(const unsigned int &a, const unsigned int &b)
	{
		return a < b ? b : a;
	}
	void constructNullAux(char *p, const BfmeRangeFalseType &) { *p = 0; }
	void constructNull(char *p) { constructNullAux(p, BfmeRangeFalseType()); }
	void deallocateBlock();

	// Out of line in retail at 0x00830DE0: the plain forward-iterator replace.
	Rva008314E0String &replaceBase(char *__first, char *__last, char *__f,
		char *__l, const BfmeRangeTag &)
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
	static void copyRange(const char *first, const char *last, char *result)
	{
		copy(result, first, last - first);
	}
	static void moveRange(const char *first, const char *last, char *result)
	{
		move(result, first, last - first);
	}
	void insertDispatch(char *position, char *first, char *last, const BfmeRangeFalseType &)
	{
		insertRange(position, first, last, BfmeRangeTag());
	}
	void insert(char *position, char *first, char *last)
	{
		insertDispatch(position, first, last, BfmeRangeFalseType());
	}
	static char *move(char *s1, const char *s2, size_t n)
	{
		return n == 0 ? s1 : (char *)memmove(s1, s2, n);
	}
	static char *copy(char *s1, const char *s2, size_t n)
	{
		return n == 0 ? s1 : (char *)memcpy(s1, s2, n);
	}

	char *m_start;
	char *m_finish;
	char *m_endOfStorage;
};

Rva008314E0String &Rva008314E0String::replaceRange(char *first, char *last,
	char *sourceFirst, char *sourceLast, const BfmeRangeTag &tag)
{
	if (inside(sourceFirst))
	{
		int __n = sourceLast - sourceFirst;
		const int __len = last - first;
		if (__len >= __n)
		{
			moveRange(sourceFirst, sourceLast, first);
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
		return replaceBase(first, last, sourceFirst, sourceLast, BfmeRangeTag());
}
