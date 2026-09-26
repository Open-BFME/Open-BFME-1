// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail RVA 0x005585B0 (372 bytes).
//
// The receiver is the OnlineQuickMatch APT object identified by its
// 0x01108BCC vtable and the matched 0x005587F0 destructor.  This method's
// source-level spelling is not present in the recovered BFME additions, so
// its entry remains address-derived while the class/lifetime and raw ABI are
// proven by the neighbouring methods.  The body saves the five gadget
// selections into a temporary QuickMatchPreferences object.

class AsciiString
{
public:
	static const AsciiString TheEmptyString;
	void *m_data;
};


class UserPreferences
{
public:
	virtual ~UserPreferences();
	virtual bool write();

private:
	unsigned char m_unmodelled[ 0x10 ];
};

class QuickMatchPreferences : public UserPreferences
{
public:
	QuickMatchPreferences();
	virtual ~QuickMatchPreferences();
	void setLastLadder( const AsciiString &address, unsigned short port );
	void setNumPlayers( int value );
	void setMaxPing( int value );
	void setSide( int value );
	void setColor( int value );
};

class LadderInfo
{
private:
	unsigned char m_unmodelled[ 0x28 ];

public:
	AsciiString address;
	unsigned short port;
};

class LadderList
{
public:
	const LadderInfo *findLadderByIndex( int index );
};

extern LadderList *TheLadderList;

class BfmeC1040
{
public:
	int bfmeGo1040C();
};

class GameWindow;
extern void GadgetComboBoxGetSelectedPos( GameWindow *combo, int *selected );
extern void *GadgetComboBoxGetItemData( GameWindow *combo, int selected );

class BfmeAptScreenOnlineQuickMatch
{
public:
	void rva005585B0SaveOptions();

private:
	unsigned char m_unmodelled[ 0x5C ];
	GameWindow *m_color;
	GameWindow *m_numPlayers;
	GameWindow *m_side;
	GameWindow *m_connectionSpeed;
	GameWindow *m_ladder;
};

template <typename T> const T &max( const T &a, const T &b )
{
	if( a > b )
		return a;
	return b;
}

void BfmeAptScreenOnlineQuickMatch::rva005585B0SaveOptions()
{
	QuickMatchPreferences pref;
	int selected;

	GadgetComboBoxGetSelectedPos( m_ladder, &selected );
	int ladderID = (int)GadgetComboBoxGetItemData( m_ladder, selected );
	const LadderInfo *li = TheLadderList->findLadderByIndex( ladderID );
	if( li != 0 )
	{
		pref.setLastLadder(
			li->address, li->port );
		pref.write();
	}
	else
	{
		pref.setLastLadder(
			AsciiString::TheEmptyString, 0 );
		GadgetComboBoxGetSelectedPos( m_numPlayers, &selected );
		if( selected < 0 )
			selected = 0;
	}

	GadgetComboBoxGetSelectedPos( m_numPlayers, &selected );
	pref.setNumPlayers( selected );

	GadgetComboBoxGetSelectedPos( m_connectionSpeed, &selected );
	pref.setMaxPing( selected );

	int item;
	GadgetComboBoxGetSelectedPos( m_side, &selected );
	item = (int)GadgetComboBoxGetItemData( m_side, selected );
	pref.setSide( max( 0, item ) );

	selected = ((BfmeC1040 *)&m_color)->bfmeGo1040C();
	pref.setColor( max( 0, selected ) );
	pref.write();
}
