// cl: /O2 /DNDEBUG /MD /EHsc

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase( const StringBase<T> &other );
	void releaseBuffer();

	void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString()
	{
		((StringBase<unsigned short> *)this)->releaseBuffer();
	}
};

class GameWindow
{
public:
	void *winGetUserData();
};

class Rva00525080WindowData
{
private:
	unsigned char m_padding[0x2c];

public:
	GameWindow *m_listBox;
};

int GadgetListBoxGetNumEntries( GameWindow *window );
void *GadgetListBoxGetItemData( GameWindow *window, int item, int column );
void GadgetComboBoxSetSelectedPos( GameWindow *window, int item, bool dontHide );
UnicodeString GadgetComboBoxGetText( GameWindow *window );

class GameSlot
{
};

class GameInfo
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual bool amIHost() const = 0;

	GameSlot *getSlot( int index );
};

enum SlotState
{
	SLOT_OPEN,
	SLOT_CLOSED,
	SLOT_EASY_AI,
	SLOT_MED_AI,
	SLOT_BRUTAL_AI,
	SLOT_PLAYER
};

class Rva00525080Owner
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual bool setPlayerState( GameSlot *slot, SlotState state,
		const UnicodeString &name ) = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual bool contains( GameInfo *game ) = 0;
};

class Rva00525080SkirmishScreenState
{
public:
	void rva00525080( int index, int state );

private:
	unsigned char m_vtable[4];
	Rva00525080Owner *m_owner;
	GameInfo *m_game;
	GameInfo *m_secondaryGame;
	unsigned char m_unmodelled10[0x58];
	GameWindow *m_playerTypeCombos[8];
};

// ?rva00525080@Rva00525080SkirmishScreenState@@QAEXHH@Z
void Rva00525080SkirmishScreenState::rva00525080( int index, int state )
{
	if (m_game && !m_owner->contains( m_game ))
		m_game = 0;

	if (m_secondaryGame && !m_owner->contains( m_secondaryGame ))
		m_secondaryGame = 0;

	if (!m_game)
		return;

	GameWindow *combo = m_playerTypeCombos[index];
	if (!combo)
		return;

	Rva00525080WindowData *data =
		(Rva00525080WindowData *)combo->winGetUserData();
	GameWindow *listBox;
	if (data && data->m_listBox)
		listBox = data->m_listBox;
	else
		listBox = 0;
	const int count = GadgetListBoxGetNumEntries( listBox );
	for (int item = 0; item < count; ++item)
	{
		if ((int)GadgetListBoxGetItemData( listBox, item, 0 ) == state)
		{
			GadgetComboBoxSetSelectedPos( combo, item, false );
			if (!m_game->amIHost())
				return;

			if (GameSlot *slot = m_game->getSlot( index ))
			{
				UnicodeString name = GadgetComboBoxGetText( combo );
				m_owner->setPlayerState( slot, (SlotState)state, name );
			}
			else
				return;
			return;
		}
	}
}
