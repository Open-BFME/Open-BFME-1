// cl: /DNDEBUG /MD /G6 /EHsc
//
// Retail STL threshold allocator 0x0093D510: a zero count returns null,
// otherwise the count is scaled x3 then x8 (24-byte elements) and sizes
// above 0x80 go through operator new at 0x00881F30 while smaller sizes go
// through __node_alloc<true, 0>::_M_allocate at 0x0082E540. Same nonzero-guard idiom as
// the landed Small03gStlAlloc trio (0x0094C210/0x009A3450/0x0094C1C0).
// IDENTITY IS NOT RECOVERED: the allocator keeps its address token.
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

void *__stdcall Rva0093D510Alloc(unsigned int n, unsigned int tag)
{
	(void)tag;
	unsigned int bytes = n;
	if (bytes != 0)
	{
		bytes = n + n * 2;
		bytes <<= 3;
		if (bytes > 0x80)
			return ::operator new(bytes);
		return _STL::vectorSmallAllocate(bytes);
	}
	return 0;
}
