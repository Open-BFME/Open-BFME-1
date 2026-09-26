// ?do_transform@?$collate@G@_STL@@MBE?AV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@2@PBG0@Z
// partial score=0.99 date=2026-09-11
// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// STLport 4.5.3 collate<char/wchar_t>::do_transform.

namespace _STL
{

struct input_iterator_tag {};
struct forward_iterator_tag : input_iterator_tag {};
struct bidirectional_iterator_tag : forward_iterator_tag {};
struct random_access_iterator_tag : bidirectional_iterator_tag {};

template <class T>
inline random_access_iterator_tag iterator_category(const T *)
{
	return random_access_iterator_tag();
}

struct __false_type {};

template <class T>
struct _Is_integer
{
	typedef __false_type _Integral;
};

template <class Iterator>
struct iterator_traits;

template <class T>
struct iterator_traits<T *>
{
	typedef random_access_iterator_tag iterator_category;
};

template <class T>
class allocator {};

template <class T>
class char_traits {};

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
	typedef Alloc allocator_type;

	_String_base(const allocator_type &a)
		: _M_start(0), _M_finish(0), _M_end_of_storage(a, (T *)0) {}
	~_String_base();

	T *_M_start;
	T *_M_finish;
	_STLP_alloc_proxy<T *, T, allocator_type> _M_end_of_storage;
};

template <class CharT, class Traits, class Alloc>
class basic_string : protected _String_base<CharT, Alloc>
{
public:
	typedef Alloc allocator_type;
	~basic_string();

	template <class InputIterator>
	__forceinline basic_string(InputIterator first, InputIterator last)
		: _String_base<CharT, Alloc>(allocator_type())
	{
		typedef typename _Is_integer<InputIterator>::_Integral Integral;
		_M_initialize_dispatch(first, last, Integral());
	}

private:
	template <class InputIterator>
	void _M_initialize_dispatch(InputIterator first,
		InputIterator last, const __false_type &)
	{
		_M_range_initialize(first, last);
	}

	template <class InputIterator>
	void _M_range_initialize(InputIterator first, InputIterator last,
		const forward_iterator_tag &tag);

	template <class InputIterator>
	void _M_range_initialize(InputIterator first,
		InputIterator last)
	{
		_M_range_initialize(first, last, iterator_category(first));
	}
};

typedef basic_string<char, char_traits<char>, allocator<char> > string;
typedef unsigned short wchar_t;
typedef basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> > wstring;

template <class CharT> class collate;

template <>
class collate<char>
{
protected:
	virtual string do_transform(const char *low, const char *high) const;
};

template <>
class collate<wchar_t>
{
protected:
	virtual wstring do_transform(const wchar_t *low, const wchar_t *high) const;
};

string collate<char>::do_transform(const char *low, const char *high) const
{
	return string(low, high);
}

wstring collate<wchar_t>::do_transform(const wchar_t *low,
	const wchar_t *high) const
{
	return wstring(low, high);
}

}
