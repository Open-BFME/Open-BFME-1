// The 16 byte-identical 35-byte release-and-assign members at
// 0x005C1410-0x005C2FC0.
//
//     push esi / mov esi,ecx / mov ecx,[esi] / test ecx,ecx / je skip
//     mov eax,[ecx] / push 1 / call dword ptr [eax]
//     mov ecx,[esp+8] / mov [esi],ecx / pop esi / ret 4
//     skip: mov edx,[esp+8] / mov [esi],edx / pop esi / ret 4
//
// WHAT THE BYTES SHOW.  `ret 4` with `this` in ecx is __thiscall taking one
// dword argument.  The only member touched is the dword at `this+0`, and it is
// both read (null-checked) and written (with the incoming argument), so the
// enclosing class's first -- and, as far as this body can tell, only -- member
// is a pointer of the argument's type.  When the held pointer is non-null its
// own first dword is loaded and called through displacement 0 with a single
// immediate argument 1, which makes the pointee polymorphic, that load its
// vftable, and the callee slot 0.  The callee cleans its own argument: `esp+8`
// still addresses this function's argument after the call returns, which it
// would not if the call were __cdecl.
//
// That is the release half of a held-reference assignment: "if I am holding
// something, tell it to let go with flag 1, then hold the new thing instead."
// The immediate 1 is the customary destroy/delete-if-last flag of a Release or
// deleteInstance slot; the bytes fix its value but not its name, and `push 1`
// is equally `1` and `true`, which is why the spelling below is not evidence
// of the parameter's declared type.
//
// The trailing store is duplicated into both arms rather than merged after the
// join -- once through ecx on the released path, once through edx on the null
// path.  That is /O2 tail duplication of a two-instruction epilogue, not two
// different assignments in the source: both arms load the same `[esp+8]` and
// store to the same `[esi]`.  A single `m_target = p` after the `if` produces
// exactly these bytes.
//
// WHY THE MEMBERS ARE SEPARATE FUNCTIONS AND NOT ALIASES.  The 16 bodies sit at
// 16 distinct addresses in one dead-COMDAT drawer.  They are not one function
// copied per translation unit -- there is no inline assembly here and nothing
// else to defeat inlining -- they are 16 instantiations of the same held-pointer
// pattern over 16 different held types, which compile to identical bytes because
// the released slot index and the flag value coincide.  Aliasing them would
// assert that 16 functions are one; the macro below keeps them 16.
//
// WHY THE NAMES ARE ADDRESS-DERIVED.  Nothing in the image witnesses a name for
// the holder or for the interface it releases: no ledger-known vftable points at
// these bodies and no RTTI descriptor is reachable from them.  Ghidra's
// FUN_009c1410-style labels recorded on the retired dump rows are themselves
// address-derived and witness nothing.  Each body is therefore named for its own
// address, so the rows claim the bytes without asserting an identity nobody has
// recovered.

class ReleaseTarget
{
public:
	virtual void release( int destroy );
};

#define BFME_RELEASING_ASSIGN( NAME )                                         \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		void assign( ReleaseTarget *p );                                      \
                                                                              \
		ReleaseTarget *m_target;                                              \
	};                                                                        \
	void NAME::assign( ReleaseTarget *p )                                     \
	{                                                                         \
		if ( m_target )                                                       \
		{                                                                     \
			m_target->release( 1 );                                           \
		}                                                                     \
                                                                              \
		m_target = p;                                                         \
	}

BFME_RELEASING_ASSIGN( Rva005C1410Holder )
BFME_RELEASING_ASSIGN( Rva005C1520Holder )
BFME_RELEASING_ASSIGN( Rva005C1660Holder )
BFME_RELEASING_ASSIGN( Rva005C1700Holder )
BFME_RELEASING_ASSIGN( Rva005C17A0Holder )
BFME_RELEASING_ASSIGN( Rva005C1840Holder )
BFME_RELEASING_ASSIGN( Rva005C18C0Holder )
BFME_RELEASING_ASSIGN( Rva005C18F0Holder )
BFME_RELEASING_ASSIGN( Rva005C2DF0Holder )
BFME_RELEASING_ASSIGN( Rva005C2EA0Holder )
BFME_RELEASING_ASSIGN( Rva005C2ED0Holder )
BFME_RELEASING_ASSIGN( Rva005C2F00Holder )
BFME_RELEASING_ASSIGN( Rva005C2F30Holder )
BFME_RELEASING_ASSIGN( Rva005C2F60Holder )
BFME_RELEASING_ASSIGN( Rva005C2F90Holder )
BFME_RELEASING_ASSIGN( Rva005C2FC0Holder )
