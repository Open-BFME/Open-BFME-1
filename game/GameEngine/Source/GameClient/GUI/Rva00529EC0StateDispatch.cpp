// cl: /O2 /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail RVA 0x00529EC0, 843 bytes: the window-message handler of the
// skirmish/multiplayer game-setup state that Rva0057E9A0Screen embeds at +0x25C
// (SkirmishProfileMessage0057E9A0.cpp calls it through ILT 0x00041EE3).
// Zero Hour twin: SkirmishGameOptionsMenuSystem (SkirmishGameOptionsMenu.cpp),
// ported onto the state object: the UnicodeString txtInput local, the
// create/destroy/input-focus arms, the combo-selection slot loop and the
// map start-position button logic follow it line for line. BFME compares the
// window pointers directly and calls the state's own helpers; the method
// keeps its address-derived name.

#include "ascii_string.h"
#include "unicode_string.h"

inline UnicodeString::UnicodeString()
{
	m_text = 0;
}

inline UnicodeString::~UnicodeString()
{
	( (StringBase<unsigned short> *)this )->releaseBuffer();
}

class GameWindow;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	bool isAI( void ) const;
	int getStartPos( void ) const { return m_startPos; }

private:
	unsigned char m_unmodelled[ 0x10 ];
	int m_startPos;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	virtual void bfmeSlot0( void ) = 0;
	virtual void bfmeSlot1( void ) = 0;
	virtual void bfmeSlot2( void ) = 0;
	virtual void bfmeSlot3( void ) = 0;
	virtual bool amIHost( void ) const = 0;
	virtual int getLocalSlotNum( void ) const = 0;

	GameSlot *getSlot( int index );
};

// upstream: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
class UserPreferences
{
public:
	virtual ~UserPreferences();
	virtual void bfmeSlot1( void );
	virtual bool load( AsciiString fname );
	virtual bool write( void );

	void setBool( AsciiString key, bool val );
};

class Rva00529EC0Owner
{
public:
	virtual void bfmeSlot0( void ) = 0;
	virtual UserPreferences *bfmeSlot1( void ) = 0;
	virtual void bfmeSlot2( void ) = 0;
	virtual void bfmeSlot3( void ) = 0;
	virtual void bfmeSlot4( void ) = 0;
	virtual void bfmeSlot5( void ) = 0;
	virtual void bfmeSlot6( void ) = 0;
	virtual void bfmeSlot7( void ) = 0;
	virtual void bfmeSlot8( void ) = 0;
	virtual bool bfmeContains( GameInfo *game ) = 0;
};

// Map preview member at +0x28: find() maps a start-position button to its index.
class Rva00520490
{
public:
	int find( int window );

private:
	unsigned char m_unmodelled[ 0x40 ];
};

class MpGameSetup
{
public:
	int findRepresentativeSlot( void );
	int getNextSelectablePlayer( int firstIndex );
	bool handleStartPositionSelection( int index, int startPosition );
	bool handlePlayerTemplateSelection( int index );
	bool handleTeamSelection( int index );
	bool rva00525D10( int index );
	void bfmeSetMap( const AsciiString &mapName );
};

class SkirmishScreenState
{
public:
	bool handlePlayerSelection( int index );
};

int bfmeGo1022L( int window );

extern const AsciiString Rva01336E50EmptyString;

// 0x4025 is the ZH GCM_SELECTED arm (combo slot loop), 0x4008 the GBM_SELECTED
// start-position button arm, 0x4014 the map list selection (mData2 = row).
// BFME renumbered the gadget messages, so they keep their values as names.
enum
{
	GWM_CREATE = 1,
	GWM_DESTROY = 2,
	GWM_INPUT_FOCUS = 0x17,
	BFME_MSG_4008 = 0x4008,
	BFME_MSG_4014 = 0x4014,
	BFME_MSG_4025 = 0x4025
};

class Rva00529EC0State
{
public:
	int dispatch( int message, void *argument, void *data );

private:
	unsigned char m_vtable[ 4 ];
	Rva00529EC0Owner *m_owner;
	GameInfo *m_first;
	GameInfo *m_second;
	bool m_flag10;
	bool m_flag11;
	unsigned char m_unmodelled12[ 4 ];
	bool m_flag16;
	unsigned char m_unmodelled17[ 0x11 ];
	Rva00520490 m_member28;
	GameWindow *m_playerTypeCombos[ 8 ];
	GameWindow *m_window88[ 8 ];
	GameWindow *m_teamCombos[ 8 ];
	GameWindow *m_playerTemplateCombos[ 8 ];
	GameWindow *m_windowE8[ 8 ];
	GameWindow *m_window108;
	AsciiString *m_value10c;
	AsciiString *m_value110;
	AsciiString *m_value114;
	GameWindow *m_window118;
	GameWindow *m_window11C;
};

// ?dispatch@Rva00529EC0State@@QAEHHPAX0@Z
int Rva00529EC0State::dispatch( int message, void *argument, void *data )
{
	if( m_first && !m_owner->bfmeContains( m_first ) )
		m_first = 0;

	if( m_second && !m_owner->bfmeContains( m_second ) )
		m_second = 0;

	if( !m_first )
		return 0;

	if( m_flag16 )
		return 1;

	UnicodeString txtInput;
	switch( (unsigned int)message )
	{
		case GWM_CREATE:
			break;

		case GWM_DESTROY:
			break;

		case GWM_INPUT_FOCUS:
			if( (int)argument == 1 )
				*(bool *)data = true;
			break;

		case BFME_MSG_4025:
		{
			GameWindow *control = (GameWindow *)argument;
			for( int i = 0; i < 8; ++i )
			{
				if( control == m_window88[ i ] )
				{
					( (MpGameSetup *)this )->rva00525D10( i );
					m_flag10 = true;
					break;
				}
				else if( control == m_playerTemplateCombos[ i ] )
				{
					( (MpGameSetup *)this )->handlePlayerTemplateSelection( i );
					m_flag10 = true;
					break;
				}
				else if( control == m_teamCombos[ i ] )
				{
					( (MpGameSetup *)this )->handleTeamSelection( i );
					m_flag10 = true;
					break;
				}
				else if( control == m_playerTypeCombos[ i ] && m_first->amIHost() )
				{
					( (SkirmishScreenState *)this )->handlePlayerSelection( i );
					m_flag10 = true;
					break;
				}
				else if( control == m_window118 )
				{
					m_owner->bfmeSlot1()->setBool( "UseSystemMapDir", bfmeGo1022L( (int)m_window118 ) == 0 );
					m_owner->bfmeSlot1()->write();
					m_flag11 = true;
					m_flag10 = true;
					break;
				}
				else if( control == m_window11C )
				{
					m_owner->bfmeSlot1()->setBool( "UseScenarioMaps", false );
					m_owner->bfmeSlot1()->write();
					m_flag11 = true;
					m_flag10 = true;
					break;
				}
			}
			break;
		}

		case BFME_MSG_4008:
		{
			int pos = m_member28.find( (int)argument );
			if( pos < 0 )
				break;

			int playerIdxInPos = -1;
			for( int j = 0; j < 8; ++j )
			{
				GameSlot *slot = m_first->getSlot( j );
				if( slot && slot->getStartPos() == pos )
				{
					playerIdxInPos = j;
					break;
				}
			}

			if( playerIdxInPos >= 0 )
			{
				GameSlot *slot = m_first->getSlot( playerIdxInPos );
				if( playerIdxInPos == m_first->getLocalSlotNum() || ( m_first->amIHost() && slot && slot->isAI() ) )
				{
					int nextPlayer = ( (MpGameSetup *)this )->getNextSelectablePlayer( playerIdxInPos + 1 );
					( (MpGameSetup *)this )->handleStartPositionSelection( playerIdxInPos, -1 );
					if( nextPlayer >= 0 )
						( (MpGameSetup *)this )->handleStartPositionSelection( nextPlayer, pos );
				}
			}
			else
			{
				int nextPlayer = ( (MpGameSetup *)this )->getNextSelectablePlayer( 0 );
				if( nextPlayer < 0 )
					nextPlayer = ( (MpGameSetup *)this )->findRepresentativeSlot();
				( (MpGameSetup *)this )->handleStartPositionSelection( nextPlayer, pos );
			}
			break;
		}

		case BFME_MSG_4014:
		{
			if( (GameWindow *)argument == m_window108 )
			{
				int selected = (int)data;
				if( selected < 0 )
				{
					( (MpGameSetup *)this )->bfmeSetMap( Rva01336E50EmptyString );
				}
				else
				{
					// Reading the array base into a local first is what gives
					// retail's ecx index / eax base register assignment.
					const AsciiString *names = m_value10c;
					AsciiString mapName = names[ selected ];
					( (MpGameSetup *)this )->bfmeSetMap( mapName );
				}
			}
			break;
		}

		default:
			return 0;
	}

	return 1;
}
