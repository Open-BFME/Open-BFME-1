// Thirteen null-checked virtual forwarders, 17 or 20 bytes, sitting on a
// 0x20 stride through 0x005C4460-0x005C45F0.  Retail (the 17-byte arity):
//
//     mov ecx,[ecx+<OFF>] / test ecx,ecx / je null
//     mov eax,[ecx] / jmp dword ptr [eax+8]
//     null: xor eax,eax / ret 4
//
// WHAT THE BYTES SHOW.  `this` in ecx and `ret 4` is __thiscall with one dword
// parameter.  The first instruction replaces `this` with a dword read out of
// the object, and that dword is the only thing the function touches -- so it
// is a pointer member and nothing else is read.  It is null-checked; when it
// is non-null its own first dword is loaded and control TAIL-JUMPS through
// displacement 8 of it, which makes the pointee polymorphic, the loaded dword
// its vftable, and the forwarded method SLOT 2.  The incoming argument is
// never touched: the jump hands the callee the frame untouched, so the
// callee's signature is this function's signature and the callee's `ret 4` is
// what balances the stack.
//
// THE RETURN TYPE IS A VALUE, unlike the void-returning forwarders in
// NullCheckedForwarders.cpp: the null arm does not fall into the `ret`, it
// loads eax with zero first.  A void function would have no reason to write
// eax on that path, so this shape returns something, and zero is its value
// when the member is null -- a pointer return spelled `0`.
//
// WHY THE POINTER IS NAMED IN A LOCAL.  Written the obvious way --
// `if ( m_target ) return m_target->slot2( a );` -- MSVC 7.1 loads the member
// into EAX, tests eax, then copies it to ecx for the call: 20 bytes for the
// 17-byte arity, with `mov eax,[ecx+OFF] / test eax,eax / je +7 / mov ecx,eax`
// where retail has `mov ecx,[ecx+OFF] / test ecx,ecx / je +5`.  Binding the
// member to a local first makes the compiler load straight into ecx and
// reproduces retail exactly.  The same three-instruction prologue comes out of
// the ternary and the if/else spellings once the local is there, so the local
// -- not the branch shape -- is what the bytes are witnessing.
//
// THE OFFSETS ARE TWO ASCENDING DWORD-STRIDED RUNS, 0x3C/0x40/0x44/0x48 and
// 0x54, and 0xA0/0xA4/0xA8/0xAC/0xB0/0xB4/0xB8/0xBC, interleaved through the
// stride in emission order.  That is what one class's members emitted in
// declaration order looks like, but nothing in any single body says the
// thirteen share a class -- each body sees only its own displacement.  So,
// as in the sibling forwarder family, each row gets its own class padded to
// its own offset: thirteen addresses, thirteen bodies, no claim that any two
// are members of one type.  Folding them into one class would assert exactly
// that, and the bytes do not.
//
// IDENTITY IS NOT RECOVERED.  No vftable known to the ledger points at these
// bodies, no string reaches them, and the forwarded interface is named
// nowhere.  Names are address-derived; the interface is spelled with the
// forwarded method third so the tail jump lands on displacement 8.

class T1SlotTwoTarget
{
public:
	virtual void s0();
	virtual void s1();
	virtual void *s2( void *a );
};

#define T1_NULL_CHECKED_LOOKUP( ROW, OFFSET )                                 \
	class T1Lookup_##ROW                                                      \
	{                                                                         \
	public:                                                                   \
		void *lookup( void *a );                                              \
                                                                              \
		char m_pad[ OFFSET ];                                                 \
		T1SlotTwoTarget *m_target;                                            \
	};                                                                        \
	void *T1Lookup_##ROW::lookup( void *a )                                   \
	{                                                                         \
		T1SlotTwoTarget *target = m_target;                                   \
		if ( target )                                                         \
		{                                                                     \
			return target->s2( a );                                           \
		}                                                                     \
		return 0;                                                             \
	}

T1_NULL_CHECKED_LOOKUP( 005C4460, 0x3c )
T1_NULL_CHECKED_LOOKUP( 005C4490, 0xa0 )
T1_NULL_CHECKED_LOOKUP( 005C44B0, 0x40 )
T1_NULL_CHECKED_LOOKUP( 005C44D0, 0xa4 )
T1_NULL_CHECKED_LOOKUP( 005C44F0, 0x44 )
T1_NULL_CHECKED_LOOKUP( 005C4510, 0xa8 )
T1_NULL_CHECKED_LOOKUP( 005C4530, 0x48 )
T1_NULL_CHECKED_LOOKUP( 005C4550, 0xac )
T1_NULL_CHECKED_LOOKUP( 005C4570, 0xb0 )
T1_NULL_CHECKED_LOOKUP( 005C4590, 0xb4 )
T1_NULL_CHECKED_LOOKUP( 005C45B0, 0xb8 )
T1_NULL_CHECKED_LOOKUP( 005C45D0, 0x54 )
T1_NULL_CHECKED_LOOKUP( 005C45F0, 0xbc )
