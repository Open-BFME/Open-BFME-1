// cl: /EHs-c-
// Four 62-byte __thiscall copy constructors, one level further down the chain
// than V3CopyCtorForwarders.cpp.  Retail:
//
//     push esi ; push edi ; mov edi,[esp+0xC] ; push edi ; mov esi,ecx
//     call <FIRST BASE COPY CTOR>            ; base at 0, argument forwarded
//     test edi,edi ; je L ; lea eax,[edi+0xC] ; jmp M ; L: xor eax,eax ; M:
//     lea edi,[esi+0xC] ; push eax ; mov ecx,edi
//     call <SECOND BASE COPY CTOR>           ; base at 0xC, argument converted
//     mov [edi],   <DERIVED VFTABLE 0xC>
//     pop edi
//     mov [esi],   <DERIVED VFTABLE 0>
//     mov [esi+8], <DERIVED VFTABLE 8>
//     mov eax,esi ; pop esi ; ret 4
//
// WHAT THE BYTES SHOW.  Two calls, both taking one pointer: the first gets the
// argument unchanged (a base at offset 0), the second gets it through the
// null-propagating test/je/lea/jmp/xor conversion that a derived-to-base
// pointer cast at a non-zero offset compiles to -- so the second is a BASE at
// 0xC, not a member (a member subobject's address is never null and gets a bare
// displacement).  Three vptr slots are stamped afterwards, at 0, 8 and 0xC, so
// the first base carries two of them and is 0xC bytes wide.
//
// EVERY CALLEE IS ALREADY A LEDGER ROW, so this file mints no pin at all.  The
// first bases are the 32-byte forwarders landed in V3CopyCtorForwarders.cpp --
// 0x005EA920, 0x005EAB80 (twice) and 0x005EADE0 -- and their {0, 8} slot pair
// and 0xC width are exactly what those bodies and their own bases already say.
// The second bases are the polymorphic scalar-only classes landed in
// V3PolyCopyCtors.cpp (0x005E9800, 0x005E9C70, 0x005EA0D0) and in
// game/GameEngine/Source/GameClient/Gen_005e9a20.cpp.  Each is re-declared here
// with the layout that file gives it and its copy constructor DECLARED AND NOT
// DEFINED, because defining one would inline it and destroy the call.
//
// THAT MAKES FIVE LEVELS OF ONE CHAIN VISIBLE IN THIS RANGE, e.g.
// 0x005EAA80 -> 0x005EAAB0 -> 0x005EAB80 -> 0x005EABB0 -> its two inlined bases.
//
// FOUR DIFFERENT DERIVED VFTABLE TRIPLES, so four classes.  Two of them share a
// first base (0x005EAB80) and differ in their second, which is what makes the
// second base a real axis rather than a spelling.
//
// IDENTITY IS NOT RECOVERED.  Names come from addresses; three vftable dwords
// per body are DIR32 sites the gate takes from the target, leaving 38 of the 62
// bytes concrete.

typedef int Int;

// ---- the pieces the first bases are built from (no byte of these bodies) ----

class V3Slot0N	{ public: virtual void s0(); virtual ~V3Slot0N() {} int m_a; };
class V3Slot1	{ public: virtual void s0(); virtual ~V3Slot1() {} };

#define V3_FIRST_BASE_PAIR( INNER, OUTER )                                \
	class INNER : public V3Slot0N, public V3Slot1                         \
	{                                                                     \
	public:                                                               \
		INNER( const INNER & );                                           \
	};                                                                    \
	class OUTER : public INNER                                            \
	{                                                                     \
	public:                                                               \
		OUTER( const OUTER & );                                           \
	};

V3_FIRST_BASE_PAIR( Rva005EA9B0, Rva005EA920 )
V3_FIRST_BASE_PAIR( Rva005EABB0, Rva005EAB80 )
V3_FIRST_BASE_PAIR( Rva005EAE70, Rva005EADE0 )

// ---------------------------------- the second bases, at 0xC ----------------

#define V3_SECOND_BASE_ONE_INT( NAME )                                    \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		NAME( const NAME &other );                                        \
		virtual ~NAME();                                                  \
		Int m_field04;                                                    \
	};

V3_SECOND_BASE_ONE_INT( Rva005E9800 )
V3_SECOND_BASE_ONE_INT( Rva005E9C70 )

class Rva005EA0D0
{
public:
	Rva005EA0D0( const Rva005EA0D0 &other );
	virtual ~Rva005EA0D0();

	Int m_field04, m_field08, m_field0C, m_field10, m_field14;
	Int m_field18, m_field1C, m_field20, m_field24, m_field28;
	Int m_field2C, m_field30, m_field34;
};

class Gen_005e9a20
{
public:
	Gen_005e9a20( const Gen_005e9a20 &other );
	virtual ~Gen_005e9a20();
	virtual void v1( void );
	virtual void v2( void );
	virtual void v3( void );

	Int m_field04, m_field08, m_field0C, m_field10;
	Int m_field14, m_field18, m_field1C;
};

// -------------------------------------------------------------- the rows ----

#define V3_CHAINED_COPY_CTOR( NAME, FIRST, SECOND )                       \
	class NAME : public FIRST, public SECOND                              \
	{                                                                     \
	public:                                                               \
		NAME( const NAME & );                                             \
	};                                                                    \
	NAME::NAME( const NAME &o ) : FIRST( o ), SECOND( o ) {}

V3_CHAINED_COPY_CTOR( Rva005EA850, Rva005EA920, Rva005E9800 )
V3_CHAINED_COPY_CTOR( Rva005EAAB0, Rva005EAB80, Gen_005e9a20 )
V3_CHAINED_COPY_CTOR( Rva005EAD10, Rva005EADE0, Rva005E9C70 )
V3_CHAINED_COPY_CTOR( Rva005EB1F0, Rva005EAB80, Rva005EA0D0 )
