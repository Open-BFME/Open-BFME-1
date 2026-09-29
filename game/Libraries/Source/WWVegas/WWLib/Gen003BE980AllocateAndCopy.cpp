// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x003BE980 is the STLport vector<Gen_t_003c0ce0_p2pod>
// _M_allocate_and_copy body called by reserve in tgrid_114.cpp. The
// Gen_t_003c0ce0_p2pod record is two bytes wide, so the allocator branches and
// the copy loop both use a two-byte stride. The retail calls at 0x00881F30 and
// 0x0082E540 select the large and small allocation paths.

namespace _STL
{
// The node allocator's pool entry points are private STLport members
// (_STL::__node_alloc<true, 0>::_M_allocate at 0x0082E540, _M_deallocate at
// 0x0082E5F0); these TU-local helpers reach them under their real names.
template <bool __threads, int __inst> class __node_alloc;
static void *vectorSmallAllocate(unsigned int bytes);
template <bool __threads, int __inst>
class __node_alloc
{
	friend void *vectorSmallAllocate(unsigned int);
	static void *__cdecl _M_allocate(unsigned int __n);
	static void __cdecl _M_deallocate(void *__p, unsigned int __n);
};
static inline void *vectorLargeAllocate(unsigned int bytes) { return ::operator new(bytes); }
static inline void *vectorSmallAllocate(unsigned int bytes) { return __node_alloc<true, 0>::_M_allocate(bytes); }

template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
protected:
	template <class Iterator>
	Type *_M_allocate_and_copy(unsigned int, Iterator, Iterator);
};

template <class Type, class Allocator>
template <class Iterator>
Type *vector<Type, Allocator>::_M_allocate_and_copy(
	unsigned int count, Iterator first, Iterator last)
{
	Type *result;
	if (count)
	{
		unsigned int bytes = count * sizeof(Type);
		if (bytes > 128)
			result = (Type *)vectorLargeAllocate(bytes);
		else
			result = (Type *)vectorSmallAllocate(bytes);
	}
	else
	{
		result = 0;
	}

	Type *source = first;
	Type *end = last;
	if (source != end)
	{
		int offset = (char *)result - (char *)source;
		do
		{
			if ((Type *)((char *)source + offset) != 0)
				*(short *)((char *)source + offset) = source->a;
			++source;
		}
		while (source != end);
	}
	return result;
}
}

struct Gen_t_003c0ce0_p2pod
{
	short a;
};

template Gen_t_003c0ce0_p2pod *_STL::vector<Gen_t_003c0ce0_p2pod,
	_STL::allocator<Gen_t_003c0ce0_p2pod> >::_M_allocate_and_copy<
	Gen_t_003c0ce0_p2pod *>(unsigned int, Gen_t_003c0ce0_p2pod *,
	Gen_t_003c0ce0_p2pod *);
