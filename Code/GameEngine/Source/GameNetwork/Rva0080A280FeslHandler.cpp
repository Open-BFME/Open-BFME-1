// cl: /O2 /GX- /GS
// Retail 0x0080A280 has no caller or proven semantic owner, so this source
// keeps the address-derived owner and method names.

char *__cdecl ji_009f709c( const char *text, const char *find );
#pragma comment( linker, "/alternatename:?ji_009f709c@@YAPADPBD0@Z=?ji_009f709c@@YAXXZ" )
extern "C" __declspec( dllimport ) unsigned int __cdecl strlen(
	const char *text );
#pragma intrinsic( strlen )

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

class Rva008091C0Owner
{
public:
	void handle( BfmeC994 *message, int value, char *name );
};

struct Rva0080A280State
{
	char m_pad00[ 0x2d8 ];
	char *m_text;
};

struct Rva0080A280Input
{
	int m_field00;
	int m_field04;
	int m_field08;
	int m_field0c;
	char m_pad10[ 0x0c ];
	int m_field1c;
};

class Rva0080A280Owner
{
public:
	void rva0080A280( Rva0080A280Input *input );

	char m_pad00[ 8 ];
	Rva0080A280State *m_state;
	char m_pad0c[ 4 ];
	void *m_routeOwner;
	char m_pad14[ 0x44 ];
	char *m_field58;
};

extern int g_bfmeKeyVHE;
void *Rva007F93E0( void *message, void *route, void *owner );

void Rva0080A280Owner::rva0080A280( Rva0080A280Input *input )
{
	char buffer[ 0x200 ];
	BfmeC994 message( buffer, sizeof( buffer ) );
	BfmeThingRF *source = reinterpret_cast< BfmeThingRF * >( input );

	message.m_category = input->m_field1c;
	void *value = source->bfmeGoRF( &g_bfmeKeyVHE, (void *)-1 );
	if( value != (void *)-1 )
		reinterpret_cast< BfmeThingCIB * >( &message )->bfmeGoCIB(
			&g_bfmeKeyVHE, value );
	message.m_field04 = input->m_field04;
	message.m_field08 = input->m_field08;
	message.m_field0c = input->m_field0c;

	char name[ 0x100 ];
	reinterpret_cast< BfmeThingUPB * >( input )->bfmeGoUPB(
		(void *)0x112C018, name, (void *)0x100 );
	if( m_state->m_text != 0 )
	{
		int length = strlen( name );
		if( length == 0 || ji_009f709c( name, m_field58 + 0x8c ) != 0 )
		{
			char shortName[ 0x20 ];
			reinterpret_cast< BfmeThingUPB * >( input )->bfmeGoUPB(
				(void *)0x112BE6C, shortName, (void *)0x20 );
			reinterpret_cast< Rva008091C0Owner * >( this )->handle(
				&message,
				(int)( long )source->bfmeGoRF( (void *)0x112B568, (void *)0 ),
				shortName );
			goto send;
		}
	}

	message.m_field20 = 0x6e67616d;

send:
	Rva007F93E0( &message, (void *)0x112C7C0, m_routeOwner );
}
