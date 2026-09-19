// ?Rva00524B40Tooltip@@YAXPAVGameWindow@@PAVWinInstanceData@@I@Z
// partial score=0.92 date=2026-09-19
// ?Rva00524B40Tooltip@@YAXPAVGameWindow@@PAVWinInstanceData@@I@Z
// The MpGameSetup player-window tooltip callback is registered by the
// onInitGadget body at 0x00525AB0 through ILT 0x0002D727.

class GameWindow
{
public:
	void *winGetUserData();
};

class WinInstanceData;

class GameSlot;

class GameInfo
{
public:
	GameSlot *getSlot( int index );
};

class MpGameSetupOwner
{
public:
	virtual void slot0( void ) = 0;
	virtual void slot1( void ) = 0;
	virtual void slot2( void ) = 0;
	virtual void slot3( void ) = 0;
	virtual void slot4( void ) = 0;
	virtual void slot5( void ) = 0;
	virtual void slot6( void ) = 0;
	virtual void slot7( void ) = 0;
	virtual void slot8( void ) = 0;
	virtual bool contains( GameInfo *game ) = 0;
	virtual void slot10( void ) = 0;
	virtual void updateSlot( GameSlot *slot ) = 0;
};

class MpGameSetup
{
public:
	unsigned char m_unmodelled_000[ 4 ];
	MpGameSetupOwner *m_owner;
	GameInfo *m_first;
	GameInfo *m_second;
	unsigned char m_unmodelled_010[ 0x58 ];
	GameWindow *m_player[ 8 ];
};

void Rva00524B40Tooltip( GameWindow *window, WinInstanceData *, unsigned int )
{
	if ( *(MpGameSetup **)0x012F49D4 == 0 )
		return;

	int playerIndex = 0;
	int offset = 0x68;
	GameWindow *callback = window;
	do
	{
		void *match = 0;
		if ( callback )
		{
			GameWindow *player = *(GameWindow **)(
				(char *)*(MpGameSetup **)0x012F49D4 + offset);
			void *data = player->winGetUserData();
			if ( data )
				match = *(void **)((char *)data + 0x28);
		}
		if ( callback == match )
			goto cleanup;

		offset += 4;
		++playerIndex;
	}
	while ( offset < 0x88 );
	return;

cleanup:
	if ( playerIndex == -1 )
		return;

	MpGameSetup *setup = *(MpGameSetup **)0x012F49D4;
	if ( setup->m_first && !setup->m_owner->contains( setup->m_first ) )
		setup->m_first = 0;
	if ( setup->m_second && !setup->m_owner->contains( setup->m_second ) )
		setup->m_second = 0;

	if ( setup->m_first )
	{
		GameSlot *slot = setup->m_first->getSlot( playerIndex );
		if ( slot )
			setup->m_owner->updateSlot( slot );
	}
}
