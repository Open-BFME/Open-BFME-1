// ?personaRemove@BfmeAptScreenSkirmish@@QAEXH@Z
// lane 35 scratch reconstruction of the profile-removal callback.
// Retail 0x0057D350: remove the current profile, select the first remaining
// profile when available, and refresh the honors snapshot.

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const StringBase<T> &other );
	void set( const StringBase<T> &other );
	void trim();
	void releaseBuffer();

public:
	void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString( const UnicodeString &other )
		: StringBase<unsigned short>( other ) {}
	~UnicodeString() { releaseBuffer(); }
	UnicodeString &operator=( const UnicodeString &other )
	{
		set( other );
		return *this;
	}
	void trim() { StringBase<unsigned short>::trim(); }
};

class Rva0009F090WideList
{
public:
	UnicodeString first() const;
};

class Rva005672C0Map
{
public:
	virtual void slot0();
	void *m_head;
	Rva005672C0Map &operator=( const Rva005672C0Map &other );
};

class SkirmishPreferences
{
public:
	virtual ~SkirmishPreferences();
	virtual void slot1();
	virtual bool load();
	virtual bool write();

	bool unidentified_00017AF8();
	UnicodeString getUserName();
	void Rva0009F560( UnicodeString value );

private:
	char m_unmodelled[ 0x14 ];
};

class Gen0009FBB0Owner
{
public:
	void Rva0009FBB0( UnicodeString value );
};

typedef bool (__fastcall *SkirmishPreferencesWriteCall)(
	SkirmishPreferences * );

struct SkirmishBattleHonorsValues
{
	int m_value[ 10 ];
};

class SkirmishBattleHonors
{
public:
	virtual ~SkirmishBattleHonors();
	virtual void slot1();
	virtual bool load();
	virtual bool write();
	SkirmishBattleHonors( UnicodeString userName );

	Rva005672C0Map m_map;
	char m_unmodelled_0c[ 4 ];
	UnicodeString m_userName;
	SkirmishBattleHonorsValues m_values;
};

class SkirmishScreenState
{
public:
	virtual void slot0();
	virtual void reset();

private:
	char m_unmodelled[ 0x130 ];
};

class WindowManager
{
public:
	void unidentified_00015235( int movie, const char *function,
		int argumentCount, const void *argument1, const void *argument2,
		int unused1, int unused2, int unused3 );
};

class GameWindow {};
class GameWindowManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43();
	virtual int winSetFocus( GameWindow *window );
};

extern WindowManager *g_theWindowManager;
extern GameWindowManager *TheWindowManager;
extern UnicodeString g_personaText;
extern void GadgetTextEntrySetText( GameWindow *window, UnicodeString text );

class BfmeAptScreenSkirmish
{
public:
	void personaRemove( int argument );
	void _bfme_refreshProfile();

private:
	char m_unmodelled_250[ 0x250 ];
	int m_movie;
	char m_unmodelled_254[ 8 ];
	SkirmishScreenState m_state;
	char m_unmodelled_390[ 0x1c ];
	SkirmishPreferences m_preferences;
	SkirmishBattleHonors m_honors;
	int m_mode;
	int m_previousMode;
	unsigned char m_unmodelled_408;
	bool m_profileOpen;
	char m_unmodelled_40a[ 0x22 ];
	GameWindow *m_createPersonaEntry;
};

static const char *const kPopUpControl = (const char *)0x0110B2DC;
static const char *const kClose = (const char *)0x0110B2EC;
static const char *const kPersonaAction = (const char *)0x0110B34C;

// ?personaRemove@BfmeAptScreenSkirmish@@QAEXH@Z
void BfmeAptScreenSkirmish::personaRemove( int )
{
	UnicodeString current = m_preferences.getUserName();
	current.trim();
	m_preferences.Rva0009F560( current );

	if( m_preferences.unidentified_00017AF8() )
	{
		current = ( (Rva0009F090WideList *)&m_preferences )->first();
		( (Gen0009FBB0Owner *)&m_preferences )->Rva0009FBB0( current );
		m_preferences.write();

		{
			SkirmishBattleHonors honors( m_preferences.getUserName() );
			Rva005672C0Map *currentMap = &m_honors.m_map;
			const Rva005672C0Map *newMap = &honors.m_map;
			currentMap->operator=( *newMap );
			m_honors.m_userName = honors.m_userName;
			m_honors.m_values = honors.m_values;
		}

		_bfme_refreshProfile();
		m_preferences.write();
		g_theWindowManager->unidentified_00015235(
			m_movie, kPopUpControl, 1, kClose, 0, 0, 0, 0 );
		m_profileOpen = true;
		void **preferencesVtable = *(void ***)&m_preferences;
		( (SkirmishPreferencesWriteCall)preferencesVtable[ 3 ] )(
			&m_preferences );
		m_state.reset();
		m_mode = 5;
	}
	else
	{
		{
			int movie = m_movie;
			g_theWindowManager->unidentified_00015235(
				movie, kPopUpControl, 1, kClose, 0, 0, 0, 0 );
		}
		m_profileOpen = true;
		m_mode = 2;
		GameWindow *focusWindow = m_createPersonaEntry;
		TheWindowManager->winSetFocus( focusWindow );
		GadgetTextEntrySetText( m_createPersonaEntry, g_personaText );
		int finalMovie = m_movie;
		WindowManager *windowManager = g_theWindowManager;
		windowManager->unidentified_00015235(
			finalMovie, kPersonaAction, 0, 0, 0, 0, 0, 0 );
	}
}
