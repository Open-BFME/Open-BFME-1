// cl: /O2 /DNDEBUG /MD /EHsc

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
};

class GameWindow;

void GadgetComboBoxGetSelectedPos( GameWindow *window, int *selected );
void *GadgetComboBoxGetItemData( GameWindow *window, int selected );
UnicodeString GadgetComboBoxGetText( GameWindow *window );

enum SlotState
{
	SLOT_OPEN,
	SLOT_CLOSED,
	SLOT_EASY_AI,
	SLOT_MED_AI,
	SLOT_BRUTAL_AI,
	SLOT_PLAYER
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	virtual void reset( void );
	bool isAI( void ) const;

	SlotState m_state;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	virtual void slot0( void ) = 0;
	virtual void slot1( void ) = 0;
	virtual void slot2( void ) = 0;
	virtual void slot3( void ) = 0;
	virtual bool amIHost( void ) const = 0;
	virtual int getLocalSlotNum( void ) const = 0;

	GameSlot *getSlot( int index );
};

class SkirmishScreenOwner
{
public:
	virtual void slot0( void ) = 0;
	virtual void slot1( void ) = 0;
	virtual void slot2( void ) = 0;
	virtual void slot3( void ) = 0;
	virtual void slot4( void ) = 0;
	virtual void slot5( void ) = 0;
	virtual bool setPlayerState( GameSlot *slot, SlotState state,
		const UnicodeString &name ) = 0;
	virtual void slot7( void ) = 0;
	virtual void slot8( void ) = 0;
	virtual bool contains( GameInfo *game ) = 0;
};

class SkirmishScreenState
{
public:
	bool handlePlayerSelection( int index );
	void refreshPlayerControls( int index );

private:
	unsigned char m_vtable[ 4 ];
	SkirmishScreenOwner *m_owner;
	GameInfo *m_game;
	GameInfo *m_secondaryGame;
	bool m_dirty;
	unsigned char m_flags11[ 6 ];
	bool m_refreshingPlayerControls;
	unsigned char m_unmodelled18[ 0x50 ];
	GameWindow *m_playerTypeCombos[ 8 ];
};

// Apply a host-selected player type, and rebuild that row when it crosses the
// human/AI boundary because the dependent controls have different choices.
// ?handlePlayerSelection@SkirmishScreenState@@QAE_NH@Z
bool SkirmishScreenState::handlePlayerSelection( int index )
{
	if( m_game && !m_owner->contains( m_game ) )
		m_game = 0;

	if( m_secondaryGame && !m_owner->contains( m_secondaryGame ) )
		m_secondaryGame = 0;

	if( !m_game )
		return false;

	m_refreshingPlayerControls = false;
	if( index == m_game->getLocalSlotNum() )
		return false;

	GameWindow *combo = m_playerTypeCombos[ index ];
	int selected;
	GadgetComboBoxGetSelectedPos( combo, &selected );
	if( selected < 0 )
		return false;

	GameSlot *slot = m_game->getSlot( index );
	if( !slot )
		return false;

	SlotState state = (SlotState)(int)GadgetComboBoxGetItemData( combo, selected );
	if( state == slot->m_state || state == SLOT_PLAYER )
		return false;

	bool wasAI = slot->isAI();
	UnicodeString name = GadgetComboBoxGetText( combo );
	if( m_owner->setPlayerState( slot, state, name ) )
	{
		if( slot->isAI() ^ wasAI )
			refreshPlayerControls( index );
		m_dirty = true;
		return true;
	}

	return false;
}
