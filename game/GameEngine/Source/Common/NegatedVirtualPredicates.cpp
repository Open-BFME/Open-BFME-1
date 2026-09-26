// The four byte-identical 11-byte members at 0x001713A0, 0x00171870, 0x001718F0
// and 0x0017CA20.
//
//     mov eax,[ecx] / call dword ptr [eax+0x1C] / neg al / sbb eax,eax / inc eax
//
// WHAT THE BYTES SHOW.  `this` in ecx, no arguments, no stack cleanup: a
// __thiscall member of a polymorphic class that immediately loads its own
// vftable and calls slot 7 with no arguments.  The three instructions after the
// call are MSVC 7.1's canonical logical negation of a `bool` in al: `neg al`
// sets the carry flag exactly when al is non-zero, `sbb eax,eax` turns that into
// 0 or -1, and `inc eax` turns it into 1 or 0.  Only al participates, so the
// callee returns `bool`, and the sequence is the whole tail of the function, so
// this member returns `bool` too.
//
// The call is not a tail jump even though nothing follows it but the negation,
// which is what makes the negation visible at all: the body is exactly
// `return !virtualProbe();` on a virtual the class declares seventh.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  Four distinct addresses; three of them
// (0x001713A0, 0x00171870, 0x001718F0) sit in one drawer and the fourth well
// away from it.  Nothing here defeats inlining, so the per-translation-unit
// reading that would justify an alias does not apply -- these are four negated
// wrappers over four classes whose probe happens to land in the same slot.
//
// IDENTITY IS NOT RECOVERED.  Neither the wrapper nor the probed virtual is
// named anywhere in the image, so the names are address-derived.

#define BFME_NEGATED_VIRTUAL_PREDICATE( NAME )                                \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		virtual void probePad0();                                             \
		virtual void probePad1();                                             \
		virtual void probePad2();                                             \
		virtual void probePad3();                                             \
		virtual void probePad4();                                             \
		virtual void probePad5();                                             \
		virtual void probePad6();                                             \
		virtual bool probe();                                                 \
                                                                              \
		bool absent();                                                        \
	};                                                                        \
	bool NAME::absent()                                                       \
	{                                                                         \
		return !probe();                                                      \
	}

BFME_NEGATED_VIRTUAL_PREDICATE( Rva001713A0Probe )
BFME_NEGATED_VIRTUAL_PREDICATE( Rva00171870Probe )
BFME_NEGATED_VIRTUAL_PREDICATE( Rva001718F0Probe )
BFME_NEGATED_VIRTUAL_PREDICATE( Rva0017CA20Probe )
