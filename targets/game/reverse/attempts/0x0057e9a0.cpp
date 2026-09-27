// ?d_0057e9a0@@YAXXZ
// partial score=0.305 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /FAsc /Fabuild/Rva0057E9A0.exp11.cod
// The callback identity remains address-derived; its owner layout is witnessed by landed neighbours.

#include "ascii_string.h"
#include "unicode_string.h"

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

class Rva0057E9A0State
{
public:
	virtual void slot00();
	char m_unmodelled[ 0x128 ];
	void dispatch( int message, void *argument, void *data );
};

class SkirmishPreferences
{
public:
	virtual ~SkirmishPreferences();
	virtual void slot1();
	virtual bool load();
	virtual bool write();
	UnicodeString getUserName() throw();
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
extern WindowManager *g_theWindowManager;
extern GameTextInterface *TheGameText;
extern const UnicodeString BFMEUnicodeEmptyString;
extern void GadgetTextEntrySetText( GameWindow *window, UnicodeString text );
extern UnicodeString GadgetComboBoxGetText( GameWindow *window );

struct Rva00579160Current {};
extern Rva00579160Current *Rva00579160TheCurrent;

class Rva0057E9A0Screen : public BfmeMsgHandler
{
public:
	int handleMessage( int message, void *argument, void *data );
	void personaAccept( int value );
	void reloadHonors();

private:
	char m_unmodelled_250[ 0x250 ];
	int m_movie;
	char m_unmodelled_254[ 8 ];
	Rva0057E9A0State m_state;
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
	defaultHandler( message, argument, data );

	if( Rva00579160TheCurrent != 0 )
	{
		m_state.dispatch( message, argument, data );
		switch( message )
		{
		case 0x4025:
		{
			if( argument != m_playerProfile )
				goto success;

			UnicodeString selected = GadgetComboBoxGetText( m_playerProfile );
			if( selected.compare( TheGameText->fetch( "APT:NewProfile" ) ) != 0 )
			{
				m_mode = 2;
				TheWindowManager->winSetFocus( m_createPersonaEntry );
				GadgetTextEntrySetText( m_createPersonaEntry, BFMEUnicodeEmptyString );
				g_theWindowManager->unidentified_00015235(
					m_movie, "PopUpPersona", 0, 0, 0, 0, 0, 0 );
				goto success;
			}

			if( selected.compare( TheGameText->fetch( "APT:DeleteProfile" ) ) != 0 )
			{
				m_mode = 3;
				TheWindowManager->winSetFocus( m_createPersonaEntry );
				g_theWindowManager->unidentified_00015235(
					m_movie, "PopUpRemove", 0, 0, 0, 0, 0, 0 );
				AsciiString name( "APT:RemoveEntryName" );
				g_theWindowManager->bfme_setAptText( name, m_preferences.getUserName() );
			goto success;
			}

			if( selected.compare( m_preferences.getUserName() ) != 0 )
			{
				( (Gen0009FBB0Owner *)&m_preferences )->Rva0009FBB0( selected );
				m_preferences.write();
				reloadHonors();
			}
			goto success;
		}

		case 0x4030:
			if( argument != m_createPersonaEntry )
				return 0;
		{
			if( data == 0 )
				personaAccept( 0 );
			goto success;
		}

		default:
			return 0;
		}
	}

	return 0;

success:
	return 1;
}
