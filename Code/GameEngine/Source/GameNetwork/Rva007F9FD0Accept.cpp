// cl: /O2 /GX-
// Retail 0x007F9FD0 is the FESL transactor accept path reached by the
// named Rva007FA2C0::dispatch operation.  It base64-encodes the queued
// payload, fills the real FESL message ABI, and forwards bounded data chunks
// through the already matched busy operation.

extern "C" unsigned int __cdecl strlen( const char *text );
#pragma intrinsic( strlen )

class Rva007EFFC0Allocator
{
public:
	virtual void v0();
	virtual void v1();
	virtual void *allocate( int size, int flags );
	virtual void release( void *block, int flags );
};

Rva007EFFC0Allocator *Rva007EFFC0Get();
void rva007FF100Encode( unsigned int length, const char *source,
	void *destination );

class Rva007E8810Message
{
public:
	Rva007E8810Message();
	~Rva007E8810Message();
	void addInt( const char *key, int value );
	void addString( const char *key, const char *value );

	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	char *m_10;
	int m_14;
	int m_18;
	unsigned m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	char m_30;
	char m_pad31[ 3 ];
};

struct Rva007F9FD0Arg
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	char *m_text;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	unsigned char m_30;
};

class Rva007FA2C0Hub
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void *v5( void *message, int first, int second );
};

class Rva007FA2C0
{
public:
	int onAccept( void *arg );
	int onBusy( void *arg );

	char m_pad00[ 0x1c ];
	void *m_field1C;
	char m_pad20[ 4 ];
	Rva007FA2C0Hub *m_hub;
	char m_pad28[ 0x684 ];
};

int Rva007FA2C0::onAccept( void *rawArg )
{
	Rva007F9FD0Arg *arg = (Rva007F9FD0Arg *)rawArg;
	unsigned int length = strlen( arg->m_text );
	unsigned int encodedLength = ( ( length + 2 ) / 3 ) * 4;
	char *encoded = (char *)Rva007EFFC0Get()->allocate(
		(int)( encodedLength + 1 ), 0 );
	rva007FF100Encode( length, arg->m_text, encoded );

	{
	Rva007E8810Message message;
	message.m_04 = arg->m_04;
	message.m_08 = arg->m_08;
	message.m_0C = arg->m_0C;
	message.m_10 = arg->m_text;
	message.m_14 = arg->m_14;
	message.m_18 = arg->m_18;
	message.m_1C = arg->m_1C;
	message.m_20 = arg->m_20;
	message.m_24 = arg->m_24;
	message.m_28 = arg->m_28;
	message.m_2C = arg->m_2C;
	message.m_30 = arg->m_30;
	message.m_20 = (int)m_hub->v5( &message, 1, 1 );

	char *scratch = (char *)Rva007EFFC0Get()->allocate( 0x800, 0 );
	message.m_10 = scratch;
	message.m_14 = 0x800;
	unsigned int offset = 0;
	while( offset < encodedLength )
	{
		unsigned int chunk = encodedLength - offset;
		char *part = encoded + offset;
		if( chunk > 0x7e0 )
			chunk = 0x7e0;
		char saved = part[ chunk ];
		part[ chunk ] = 0;
		scratch[ 0 ] = 0;
		message.addInt( "size", (int)encodedLength );
		message.addString( "data", part );
		onBusy( &message );
		part[ chunk ] = saved;
		offset += chunk;
	}

	Rva007EFFC0Get()->release( encoded, 0 );
	Rva007EFFC0Get()->release( scratch, 0 );
	}
	return 0;
}
