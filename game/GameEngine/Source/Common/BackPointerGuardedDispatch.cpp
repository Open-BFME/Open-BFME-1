// The six byte-identical 40-byte guarded dispatchers at 0x00259210, 0x00259E20,
// 0x0025B8E0, 0x0025D830, 0x00262D60 and 0x0026B7E0 -- all six in one drawer of
// the retail image, none of them referenced by any call or by any vftable slot
// the inventory knows, so the bytes are the only evidence there is.
//
//     mov eax,[ecx-8] / mov edx,[eax+0x1A4] / test edx,edx / jne done
//     mov eax,[esp+4] / test eax,eax / je done
//     mov edx,[ecx] / push esi / mov esi,[esp+0xC] / push esi
//     add eax,0x38 / push eax / call dword ptr [edx+0x34] / pop esi
//     done: ret 8
//
// WHAT THE BYTES SHOW.  `this` in ecx, two stack arguments, `ret 8`: __thiscall.
// `mov edx,[ecx]` loads a vftable from offset 0 and dispatches slot 0x34 with
// ecx untouched, so the class is polymorphic and the call is `this->something()`
// on itself, not on either argument.
//
// `mov eax,[ecx-8]` IS THE INTERESTING BYTE.  A NEGATIVE displacement off `this`
// means the source computed a fixed offset backwards out of the object, and what
// it finds there is a POINTER, because the very next instruction dereferences it
// at +0x1A4.  So an object of about 420 bytes owns this one and keeps its own
// back-reference eight bytes ahead of it, and the dispatcher's first act is to
// read a field of that owner and do nothing at all when it is non-zero.
//
// This is not a virtual base and not a vtordisp adjustment.  Both were compiled
// and neither produces these bytes: an override reached through a virtual base's
// vftable reads its adjustment at [ecx-4] and then does vbptr arithmetic, which
// is ten bytes longer and a different shape.  Multiple inheritance does not
// produce it either -- MSVC makes the polymorphic base primary, so the
// non-polymorphic half lands at a POSITIVE offset and the adjustment goes into a
// separate thunk.  What matches is a plain fixed-displacement read back out of
// the object, which is what is written below.
//
// The rest is a two-stage guard and a forward: return if the owner's field is
// set, return if the first argument is null, otherwise dispatch slot 0x34 with a
// reference to that argument's member at +0x38 and the second argument
// unchanged.  Both early exits jump to the SAME `ret 8`, and `push esi` sits
// inside the surviving path so neither guard pays for it -- /O2 shrink wrapping,
// which needs nothing from the source.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  Six addresses, six instantiations over six
// sets of classes that coincide because the offsets and the dispatched slot
// coincide.  Nothing here defeats inlining, so there is no per-translation-unit
// COMDAT argument for asserting they are one function.
//
// IDENTITY IS NOT RECOVERED.  No caller, no vftable slot and no string reaches
// any of the six, so nothing in the image names the owner, the arguments or the
// dispatcher.  Every name below is address-derived and disclaims identity.

#define BFME_BACKPOINTER_GUARDED_DISPATCH( NAME )                             \
	class NAME##Owner                                                         \
	{                                                                         \
	public:                                                                   \
		char m_leading[ 0x1A4 ];                                              \
		int m_gate;                                                           \
	};                                                                        \
	struct NAME##Part                                                         \
	{                                                                         \
		int m_word0;                                                          \
	};                                                                        \
	class NAME##Subject                                                       \
	{                                                                         \
	public:                                                                   \
		char m_leading[ 0x38 ];                                               \
		NAME##Part m_part;                                                    \
	};                                                                        \
	class NAME##Context;                                                      \
	class NAME##Dispatcher                                                    \
	{                                                                         \
	public:                                                                   \
		virtual void slot00(); virtual void slot04();                         \
		virtual void slot08(); virtual void slot0C();                         \
		virtual void slot10(); virtual void slot14();                         \
		virtual void slot18(); virtual void slot1C();                         \
		virtual void slot20(); virtual void slot24();                         \
		virtual void slot28(); virtual void slot2C();                         \
		virtual void slot30();                                                \
		virtual void apply( NAME##Part *part, NAME##Context *context );       \
		void run( NAME##Subject *subject, NAME##Context *context );           \
	};                                                                        \
	void NAME##Dispatcher::run( NAME##Subject *subject,                       \
	                            NAME##Context *context )                      \
	{                                                                         \
		NAME##Owner *owner = *(NAME##Owner **)( (char *)this - 8 );           \
		if ( owner->m_gate != 0 )                                             \
		{                                                                     \
			return;                                                           \
		}                                                                     \
		if ( subject == 0 )                                                   \
		{                                                                     \
			return;                                                           \
		}                                                                     \
		apply( &subject->m_part, context );                                   \
	}

BFME_BACKPOINTER_GUARDED_DISPATCH( Rva00259210 )
BFME_BACKPOINTER_GUARDED_DISPATCH( Rva00259E20 )
BFME_BACKPOINTER_GUARDED_DISPATCH( Rva0025B8E0 )
BFME_BACKPOINTER_GUARDED_DISPATCH( Rva0025D830 )
BFME_BACKPOINTER_GUARDED_DISPATCH( Rva00262D60 )
BFME_BACKPOINTER_GUARDED_DISPATCH( Rva0026B7E0 )

// ---------------------------------------------------------------------------
// The five byte-identical 57-byte guarded dispatchers at 0x00259250,
// 0x00259E60, 0x0025B920, 0x0025D870 and 0x0026B820 -- each one sits 0x40 bytes
// past a member of the family above, in the same drawers, and repeats its
// opening verbatim.  Retail:
//
//     mov eax,[ecx-8] / mov edx,[eax+0x1A4] / sub esp,0xC
//     test edx,edx / jne done
//     mov edx,[eax+0x38] / mov [esp],edx
//     mov edx,[eax+0x3C] / mov [esp+4],edx
//     mov eax,[eax+0x40] / mov edx,[ecx] / mov [esp+8],eax
//     mov eax,[esp+0x10] / push eax / lea eax,[esp+4] / push eax
//     call dword ptr [edx+0x34] / add esp,0xC
//     done: ret 4
//
// Same owner back-reference at [ecx-8], same gate at owner+0x1A4, same vftable
// slot 0x34 on `this`, and the same two-argument call whose first argument is
// an address and whose second is the one incoming stack argument.  What differs
// is where that address comes from: instead of a member of an argument, it is a
// TWELVE-BYTE STACK TEMPORARY -- `sub esp,0xC` builds it, `lea eax,[esp+4]`
// takes its address (esp having just moved by the `push`), and `add esp,0xC`
// releases it.  There is no argument null check here because there is no
// argument pointer to check.
//
// THE THREE FIELDS ARE COPIED ONE AT A TIME, and that is source evidence, not
// scheduling.  Copying a three-dword SUBOBJECT -- `Triple t = owner->m_trip;`
// -- makes MSVC 7.1 compute the subobject's address once (`add eax,0x38`) and
// then read `[eax]`, `[eax+4]`, `[eax+8]`: a 59-byte body, two bytes long and
// wrong in five places.  Retail reads `[eax+0x38]`, `[eax+0x3C]`, `[eax+0x40]`
// directly off the owner, which is what three separate member-to-member
// assignments produce.  So the owner holds three scalars there, not a nested
// struct, and the source names each of them.  (The same distinction settled the
// container-of accessors in ContainerOfGuardedAccessors.cpp: naming the
// composite once lets the optimiser fold, and retail did not fold.)
//
// `mov edx,[ecx]` landing BETWEEN the second and third store is scheduling and
// needs nothing from the source; the matching spelling reproduces it.  Writing
// the guard as `if (gate == 0) { ... }` instead of an early return reorders the
// three stores and fails.
//
// SEPARATE FUNCTIONS, NOT ALIASES; IDENTITY IS NOT RECOVERED.  As above: five
// addresses, five instantiations, nothing in the image naming any of them.

#define BFME_BACKPOINTER_GUARDED_TRIPLE_DISPATCH( NAME )                      \
	class NAME##Owner                                                         \
	{                                                                         \
	public:                                                                   \
		char m_leading[ 0x38 ];                                               \
		int m_first;                                                          \
		int m_second;                                                         \
		int m_third;                                                          \
		char m_trailing[ 0x1A4 - 0x44 ];                                      \
		int m_gate;                                                           \
	};                                                                        \
	class NAME##Triple                                                        \
	{                                                                         \
	public:                                                                   \
		int m_first;                                                          \
		int m_second;                                                         \
		int m_third;                                                          \
	};                                                                        \
	class NAME##Context;                                                      \
	class NAME##Dispatcher                                                    \
	{                                                                         \
	public:                                                                   \
		virtual void slot00(); virtual void slot04();                         \
		virtual void slot08(); virtual void slot0C();                         \
		virtual void slot10(); virtual void slot14();                         \
		virtual void slot18(); virtual void slot1C();                         \
		virtual void slot20(); virtual void slot24();                         \
		virtual void slot28(); virtual void slot2C();                         \
		virtual void slot30();                                                \
		virtual void apply( NAME##Triple *triple, NAME##Context *context );   \
		void run( NAME##Context *context );                                   \
	};                                                                        \
	void NAME##Dispatcher::run( NAME##Context *context )                      \
	{                                                                         \
		NAME##Owner *owner = *(NAME##Owner **)( (char *)this - 8 );           \
		if ( owner->m_gate != 0 )                                             \
		{                                                                     \
			return;                                                           \
		}                                                                     \
		NAME##Triple triple;                                                  \
		triple.m_first = owner->m_first;                                      \
		triple.m_second = owner->m_second;                                    \
		triple.m_third = owner->m_third;                                      \
		apply( &triple, context );                                            \
	}

BFME_BACKPOINTER_GUARDED_TRIPLE_DISPATCH( Rva00259250 )
BFME_BACKPOINTER_GUARDED_TRIPLE_DISPATCH( Rva00259E60 )
BFME_BACKPOINTER_GUARDED_TRIPLE_DISPATCH( Rva0025B920 )
BFME_BACKPOINTER_GUARDED_TRIPLE_DISPATCH( Rva0025D870 )
BFME_BACKPOINTER_GUARDED_TRIPLE_DISPATCH( Rva0026B820 )
