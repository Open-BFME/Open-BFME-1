// The 24 byte-identical 18-byte __cdecl initialisers of BFME's OTHER
// functor-bind family -- the one whose bound pointer-to-member is a
// SINGLE-inheritance PMF.
//
// Companion to FunctorBindCdeclInit.cpp and FunctorBindInvokers.cpp; read
// FunctorBindConstructors.cpp's header first for how the family's layout was
// recovered.  Retail:
//
//     mov eax,[esp+4] / mov ecx,[esp+0xC] / mov edx,[esp+8]
//     mov [eax],ecx / mov [eax+4],edx / ret
//
// A bare `ret` with three dword slots consumed is __cdecl -- __stdcall would be
// `ret 0xC` and __thiscall `ret 8`.  The first slot is the object: eax is loaded
// from it and both stores are based on eax.  The remaining two land at +0x00 and
// +0x04, in the argument order 3rd, 2nd.
//
// WHY IT IS THE SINGLE-INHERITANCE SIBLING OF THE LANDED FAMILY.  Put it beside
// the landed __cdecl initialiser at 0x0050DF30:
//
//     0x0050DF30   self=[esp+4] a=[esp+8] b=[esp+0xC] c=[esp+0x10]
//                  [self+0]=c  [self+8]=a  [self+0xC]=b   ret
//     0x00510280   self=[esp+4] a=[esp+8]               c=[esp+0xC]
//                  [self+0]=c  [self+4]=a                 ret
//
// The same member-to-argument mapping with the pointer-to-member collapsed from
// two stack slots to one, and the skipped +0x04 member gone with it: a 4-byte
// single-inheritance PMF instead of the 8-byte {code, delta} pair.  The family's
// own invoker settles it -- 0x005102D0, in FunctorBindSingleInvokers.cpp, is
//
//     mov eax,ecx / mov ecx,[eax+8] / jmp [eax+0xC]
//
// i.e. the bound object is loaded into ecx and the code address is the very next
// dword with NO delta added, which is what a single-inheritance PMF invoked on a
// bound object looks like.  Relative to the sub-object at +0x08 those fields are
// +0x00 (object) and +0x04 (code) -- the two slots this initialiser writes.  The
// 24 initialisers and the 24 invokers occupy the same address regions
// (0x0051xxxx, 0x0052xxxx, 0x0054xxxx, 0x0055xxxx, 0x0058xxxx) and pair off one
// to one, the invoker trailing its initialiser in every region.
//
// WHY IT IS NOT SPELLED AS A CONSTRUCTOR, WHY THE COPIES ARE NOT FOLDED, AND WHY
// THE NAMES ARE ADDRESS-DERIVED: exactly as in FunctorBindCdeclInit.cpp.  MSVC
// 7.1 forces __thiscall on constructors and silently discards an explicit
// `__cdecl` on one; the 24 bodies sit at 24 distinct addresses and are 24
// separate template instantiations that merely compile to the same bytes; and
// the image witnesses this framework only through the RTTI descriptor
// `.?AVFunctorNotSet@@`, so no class name has been recovered and these rows
// claim the bytes without asserting one.

class __single_inheritance FunctorTargetSingle;

typedef void (FunctorTargetSingle::*SingleInheritancePmf)(void);

#define BFME_FUNCTOR_BIND_SINGLE_INIT( NAME )                                                     \
	struct NAME                                                                                   \
	{                                                                                             \
		FunctorTargetSingle *m_target;                                                            \
		SingleInheritancePmf m_method;                                                            \
	};                                                                                            \
	void __cdecl NAME##Init( NAME *binding, SingleInheritancePmf method, FunctorTargetSingle *target )\
	{                                                                                             \
		binding->m_target = target;                                                               \
		binding->m_method = method;                                                               \
	}

BFME_FUNCTOR_BIND_SINGLE_INIT( Rva00510280FunctorBind )
BFME_FUNCTOR_BIND_SINGLE_INIT( Rva0051BDC0FunctorBind )
BFME_FUNCTOR_BIND_SINGLE_INIT( Rva00520A70FunctorBind )
BFME_FUNCTOR_BIND_SINGLE_INIT( Rva00520A90FunctorBind )
BFME_FUNCTOR_BIND_SINGLE_INIT( Rva00522550FunctorBind )
BFME_FUNCTOR_BIND_SINGLE_INIT( Rva005264F0FunctorBind )
BFME_FUNCTOR_BIND_SINGLE_INIT( Rva0052E140FunctorBind )
BFME_FUNCTOR_BIND_SINGLE_INIT( Rva0052E160FunctorBind )
BFME_FUNCTOR_BIND_SINGLE_INIT( Rva005464B0FunctorBind )
BFME_FUNCTOR_BIND_SINGLE_INIT( Rva005464D0FunctorBind )
BFME_FUNCTOR_BIND_SINGLE_INIT( Rva005464F0FunctorBind )
BFME_FUNCTOR_BIND_SINGLE_INIT( Rva0054D800FunctorBind )
BFME_FUNCTOR_BIND_SINGLE_INIT( Rva0054D820FunctorBind )
BFME_FUNCTOR_BIND_SINGLE_INIT( Rva00554260FunctorBind )
BFME_FUNCTOR_BIND_SINGLE_INIT( Rva00554280FunctorBind )
BFME_FUNCTOR_BIND_SINGLE_INIT( Rva00558DA0FunctorBind )
BFME_FUNCTOR_BIND_SINGLE_INIT( Rva00558DC0FunctorBind )
BFME_FUNCTOR_BIND_SINGLE_INIT( Rva00558DE0FunctorBind )
BFME_FUNCTOR_BIND_SINGLE_INIT( Rva00566A40FunctorBind )
BFME_FUNCTOR_BIND_SINGLE_INIT( Rva0058F5F0FunctorBind )
BFME_FUNCTOR_BIND_SINGLE_INIT( Rva0058F610FunctorBind )
BFME_FUNCTOR_BIND_SINGLE_INIT( Rva0058F630FunctorBind )
BFME_FUNCTOR_BIND_SINGLE_INIT( Rva0058F650FunctorBind )
BFME_FUNCTOR_BIND_SINGLE_INIT( Rva0058F670FunctorBind )
