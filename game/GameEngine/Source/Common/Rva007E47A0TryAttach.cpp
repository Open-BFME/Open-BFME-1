// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

class Rva007E47A0Peer
{
public:
	virtual void unused0();
	virtual void notify( int flag );
	virtual bool query( int first, int second );

private:
	unsigned char m_pad[ 0x24 - 4 ];
	int m_mode;
	friend class Rva007E47A0Self;
};

class Rva007E47A0SelfView
{
public:
	virtual void unused0(); virtual void unused1();
	virtual void unused2(); virtual void unused3();
	virtual void unused4(); virtual void unused5();
	virtual void unused6(); virtual void unused7();
	virtual void unused8(); virtual void unused9();
	virtual void unused10();
	virtual int slotB( int flag );
	virtual int slotC();
	unsigned char m_pad[ 0x2c - 4 ];
};

class Rva007E47A0Self : public Rva007E47A0SelfView
{
public:
	bool tryAttach( Rva007E47A0Peer *peer );

private:
	Rva007E47A0Peer *m_attached;
};

bool Rva007E47A0Self::tryAttach( Rva007E47A0Peer *peer )
{
	union FlagSlot {
		int value;
		bool flag;
	} volatile state;
	state.flag = 0;
	if ( peer->m_mode == 5 ) {
		state.flag = 1;
	}
	int flagValue = state.value;
	if ( peer->query( slotC(), slotB( flagValue ) ) ) {
		m_attached = peer;
		return true;
	}
	peer->notify( 1 );
	return false;
}
