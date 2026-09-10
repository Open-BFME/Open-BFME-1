// cl: /O2 /GX- /GS
// Retail 0x0080A3C0 is the BfmeThingUNC PDAT/TADP dispatcher.  Its receiver
// is the registered object constructed at 0x00808FD0; the matched
// rva00809330 and rva00809400 siblings consume the live message and GID on
// the two response arms.  The remaining 0x008091C0 call is retained as an
// address-derived declaration-only helper with its direct ret-0xc ABI.

class Rva007E86B0Base
{
public:
	Rva007E86B0Base();
	virtual ~Rva007E86B0Base();

	int m_field04;
};

class BfmeC994 : public Rva007E86B0Base
{
public:
	BfmeC994( char *buffer, int capacity );

	int m_field08;
	int m_field0c;
	char m_pad10[ 0x0c ];
	int m_category;
	int m_field20;
	char m_pad24[ 0x0c ];
	char m_tail30;
};

class BfmeThingCIB
{
public:
	void bfmeGoCIB( void *one, void *two );
};

class BfmeThingRF
{
public:
	void *bfmeGoRF( void *one, void *two );
};

class BfmeThingUPB
{
public:
	char bfmeGoUPB( void *one, char *out, void *two );
};

class Rva00802680Owner
{
public:
	virtual ~Rva00802680Owner();
	virtual const char *name() = 0;
	virtual int get() const = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual const char *valueForKey( const char *key ) = 0;
	virtual void slot18() = 0;
	virtual int type() = 0;
};

class Rva00809330Sender
{
public:
	virtual void slot00();
	virtual const char *value( const char *key ) const;
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual const char *uid() const;
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual int count();
	virtual Rva00802680Owner *at( int index );
};

struct BfmeOwnerUNC
{
	char m_pad00[ 0x2b0 ];
	char m_pad2b0[ 0x28 ];
	Rva00809330Sender *m_sender;
};

struct Rva0080A3C0Input
{
	int m_field00;
	int m_field04;
	int m_field08;
	int m_field0c;
	char m_pad10[ 0x0c ];
	int m_field1c;
};

class Rva008091C0Owner
{
public:
	void handle( BfmeC994 *message, int gid, char *name );
};

class BfmeThingUNC
{
public:
	void rva00809330( BfmeC994 *message, int gid );
	void rva00809400( BfmeC994 *message, int gid,
		Rva00802680Owner *player );
	void rva0080A3C0( Rva0080A3C0Input *input );

	void *m_vtable;
	int m_registrationValue;
	BfmeOwnerUNC *m_owner;
	char m_pad0c[ 4 ];
	void *m_routeOwner;
};

void *Rva007F93E0( void *message, void *route, void *owner );
extern int g_bfmeKeyVHE;

void BfmeThingUNC::rva0080A3C0( Rva0080A3C0Input *input )
{
	char buffer[ 0x200 ];
	BfmeC994 message( buffer, sizeof( buffer ) );
	BfmeThingRF *sourceRF = reinterpret_cast< BfmeThingRF * >( input );
	BfmeThingCIB *messageCIB = reinterpret_cast< BfmeThingCIB * >( &message );

	message.m_category = input->m_field1c;
	void *value = sourceRF->bfmeGoRF( &g_bfmeKeyVHE, (void *)-1 );
	if( value != (void *)-1 )
		messageCIB->bfmeGoCIB( &g_bfmeKeyVHE, value );
	message.m_field04 = input->m_field04;
	message.m_field08 = input->m_field08;
	message.m_field0c = input->m_field0c;

	if( m_owner->m_sender == 0 )
	{
		message.m_field20 = 0x6e67616d;
		Rva007F93E0( &message, (void *)"->L", m_routeOwner );
		return;
	}

	int gid = (int)(long)sourceRF->bfmeGoRF( (void *)"GID", (void *)0 );
	char name[ 0x20 ];
	reinterpret_cast< BfmeThingUPB * >( input )->bfmeGoUPB(
		(void *)"I", name, (void *)0x20 );
	reinterpret_cast< Rva008091C0Owner * >( this )->handle(
		&message, gid, name );
	Rva007F93E0( &message, (void *)"->L", m_routeOwner );

	BfmeC994 second( buffer, sizeof( buffer ) );
	BfmeThingCIB *secondCIB = reinterpret_cast< BfmeThingCIB * >( &second );
	second.m_category = input->m_field1c;
	value = sourceRF->bfmeGoRF( &g_bfmeKeyVHE, (void *)-1 );
	if( value != (void *)-1 )
		secondCIB->bfmeGoCIB( &g_bfmeKeyVHE, value );
	second.m_field04 = input->m_field04;
	second.m_field08 = input->m_field08;
	second.m_field0c = input->m_field0c;
	second.m_category = 0x47444554;
	rva00809330( &second, gid );
	Rva007F93E0( &second, (void *)"->L", m_routeOwner );

	Rva00809330Sender *sender = m_owner->m_sender;
	int index = 0;
	int count = sender->count();
	while( index < count )
	{
		Rva00802680Owner *player = sender->at( index );
		if( player->type() == 4 )
		{
			BfmeC994 playerMessage( buffer, sizeof( buffer ) );
			BfmeThingCIB *playerCIB =
				reinterpret_cast< BfmeThingCIB * >( &playerMessage );
			playerMessage.m_category = input->m_field1c;
			value = sourceRF->bfmeGoRF( &g_bfmeKeyVHE, (void *)-1 );
			if( value != (void *)-1 )
				playerCIB->bfmeGoCIB( &g_bfmeKeyVHE, value );
			playerMessage.m_field04 = input->m_field04;
			playerMessage.m_field08 = input->m_field08;
			playerMessage.m_field0c = input->m_field0c;
			playerMessage.m_category = 0x50444154;
			rva00809400( &playerMessage, gid, player );
			Rva007F93E0( &playerMessage, (void *)"->L",
				m_routeOwner );
		}
		++index;
		count = sender->count();
	}
}
