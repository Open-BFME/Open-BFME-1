// ?Rva004F1210Deallocate@@YGXPAXI@Z
// cl: /DNDEBUG /MD /EHs-c-

typedef unsigned int UnsignedInt;

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

void operator delete(void *pointer);

// The caller evidence proves a two-argument allocator helper. Its semantic
// owner remains unknown, so the function keeps the retail address in its name.
void __stdcall Rva004F1210Deallocate(void *pointer, UnsignedInt count)
{
	if (pointer != 0)
	{
		UnsignedInt bytes = count * 0x338;

		if (bytes > 0x80)
		{
			operator delete(pointer);
			return;
		}

		_STL::nodePoolDeallocate(pointer, bytes);
	}
}
