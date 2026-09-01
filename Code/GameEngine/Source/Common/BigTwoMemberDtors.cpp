// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Twenty-four 67-byte __thiscall destructors, one shape.  Retail:
//
//     push -1 / push <ehdata> / fs:[0] frame ; EH state 0, `this` at [esp+4]
//     lea ecx,[esi+<OFFSET>] / call <REL32>   ; destroy the member at OFFSET
//     mov [esi],<VFTABLE>                     ; inlined empty virtual dtor at 0
//
// WHAT THE BYTES SHOW.  There is exactly ONE vptr store and it is at the END.
// A destructor of a class that has a vptr of its own opens with a store of its
// own vftable; this one does not, so THE OWNER IS NOT POLYMORPHIC.  The single
// trailing store is therefore a subobject's inlined `virtual ~X() {}`, and it
// writes to [esi+0] -- offset zero.  A polymorphic BASE would give the owner a
// vftable of its own and bring the opening store back (measured: 73 bytes, six
// more, for every base spelling tried -- virtual dtor, non-virtual dtor, and a
// non-virtual-dtor base with an unrelated virtual function).  A polymorphic
// MEMBER at offset 0 does not, and reproduces all 67 bytes.
//
// The call is the destructor of a second member at OFFSET, and it runs BEFORE
// the offset-0 member's inlined one: members are destroyed in reverse
// declaration order, which is what puts the higher offset first.  The EH state
// is set to 0 and never reset, so the unwind funclet exists to finish the
// offset-0 member if the first destructor throws.
//
// TWO AXES, BOTH READ DIRECTLY: the member OFFSET (a disp8, so every member of
// this family sits below 0x80) and the REL32 destructor it calls.  Eight
// distinct callees over three distinct offset-0 vftables.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.  The
// vftable and the EH data are DIR32 relocation sites the byte gate takes from
// the target; the member destructors are REL32 and are pinned in
// reverse/symbols.csv.

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <vector>

#define BFME_INNER_VPTR( VT )                                             \
	class Inner##VT                                                       \
	{                                                                     \
	public:                                                               \
		virtual ~Inner##VT() {}                                           \
	};

#define BFME_MEMBER_DTOR( ADDR )                                          \
	class Mem##ADDR                                                       \
	{                                                                     \
	public:                                                               \
		~Mem##ADDR();                                                     \
	};

#define BFME_TWO_MEMBER_DTOR( NAME, INNER, MEMBER, PAD )                  \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		~NAME();                                                          \
		INNER  m_head;                                                    \
		char   m_pad[ PAD ];                                              \
		MEMBER m_tail;                                                    \
	};                                                                    \
	NAME::~NAME() {}

#define BFME_TWO_MEMBER_DTOR_TIGHT( NAME, INNER, MEMBER )                 \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		~NAME();                                                          \
		INNER  m_head;                                                    \
		MEMBER m_tail;                                                    \
	};                                                                    \
	NAME::~NAME() {}

BFME_INNER_VPTR( 01073744 )
BFME_INNER_VPTR( 010EAD58 )
BFME_INNER_VPTR( 010EDAA0 )
BFME_INNER_VPTR( 010F6F58 )

BFME_MEMBER_DTOR( 00129C80 )
BFME_MEMBER_DTOR( 0039D550 )
BFME_MEMBER_DTOR( 003AB460 )
BFME_MEMBER_DTOR( 00887940 )
BFME_MEMBER_DTOR( 008881D0 )

class Mem004CRefCounted
{
public:
	void Release_Ref()
	{
		if( (m_refs = m_refs - 1) <= 0 )
			Delete_This( 1 );
	}

protected:
	virtual void Delete_This( unsigned int );
	int m_refs;
};

template <int Tag>
class Mem004CRefPtr
{
public:
	~Mem004CRefPtr()
	{
		if( m_ptr )
			m_ptr->Release_Ref();
	}

private:
	Mem004CRefCounted *m_ptr;
};

#define BFME_REF_PAIR_DTOR( NAME, TAG )                                   \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		~NAME();                                                          \
	private:                                                              \
		Mem004CRefPtr<TAG> m_first;                                      \
		Mem004CRefPtr<TAG + 1> m_second;                                 \
	};                                                                    \
	NAME::~NAME() {}

BFME_REF_PAIR_DTOR( Mem004C5700, 0 )
BFME_REF_PAIR_DTOR( Mem004C57D0, 2 )

struct Mem0027E9C0Element
{
	int m_pad0;
	int m_pad1;
	_STL::list<int> m_values;
};

// The 0x0027E9C0 body is the authentic vector destructor: its 12-byte
// elements contain two words followed by a list<int>.  Naming the member as
// that vector also makes the already-matched 0x0027EED0 owner call it directly.
typedef _STL::vector<Mem0027E9C0Element> Mem0027E9C0;

BFME_TWO_MEMBER_DTOR( Rva000ED4A0, Inner01073744, Mem00887940, 12 )
BFME_TWO_MEMBER_DTOR( Rva00126CF0, Inner01073744, Mem00887940, 4 )
BFME_TWO_MEMBER_DTOR( Rva00126FC0, Inner01073744, Mem00887940, 64 )
BFME_TWO_MEMBER_DTOR( Rva00127190, Inner01073744, Mem00887940, 64 )
BFME_TWO_MEMBER_DTOR( Rva00127220, Inner01073744, Mem00887940, 64 )
BFME_TWO_MEMBER_DTOR( Rva00129CF0, Inner01073744, Mem00129C80, 4 )
BFME_TWO_MEMBER_DTOR( Rva0012ACD0, Inner01073744, Mem00129C80, 4 )
BFME_TWO_MEMBER_DTOR( Rva0012AEC0, Inner01073744, Mem00129C80, 4 )
BFME_TWO_MEMBER_DTOR( Rva0012B1A0, Inner01073744, Mem00129C80, 4 )
BFME_TWO_MEMBER_DTOR( Rva0012B2C0, Inner01073744, Mem00129C80, 4 )
BFME_TWO_MEMBER_DTOR( Rva0012B3D0, Inner01073744, Mem00129C80, 4 )
BFME_TWO_MEMBER_DTOR( Rva0012B4D0, Inner01073744, Mem00129C80, 4 )
BFME_TWO_MEMBER_DTOR( Rva0012B5F0, Inner01073744, Mem00129C80, 4 )
BFME_TWO_MEMBER_DTOR( Rva00204F90, Inner01073744, Mem00129C80, 4 )
BFME_TWO_MEMBER_DTOR( Rva00215DF0, Inner01073744, Mem0039D550, 40 )
BFME_TWO_MEMBER_DTOR( Rva0024FB30, Inner01073744, Mem00887940, 4 )
BFME_TWO_MEMBER_DTOR( Rva00250DF0, Inner01073744, Mem00887940, 4 )
BFME_TWO_MEMBER_DTOR_TIGHT( Rva0027EED0, Inner01073744, Mem0027E9C0 )
BFME_TWO_MEMBER_DTOR( Rva00388770, Inner010EAD58, Mem00887940, 4 )
BFME_TWO_MEMBER_DTOR( Rva003BC490, Inner01073744, Mem003AB460, 8 )
BFME_TWO_MEMBER_DTOR_TIGHT( Rva003BD770, Inner010EDAA0, Mem008881D0 )
BFME_TWO_MEMBER_DTOR( Rva004C60A0, Inner010EAD58, Mem004C5700, 4 )
BFME_TWO_MEMBER_DTOR( Rva004C61D0, Inner010EAD58, Mem004C57D0, 4 )
BFME_TWO_MEMBER_DTOR( Rva00789740, Inner010F6F58, Mem00887940, 4 )
