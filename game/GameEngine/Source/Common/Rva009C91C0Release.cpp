namespace _STL
{
// The node allocator's pool entry points are private STLport members
// (_STL::__node_alloc<true, 0>::_M_allocate at 0x0082E540, _M_deallocate at
// 0x0082E5F0); these TU-local helpers reach them under their real names.
template <bool __threads, int __inst> class __node_alloc;
static void nodePoolDeallocate(void *block, unsigned int bytes);
template <bool __threads, int __inst>
class __node_alloc
{
	friend void nodePoolDeallocate(void *, unsigned int);
	static void *__cdecl _M_allocate(unsigned int __n);
	static void __cdecl _M_deallocate(void *__p, unsigned int __n);
};
static inline void nodePoolDeallocate(void *block, unsigned int bytes) { __node_alloc<true, 0>::_M_deallocate(block, bytes); }
}

void __cdecl operator delete(void *block);

struct Rva009C91C0Element
{
	char bytes[0x30];
};

// ?Rva009C91C0Release@@YGXPAXI@Z
void __stdcall Rva009C91C0Release(void *block, unsigned int count)
{
	if (block)
	{
		unsigned int bytes = count * sizeof(Rva009C91C0Element);
		if (bytes > 0x80)
			operator delete(block);
		else
			_STL::nodePoolDeallocate(block, bytes);
	}
}
