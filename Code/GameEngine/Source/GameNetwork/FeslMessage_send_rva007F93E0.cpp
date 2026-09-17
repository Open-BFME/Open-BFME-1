// cl: /O2 /GX- /GS
// Retail 0x007F93E0: the FESL message route/send helper.  The direct dispatch
// caller passes three pointers; the chain-report caller preserves the pointer
// return from connection vtable slot 3.

typedef unsigned char Byte;

extern int vftable_011296B0;

class Rva007E86B0Base
{
public:
	Rva007E86B0Base();
	virtual ~Rva007E86B0Base();

	int m_field04;
};

struct Rva007F93E0Prefix
{
	Rva007F93E0Prefix()
	{
		m_00 = 0;
		m_04 = 0;
		m_08 = 0;
		m_0c = 0;
		m_10 = 0;
	}

	int m_00;
	int m_04;
	char *m_08;
	int m_0c;
	Byte m_10;
};

class Rva007F93E0Tail : public Rva007E86B0Base
{
};

class Rva007F93E0Envelope
{
	public:
	Rva007F93E0Prefix m_prefix;
	Rva007F93E0Tail m_tail;
	volatile int m_1c;
	volatile int m_20;
};

struct Rva007F93E0Message
{
	Byte m_pad00[ 8 ];
	int m_08;
	int m_0c;
	char *m_10;
	Byte m_pad14[ 8 ];
	int m_1c;
	int m_20;
	Byte m_pad24[ 12 ];
	Byte m_30;
};

struct Rva00800E50Header;
void Rva007F91D0( Rva00800E50Header *header, const char *route );

class Rva007F93E0Connection
{
public:
	virtual void v0() = 0;
	virtual void v1() = 0;
	virtual void v2() = 0;
	virtual void *v3( Rva007F93E0Envelope *envelope ) = 0;
};

void *Rva007F93E0( void *rawMessage, void *rawRoute, void *rawConnection )
{
	Rva007F93E0Message *message = (Rva007F93E0Message *)rawMessage;
	Rva007F93E0Connection *connection =
		(Rva007F93E0Connection *)rawConnection;
	Rva007F93E0Envelope envelope;

	int message20 = message->m_20;
	envelope.m_prefix.m_00 = message->m_1c;
	char *messageBuffer = message->m_10;
	*(volatile int *)&envelope.m_tail = (int)&vftable_011296B0;
	envelope.m_1c = 0;
	envelope.m_20 = 0;
	envelope.m_tail.m_field04 = 0;
	*(volatile int *)&envelope.m_prefix.m_04 = message20;
	envelope.m_prefix.m_08 = messageBuffer;

	char *scan = envelope.m_prefix.m_08;
	char *start = scan + 1;
	Byte value;
	do
	{
		value = (Byte)*scan;
		++scan;
	}
	while ( value != 0 );
	int message08 = message->m_08;
	envelope.m_prefix.m_0c = (int)( scan - start ) + 1;
	envelope.m_prefix.m_10 = message->m_30;
	envelope.m_1c = message08;
	envelope.m_20 = message->m_0c;

	Rva007F91D0( (Rva00800E50Header *)&envelope, (const char *)rawRoute );
	return connection->v3( &envelope );
}
