// EA FESL game-browser hosted-player activation reply at retail 0x007F5D10.
// The assertion text names the pending-active state and the message carries
// the hosted-player TID used by the lookup.

extern "C" unsigned char bfmeInfoDFI[];

class Rva00803620Getter
{
public:
	void *getPtr( void *key, void *fallback );
};

class Rva007E8810Message
{
public:
	bool hasError();
	int getError();
};

class Rva008022A0Owner
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual int getState();
	void setHpState( int state );
};

class Rva007F5D10HostLookup
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual Rva008022A0Owner *find( int id );
	void resetHpState( Rva008022A0Owner *player );
};

#pragma comment(linker, "/alternatename:?resetHpState@Rva007F5D10HostLookup@@QAEXPAVRva008022A0Owner@@@Z=?Rva008014F0ResetHpState@@YGXPAVRva008022A0Owner@@@Z")

class Rva007F5D10Listener
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void notifyPendingActive( int id, int error );
	virtual void notifyActive( int id );
};

struct Rva007EB810Diag
{
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void fail( const char *expression, const char *file, int line );
};

extern Rva007EB810Diag *Rva007EB810Get();

class Rva007F5D10GameBrowser
{
public:
	void handlePendingActiveReply( Rva007E8810Message *message ) throw();

	char m_pad00[0x10];
	void *m_sender;
	void *m_notifier;
	char m_pad18[4];
	Rva007F5D10Listener *m_listener;
	char m_pad20[0x2b8];
	Rva007F5D10HostLookup *m_hosts;
	char m_messageBuffer[0x400];
	int m_transaction;
};

void Rva007F5D10GameBrowser::handlePendingActiveReply( Rva007E8810Message *message ) throw()
{
	if ( m_hosts == 0 )
		return;

	int id = (int)((Rva00803620Getter *)message)->getPtr(
		(void *)bfmeInfoDFI, 0 );
	Rva008022A0Owner *player = m_hosts->find( id );
	if ( player == 0 )
	{
		Rva007EB810Get()->fail( "hp",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowser.cpp",
			0x41d );
		return;
	}
	if ( player->getState() != 3 )
	{
		Rva007EB810Get()->fail(
			"hp->GetState() == HostedPlayerStatePendingActive",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowser.cpp",
			0x421 );
	}
	if ( !message->hasError() )
		player->setHpState( 4 );

	m_listener->notifyPendingActive( id, message->getError() );
	if ( message->hasError() )
	{
		m_listener->notifyActive( id );
		m_hosts->resetHpState( player );
	}
}
