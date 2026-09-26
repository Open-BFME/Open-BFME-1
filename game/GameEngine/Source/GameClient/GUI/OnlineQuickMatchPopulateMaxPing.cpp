// ?rva00558A30Ready@BfmeAptScreenOnlineQuickMatch@@QAE_NXZ
// BFME APT OnlineQuickMatch max-ping combo population helper, retail
// 0x00558A30, 335 bytes. The matched update caller establishes the owner and
// bool/no-argument ABI; the BFME-only split-helper method name remains unknown.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /FAsc /Fabuild/online_quick_match.cod
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
extern int GadgetComboBoxAddEntry(
	GameWindow *comboBox, UnicodeString text, int color );


extern void GadgetComboBoxReset( GameWindow *comboBox );
extern void GadgetComboBoxSetSelectedPos(
	GameWindow *comboBox, int selected, bool dontHide );

#pragma comment(linker, "/alternatename:?GadgetComboBoxAddEntryPopulateRemoteIPComboBox@@YAHPAVGameWindow@@VPopulateRemoteIPComboBoxEntry@@H@Z=?j_0002f338@@YAXXZ")
#pragma comment(linker, "/alternatename:?GadgetComboBoxAddEntry@@YAHPAVGameWindow@@VUnicodeString@@H@Z=?j_0002f338@@YAXXZ")

class QuickMatchPreferences
{
public:
	virtual ~QuickMatchPreferences();
	int getMaxPing();

private:
	unsigned char m_unmodelled[ 0x24 ];
};

#pragma comment(linker, "/alternatename:?getMaxPing@QuickMatchPreferences@@QAEHXZ=?j_00038a0f@@YAXXZ")

struct BfmeQuickMatchObjectView
{
	unsigned char m_beforePreferences[ 0x40 ];
	QuickMatchPreferences m_preferences;
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
	unsigned char m_beforePreferences[ 0x40 ];
	QuickMatchPreferences m_preferences;
	GameWindow *m_maxPing;
	bool m_ready;
	bool m_startRequested;
};

bool BfmeAptScreenOnlineQuickMatch::rva00558A30Ready()
{
	Color color;
	BfmeAptScreenOnlineQuickMatch &view = *this;
	int maxPingEntries;
	if ( view.m_maxPing == 0 )
		return false;

	color = GameSpyColor[ 0 ];
	UnicodeString text;
	GadgetComboBoxReset( view.m_maxPing );

	maxPingEntries =
		(TheGameSpyConfig->getPingTimeoutInMs() - 1) / 100;
	maxPingEntries++;
	s_bfmeMaxPingEntries = maxPingEntries;
	if ( maxPingEntries > 1 )
	{
		int ping = 100;
		register int remaining = maxPingEntries - 1;
		do
		{
			text.format(
				TheGameText->fetch( "GUI:TimeInMilliseconds" ), ping );
			GadgetComboBoxAddEntryPopulateRemoteIPComboBox(
				view.m_maxPing, text, color );
			ping += 100;
		} while ( --remaining != 0 );
	}

	GadgetComboBoxAddEntry(
		view.m_maxPing, TheGameText->fetch( "GUI:ANY" ), color );

	int selected = view.m_preferences.getMaxPing();
	if ( selected < 0 || selected >= maxPingEntries )
		selected = maxPingEntries - 1;
	GadgetComboBoxSetSelectedPos(
		view.m_maxPing, selected, false );

	return true;
}
