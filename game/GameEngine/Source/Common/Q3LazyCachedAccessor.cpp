// Eight copies of a lazily-filled cached pointer, reached one indirection deep.
//
// WHAT THE BYTES SHOW.  A __thiscall with no stack arguments.  It loads the
// dword at offset 4 of the receiver -- call it the owner -- then the dword at a
// fixed large offset inside the owner.  If that is non-null it returns it.  If
// it is null it calls a ONE-argument cdecl helper with the owner, stores the
// result back into the owner at the same offset, and returns it.
//
// The owner pointer is RE-LOADED from offset 4 three separate times: once for
// the test and the helper argument, once for the store-back, once for the
// return.  That is not the compiler being redundant -- an optimiser folds those
// into one register when the source names the composite once.  Retail did not
// fold, so the SOURCE spelled the owner-and-slot expression out at each use.
//
// TWO AXES, EACH APPEARING ONCE PER ROW.  The slot offset inside the owner --
// 0x234, 0x238, 0x23C, 0x240, 0x248, 0x24C, 0x2A4, 0x2A8 -- and the helper.
// Eight rows, eight distinct offsets, eight distinct helpers; no helper turns up
// at a second offset, so the pairing is a real grid and not one axis mistaken
// for two.  One helper, 0x007E9B40, is itself a small allocator body sitting a
// few hundred bytes away from this block.
//
// IDENTITY IS NOT RECOVERED.  All names are address-derived; helper pins are
// address-derived and additive.
//
// WHAT THE BYTES CANNOT DECIDE.  The type of what is cached, and whether the
// dword at offset 0 of the receiver -- never read here -- is a vftable, a
// pointer, or anything else.

#define BFME_LAZY_CACHED_ACCESSOR( NAME, HELPER, OFFSET )                     \
	struct NAME##Cached { int m_opaque; };                                    \
	struct NAME##Owner                                                        \
	{                                                                         \
		char m_lead[ OFFSET ];                                                \
		NAME##Cached *m_slot;                                                 \
	};                                                                        \
	NAME##Cached *HELPER( NAME##Owner *owner );                               \
	struct NAME                                                               \
	{                                                                         \
		void *m_head;                                                         \
		NAME##Owner *m_owner;                                                 \
		NAME##Cached *get();                                                  \
	};                                                                        \
	NAME##Cached *NAME::get()                                                 \
	{                                                                         \
		if ( m_owner->m_slot == 0 )                                           \
			m_owner->m_slot = HELPER( m_owner );                              \
		return m_owner->m_slot;                                               \
	}

BFME_LAZY_CACHED_ACCESSOR( Rva007E9CE0, Gen007F1C20, 0x24C )
BFME_LAZY_CACHED_ACCESSOR( Rva007E9D70, Gen007E9B40, 0x234 )
BFME_LAZY_CACHED_ACCESSOR( Rva007E9DB0, Gen007F2150, 0x248 )
BFME_LAZY_CACHED_ACCESSOR( Rva007E9DF0, Gen007F2E60, 0x238 )
BFME_LAZY_CACHED_ACCESSOR( Rva007E9E30, Gen007F3410, 0x23C )
BFME_LAZY_CACHED_ACCESSOR( Rva007E9E70, Gen007F40F0, 0x240 )
BFME_LAZY_CACHED_ACCESSOR( Rva007E9EF0, Gen007F86A0, 0x2A4 )
BFME_LAZY_CACHED_ACCESSOR( Rva007E9F30, Gen007F89D0, 0x2A8 )
