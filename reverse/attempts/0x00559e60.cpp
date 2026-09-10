// ?rva00559E60Ready@BfmeAptScreenOnlineQuickMatch@@QAE_NXZ
// partial score=0.55 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Open-BFME: the OnlineQuickMatch APT side-combo population callback at
// retail 0x00559E60 (787 bytes).  This is the side-list sibling of update()
// and uses the embedded preference/gadget layout proven by the neighboring
// OnlineQuickMatch callbacks.

#define _STLP_USE_NEWALLOC 1

#include <algorithm>
#include <list>
#include <set>

typedef int Int;
typedef bool Bool;

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[ 1 ];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	void __cdecl format( AsciiString format, ... );
	const char *str() const
	{
		return m_data ? m_data->m_text : "";
	}
	int compare( const AsciiString &other ) const;
};

inline bool operator<( const AsciiString &left, const AsciiString &right )
{
	return left.compare( right ) < 0;
}

inline bool operator==( const AsciiString &left, const AsciiString &right )
{
	return left.compare( right ) == 0;
}

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const UnicodeString &other )
		: StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
};

class GameTextInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual UnicodeString fetch( const char *label, Bool *exists = 0 ) = 0;
	virtual UnicodeString fetch( AsciiString label, Bool *exists = 0 ) = 0;
};

extern GameTextInterface *TheGameText;

class GameWindow
{
public:
	int winEnable( Bool enable );
};

class PopulateRemoteIPComboBoxEntry : public UnicodeString
{
public:
	PopulateRemoteIPComboBoxEntry( const UnicodeString &source )
		: UnicodeString( source ) {}
};

extern void gadgetComboBoxReset( GameWindow *comboBox );
extern int GadgetComboBoxAddEntryPopulateRemoteIPComboBox(
	GameWindow *comboBox, PopulateRemoteIPComboBoxEntry text, int color );
extern void GadgetComboBoxGetSelectedPos( GameWindow *comboBox, int *selected );
extern void *GadgetComboBoxGetItemData( GameWindow *comboBox, int selected );
extern void GadgetComboBoxSetItemData(
	GameWindow *comboBox, int selected, void *data );
extern void GadgetComboBoxSetSelectedPos(
	GameWindow *comboBox, int selected, Bool dontHide );

class QuickMatchPreferences
{
public:
	virtual ~QuickMatchPreferences();
	int getSide();

private:
	unsigned char m_unmodelled[ 0x10 ];
};

class PlayerTemplate
{
public:
	const AsciiString &getSide() const
	{
		return m_side;
	}

	Bool isPlayableSide() const
	{
		return m_playableSide;
	}

private:
	unsigned char m_beforeSide[ 0x08 ];
	AsciiString m_side;
	unsigned char m_beforePlayableSide[ 0xBD - 0x0C ];
	Bool m_playableSide;
	unsigned char m_afterPlayableSide[ 0x124 - 0xBE ];
};

class PlayerTemplateStore
{
public:
	const PlayerTemplate *getNthPlayerTemplate( Int index ) const;

	Int getPlayerTemplateCount() const
	{
		return (Int)( m_end - m_begin );
	}

private:
	unsigned char m_beforeTemplates[ 0x08 ];
	PlayerTemplate *m_begin;
	PlayerTemplate *m_end;
};

extern PlayerTemplateStore *ThePlayerTemplateStore;

class LadderInfo
{
public:
	UnicodeString name;
	UnicodeString description;
	UnicodeString location;
	Int playersPerTeam;
	Int minWins;
	Int maxWins;
	Bool randomMaps;
	Bool randomFactions;
	Bool validQM;
	Bool validCustom;
	std::list<AsciiString> validMaps;
	std::list<AsciiString> validFactions;
};

class LadderList
{
public:
	const LadderInfo *findLadderByIndex( Int index );
};

extern LadderList *TheLadderList;

class MultiplayerColorDefinition
{
public:
	int getColor() const
	{
		return *(const int *)((const char *)this + 0x10);
	}
};

class MultiplayerSettings
{
public:
	MultiplayerColorDefinition *getColor( Int color );
};

extern MultiplayerSettings *TheMultiplayerSettings;

class BfmeAptScreenOnlineQuickMatch
{
public:
	void update();
	bool rva005588E0Ready();
	bool rva00558A30Ready();
	bool rva00559E60Ready();
	void _bfme_sendStartQuickMatchRequest();

private:
	unsigned char m_beforePreferences[ 0x40 ];
	QuickMatchPreferences m_preferences;
	bool m_ready;
	bool m_startRequested;
	unsigned char m_pad56;
	unsigned char m_pad57;
	int m_flags;
	GameWindow *m_color;
	GameWindow *m_numPlayers;
	GameWindow *m_side;
	GameWindow *m_connectionSpeed;
	GameWindow *m_ladder;
};

void BfmeAptScreenOnlineQuickMatch::update()
{
	if ( !m_ready && rva005588E0Ready() && rva00558A30Ready()
		&& rva00559E60Ready() )
	{
		m_ready = true;
	}

	if ( m_startRequested )
	{
		_bfme_sendStartQuickMatchRequest();
		m_startRequested = false;
	}
}

bool BfmeAptScreenOnlineQuickMatch::rva00559E60Ready()
{
	if ( m_side == 0 )
		return false;

	UnicodeString playerTemplateName;
	int favSide = m_preferences.getSide();
	int selected;
	GadgetComboBoxGetSelectedPos( m_ladder, &selected );
	int ladderID = (int)GadgetComboBoxGetItemData( m_ladder, selected );
	const LadderInfo *li = TheLadderList->findLadderByIndex( ladderID );

	Int numPlayerTemplates = ThePlayerTemplateStore->getPlayerTemplateCount();

	gadgetComboBoxReset( m_side );

	MultiplayerColorDefinition *def = TheMultiplayerSettings->getColor( -1 );
	int newIndex = GadgetComboBoxAddEntryPopulateRemoteIPComboBox(
		m_side, TheGameText->fetch( (const char *)"GUI:Random", (Bool *)0 ),
		def->getColor() );
	GadgetComboBoxSetItemData( m_side, newIndex, (void *)-1 );

	std::set<AsciiString> seenSides;
	Int entryToSelect = 0;

	for ( Int c = 0; c < numPlayerTemplates; ++c )
	{
		const PlayerTemplate *fac =
			ThePlayerTemplateStore->getNthPlayerTemplate( c );
		if ( fac == 0 )
			continue;
		if ( !fac->isPlayableSide() )
			continue;

		AsciiString side;
		side.format( "SIDE:%s", fac->getSide().str() );
		if ( seenSides.find( side ) != seenSides.end() )
			continue;

		if ( li )
		{
			if ( std::find( li->validFactions.begin(), li->validFactions.end(),
				fac->getSide() ) == li->validFactions.end() )
				continue;
		}

		seenSides.insert( side );
		newIndex = GadgetComboBoxAddEntryPopulateRemoteIPComboBox(
			m_side, TheGameText->fetch( side ), def->getColor() );
		GadgetComboBoxSetItemData( m_side, newIndex, (void *)c );
		if ( c == favSide )
			entryToSelect = newIndex;
	}

	seenSides.clear();

	GadgetComboBoxSetSelectedPos( m_side, entryToSelect, false );
	if ( li && li->randomFactions )
		m_side->winEnable( false );
	else
		m_side->winEnable( true );

	return true;
}
