// Five __thiscall members that hand a sub-object its own first two dwords:
//
//     mov eax,[ecx+<K>+4] / mov edx,[ecx+<K>] / add ecx,<K> / push eax /
//     push edx / call <REL32> / ret
//
// WHAT THE BYTES SHOW.  ecx is ADJUSTED IN PLACE by a constant rather than
// replaced by a load, so the receiver is a sub-object at a fixed offset, not a
// stored pointer.  Both pushed values are read relative to the SAME constant,
// from that sub-object's offsets 0 and 4, and they are pushed right-to-left --
// so the call is `sub.f(sub.m_a, sub.m_b)` with m_a first.  The bare `ret`
// leaves the callee to clean up, making it __thiscall with two stack arguments.
//
// THE SPELLING IS NOT FREE HERE.  Writing the obvious `m_sub.handle(m_sub.m_a,
// m_sub.m_b)` compiles to a DIFFERENT nineteen-byte body -- MSVC 7.1 copies
// `this` into eax and forms the receiver with `lea ecx,[eax+K]`.  Binding the
// sub-object to a reference first (`GenX &s = m_sub;`) is what makes it destroy
// `this` in place with `add ecx,K`, which is what retail does.  That is a real
// source distinction recovered from seventeen concrete bytes.
//
// FOUR CALLEES OVER FIVE CALLERS: 000FB1F0 and 003C3AC0 both call 0x0001D63D,
// so they share a sub-object TYPE while embedding it at different offsets (4
// and 0x68).  Every callee address is read out of the REL32 displacement and
// lands on a low-RVA incremental-link thunk.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived, the argument types are
// spelled int because a dword push cannot say more, and the leading char arrays
// are padding that reproduces a proven offset.

#define BFME_PAIR_CALL_CALLEE( ADDR )                                     \
	class Gen##ADDR                                                       \
	{                                                                     \
	public:                                                               \
		void handle( int a, int b );                                      \
		int m_a;                                                          \
		int m_b;                                                          \
	};

#define BFME_PAIR_CALL( NAME, CALLEE, LEAD )                              \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void forward();                                                   \
		char m_lead[ LEAD ];                                              \
		CALLEE m_sub;                                                     \
	};                                                                    \
	void NAME::forward()                                                  \
	{                                                                     \
		CALLEE &sub = m_sub;                                              \
		sub.handle( sub.m_a, sub.m_b );                                   \
	}

BFME_PAIR_CALL_CALLEE( 00024C17 )
BFME_PAIR_CALL_CALLEE( 0001D63D )
BFME_PAIR_CALL_CALLEE( 00046B00 )
BFME_PAIR_CALL_CALLEE( 0001D3EA )

BFME_PAIR_CALL( Rva00065A40, Gen00024C17, 4 )
BFME_PAIR_CALL( Rva000FB1F0, Gen0001D63D, 4 )
BFME_PAIR_CALL( Rva00366C80, Gen00046B00, 0x18 )
BFME_PAIR_CALL( Rva003A3580, Gen0001D3EA, 0x2C )
BFME_PAIR_CALL( Rva003C3AC0, Gen0001D63D, 0x68 )
