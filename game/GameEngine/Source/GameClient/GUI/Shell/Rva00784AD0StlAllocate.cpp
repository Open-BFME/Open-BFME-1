// cl: /O2

namespace _STL
{
	// Retail 0x0082E540 is the matched node pool refill/mutex body.
static __forceinline void *vectorSmallAllocate(unsigned int bytes);
template <bool Threads, int Instance>
class __node_alloc
{
	static void *__cdecl _M_allocate(unsigned int bytes);
	friend void *vectorSmallAllocate(unsigned int bytes);
};
static __forceinline void *vectorSmallAllocate(unsigned int bytes)
{
	return __node_alloc<true, 0>::_M_allocate(bytes);
}
}

void *operator new(unsigned int bytes);

void *__stdcall Rva00784AD0StlAllocate(unsigned int count, const void *)
{
	if (count != 0)
	{
		unsigned int bytes = count * 4;
		if (bytes > 0x80)
			return ::operator new(bytes);

		return _STL::vectorSmallAllocate(bytes);
	}

	return 0;
}
