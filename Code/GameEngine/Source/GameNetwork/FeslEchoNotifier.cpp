// cl: /GS

void sendFeslMessage( void *message, const char *route, void *connection ) throw();

class FeslEchoMessage
{
public:
	FeslEchoMessage( char *buffer, int capacity ) throw();
	~FeslEchoMessage() throw();
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
extern char g_feslUserIdKey[];
extern char g_feslSecretKey[];
extern char g_feslDirectRoute[];

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
		message.addString( g_feslUserIdKey, m_userId );
		message.addString( g_feslSecretKey, m_secret );
	}
	sendFeslMessage( &message, g_feslDirectRoute, m_connection );
}
