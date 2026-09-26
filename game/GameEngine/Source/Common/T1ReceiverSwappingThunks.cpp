// Six bodies that make ONE call and hand the receiver over to something else.
// Two arities, both of them pure forwarding.
//
// SHAPE A -- 21 bytes, two rows, a FREE function returning its first argument:
//
//     mov eax,[esp+8] / push esi / mov esi,[esp+8] / push eax
//     mov ecx,esi / call <REL32> / mov eax,esi / pop esi / ret
//
// The trailing `ret` pops nothing, so the caller cleans the stack: __cdecl,
// two dword parameters, and ecx is never read on entry -- this is not a
// member.  The FIRST parameter is loaded into esi and becomes the callee's
// `this`; the SECOND is re-pushed unchanged as the callee's only argument; and
// esi is returned.  A free function that calls a member on its first argument
// and hands that argument back is the classic operator-style helper, and the
// bytes fix everything about it except the names.
//
// SHAPE B -- 18 bytes, four rows, a MEMBER that passes `this` to a method of
// its second argument:
//
//     mov eax,[esp+4] / push eax / push ecx / mov ecx,[esp+0x10]
//     call <REL32> / ret 8
//
// ecx is live on entry and `ret 8` pops two dwords: __thiscall with two
// parameters.  The pushes are the giveaway -- `push eax` then `push ecx` puts
// the FIRST parameter second and `this` FIRST in the callee's argument list,
// and the receiver for that call is then loaded from [esp+0x10], which after
// the two pushes is the SECOND parameter.  So the body is `return
// second->f( this, first );`, with the callee's return value left in eax and
// the callee popping its own arguments.  Nothing else is read or written.
//
// TWO CALLEES, FOUR ROWS, IN SHAPE B: 0x005C98A0 and 0x005CACC0 call one
// target, 0x005C98C0 and 0x005CACE0 the other, so the four rows are two pairs.
// Each pair shares its callee's class; the enclosing classes stay separate
// because four addresses are four COMDATs and nothing says any two of them are
// members of one type.  Same duplicate-translation-unit spacing as the cached
// accessor family: 0x005C98A0/0x005C98C0 and 0x005CACC0/0x005CACE0 are two
// copies of the same adjacent pair.
//
// IDENTITY IS NOT RECOVERED.  Every name is address-derived, and the callees
// are unclaimed, so they enter as declarations pinned by address.

// ------------------------------------------------------- shape A, free helper

#define T1_RECEIVER_HELPER( ROW, CALLEE )                                     \
	class T1Arg_##CALLEE;                                                     \
	class T1Recv_##CALLEE                                                     \
	{                                                                         \
	public:                                                                   \
		void apply( T1Arg_##CALLEE *b );                                      \
	};                                                                        \
	T1Recv_##CALLEE *t1Apply_##ROW( T1Recv_##CALLEE *a, T1Arg_##CALLEE *b )   \
	{                                                                         \
		a->apply( b );                                                        \
		return a;                                                             \
	}

T1_RECEIVER_HELPER( 005C5DB0, 005C49D0 )
T1_RECEIVER_HELPER( 005C5DD0, 005C47D0 )

// ---------------------------------------------------- shape B, member forward

#define T1_FORWARD_TARGET( CALLEE )                                           \
	class T1Sink_##CALLEE                                                     \
	{                                                                         \
	public:                                                                   \
		void *accept( void *owner, void *a );                                 \
	};

#define T1_RECEIVER_FORWARD( ROW, CALLEE )                                    \
	class T1Fwd_##ROW                                                         \
	{                                                                         \
	public:                                                                   \
		void *hand( void *a, T1Sink_##CALLEE *sink );                         \
	};                                                                        \
	void *T1Fwd_##ROW::hand( void *a, T1Sink_##CALLEE *sink )                 \
	{                                                                         \
		return sink->accept( this, a );                                       \
	}

T1_FORWARD_TARGET( 005C8D40 )
T1_FORWARD_TARGET( 005C8E90 )

T1_RECEIVER_FORWARD( 005C98A0, 005C8D40 )
T1_RECEIVER_FORWARD( 005C98C0, 005C8E90 )
T1_RECEIVER_FORWARD( 005CACC0, 005C8D40 )
T1_RECEIVER_FORWARD( 005CACE0, 005C8E90 )
