// ??1Rva006BDB50@@UAE@XZ
// cl: /DNDEBUG /MD /EHsc
struct Rva006BDB50Node { virtual ~Rva006BDB50Node(); char m_pad[0x10c]; Rva006BDB50Node* m_next; };
struct Rva006BDB50Base {
	virtual ~Rva006BDB50Base();
	int m_4;
	int m_8;
};
struct Rva006BDB50 : Rva006BDB50Base {
	Rva006BDB50Node* m_head;
	void reset();
	virtual ~Rva006BDB50();
};

// The +0x2B call is a 5-byte ILT thunk: retail 0x000095D4 ->
// ?j_000095d4@@YAXXZ (game/gen_small/thunks_004.cpp, row in
// targets/game/reverse/functions.csv, which jumps on to
// ?drain@Rva006BDB00@@QAEXXZ at 0x006BDB00).  The address-scoped pin
// ?reset@Rva006BDB50@@QAEXXZ names that thunk but nothing defines it, so route
// the call through the thunk's own name exactly as Rva002BC400StateAction.cpp
// does; the emitted instruction is unchanged.
//
// The trailing base-destructor call cannot be moved the same way: retail's
// `mov [esp+0x10],-1` EH-state write before the call at +0x5D only exists
// because MSVC emits an implicit base-subobject destructor call, so ??1
// Rva006BDB50Base@@UAE@XZ (thunk ?j_000231a5@@YAXXZ at 0x000231A5) stays the
// name this TU references.  It has no definition anywhere in game/.
extern void j_000095d4();

typedef void (Rva006BDB50::*Rva006BDB50ResetCall)();

union Rva006BDB50ResetPointer {
	void (*entry)();
	Rva006BDB50ResetCall member;
};

Rva006BDB50::~Rva006BDB50()
{
	Rva006BDB50ResetPointer resetCall;
	resetCall.entry = j_000095d4;
	(((Rva006BDB50*)this)->*resetCall.member)();
	Rva006BDB50Node* n = m_head;
	while (n) {
		Rva006BDB50Node* next = n->m_next;
		delete n;
		n = next;
	}
}