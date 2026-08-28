// Nineteen 33-byte __thiscall const members that read one field out of the
// object's data pointer after walking that pointer's override chain:
//
//   mov eax,[ecx+4] / test eax,eax / jne walk
//   <read [eax+<OFFSET>]> / ret                 ; eax is the null pointer here
//  walk:
//   mov ecx,[eax+4] / test ecx,ecx / je read
//   call ?getFinalOverride@Overridable@@QBEPBV1@XZ
//  read:
//   <read [eax+<OFFSET>]> / ret
//
// WHAT THE BYTES SHOW.  The callee resolves through incremental-link thunk
// 0x000022BB to 0x00087A80, which the ledger already carries as
// Overridable::getFinalOverride -- so the second dword of the pointed-at object
// is Overridable::m_nextOverride and the first is its vptr.  The call site
// tests that member ITSELF before calling, which is the first level of the
// override walk expanded at the call site with the rest left to the
// out-of-line copy; the argument of the call is m_nextOverride, not the object,
// so the expansion is `n ? n->getFinalOverride() : d`, not a plain call.
//
// Two families share these bytes and differ only in how the field comes back:
// `mov al,[eax+OFF]` (11 rows) and `fld dword ptr [eax+OFF]` (8 rows).  A byte
// load into al with nothing else is a one-byte field; fld is a float.
//
// WHY THE TAIL IS WRITTEN TWICE, which is the one thing here that is not
// obvious and that pins the source shape.  Retail's null arm reads
// `[eax+OFF]` with eax provably zero and does NOT fold that to the absolute
// form `a0 <OFF>` -- but every spelling in which the null case has its own
// `return d->m_field;` DOES fold, and every spelling that assigns through the
// same variable and falls into one shared tail comes out 26 bytes with no
// duplicate at all.  Only a spelling that assigns a SECOND pointer variable in
// both arms of the branch and dereferences that variable once at the end
// reproduces retail: the merged variable stays in a register and the tail is
// cloned late, after the fold would have happened.  That is evidence about the
// source, recovered from 7 bytes retail declined to shrink.
//
// TWO AXES: the field offset and the return width.  29 of the 33 bytes are
// concrete; only the call displacement is resolved, and it resolves to a name
// already matched in the ledger, so no new pin was needed for this file.
//
// WHAT THE BYTES DO NOT DECIDE.  `mov al` fits bool, char and unsigned char
// equally; bool is used and nothing rests on it.  Nothing says the nineteen
// data classes are nineteen distinct types rather than a few types read at
// different offsets, and nothing says the owner objects are distinct either --
// one pair of classes per row is the spelling that assumes the least about
// which rows belong together.  The dword before the data pointer in each owner
// is unidentified.  Everything about the data class except the base and the
// one field is padding.
//
// IDENTITY IS NOT RECOVERED.  Every name except Overridable is derived from an
// address.

// Declared, never defined: the body is matched at 0x00087A80 from
// Code/GameEngine/Source/Common/INI/INIWater.cpp.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;									///< retail this+0x00
	const Overridable *m_nextOverride;				///< retail this+0x04
};

#define Q2_OVERRIDE_CHAIN_FIELD( NAME, TYPE, OFFSET )                     \
	class NAME##Data : public Overridable                                 \
	{                                                                     \
	public:                                                               \
		char m_unreconstructed_08[ OFFSET - 8 ];                          \
		TYPE m_field;                                                     \
	};                                                                    \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		TYPE field() const;                                               \
	private:                                                              \
		void *m_unreconstructed_00;                                       \
		const NAME##Data *m_data;                                         \
	};                                                                    \
	TYPE NAME::field() const                                              \
	{                                                                     \
		const NAME##Data *d = m_data;                                     \
		const NAME##Data *f;                                              \
		if ( d == 0 )                                                     \
			f = d;                                                        \
		else                                                              \
			f = (const NAME##Data *)( d->m_nextOverride                   \
				? d->m_nextOverride->getFinalOverride()                   \
				: d );                                                    \
		return f->m_field;                                                \
	}

// ------------------------------------------------------- one-byte field rows

Q2_OVERRIDE_CHAIN_FIELD( Rva000C4A70, bool, 0x4CA )
Q2_OVERRIDE_CHAIN_FIELD( Rva0016E3C0, bool, 0x0FE )
Q2_OVERRIDE_CHAIN_FIELD( Rva0016FFA0, bool, 0x49D )
Q2_OVERRIDE_CHAIN_FIELD( Rva001B50F0, bool, 0x0CF )
Q2_OVERRIDE_CHAIN_FIELD( Rva001B5160, bool, 0x0E8 )
Q2_OVERRIDE_CHAIN_FIELD( Rva00216D20, bool, 0x4B1 )
Q2_OVERRIDE_CHAIN_FIELD( Rva002700A0, bool, 0x0CC )
Q2_OVERRIDE_CHAIN_FIELD( Rva002E3FA0, bool, 0x4C8 )
Q2_OVERRIDE_CHAIN_FIELD( Rva003DB4C0, bool, 0x4CC )
Q2_OVERRIDE_CHAIN_FIELD( Rva004131E0, bool, 0x0D8 )
Q2_OVERRIDE_CHAIN_FIELD( Rva00413240, bool, 0x0E9 )

// ----------------------------------------------------------- float field rows

Q2_OVERRIDE_CHAIN_FIELD( Rva0016E3F0, float, 0x0EC )
Q2_OVERRIDE_CHAIN_FIELD( Rva0016E420, float, 0x0F4 )
Q2_OVERRIDE_CHAIN_FIELD( Rva00216CC0, float, 0x4A8 )
Q2_OVERRIDE_CHAIN_FIELD( Rva00216CF0, float, 0x4AC )
Q2_OVERRIDE_CHAIN_FIELD( Rva004132D0, float, 0x108 )
Q2_OVERRIDE_CHAIN_FIELD( Rva00413300, float, 0x10C )
Q2_OVERRIDE_CHAIN_FIELD( Rva00413330, float, 0x110 )
Q2_OVERRIDE_CHAIN_FIELD( Rva00413360, float, 0x114 )
Q2_OVERRIDE_CHAIN_FIELD( Rva003FE740, float, 0x3C )
