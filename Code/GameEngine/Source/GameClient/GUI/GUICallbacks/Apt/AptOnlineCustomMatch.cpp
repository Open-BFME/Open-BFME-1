// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
//
// BfmeAptScreenOnlineCustomMatch leave/cancel helper, retail 0x00539750,
// 93 bytes. State 8 only clears this+0x57. Otherwise a thiscall at ILT
// 0x0001118F runs, then TheGameSpyInfo (nullable) getCurrentStagingRoom
// (+0xC4) is reset (+0x08) and leaveStagingRoom (+0xB0) fires, then the
// embedded +0x40 object vslot +4 and this+0x188 is cleared.

class GameSpyStagingRoom
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void reset() = 0;
};

#define GAMESPY_SLOT( n ) virtual void gamespySlot##n() = 0
class GameSpyInfo
{
public:
	GAMESPY_SLOT( 0 ); GAMESPY_SLOT( 1 ); GAMESPY_SLOT( 2 ); GAMESPY_SLOT( 3 );
	GAMESPY_SLOT( 4 ); GAMESPY_SLOT( 5 ); GAMESPY_SLOT( 6 ); GAMESPY_SLOT( 7 );
	GAMESPY_SLOT( 8 ); GAMESPY_SLOT( 9 ); GAMESPY_SLOT( 10 ); GAMESPY_SLOT( 11 );
	GAMESPY_SLOT( 12 ); GAMESPY_SLOT( 13 ); GAMESPY_SLOT( 14 ); GAMESPY_SLOT( 15 );
	GAMESPY_SLOT( 16 ); GAMESPY_SLOT( 17 ); GAMESPY_SLOT( 18 ); GAMESPY_SLOT( 19 );
	GAMESPY_SLOT( 20 ); GAMESPY_SLOT( 21 ); GAMESPY_SLOT( 22 ); GAMESPY_SLOT( 23 );
	GAMESPY_SLOT( 24 ); GAMESPY_SLOT( 25 ); GAMESPY_SLOT( 26 ); GAMESPY_SLOT( 27 );
	GAMESPY_SLOT( 28 ); GAMESPY_SLOT( 29 ); GAMESPY_SLOT( 30 ); GAMESPY_SLOT( 31 );
	GAMESPY_SLOT( 32 ); GAMESPY_SLOT( 33 ); GAMESPY_SLOT( 34 ); GAMESPY_SLOT( 35 );
	GAMESPY_SLOT( 36 ); GAMESPY_SLOT( 37 ); GAMESPY_SLOT( 38 ); GAMESPY_SLOT( 39 );
	GAMESPY_SLOT( 40 ); GAMESPY_SLOT( 41 ); GAMESPY_SLOT( 42 ); GAMESPY_SLOT( 43 );
	virtual void leaveStagingRoom() = 0;
	GAMESPY_SLOT( 45 ); GAMESPY_SLOT( 46 ); GAMESPY_SLOT( 47 ); GAMESPY_SLOT( 48 );
	virtual GameSpyStagingRoom *getCurrentStagingRoom() = 0;
};
#undef GAMESPY_SLOT

extern GameSpyInfo *TheGameSpyInfo;

class BfmeCustomMatchMember40
{
public:
	virtual void slot00();
	virtual void notifyLeave();
};

class BfmeAptScreenOnlineCustomMatch
{
public:
	void leaveStagingRoom( int unused );
	void clearLocalStagingState();

private:
	unsigned char m_head[ 0x40 ];
	BfmeCustomMatchMember40 m_setup;
	unsigned char m_mid[ 0x57 - 0x44 ];
	unsigned char m_flag57;
	unsigned char m_tail[ 0x188 - 0x58 ];
	int m_state;
};

void BfmeAptScreenOnlineCustomMatch::leaveStagingRoom( int unused )
{
	(void)unused;
	if( m_state == 8 )
	{
		m_flag57 = 0;
		return;
	}
	clearLocalStagingState();
	if( TheGameSpyInfo )
	{
		GameSpyStagingRoom *room = TheGameSpyInfo->getCurrentStagingRoom();
		if( room )
			room->reset();
		TheGameSpyInfo->leaveStagingRoom();
	}
	m_setup.notifyLeave();
	m_state = 0;
}
