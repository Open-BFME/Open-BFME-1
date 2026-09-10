// ?rva00558A30Ready@BfmeAptScreenOnlineQuickMatch@@QAE_NXZ
// partial score=0.7 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME: the OnlineQuickMatch APT vtable update slot at 0x0055B9A0.

typedef int Color;

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const UnicodeString &other )
		: StringBase<unsigned short>( other ) {}
	~UnicodeString() {}

	void format( UnicodeString format, ... );
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
	virtual void slot24() = 0;
	virtual UnicodeString fetch( const char *label, bool *exists = 0 ) = 0;
};

class GameSpyConfigInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual int getPingTimeoutInMs() = 0;
};

class GameWindow {};

class PopulateRemoteIPComboBoxEntry : public UnicodeString
{
public:
	PopulateRemoteIPComboBoxEntry( const UnicodeString &source )
		: UnicodeString( source ) {}
};

extern GameTextInterface *TheGameText;
extern GameSpyConfigInterface *TheGameSpyConfig;
extern int GameSpyColor[];
extern int GadgetComboBoxAddEntryPopulateRemoteIPComboBox(
	GameWindow *comboBox, PopulateRemoteIPComboBoxEntry text, int color );

extern void rva00558A30Reset( GameWindow *comboBox );
extern void rva00558A30SetSelectedPos(
	GameWindow *comboBox, int selected, bool dontHide );

#pragma comment(linker, "/alternatename:?GadgetComboBoxAddEntryPopulateRemoteIPComboBox@@YAHPAVGameWindow@@VPopulateRemoteIPComboBoxEntry@@H@Z=?j_0002f338@@YAXXZ")

class BfmeQuickMatchPreferencesView
{
public:
	int getMaxPing();

private:
	unsigned char m_unmodelled[ 0x28 ];
};

#pragma comment(linker, "/alternatename:?getMaxPing@BfmeQuickMatchPreferencesView@@QAEHXZ=?j_00038a0f@@YAXXZ")

struct BfmeQuickMatchObjectView
{
	unsigned char m_beforePreferences[ 0x40 ];
	BfmeQuickMatchPreferencesView m_preferences;
	GameWindow *m_maxPing;
};

static int s_bfmeMaxPingEntries = 0;

class BfmeAptScreenOnlineQuickMatch
{
public:
	void update();
	bool rva005588E0Ready();
	bool rva00558A30Ready();
	bool rva00559E60Ready();
	void _bfme_sendStartQuickMatchRequest();


private:
	unsigned char m_unmodelled_000[ 0x54 ];
	bool m_ready;
	bool m_startRequested;
};

bool BfmeAptScreenOnlineQuickMatch::rva00558A30Ready()
{
	BfmeQuickMatchObjectView *view = (BfmeQuickMatchObjectView *)this;
	if ( view->m_maxPing == 0 )
		return false;

	Color color = GameSpyColor[ 0 ];
	UnicodeString text;
	rva00558A30Reset( view->m_maxPing );

	s_bfmeMaxPingEntries =
		(TheGameSpyConfig->getPingTimeoutInMs() - 1) / 100;
	s_bfmeMaxPingEntries++;
	if ( s_bfmeMaxPingEntries > 1 )
	{
		int ping = 100;
		register int remaining = s_bfmeMaxPingEntries - 1;
		do
		{
			text.format(
				TheGameText->fetch( "GUI:TimeInMilliseconds" ), ping );
			GadgetComboBoxAddEntryPopulateRemoteIPComboBox(
				view->m_maxPing, text, color );
			ping += 100;
		} while ( --remaining != 0 );
	}

	GadgetComboBoxAddEntryPopulateRemoteIPComboBox(
		view->m_maxPing, TheGameText->fetch( "GUI:ANY" ), color );

	int selected = view->m_preferences.getMaxPing();
	if ( selected < 0 )
		selected = 0;
	if ( selected >= s_bfmeMaxPingEntries )
		selected = s_bfmeMaxPingEntries - 1;
	rva00558A30SetSelectedPos(
		view->m_maxPing, selected, false );

	return true;
}

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
