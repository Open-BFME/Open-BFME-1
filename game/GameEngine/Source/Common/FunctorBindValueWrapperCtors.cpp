// The 6 byte-identical 25-byte wrapper constructors of the functor-bind
// family's BY-VALUE variant.
//
// Companion to FunctorBindSlotWrapperCtors.cpp; read
// FunctorBindWrapperCtors.cpp's header first for how the family's layout was
// recovered.  Retail:
//
//     mov eax,ecx / mov ecx,[esp+4]
//     mov [eax+4],0 / mov [eax],<vftable>
//     mov [eax+8],ecx / ret 4
//
// The one-dword constructor again, two bytes shorter because the argument
// register is stored straight into +0x08 with no load through it.  That single
// difference is the whole reading: the 27-byte variant is
// `mov edx,[ecx] / mov [eax+8],edx`, an argument that must be dereferenced --
// a reference to a one-dword object -- whereas here the incoming dword IS the
// member, so the parameter is taken by value.  Everything else is identical:
// `mov eax,ecx` with no other use of eax is a __thiscall constructor returning
// `this`, one dword argument and `ret 4`, a vftable to +0x00 and zero to
// +0x04.
//
// The leading two dwords are a base for the reason FunctorBindInvokers.cpp
// measured; the base zeroes the unmodelled dword and MSVC drops the base's own
// vftable store as dead, which is why retail writes +0x04 before +0x00.
//
// WHY THE COPIES ARE NOT FOLDED, AND WHY THE NAMES ARE ADDRESS-DERIVED: as in
// FunctorBindConstructors.cpp.  6 distinct addresses, 6 separate template
// instantiations, and no surviving name for the class.

class FunctorValueWrapperHead
{
public:
	FunctorValueWrapperHead() : m_unmodelled_04( 0 ) {}

	virtual void functorValueWrapperAnchor();

	unsigned int m_unmodelled_04;
};

#define BFME_FUNCTOR_VALUE_WRAPPER_CTOR( NAME )                               \
	class NAME : public FunctorValueWrapperHead                               \
	{                                                                         \
	public:                                                                   \
		NAME( void *slot );                                                   \
                                                                              \
		void *m_slot;                                                         \
	};                                                                        \
	NAME::NAME( void *slot ) : m_slot( slot ) {}

BFME_FUNCTOR_VALUE_WRAPPER_CTOR( Rva00149FC0FunctorValueWrapper )
BFME_FUNCTOR_VALUE_WRAPPER_CTOR( Rva00149FF0FunctorValueWrapper )
BFME_FUNCTOR_VALUE_WRAPPER_CTOR( Rva0014A580FunctorValueWrapper )
BFME_FUNCTOR_VALUE_WRAPPER_CTOR( Rva0014A5E0FunctorValueWrapper )
BFME_FUNCTOR_VALUE_WRAPPER_CTOR( Rva0016A9F0FunctorValueWrapper )
BFME_FUNCTOR_VALUE_WRAPPER_CTOR( Rva0026FA60FunctorValueWrapper )
