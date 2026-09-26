// The 21 byte-identical null-checked forwarding thunks at 0x005BFF70-0x005C07E0.
//
// Two arities of one shape, differing in nothing but the trailing `ret imm16`:
// thirteen copies of `ret 4` and eight of `ret 8`, interleaved through a single
// 2.2KB stretch of dead COMDATs.  Retail (the `ret 4` arity):
//
//     mov ecx,[ecx] / test ecx,ecx / je end / mov eax,[ecx]
//     jmp dword ptr [eax+0xC] / end: ret 4
//
// WHAT THE BYTES SHOW.  `ret imm16` with `this` arriving in ecx is __thiscall.
// The first instruction replaces `this` with the dword at `this+0`, so the
// enclosing class's first member is a pointer and it is the only member this
// function touches.  That pointer is null-checked; when it is non-null its own
// first dword is loaded and control TAIL-JUMPS through slot 3 of it, which makes
// the pointee polymorphic and the load its vftable.  The incoming stack
// arguments are never read, moved or re-pushed -- the jump hands the callee the
// frame untouched, so the callee's signature is this function's signature and
// its `ret` is what balances the stack.  That is why the two arities differ only
// in the immediate: `ret 4` forwards one dword argument, `ret 8` forwards two,
// and nothing else in the body can tell them apart.
//
// The null branch falls straight to the `ret`, returning nothing -- so the
// return type is void, since a value-returning shape would have to load eax on
// that path.
//
// WHY THE MEMBERS ARE SEPARATE FUNCTIONS AND NOT ALIASES.  The 21 bodies sit at
// 21 distinct addresses.  They are not one function copied per TU; they are
// distinct instantiations -- the classic "delegate every call to my held
// interface pointer if I have one" wrapper, one member function per forwarded
// interface method -- that happen to compile to the same bytes because the
// forwarded slot index and the argument count coincide.  Claiming them as a
// single COMDAT with aliases would assert 21 functions are one function; the
// macro below keeps them 21.
//
// WHY THE NAMES ARE ADDRESS-DERIVED.  Nothing in the image witnesses a name for
// the wrapper or for the interface it holds: no vftable known to the ledger
// points at these bodies, no RTTI descriptor is reachable from them, and the
// surrounding stretch is a mixed dead-COMDAT drawer whose neighbours come from
// half a dozen unrelated sources.  Each body is therefore named for its own
// address, so the rows claim the bytes without asserting an identity nobody has
// recovered.  Promoting them is a mechanical repoint once the interface is named.

// Both arities dispatch slot 3, so each is spelled against its own interface
// with the forwarded method fourth.  The bytes say nothing more than "slot 3":
// they cannot tell whether the two arities forward into one interface or two.

class ForwardTargetOne
{
public:
	virtual void forwardPad0();
	virtual void forwardPad1();
	virtual void forwardPad2();
	virtual void forwardOne( void *a );
};

class ForwardTargetTwo
{
public:
	virtual void forwardPad0();
	virtual void forwardPad1();
	virtual void forwardPad2();
	virtual void forwardTwo( void *a, void *b );
};

#define BFME_NULL_CHECKED_FORWARD_1( NAME )                                   \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		void forward( void *a );                                              \
                                                                              \
		ForwardTargetOne *m_target;                                           \
	};                                                                        \
	void NAME::forward( void *a )                                             \
	{                                                                         \
		if ( m_target )                                                       \
		{                                                                     \
			m_target->forwardOne( a );                                        \
		}                                                                     \
	}

#define BFME_NULL_CHECKED_FORWARD_2( NAME )                                   \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		void forward( void *a, void *b );                                     \
                                                                              \
		ForwardTargetTwo *m_target;                                           \
	};                                                                        \
	void NAME::forward( void *a, void *b )                                    \
	{                                                                         \
		if ( m_target )                                                       \
		{                                                                     \
			m_target->forwardTwo( a, b );                                     \
		}                                                                     \
	}

BFME_NULL_CHECKED_FORWARD_1( Rva005BFF70Forward )
BFME_NULL_CHECKED_FORWARD_1( Rva005C0040Forward )
BFME_NULL_CHECKED_FORWARD_1( Rva005C01E0Forward )
BFME_NULL_CHECKED_FORWARD_1( Rva005C0260Forward )
BFME_NULL_CHECKED_FORWARD_1( Rva005C03F0Forward )
BFME_NULL_CHECKED_FORWARD_1( Rva005C04E0Forward )
BFME_NULL_CHECKED_FORWARD_1( Rva005C0590Forward )
BFME_NULL_CHECKED_FORWARD_1( Rva005C05E0Forward )
BFME_NULL_CHECKED_FORWARD_1( Rva005C0670Forward )
BFME_NULL_CHECKED_FORWARD_1( Rva005C06F0Forward )
BFME_NULL_CHECKED_FORWARD_1( Rva005C0770Forward )
BFME_NULL_CHECKED_FORWARD_1( Rva005C07A0Forward )
BFME_NULL_CHECKED_FORWARD_1( Rva005C07E0Forward )

BFME_NULL_CHECKED_FORWARD_2( Rva005C0000Forward )
BFME_NULL_CHECKED_FORWARD_2( Rva005C0200Forward )
BFME_NULL_CHECKED_FORWARD_2( Rva005C04B0Forward )
BFME_NULL_CHECKED_FORWARD_2( Rva005C05C0Forward )
BFME_NULL_CHECKED_FORWARD_2( Rva005C0640Forward )
BFME_NULL_CHECKED_FORWARD_2( Rva005C06C0Forward )
BFME_NULL_CHECKED_FORWARD_2( Rva005C0740Forward )
BFME_NULL_CHECKED_FORWARD_2( Rva005C07C0Forward )

// ---------------------------------------------------------------------------
// THE THIRD ARITY, AND A DIFFERENT SLOT.  Interleaved through the same drawer
// -- 0x005BFF60 sits sixteen bytes before 0x005BFF70, 0x005C01D0 before
// 0x005C01E0, 0x005C03E0 before 0x005C03F0, 0x005C0580 before 0x005C0590 --
// and continuing past its end into 0x005C2450-0x005C2710, there are thirteen
// more copies of a twelve-byte body that is the same shape with two of its
// three parameters different:
//
//     mov ecx,[ecx] / test ecx,ecx / je end / mov eax,[ecx]
//     jmp dword ptr [eax+4] / end: ret
//
// A bare `ret` and no argument bytes: this arity takes NO arguments beyond
// `this`, which is why the tail jump needs no stack adjustment at all and the
// callee's own `ret` balances an already-balanced frame.  And the dispatch is
// through displacement 4, not 0xC -- slot 1 of the target's vftable rather than
// slot 3.  Everything else is byte-for-byte the shape documented above: same
// first-member pointer, same null check, same fall-through to a value-less
// return, same __thiscall convention.
//
// The pairing is what makes the slot reading solid rather than a guess.  Four
// of the thirteen sit immediately in front of a `ret 4` / slot-3 member of the
// family above, at a sixteen-byte stride -- the layout of a class that holds
// one interface pointer and wraps two of its methods, emitted in declaration
// order.  Two different displacements from two adjacent members of one class is
// exactly what "one wrapper per forwarded method" predicts.
//
// SEPARATE FUNCTIONS, NOT ALIASES, for the same reason as above: thirteen
// distinct addresses, thirteen distinct instantiations that coincide in bytes
// because slot index and argument count coincide.  The macro keeps them
// thirteen.  And because the forwarded method is at slot 1 here and slot 3
// there, it gets its own interface with the method declared second -- spelling
// a different slot against the existing interface would put the jump at the
// wrong displacement, which is the failure this file's earlier note records.

class ForwardTargetZero
{
public:
	virtual void forwardPad0();
	virtual void forwardZero();
};

#define BFME_NULL_CHECKED_FORWARD_0( NAME )                                   \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		void forward( void );                                                 \
                                                                              \
		ForwardTargetZero *m_target;                                          \
	};                                                                        \
	void NAME::forward( void )                                                \
	{                                                                         \
		if ( m_target )                                                       \
		{                                                                     \
			m_target->forwardZero();                                          \
		}                                                                     \
	}

BFME_NULL_CHECKED_FORWARD_0( Rva005BFF60Forward )
BFME_NULL_CHECKED_FORWARD_0( Rva005C01D0Forward )
BFME_NULL_CHECKED_FORWARD_0( Rva005C03E0Forward )
BFME_NULL_CHECKED_FORWARD_0( Rva005C0580Forward )
BFME_NULL_CHECKED_FORWARD_0( Rva005C0790Forward )
BFME_NULL_CHECKED_FORWARD_0( Rva005C2450Forward )
BFME_NULL_CHECKED_FORWARD_0( Rva005C2570Forward )
BFME_NULL_CHECKED_FORWARD_0( Rva005C2600Forward )
BFME_NULL_CHECKED_FORWARD_0( Rva005C2620Forward )
BFME_NULL_CHECKED_FORWARD_0( Rva005C2630Forward )
BFME_NULL_CHECKED_FORWARD_0( Rva005C2640Forward )
BFME_NULL_CHECKED_FORWARD_0( Rva005C2650Forward )
BFME_NULL_CHECKED_FORWARD_0( Rva005C2710Forward )
