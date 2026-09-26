// cl: /O2
// 0x007F5720: FESL game-browser login-reply handler.
//
// The assertion text identifies state 4 as GameBrowserStateLoggingIn, while
// the receiver layout, message accessors, and listener slot are established by
// neighboring recovered gamebrowser bodies.  The original C++ method and
// listener-interface names are unavailable, so the remaining names are
// address-derived.

class Rva007E8810Message
{
public:
	bool hasError( void );
	int getError( void );
};

class Rva007F5720Listener
{
public:
	virtual void v0();
	virtual void v1();
	virtual void onSlot2( int status );
};

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail( const char *expression, const char *file, int line );
};

extern Rva007EB810Diag *Rva007EB810Get();

class Rva007F5720GameBrowser
{
public:
	void handleLoginReply( Rva007E8810Message *msg );

private:
	char m_pad000[ 0x1c ];
	Rva007F5720Listener *m_listener;
	char m_pad020[ 0x10 ];
	int m_state;
};

void Rva007F5720GameBrowser::handleLoginReply( Rva007E8810Message *msg )
{
	int status = 0;

	if( m_state != 4 )
	{
		Rva007EB810Get()->fail(
			"mState == GameBrowserStateLoggingIn",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowser.cpp",
			0x173 );
	}

	if( msg->hasError() )
	{
		status = msg->getError();
		m_state = 3;
	}
	else
	{
		m_state = 5;
	}

	m_listener->onSlot2( status );
}
