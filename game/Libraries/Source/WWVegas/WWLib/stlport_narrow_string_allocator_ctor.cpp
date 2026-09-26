// cl: /DNDEBUG /MD /EHsc /Od /Ob2

// Open-BFME5: STLport basic_string<char> allocator constructor at retail
// 0x00830700, 124 bytes.
//
// inputs/vendor/stlport/stl/_string.h defines this constructor with an eight-element
// allocation in _String_base, followed by _M_terminate_string in
// basic_string. The decorated signature identifies the narrow STLport
// specialization, and the retail body matches that source structure.

namespace _STL
{

template <class T>
class allocator
{
public:
	allocator(void) __declspec(nothrow) {}
	allocator(const allocator &) __declspec(nothrow) {}
	~allocator(void) __declspec(nothrow) {}
};

template <class T>
class char_traits {};

struct true_type {};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	_STLP_alloc_proxy(const Alloc &a, Pointer p) : Alloc(a), _M_data(p) {}

	Pointer _M_data;
};

template <class T, class Alloc>
class _String_base
{
public:
	typedef allocator<T> allocator_type;
	void _M_allocate_block(unsigned n);

	_String_base(const allocator_type &a)
		: _M_start(0), _M_finish(0), _M_end_of_storage(a, (T *)0) {}

	_String_base(const allocator_type &a, unsigned n)
		: _M_start(0), _M_finish(0), _M_end_of_storage(a, (T *)0)
	{
		_M_allocate_block(n);
	}

	~_String_base(void)
	{
		_M_deallocate_block();
	}

	void _M_deallocate_block(void);

	T *_M_start;
	T *_M_finish;
	_STLP_alloc_proxy<T *, T, allocator_type> _M_end_of_storage;
};

template <class CharT, class Traits, class Alloc>
class basic_string : protected _String_base<CharT, Alloc>
{
public:
	typedef allocator<CharT> allocator_type;

	basic_string(const allocator_type &a);

	void __declspec(nothrow) _M_terminate_string_aux(const true_type &)
	{
		*(this->_M_finish) = 0;
	}

	void __declspec(nothrow) _M_terminate_string(void)
	{
		_M_terminate_string_aux(true_type());
	}
};

template <class CharT, class Traits, class Alloc>
basic_string<CharT, Traits, Alloc>::basic_string(const allocator_type &a)
	: _String_base<CharT, Alloc>(a, 8)
{
	_M_terminate_string();
}

}

inline void *operator new(unsigned int, void *place) { return place; }

void BfmeNarrowStringAllocatorAnchor(void *storage,
	const _STL::allocator<char> &alloc)
{
	new (storage) _STL::basic_string<char, _STL::char_traits<char>,
		_STL::allocator<char> >(alloc);
}
