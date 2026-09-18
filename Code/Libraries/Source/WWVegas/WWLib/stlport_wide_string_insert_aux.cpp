// ?_M_insert_aux@?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@_STL@@AAEPAGPAGG@Z
// Retail STLport wide-string insertion helper at 0x0083E4D0.
// The begin, finish, and end-of-storage accessors preserve the retail
// register schedule in the growth path.
// cl: /DNDEBUG /MD /EHsc

extern "C" __declspec(dllimport) void *__cdecl BfmeMemMove(
	void *dest, const void *src, unsigned int count);

inline void *operator new(unsigned int, void *p) { return p; }

struct Rva0082C6E0Value
{
	unsigned long m_value;
};

extern Rva0082C6E0Value *__cdecl rva0082C6E0CopyValues(
	Rva0082C6E0Value *first, Rva0082C6E0Value *last,
	Rva0082C6E0Value *result);

namespace _STL
{

template <bool threads, int inst>
class __node_alloc
{
public:
	static void *allocate(unsigned int bytes);
	static void deallocate(void *p, unsigned int bytes);
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
class char_traits
{
public:
	static T *move(T *dest, const T *src, unsigned int n)
	{
		return (T *)BfmeMemMove(dest, src, n * sizeof(T));
	}

	static void assign(T &c1, const T &c2) { c1 = c2; }
};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	Pointer _M_data;
};

template <class InputIter, class ForwardIter>
ForwardIter uninitialized_copy(InputIter first, InputIter last, ForwardIter result)
{
	return (ForwardIter)rva0082C6E0CopyValues(
		(Rva0082C6E0Value *)first, (Rva0082C6E0Value *)last,
		(Rva0082C6E0Value *)result);
}

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	typedef unsigned int size_type;
	typedef CharT *pointer;

	size_type size(void) const
	{
		return (size_type)(finish() - begin());
	}

	pointer begin(void) const { return _M_start; }
	pointer finish(void) const { return _M_finish; }
	pointer end_of_storage(void) const { return _M_end_of_storage._M_data; }

private:
	pointer _M_insert_aux(pointer p, CharT c);

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

template <class CharT, class Traits, class Alloc>
typename basic_string<CharT, Traits, Alloc>::pointer
basic_string<CharT, Traits, Alloc>::_M_insert_aux(pointer p, CharT c)
{
	pointer new_pos = p;
	if (finish() + 1 < end_of_storage())
	{
		_M_construct_null(finish() + 1);
		size_type n = (size_type)(finish() - p);
		if (n != 0)
			Traits::move(p + 1, p, n);
		Traits::assign(*p, c);
		++_M_finish;
	}
	else
	{
		const size_type old_len = size();
		size_type one = 1;
		const size_type &mx = *(old_len < one ? &one : &old_len);
		const size_type len = old_len + mx + 1;
		pointer new_start = _M_end_of_storage.allocate(len);
		new_pos = uninitialized_copy(begin(), p, new_start);
		if (new_pos)
			*new_pos = c;
		pointer new_finish = uninitialized_copy(p, finish(), new_pos + 1);
		_M_construct_null(new_finish);
		_M_deallocate_block();
		_M_start = new_start;
		_M_finish = new_finish;
		_M_end_of_storage._M_data = new_start + len;
	}
	return new_pos;
}

template unsigned short *basic_string<unsigned short, char_traits<unsigned short>,
	allocator<unsigned short> >::_M_insert_aux(unsigned short *, unsigned short);

}
