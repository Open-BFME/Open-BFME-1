// The 41 byte-identical 25-byte __cdecl siblings of the functor-bind
// constructor family in game/GameEngine/Source/Common/FunctorBindConstructors.cpp.
//
// WHAT THE BODY IS.  Retail:
//
//     mov eax,[esp+4] / mov ecx,[esp+0x10] / mov edx,[esp+8] / mov [eax],ecx
//     mov ecx,[esp+0xC] / mov [eax+8],edx / mov [eax+0xC],ecx / ret
//
// A bare `ret` with four dword slots consumed is __cdecl -- __stdcall would be
// `ret 0x10` and __thiscall `ret 0xC`.  The first slot is the object: eax is
// loaded from it and every store is based on eax.  The remaining three land at
// +0x00, +0x08 and +0x0C, in the argument order 4th, 2nd, 3rd.
//
// WHY IT IS THE SAME FUNCTION AS THE LANDED __thiscall FAMILY.  Put the two
// side by side with `this` counted as slot zero:
//
//     0x0050DA20 (__thiscall)  this=ecx  a=[esp+4]  b=[esp+8]  c=[esp+0xC]
//                              [this+0]=c  [this+8]=a  [this+0xC]=b  ret 0xC
//     0x0050DF30 (__cdecl)     this=[esp+4] a=[esp+8] b=[esp+0xC] c=[esp+0x10]
//                              [this+0]=c  [this+8]=a  [this+0xC]=b  ret
//
// Identical member-to-argument mapping, identical skipped slot at +0x04, one
// argument slot of shift.  These 41 bodies sit in the same dead-COMDAT zone as
// the 82 -- 0x0050Dxxx, 0x0051Exxx, 0x0056Cxxx, 0x00572xxx -- so the reading
// that settled that family settles this one: the arguments are an 8-byte
// multiple-inheritance pointer-to-member-function occupying two slots and an
// object pointer, and the three stores are {object at +0x00 code at +0x08
// delta at +0x0C}.
//
// WHY IT IS NOT SPELLED AS A CONSTRUCTOR.  It cannot be one.  MSVC 7.1 forces
// __thiscall on constructors and silently discards an explicit `__cdecl` on
// one: writing `__cdecl NAME( FunctorMethod, FunctorTarget * )` compiles to
// `??0NAME@@QAE@...` and emits the 0x0050DA20 bytes, not these.  What does
// emit these -- on the first spelling, and equally from a `__cdecl` member
// function -- is a free __cdecl function taking the object as its first
// argument, which is written here because it is the plainest C++ that asserts
// only what the bytes show.
//
// WHY THE COPIES ARE NOT FOLDED, AND WHY THE NAMES ARE ADDRESS-DERIVED: as in
// FunctorBindConstructors.cpp.  41 distinct addresses, 41 separate template
// instantiations, and no surviving name for the class -- the only RTTI
// descriptor the framework leaves in the image is `.?AVFunctorNotSet@@`.

class __multiple_inheritance FunctorTarget;

typedef void (FunctorTarget::*FunctorMethod)(void);

#define BFME_FUNCTOR_BIND_CDECL_INIT( NAME )                                            \
	struct NAME                                                                         \
	{                                                                                   \
		FunctorTarget *m_target;                                                        \
		unsigned int   m_unmodelled_04;                                                 \
		FunctorMethod  m_method;                                                        \
	};                                                                                  \
	void __cdecl NAME##Init( NAME *self, FunctorMethod method, FunctorTarget *target )  \
	{                                                                                   \
		self->m_target = target;                                                        \
		self->m_method = method;                                                        \
	}

BFME_FUNCTOR_BIND_CDECL_INIT( Rva0050DF30FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva0050DF50FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva0050DF70FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva0050F3C0FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva0050F3E0FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva0050F400FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva005122E0FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva00512300FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva00512320FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva00518030FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva00518050FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva0051EAB0FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva0051EAD0FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva0051EAF0FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva0051EB10FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva0051EB30FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva0052BB00FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva0052BB20FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva0052BB40FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva005394A0FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva005394C0FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva0055C5A0FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva0055C5C0FunctorBind )
void Rva0055C5E0FunctorNoOp( void ) {}
BFME_FUNCTOR_BIND_CDECL_INIT( Rva0055EF90FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva0055EFB0FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva0055EFD0FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva0056A090FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva0056A0B0FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva0056CDC0FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva0056CDE0FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva0056CE00FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva0056CE20FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva00572150FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva00572170FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva00572190FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva00579FC0FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva00579FE0FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva0057A000FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva0058F690FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva0058F6B0FunctorBind )
BFME_FUNCTOR_BIND_CDECL_INIT( Rva00599920FunctorBind )
