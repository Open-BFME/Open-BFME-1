// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// BfmeThingDGD virtual at retail 0x007F8400, 452 bytes. The owner is proven
// by vtable 0x0112B800 slot 6, which the matched constructor 0x007F7FA0
// installs at this+0; that constructor also zeroes the +0x14..+0x30 words
// this body reads and writes. The method identity is not proven, so it
// keeps the address token.
//
// this+4 and this+8 carry the two secondary vtables the constructor writes
// (0x0112B7F8 and 0x0112B7F0), so the pointers handed out at those offsets
// are base conversions. The last store goes through a one-line inline
// setter: its by-value argument is what makes retail form this+8 in ecx
// ahead of the m_24 store on both arms of the duplicated return.
//
// The helper at 0x007EA4F0 ends in `jmp [edx+0x14]` with the stack
// untouched, forwarding its caller's single stack argument to the maker's
// slot 5; this body pushes its third argument for it.

#include <new>

class Rva0112B800Base
{
public:
	virtual void slot0();
};

class Rva0112B7F8Base
{
public:
	virtual void slot0();
};

class Rva0112B7F0Base
{
public:
	virtual void slot0();
};

struct BfmeOwnerUNC;
class BfmeOwnerAEB;
struct Rva00800920Host;

class BfmeThingRE
{
public:
	void bfmeRunRE( void *value );
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
	Rva00803890Owner( unsigned char value, BfmeOwnerUNC *owner );
};

class BfmeThingAEB
{
public:
	void bfmeStartAEB( BfmeOwnerAEB *owner );
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
	Rva00800920Owner( Rva00800920Host *host );

	void set0c( Rva0112B7F0Base *value ) { m_0c = value; }

	unsigned char m_pad[ 0x0c ];
	Rva0112B7F0Base *m_0c;
};

class Gen007F0130
{
public:
	static void *operator new( unsigned int size );
};

class BfmeThingDGD : public Rva0112B800Base, public Rva0112B7F8Base, public Rva0112B7F0Base
{
public:
	void rva007F8400( unsigned char arg34, int arg35, void *forwarded );

	void *m_0c;
	Rva007F8400Node *m_10;
	Rva007F8400Node *m_14;
	Rva00803890Owner *m_18;
	Rva007F8400Node *m_1c;
	Rva00803080 *m_20;
	Rva00800920Owner *m_24;
	unsigned m_28;
	unsigned m_2c;
	unsigned m_30;
	unsigned char m_34;
	unsigned char m_35;
};

// ?rva007F8400@BfmeThingDGD@@QAEXEHPAX@Z
void BfmeThingDGD::rva007F8400( unsigned char arg34, int arg35, void *forwarded )
{
	if( m_30 != 0 )
	{
		m_1c->v0( -105 );
		return;
	}

	unsigned char byte35 = (unsigned char)arg35;
	m_34 = arg34;
	m_30 = 1;
	m_35 = byte35;
	((BfmeThingRE *)m_0c)->bfmeRunRE( forwarded );
	m_14 = m_10->v1();
	m_14->m_6a8->v3( static_cast< Rva0112B7F8Base * >( this ), 0 );
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

	if( byte35 != 0 )
	{
		Rva00803890Owner *node = new (Gen007F0130::operator new( 0x1c )) Rva00803890Owner( arg34, (BfmeOwnerUNC *)this );
		m_18 = node;
		((BfmeThingAEB *)node)->bfmeStartAEB( (BfmeOwnerAEB *)m_14 );
	}

	if( arg34 )
		((Rva007EADC0Owner *)m_0c)->send();

	Rva00803080 *pool = (Rva00803080 *)Gen007F0130::operator new( 0x14 );
	if( pool != 0 )
		pool = &pool->set( (int)this );
	else
		pool = 0;
	m_20 = pool;
	pool->initPool();

	m_24 = new (Gen007F0130::operator new( 0x1f8 )) Rva00800920Owner( (Rva00800920Host *)this );
	m_24->set0c( this );
}
