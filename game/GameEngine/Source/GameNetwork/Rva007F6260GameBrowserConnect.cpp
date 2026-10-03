// cl: /O2
// 0x007F6260: FESL game-browser ConnectingProtocol reply handler.
//
// The assertion names state 2.  The bytes establish the listener at +0x1c,
// the demangler/connect owner at +0x24, state at +0x30, and the optional-
// connect flag at +0x34.  The exact original interface names are unavailable;
// address- and state-derived names are used for those views.

// LINK: retail calls the message's error predicate at 0x007E88A0 and its
// error-code getter at 0x007E88B0 by their ledger names --
// ?valid@W3DVideoBuffer@@UAE_NXZ (11 bytes, the row owned by
// game/GameEngineDevice/Source/W3DDevice/GameClient/W3DVideoBuffer.cpp) and
// ?m@Gen_007e88b0@@QAEHXZ (4 bytes, the gen-shim row owned by
// game/gen_small/fun_005.cpp).  Neither `hasError` nor `getError` is defined by
// any object, so this TU now declares the two owning classes as local views and
// casts at each use, exactly as
// game/GameEngine/Source/Common/SmallGaps/Rva007F5A70VideoBufferValue.cpp does
// for the same pair.  `valid` is virtual (UAE) and `m` is not (QAE); both are
// called non-virtually here, which is a direct call in either case, so the two
// `call rel32` sites and their 0x007E88A0 / 0x007E88B0 targets are unchanged.
class W3DVideoBuffer
{
public:
	virtual bool valid();
};

class Gen_007e88b0
{
public:
	int m();
};

// The message pointer type of the two accessors above; kept for the signatures
// of the handler and the relay, which pass the object through untouched.
class Rva007E8810Message
{
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

	// Qualified call: retail calls the body directly rather than through the
	// vtable, so suppress virtual dispatch (as the VideoBufferValue TU does).
	if( ((W3DVideoBuffer *)msg)->W3DVideoBuffer::valid() )
	{
		status = ((Gen_007e88b0 *)msg)->m();
	}
	else
	{
		m_state = 3;
		if( m_connectProtocol )
			m_connectOwner->connect( 0, 0, 0 );
	}

	m_listener->onSlot0( status );
}

void Rva007F62E0Callback(Rva007E8810Message *message,
	Rva007F6260GameBrowser *browser)
{
	browser->handleConnectingProtocolReply(message);
}
