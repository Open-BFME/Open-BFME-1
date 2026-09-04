// cl: /DNDEBUG /MD /O2 /Ob2
// Isolated 1054 category-table fragments already named by BfmeConv1054.cpp.
// 0x005CD4E0 is the last quartet of bfmeTailA1054Impl (make 8 + ILT 0x0003C9CF).
// 0x005CEF60 is H4+H5 then the cdecl A tail. 0x005D10E0 is key1+key2 then
// the cdecl B tail. 0x005CD990 is H7+H8 with no tail.

int bfmeMake1054( int n );

struct BfmeA1054H8
{
	char m_pad[ 0x80 ];
	int m_h8;
	void ( *m_fn8 )( void );
	int m_88;
	int m_8c;
};

void __cdecl bfmeInitH8_005CD4E0( BfmeA1054H8 *p )
{
	int z = 0;
	p->m_h8 = bfmeMake1054( 8 );
	p->m_fn8 = reinterpret_cast<void ( * )( void )>( 0x0043c9cf );
	p->m_88 = z;
	p->m_8c = z;
}

struct BfmeA1054
{
	char m_pad[ 0x50 ];
	int m_h;
	void ( *m_fn )( void );
	int m_58;
	int m_5c;
	int m_h6;
	void ( *m_fn6 )( void );
	int m_68;
	int m_6c;
	int m_h7;
	void ( *m_fn7 )( void );
	int m_78;
	int m_7c;
	int m_h8;
	void ( *m_fn8 )( void );
	int m_88;
	int m_8c;
};

struct BfmeB1054
{
	char m_pad[ 0x20 ];
	int m_h;
	void ( *m_fn )( void );
	int m_28;
	int m_2c;
	int m_h3;
	void ( *m_fn3 )( void );
	int m_38;
	int m_3c;
	int m_h4;
	void ( *m_fn4 )( void );
	int m_48;
	int m_4c;
	int m_h5;
	void ( *m_fn5 )( void );
	int m_58;
	int m_5c;
};

void bfmeTailA1054Cdecl( BfmeA1054 *p );
void bfmeTailB1054Cdecl( BfmeB1054 *p );

// H4+H5 then the cdecl A tail -- the back half of bfmeTailB1054Impl.
void __cdecl bfmeInitH45_005CEF60( BfmeB1054 *p )
{
	int z = 0;
	p->m_h4 = bfmeMake1054( 4 );
	p->m_fn4 = reinterpret_cast<void ( * )( void )>( 0x004410dd );
	p->m_48 = z;
	p->m_4c = z;
	p->m_h5 = bfmeMake1054( 5 );
	p->m_fn5 = reinterpret_cast<void ( * )( void )>( 0x00408b39 );
	p->m_58 = z;
	p->m_5c = z;
	bfmeTailA1054Cdecl( reinterpret_cast<BfmeA1054 *>( p ) );
}

struct BfmeCategoryHead1054
{
	int m_key0;
	void ( *m_callback0 )( void );
	int m_zero08;
	int m_zero0c;
	int m_key1;
	void ( *m_callback1 )( void );
	int m_zero18;
	int m_zero1c;
	int m_key2;
	void ( *m_callback2 )( void );
	int m_zero28;
	int m_zero2c;
};

// key1+key2 then the cdecl B tail -- the back half of bfmeCategoryHead1054.
void __cdecl bfmeInitKey12_005D10E0( BfmeCategoryHead1054 *p )
{
	int z = 0;
	p->m_key1 = bfmeMake1054( 1 );
	p->m_callback1 = reinterpret_cast<void ( * )( void )>( 0x004391a8 );
	p->m_zero18 = z;
	p->m_zero1c = z;
	p->m_key2 = bfmeMake1054( 2 );
	p->m_callback2 = reinterpret_cast<void ( * )( void )>( 0x00411897 );
	p->m_zero28 = z;
	p->m_zero2c = z;
	bfmeTailB1054Cdecl( reinterpret_cast<BfmeB1054 *>( p ) );
}

// H7+H8 with no tail -- the last two quartets of bfmeTailA1054Impl.
// Retail pops both make args in one add esp,8 and writes the H8 zeros
// before the handle and callback.
void __cdecl bfmeInitH78_005CD990( BfmeA1054 *p )
{
	int z = 0;
	p->m_h7 = bfmeMake1054( 7 );
	p->m_fn7 = reinterpret_cast<void ( * )( void )>( 0x00441c09 );
	p->m_78 = z;
	p->m_7c = z;
	int h8 = bfmeMake1054( 8 );
	p->m_88 = z;
	p->m_8c = z;
	p->m_h8 = h8;
	p->m_fn8 = reinterpret_cast<void ( * )( void )>( 0x0043c9cf );
}
