// The 24 byte-identical 8-byte invokers of BFME's single-inheritance
// functor-bind family.
//
// Companion to FunctorBindSingleInit.cpp -- read that file's header for how this
// family was separated from the landed multiple-inheritance one in
// FunctorBindInvokers.cpp.  Retail:
//
//     mov eax,ecx / mov ecx,[eax+8] / jmp [eax+0xC]
//
// `this` is copied out of ecx precisely because ecx is needed for the call it
// tail-jumps into: ecx becomes the bound object and the code address is the next
// dword.  No delta is added -- that is the whole difference from the landed
// invoker at 0x0050DB20, `mov ecx,[eax+0x14] / add ecx,[eax+8] / jmp [eax+0x10]`
// -- so the bound pointer-to-member is a 4-byte single-inheritance PMF, not the
// 8-byte {code, delta} pair.
//
// In wrapper coordinates the bound sub-object sits at +0x08 (object +0x08, code
// +0x0C), which leaves two dwords ahead of it.  As in FunctorBindInvokers.cpp
// they are modelled as a polymorphic base -- a vftable slot and one unmodelled
// dword -- rather than as raw padding.  Worth recording: unlike the
// multiple-inheritance family the layout does NOT depend on that split here.
// The landed file notes that MSVC 7.1 places a sub-object holding a
// `__multiple_inheritance` PMF eight bytes further along than the naive count
// when the enclosing class declares its own first virtual, which forced the
// base; probed both ways here, a single class with its own first virtual and the
// binding inline emits the same [eax+8]/[eax+0xC], because a 4-byte PMF makes no
// alignment demand that could push the sub-object along.  The base is kept
// anyway, so that the vftable slot the family's copy constructors write has
// somewhere real to live and so the two invoker files read the same way.
//
// Names are address-derived for the same reason as the rest of the family: the
// image witnesses it only through the RTTI descriptor `.?AVFunctorNotSet@@` and
// carries no other Functor string or symbol, so these rows claim bytes without
// asserting a class name nobody has recovered.

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
	virtual void functorSingleWrapperAnchor();

	unsigned int m_unmodelled_04;
};

#define BFME_FUNCTOR_SINGLE_INVOKE( NAME )                                    \
	class NAME : public FunctorSingleWrapperHead                               \
	{                                                                          \
	public:                                                                    \
		void invoke( void );                                                   \
                                                                               \
		FunctorBindingSingle m_binding;                                        \
	};                                                                         \
	void NAME::invoke( void )                                                  \
	{                                                                          \
		( m_binding.m_target->*m_binding.m_method )();                         \
	}

BFME_FUNCTOR_SINGLE_INVOKE( Rva005102D0FunctorInvoke )
BFME_FUNCTOR_SINGLE_INVOKE( Rva0051BE10FunctorInvoke )
BFME_FUNCTOR_SINGLE_INVOKE( Rva00520AE0FunctorInvoke )
BFME_FUNCTOR_SINGLE_INVOKE( Rva00520B20FunctorInvoke )
BFME_FUNCTOR_SINGLE_INVOKE( Rva005225A0FunctorInvoke )
BFME_FUNCTOR_SINGLE_INVOKE( Rva00525A60FunctorInvoke )
BFME_FUNCTOR_SINGLE_INVOKE( Rva0052E270FunctorInvoke )
BFME_FUNCTOR_SINGLE_INVOKE( Rva0052E2B0FunctorInvoke )
BFME_FUNCTOR_SINGLE_INVOKE( Rva00546540FunctorInvoke )
BFME_FUNCTOR_SINGLE_INVOKE( Rva00546580FunctorInvoke )
BFME_FUNCTOR_SINGLE_INVOKE( Rva005465C0FunctorInvoke )
BFME_FUNCTOR_SINGLE_INVOKE( Rva0054D8A0FunctorInvoke )
BFME_FUNCTOR_SINGLE_INVOKE( Rva0054D8E0FunctorInvoke )
BFME_FUNCTOR_SINGLE_INVOKE( Rva005542D0FunctorInvoke )
BFME_FUNCTOR_SINGLE_INVOKE( Rva00554310FunctorInvoke )
BFME_FUNCTOR_SINGLE_INVOKE( Rva00558E30FunctorInvoke )
BFME_FUNCTOR_SINGLE_INVOKE( Rva00558E70FunctorInvoke )
BFME_FUNCTOR_SINGLE_INVOKE( Rva00558EB0FunctorInvoke )
BFME_FUNCTOR_SINGLE_INVOKE( Rva00566A90FunctorInvoke )
BFME_FUNCTOR_SINGLE_INVOKE( Rva0058CF40FunctorInvoke )
BFME_FUNCTOR_SINGLE_INVOKE( Rva0058D060FunctorInvoke )
BFME_FUNCTOR_SINGLE_INVOKE( Rva0058D0D0FunctorInvoke )
BFME_FUNCTOR_SINGLE_INVOKE( Rva0058D110FunctorInvoke )
BFME_FUNCTOR_SINGLE_INVOKE( Rva0058D210FunctorInvoke )
