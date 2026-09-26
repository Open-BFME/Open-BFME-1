// 15 byte-identical thirty-four-byte __cdecl bodies:
//
//     push esi / mov esi,[esp+8] / push esi / call 0x00897330 /
//     mov eax,[esp+0x10] / add eax,8 / push eax / add esi,-8 / push esi /
//     call dword ptr [0x01337830] / add esp,0xc / pop esi / ret
//
// WHAT THE BODY IS.  Two dword arguments, caller cleanup, nothing returned:
// `f( storage, size )`.  It hands `storage` to the notify call at 0x00897330
// and then frees `storage - 8` with `size + 8` through the run-time deallocator
// pointer at 0x01337830 -- the eight bytes ahead of the object are an
// allocation header, and the size the allocator is told is the object plus that
// header.  That is a class-level `operator delete( void *, size_t )`: MSVC 7.1
// gives a static member operator __cdecl and passes it the class's own size.
//
// WHY 15 COPIES.  All 15 are identical byte for byte -- same constants, same
// two callees -- and sit at 15 distinct addresses, so the linker did not fold
// them.  They are 15 classes' operators, each written out for its own address;
// the same body inlined is what the helpers in HeaderedDeleteDestructors.cpp
// carry, and reading it here is what settles the `+ 8` those helpers fold into
// a single constant.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

extern void ( __cdecl *g_Va01337830 )( void *storage, unsigned int size );

void __cdecl Rva00897330NotifyFree( void *storage );

#define BFME_HEADERED_DELETE_OPERATOR( NAME )                                 \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		static void operator delete( void *storage, unsigned int size );      \
	};                                                                        \
	void NAME::operator delete( void *storage, unsigned int size )            \
	{                                                                         \
		Rva00897330NotifyFree( storage );                                     \
		g_Va01337830( (char *)storage - 8, size + 8 );                        \
	}

BFME_HEADERED_DELETE_OPERATOR( Rva00891650HeaderedDelete )
BFME_HEADERED_DELETE_OPERATOR( Rva00897590HeaderedDelete )
BFME_HEADERED_DELETE_OPERATOR( Rva00897670HeaderedDelete )
BFME_HEADERED_DELETE_OPERATOR( Rva00897790HeaderedDelete )
BFME_HEADERED_DELETE_OPERATOR( Rva008977F0HeaderedDelete )
BFME_HEADERED_DELETE_OPERATOR( Rva00897850HeaderedDelete )
BFME_HEADERED_DELETE_OPERATOR( Rva008978B0HeaderedDelete )
BFME_HEADERED_DELETE_OPERATOR( Rva00897910HeaderedDelete )
BFME_HEADERED_DELETE_OPERATOR( Rva00897970HeaderedDelete )
BFME_HEADERED_DELETE_OPERATOR( Rva008A3160HeaderedDelete )
BFME_HEADERED_DELETE_OPERATOR( Rva008A9120HeaderedDelete )
BFME_HEADERED_DELETE_OPERATOR( Rva008AB870HeaderedDelete )
BFME_HEADERED_DELETE_OPERATOR( Rva008BA800HeaderedDelete )
BFME_HEADERED_DELETE_OPERATOR( Rva008BA870HeaderedDelete )
BFME_HEADERED_DELETE_OPERATOR( Rva008C48C0HeaderedDelete )
