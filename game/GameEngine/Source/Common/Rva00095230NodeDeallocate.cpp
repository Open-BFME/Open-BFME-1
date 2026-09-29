// cl: /DNDEBUG /MD /EHs-c-
// Retail 0x00095230, the STLport node allocator's eight-byte element
// deallocator. The carved body has two stack arguments and ret 8. Its
// threshold branch calls operator delete above 0x80 bytes and
// __node_alloc<true, 0>::_M_deallocate below that threshold.

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

void operator delete( void *p );

void __stdcall Rva00095230NodeDeallocate( void *p, UnsignedInt count )
{
	if ( p == 0 )
		return;

	UnsignedInt bytes = count * 8;
	if ( bytes > 0x80 )
	{
		operator delete( p );
		return;
	}

	_STL::nodePoolDeallocate( p, bytes );
}
