// cl: /O2 /GX- /GS
// Retail 0x008099A0: parse the FESL LAN theater list response line by line and
// send one GLST answer per UDP game the entry table accepts.

struct Rva0080F100Object
{
	char m_defaultKey[ 0x60 ];
	void *m_module;
};

extern "C" int Rva0080F180( Rva0080F100Object *object,
	const char *key, char *output, int outputSize );

class BfmeC994
{
public:
	BfmeC994( char *buffer, int capacity );

	void *m_vft;
	int m_field04;
	int m_field08;
	int m_field0c;
	char *m_buffer;
	int m_capacity;
	int m_field18;
	int m_category;
	int m_field20;
	int m_field24;
	int m_field28;
	int m_field2c;
	char m_field30;
};

class BfmeThingCIB
{
public:
	void bfmeGoCIB( void *key, void *value );
};

class BfmeThingCIC
{
public:
	void bfmeGoCIC( void *key, void *value );
};

class Rva007EA650FieldAddress
{
public:
	char *get();
};

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail( const char *expression, const char *file, int line );
};

Rva007EB810Diag *Rva007EB810Get();

class Gen_007e86c0
{
public:
	void m();
};

class Rva007E8760Addr
{
public:
	void parse( const char *text, int extra );

	char m_pad00[ 8 ];
	unsigned int m_address;
	int m_extra;
};

struct Rva00809050Input
{
	int m_field00;
	int m_field04;
	int m_field08;
	int m_field0c;
};

class Rva00808CB0LanGameEntry;

class Rva00803620Sink
{
public:
	Rva00808CB0LanGameEntry *rva00809050( Rva00809050Input *input );
};

class Rva007E86B0Base
{
public:
	Rva007E86B0Base();
	virtual ~Rva007E86B0Base();

	int m_field04;
};

class Rva00808CB0LanGameEntry : public Rva007E86B0Base
{
public:
	__forceinline Rva00808CB0LanGameEntry()
	{
		m_field08 = 0;
		m_field0c = 0;
		m_field04 = 0;
	}

	int m_field08;
	int m_field0c;
	int m_sequence;
};

extern int g_bfmeKeyVHE;
void *Rva007F93E0( void *message, void *route, void *owner );
extern "C" char *strchr( const char *text, int character );
extern "C" int strcmp( const char *left, const char *right );
extern "C" int sscanf( const char *text, const char *format, ... );

class Rva0080A940Owner
{
public:
	bool finish();

	void *m_field00;
	void *m_field04;
	void *m_field08;
	Rva0080F100Object *m_field0c;
	void *m_field10;
	int m_nextLanGameId;
	Rva00808CB0LanGameEntry *m_lanGames[ 16 ];
	void *m_game;
	unsigned int m_t0;       // +0x5C
	unsigned int m_t1;       // +0x60
	int m_tid;               // +0x64
	char m_favGameUid[ 0x100 ]; // +0x68
	char m_gap168[ 1 ];      // +0x168
};

// Cuts text at the first separator and returns the text after it, or null.
static char *splitAt( char *text, int separator )
{
	char *found = strchr( text, separator );
	if( found == 0 )
		return 0;
	*found = 0;
	return found + 1;
}

bool Rva0080A940Owner::finish()
{
	char response[ 0x1000 ];
	char messageBuffer[ 0x80 ];
	Rva007EA650FieldAddress *keySource = reinterpret_cast< Rva007EA650FieldAddress * >(
		*(void **)( (char *)m_field08 + 0x0c ) );
	int remaining = Rva0080F180( m_field0c, keySource->get(),
		response, sizeof( response ) );
	int result = 0;
	BfmeC994 request( messageBuffer, sizeof( messageBuffer ) );
	request.m_category = 'GLST';
	request.m_field20 = (int)0xC0000000;
	reinterpret_cast< BfmeThingCIB * >( &request )->bfmeGoCIB(
		&g_bfmeKeyVHE, (void *)m_tid );

	char *cursor = response;
	for( ; remaining > 0; --remaining )
	{
		// Line layout: name TAB id TAB transport:address:port NEWLINE.
		cursor = splitAt( cursor, '\t' );
		char *idText = cursor;
		cursor = splitAt( cursor, '\t' );
		char *transport = cursor;
		cursor = splitAt( cursor, '\n' );
		char *addressText = splitAt( transport, ':' );
		char *colon = strchr( addressText, ':' );
		if( colon != 0 )
			*colon = 0;
		if( strcmp( "UDP", transport ) == 0 )
		{
			Rva00808CB0LanGameEntry entry;
			sscanf( idText, "%d", &entry.m_sequence );
			reinterpret_cast< Rva007E8760Addr * >( &entry )->parse(
				addressText, entry.m_sequence );
			Rva00808CB0LanGameEntry *found =
				reinterpret_cast< Rva00803620Sink * >( this )
					->rva00809050(
						 reinterpret_cast< Rva00809050Input * >( &entry ) );
			if( found == 0 )
			{
				Rva007EB810Get()->fail(
					"false",
					"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\lantheateremulator.cpp",
					0x24B );
			}
			else
			{
				request.m_field04 = entry.m_field04;
				request.m_field08 = entry.m_field08;
				request.m_field0c = entry.m_field0c;
				reinterpret_cast< BfmeThingCIC * >( &request )
					->bfmeGoCIC( (void *)"I", addressText );
				reinterpret_cast< BfmeThingCIB * >( &request )->bfmeGoCIB(
					(void *)"GID", (void *)found->m_sequence );
				reinterpret_cast< BfmeThingCIC * >( &request )->bfmeGoCIC(
					(void *)"FAV-GAME-UID", m_favGameUid );
				Rva007F93E0( &request, (void *)"->L", m_field10 );
				++result;
			}
		}
	}

	reinterpret_cast< Gen_007e86c0 * >( &request )->m();
	return result > 0 ? true : false;
}
