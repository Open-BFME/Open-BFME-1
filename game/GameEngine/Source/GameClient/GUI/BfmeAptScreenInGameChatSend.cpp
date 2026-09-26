// cl: /DNDEBUG /MD /EHsc
//
// BfmeAptScreenInGameChat::_bfme_send, retail 0x00514000, 778 bytes. The Apt
// selector table registers this body under "AptInGameChat::Send", which is
// what names it.
//
// The button reads the chat entry at this+0x260, clears it, and drops the line
// when it trims to nothing. Otherwise it walks the eight game slots, turns each
// slot's key string at +0x2c into a Player, and builds the recipient mask the
// way Zero Hour's InGameChat.cpp does. The three chat modes at this+0x25c pick
// APT:TeamChat, APT:GlobalChat and APT:SelfChat, and mode 3 hands the whole
// call to the body at 0x00513E70 instead.

typedef bool Bool;
typedef int Int;
typedef unsigned short WideChar;

class GameWindow;
class GameSlot;
class Team;

extern char Rva006A16B0Empty[];
extern const char g_bfmeEmptyUnicode[];

class UnicodeString;
class AsciiString;

template <typename T>
class StringBase
{
	friend class UnicodeString;
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

public:
	void set( const StringBase<T> &other );
	void trim();

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[ 1 ];
	};

	Header *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() {}
	UnicodeString( const WideChar *text )
		: StringBase<unsigned short>( text ) {}
	UnicodeString( const UnicodeString &other )
		: StringBase<unsigned short>( other ) {}
	~UnicodeString() {}

	static UnicodeString TheEmptyString;

	void __cdecl format( UnicodeString fmt, ... );

	void set( const UnicodeString &other )
	{
		StringBase<unsigned short>::set( other );
	}

	void trim()
	{
		StringBase<unsigned short>::trim();
	}

	Bool isEmpty() const
	{
		return !m_data || m_data->length == 0;
	}

	const WideChar *str() const
	{
		return m_data ? &m_data->data[ 0 ]
		              : reinterpret_cast<const WideChar *>( g_bfmeEmptyUnicode );
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() {}
	~AsciiString() {}

	void set( const AsciiString &other )
	{
		StringBase<char>::set( other );
	}

	const char *str() const
	{
		return m_data ? &m_data->data[ 0 ] : Rva006A16B0Empty;
	}
};

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09();
	virtual UnicodeString fetch( const char *label, bool *exists );
};

extern GameTextInterface *TheGameText;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetworkInterface.h
class NetworkInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void sendChat( UnicodeString text, Int playerMask );
	virtual void sendDisconnectChat( UnicodeString text );
};

extern NetworkInterface *TheNetwork;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LanguageFilter.h
class LanguageFilter
{
public:
	void filterLine( UnicodeString &line );
};

extern LanguageFilter *TheLanguageFilter;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

extern NameKeyGenerator *TheNameKeyGenerator;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Relationship getRelationship( const Team *that ) const;

	const Team *getDefaultTeam() const { return m_defaultTeam; }

private:
	unsigned char m_unmodelled000[ 0x230 ];
	Team *m_defaultTeam;
};

class PlayerList
{
public:
	Player *findPlayerWithNameKey( NameKeyType key );

	unsigned char m_unmodelled000[ 0xc ];
	Player *m_local;
};

// The ledger types the player-list global's pointee Rva002EE330PlayerList, so
// the pointee keeps that spelling and inherits the methods under their names.
class Rva002EE330PlayerList : public PlayerList {};
extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	GameSlot *getSlot( Int index );
	const GameSlot *getConstSlot( Int index ) const;
};

extern GameInfo *TheGameInfo;

// 84DB routes to the mode-3 handler at 0x00513E70, which takes the gadget name
// and cleans its own argument.
extern void j_000084db();

class BfmeAptScreenInGameChat
{
public:
	void _bfme_send( const char *name );

private:
	unsigned char m_unmodelled000[ 0x258 ];
	Int m_rva0258;
	// The three GameText labels below are selected by this field, so it holds
	// the chat mode.
	Int m_chatMode;
	// named by game/GameEngine/Source/GameClient/GUI/BfmeAptScreenInGameChatInitGadgets.cpp
	GameWindow *m_chatEntry;
};

UnicodeString GadgetTextEntryGetText( GameWindow *textEntry );
void GadgetTextEntrySetText( GameWindow *textEntry, UnicodeString text );

// @?_bfme_send@BfmeAptScreenInGameChat@@QAEXPBD@Z 0x00514000
void BfmeAptScreenInGameChat::_bfme_send( const char *name )
{
	if( m_rva0258 != 1 )
		return;

	if( m_chatMode == 3 )
	{
		( (void( __stdcall * )( const char * ))j_000084db )( name );
		return;
	}

	UnicodeString msg;
	msg.set( GadgetTextEntryGetText( m_chatEntry ) );
	GadgetTextEntrySetText( m_chatEntry, UnicodeString::TheEmptyString );
	msg.trim();
	// playerMask is declared here and cleared inside the branch on purpose.
	// Retail keeps the mask in the stack slot the dead name argument left
	// behind. Declaring it inside the branch lets MSVC 7.1 keep it in EBX
	// instead, which costs the saved register and 21 bytes.
	Int playerMask;

	if( !msg.isEmpty() )
	{
		const Player *localPlayer = Rva002EE330ThePlayers->m_local;
		AsciiString playerName;
		playerMask = 0;
		UnicodeString chatText( L"Unknown" );

		for( Int i = 0; i < 8; ++i )
		{
			// The slot's key string sits at GameSlot+0x2c. The cast keeps the
			// field unnamed, because the witnessed layout calls that offset
			// m_IP and this body proves it holds a StringBase<char>.
			playerName.set(
				*(const AsciiString *)( (const char *)TheGameInfo->getSlot( i ) + 0x2c ) );

			const Player *player = Rva002EE330ThePlayers->findPlayerWithNameKey(
				TheNameKeyGenerator->nameToKey( playerName.str() ) );

			if( player && localPlayer )
			{
				switch( m_chatMode )
				{
					case 0:
						if( ( player->getRelationship( localPlayer->getDefaultTeam() ) == ALLIES &&
							localPlayer->getRelationship( player->getDefaultTeam() ) == ALLIES ) ||
							player == localPlayer )
							playerMask |= 1 << i;
						chatText.format( TheGameText->fetch( "APT:TeamChat", 0 ), msg.str() );
						break;

					case 1:
						// GameSlot+0xa is the muted flag.
						if( !*( (const char *)TheGameInfo->getConstSlot( i ) + 0xa ) )
							playerMask |= 1 << i;
						chatText.format( TheGameText->fetch( "APT:GlobalChat", 0 ), msg.str() );
						break;

					case 2:
						if( player == localPlayer )
							playerMask |= 1 << i;
						chatText.format( TheGameText->fetch( "APT:SelfChat", 0 ), msg.str() );
						break;
				}
			}
		}

		TheLanguageFilter->filterLine( chatText );
		TheNetwork->sendChat( chatText, playerMask );
	}

	m_rva0258 = 2;
}
