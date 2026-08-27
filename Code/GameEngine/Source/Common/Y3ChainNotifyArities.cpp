// cl: /DNDEBUG /MD /EHsc
// Twenty-two bodies, 23 to 86 bytes, in three related shapes: notify a run of
// optional listeners and then hand the job on, either to a member subobject or
// to a container.  Retail, the three-listener no-argument arity:
//
//     push esi / mov esi,ecx
//     mov ecx,[esi+0] / test ecx,ecx / je L1
//     mov eax,[ecx] / call dword ptr [eax+4]
//     L1: ... same at +4 and +8 ...
//     lea ecx,[esi+0xC] / pop esi / jmp <REL32>
//
// and the three-listener one-argument arity:
//
//     push esi / mov esi,ecx / mov ecx,[esi] / test ecx,ecx
//     push edi / mov edi,[esp+0xC] / je L1
//     mov eax,[ecx] / push edi / call dword ptr [eax+0xC]
//     L1: ... same at +4 and +8 ...
//     push edi / lea ecx,[esi+0xC] / call <REL32>
//     pop edi / pop esi / ret 4
//
// WHAT THE BYTES SHOW.  `this` in ecx; `ret` with no count and no argument
// touched in the first shape, `ret 4` with one dword loaded ONCE into edi and
// re-pushed at every call site in the second.  Nothing returns a value.
//
// EACH LISTENER IS A NULL-CHECKED POINTER MEMBER at a dword-strided offset,
// loaded STRAIGHT INTO ECX and tested there -- the local-binding tell this
// drawer keeps witnessing; testing the member itself costs two more bytes at
// every listener.  The no-argument shape dispatches SLOT 1 and the one-
// argument shape dispatches SLOT 3, so they are two different interfaces and
// are spelled as two here.
//
// THE TAIL IS A MEMBER SUBOBJECT, NOT A LISTENER.  It is not null-checked, not
// virtual, and its receiver is a bare `lea ecx,[esi+K]` on `this` -- a base at
// a non-zero offset would carry the null-guarded adjust.  K is always 4*N, so
// the listeners are N consecutive pointers followed by the tail, in
// declaration order.  In the no-argument shape the tail is the last statement
// of a void function with nothing to clean up, so MSVC emits `jmp` and the
// row ends without its own `ret`.
//
// THE THIRD SHAPE REPLACES THE MEMBER TAIL WITH A CONTAINER.  A begin/end
// pointer pair is compared and walked four bytes at a time, dispatching the
// same slot on every element, with the END POINTER RELOADED each iteration --
// the compiler conceding an opaque virtual call may have modified the member.
// Its listeners are NOT contiguous (0 and 0xC, or 0, 4 and 0x10), so those
// classes carry other members between them; the gaps are spelled as padding
// because nothing here says what fills them.
//
// WHICH ROWS SHARE A TAIL IS THE ONLY GROUPING THE BYTES SUPPORT.  A call
// target is a function and a function belongs to one class:
//
//     no-argument  -> 0x005C5A00 (six rows)   0x005CAB40 (two rows)
//     one-argument -> 0x005C5A50 (five rows)  0x005C9740 (three rows)
//                     0x005CBB30 (one row)
//
// 0x005CAB40, 0x005C9740 and 0x005CBB30 are converted here, so they are
// defined __declspec(noinline) -- retail's `call` proves they stayed out of
// line, and this file must not inline what retail did not.  0x005C5A00 and
// 0x005C5A50 are outside this conversion and are declared only; they are
// REL32 sites pinned in reverse/symbols.csv.  Note what the grouping rules
// out: 0x005CC200, a one-listener row, calls 0x005CBB30, a five-listener row,
// so the shape is NOT purely "N siblings plus a fixed tail" -- at least one
// level nests inside another.
//
// IDENTITY IS NOT RECOVERED.  No vftable in the ledger reaches these bodies
// and no string names a field; every name here comes from a row or callee
// address.

class Y3Item0
{
public:
	virtual void pad0();
	virtual void reset();
};

class Y3Item1
{
public:
	virtual void pad0();
	virtual void pad1();
	virtual void pad2();
	virtual void update( void *argument );
};

#define Y3_RESET_HEAD( N )                                                    \
	{                                                                         \
		Y3Item0 *head = m_h##N;                                               \
		if ( head )                                                           \
			head->reset();                                                    \
	}

#define Y3_NOTIFY_HEAD( N )                                                   \
	{                                                                         \
		Y3Item1 *head = m_h##N;                                               \
		if ( head )                                                           \
			head->update( argument );                                         \
	}

#define Y3_RESET_B1 Y3_RESET_HEAD( 0 )
#define Y3_RESET_B2 Y3_RESET_B1 Y3_RESET_HEAD( 1 )
#define Y3_RESET_B3 Y3_RESET_B2 Y3_RESET_HEAD( 2 )
#define Y3_RESET_B4 Y3_RESET_B3 Y3_RESET_HEAD( 3 )
#define Y3_RESET_B5 Y3_RESET_B4 Y3_RESET_HEAD( 4 )
#define Y3_RESET_B6 Y3_RESET_B5 Y3_RESET_HEAD( 5 )

#define Y3_NOTIFY_B1 Y3_NOTIFY_HEAD( 0 )
#define Y3_NOTIFY_B2 Y3_NOTIFY_B1 Y3_NOTIFY_HEAD( 1 )
#define Y3_NOTIFY_B3 Y3_NOTIFY_B2 Y3_NOTIFY_HEAD( 2 )
#define Y3_NOTIFY_B4 Y3_NOTIFY_B3 Y3_NOTIFY_HEAD( 3 )
#define Y3_NOTIFY_B5 Y3_NOTIFY_B4 Y3_NOTIFY_HEAD( 4 )

#define Y3_F1 Y3Item0 *m_h0;
#define Y3_F2 Y3_F1 Y3Item0 *m_h1;
#define Y3_F3 Y3_F2 Y3Item0 *m_h2;
#define Y3_F4 Y3_F3 Y3Item0 *m_h3;
#define Y3_F5 Y3_F4 Y3Item0 *m_h4;
#define Y3_F6 Y3_F5 Y3Item0 *m_h5;

#define Y3_G1 Y3Item1 *m_h0;
#define Y3_G2 Y3_G1 Y3Item1 *m_h1;
#define Y3_G3 Y3_G2 Y3Item1 *m_h2;
#define Y3_G4 Y3_G3 Y3Item1 *m_h3;
#define Y3_G5 Y3_G4 Y3Item1 *m_h4;

// ---- tails that are only declared here ------------------------------------

class Y3ResetTail_005C5A00
{
public:
	void resetAll();
};

class Y3NotifyTail_005C5A50
{
public:
	__declspec(noinline) void notifyAll( void *argument );

	Y3Item1 *m_h0;
	Y3Item1 *m_h1;
	Y3Item1 **m_begin;
	Y3Item1 **m_end;
};

void Y3NotifyTail_005C5A50::notifyAll( void *argument )
{
	Y3_NOTIFY_HEAD( 0 )
	Y3_NOTIFY_HEAD( 1 )
	for ( Y3Item1 **it = m_begin; it != m_end; ++it )
		( *it )->update( argument );
}

// ---- tails that are defined here (out of line, as retail has them) --------

class Y3ResetTail_005CAB40
{
public:
	__declspec(noinline) void resetAll();

	Y3Item0 *m_h0;
	Y3Item0 *m_h1;
	char m_gap[8];
	Y3Item0 *m_h2;
	Y3Item0 **m_begin;
	Y3Item0 **m_end;
};

void Y3ResetTail_005CAB40::resetAll()
{
	Y3_RESET_HEAD( 0 )
	Y3_RESET_HEAD( 1 )
	Y3_RESET_HEAD( 2 )
	for ( Y3Item0 **it = m_begin; it != m_end; ++it )
		( *it )->reset();
}

class Y3NotifyTail_005C9740
{
public:
	__declspec(noinline) void notifyAll( void *argument );

	Y3Item1 *m_h0;
	char m_gap[8];
	Y3Item1 *m_h1;
	Y3Item1 **m_begin;
	Y3Item1 **m_end;
};

void Y3NotifyTail_005C9740::notifyAll( void *argument )
{
	Y3_NOTIFY_HEAD( 0 )
	Y3_NOTIFY_HEAD( 1 )
	for ( Y3Item1 **it = m_begin; it != m_end; ++it )
		( *it )->update( argument );
}

class Y3NotifyTail_005CBB30
{
public:
	__declspec(noinline) void notifyAll( void *argument );

	Y3_G5
	Y3NotifyTail_005C5A50 m_tail;
};

void Y3NotifyTail_005CBB30::notifyAll( void *argument )
{
	Y3_NOTIFY_B5
	m_tail.notifyAll( argument );
}

// ---- standalone container rows -------------------------------------------

class Y3Vector_005C6D40
{
public:
	void resetAll();

	char m_gap[4];
	Y3Item0 *m_h0;
	Y3Item0 **m_begin;
	Y3Item0 **m_end;
};

void Y3Vector_005C6D40::resetAll()
{
	Y3_RESET_HEAD( 0 )
	for ( Y3Item0 **it = m_begin; it != m_end; ++it )
		( *it )->reset();
}

class Y3Vector_005C86D0
{
public:
	void resetAll();

	char m_gap[8];
	Y3Item0 *m_h0;
	Y3Item0 **m_begin;
	Y3Item0 **m_end;
};

void Y3Vector_005C86D0::resetAll()
{
	Y3_RESET_HEAD( 0 )
	for ( Y3Item0 **it = m_begin; it != m_end; ++it )
		( *it )->reset();
}

class Y3Vector_005C96F0
{
public:
	void resetAll();

	Y3Item0 *m_h0;
	char m_gap[8];
	Y3Item0 *m_h1;
	Y3Item0 **m_begin;
	Y3Item0 **m_end;
};

void Y3Vector_005C96F0::resetAll()
{
	Y3_RESET_HEAD( 0 )
	Y3_RESET_HEAD( 1 )
	for ( Y3Item0 **it = m_begin; it != m_end; ++it )
		( *it )->reset();
}

// ---- the listener runs ----------------------------------------------------

#define Y3_RESET_ROW( ROW, N, TAIL )                                          \
	class Y3Reset_##ROW                                                       \
	{                                                                         \
	public:                                                                   \
		void resetAll();                                                      \
                                                                              \
		Y3_F##N                                                               \
		TAIL m_tail;                                                          \
	};                                                                        \
	void Y3Reset_##ROW::resetAll()                                            \
	{                                                                         \
		Y3_RESET_B##N                                                         \
		m_tail.resetAll();                                                    \
	}

#define Y3_NOTIFY_ROW( ROW, N, TAIL )                                         \
	class Y3Notify_##ROW                                                      \
	{                                                                         \
	public:                                                                   \
		void notifyAll( void *argument );                                     \
                                                                              \
		Y3_G##N                                                               \
		TAIL m_tail;                                                          \
	};                                                                        \
	void Y3Notify_##ROW::notifyAll( void *argument )                          \
	{                                                                         \
		Y3_NOTIFY_B##N                                                        \
		m_tail.notifyAll( argument );                                         \
	}

Y3_RESET_ROW( 005C6E20, 1, Y3ResetTail_005C5A00 )
Y3_RESET_ROW( 005C87C0, 2, Y3ResetTail_005C5A00 )
Y3_RESET_ROW( 005C9810, 3, Y3ResetTail_005C5A00 )
Y3_RESET_ROW( 005CAC10, 4, Y3ResetTail_005C5A00 )
Y3_RESET_ROW( 005CBAD0, 5, Y3ResetTail_005C5A00 )
Y3_RESET_ROW( 005CC190, 6, Y3ResetTail_005C5A00 )

Y3_RESET_ROW( 005CBA20, 1, Y3ResetTail_005CAB40 )
Y3_RESET_ROW( 005CC0B0, 2, Y3ResetTail_005CAB40 )

Y3_NOTIFY_ROW( 005C6E40, 1, Y3NotifyTail_005C5A50 )
Y3_NOTIFY_ROW( 005C87F0, 2, Y3NotifyTail_005C5A50 )
Y3_NOTIFY_ROW( 005C9850, 3, Y3NotifyTail_005C5A50 )
Y3_NOTIFY_ROW( 005CAC60, 4, Y3NotifyTail_005C5A50 )

Y3_NOTIFY_ROW( 005CABA0, 1, Y3NotifyTail_005C9740 )
Y3_NOTIFY_ROW( 005CBA40, 2, Y3NotifyTail_005C9740 )
Y3_NOTIFY_ROW( 005CC0E0, 3, Y3NotifyTail_005C9740 )

Y3_NOTIFY_ROW( 005CC200, 1, Y3NotifyTail_005CBB30 )
