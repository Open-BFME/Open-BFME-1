// cl: /DNDEBUG /MD /EHs-c-
// Retail 0x00095230, the STLport node allocator's eight-byte element
// deallocator. The carved body has two stack arguments and ret 8. Its
// threshold branch calls operator delete above 0x80 bytes and
// __node_alloc<true, 0>::_M_deallocate below that threshold.

typedef unsigned int UnsignedInt;

namespace _STL
{
	template <bool threads, int inst>
	class __node_alloc
	{
	public:
		static void _M_deallocate( void *p, UnsignedInt size );
	};
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

	_STL::__node_alloc<true, 0>::_M_deallocate( p, bytes );
}
