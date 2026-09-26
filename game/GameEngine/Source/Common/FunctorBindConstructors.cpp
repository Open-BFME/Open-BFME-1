// The 82 byte-identical 25-byte constructors of BFME's functor-binding family.
//
// WHAT THE BODY IS.  Retail:
//
//     mov edx,[esp+4] / mov eax,ecx / mov ecx,[esp+0xC] / mov [eax],ecx
//     mov ecx,[esp+8] / mov [eax+8],edx / mov [eax+0xC],ecx / ret 0xC
//
// `mov eax,ecx` with no other use of eax is a constructor returning `this`;
// three dword arguments; stores land at +0x00, +0x08, +0x0C in that order, so
// those are the members in DECLARATION order and +0x04 is a member this
// constructor leaves alone.
//
// WHY THE ARGUMENTS ARE A POINTER-TO-MEMBER PLUS AN OBJECT.  The neighbours of
// the first cluster settle the layout.  0x0050DB20 is the call operator of the
// wrapper that embeds one of these at +0x08:
//
//     mov eax,ecx / mov ecx,[eax+0x14] / add ecx,[eax+8] / jmp [eax+0x10]
//
// -- `this` for the dispatched call is (object + delta) and the code address is
// a third field, which is MSVC's multiple-inheritance pointer-to-member-function
// representation {code, delta} bound to an object.  Relative to the embedded
// sub-object at +0x08 those fields sit at +0x00 (object), +0x08 (code) and
// +0x0C (delta) -- exactly the three slots this constructor writes, and exactly
// what `(m_obj, <unused>, m_pmf)` produces when the second argument is an
// 8-byte pointer-to-member occupying stack slots 1 and 2 and the object is the
// third.  0x0050DAE0, the wrapper's copy constructor, corroborates it: vftable
// to +0x00, zero to +0x04, then sixteen bytes copied into +0x08.
//
// WHY THE NAMES ARE ADDRESS-DERIVED.  The image witnesses the framework's
// existence but not this class's name: the only surviving RTTI descriptor for
// it is `.?AVFunctorNotSet@@`, the exception type, and no other "Functor"
// string or symbol appears anywhere in the image or the ledger.  The 82 bodies
// are 82 separate template instantiations, kept apart rather than folded, and
// each is named here for its own address so the row claims the bytes without
// asserting a class name nobody has recovered.  Promoting them is a mechanical
// repoint once the template is named.
//
// The prior verdict on 0x0050DA20 recorded "86-fam ICF-folded ... never
// reproduced from any of 50+ C++ shape variants".  Both halves are wrong: the
// copies are 82 and are NOT folded (they occupy 82 distinct addresses), and a
// plain three-member class with a two-argument constructor reproduces the bytes
// on the first attempt.

class __multiple_inheritance FunctorTarget;

typedef void (FunctorTarget::*FunctorMethod)(void);

#define BFME_FUNCTOR_BIND_CTOR(NAME)                                          \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		NAME( FunctorMethod method, FunctorTarget *target );                  \
                                                                              \
	private:                                                                  \
		FunctorTarget *m_target;                                              \
		unsigned int   m_unmodelled_04;                                       \
		FunctorMethod  m_method;                                              \
	};                                                                        \
	NAME::NAME( FunctorMethod method, FunctorTarget *target )                 \
		: m_target( target ), m_method( method ) {}

BFME_FUNCTOR_BIND_CTOR( Rva0050DA20FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0050DA40FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0050DA60FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0050DA80FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0050DAA0FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0050DAC0FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0050E7A0FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0050E7C0FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0050E7E0FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0050E850FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0050E870FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0050E890FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva00511620FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva00511640FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva00511660FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva00511930FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva00511950FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva00511970FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva00516BD0FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva00516BF0FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva00517990FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva005179B0FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0051D390FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0051D3B0FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0051D3D0FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0051D3F0FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0051D410FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0051E340FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0051E360FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0051E380FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0051E3A0FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0051E3C0FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0052B230FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0052B250FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0052B270FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0052B680FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0052B6A0FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0052B6C0FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva00538000FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva00538020FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva00538AD0FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva00538AF0FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0055BFA0FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0055BFC0FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0055C130FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0055C150FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0055E230FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0055E250FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0055E270FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0055ED50FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0055ED70FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0055ED90FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva00569640FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva00569660FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva00569BF0FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva00569C10FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0056BEC0FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0056BEE0FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0056BF00FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0056BF20FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0056C920FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0056C940FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0056C960FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0056C980FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva00570A40FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva00570A60FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva00570A80FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva00571670FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva00571690FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva005716B0FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva00579330FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva00579350FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva00579370FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva005793E0FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva00579400FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva00579420FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0058B120FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0058B140FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0058CDE0FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva0058CE00FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva00599310FunctorBind )
BFME_FUNCTOR_BIND_CTOR( Rva00599610FunctorBind )
