// cl: /MD

#include <string.h>

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
};

namespace _STL
{
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

class ObjectPointerAllocateAndCopyShim
{
public:
	Object **allocate_and_copy(unsigned int n, Object *const *first, Object *const *last);
};

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

template <class Type, class Allocator>
template <class Iterator>
Type *vector<Type, Allocator>::_M_allocate_and_copy(unsigned int n, Iterator first, Iterator last)
{
	return (Type *)((ObjectPointerAllocateAndCopyShim *)this)->allocate_and_copy(
		n, (Object *const *)first, (Object *const *)last);
}

template Object **vector<Object *, allocator<Object *> >::_M_allocate_and_copy<Object *const *>(
	unsigned int, Object *const *, Object *const *);

// ?allocate_and_copy@ObjectPointerAllocateAndCopyShim@_STL@@QAEPAPAVObject@@IPBQAV3@0@Z present-unmatched
__declspec(noinline) Object **ObjectPointerAllocateAndCopyShim::allocate_and_copy(
	unsigned int n, Object *const *first, Object *const *last)
{
	Object **result;
	if (n)
	{
		unsigned int bytes = n * sizeof(Object *);
		if (bytes > 128)
			result = (Object **)vectorLargeAllocate(bytes);
		else
			result = (Object **)vectorSmallAllocate(bytes);
	}
	else
	{
		result = 0;
	}

	if (last != first)
	{
		memmove(result, first, (unsigned int)((const char *)last - (const char *)first));
	}

	return result;
}
}
