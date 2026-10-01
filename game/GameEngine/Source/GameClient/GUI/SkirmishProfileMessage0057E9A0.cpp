// ?handleMessage@Rva0057E9A0Screen@@QAEHHPAX0@Z
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail RVA 0x0057E9A0, 674 bytes. Message handling for the skirmish
// profile UI; the method spelling remains address-derived. Storage offsets
// agree with the matched AptSkirmishConstructor.cpp, PersonaAccept.cpp and
// SkirmishScreenReloadHonors.cpp: preferences +3AC, mode +400 and entry +42C.
// Started from the preferred 674-byte bank (24 differing bytes). Native
// entry accessors plus local copies of each movie argument restore allocation.
// The nested state dispatch target is independently decoded through ILT41EE3
// to RVA529EC0; its body preserves ECX as receiver and ends in RET12.

#include "ascii_string.h"
#include "unicode_string.h"

template<> int StringBase<unsigned short>::compare( const StringBase<unsigned short> &str ) const throw();

inline UnicodeString::UnicodeString( const UnicodeString &value )
{
	( (StringBase<unsigned short> *)this )->StringBase<unsigned short>::StringBase(
		*(const StringBase<unsigned short> *)&value );
}

inline UnicodeString::~UnicodeString()
{
	( (StringBase<unsigned short> *)this )->releaseBuffer();
}

class BfmeMsgHandler
{
public:
	int defaultHandler( int message, void *argument, void *data );
};

class Rva00529EC0State
{
public:
	virtual void slot00();
	char m_unmodelled[ 0x128 ];
	int dispatch( int message, void *argument, void *data );
};

class SkirmishPreferences
{
public:
	virtual ~SkirmishPreferences();
	virtual void slot1();
	virtual bool load();
	virtual bool write();
	UnicodeString getUserName();
	char m_unmodelled[ 0x14 ];
};

class Gen0009FBB0Owner
{
public:
	void Rva0009FBB0( UnicodeString value );
};

class SkirmishBattleHonors
{
public:
	virtual ~SkirmishBattleHonors();
	virtual void slot1();
	virtual bool load();
	virtual bool write();
	char m_unmodelled[ 0x38 ];
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

class WindowManager
{
public:
	void unidentified_00015235( int movie, const char *function,
		int argumentCount, const void *argument1,
		int unused1, int unused2, int unused3, int unused4 );
	void bfme_setAptText( const AsciiString &name, const UnicodeString &text );
};

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09();
	virtual UnicodeString fetch( const char *label, bool *exists = 0 );
};

extern GameWindowManager *TheWindowManager;
extern WindowManager *g_rva012F19E8WindowManager;	///< retail [0x012F19E8]
extern GameTextInterface *TheGameText;
extern const UnicodeString BFMEEmptyPlayerName;
extern void GadgetTextEntrySetText( GameWindow *window, UnicodeString text );
extern UnicodeString GadgetComboBoxGetText( GameWindow *window );

struct Rva00579160Current {};
extern Rva00579160Current *Rva00579160TheCurrent;

class BfmeAptScreenSkirmish { public: void personaAccept(int); void reloadHonors(); };

class Rva0057E9A0Screen : public BfmeMsgHandler
{
public:
	int handleMessage( int message, void *argument, void *data );
 GameWindow* createPersonaEntry() const { return m_createPersonaEntry; }

private:
	char m_unmodelled_250[ 0x250 ];
	int m_movie;
	char m_unmodelled_254[ 8 ];
	Rva00529EC0State m_state;
	char m_unmodelled_388[ 8 ];
	char m_unmodelled_390[ 0x1c ];
	SkirmishPreferences m_preferences;
	SkirmishBattleHonors m_honors;
	int m_mode;
	int m_previousMode;
	unsigned char m_unmodelled_408;
	bool m_profileOpen;
	char m_unmodelled_40a[ 2 ];
	char m_unmodelled_40c[ 0x14 ];
	GameWindow *m_playerProfile;
	char m_unmodelled_424[ 8 ];
	GameWindow *m_createPersonaEntry;
};

// ?handleMessage@Rva0057E9A0Screen@@QAEHHPAX0@Z
int Rva0057E9A0Screen::handleMessage( int message, void *argument, void *data )
{
	int result = defaultHandler( message, argument, data );

	if( Rva00579160TheCurrent != 0 )
		result = m_state.dispatch( message, argument, data );

	switch( message )
	{
	case 0x4025:
		if( argument == m_playerProfile )
		{
			UnicodeString selected = GadgetComboBoxGetText( m_playerProfile );
			if( selected.compare( TheGameText->fetch( "APT:NewProfile" ) ) == 0 )
			{
				m_mode = 2;
				TheWindowManager->winSetFocus( createPersonaEntry() );
				GadgetTextEntrySetText( createPersonaEntry(), BFMEEmptyPlayerName );
				int movie = m_movie;
				g_rva012F19E8WindowManager->unidentified_00015235(
					movie, "PopUpPersona", 0, 0, 0, 0, 0, 0 );
				break;
			}
			if( selected.compare( TheGameText->fetch( "APT:DeleteProfile" ) ) == 0 )
			{
				m_mode = 3;
				GameWindow* entry = m_createPersonaEntry;
				TheWindowManager->winSetFocus( entry );
				int movie = m_movie;
				g_rva012F19E8WindowManager->unidentified_00015235(
					movie, "PopUpRemove", 0, 0, 0, 0, 0, 0 );
				AsciiString name( "APT:RemoveEntryName" );
				g_rva012F19E8WindowManager->bfme_setAptText( name, m_preferences.getUserName() );
				break;
			}
			if( selected.compare( m_preferences.getUserName() ) != 0 )
			{
				( (Gen0009FBB0Owner *)&m_preferences )->Rva0009FBB0( selected );
				m_preferences.write();
				((BfmeAptScreenSkirmish*)this)->reloadHonors();
				break;
			}
		}
		break;

	case 0x4030:
		if( argument == m_createPersonaEntry )
		{
			if( data == 0 )
				((BfmeAptScreenSkirmish*)this)->personaAccept( 0 );
			break;
		}
		return 0;

	default:
		return result;
	}

	return 1;
}
