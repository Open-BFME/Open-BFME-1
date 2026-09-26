// cl: /O2 /GX- /GS
// Retail 0x0080A110: route one FESL browser message.  The owner spelling is
// intentionally address-derived; the dispatcher at 0x0080A680 selects this
// body by message category, but no canonical owner class name is established.

extern "C" void _ReadWriteBarrier( void );
#pragma intrinsic( _ReadWriteBarrier )

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
	char m_pad30;
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

class BfmeThingHA
{
	public:
	char m_pad00[ 8 ];
	int m_keyA;
	int m_keyB;
	void *m_field10;
};

class Gen_00808E90
{
public:
	BfmeThingHA *bfmeFind( const BfmeThingHA *key ) const;
};

class Rva008038F0Sender
{
public:
	void send( BfmeC994 *message );
};

void sendFeslMessage( void *message, const char *route, void *owner );
extern int g_bfmeKeyVHE;
extern char g_bfmeLidKey[];
extern "C" char bfmeInfoDFI[];

struct Rva0080A110Message
{
	int m_category;
	int m_field04;
	int m_field08;
	int m_field0c;
	int m_field10;
	int m_field14;
	int m_field18;
	int m_field1c;
	int m_field20;
};

struct Rva0080A110State
{
	char m_pad00[ 0x2d8 ];
	void *m_sender;
};

class Rva0080A110Owner
{
public:
	void route( Rva0080A110Message *input );

	char m_pad00[ 4 ];
	Rva008038F0Sender *m_sender;
	Rva0080A110State *m_state;
	char m_pad0c[ 4 ];
	void *m_routeOwner;
	char m_pad14[ 0x44 ];
	Gen_00808E90 *m_lookup;
};

void Rva0080A110Owner::route( Rva0080A110Message *input )
{
	char buffer[ 0x40 ];
	BfmeC994 message( buffer, sizeof( buffer ) );

	message.m_category = input->m_field1c;
	void *value = reinterpret_cast< BfmeThingRF * >( input )->bfmeGoRF(
		&g_bfmeKeyVHE, (void *)-1 );
	if( value != (void *)-1 )
	{
		reinterpret_cast< BfmeThingCIB * >( &message )->bfmeGoCIB(
			&g_bfmeKeyVHE, value );
	}

	message.m_field04 = input->m_field04;
	message.m_field08 = input->m_field08;
	message.m_field0c = input->m_field0c;
	reinterpret_cast< BfmeThingCIB * >( &message )->bfmeGoCIB(
		g_bfmeLidKey, (void *)-2 );

	value = reinterpret_cast< BfmeThingRF * >( input )->bfmeGoRF(
		(void *)"GID", 0 );
	reinterpret_cast< BfmeThingCIB * >( &message )->bfmeGoCIB(
		(void *)"GID", value );

	if( m_state->m_sender == 0 || m_lookup == 0 )
	{
		message.m_field20 = 0x6e67616d;
		sendFeslMessage( &message, "->L", m_routeOwner );
	}
	else
	{
		BfmeThingHA *found = m_lookup->bfmeFind(
			reinterpret_cast< const BfmeThingHA * >( input ) );
		if( found == 0 )
		{
			message.m_field20 = 0x6e69676d;
			sendFeslMessage( &message, "->L", m_routeOwner );
		}
		else
		{
			sendFeslMessage( &message, "->L", m_routeOwner );

			BfmeC994 kick( buffer, sizeof( buffer ) );
			kick.m_category = 0x4b49434b;
			_ReadWriteBarrier();
			reinterpret_cast< BfmeThingCIB * >( &kick )->bfmeGoCIB(
				bfmeInfoDFI, found->m_field10 );
			m_sender->send( &kick );
			return;
		}
	}
}
