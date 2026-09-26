// Sixteen nineteen-byte __thiscall members that are BYTE-IDENTICAL apart from
// the position-dependent encoding of their one call:
//
//     mov eax,[ecx+8] / mov dword ptr [ecx],<ADDRESS>
//     mov ecx,[ecx+4] / push eax / call <REL32> / ret
//
// WHAT THE BYTES SHOW.  This is the only family in this batch with NO varying
// payload field at all.  All sixteen store the same address into offset 0, read
// the same two offsets, and reach the same callee -- the REL32 displacements
// differ only because the call sites differ, and every one of them resolves to
// RVA 0x0000871A.  The axis of this family is therefore the ADDRESS OF THE
// FUNCTION ITSELF and nothing else: retail carries sixteen separate copies of
// one body.
//
// The store is NOT a vftable store.  There is no `mov eax,ecx` constructor
// tail, and the object is read from afterwards, so this is an ordinary member
// that assigns a pointer-to-something-global into its first field and then
// forwards.  ONE address across all sixteen means ONE global, which is why one
// extern object serves the whole file and verify_dir32_consistency holds.
//
// The forward is __thiscall, and that is read off the bytes: the receiver comes
// out of the object at +4, the single argument out of the object at +8, and the
// call is followed immediately by `ret` with no stack adjustment, so the callee
// pops its own argument.
//
// WHAT THE BYTES CANNOT DECIDE.  THE FOUR RELOCATED BYTES AT OFFSET 5 ARE NOT
// EVIDENCE -- the patcher copies them out of retail.  What IS evidence is that
// all sixteen sites carry the SAME four bytes, which is what lets them share
// one declaration.  The pushed dword is spelled `int`; the bytes cannot tell an
// int from a pointer.  Nothing says the sixteen classes are related to each
// other, so they are sixteen classes.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address, and the
// callee pin is address-derived and additive.

class Q1SharedTarget0107C7D0
{
public:
	int m_opaque;
};

extern Q1SharedTarget0107C7D0 g_q1Shared0107C7D0;

class Q1Forwardee0000871A
{
public:
	void handle( int value );
};

#define Q1_SHARED_STORE_FORWARD( NAME )                                   \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		Q1SharedTarget0107C7D0 *m_target;                                     \
		Q1Forwardee0000871A *m_receiver;                                      \
		int m_value;                                                      \
		void invoke();                                                    \
	};                                                                    \
	void NAME::invoke()                                                   \
	{                                                                     \
		m_target = &g_q1Shared0107C7D0;                                       \
		m_receiver->handle( m_value );                                    \
	}

Q1_SHARED_STORE_FORWARD( Rva000875F0 )
Q1_SHARED_STORE_FORWARD( Rva00089040 )
Q1_SHARED_STORE_FORWARD( Rva0018F0E0 )
Q1_SHARED_STORE_FORWARD( Rva00190EF0 )
Q1_SHARED_STORE_FORWARD( Rva001915E0 )
Q1_SHARED_STORE_FORWARD( Rva00191600 )
Q1_SHARED_STORE_FORWARD( Rva00191620 )
Q1_SHARED_STORE_FORWARD( Rva0034FA20 )
Q1_SHARED_STORE_FORWARD( Rva0034FA40 )
Q1_SHARED_STORE_FORWARD( Rva0044F6D0 )
Q1_SHARED_STORE_FORWARD( Rva0044F6F0 )
Q1_SHARED_STORE_FORWARD( Rva00746EC0 )
Q1_SHARED_STORE_FORWARD( Rva00746EE0 )
Q1_SHARED_STORE_FORWARD( Rva00746F00 )
Q1_SHARED_STORE_FORWARD( Rva00746F20 )
Q1_SHARED_STORE_FORWARD( Rva00746F40 )
