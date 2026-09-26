// cl: /O2
// 0x007F6260: FESL game-browser ConnectingProtocol reply handler.
//
// The assertion names state 2.  The bytes establish the listener at +0x1c,
// the demangler/connect owner at +0x24, state at +0x30, and the optional-
// connect flag at +0x34.  The exact original interface names are unavailable;
// address- and state-derived names are used for those views.

class Rva007E8810Message
{
public:
	bool hasError( void );
	int getError( void );
};

class Rva007F6260Listener
{
public:
	virtual void onSlot0( int status );
};

class Rva008006C0Owner
{
public:
	int connect( const char *name, const char *addr, int cookie );
};

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail( const char *expression, const char *file, int line );
};

extern Rva007EB810Diag *Rva007EB810Get();

class Rva007F6260GameBrowser
{
public:
	void handleConnectingProtocolReply( Rva007E8810Message *msg );

private:
	char m_pad000[ 0x1c ];
	Rva007F6260Listener *m_listener;
	char m_pad020[ 4 ];
	Rva008006C0Owner *m_connectOwner;
	char m_pad028[ 8 ];
	int m_state;
	bool m_connectProtocol;
};

void Rva007F6260GameBrowser::handleConnectingProtocolReply(
	Rva007E8810Message *msg )
{
	int status = 0;

	if( m_state != 2 )
	{
		Rva007EB810Get()->fail(
			"mState == GameBrowserStateConnectingProtocol",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowser.cpp",
			0x508 );
	}

	if( msg->hasError() )
	{
		status = msg->getError();
	}
	else
	{
		m_state = 3;
		if( m_connectProtocol )
			m_connectOwner->connect( 0, 0, 0 );
	}

	m_listener->onSlot0( status );
}
