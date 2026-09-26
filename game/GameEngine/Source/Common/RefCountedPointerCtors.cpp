// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ten reference-counted pointer constructors, 29 or 31 bytes.
// Retail, the two shapes:
//
//     mov eax,[esp+4]                      ; 29-byte form: the argument IS the
//     test eax,eax                         ; pointer
//     push esi ; mov esi,ecx ; mov [esi],eax
//     je +
//     add eax,<OFF> ; push eax ; call dword ptr [__imp__InterlockedIncrement@4]
//     mov eax,esi ; pop esi ; ret 4
//
//     mov eax,[esp+4] ; mov eax,[eax]      ; 31-byte form: one more load, so
//     ...                                  ; the argument is a REFERENCE to
//                                          ; another pointer -- a copy ctor
//
// WHAT THE BYTES SHOW.  `ret 4` and `mov eax,esi` make these one-argument
// __thiscall constructors returning this; the whole body stores the argument in
// the first (and only) member and, when it is not null, raises a refcount
// through a dllimport whose FF15 slot 0x01358E5C the ledger already identifies
// as InterlockedIncrement.  The count is at +4 in eight of them and at +0x74 in
// the pair at 0x00696420/0x00696450, so those two name a wider target.
//
// THE EXTRA LOAD IS THE WHOLE DIFFERENCE between the two shapes and it settles
// the parameter: dereferencing it before storing it means it is a reference to
// a pointer, not the pointer, so the 31-byte rows are copy constructors and the
// 29-byte rows take the raw pointer.
//
// TEN BODIES, FIVE BYTE-IDENTICAL PAIRS, AND THE PAIRING IS NOT DECIDED.  The
// four 29-byte rows at +4 are byte-for-byte identical to each other and so are
// the four 31-byte ones, so nothing here says which copy constructor belongs to
// which pointer constructor -- only the 0x00696420/0x00696450 and
// 0x006967B0/0x006967E0 pairs are adjacent enough to suggest it.  Each row is
// therefore spelled as its own class carrying only the constructor it needs,
// which asserts the shape without inventing the pairing.
//
// IDENTITY IS NOT RECOVERED: every name here is address-derived.

typedef long Long;

extern "C" __declspec(dllimport) Long __stdcall InterlockedIncrement( Long volatile *addend );
extern "C" __declspec(dllimport) Long __stdcall InterlockedDecrement( Long volatile *addend );

class RefTargetBase006964E0
{
public:
	virtual ~RefTargetBase006964E0() {}
	Long m_refCount;
};

struct Rva006964E0Target
{
	char m_unreconstructed_00[ 0x70 ];
	RefTargetBase006964E0 m_base;
};

class Rva006964E0Ptr
{
public:
	void reset( void );
	Rva006964E0Target *m_ptr;
};

void Rva006964E0Ptr::reset( void )
{
	Rva006964E0Target *p = m_ptr;
	if ( p )
	{
		RefTargetBase006964E0 *base = &p->m_base;
		if ( InterlockedDecrement( &base->m_refCount ) <= 0 )
			delete base;
		m_ptr = 0;
	}
}

#define RVA_REF_TARGET( NAME, PAD )                                       \
	struct NAME##Target                                                   \
	{                                                                     \
		char m_unreconstructed_00[ PAD ];                                 \
		Long m_refCount;                                                  \
	};                                                                    \

#define RVA_REF_PTR_CTOR( NAME, PAD )                                     \
	RVA_REF_TARGET( NAME, PAD )                                           \
	class NAME##Ptr                                                       \
	{                                                                     \
	public:                                                               \
		NAME##Ptr( NAME##Target *p );                                     \
		NAME##Target *m_ptr;                                              \
	};                                                                    \
	NAME##Ptr::NAME##Ptr( NAME##Target *p )                               \
	{                                                                     \
		m_ptr = p;                                                        \
		if ( p )                                                          \
			InterlockedIncrement( &p->m_refCount );                       \
	}

#define RVA_REF_COPY_CTOR( NAME, PAD )                                    \
	RVA_REF_TARGET( NAME, PAD )                                           \
	class NAME##Ptr                                                       \
	{                                                                     \
	public:                                                               \
		NAME##Ptr( const NAME##Ptr &other );                              \
		NAME##Target *m_ptr;                                              \
	};                                                                    \
	NAME##Ptr::NAME##Ptr( const NAME##Ptr &other )                        \
	{                                                                     \
		m_ptr = other.m_ptr;                                              \
		if ( m_ptr )                                                      \
			InterlockedIncrement( &m_ptr->m_refCount );                   \
	}

RVA_REF_PTR_CTOR( Rva00087720, 0x4 )
RVA_REF_PTR_CTOR( Rva00412610, 0x4 )
RVA_REF_PTR_CTOR( Rva006967B0, 0x4 )
RVA_REF_PTR_CTOR( Rva00696CF0, 0x4 )
RVA_REF_PTR_CTOR( Rva00696420, 0x74 )

RVA_REF_COPY_CTOR( Rva000B97D0, 0x4 )
RVA_REF_COPY_CTOR( Rva001C0210, 0x4 )
RVA_REF_COPY_CTOR( Rva006967E0, 0x4 )
RVA_REF_COPY_CTOR( Rva00698660, 0x4 )
RVA_REF_COPY_CTOR( Rva00696450, 0x74 )
