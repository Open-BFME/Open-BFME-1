// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::basic_string<char>::reserve, retail 0x0053A100, 177 bytes.
// The body carried only a machine byte-dump row; targets/game/reverse/reloc_names.csv holds
// the name with identity=real.
//
// The same BFME-shaped reserve as the wide twin at 0x00839590 -- early return
// below capacity, grow to res_arg + 1 flat, no unwind frame -- but this
// translation unit inlines everything the wide one called out of line:
//
//   * the allocator's small/large branch is open in the body, because with a
//     one-byte element the byte count is the count and not a folded constant;
//   * the same branch appears again on the way out, in _M_deallocate_block;
//   * uninitialized_copy is a memcpy through the import table, with the new
//     finish computed as the returned destination plus the length.
//
// That is why 177 bytes here against 110 there for the same source.

extern "C" __declspec(dllimport) void *__cdecl BfmeMemMove(void *dest, const void *src, unsigned int count);

namespace _STL
{

void *__cdecl vectorLargeAllocate(unsigned int bytes);		// retail 0x00881F30
void *__cdecl vectorSmallAllocate(unsigned int bytes);		// retail 0x0082E540
void __cdecl vectorLargeDeallocate(void *p);			// retail 0x00881EB0

template <bool threads, int inst>
class __node_alloc
{
public:
	static void _M_deallocate(void *p, unsigned int bytes);	// retail 0x0082E5F0
};

template <class T>
class char_traits {};

template <class T>
class allocator
{
public:
	// Written with a single exit on purpose: two returns let MSVC share one
	// epilogue between the arms, where retail repeats the stack fixup and the
	// move in each of them.
	T *allocate(unsigned int n)
	{
		T *result;
		if (n != 0)
		{
			unsigned int bytes = n * sizeof(T);
			if (bytes > 128)
				result = (T *)vectorLargeAllocate(bytes);
			else
				result = (T *)vectorSmallAllocate(bytes);
		}
		else
		{
			result = 0;
		}
		return result;
	}

	// The byte count is taken before the null test, not inside it: written the
	// other way round MSVC sinks the subtraction past the test, which is the
	// one place this body and retail disagreed.
	void deallocate(T *p, unsigned int n)
	{
		unsigned int bytes = n * sizeof(T);
		if (p != 0)
		{
			if (bytes > 128)
				vectorLargeDeallocate(p);
			else
				__node_alloc<true, 0>::_M_deallocate(p, bytes);
		}
	}
};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	Pointer _M_data;
};

// Spelled the way STLport's own __copy_trivial is, as a conditional
// expression rather than an early return: written with an if, MSVC keeps the
// end pointer in the accumulator and subtracts in place, where retail copies
// it aside first.
inline void *__copy_trivial(const void *first, const void *last, void *result)
{
	return (last == first) ? result :
		((char *)BfmeMemMove(result, first, ((const char *)last - (const char *)first))) +
		((const char *)last - (const char *)first);
}

template <class T>
inline T *uninitialized_copy(const T *first, const T *last, T *result)
{
	return (T *)__copy_trivial(first, last, result);
}

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

// ?reserve@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEXI@Z
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

template void basic_string<char, char_traits<char>, allocator<char> >::reserve(unsigned int);

}
