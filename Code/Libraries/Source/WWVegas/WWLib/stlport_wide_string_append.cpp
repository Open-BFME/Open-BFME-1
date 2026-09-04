// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: _STL::basic_string<wchar>::append(first, last, forward_iterator_tag),
// retail 0x004D4FC0, 338 bytes. Converted from gen-dump d_004d4fc0. Named by
// three matched callers in PopupHostGame.cpp: append<PBG> at 0x004D55A0,
// _M_append_dispatch<PBG> at 0x004D5590, and assign(PBG,PBG) at 0x004D5600.
//
// Same inlined allocator / memmove shape as stlport_narrow_string_reserve.cpp,
// without the stock STLport max_size / _M_throw_length_error guard. The grow
// length is old_size + max(old_size, n) + 1.

extern "C" __declspec(dllimport) void *__cdecl BfmeMemMove(void *dest, const void *src, unsigned int count);

namespace _STL
{

void *__cdecl vectorLargeAllocate(unsigned int bytes);
void *__cdecl vectorSmallAllocate(unsigned int bytes);
void __cdecl vectorLargeDeallocate(void *p);

template <bool threads, int inst>
class __node_alloc
{
public:
	static void _M_deallocate(void *p, unsigned int bytes);
};

template <class T>
class char_traits {};

template <class T>
class allocator
{
public:
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

	void deallocate(T *p, unsigned int n)
	{
		if (p != 0)
		{
			unsigned int bytes = n * sizeof(T);
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

struct input_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};

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
	typedef int difference_type;
	typedef CharT *pointer;

	basic_string &append(const CharT *first, const CharT *last,
		const forward_iterator_tag &);

	private:
	template <class InputIterator>
	basic_string &append(InputIterator first, InputIterator last,
		const forward_iterator_tag &);

	public:
	size_type size(void) const
	{
		return (size_type)(_M_finish - _M_start);
	}

	size_type capacity(void) const
	{
		return (size_type)(_M_end_of_storage._M_data - _M_start) - 1;
	}

	pointer end(void) { return _M_finish; }

private:
	void _M_construct_null(CharT *p) { *p = 0; }

	void _M_deallocate_block(void)
	{
		_M_end_of_storage.deallocate(_M_start,
			(size_type)(_M_end_of_storage._M_data - _M_start));
	}

	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, allocator<CharT> > _M_end_of_storage;
};

// ??$append@PBG@?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@_STL@@AAEAAV01@PBG0ABUforward_iterator_tag@1@@Z
template <class CharT, class Traits, class Alloc>
basic_string<CharT, Traits, Alloc> &
basic_string<CharT, Traits, Alloc>::append(const CharT *first, const CharT *last,
	const forward_iterator_tag &)
{
	const CharT *l = last;
	const CharT *f = first;
	if (f != l)
	{
		const size_type old_size = size();
		difference_type n = l - f;
		if (old_size + (size_type)n > capacity())
		{
			size_type n_sz = (size_type)n;
			size_type mx = *(old_size < n_sz ? &n_sz : &old_size);
			const size_type len = old_size + mx + 1;
			pointer new_start = _M_end_of_storage.allocate(len);
			pointer new_finish = uninitialized_copy(_M_start, _M_finish, new_start);
			new_finish = uninitialized_copy(f, l, new_finish);
			_M_construct_null(new_finish);
			_M_deallocate_block();
			_M_start = new_start;
			_M_finish = new_finish;
			_M_end_of_storage._M_data = new_start + len;
		}
		else
		{
			const CharT *f1 = f;
			++f1;
			uninitialized_copy(f1, l, _M_finish + 1);
			_M_construct_null(_M_finish + n);
			*_M_finish = *f;
			_M_finish += n;
		}
	}
	return *this;
}

template <class CharT, class Traits, class Alloc>
template <class InputIterator>
basic_string<CharT, Traits, Alloc> &
basic_string<CharT, Traits, Alloc>::append(InputIterator first, InputIterator last,
	const forward_iterator_tag &)
{
	const CharT *l = last;
	const CharT *f = first;
	if (f != l)
	{
		const typename basic_string<CharT, Traits, Alloc>::size_type old_size = size();
		difference_type n = l - f;
		if (old_size + (size_type)n > capacity())
		{
			size_type n_sz = (size_type)n;
			size_type mx = *(old_size < n_sz ? &n_sz : &old_size);
			const size_type len = old_size + mx + 1;
			pointer new_start = _M_end_of_storage.allocate(len);
			pointer new_finish = uninitialized_copy(_M_start, _M_finish, new_start);
			new_finish = uninitialized_copy(f, l, new_finish);
			_M_construct_null(new_finish);
			_M_deallocate_block();
			_M_start = new_start;
			_M_finish = new_finish;
			_M_end_of_storage._M_data = new_start + len;
		}
		else
		{
			const CharT *f1 = f;
			++f1;
			uninitialized_copy(f1, l, _M_finish + 1);
			_M_construct_null(_M_finish + n);
			*_M_finish = *f;
			_M_finish += n;
		}
	}
	return *this;
}

template basic_string<unsigned short, char_traits<unsigned short>,
	allocator<unsigned short> > &
basic_string<unsigned short, char_traits<unsigned short>,
	allocator<unsigned short> >::append(const unsigned short *,
	const unsigned short *, const forward_iterator_tag &);

template basic_string<unsigned short, char_traits<unsigned short>,
	allocator<unsigned short> > &
basic_string<unsigned short, char_traits<unsigned short>,
	allocator<unsigned short> >::append<unsigned short *>(unsigned short *,
	unsigned short *, const forward_iterator_tag &);

}
