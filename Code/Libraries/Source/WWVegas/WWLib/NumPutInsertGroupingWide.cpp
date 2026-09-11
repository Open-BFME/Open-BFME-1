// cl: /O2 /EHsc /MD
// STLport 4.5.3 __insert_grouping(wchar_t*,...) at retail 0x00845AA0 (177B).

typedef int ptrdiff_t;

extern "C" __declspec(dllimport) void *__cdecl memmove(void *,
	const void *, unsigned int);

namespace _STL
{

class string
{
public:
	typedef unsigned size_type;
	typedef const char &const_reference;

	size_type size() const { return (size_type)(_M_finish - _M_start); }
	const_reference operator[](unsigned n) const { return _M_start[n]; }

private:
	char *_M_start;
	char *_M_finish;
};

struct __true_type
{
};

inline void *__copy_trivial_backward(const void *first, const void *last,
	void *result)
{
	const ptrdiff_t nbytes = (const char *)last - (const char *)first;
	return nbytes > 0
		? memmove((char *)result - nbytes, first, nbytes)
		: result;
}

template <class InputIter, class OutputIter>
inline OutputIter __copy_backward_ptrs(InputIter first, InputIter last,
	OutputIter result, const __true_type &)
{
	return (OutputIter)__copy_trivial_backward(first, last, result);
}

template <class InputIter, class OutputIter>
inline OutputIter __copy_backward_aux(InputIter first, InputIter last,
	OutputIter result, const __true_type &)
{
	return __copy_backward_ptrs(first, last, result, __true_type());
}

template <class InputIter, class OutputIter>
inline OutputIter copy_backward(InputIter first, InputIter last,
	OutputIter result)
{
	return __copy_backward_aux(first, last, result, __true_type());
}

ptrdiff_t __cdecl __insert_grouping(unsigned short *first,
	unsigned short *last, const string &grouping, unsigned short separator,
	unsigned short Plus, unsigned short Minus, int basechars)
{
	if (first == last)
		return 0;

	int sign = 0;
	if (*first == Plus || *first == Minus)
	{
		sign = 1;
		++first;
	}

	first += basechars;
	string::size_type n = 0;
	unsigned short *cur_group = last;
	int groupsize = 0;
	while (true)
	{
		groupsize = n < grouping.size()
			? (int)(signed char)grouping[n] : groupsize;
		++n;

		if (groupsize <= 0 || groupsize >= (int)(cur_group - first))
			break;

		cur_group -= groupsize;
		++last;
		copy_backward(cur_group, last, last + 1);
		*cur_group = separator;
	}

	return (last - first) + sign + basechars;
}

} // namespace _STL
