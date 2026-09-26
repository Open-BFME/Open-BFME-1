// cl: /EHs-c-
// Two 62-byte __thiscall copy constructors, the same two-call shape
// V3ChainedCopyCtorsWithSecondBase.cpp landed at 0xC, with the second base at
// 0x8 instead.  Retail:
//
//     push esi ; push edi ; mov edi,[esp+0xC] ; push edi ; mov esi,ecx
//     call <FIRST BASE CTOR>                 ; base at 0, argument unchanged
//     test edi,edi ; je L ; lea eax,[edi+8] ; jmp M ; L: xor eax,eax ; M:
//     lea edi,[esi+8] ; push eax ; mov ecx,edi
//     call <SECOND BASE COPY CTOR>           ; base at 8, argument converted
//     mov [edi],   <DERIVED VFTABLE 8>
//     pop edi
//     mov [esi],   <DERIVED VFTABLE 0>
//     mov [esi+4], <DERIVED VFTABLE 4>
//     mov eax,esi ; pop esi ; ret 4
//
// WHAT THE BYTES SHOW.  The second argument goes through the null-propagating
// test/je/lea/jmp/xor conversion, so the thing at 0x8 is a BASE and not a
// member; ONE round of three vptr stores, so one class and no intermediate
// level; and the first base is therefore 8 bytes wide carrying the slots at 0
// and 4.
//
// EVERY CALLEE IS ALREADY A LEDGER ROW, so this file mints no pin.  The first
// bases are the 32-byte forwarders T1ChainedVtableCtors.cpp landed at
// 0x005E9400 and 0x005E9640, whose own two vftable stores are exactly the
// {0, 4} pair re-stamped here and whose 8-byte width is what that pair means.
// Their constructors are declared there as taking one `void *`, so that is the
// spelling this file forwards to; the argument is the object being copied and
// reaches them at offset 0.
//
// The second bases are the polymorphic scalar-only classes V3PolyCopyCtors.cpp
// landed: 0x005E9390 (vptr plus a sixteen-dword block, 0x44 wide) and
// 0x005E95C0 (vptr plus a thirty-two-dword block and one more dword, 0x88
// wide).  Each is re-declared here with the layout that file gives it and its
// copy constructor DECLARED AND NOT DEFINED, because defining one would inline
// it and destroy the call -- the same rule V3ChainedCopyCtorsWithSecondBase.cpp
// states.  Nothing in this file reads their fields, so only their widths matter,
// and both widths come from bodies that copy every dword individually.
//
// THAT MAKES THE 0x005E9340 CHAIN FOUR LEVELS DEEP: 0x005E9310 -> 0x005E9340
// -> 0x005E9400 -> 0x005E9430, and the same for the 0x005E9570 column.
//
// IDENTITY IS NOT RECOVERED.  Names come from addresses; the three vftable
// dwords per body are DIR32 sites the gate takes from the target, leaving 44 of
// the 62 bytes concrete.

typedef int Int;

struct V3Block16 { Int m_v[ 16 ]; };
struct V3Block32 { Int m_v[ 32 ]; };

// ---- the first bases, landed in T1ChainedVtableCtors.cpp; declared only -----

#define V3_FIRST_BASE_AT_EIGHT( NAME )                                    \
	class NAME##P0 { public: virtual void s0(); };                        \
	class NAME##P1 { public: virtual void s0(); };                        \
	class NAME : public NAME##P0, public NAME##P1                         \
	{                                                                     \
	public:                                                               \
		NAME( void *a );                                                  \
	};

V3_FIRST_BASE_AT_EIGHT( T1Derived_005E9400 )
V3_FIRST_BASE_AT_EIGHT( T1Derived_005E9640 )

// ---- the second bases, landed in V3PolyCopyCtors.cpp; declared only --------

class Rva005E9390
{
public:
	Rva005E9390( const Rva005E9390 &other );
	virtual ~Rva005E9390();

	V3Block16 m_block;
};

class Rva005E95C0
{
public:
	Rva005E95C0( const Rva005E95C0 &other );
	virtual ~Rva005E95C0();

	V3Block32 m_block;
	Int m_field84;
};

// -------------------------------------------------------------- the rows ----

#define V3_CHAINED_COPY_CTOR_AT_EIGHT( NAME, FIRST, SECOND )              \
	class NAME : public FIRST, public SECOND                              \
	{                                                                     \
	public:                                                               \
		NAME( NAME &o );                                                  \
	};                                                                    \
	NAME::NAME( NAME &o ) : FIRST( &o ), SECOND( o ) {}

V3_CHAINED_COPY_CTOR_AT_EIGHT( Rva005E9340, T1Derived_005E9400, Rva005E9390 )
V3_CHAINED_COPY_CTOR_AT_EIGHT( Rva005E9570, T1Derived_005E9640, Rva005E95C0 )
