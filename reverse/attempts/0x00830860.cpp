// ??0?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@PBDIABV?$allocator@D@1@@Z
// partial score=0.97 date=2026-09-10
// cl: /Od /EHsc /Ob2

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
	void _M_range_initialize(const CharT *, const CharT *, const forward_iterator_tag &);
};

template <class CharT, class Traits, class Alloc>
basic_string<CharT, Traits, Alloc>::basic_string(
	const CharT *text, size_type count, const allocator_type &a)
	: _String_base<CharT, Alloc>(a)
{
	char padding0[4];
	char padding1[4];
	_M_range_initialize(text, text + count, forward_iterator_tag());
}

template basic_string<char, char_traits<char>, allocator<char> >::basic_string(
	const char *, unsigned, const allocator<char> &);

}
