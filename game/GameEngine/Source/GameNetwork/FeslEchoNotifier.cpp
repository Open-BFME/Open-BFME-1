// cl: /GS

void sendFeslMessage( void *message, const char *route, void *connection ) throw();

// Retail 0x007E86C0: the shared seven-byte cleanup the FESL message bodies call
// (store the base vtable 0x01129358 into *this, then ret).  The local message's
// user-declared destructor is the only reference to it, so the scope-exit call
// is spelled through this neutral declaration instead.  The definition lives in
// game/gen_small/fun_005.cpp.
class Gen_007e86c0
{
public:
	void m();
};

class FeslEchoMessage
{
public:
	FeslEchoMessage( char *buffer, int capacity ) throw();
	void addInt( const char *key, int value ) throw();
	void addString( const char *key, const char *value ) throw();

	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	char m_pad10[ 0x0c ];
	unsigned int m_type;
	int m_20;
	char m_pad24[ 0x0c ];
	char m_ready;
	char m_pad31[ 3 ];
};

class FeslEchoNotifier
{
public:
	void notifyEcho();

private:
	char m_pad00[ 8 ];
	int *m_owner;
	char m_pad0c[ 4 ];
	void *m_connection;
	char m_pad14[ 8 ];
	char m_userId[ 0x25 ];
	char m_secret[ 0x25 ];
	char m_pad66[ 0x62 ];
	int m_transactionId;
};

extern char g_feslTransactionIdKey[];
extern char g_feslTypeKey[];

// ?notifyEcho@FeslEchoNotifier@@QAEXXZ
void FeslEchoNotifier::notifyEcho()
{
	char buffer[ 0x100 ];
	FeslEchoMessage message( buffer, sizeof( buffer ) );

	int *echo = (int *)( (char *)m_owner[ 3 ] + 0x28c );
	message.m_04 = echo[ 1 ];
	message.m_08 = echo[ 2 ];
	message.m_0c = echo[ 3 ];
	message.m_type = 'ECHO';
	message.m_20 = 0;
	message.m_ready = 1;
	message.addInt( g_feslTransactionIdKey, m_transactionId );
	message.addInt( g_feslTypeKey, 1 );
	if( m_userId[ 0 ] )
	{
		message.addString( "UGID", m_userId );
		message.addString( "SECRET", m_secret );
	}
	sendFeslMessage( &message, "->D", m_connection );
	reinterpret_cast< Gen_007e86c0 * >( &message )->m();
}
