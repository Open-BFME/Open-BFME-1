// ?do_transform@?$collate@D@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@PBD0@Z
// partial score=0.99 date=2026-09-11
// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// STLport 4.5.3 src/collate.cpp: collate<char>::do_transform.

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

struct input_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};
struct __false_type {};

template <class Iterator>
struct iterator_traits;

template <class T>
struct iterator_traits<T *>
{
	typedef random_access_iterator_tag iterator_category;
};

template <class T>
struct iterator_traits<const T *>
{
	typedef random_access_iterator_tag iterator_category;
};

template <class T>
struct _Is_integer
{
	typedef __false_type _Integral;
};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	_STLP_alloc_proxy(const Alloc &alloc, Pointer value) : Alloc(alloc), _M_data(value) {}

	Pointer _M_data;
};

template <class T, class Alloc>
class _String_base
{
public:
	typedef Alloc allocator_type;

	_String_base(const allocator_type &value) :
		_M_start(0), _M_finish(0), _M_end_of_storage(value, (T *)0)
	{
	}

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

	template <class InputIterator>
	__forceinline basic_string(InputIterator first, InputIterator last) :
		_String_base<CharT, Alloc>(allocator_type())
	{
		typedef typename _Is_integer<InputIterator>::_Integral _Integral;
		_M_initialize_dispatch(first, last, _Integral());
	}

private:
	template <class InputIterator>
	void _M_range_initialize(InputIterator first, InputIterator last,
		const forward_iterator_tag &);

	template <class InputIterator>
	void _M_range_initialize(InputIterator first, InputIterator last)
	{
		_M_range_initialize(first, last,
			typename iterator_traits<InputIterator>::iterator_category());
	}

	template <class InputIterator>
	void _M_initialize_dispatch(InputIterator first,
		InputIterator last, const __false_type &)
	{
		_M_range_initialize(first, last);
	}
};

template <class CharT>
class collate
{
};

template <>
class collate<char>
{
public:
	typedef basic_string<char, char_traits<char>, allocator<char> > string_type;

protected:
	virtual string_type do_transform(const char *, const char *) const;
};

collate<char>::string_type
collate<char>::do_transform(const char *low, const char *high) const
{
	return string_type(low, high);
}
}
