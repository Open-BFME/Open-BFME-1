// Two families of tiny __thiscall forwarders that read fields of the object and
// pass them straight to one direct call.  They are kept in one translation unit
// because they are the same shape at two arities; they share no callee.
//
// TWENTY-FOUR 14-BYTE BODIES -- one field, passed twice:
//
//     mov eax,[ecx+4] / push eax / push eax / call <REL32> / add esp,8 / ret
//
// The plain `ret` pops nothing and ecx is read once: __thiscall with no
// arguments.  The caller pops the eight bytes itself, so the callee is __cdecl
// -- a free function, not a member -- and it receives the SAME dword twice.
//
// TWENTY-ONE 13-BYTE BODIES -- two adjacent fields, in declaration order:
//
//     mov eax,[ecx+4] / mov edx,[ecx] / push eax / push edx / call <REL32> / ret
//
// Same __thiscall entry, but nothing adjusts esp after the call and ecx still
// holds `this` when the callee is entered: the callee pops its own two dwords
// and receives `this` in ecx, so it is a __thiscall member of this class or of
// a base of it.  The field at +0 is the first argument and the field at +4 the
// second -- the loads are emitted second-argument-first because the pushes run
// right to left.
//
// THAT ARITY DIFFERENCE IS READ FROM THE STACK DISCIPLINE ALONE, not from the
// callees, none of which is examined here.
//
// THE ONLY AXIS WITHIN EACH FAMILY IS THE REL32 TARGET: twenty-four members
// over eight callees, and twenty-one members over twenty callees.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived; callee pins are
// additive and address-derived.

#define BFME_FIELD_TWICE_CALLEE( ADDR )                                      \
	void gen##ADDR( void *first, void *second );

#define BFME_FIELD_TWICE_FORWARDER( NAME, CALLEE )                           \
	class NAME                                                               \
	{                                                                        \
	public:                                                                  \
		void invoke();                                                       \
		int m_head;                                                          \
		void *m_value;                                                       \
	};                                                                       \
	void NAME::invoke()                                                      \
	{                                                                        \
		CALLEE( m_value, m_value );                                          \
	}

#define BFME_FIELD_PAIR_CALLEE( ADDR )                                       \
	class Gen##ADDR                                                          \
	{                                                                        \
	public:                                                                  \
		void handle( void *first, void *second );                            \
	};

#define BFME_FIELD_PAIR_FORWARDER( NAME, CALLEE )                            \
	class NAME : public CALLEE                                               \
	{                                                                        \
	public:                                                                  \
		void invoke();                                                       \
		void *m_first;                                                       \
		void *m_second;                                                      \
	};                                                                       \
	void NAME::invoke()                                                      \
	{                                                                        \
		handle( m_first, m_second );                                         \
	}

BFME_FIELD_TWICE_CALLEE( 000772C0 )
BFME_FIELD_TWICE_CALLEE( 0009B4B0 )
BFME_FIELD_TWICE_CALLEE( 00389840 )
BFME_FIELD_TWICE_CALLEE( 003C92A0 )
BFME_FIELD_TWICE_CALLEE( 005278B0 )
BFME_FIELD_TWICE_CALLEE( 0054E9E0 )
BFME_FIELD_TWICE_CALLEE( 0056DFC0 )
BFME_FIELD_TWICE_CALLEE( 005930E0 )

BFME_FIELD_TWICE_FORWARDER( Rva000781F0FieldTwiceForwarder, gen000772C0 )
BFME_FIELD_TWICE_FORWARDER( Rva00078400FieldTwiceForwarder, gen000772C0 )
BFME_FIELD_TWICE_FORWARDER( Rva000784E0FieldTwiceForwarder, gen000772C0 )
BFME_FIELD_TWICE_FORWARDER( Rva0009B660FieldTwiceForwarder, gen0009B4B0 )
BFME_FIELD_TWICE_FORWARDER( Rva0009B680FieldTwiceForwarder, gen0009B4B0 )
BFME_FIELD_TWICE_FORWARDER( Rva0009B6A0FieldTwiceForwarder, gen0009B4B0 )
BFME_FIELD_TWICE_FORWARDER( Rva0038ED60FieldTwiceForwarder, gen00389840 )
BFME_FIELD_TWICE_FORWARDER( Rva003909E0FieldTwiceForwarder, gen00389840 )
BFME_FIELD_TWICE_FORWARDER( Rva003928C0FieldTwiceForwarder, gen00389840 )
BFME_FIELD_TWICE_FORWARDER( Rva003CA440FieldTwiceForwarder, gen003C92A0 )
BFME_FIELD_TWICE_FORWARDER( Rva003CA5D0FieldTwiceForwarder, gen003C92A0 )
BFME_FIELD_TWICE_FORWARDER( Rva003CA6A0FieldTwiceForwarder, gen003C92A0 )
BFME_FIELD_TWICE_FORWARDER( Rva005292F0FieldTwiceForwarder, gen005278B0 )
BFME_FIELD_TWICE_FORWARDER( Rva005293C0FieldTwiceForwarder, gen005278B0 )
BFME_FIELD_TWICE_FORWARDER( Rva00529B90FieldTwiceForwarder, gen005278B0 )
BFME_FIELD_TWICE_FORWARDER( Rva0054F3B0FieldTwiceForwarder, gen0054E9E0 )
BFME_FIELD_TWICE_FORWARDER( Rva0054F8B0FieldTwiceForwarder, gen0054E9E0 )
BFME_FIELD_TWICE_FORWARDER( Rva0054F980FieldTwiceForwarder, gen0054E9E0 )
BFME_FIELD_TWICE_FORWARDER( Rva0056E810FieldTwiceForwarder, gen0056DFC0 )
BFME_FIELD_TWICE_FORWARDER( Rva0056E8E0FieldTwiceForwarder, gen0056DFC0 )
BFME_FIELD_TWICE_FORWARDER( Rva0056E930FieldTwiceForwarder, gen0056DFC0 )
BFME_FIELD_TWICE_FORWARDER( Rva00595940FieldTwiceForwarder, gen005930E0 )
BFME_FIELD_TWICE_FORWARDER( Rva00596D20FieldTwiceForwarder, gen005930E0 )
BFME_FIELD_TWICE_FORWARDER( Rva00597730FieldTwiceForwarder, gen005930E0 )

BFME_FIELD_PAIR_CALLEE( 000FAF90 )
BFME_FIELD_PAIR_CALLEE( 00142350 )
BFME_FIELD_PAIR_CALLEE( 00147180 )
BFME_FIELD_PAIR_CALLEE( 00147EB0 )
BFME_FIELD_PAIR_CALLEE( 00197120 )
BFME_FIELD_PAIR_CALLEE( 00252E70 )
BFME_FIELD_PAIR_CALLEE( 002EB190 )
BFME_FIELD_PAIR_CALLEE( 00363820 )
BFME_FIELD_PAIR_CALLEE( 003668E0 )
BFME_FIELD_PAIR_CALLEE( 0039EB70 )
BFME_FIELD_PAIR_CALLEE( 003A3280 )
BFME_FIELD_PAIR_CALLEE( 003A5370 )
BFME_FIELD_PAIR_CALLEE( 003AF7A0 )
BFME_FIELD_PAIR_CALLEE( 003B2540 )
BFME_FIELD_PAIR_CALLEE( 003B2830 )
BFME_FIELD_PAIR_CALLEE( 003B6FD0 )
BFME_FIELD_PAIR_CALLEE( 006A3F30 )
BFME_FIELD_PAIR_CALLEE( 006F2A10 )
BFME_FIELD_PAIR_CALLEE( 007716A0 )
BFME_FIELD_PAIR_CALLEE( 00777EE0 )

BFME_FIELD_PAIR_FORWARDER( Rva000FB070FieldPairForwarder, Gen000FAF90 )
BFME_FIELD_PAIR_FORWARDER( Rva001444F0FieldPairForwarder, Gen00142350 )
BFME_FIELD_PAIR_FORWARDER( Rva00145270FieldPairForwarder, Gen00142350 )
BFME_FIELD_PAIR_FORWARDER( Rva00147EA0FieldPairForwarder, Gen00147180 )
BFME_FIELD_PAIR_FORWARDER( Rva001485A0FieldPairForwarder, Gen00147EB0 )
BFME_FIELD_PAIR_FORWARDER( Rva00197D20FieldPairForwarder, Gen00197120 )
BFME_FIELD_PAIR_FORWARDER( Rva00253130FieldPairForwarder, Gen00252E70 )
BFME_FIELD_PAIR_FORWARDER( Rva002EB760FieldPairForwarder, Gen002EB190 )
BFME_FIELD_PAIR_FORWARDER( Rva00364480FieldPairForwarder, Gen00363820 )
BFME_FIELD_PAIR_FORWARDER( Rva00366A10FieldPairForwarder, Gen003668E0 )
BFME_FIELD_PAIR_FORWARDER( Rva0039EC60FieldPairForwarder, Gen0039EB70 )
BFME_FIELD_PAIR_FORWARDER( Rva003A3400FieldPairForwarder, Gen003A3280 )
BFME_FIELD_PAIR_FORWARDER( Rva003A54F0FieldPairForwarder, Gen003A5370 )
BFME_FIELD_PAIR_FORWARDER( Rva003AFFF0FieldPairForwarder, Gen003AF7A0 )
BFME_FIELD_PAIR_FORWARDER( Rva003B2820FieldPairForwarder, Gen003B2540 )
BFME_FIELD_PAIR_FORWARDER( Rva003B28F0FieldPairForwarder, Gen003B2830 )
BFME_FIELD_PAIR_FORWARDER( Rva003B7080FieldPairForwarder, Gen003B6FD0 )
BFME_FIELD_PAIR_FORWARDER( Rva006A6DB0FieldPairForwarder, Gen006A3F30 )
BFME_FIELD_PAIR_FORWARDER( Rva006F2AF0FieldPairForwarder, Gen006F2A10 )
BFME_FIELD_PAIR_FORWARDER( Rva00774080FieldPairForwarder, Gen007716A0 )
BFME_FIELD_PAIR_FORWARDER( Rva00779CE0FieldPairForwarder, Gen00777EE0 )
