// The seven byte-identical 14-byte guarded accessors at 0x001EEAE0, 0x001F35C0,
// 0x001FB210, 0x001FBE90, 0x0020B060, 0x00219360 and 0x002D3170.  Retail:
//
//     lea eax,[ecx-0xC] / test eax,eax / je null
//     lea eax,[ecx+0x1C] / ret
//     null: xor eax,eax / ret
//
// WHAT THE BYTES SHOW.  `this` in ecx, no stack argument, plain `ret`, a
// pointer-sized result in eax: a __thiscall member function of no arguments
// returning an address.
//
// `lea eax,[ecx-0xC]` IS THE INTERESTING INSTRUCTION.  A NEGATIVE displacement
// off `this` that is then tested for null and never dereferenced here is the
// container-of idiom: the object at `this` sits twelve bytes into a larger one,
// and the source recovers the enclosing object by subtracting that offset.  It
// is not a vtordisp and not a virtual-base adjustment -- both of those read an
// adjustment word out of the object first, and neither can produce a bare `lea`
// with no load around it.
//
// WHY THE SECOND `lea` IS OFF ecx AND NOT OFF eax.  The returned address is the
// owner's member at owner+0x28, which is this+0x1C.  A body that names the
// owner ONCE and reuses it -- `Owner *o = owner(); return o ? &o->m : 0;` --
// compiles to `add eax,0x28`, because eax already holds the owner and the
// optimiser adds to it.  Retail instead recomputes the whole address from ecx
// in a single `lea`, which is what MSVC 7.1 emits when the source spells the
// owner TWICE: the guard evaluates one copy, the returned expression is a
// second, independent `(char *)this - 0xC + 0x28`, and constant folding
// collapses it to `this + 0x1C`.  Eight spellings were compiled; only the
// doubled accessor reproduces all fourteen bytes, and the single-name form is
// exactly the `add eax,0x28` residue an earlier attempt on this family logged.
//
// The dead `xor eax,eax` on the null path -- eax is provably zero there, the
// `test` just said so -- is the compiler materialising the source's literal
// null return rather than falling through, and needs nothing from the source.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  Seven addresses cannot be one COMDAT; they
// are seven accessors over seven pairs of classes whose offsets -- owner at
// -0xC, member at +0x28 -- happen to coincide.  Distinct bodies are written
// below for that reason.
//
// IDENTITY IS NOT RECOVERED.  No caller, no vftable slot and no string reaches
// any of the seven, so every name below is address-derived and disclaims
// identity.

#define BFME_CONTAINER_OF_GUARDED_ACCESSOR( NAME )                            \
	class NAME##Field                                                         \
	{                                                                         \
	public:                                                                   \
		int m_word0;                                                          \
	};                                                                        \
	class NAME##Owner;                                                        \
	class NAME##Part                                                          \
	{                                                                         \
	public:                                                                   \
		NAME##Owner *owner() const;                                           \
		NAME##Field *field();                                                 \
	};                                                                        \
	class NAME##Owner                                                         \
	{                                                                         \
	public:                                                                   \
		char m_leading[ 0x28 ];                                               \
		NAME##Field m_field;                                                  \
	};                                                                        \
	inline NAME##Owner *NAME##Part::owner() const                             \
	{                                                                         \
		return (NAME##Owner *)( (char *)this - 0xC );                         \
	}                                                                         \
	NAME##Field *NAME##Part::field()                                          \
	{                                                                         \
		return owner() ? &owner()->m_field : 0;                               \
	}

BFME_CONTAINER_OF_GUARDED_ACCESSOR( Rva001EEAE0 )
BFME_CONTAINER_OF_GUARDED_ACCESSOR( Rva001F35C0 )
BFME_CONTAINER_OF_GUARDED_ACCESSOR( Rva001FB210 )
BFME_CONTAINER_OF_GUARDED_ACCESSOR( Rva001FBE90 )
BFME_CONTAINER_OF_GUARDED_ACCESSOR( Rva0020B060 )
BFME_CONTAINER_OF_GUARDED_ACCESSOR( Rva00219360 )
BFME_CONTAINER_OF_GUARDED_ACCESSOR( Rva002D3170 )
