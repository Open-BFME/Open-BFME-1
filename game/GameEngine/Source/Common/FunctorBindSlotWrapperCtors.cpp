// The 9 byte-identical 27-byte wrapper constructors of the functor-bind
// family's ONE-DWORD variant.
//
// Companion to FunctorBindWrapperCtors.cpp (four dwords) and
// FunctorBindSingleWrapperCtors.cpp (two); read the first of those headers
// before this one.  Retail:
//
//     mov eax,ecx / mov ecx,[esp+4]
//     mov [eax+4],0 / mov [eax],<vftable>
//     mov edx,[ecx] / mov [eax+8],edx / ret 4
//
// The same constructor as its two siblings with the embedded sub-object down
// to a single dword: `mov eax,ecx` with no other use of eax is a __thiscall
// constructor returning `this`, one dword argument and `ret 4`, a vftable to
// +0x00, zero to +0x04, and FOUR bytes copied out of the argument into +0x08.
// The load through `[ecx]` -- rather than storing the argument register
// itself, which is what the 25-byte variant at 0x00149FC0 does -- is what
// makes the argument a reference to a one-dword object and not the dword.
//
// WHAT SITS AT +0x08.  The invoker paired with each of these is not the
// sibling families' `mov ecx,[eax+8] / jmp [eax+0xC]` but an offset tail jump:
// 0x0058D150, 0x0058D190 and 0x0058D1D0, landed in MemberOffsetTailThunks.cpp,
// are `add ecx,8 / jmp <rel32>`.  Dispatch therefore enters a named function
// with `this` pointing AT +0x08, so +0x08 holds an embedded sub-object whose
// own member function is called -- not a bound {object, code} pair that the
// wrapper itself has to take apart.  Four bytes of it are copied in, so it is
// modelled here as a one-dword aggregate passed by const reference, which is
// the least the bytes assert.
//
// The leading two dwords are a base for the reason FunctorBindInvokers.cpp
// measured; the base zeroes the unmodelled dword and MSVC drops the base's own
// vftable store as dead, which is why retail writes +0x04 before +0x00.
//
// WHY THE COPIES ARE NOT FOLDED, AND WHY THE NAMES ARE ADDRESS-DERIVED: as in
// FunctorBindConstructors.cpp.  9 distinct addresses, 9 separate template
// instantiations, and no surviving name for the class.


// WHAT +0x04 IS.  The dword the head zeroes is a REFERENCE COUNT, and the
// holders appended below are what prove it: every one of them allocates a
// wrapper, runs this constructor, and then does `inc dword ptr [eax+4]` on the
// result -- raising to one the counter this constructor had just set to zero.
// It is named m_refCount here for that reason; before the holders it was only
// an unmodelled dword.  The counter is non-atomic, a plain `inc`.
//
// THE HOLDERS.  Each wrapper is paired with two 58-byte-family constructors of
// a holder that owns one:
//
//     push 12 / mov esi,ecx / call operator new / add esp,4 / test eax,eax /
//     je <null> / <this constructor, inlined> / jmp <done> /
//     <null>: xor eax,eax / <done>: test eax,eax / mov [esi],eax /
//     je +3 / inc dword ptr [eax+4] / mov eax,esi / pop esi / ret
//
// which is `m_ptr = new WRAPPER( binding ); if ( m_ptr ) m_ptr->m_refCount++;`
// -- MSVC 7.1's `new` expression is exactly the allocate, null-test, inlined
// construct, and the null-test around the increment is separate from it.  The
// allocation size is 12 bytes, which is the whole wrapper: vftable, counter and
// the four-byte binding.
//
// The two holders per wrapper differ ONLY in how the binding arrives.  The
// longer takes `const FunctorSlot &` and reads through the pointer; the shorter takes it
// BY VALUE and reads the caller's own stack slots, which is why it consumes
// 4 bytes of arguments instead of four and why its copy has no pointer to
// dereference.  Nothing else about them differs.

struct FunctorSlot
{
	void *m_slot;
};

class FunctorSlotWrapperHead
{
public:
	FunctorSlotWrapperHead() : m_refCount( 0 ) {}

	virtual void functorSlotWrapperAnchor();

	unsigned int m_refCount;
};

#define BFME_FUNCTOR_SLOT_WRAPPER_CTOR( NAME )                                \
	class NAME : public FunctorSlotWrapperHead                                \
	{                                                                         \
	public:                                                                   \
		NAME( const FunctorSlot &slot );                                      \
                                                                              \
		FunctorSlot m_slot;                                                   \
	};                                                                        \
	NAME::NAME( const FunctorSlot &slot ) : m_slot( slot ) {}

BFME_FUNCTOR_SLOT_WRAPPER_CTOR( Rva003BE8F0FunctorSlotWrapper )
BFME_FUNCTOR_SLOT_WRAPPER_CTOR( Rva0045ED70FunctorSlotWrapper )
BFME_FUNCTOR_SLOT_WRAPPER_CTOR( Rva0045EDD0FunctorSlotWrapper )
BFME_FUNCTOR_SLOT_WRAPPER_CTOR( Rva0045EE10FunctorSlotWrapper )
BFME_FUNCTOR_SLOT_WRAPPER_CTOR( Rva0046F150FunctorSlotWrapper )
BFME_FUNCTOR_SLOT_WRAPPER_CTOR( Rva004C5660FunctorSlotWrapper )
BFME_FUNCTOR_SLOT_WRAPPER_CTOR( Rva0058D120FunctorSlotWrapper )
BFME_FUNCTOR_SLOT_WRAPPER_CTOR( Rva0058D160FunctorSlotWrapper )
BFME_FUNCTOR_SLOT_WRAPPER_CTOR( Rva0058D1A0FunctorSlotWrapper )

#define BFME_FUNCTOR_SLOT_HOLDER_FROM_REFERENCE( NAME, WRAPPER )                       \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		NAME( const FunctorSlot &binding );                          \
                                                                              \
		WRAPPER *m_ptr;                                                       \
	};                                                                        \
	NAME::NAME( const FunctorSlot &binding )                      \
	{                                                                         \
		m_ptr = new WRAPPER( binding );                                       \
		if ( m_ptr != 0 )                                                     \
			m_ptr->m_refCount++;                                              \
	}

#define BFME_FUNCTOR_SLOT_HOLDER_FROM_VALUE( NAME, WRAPPER )                           \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		NAME( FunctorSlot binding );                                 \
                                                                              \
		WRAPPER *m_ptr;                                                       \
	};                                                                        \
	NAME::NAME( FunctorSlot binding )                             \
	{                                                                         \
		m_ptr = new WRAPPER( binding );                                       \
		if ( m_ptr != 0 )                                                     \
			m_ptr->m_refCount++;                                              \
	}

BFME_FUNCTOR_SLOT_HOLDER_FROM_REFERENCE( Rva003BFA00FunctorSlotHolder, Rva003BE8F0FunctorSlotWrapper )
BFME_FUNCTOR_SLOT_HOLDER_FROM_REFERENCE( Rva0045F650FunctorSlotHolder, Rva0045ED70FunctorSlotWrapper )
BFME_FUNCTOR_SLOT_HOLDER_FROM_REFERENCE( Rva0045F6A0FunctorSlotHolder, Rva0045EDD0FunctorSlotWrapper )
BFME_FUNCTOR_SLOT_HOLDER_FROM_REFERENCE( Rva0045F6F0FunctorSlotHolder, Rva0045EE10FunctorSlotWrapper )
BFME_FUNCTOR_SLOT_HOLDER_FROM_REFERENCE( Rva0046FB20FunctorSlotHolder, Rva0046F150FunctorSlotWrapper )
BFME_FUNCTOR_SLOT_HOLDER_FROM_REFERENCE( Rva004C5BE0FunctorSlotHolder, Rva004C5660FunctorSlotWrapper )
BFME_FUNCTOR_SLOT_HOLDER_FROM_REFERENCE( Rva0058FAC0FunctorSlotHolder, Rva0058D120FunctorSlotWrapper )
BFME_FUNCTOR_SLOT_HOLDER_FROM_REFERENCE( Rva0058FB10FunctorSlotHolder, Rva0058D160FunctorSlotWrapper )
BFME_FUNCTOR_SLOT_HOLDER_FROM_REFERENCE( Rva0058FB60FunctorSlotHolder, Rva0058D1A0FunctorSlotWrapper )

BFME_FUNCTOR_SLOT_HOLDER_FROM_VALUE( Rva003C00B0FunctorSlotHolder, Rva003BE8F0FunctorSlotWrapper )
BFME_FUNCTOR_SLOT_HOLDER_FROM_VALUE( Rva0045FBD0FunctorSlotHolder, Rva0045ED70FunctorSlotWrapper )
BFME_FUNCTOR_SLOT_HOLDER_FROM_VALUE( Rva0045FC20FunctorSlotHolder, Rva0045EDD0FunctorSlotWrapper )
BFME_FUNCTOR_SLOT_HOLDER_FROM_VALUE( Rva0045FC70FunctorSlotHolder, Rva0045EE10FunctorSlotWrapper )
BFME_FUNCTOR_SLOT_HOLDER_FROM_VALUE( Rva0046FCF0FunctorSlotHolder, Rva0046F150FunctorSlotWrapper )
BFME_FUNCTOR_SLOT_HOLDER_FROM_VALUE( Rva004C5E50FunctorSlotHolder, Rva004C5660FunctorSlotWrapper )
BFME_FUNCTOR_SLOT_HOLDER_FROM_VALUE( Rva00590F90FunctorSlotHolder, Rva0058D120FunctorSlotWrapper )
BFME_FUNCTOR_SLOT_HOLDER_FROM_VALUE( Rva00590FE0FunctorSlotHolder, Rva0058D160FunctorSlotWrapper )
BFME_FUNCTOR_SLOT_HOLDER_FROM_VALUE( Rva00591030FunctorSlotHolder, Rva0058D1A0FunctorSlotWrapper )

