// Level three -- the top -- of the constructor chain in
// 0x005E97B0..0x005EA1F0.  Levels one and two are
// game/GameEngine/Source/Common/T4ForwardingCtorChainL1.cpp and
// T4ForwardingCtorChainL2.cpp; the leaves are in T4VtableSetCtors.cpp.  Each
// level is its own translation unit because MSVC 7.1 inlines a callee defined
// alongside its caller and retail keeps a `call`.
//
// Retail, all five rows (39 bytes):
//
//     mov eax,[esp+4] / push esi / push eax / mov esi,ecx
//     call <LEVEL-TWO CTOR>
//     mov [esi],  <V0>
//     mov [esi+4],<V4>
//     mov [esi+N],<VN>          ; N = 8 or 0xC
//     mov eax,esi / pop esi / ret 4
//
// WHAT THE BYTES SHOW.  One dword argument, re-pushed unchanged and never read,
// `mov eax,esi` before `ret 4`: a constructor that forwards its parameter to a
// single base and does nothing else.  Three constant stores, each written once,
// in ascending offset order -- the derived class stamping its own vftables
// after base construction.  No base store survives, so there is exactly one
// base, and the three vptrs are that base's own: the level-two class this row
// calls owns exactly three, at 0, 4 and N.  N AGREES ROW BY ROW with the offset
// its level-two callee adjusted by -- 8 for the three whose second base sits at
// 8, 0xC for the two whose second base sits at 0xC -- which is what makes the
// pairing a reading of the chain rather than a fit.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address; the
// vftable dwords are DIR32 operands copied from retail and say only that the
// five derived classes differ from each other and from their bases.

// ------------------------------- the chain below this level, declared only ---

#define T4_SECOND_BASE( VT )                                                  \
	class T4A2_##VT { public: virtual void s0(); };

#define T4_TWO_VPTR_LEAF( NAME, VT )                                          \
	class T4P0_##NAME { public: virtual void s0(); };                         \
	class NAME : public T4P0_##NAME, public T4A2_##VT                         \
	{                                                                         \
	public:                                                                   \
		NAME( unsigned int a );                                               \
	};

T4_SECOND_BASE( 0110F9E8 )
T4_SECOND_BASE( 0110FA14 )
T4_SECOND_BASE( 0107375C )

T4_TWO_VPTR_LEAF( Rva005E9AE0, 0110F9E8 )
T4_TWO_VPTR_LEAF( Rva005E9D00, 0110FA14 )
T4_TWO_VPTR_LEAF( Rva005E9F40, 0107375C )

#define T4_CHAIN_FORWARD_DECL( ROW, BASE )                                    \
	class Rva##ROW : public BASE                                              \
	{                                                                         \
	public:                                                                   \
		Rva##ROW( unsigned int a );                                           \
	};

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

#define T4_SECOND_BASE_1DWORD( ADDR )                                         \
	class T4B##ADDR                                                           \
	{                                                                         \
	public:                                                                   \
		T4B##ADDR( const T4B##ADDR &other );                                  \
		virtual void s0();                                                    \
		void *m_field04;                                                      \
	};

T4_SECOND_BASE_1DWORD( 005E9C70 )

class T4B005EA0D0
{
public:
	T4B005EA0D0( const T4B005EA0D0 &other );
	virtual void s0();
	void *m_field[ 13 ];
};

class T4B005EA240
{
public:
	T4B005EA240( const T4B005EA240 &other );
	virtual void s0();
	void *m_field04;
	void *m_field08;
	unsigned char m_field0C;
};

class Gen_005e9a20
{
public:
	Gen_005e9a20( const Gen_005e9a20 &other );
	virtual void s0();
	int m_field[ 7 ];
};

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

#define T4_TWO_BASE_FORWARD_DECL( ROW, BASE0, BASE2 )                         \
	class Rva##ROW : public BASE0, public BASE2                               \
	{                                                                         \
	public:                                                                   \
		Rva##ROW( unsigned int a );                                           \
	};

T4_TWO_BASE_FORWARD_DECL( 005E99D0, Rva005E9AB0, Gen_005e9a20 )
T4_TWO_BASE_FORWARD_DECL( 005E9C20, Rva005E9CD0, T4B005E9C70 )
T4_TWO_BASE_FORWARD_DECL( 005EA080, Rva005E9AB0, T4B005EA0D0 )
T4_TWO_BASE_FORWARD_DECL( 005EA1F0, Rva005E9F00, T4B005EA240 )
T4_TWO_BASE_FORWARD_DECL( 005E9E40, Rva005E9F00, SimpleVecClass< Vector3 > )

// ------------------------------------------------------------------ the rows

#define T4_CHAIN_FORWARD( ROW, BASE )                                         \
	class Rva##ROW : public BASE                                              \
	{                                                                         \
	public:                                                                   \
		Rva##ROW( unsigned int a );                                           \
	};                                                                        \
	Rva##ROW::Rva##ROW( unsigned int a ) : BASE( a )                          \
	{                                                                         \
	}

T4_CHAIN_FORWARD( 005E99A0, Rva005E99D0 )
T4_CHAIN_FORWARD( 005E9BF0, Rva005E9C20 )
T4_CHAIN_FORWARD( 005E9E10, Rva005E9E40 )
T4_CHAIN_FORWARD( 005EA050, Rva005EA080 )
T4_CHAIN_FORWARD( 005EA1C0, Rva005EA1F0 )
