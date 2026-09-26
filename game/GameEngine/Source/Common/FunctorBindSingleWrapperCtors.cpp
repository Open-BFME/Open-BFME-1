// The 30 byte-identical 33-byte wrapper constructors of BFME's
// single-inheritance functor-bind family.
//
// Companion to FunctorBindWrapperCtors.cpp, which lands the same constructor
// for the multiple-inheritance family; read that header and
// FunctorBindSingleInvokers.cpp first.  Retail:
//
//     mov eax,ecx / mov ecx,[esp+4]
//     mov [eax+4],0 / mov [eax],<vftable>
//     mov edx,[ecx] / mov [eax+8],edx
//     mov ecx,[ecx+4] / mov [eax+0xC],ecx / ret 4
//
// The same function as the 49-byte one with the bound sub-object collapsed
// from four dwords to two: `mov eax,ecx` with no other use of eax is a
// __thiscall constructor returning `this`, one dword argument and `ret 4`, a
// vftable to +0x00, zero to +0x04, and EIGHT bytes copied out of the argument
// into +0x08.  Eight bytes is {object, code} -- a 4-byte single-inheritance
// pointer-to-member bound to an object, exactly what the family's own invoker
// dispatches through: 0x0058D110 and its 23 twins in
// FunctorBindSingleInvokers.cpp are `mov eax,ecx / mov ecx,[eax+8] /
// jmp [eax+0xC]`, object at wrapper +0x08 and code at +0x0C with no delta
// added.  The source is read at +0x00 and +0x04, from the argument's own base
// rather than from +0x08, so the argument is the binding and not another
// wrapper -- the shape the 24 initialisers in FunctorBindSingleInit.cpp fill
// in.
//
// The leading two dwords are a base for the reason FunctorBindInvokers.cpp
// measured and FunctorBindSingleInvokers.cpp repeats; here it also gives the
// vftable this constructor writes somewhere real to live.  The base zeroes the
// unmodelled dword and MSVC drops the base's own vftable store as dead, which
// is why retail writes +0x04 before +0x00.
//
// Unlike the 49-byte family the two copied dwords are stored straight off
// `this` instead of through a `lea ecx,[eax+8]`: with only two dwords MSVC 7.1
// inlines the sub-object copy without materialising its address.  Same source
// shape, different inlining.
//
// WHY THE COPIES ARE NOT FOLDED, AND WHY THE NAMES ARE ADDRESS-DERIVED: as in
// FunctorBindConstructors.cpp.  30 distinct addresses, 30 separate template
// instantiations, and no surviving name for the class -- the only RTTI
// descriptor the framework leaves in the image is `.?AVFunctorNotSet@@`.


// WHAT +0x04 IS.  The dword the head zeroes is a REFERENCE COUNT, and the
// holders appended below are what prove it: every one of them allocates a
// wrapper, runs this constructor, and then does `inc dword ptr [eax+4]` on the
// result -- raising to one the counter this constructor had just set to zero.
// It is named m_refCount here for that reason; before the holders it was only
// an unmodelled dword.  The counter is non-atomic, a plain `inc`.
//
// THE HOLDERS.  Each wrapper is paired with two 64-byte-family constructors of
// a holder that owns one:
//
//     push 16 / mov esi,ecx / call operator new / add esp,4 / test eax,eax /
//     je <null> / <this constructor, inlined> / jmp <done> /
//     <null>: xor eax,eax / <done>: test eax,eax / mov [esi],eax /
//     je +3 / inc dword ptr [eax+4] / mov eax,esi / pop esi / ret
//
// which is `m_ptr = new WRAPPER( binding ); if ( m_ptr ) m_ptr->m_refCount++;`
// -- MSVC 7.1's `new` expression is exactly the allocate, null-test, inlined
// construct, and the null-test around the increment is separate from it.  The
// allocation size is 16 bytes, which is the whole wrapper: vftable, counter and
// the eight-byte binding.
//
// The two holders per wrapper differ ONLY in how the binding arrives.  The
// longer takes `const FunctorBindingSingle &` and reads through the pointer; the shorter takes it
// BY VALUE and reads the caller's own stack slots, which is why it consumes
// 8 bytes of arguments instead of four and why its copy has no pointer to
// dereference.  Nothing else about them differs.

class __single_inheritance FunctorTargetSingle;

typedef void (FunctorTargetSingle::*FunctorMethodSingle)(void);

struct FunctorBindingSingle
{
	FunctorTargetSingle *m_target;
	FunctorMethodSingle  m_method;
};

class FunctorSingleWrapperHead
{
public:
	FunctorSingleWrapperHead() : m_refCount( 0 ) {}

	virtual void functorSingleWrapperAnchor();

	unsigned int m_refCount;
};

#define BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( NAME )                              \
	class NAME : public FunctorSingleWrapperHead                              \
	{                                                                         \
	public:                                                                   \
		NAME( const FunctorBindingSingle &binding );                          \
                                                                              \
		FunctorBindingSingle m_binding;                                       \
	};                                                                        \
	NAME::NAME( const FunctorBindingSingle &binding ) : m_binding( binding ) {}

BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0049A120FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva005102A0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0051BDE0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva00520AB0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva00520AF0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva00522570FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva00525A30FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0052E240FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0052E280FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva00546510FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva00546550FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva00546590FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0054D870FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0054D8B0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva005542A0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva005542E0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva00558E00FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva00558E40FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva00558E80FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva00566A60FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva00582470FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0058CF10FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0058CF50FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0058CF80FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0058CFD0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0058D030FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0058D070FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0058D0A0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0058D0E0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0058D1E0FunctorSingleWrapper )

#define BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( NAME, WRAPPER )                       \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		NAME( const FunctorBindingSingle &binding );                          \
                                                                              \
		WRAPPER *m_ptr;                                                       \
	};                                                                        \
	NAME::NAME( const FunctorBindingSingle &binding )                      \
	{                                                                         \
		m_ptr = new WRAPPER( binding );                                       \
		if ( m_ptr != 0 )                                                     \
			m_ptr->m_refCount++;                                              \
	}

#define BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( NAME, WRAPPER )                           \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		NAME( FunctorBindingSingle binding );                                 \
                                                                              \
		WRAPPER *m_ptr;                                                       \
	};                                                                        \
	NAME::NAME( FunctorBindingSingle binding )                             \
	{                                                                         \
		m_ptr = new WRAPPER( binding );                                       \
		if ( m_ptr != 0 )                                                     \
			m_ptr->m_refCount++;                                              \
	}

BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva0049A2E0FunctorSingleHolder, Rva0049A120FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva00510420FunctorSingleHolder, Rva005102A0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva0051BE90FunctorSingleHolder, Rva0051BDE0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva00520DD0FunctorSingleHolder, Rva00520AB0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva00520E20FunctorSingleHolder, Rva00520AF0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva00522910FunctorSingleHolder, Rva00522570FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva005265A0FunctorSingleHolder, Rva00525A30FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva0052ECA0FunctorSingleHolder, Rva0052E240FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva0052ECF0FunctorSingleHolder, Rva0052E280FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva00546720FunctorSingleHolder, Rva00546510FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva00546770FunctorSingleHolder, Rva00546550FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva005467C0FunctorSingleHolder, Rva00546590FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva0054E480FunctorSingleHolder, Rva0054D870FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva0054E4D0FunctorSingleHolder, Rva0054D8B0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva005543D0FunctorSingleHolder, Rva005542A0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva00554420FunctorSingleHolder, Rva005542E0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva005590F0FunctorSingleHolder, Rva00558E00FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva00559140FunctorSingleHolder, Rva00558E40FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva00559190FunctorSingleHolder, Rva00558E80FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva00566E20FunctorSingleHolder, Rva00566A60FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva00582880FunctorSingleHolder, Rva00582470FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva0058F840FunctorSingleHolder, Rva0058CF10FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva0058F890FunctorSingleHolder, Rva0058CF50FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva0058F8E0FunctorSingleHolder, Rva0058CF80FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva0058F930FunctorSingleHolder, Rva0058CFD0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva0058F980FunctorSingleHolder, Rva0058D030FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva0058F9D0FunctorSingleHolder, Rva0058D070FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva0058FA20FunctorSingleHolder, Rva0058D0A0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva0058FA70FunctorSingleHolder, Rva0058D0E0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_REFERENCE( Rva0058FBB0FunctorSingleHolder, Rva0058D1E0FunctorSingleWrapper )

BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva0049A3A0FunctorSingleHolder, Rva0049A120FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva00510470FunctorSingleHolder, Rva005102A0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva0051BEE0FunctorSingleHolder, Rva0051BDE0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva00520F60FunctorSingleHolder, Rva00520AB0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva00520FB0FunctorSingleHolder, Rva00520AF0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva00522CD0FunctorSingleHolder, Rva00522570FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva00527000FunctorSingleHolder, Rva00525A30FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva0052F840FunctorSingleHolder, Rva0052E240FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva0052F890FunctorSingleHolder, Rva0052E280FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva00546830FunctorSingleHolder, Rva00546510FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva00546880FunctorSingleHolder, Rva00546550FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva005468D0FunctorSingleHolder, Rva00546590FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva0054EA60FunctorSingleHolder, Rva0054D870FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva0054EAB0FunctorSingleHolder, Rva0054D8B0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva00554470FunctorSingleHolder, Rva005542A0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva005544C0FunctorSingleHolder, Rva005542E0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva005591E0FunctorSingleHolder, Rva00558E00FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva00559230FunctorSingleHolder, Rva00558E40FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva00559280FunctorSingleHolder, Rva00558E80FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva00566E70FunctorSingleHolder, Rva00566A60FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva00582E80FunctorSingleHolder, Rva00582470FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva00590D10FunctorSingleHolder, Rva0058CF10FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva00590D60FunctorSingleHolder, Rva0058CF50FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva00590DB0FunctorSingleHolder, Rva0058CF80FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva00590E00FunctorSingleHolder, Rva0058CFD0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva00590E50FunctorSingleHolder, Rva0058D030FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva00590EA0FunctorSingleHolder, Rva0058D070FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva00590EF0FunctorSingleHolder, Rva0058D0A0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva00590F40FunctorSingleHolder, Rva0058D0E0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_HOLDER_FROM_VALUE( Rva00591080FunctorSingleHolder, Rva0058D1E0FunctorSingleWrapper )

