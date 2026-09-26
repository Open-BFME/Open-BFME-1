// The 41 byte-identical 11-byte invokers of BFME's functor-binding family.
//
// Companion to FunctorBindConstructors.cpp; read that file's header first for
// how the family's layout was recovered.  Retail:
//
//     mov eax,ecx / mov ecx,[eax+0x14] / add ecx,[eax+8] / jmp [eax+0x10]
//
// `this` is copied out of ecx precisely because ecx is needed for the call it
// tail-jumps into: ecx becomes (object + delta) and the code address comes from
// a third slot, which is MSVC's multiple-inheritance pointer-to-member-function
// {code, delta} invoked on a bound object.  In wrapper coordinates the bound
// sub-object sits at +0x08 -- object +0x08, unmodelled +0x0C, code +0x10,
// delta +0x14 -- which is the same sixteen bytes the family's copy constructor
// at 0x0050DAE0 copies to +0x08 after writing a vftable to +0x00 and zero to
// +0x04.  The two leading dwords are therefore a vftable slot and one
// unmodelled dword, and they are modelled here as a polymorphic base rather
// than as raw padding so the vftable slot the copy constructor writes has
// somewhere real to live.
//
// Layout note worth keeping: in MSVC 7.1 a class whose FIRST declared virtual
// is in the same class as the bound sub-object places that sub-object eight
// bytes further along than the naive count, so the wrapper cannot be spelled as
// one class with a virtual and the bind inline -- probed both ways, they emit
// [eax+0x1C]/[eax+0x18].  Splitting the vftable and the +0x04 dword into a base
// gives retail's [eax+0x14]/[eax+0x10] exactly.
//
// Names are address-derived for the same reason as the constructors: the image
// witnesses the framework only through the RTTI descriptor `.?AVFunctorNotSet@@`
// and carries no other Functor string or symbol, so the class template's real
// name has not been recovered and these rows claim bytes without asserting one.

class __multiple_inheritance FunctorTarget;

typedef void (FunctorTarget::*FunctorMethod)(void);

struct FunctorBinding
{
	FunctorTarget *m_target;
	unsigned int   m_unmodelled_04;
	FunctorMethod  m_method;
};

class FunctorWrapperHead
{
public:
	virtual void functorWrapperAnchor();

	unsigned int m_unmodelled_04;
};

#define BFME_FUNCTOR_INVOKE(NAME)                                             \
	class NAME : public FunctorWrapperHead                                    \
	{                                                                         \
	public:                                                                   \
		void invoke( void );                                                  \
                                                                              \
		FunctorBinding m_binding;                                             \
	};                                                                        \
	void NAME::invoke( void )                                                 \
	{                                                                         \
		( m_binding.m_target->*m_binding.m_method )();                        \
	}

BFME_FUNCTOR_INVOKE( Rva0050DB20FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva0050DB70FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva0050DBC0FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva0050E8F0FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva0050E940FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva0050E990FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva005119E0FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva00511A30FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva00511A80FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva00517A10FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva00517A60FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva0051E420FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva0051E470FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva0051E4C0FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva0051E510FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva0051E560FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva0052B720FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva0052B770FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva0052B7C0FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva00538BC0FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva00538C10FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva0055C630FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva0055C680FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva0055EDF0FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva0055EE40FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva0055EE90FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva00569C70FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva00569CC0FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva0056C9E0FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva0056CA30FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva0056CA80FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva0056CAD0FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva00571770FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva005717C0FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva00571810FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva0057A060FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva0057A0B0FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva0057A100FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva0058D260FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva0058D2B0FunctorInvoke )
BFME_FUNCTOR_INVOKE( Rva00599670FunctorInvoke )
