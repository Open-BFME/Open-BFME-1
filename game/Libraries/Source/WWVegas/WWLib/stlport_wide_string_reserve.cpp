// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::basic_string<wchar>::reserve, retail 0x00839590, 110
// bytes. The body carried only a machine byte-dump row;
// targets/game/reverse/reloc_names.csv holds the name with identity=real.
//
// This is not stock STLport reserve. Vanilla checks max_size and throws, then
// grows to max(res_arg, size()) + 1 unconditionally. BFME's returns early when
// the request is below the current capacity and grows to res_arg + 1 flat, and
// there is no unwind frame at all, so the _STLP_TRY around the copy is gone
// too.
//
// The allocator is the node allocator reached through the proxy: allocate
// null-checks the count before asking for count * 2 bytes, and deallocate
// null-checks the pointer. The redundant halve-then-double on the way into
// deallocate is the compiler turning the pointer difference back into a byte
// count.

namespace _STL
{

template <bool threads, int inst>
class __node_alloc
{
public:
	static void *allocate(unsigned int bytes);		// retail 0x00061CE0
	static void deallocate(void *p, unsigned int bytes);	// retail 0x00061D10
};

template <class T>
class allocator
{
public:
	T *allocate(unsigned int n)
	{
		return n != 0 ? (T *)__node_alloc<true, 0>::allocate(n * sizeof(T)) : 0;
	}

	void deallocate(T *p, unsigned int n)
	{
		if (p != 0)
			__node_alloc<true, 0>::deallocate(p, n * sizeof(T));
	}
};

template <class T>
class char_traits {};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	Pointer _M_data;
};

template <class InputIter, class ForwardIter>
ForwardIter uninitialized_copy(InputIter first, InputIter last, ForwardIter result);

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	typedef unsigned int size_type;
	typedef CharT *pointer;

	void reserve(size_type resArg);

	size_type capacity(void) const
	{
		return (size_type)(_M_end_of_storage._M_data - _M_start) - 1;
	}

private:
	void _M_construct_null(CharT *p) { *p = 0; }

	void _M_deallocate_block(void)
	{
		_M_end_of_storage.deallocate(_M_start,
			(size_type)(_M_end_of_storage._M_data - _M_start));
	}

	CharT *_M_start;					// +0x00
	CharT *_M_finish;					// +0x04
	_STLP_alloc_proxy<CharT *, CharT, allocator<CharT> > _M_end_of_storage;	// +0x08
};

// ?reserve@?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@_STL@@QAEXI@Z
template <class CharT, class Traits, class Alloc>
void basic_string<CharT, Traits, Alloc>::reserve(size_type resArg)
{
	if (resArg < capacity())
		return;

	size_type n = resArg + 1;
	pointer newStart = _M_end_of_storage.allocate(n);
	pointer newFinish = uninitialized_copy(_M_start, _M_finish, newStart);
	_M_construct_null(newFinish);

	_M_deallocate_block();

	_M_start = newStart;
	_M_finish = newFinish;
	_M_end_of_storage._M_data = newStart + n;
}

template void basic_string<unsigned short, char_traits<unsigned short>,
	allocator<unsigned short> >::reserve(unsigned int);

}
