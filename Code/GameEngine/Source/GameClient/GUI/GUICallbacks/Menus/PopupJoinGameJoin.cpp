// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/shims/nat /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad

typedef unsigned short WideChar;
typedef unsigned int size_t;
typedef int Int;

extern "C" size_t __cdecl strlen( const char *s );

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	struct Header
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_text[1];
	};

	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	const char *str() const
	{
		return m_data ? m_data->m_text : (const char *)0x0107388B;
	}
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString( const UnicodeString &other ) : StringBase<WideChar>( other ) {}
	~UnicodeString() {}

	const WideChar *str() const
	{
		char *p = (char *)m_data;
		if ( p )
			p += 8;
		else
			p = (char *)0x0107388C;
		return (const WideChar *)p;
	}
};

// These are the STLport string subobjects in BFME's 0x194-byte PeerRequest.
// Their range assigners are the existing retail ILTs at 0x00004A75 and
// 0x0002B297, respectively.
class StlStr
{
public:
	StlStr &assign( const char *first, const char *last );
	StlStr &operator=( const char *text )
	{
		return assign( text, text + strlen( text ) );
	}
	const char *c_str() const { return m_start; }

private:
	const char *m_start;
	char m_rest[8];
};

class StlWStr
{
public:
	StlWStr &assign( const WideChar *first, const WideChar *last );
	StlWStr &operator=( const WideChar *text )
	{
		int length = 0;
		if ( text[0] )
		{
			do
				++length;
			while ( text[length] );
		}
		return assign( text, text + length );
	}

private:
	char m_bytes[12];
};

class PeerRequest
{
public:
	enum
	{
		PEERREQUEST_JOINSTAGINGROOM = 0x0B
	};

	PeerRequest();
	~PeerRequest();

	int peerRequestType;
	StlStr nick;
	StlWStr text;
	StlStr password;
	char m_mid28[0x4C - 0x28];
	StlStr ladderIP;
	StlStr hostPingStr;
	char m_mid64[0xE4 - 0x64];
	union
	{
		struct { Int id; } stagingRoom;
		unsigned char raw[0x19];
	};
	// The union's 25 meaningful bytes are naturally rounded to 0x1C; BFME's
	// final three padding bytes therefore put the tail at +0x100.
	char m_tail[0x194 - 0x100];
};

typedef char PeerRequestSizeCheck[sizeof(PeerRequest) == 0x194 ? 1 : -1];

class GameSpyStagingRoom
{
public:
	// This is the BFME non-const accessor.  The canonical symbol is the ILT at
	// 0x0002C7B4, whose body copies the UnicodeString at this+0x418.
	UnicodeString getGameName();

	Int getID() const
	{
		return *(const Int *)((const unsigned char *)this + 0x41C);
	}

private:
	unsigned char m_head[0x418];
	UnicodeString m_gameName;
};

#define GSI_SLOT(n) virtual void gsiSlot##n() = 0
class GameSpyInfo
{
public:
	GSI_SLOT(0);  GSI_SLOT(1);  GSI_SLOT(2);  GSI_SLOT(3);
	GSI_SLOT(4);  GSI_SLOT(5);  GSI_SLOT(6);  GSI_SLOT(7);
	GSI_SLOT(8);  GSI_SLOT(9);
	GSI_SLOT(10); GSI_SLOT(11); GSI_SLOT(12); GSI_SLOT(13);
	GSI_SLOT(14); GSI_SLOT(15); GSI_SLOT(16); GSI_SLOT(17);
	GSI_SLOT(18); GSI_SLOT(19); GSI_SLOT(20); GSI_SLOT(21);
	GSI_SLOT(22); GSI_SLOT(23); GSI_SLOT(24); GSI_SLOT(25);
	GSI_SLOT(26); GSI_SLOT(27); GSI_SLOT(28); GSI_SLOT(29);
	GSI_SLOT(30); GSI_SLOT(31); GSI_SLOT(32); GSI_SLOT(33);
	GSI_SLOT(34); GSI_SLOT(35); GSI_SLOT(36); GSI_SLOT(37);
	GSI_SLOT(38);
	virtual GameSpyStagingRoom *findStagingRoomByID( Int id ) = 0;
	GSI_SLOT(40); GSI_SLOT(41); GSI_SLOT(42); GSI_SLOT(43);
	GSI_SLOT(44); GSI_SLOT(45); GSI_SLOT(46); GSI_SLOT(47);
	GSI_SLOT(48); GSI_SLOT(49); GSI_SLOT(50); GSI_SLOT(51);
	virtual Int getCurrentStagingRoomID( void ) = 0;
};
#undef GSI_SLOT

inline GameSpyInfo *gameSpyReceiver(GameSpyInfo *p) { return p; }

extern GameSpyInfo *TheGameSpyInfo;

class GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueueInterface() {}
	virtual void startThread() = 0;
	virtual void endThread() = 0;
	virtual int isThreadRunning() = 0;
	virtual int isConnected() = 0;
	virtual int isConnecting() = 0;
	virtual void addRequest( const PeerRequest &request ) = 0;
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

class GameWindow;
namespace PopupJoinGameState { extern GameWindow *parentPopup; }
using namespace PopupJoinGameState;

enum GSOverlayType
{
	GSOVERLAY_GAMEPASSWORD = 5
};

void GameSpyCloseOverlay( GSOverlayType );
void SetLobbyAttemptHostJoin( bool );

// ?joinGame@@YAXVAsciiString@@@Z
void joinGame( AsciiString password )
{
	GameSpyStagingRoom *ourRoom = TheGameSpyInfo->findStagingRoomByID(
        gameSpyReceiver(TheGameSpyInfo)->getCurrentStagingRoomID());
	if ( !ourRoom )
	{
		GameSpyCloseOverlay( GSOVERLAY_GAMEPASSWORD );
		SetLobbyAttemptHostJoin( false );
		parentPopup = 0;
		return;
	}

	PeerRequest req;
	req.peerRequestType = PeerRequest::PEERREQUEST_JOINSTAGINGROOM;
	req.text = ourRoom->getGameName().str();
	req.stagingRoom.id = ourRoom->getID();
	req.password = password.str();
	TheGameSpyPeerMessageQueue->addRequest( req );
	GameSpyCloseOverlay( GSOVERLAY_GAMEPASSWORD );
	parentPopup = 0;
}

