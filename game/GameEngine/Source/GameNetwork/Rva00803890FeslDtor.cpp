// cl: /GX-
// FESL browser factory dtor @ 0x803890 (96B). Twin of ctor shape at 0x803820:
// derived dual-vptr, optional m_10/m_14 unlink when +9 set, scalar-delete m_18,
// clear +0C/+10/+14, tail to base vptr restore (Gen_007fa650). Secondary vptr
// at +4 is an ordinary member so the primary vfptr stays compiler-owned.

extern void *g_Rva00803890Vt2[];

class Gen_007f9590
{
public:
	void m( int a );
};

class Rva00803890Peer
{
public:
	virtual void v0();
	virtual void release( void *p );
};

class Rva00803890Child
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void *deleting( unsigned char flags );
};

class Rva00803890Base
{
public:
	virtual ~Rva00803890Base();
};

__declspec(noinline) Rva00803890Base::~Rva00803890Base() {}

class Rva00803890Owner : public Rva00803890Base
{
public:
	virtual ~Rva00803890Owner();

	void *m_vt2;
	char m_08;
	char m_09;
	char m_pad0a[2];
	void *m_0c;
	Gen_007f9590 *m_10;
	Rva00803890Peer *m_14;
	Rva00803890Child *m_18;
};

Rva00803890Owner::~Rva00803890Owner()
{
	m_vt2 = g_Rva00803890Vt2;
	if( m_09 )
	{
		m_10->m( (int)m_14 );
		void *adj = m_10 ? (char *)m_10 + 4 : 0;
		m_14->release( adj );
		m_09 = 0;
	}
	if( m_18 )
		m_18->deleting( 1 );
	m_0c = 0;
	m_10 = 0;
	m_14 = 0;
}
