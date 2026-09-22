// ?rva007F8400@BfmeThingDGD@@QAEXEHPAX@Z
// partial score=0.78 date=2026-09-22
// Retail 0x007F8400 is slot 6 of the proven BfmeThingDGD vtable.
// The surrounding constructor and destructor establish this field layout.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

#include <new>

class Rva007F8090Base
{
protected:
	unsigned m_v0;
	unsigned m_v4;
	unsigned m_v8;
};

class BfmeThingRE
{
public:
	void bfmeRunRE( int value );
};

class Rva007EADC0Owner
{
public:
	void send();
};

class Rva007F8400Node
{
public:
	virtual void v0( int value );
	virtual Rva007F8400Node *v1();
	virtual void v2();
	virtual void v3( void *value, int flag );
	virtual void v4( void *table, void *helper, void *owner );

	unsigned char m_pad[ 0x6a4 ];
	Rva007F8400Node *m_6a8;
};

class Rva00803890Owner
{
public:
	Rva00803890Owner( unsigned char flag, void *owner );
};

class BfmeThingAEB
{
public:
	void bfmeStartAEB( void *owner );
};

class Rva00803080
{
public:
	Rva00803080 &set( int value );
	void initPool();
};

class Rva00800920Owner
{
public:
	Rva00800920Owner( void *host );

	unsigned char m_pad[ 0x0c ];
	void *m_0c;
};

class Gen007F0130
{
public:
	static void *operator new( unsigned int size );
};

class BfmeThingDGD : public Rva007F8090Base
{
public:
	void rva007F8400( unsigned char flag, int connected, void *unused );

	void *m_0c;
	Rva007F8400Node *m_10;
	Rva007F8400Node *m_14;
	Rva007F8400Node *m_18;
	Rva007F8400Node *m_1c;
	Rva00803080 *m_20;
	Rva00800920Owner *m_24;
	unsigned m_28;
	unsigned m_2c;
	unsigned m_30;
	unsigned char m_34;
	unsigned char m_35;
};

void BfmeThingDGD::rva007F8400( unsigned char flag, int connected, void *unused )
{
	if( m_30 != 0 )
	{
		m_1c->v0( -105 );
		return;
	}

	unsigned char connectedByte = (unsigned char)connected;
	m_34 = flag;
	m_30 = 1;
	m_35 = connectedByte;
	((BfmeThingRE *)m_0c)->bfmeRunRE( connected );
	m_14 = m_10->v1();
	m_14->m_6a8->v3( (char *)this + 4, 0 );
	m_14->v4( (void *)0x0130a9d4, (void *)0x00bf6fa0, this );
	m_14->v4( (void *)0x0130a9f8, (void *)0x00bf6fb0, this );
	m_14->v4( (void *)0x0130aaac, (void *)0x00bf6fc0, this );
	m_14->v4( (void *)0x0130aaa0, (void *)0x00bf6fe0, this );
	m_14->v4( (void *)0x0130aa58, (void *)0x00bf6ff0, this );
	m_14->v4( (void *)0x0130ab18, (void *)0x00bf7000, this );
	m_14->v4( (void *)0x0130ab30, (void *)0x00bf83e0, this );
	m_14->v4( (void *)0x0130ab00, (void *)0x00bf7970, this );
	m_14->v4( (void *)0x0130ab24, (void *)0x00bf7010, this );
	m_14->v4( (void *)0x0130aa88, (void *)0x00bf7020, this );
	m_14->v4( (void *)0x0130aa7c, (void *)0x00bf83f0, this );

	if( connectedByte != 0 )
	{
		void *raw = Gen007F0130::operator new( 0x1c );
		if( raw != 0 )
			m_18 = (Rva007F8400Node *)new (raw) Rva00803890Owner( flag, this );
		else
			m_18 = 0;
	}
	else
		m_18 = 0;
	((BfmeThingAEB *)m_18)->bfmeStartAEB( m_14 );

	if( flag )
	{
		((Rva007EADC0Owner *)m_0c)->send();
		Rva00803080 *pool = (Rva00803080 *)Gen007F0130::operator new( 0x14 );
		if( pool != 0 )
			pool = &pool->set( (int)this );
		m_20 = pool;
	}
	else
		m_20 = 0;
	m_20->initPool();

	Rva00800920Owner *host = (Rva00800920Owner *)Gen007F0130::operator new( 0x1f8 );
	if( host != 0 )
		host = new (host) Rva00800920Owner( this );
	m_24 = host;
	if( host != 0 )
		host->m_0c = (void *)((char *)this + 8);
}
