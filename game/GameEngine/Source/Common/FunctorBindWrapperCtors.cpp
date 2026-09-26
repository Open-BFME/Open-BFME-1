// The 41 byte-identical 49-byte wrapper constructors of BFME's
// functor-binding family.
//
// Companion to FunctorBindConstructors.cpp and FunctorBindInvokers.cpp; read
// those headers first for how the family's layout was recovered.  Retail:
//
//     mov edx,[esp+4] / mov eax,ecx / push esi
//     mov [eax+4],0 / mov [eax],<vftable>
//     mov esi,[edx] / lea ecx,[eax+8] / mov [ecx],esi
//     mov esi,[edx+4] / mov [ecx+4],esi / mov esi,[edx+8] / mov [ecx+8],esi
//     mov edx,[edx+0xC] / mov [ecx+0xC],edx / pop esi / ret 4
//
// WHAT THE BODY IS.  `mov eax,ecx` with no other use of eax is a __thiscall
// constructor returning `this`; one dword argument and `ret 4`.  A vftable
// goes to +0x00, zero to +0x04, and sixteen bytes are copied out of the
// argument into +0x08.
//
// WHY THE ARGUMENT IS A BINDING AND NOT ANOTHER WRAPPER.  The source is read
// at +0x00, +0x04, +0x08 and +0x0C -- from the argument's own base, not from
// +0x08 -- so it is not a copy constructor taking `const Wrapper &`.  It is the
// wrapper being built around a bound-method object of exactly the shape the 82
// constructors in FunctorBindConstructors.cpp produce: {object at +0x00,
// unmodelled +0x04, code +0x08, delta +0x0C}, sixteen bytes.  The destination
// is the same sub-object the invoker at 0x0050DB20 dispatches through --
// `mov ecx,[eax+0x14] / add ecx,[eax+8] / jmp [eax+0x10]`, i.e. object +0x08,
// code +0x10, delta +0x14 in wrapper coordinates -- so the binding lands at
// wrapper +0x08 and the four dwords line up one for one.
//
// WHY THE LEADING TWO DWORDS ARE A BASE.  FunctorBindInvokers.cpp records the
// measurement: MSVC 7.1 places a sub-object holding a `__multiple_inheritance`
// pointer-to-member eight bytes further along than the naive count when the
// enclosing class declares its own first virtual, which emits [eax+0x1C] and
// [eax+0x18] instead of retail's [eax+0x14] and [eax+0x10].  Splitting the
// vftable slot and the unmodelled dword into a base fixes the layout, and this
// constructor is what gives that base a body: the base zeroes the unmodelled
// dword, and the derived vftable store that follows is the one that survives
// -- MSVC drops the base's own vftable store as dead, which is why retail
// writes +0x04 before +0x00.
//
// WHY THE MEMBER COPY GOES THROUGH ecx.  `lea ecx,[eax+8]` followed by stores
// based on ecx is an inlined __thiscall copy constructor for the binding
// sub-object, not a memberwise store sequence off `this`; writing the member
// initialiser as `m_binding( binding )` reproduces it, and the four dwords move
// in declaration order.
//
// WHY THE COPIES ARE NOT FOLDED, AND WHY THE NAMES ARE ADDRESS-DERIVED: as in
// FunctorBindConstructors.cpp.  41 distinct addresses, 41 separate template
// instantiations, and no surviving name for the class -- the only RTTI
// descriptor the framework leaves in the image is `.?AVFunctorNotSet@@`.


// WHAT +0x04 IS.  The dword the head zeroes is a REFERENCE COUNT, and the
// holders appended below are what prove it: every one of them allocates a
// wrapper, runs this constructor, and then does `inc dword ptr [eax+4]` on the
// result -- raising to one the counter this constructor had just set to zero.
// It is named m_refCount here for that reason; before the holders it was only
// an unmodelled dword.  The counter is non-atomic, a plain `inc`.
//
// THE HOLDERS.  Each wrapper is paired with two 80-byte-family constructors of
// a holder that owns one:
//
//     push 24 / mov esi,ecx / call operator new / add esp,4 / test eax,eax /
//     je <null> / <this constructor, inlined> / jmp <done> /
//     <null>: xor eax,eax / <done>: test eax,eax / mov [esi],eax /
//     je +3 / inc dword ptr [eax+4] / mov eax,esi / pop esi / ret
//
// which is `m_ptr = new WRAPPER( binding ); if ( m_ptr ) m_ptr->m_refCount++;`
// -- MSVC 7.1's `new` expression is exactly the allocate, null-test, inlined
// construct, and the null-test around the increment is separate from it.  The
// allocation size is 24 bytes, which is the whole wrapper: vftable, counter and
// the sixteen-byte binding.
//
// The two holders per wrapper differ ONLY in how the binding arrives.  The
// longer takes `const FunctorBinding &` and reads through the pointer; the shorter takes it
// BY VALUE and reads the caller's own stack slots, which is why it consumes
// 16 bytes of arguments instead of four and why its copy has no pointer to
// dereference.  Nothing else about them differs.

class __multiple_inheritance FunctorTarget;

typedef void (FunctorTarget::*FunctorMethod)(void);

struct FunctorBinding
{
	FunctorTarget *m_target;
	unsigned int   m_refCount;
	FunctorMethod  m_method;
};

// The Objectives/PlayerStatus constructor uses the shared APT holder through
// a distinct binding overload.  Its caller at 0x0052C660 constructs this
// four-dword payload and immediately passes the resulting common holder to
// _bfme_AptGameWindow::_bfme_showAptScreen.
struct BfmeObjectivesFunctorBinding
{
	FunctorTarget *m_target;
	unsigned int   m_refCount;
	FunctorMethod  m_method;
};

class FunctorWrapperHead
{
public:
	FunctorWrapperHead() : m_refCount( 0 ) {}

	virtual void functorWrapperAnchor();

	unsigned int m_refCount;
};

#define BFME_FUNCTOR_WRAPPER_CTOR( NAME )                                     \
	class NAME : public FunctorWrapperHead                                    \
	{                                                                         \
	public:                                                                   \
		NAME( const FunctorBinding &binding );                                \
                                                                              \
		FunctorBinding m_binding;                                             \
	};                                                                        \
	NAME::NAME( const FunctorBinding &binding ) : m_binding( binding ) {}

BFME_FUNCTOR_WRAPPER_CTOR( Rva0050DAE0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0050DB30FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0050DB80FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0050E8B0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0050E900FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0050E950FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva005119A0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva005119F0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva00511A40FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva005179D0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva00517A20FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0051E3E0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0051E430FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0051E480FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0051E4D0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0051E520FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0052B6E0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0052B730FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0052B780FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva00538B80FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva00538BD0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0055C5F0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0055C640FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0055EDB0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0055EE00FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0055EE50FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva00569C30FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva00569C80FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0056C9A0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0056C9F0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0056CA40FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0056CA90FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva00571730FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva00571780FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva005717D0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0057A020FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0057A070FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0057A0C0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0058D220FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0058D270FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva00599630FunctorWrapper )

#define BFME_FUNCTOR_HOLDER_FROM_REFERENCE( NAME, WRAPPER )                       \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		NAME( const FunctorBinding &binding );                          \
                                                                              \
		WRAPPER *m_ptr;                                                       \
	};                                                                        \
	NAME::NAME( const FunctorBinding &binding )                      \
	{                                                                         \
		m_ptr = new WRAPPER( binding );                                       \
		if ( m_ptr != 0 )                                                     \
			m_ptr->m_refCount++;                                              \
	}

#define BFME_FUNCTOR_HOLDER_FROM_VALUE( NAME, WRAPPER )                           \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		NAME( FunctorBinding binding );                                 \
                                                                              \
		WRAPPER *m_ptr;                                                       \
	};                                                                        \
	NAME::NAME( FunctorBinding binding )                             \
	{                                                                         \
		m_ptr = new WRAPPER( binding );                                       \
		if ( m_ptr != 0 )                                                     \
			m_ptr->m_refCount++;                                              \
	}

BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0050DF90FunctorHolder, Rva0050DAE0FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0050E000FunctorHolder, Rva0050DB30FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0050E070FunctorHolder, Rva0050DB80FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0050F420FunctorHolder, Rva0050E8B0FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0050F490FunctorHolder, Rva0050E900FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0050F500FunctorHolder, Rva0050E950FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva00512350FunctorHolder, Rva005119A0FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva005123C0FunctorHolder, Rva005119F0FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva00512430FunctorHolder, Rva00511A40FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva00518070FunctorHolder, Rva005179D0FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva005180E0FunctorHolder, Rva00517A20FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0051EB50FunctorHolder, Rva0051E3E0FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0051EBC0FunctorHolder, Rva0051E430FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0051EC30FunctorHolder, Rva0051E480FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0051ECA0FunctorHolder, Rva0051E4D0FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0051ED10FunctorHolder, Rva0051E520FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0052BB60FunctorHolder, Rva0052B6E0FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0052BBD0FunctorHolder, Rva0052B730FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0052BC40FunctorHolder, Rva0052B780FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva005394E0FunctorHolder, Rva00538B80FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva00539550FunctorHolder, Rva00538BD0FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0055C800FunctorHolder, Rva0055C5F0FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0055C870FunctorHolder, Rva0055C640FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0055EFF0FunctorHolder, Rva0055EDB0FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0055F060FunctorHolder, Rva0055EE00FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0055F0D0FunctorHolder, Rva0055EE50FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0056A0D0FunctorHolder, Rva00569C30FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0056A140FunctorHolder, Rva00569C80FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0056CEB0FunctorHolder, Rva0056C9A0FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0056CF20FunctorHolder, Rva0056C9F0FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0056CF90FunctorHolder, Rva0056CA40FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0056D000FunctorHolder, Rva0056CA90FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva00572290FunctorHolder, Rva00571730FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva00572300FunctorHolder, Rva00571780FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva00572370FunctorHolder, Rva005717D0FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0057C740FunctorHolder, Rva0057A020FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0057C7B0FunctorHolder, Rva0057A070FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0057C820FunctorHolder, Rva0057A0C0FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0058FC00FunctorHolder, Rva0058D220FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva0058FC70FunctorHolder, Rva0058D270FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_REFERENCE( Rva00599940FunctorHolder, Rva00599630FunctorWrapper )

BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva0050E1D0FunctorHolder, Rva0050DAE0FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva0050E240FunctorHolder, Rva0050DB30FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva0050E2B0FunctorHolder, Rva0050DB80FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva0050F840FunctorHolder, Rva0050E8B0FunctorWrapper )

class Rva0050F8B0FunctorHolder
{
public:
	Rva0050F8B0FunctorHolder( FunctorBinding binding );
	Rva0050F8B0FunctorHolder( BfmeObjectivesFunctorBinding binding );

	union
	{
		Rva0050E900FunctorWrapper *m_ptr;
		Rva0052B6E0FunctorWrapper *m_objectivesPtr;
	};
};

Rva0050F8B0FunctorHolder::Rva0050F8B0FunctorHolder( FunctorBinding binding )
{
	m_ptr = new Rva0050E900FunctorWrapper( binding );
	if ( m_ptr != 0 )
		m_ptr->m_refCount++;
}

Rva0050F8B0FunctorHolder::Rva0050F8B0FunctorHolder(
	BfmeObjectivesFunctorBinding binding )
{
	m_objectivesPtr = new Rva0052B6E0FunctorWrapper(
		*(const FunctorBinding *)(const void *)&binding );
	if ( m_objectivesPtr != 0 )
		m_objectivesPtr->m_refCount++;
}

BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva0050F920FunctorHolder, Rva0050E950FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva00512B70FunctorHolder, Rva005119A0FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva00512BE0FunctorHolder, Rva005119F0FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva00512C50FunctorHolder, Rva00511A40FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva00518B10FunctorHolder, Rva005179D0FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva00518B80FunctorHolder, Rva00517A20FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva0051EDB0FunctorHolder, Rva0051E3E0FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva0051EE20FunctorHolder, Rva0051E430FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva0051EE90FunctorHolder, Rva0051E480FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva0051EF00FunctorHolder, Rva0051E4D0FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva0051EF70FunctorHolder, Rva0051E520FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva0052BD50FunctorHolder, Rva0052B730FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva0052BDC0FunctorHolder, Rva0052B780FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva00539A60FunctorHolder, Rva00538B80FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva00539AD0FunctorHolder, Rva00538BD0FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva0055CA70FunctorHolder, Rva0055C5F0FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva0055CAE0FunctorHolder, Rva0055C640FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva0055F140FunctorHolder, Rva0055EDB0FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva0055F1B0FunctorHolder, Rva0055EE00FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva0055F220FunctorHolder, Rva0055EE50FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva0056A210FunctorHolder, Rva00569C30FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva0056A280FunctorHolder, Rva00569C80FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva0056D9B0FunctorHolder, Rva0056C9A0FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva0056DA20FunctorHolder, Rva0056C9F0FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva0056DA90FunctorHolder, Rva0056CA40FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva0056DB00FunctorHolder, Rva0056CA90FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva00572CA0FunctorHolder, Rva00571730FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva00572D10FunctorHolder, Rva00571780FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva00572D80FunctorHolder, Rva005717D0FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva0057C970FunctorHolder, Rva0057A020FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva0057C9E0FunctorHolder, Rva0057A070FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva0057CA50FunctorHolder, Rva0057A0C0FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva005910D0FunctorHolder, Rva0058D220FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva00591140FunctorHolder, Rva0058D270FunctorWrapper )
BFME_FUNCTOR_HOLDER_FROM_VALUE( Rva00599F70FunctorHolder, Rva00599630FunctorWrapper )
