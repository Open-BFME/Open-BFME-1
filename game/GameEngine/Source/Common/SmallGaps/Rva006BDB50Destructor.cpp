// ??1Rva006BDB50@@UAE@XZ
// cl: /DNDEBUG /MD /EHsc
struct Rva006BDB50Node { virtual ~Rva006BDB50Node(); char m_pad[0x10c]; Rva006BDB50Node* m_next; };
struct __declspec(novtable) Rva006BDB50Base;
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
// name this TU references; its definition is added at the bottom of this file.
extern void j_000095d4();

typedef void (Rva006BDB50::*Rva006BDB50ResetCall)();

union Rva006BDB50ResetPointer {
	void (*entry)();
	Rva006BDB50ResetCall member;
};

// ??1Rva006BDB50Base@@UAE@XZ is the implicit base-subobject destructor the
// derived row calls at +0x5D.  Retail's body at the pin 0x000231A5 is the
// 5-byte thunk `e9 46 09 19 00` = jmp 0x001B3AF0, i.e. the row
// ?m@Gen_001b3af0@@QAEXXZ (game/gen_small/fun_001.cpp).  Define the base
// destructor here as that same tail jump: the forward `__declspec(novtable)`
// keeps the base vftable pointer store out of this body (novtable, contrary to
// the earlier note, does suppress it in Vc7), and __declspec(noinline) keeps
// the derived row's implicit call a real call instead of inlining the store.
struct Gen_001b3af0 { void m(); };
__declspec(noinline) Rva006BDB50Base::~Rva006BDB50Base() { ((Gen_001b3af0*)this)->m(); }

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