// cl: /O2 /GS
// Retail 0x0080A9B0 copies a game address record and sends its IP through ->L.

class BfmeC994
{
public:
	BfmeC994( char *buffer, int capacity );
	char *m_vft;
	int m_04;
	int m_08;
	int m_0c;
	char *m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	int m_28;
	int m_2c;
	char m_30;
};

class BfmeThingCIC
{
public:
	void bfmeGoCIC( void *one, void *two );
};

class Gen_007e86c0
{
public:
	void m();
};

class Rva007E8760Addr
{
public:
	void format( char *buffer, unsigned size );
};

struct Rva00809500Entry
{
	char m_pad00[ 0x10 ];
	const char *m_text;
	int m_gdatBufferSize;
	int m_pad18;
	int m_length;
};

struct Rva00809500Sink
{
	void accept( Rva00809500Entry *entry );

	int m_pad00;
	int m_value04;
	int m_value08;
	int m_value0c;
	int m_pad10;
	char *m_gdatBuffer;
	int m_gdatBufferSize;
	unsigned int m_gdatTimestamp;
};

class Rva007EFFC0Allocator
{
public:
	virtual void v0();
	virtual void v1();
	virtual void *allocate( int size, int flags );
	virtual void release( void *block, int flags );
};

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail( const char *expr, const char *file, int line );
};

struct Rva007E9B70Obj
{
	virtual void v0();
	virtual void v1();
	virtual unsigned int now();
};

Rva007EFFC0Allocator *Rva007EFFC0Get();
Rva007EB810Diag *Rva007EB810Get();
Rva007E9B70Obj *Rva007E9B70Get();

void Rva00809500Sink::accept( Rva00809500Entry *entry )
{
	if( m_gdatBuffer != 0 )
		Rva007EFFC0Get()->release( m_gdatBuffer, 0 );

	m_gdatBufferSize = entry->m_gdatBufferSize;
	m_gdatBuffer = (char *)Rva007EFFC0Get()->allocate( m_gdatBufferSize, 0 );
	if( m_gdatBuffer == 0 )
	{
		Rva007EB810Get()->fail(
			"mGdatBuffer",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\lantheateremulator.cpp",
			0x4EA );
	}

	const char *source = entry->m_text;
	char *dest = m_gdatBuffer;
	char value;
	do
	{
		value = *source++;
		*dest++ = value;
	}
	while( value != 0 );

	m_gdatTimestamp = Rva007E9B70Get()->now();
}

class Rva00809010Finder
{
public:
	Rva00809500Sink *find( Rva00809500Entry *entry );
};

void *Rva007F93E0( void *message, void *route, void *owner );
char * __cdecl ji_009f70ba( char *dest, const char *src, unsigned count );

class LanTheaterEmulator
{
public:
	void notifyAddress( Rva00809500Entry *entry );
	char m_pad00[ 0x10 ];
	void *m_field10;
};

void LanTheaterEmulator::notifyAddress( Rva00809500Entry *entry )
{
	char buffer[ 0x40 ];
	BfmeC994 message( buffer, sizeof( buffer ) );
	Rva00809500Sink *sink = reinterpret_cast< Rva00809010Finder * >( this )->find( entry );
	message.m_1c = entry->m_length;
	message.m_20 = (int)0xC0000000;
	ji_009f70ba( message.m_10, entry->m_text, message.m_14 );
	char address[ 0x20 ];
	reinterpret_cast< Rva007E8760Addr * >( sink )->format( address, sizeof( address ) );
	message.m_04 = sink->m_value04;
	message.m_08 = sink->m_value08;
	message.m_0c = sink->m_value0c;
	reinterpret_cast< BfmeThingCIC * >( &message )->bfmeGoCIC(
		(void *)0x1102DE0,
		address );
	Rva007F93E0( &message, (void *)0x112C7C0, m_field10 );
	reinterpret_cast< Gen_007e86c0 * >( &message )->m();
}
