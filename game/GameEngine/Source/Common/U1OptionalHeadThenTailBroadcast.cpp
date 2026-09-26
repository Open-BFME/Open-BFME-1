// Six bodies, 42 / 56 / 70 bytes, that broadcast one pair of arguments to N
// optional listeners and then hand the same pair to a held object.  Retail,
// the two-listener arity:
//
//     push ebx / mov ebx,[esp+8] / push esi / mov esi,ecx
//     mov ecx,[esi] / test ecx,ecx / push edi / mov edi,[esp+0x14] / je L1
//     mov eax,[ecx] / push edi / push ebx / call dword ptr [eax+0xC]
//     L1: mov ecx,[esi+4] / test ecx,ecx / je L2
//     mov edx,[ecx] / push edi / push ebx / call dword ptr [edx+0xC]
//     L2: push edi / push ebx / lea ecx,[esi+8] / call <REL32>
//     pop edi / pop esi / pop ebx / ret 8
//
// WHAT THE BYTES SHOW.  `this` in ecx and `ret 8` is __thiscall with two dword
// parameters, and nothing returns a value.  Both parameters are loaded ONCE,
// into ebx and edi, before any call and are re-pushed unchanged at every call
// site -- so neither is modified and every callee receives the same pair, in
// the order (first, second).
//
// EACH LISTENER IS A NULL-CHECKED POINTER MEMBER dispatching SLOT 3.  The
// member is loaded straight into ecx and tested there; per the tell this whole
// range keeps witnessing, that only happens when the source binds it to a
// LOCAL first.  Written as a test of the member itself, MSVC 7.1 loads it into
// eax, tests eax and copies to ecx, which is two bytes longer at every
// listener.  `call dword ptr [eax+0xC]` through the loaded first dword makes
// the pointee polymorphic and the method the FOURTH slot.
//
// THE LAST CALL IS NOT A LISTENER.  It is not null-checked, it is not
// dispatched through a vftable, and its receiver is `lea ecx,[esi+K]` with no
// test -- a bare `lea` on `this`, which is a MEMBER subobject and not a base
// (a base at a non-zero offset reached by conversion would carry the
// null-guarded adjust this drawer shows elsewhere).  So the tail is a member
// object of concrete type whose broadcast method is compiled out of line: it
// is a `call`, not inlined code, which proves the method is only DECLARED in
// this translation unit.
//
// K IS ALWAYS 4*N.  The listeners sit at 0, 4, 8 and the member follows them,
// which is one class per row laid out in declaration order: N pointers, then
// the tail.  The arities present are N = 1, 2, 3.
//
// TWO TAIL TYPES, THREE ARITIES EACH.  0x005C5980 / 0x005C6DD0 / 0x005C8760
// call 0x005C4190 and 0x005CABD0 / 0x005CBA80 / 0x005CC130 call 0x005C97A0.
// A call target is a function and a function belongs to one class, so the
// three rows in each group share a tail type; nothing in any body says two
// rows share anything else, so each row keeps its own enclosing class.  Note
// what this rules out: if the shape were a recursive chain -- one listener
// plus a tail that is itself a chain -- the two-listener row would call the
// one-listener row address.  It does not.  All three call the SAME target, so
// the tail is a fixed type and the listeners are siblings in one class.
//
// IDENTITY IS NOT RECOVERED.  No vftable in the ledger points at these rows,
// no string reaches them, and neither tail type is named anywhere.  Every name
// here is derived from a row or callee address.

class U1Listener
{
public:
	virtual void listenerPad0();
	virtual void listenerPad1();
	virtual void listenerPad2();
	virtual void notify( void *first, void *second );
};

class U1Tail_005C4190
{
public:
	__declspec(noinline) void broadcast( void *first, void *second );

private:
	U1Listener *m_head;
	U1Listener **m_begin;
	U1Listener **m_end;
};

class U1Tail_005C97A0
{
public:
	__declspec(noinline) void broadcast( void *first, void *second );

private:
	U1Listener *m_heads[4];
	U1Tail_005C4190 m_tail;
};

#define U1_CHAIN_1( ROW, TAIL )                                               \
	class U1Chain_##ROW                                                       \
	{                                                                         \
	public:                                                                   \
		void broadcast( void *first, void *second );                          \
                                                                              \
		U1Listener *m_head0;                                                  \
		TAIL m_tail;                                                          \
	};                                                                        \
	void U1Chain_##ROW::broadcast( void *first, void *second )                \
	{                                                                         \
		U1Listener *head0 = m_head0;                                          \
		if ( head0 )                                                          \
		{                                                                     \
			head0->notify( first, second );                                   \
		}                                                                     \
		m_tail.broadcast( first, second );                                    \
	}

#define U1_CHAIN_2( ROW, TAIL )                                               \
	class U1Chain_##ROW                                                       \
	{                                                                         \
	public:                                                                   \
		void broadcast( void *first, void *second );                          \
                                                                              \
		U1Listener *m_head0;                                                  \
		U1Listener *m_head1;                                                  \
		TAIL m_tail;                                                          \
	};                                                                        \
	void U1Chain_##ROW::broadcast( void *first, void *second )                \
	{                                                                         \
		U1Listener *head0 = m_head0;                                          \
		if ( head0 )                                                          \
		{                                                                     \
			head0->notify( first, second );                                   \
		}                                                                     \
		U1Listener *head1 = m_head1;                                          \
		if ( head1 )                                                          \
		{                                                                     \
			head1->notify( first, second );                                   \
		}                                                                     \
		m_tail.broadcast( first, second );                                    \
	}

#define U1_CHAIN_3( ROW, TAIL )                                               \
	class U1Chain_##ROW                                                       \
	{                                                                         \
	public:                                                                   \
		void broadcast( void *first, void *second );                          \
                                                                              \
		U1Listener *m_head0;                                                  \
		U1Listener *m_head1;                                                  \
		U1Listener *m_head2;                                                  \
		TAIL m_tail;                                                          \
	};                                                                        \
	void U1Chain_##ROW::broadcast( void *first, void *second )                \
	{                                                                         \
		U1Listener *head0 = m_head0;                                          \
		if ( head0 )                                                          \
		{                                                                     \
			head0->notify( first, second );                                   \
		}                                                                     \
		U1Listener *head1 = m_head1;                                          \
		if ( head1 )                                                          \
		{                                                                     \
			head1->notify( first, second );                                   \
		}                                                                     \
		U1Listener *head2 = m_head2;                                          \
		if ( head2 )                                                          \
		{                                                                     \
			head2->notify( first, second );                                   \
		}                                                                     \
		m_tail.broadcast( first, second );                                    \
	}

U1_CHAIN_1( 005C5980, U1Tail_005C4190 )
U1_CHAIN_2( 005C6DD0, U1Tail_005C4190 )
U1_CHAIN_3( 005C8760, U1Tail_005C4190 )

U1_CHAIN_1( 005CABD0, U1Tail_005C97A0 )
U1_CHAIN_2( 005CBA80, U1Tail_005C97A0 )
U1_CHAIN_3( 005CC130, U1Tail_005C97A0 )

void U1Tail_005C4190::broadcast( void *first, void *second )
{
	U1Listener *head = m_head;
	if ( head )
		head->notify( first, second );

	for ( U1Listener **it = m_begin; it != m_end; ++it )
		(*it)->notify( first, second );
}

void U1Tail_005C97A0::broadcast( void *first, void *second )
{
	U1Listener *head0 = m_heads[0];
	if ( head0 )
		head0->notify( first, second );
	U1Listener *head1 = m_heads[1];
	if ( head1 )
		head1->notify( first, second );
	U1Listener *head2 = m_heads[2];
	if ( head2 )
		head2->notify( first, second );
	U1Listener *head3 = m_heads[3];
	if ( head3 )
		head3->notify( first, second );
	m_tail.broadcast( first, second );
}
