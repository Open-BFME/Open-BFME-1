// ?tryAttach@Rva007E47A0Self@@QAE_NPAVRva007E47A0Peer@@@Z
// partial score=0.9 date=2026-09-02
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

class Rva007E47A0Self
{
public:
	bool tryAttach( Rva007E47A0Peer *peer );
private:
	virtual void unused0(); virtual void unused1();
	virtual void unused2(); virtual void unused3();
	virtual void unused4(); virtual void unused5();
	virtual void unused6(); virtual void unused7();
	virtual void unused8(); virtual void unused9();
	virtual void unused10();
	virtual int slotB( int flag );
	virtual int slotC();
	unsigned char m_pad[ 0x2c - 4 ];
	Rva007E47A0Peer *m_attached;
};

bool Rva007E47A0Self::tryAttach( Rva007E47A0Peer *peer )
{
	union FlagSlot { char flag; int value; } state;
	state.flag = 0;
	if ( peer->m_mode == 5 ) {
		state.flag = 1;
	}
	if ( peer->query( slotC(), slotB( state.value ) ) ) {
		m_attached = peer;
		return true;
	}
	peer->notify( 1 );
	return false;
}
