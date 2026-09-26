// Level two of the constructor chain in 0x005E97B0..0x005EA1F0.  Level one is
// game/GameEngine/Source/Common/T4ForwardingCtorChainL1.cpp; the leaves are in
// T4VtableSetCtors.cpp.  Each level is its own translation unit because MSVC
// 7.1 inlines a callee defined alongside its caller and retail keeps a `call`
// at every step.
//
// Retail, all six rows (62 bytes, or 62 with the wider second base):
//
//     push esi / push edi / mov edi,[esp+0xc] / push edi / mov esi,ecx
//     call <LEVEL-ONE CTOR>                      ; first base, at offset 0
//     test edi,edi / je L / lea eax,[edi+N] / jmp M / L: xor eax,eax
//     M: lea edi,[esi+N] / push eax / mov ecx,edi
//     call <SECOND BASE CTOR>                    ; second base, at offset N
//     mov [edi],  <V_N>                          ; N is 8 or 0xC
//     mov [esi],  <V_0>
//     mov [esi+4],<V_4>
//     mov eax,esi / pop esi / ret 4
//
// WHAT THE BYTES SHOW.  Two constructor calls with the receiver at +0 and at
// +N, and the SAME incoming dword handed to both -- unadjusted to the first,
// adjusted by N through MSVC's null-checked derived-to-base pointer form to the
// second.  That form (`test/je/lea/jmp/xor`) is the one WideSlotSetup.cpp
// measured: it appears for a NAMED base-pointer conversion and not for a plain
// inherited-member access, and it is why the argument is cast here rather than
// declared as a pointer -- the cast is what the bytes show, a declared pointer
// type would be a claim about the caller.
//
// N IS THE SIZE OF THE FIRST BASE and the first base is the level-one class the
// `call` names, so the two agree without being fitted: the three rows whose
// first base is a bare two-vptr level-one class adjust by 8, and the two whose
// first base is 0x005E9F00 -- two vptrs plus the one byte it copies at +8 --
// adjust by 0xC.
//
// THE THREE CONSTANT STORES ARE THE DERIVED CLASS'S OWN VFTABLE STAMPS, one per
// vptr the object owns: +N for the second base, then 0 and 4 for the two the
// first base brought.  Retail emits the +N one first because `edi` already
// holds `this+N` from the call it just made; the other two need `esi`.  No
// base's own store survives, and none should: both bases are `call`s, so their
// stores are inside their own bodies, not here.
//
// TWO OF THE SECOND BASES ARE ALREADY NAMED IN THE LEDGER -- Gen_005e9a20 and
// SimpleVecClass<Vector3> -- and the other four are pinned by address under
// address-derived names.  Every one of the four is a copy constructor by its
// own bytes: it stamps a vftable and then copies a fixed run of dwords out of
// the object the argument points at, which is what fixes both the parameter
// and the subobject's width (0x005E9800 and 0x005E9C70 copy one dword,
// 0x005EA0D0 copies thirteen, 0x005EA240 two dwords and a byte).
//
// IDENTITY IS NOT RECOVERED for anything named Rva* or T4B*; those names come
// from addresses.  The vftable dwords are DIR32 operands copied from retail and
// assert nothing beyond the fact that all six derived classes differ.

// --------------------------------------------- level-one bases, declared only

#define T4_SECOND_BASE( VT )                                                  \
	class T4A2_##VT { public: virtual void s0(); };

#define T4_TWO_VPTR_LEAF( NAME, VT )                                          \
	class T4P0_##NAME { public: virtual void s0(); };                         \
	class NAME : public T4P0_##NAME, public T4A2_##VT                         \
	{                                                                         \
	public:                                                                   \
		NAME( unsigned int a );                                               \
	};

T4_SECOND_BASE( 0110F9E4 )
T4_SECOND_BASE( 0110F9E8 )
T4_SECOND_BASE( 0110FA14 )
T4_SECOND_BASE( 0107375C )

T4_TWO_VPTR_LEAF( Rva005E9890, 0110F9E4 )
T4_TWO_VPTR_LEAF( Rva005E9AE0, 0110F9E8 )
T4_TWO_VPTR_LEAF( Rva005E9D00, 0110FA14 )
T4_TWO_VPTR_LEAF( Rva005E9F40, 0107375C )

#define T4_CHAIN_FORWARD_DECL( ROW, BASE )                                    \
	class Rva##ROW : public BASE                                              \
	{                                                                         \
	public:                                                                   \
		Rva##ROW( unsigned int a );                                           \
	};

T4_CHAIN_FORWARD_DECL( 005E9860, Rva005E9890 )
T4_CHAIN_FORWARD_DECL( 005E9AB0, Rva005E9AE0 )
T4_CHAIN_FORWARD_DECL( 005E9CD0, Rva005E9D00 )

class T4Flag005E9F00
{
public:
	T4Flag005E9F00( const T4Flag005E9F00 *source );
	unsigned char m_flag;
};

class Rva005E9F00 : public Rva005E9F40, public T4Flag005E9F00
{
public:
	Rva005E9F00( unsigned int a );
};

// ------------------------------------------------ second bases, declared only

// One dword after the vptr; copy constructor at 0x005E9800 / 0x005E9C70.
#define T4_SECOND_BASE_1DWORD( ADDR )                                         \
	class T4B##ADDR                                                           \
	{                                                                         \
	public:                                                                   \
		T4B##ADDR( const T4B##ADDR &other );                                  \
		virtual void s0();                                                    \
		void *m_field04;                                                      \
	};

T4_SECOND_BASE_1DWORD( 005E9800 )
T4_SECOND_BASE_1DWORD( 005E9C70 )

// Thirteen dwords after the vptr; copy constructor at 0x005EA0D0.
class T4B005EA0D0
{
public:
	T4B005EA0D0( const T4B005EA0D0 &other );
	virtual void s0();
	void *m_field[ 13 ];
};

// Two dwords and a byte after the vptr; copy constructor at 0x005EA240.
class T4B005EA240
{
public:
	T4B005EA240( const T4B005EA240 &other );
	virtual void s0();
	void *m_field04;
	void *m_field08;
	unsigned char m_field0C;
};

// Already in the ledger: the copy constructor at 0x005E9A20, whose class
// game/GameEngine/Source/GameClient/Gen_005e9a20.cpp sizes at 0x20.
class Gen_005e9a20
{
public:
	Gen_005e9a20( const Gen_005e9a20 &other );
	virtual void s0();
	int m_field[ 7 ];
};

// Already in the ledger: the copy constructor at 0x005E9E90, from
// game/Libraries/Source/WWVegas/WW3D2/segline.cpp.  Declared here rather than
// included because the header's own copy constructor is implicit and would be
// inlined; retail's `call` proves this one is not.
class Vector3;

template < class T > class SimpleVecClass
{
public:
	SimpleVecClass( const SimpleVecClass< T > &other );
	virtual ~SimpleVecClass();
	virtual bool Resize( int newsize );
	virtual bool Uninitialised_Grow( int newsize );
protected:
	T *Vector;
	int VectorMax;
};

// ------------------------------------------------------------------ the rows

#define T4_TWO_BASE_FORWARD( ROW, BASE0, BASE2 )                              \
	class Rva##ROW : public BASE0, public BASE2                               \
	{                                                                         \
	public:                                                                   \
		Rva##ROW( unsigned int a );                                           \
	};                                                                        \
	Rva##ROW::Rva##ROW( unsigned int a )                                      \
		: BASE0( a ),                                                         \
		  BASE2( *(const BASE2 *)(const Rva##ROW *)a )                        \
	{                                                                         \
	}

T4_TWO_BASE_FORWARD( 005E97B0, Rva005E9860, T4B005E9800 )
T4_TWO_BASE_FORWARD( 005E99D0, Rva005E9AB0, Gen_005e9a20 )
T4_TWO_BASE_FORWARD( 005E9C20, Rva005E9CD0, T4B005E9C70 )
T4_TWO_BASE_FORWARD( 005EA080, Rva005E9AB0, T4B005EA0D0 )
T4_TWO_BASE_FORWARD( 005EA1F0, Rva005E9F00, T4B005EA240 )

class Rva005E9E40 : public Rva005E9F00, public SimpleVecClass< Vector3 >
{
public:
	Rva005E9E40( unsigned int a );
};

Rva005E9E40::Rva005E9E40( unsigned int a )
	: Rva005E9F00( a ),
	  SimpleVecClass< Vector3 >(
		  *(const SimpleVecClass< Vector3 > *)(const Rva005E9E40 *)a )
{
}
