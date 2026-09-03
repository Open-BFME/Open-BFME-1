// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
//
// BfmeAptScreenOnlineCustomMatch staging-list poll, retail 0x00544DD0,
// 84 bytes. Unless force is set, skip when this+0x1C0 is nonzero and
// last+1000 is still ahead of timeGetTime. Otherwise GameSpyInfo vslot
// +0xAC (hasStagingRoomListChanged) gates a thiscall refresh and a
// timestamp store. timeGetTime is the dllimport so the IAT load CSEs
// into EDI for both call sites.

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();

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
	GAMESPY_SLOT( 40 ); GAMESPY_SLOT( 41 ); GAMESPY_SLOT( 42 );
	virtual bool hasStagingRoomListChanged() = 0;
};
#undef GAMESPY_SLOT

extern GameSpyInfo *TheGameSpyInfo;

class BfmeAptScreenOnlineCustomMatch
{
public:
	void refreshStagingRoomList( bool force );
	void applyStagingRoomRefresh();

private:
	unsigned char m_pad[ 0x1C0 ];
	unsigned long m_lastRefresh;
};

void BfmeAptScreenOnlineCustomMatch::refreshStagingRoomList( bool force )
{
	if( !force )
	{
		if( m_lastRefresh )
		{
			unsigned long now = timeGetTime();
			if( m_lastRefresh + 1000 > now )
				return;
		}
	}
	if( TheGameSpyInfo->hasStagingRoomListChanged() )
	{
		applyStagingRoomRefresh();
		m_lastRefresh = timeGetTime();
	}
}
