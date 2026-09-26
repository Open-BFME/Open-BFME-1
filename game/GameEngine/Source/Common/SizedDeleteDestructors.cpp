// 20 thirty-three-byte __thiscall members with one shape:
//
//     push esi / mov esi,ecx / call <destructor> / test byte ptr [esp+8],1 /
//     je +12 / push <SIZE> / push esi / call dword ptr [0x01337830] /
//     add esp,8 / mov eax,esi / pop esi / ret 4
//
// WHAT THE BODY IS.  MSVC 7.1's scalar deleting destructor `??_G` again, but
// the deallocation is not `??3@YAXPAX@Z`: two arguments are pushed -- the
// object and a CONSTANT -- and the call goes indirectly through a pointer in
// .data.  The constant differs per body (4, 12, 16, 24, 28, 36, 48, 56, 120)
// and never appears anywhere else in the body, which is what a SIZED
// deallocation function receives: `operator delete( void *, size_t )` is
// handed sizeof(class), so each constant is that class's size and is what
// fixes the padding declared below.
//
// The indirection is the other half.  A class-level `operator delete` is called
// directly by name; what MSVC emits as `call dword ptr [<address>]` is that
// operator's body being INLINED and the body being a call through a function
// pointer -- a deallocator installed at run time.  Written that way, and only
// that way, the bytes come out as retail's; declared out of line it is a direct
// call, and at `/O1` the two-dword cleanup becomes `pop ecx / pop ecx` instead
// of `add esp,8`.
//
// 20 bodies call 20 distinct destructors.  Each is an address decoded from the
// retail REL32 and pinned in `targets/game/reverse/symbols.csv` under an address-derived
// name; where several bodies share one, that is identical-code folding of
// destructors that do nothing of their own.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

extern void ( __cdecl *g_Va01337830 )( void *storage, unsigned int size );

class SizedDeleteBase
{
public:
	virtual ~SizedDeleteBase();

	static void operator delete( void *storage, unsigned int size )
	{
		g_Va01337830( storage, size );
	}
};

#define BFME_SIZED_DELETE_DTOR( NAME, PAD )                                   \
	class NAME : public SizedDeleteBase                                       \
	{                                                                         \
	public:                                                                   \
		virtual ~NAME();                                                      \
                                                                              \
		char m_pad[ PAD ];                                                    \
	};                                                                        \
	NAME::~NAME()                                                             \
	{                                                                         \
	}

#define BFME_SIZED_DELETE_DTOR_BARE( NAME )                                   \
	class NAME : public SizedDeleteBase                                       \
	{                                                                         \
	public:                                                                   \
		virtual ~NAME();                                                      \
	};                                                                        \
	NAME::~NAME()                                                             \
	{                                                                         \
	}

BFME_SIZED_DELETE_DTOR_BARE( Rva00891D40SizedDeleting )
BFME_SIZED_DELETE_DTOR( Rva00891DA0SizedDeleting, 8 )
BFME_SIZED_DELETE_DTOR( Rva00894350SizedDeleting, 24 )
BFME_SIZED_DELETE_DTOR( Rva00894A60SizedDeleting, 20 )
BFME_SIZED_DELETE_DTOR( Rva008952F0SizedDeleting, 20 )
BFME_SIZED_DELETE_DTOR( Rva008960D0SizedDeleting, 12 )
BFME_SIZED_DELETE_DTOR( Rva008976F0SizedDeleting, 12 )
BFME_SIZED_DELETE_DTOR( Rva00899670SizedDeleting, 8 )
BFME_SIZED_DELETE_DTOR( Rva008A11A0SizedDeleting, 8 )
BFME_SIZED_DELETE_DTOR( Rva008A3030SizedDeleting, 52 )
BFME_SIZED_DELETE_DTOR( Rva008A4C90SizedDeleting, 8 )
BFME_SIZED_DELETE_DTOR( Rva008A9B60SizedDeleting, 12 )
BFME_SIZED_DELETE_DTOR( Rva008BD7B0SizedDeleting, 44 )
BFME_SIZED_DELETE_DTOR( Rva008BD7F0SizedDeleting, 20 )
BFME_SIZED_DELETE_DTOR( Rva008BD850SizedDeleting, 20 )
BFME_SIZED_DELETE_DTOR( Rva008BD8B0SizedDeleting, 24 )
BFME_SIZED_DELETE_DTOR( Rva008BE450SizedDeleting, 116 )
BFME_SIZED_DELETE_DTOR( Rva008BED90SizedDeleting, 32 )
BFME_SIZED_DELETE_DTOR( Rva008CB5C0SizedDeleting, 8 )
BFME_SIZED_DELETE_DTOR( Rva008CB690SizedDeleting, 8 )
