// cl: /GX- /GS
// jabba gamebrowserdemangler.cpp connect-reply @ 0x00800780 (174B).
// Matches pending TID at +0xC8; pulls ADDR/PORT, parses dotted-quad, sink notify.

class Rva007E8810Message
{
public:
	int getInt( const char *key, int defaultValue );                 // 0x007E8900
	bool getString( const char *key, char *dest, int destSize );     // 0x007E8A80
};

class Rva7F4CC0Child
{
public:
	Rva7F4CC0Child();                                                // 0x007E86B0
	virtual void v0();
	int m_04;
};

extern int vftable_011296B0;

class Rva00800780Addr : public Rva7F4CC0Child
{
public:
	Rva00800780Addr()
	{
		*(int *)this = (int)&vftable_011296B0;
		m_08 = 0;
		m_0C = 0;
		*(int *)( (char *)this + 4 ) = 0;
	}
	~Rva00800780Addr();                                              // 0x007E86C0
	void parse( const char *str, int extra );                        // 0x007E86D0

	void *m_08;
	void *m_0C;
};

struct Rva00800780Sink
{
	virtual void v0();
	virtual void notify( int status, Rva00800780Addr *addr, int cookie );
};

class Rva00800780Owner
{
public:
	void onConnectReply( Rva007E8810Message *msg );

	void *m_00;
	void *m_04;
	void *m_08;
	Rva00800780Sink *m_sink;
	char m_10[0xB8];
	int m_c8;
	int m_cc;
	int m_d0;
};

void Rva00800780Owner::onConnectReply( Rva007E8810Message *msg )
{
	if( msg->getInt( "TID", 0 ) != m_c8 )
		return;

	m_c8 = 0;
	Rva00800780Addr addr;
	char buf[0x20];
	msg->getString( "ADDR", buf, 0x20 );
	int port = msg->getInt( "PORT", 0 );
	addr.parse( buf, port );
	m_sink->notify( 0, &addr, m_d0 );
}
