// 26 forty-two-byte __thiscall members with one shape:
//
//     push esi / mov esi,ecx / call <destructor> / test byte ptr [esp+8],1 /
//     je +21 / push esi / call 0x00897330 / lea eax,[esi-8] / push <SIZE> /
//     push eax / call dword ptr [0x01337830] / add esp,0xc /
//     mov eax,esi / pop esi / ret 4
//
// WHAT THE BODY IS.  MSVC 7.1's scalar deleting destructor `??_G`, and the
// second flavour of the sized deallocator landed in SizedDeleteDestructors.cpp:
// the same run-time deallocator pointer at 0x01337830, called with the same
// (storage, size) pair, but reached through a longer `operator delete` -- one
// that first hands the object to 0x00897330 and then frees EIGHT BYTES BEFORE it.
// Freeing `p - 8` for a block whose size is passed alongside is an allocation
// header: the block the allocator owns starts eight bytes ahead of the object.
//
// WHAT VARIES AND WHAT DOES NOT.  Across all 26 bodies the -8, the notify call
// and the deallocator pointer are IDENTICAL, and only the size and the
// destructor differ.  That is what puts the -8 and the two calls inside one
// shared `operator delete` and leaves the size to `sizeof`: a class-level
// `operator delete( void *, size_t )` receives the class's own size, which is
// what fixes each class's padding below.  The size it passes ON is the object
// plus its header: HeaderedDeleteOperators.cpp lands fifteen out-of-line copies
// of this very operator, and they read `size + 8`, so the constant each helper
// pushes is eight MORE than the class it belongs to.  The padding here is set
// from that, not from the constant.  Declared inline on the base, it is
// folded into every helper, which is what produces the single merged
// `add esp,0xc` for two separate __cdecl calls.
//
// 26 bodies, 26 distinct destructors -- one each, no folding here.  Each is an
// address decoded from the retail REL32 and pinned in `reverse/symbols.csv`
// under an address-derived name, as is the notify call.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

extern void ( __cdecl *g_Va01337830 )( void *storage, unsigned int size );

void __cdecl Rva00897330NotifyFree( void *storage );

class HeaderedDeleteBase
{
public:
	virtual ~HeaderedDeleteBase();

	static void operator delete( void *storage, unsigned int size )
	{
		Rva00897330NotifyFree( storage );
		g_Va01337830( (char *)storage - 8, size + 8 );
	}
};

class Q4Sub00C9CC70
{
public:
	~Q4Sub00C9CC70();
};

class Q4Base00D35D68
{
public:
	void notify( int a, int b );
};

class Rva008B01E0HeaderedRoot
{
public:
	virtual ~Rva008B01E0HeaderedRoot() {}

	static void operator delete( void *storage, unsigned int size )
	{
		Rva00897330NotifyFree( storage );
		g_Va01337830( (char *)storage - 8, size + 8 );
	}
};

struct Rva008B01E0ReferenceCount
{
	unsigned short m_count;
};

extern void ( __cdecl **Rva01337A30ReleaseTable )( void * );

class Rva008B01E0Reference
{
public:
	~Rva008B01E0Reference()
	{
		Rva008B01E0ReferenceCount *reference = m_reference;
		--reference->m_count;
		if( reference->m_count == 0 )
			Rva01337A30ReleaseTable[ 1 ]( reference );
	}

private:
	Rva008B01E0ReferenceCount *m_reference;
};

class Rva008B01E0HeaderedMiddle : public Rva008B01E0HeaderedRoot
{
public:
	__forceinline virtual ~Rva008B01E0HeaderedMiddle()
	{
		((Q4Base00D35D68 *)this)->notify( 0, 0 );
		m_flag = 0;
	}

private:
	char m_gap0[ 8 - 4 ];
	Q4Sub00C9CC70 m_sub;
	char m_gap1[ 0x18 - 9 ];
	int m_flag;
	char m_gap2[ 0x20 - 0x1C ];
};

class Rva008B01E0HeaderedDeleting : public Rva008B01E0HeaderedMiddle
{
public:
	virtual ~Rva008B01E0HeaderedDeleting();

private:
	Rva008B01E0Reference m_reference;
	char m_pad[ 0x40 - 0x24 ];
};

Rva008B01E0HeaderedDeleting::~Rva008B01E0HeaderedDeleting()
{
}

#define BFME_HEADERED_DELETE_DTOR( NAME, PAD )                                \
	class NAME : public HeaderedDeleteBase                                    \
	{                                                                         \
	public:                                                                   \
		virtual ~NAME();                                                      \
                                                                              \
		char m_pad[ PAD ];                                                    \
	};                                                                        \
	NAME::~NAME()                                                             \
	{                                                                         \
	}

BFME_HEADERED_DELETE_DTOR( Rva00892ED0HeaderedDeleting, 96 )
BFME_HEADERED_DELETE_DTOR( Rva00899500HeaderedDeleting, 28 )
BFME_HEADERED_DELETE_DTOR( Rva00899E80HeaderedDeleting, 24 )
BFME_HEADERED_DELETE_DTOR( Rva00899FE0HeaderedDeleting, 32 )
BFME_HEADERED_DELETE_DTOR( Rva0089A3E0HeaderedDeleting, 20 )
BFME_HEADERED_DELETE_DTOR( Rva0089A4B0HeaderedDeleting, 28 )
BFME_HEADERED_DELETE_DTOR( Rva0089A660HeaderedDeleting, 20 )
BFME_HEADERED_DELETE_DTOR( Rva0089A800HeaderedDeleting, 20 )
BFME_HEADERED_DELETE_DTOR( Rva0089A9A0HeaderedDeleting, 20 )
BFME_HEADERED_DELETE_DTOR( Rva0089AB40HeaderedDeleting, 20 )
BFME_HEADERED_DELETE_DTOR( Rva008A6410HeaderedDeleting, 36 )
BFME_HEADERED_DELETE_DTOR( Rva008B2F20HeaderedDeleting, 36 )
BFME_HEADERED_DELETE_DTOR( Rva008B3A10HeaderedDeleting, 36 )
BFME_HEADERED_DELETE_DTOR( Rva008B46D0HeaderedDeleting, 32 )
BFME_HEADERED_DELETE_DTOR( Rva008B58B0HeaderedDeleting, 40 )
BFME_HEADERED_DELETE_DTOR( Rva008B9C90HeaderedDeleting, 40 )
BFME_HEADERED_DELETE_DTOR( Rva008CB760HeaderedDeleting, 32 )
BFME_HEADERED_DELETE_DTOR( Rva008CB9F0HeaderedDeleting, 96 )
BFME_HEADERED_DELETE_DTOR( Rva008CBAA0HeaderedDeleting, 28 )
BFME_HEADERED_DELETE_DTOR( Rva008CBB50HeaderedDeleting, 32 )
BFME_HEADERED_DELETE_DTOR( Rva008CBD70HeaderedDeleting, 20 )
BFME_HEADERED_DELETE_DTOR( Rva008D5780HeaderedDeleting, 32 )
BFME_HEADERED_DELETE_DTOR( Rva008D6260HeaderedDeleting, 44 )
BFME_HEADERED_DELETE_DTOR( Rva008D62C0HeaderedDeleting, 48 )
BFME_HEADERED_DELETE_DTOR( Rva008D6320HeaderedDeleting, 48 )
