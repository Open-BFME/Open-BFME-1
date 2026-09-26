// cl: /Od /EHsc /Ob2
// stlport
// STLport basic_string<char> size constructor at retail RVA 0x00830860.

namespace _STL
{

template <class T>
class allocator
{
};

template <class T>
class char_traits
{
};

struct input_iterator_tag
{
};

struct forward_iterator_tag : public input_iterator_tag
{
};

template <class T>
__forceinline void reserveSlots(T *)
{
}

__forceinline void reserveSlots(void)
{
	char padding0[4];
	char padding1[4];
	reserveSlots(padding0);
	reserveSlots(padding1);
}

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy
{
public:
	_STLP_alloc_proxy(const Alloc &, Pointer p) : _M_data(p) {}

	Pointer _M_data;
};

template <class T, class Alloc>
class _String_base
{
public:
	typedef allocator<T> allocator_type;

	__forceinline _String_base(const allocator_type &a)
		: _M_start(0), _M_finish(0), _M_end_of_storage(a, (T *)0) {}

	~_String_base(void);

	T *_M_start;
	T *_M_finish;
	_STLP_alloc_proxy<T *, T, allocator_type> _M_end_of_storage;
};

template <class CharT, class Traits, class Alloc>
class basic_string : protected _String_base<CharT, Alloc>
{
public:
	typedef allocator<CharT> allocator_type;
	typedef unsigned size_type;

	basic_string(const CharT *, size_type, const allocator_type &);

private:
	template <class InputIterator>
	void _M_range_initialize(InputIterator, InputIterator, const forward_iterator_tag &);
	__forceinline void _M_range_initialize(const CharT *first, const CharT *last)
	{
		_M_range_initialize(first, last, forward_iterator_tag());
	}
};

template <class CharT, class Traits, class Alloc>
basic_string<CharT, Traits, Alloc>::basic_string(
	const CharT *text, size_type count, const allocator_type &a)
	: _String_base<CharT, Alloc>(a)
{
	_M_range_initialize(text, text + count);
	reserveSlots();
}

template basic_string<char, char_traits<char>, allocator<char> >::basic_string(
	const char *, unsigned, const allocator<char> &);

}
