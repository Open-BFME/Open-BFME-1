// ?finish@Rva0080A940Owner@@QAE_NXZ
// partial score=0.76 date=2026-09-09
// cl: /O2 /GX- /GS
//
// Retail 0x0080A940: fill a FESL game-browser record from a message -- TID,
// FAV-GAME-UID, then two clock samples off Rva007E9B70Get vslot 2.  Its
// finish method is the adjacent FESL list response body at 0x008099A0.

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
	__forceinline Rva00808CB0LanGameEntry( int sequence )
	{
		m_field08 = 0;
		m_field0c = 0;
		m_field04 = 0;
		m_sequence = sequence;
		m_field14 = 0;
	}

	int m_field08;
	int m_field0c;
	int m_sequence;
	int m_field14;
	char m_tail18[ 8 ];
};

extern int g_bfmeKeyVHE;
extern void Rva007F93E0( void *message, void *route, void *owner );
extern "C" char *strchr( const char *text, int character );
extern "C" int memcmp( const void *left, const void *right,
	unsigned int count );
extern "C" unsigned int strlen( const char *text );
extern "C" int sscanf( const char *text, const char *format, ... );

class Rva007E8810Message
{
public:
	int getInt( const char *key, int defaultValue );
	bool getString( const char *key, char *dest, int destSize );
};

struct Rva007E9B70Obj
{
	virtual void v0();
	virtual void v1();
	virtual unsigned int now();
};

Rva007E9B70Obj *Rva007E9B70Get();

class Rva0080A940Owner
{
public:
	void initFromMessage( Rva007E8810Message *msg );
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

bool Rva0080A940Owner::finish()
{
	register Rva0080A940Owner *owner = this;
	char response[ 0x1000 ];
	char messageBuffer[ 0x80 ];
	int result = 0;
	char * volatile cursor = response;
	register char *nullPointer = 0;
	int remaining = Rva0080F180( owner->m_field0c,
		reinterpret_cast< Rva007EA650FieldAddress * >(
			*(void **)( (char *)owner->m_field08 + 0x0c ) )->get(),
		response, sizeof( response ) );
	BfmeC994 request( messageBuffer, sizeof( messageBuffer ) );
	request.m_category = 'GLST';
	request.m_field20 = (int)0xC0000000;
	reinterpret_cast< BfmeThingCIB * >( &request )->bfmeGoCIB(
		&g_bfmeKeyVHE, (void *)owner->m_tid );

	if( remaining > 0 )
	{
		do
		{
			char *transport = strchr( cursor, '\t' );
			if( transport != nullPointer )
			{
				*transport = 0;
				++transport;
			}
			transport = strchr( transport, '\t' );
			if( transport != nullPointer )
			{
				*transport = 0;
				++transport;
			}
			char *line = strchr( transport, '\n' );
			if( line == nullPointer )
				cursor = 0;
			else
			{
				*line = 0;
				cursor = line + 1;
			}
			char *addressText = strchr( transport, ':' );
			if( addressText != nullPointer )
			{
				*addressText = 0;
				++addressText;
			}
			char *secondColon = strchr( addressText, ':' );
			if( secondColon != nullPointer )
				*secondColon = 0;
			if( memcmp( transport, "UDP", 4 ) == 0 )
			{
				Rva00808CB0LanGameEntry entry( 0 );
				int parsedPort = 0;
				sscanf( cursor, "%d", &entry.m_sequence );
				reinterpret_cast< Rva007E8760Addr * >( &entry )->parse(
					addressText, parsedPort );
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
						->bfmeGoCIC( (void *)"ANSW", addressText );
					reinterpret_cast< BfmeThingCIB * >( &request )->bfmeGoCIB(
						(void *)"GID", (void *)found->m_sequence );
					reinterpret_cast< BfmeThingCIB * >( &request )->bfmeGoCIB(
						(void *)"FAV-GAME-UID", owner->m_favGameUid );
					Rva007F93E0( &request, (void *)"->L", owner->m_field10 );
					++result;
				}
			}
			--remaining;
		}
		while( remaining != 0 );
	}

	reinterpret_cast< Gen_007e86c0 * >( &request )->m();
	return result > 0;
}

void Rva0080A940Owner::initFromMessage( Rva007E8810Message *msg )
{
	m_tid = msg->getInt( "TID", 0 );
	msg->getString( "FAV-GAME-UID", m_favGameUid, 0x100 );
	m_t0 = Rva007E9B70Get()->now() + 0x5DC;
	m_t1 = Rva007E9B70Get()->now() + 0x64;
	m_gap168[ 0 ] = 0;
	finish();
}
