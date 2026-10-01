// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/stringbaseunicode /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// BfmeAptScreenOnlineLogin::_bfme_update, retail 0x00552100 (1969 bytes).
// Identity: vtable 0x01107F58 slot +0x14 of the matched BfmeAptScreenOnlineLogin
// (through ILT 0x0004244C). The body is the Apt-screen port of Zero Hour's
// WOLLoginMenuUpdate (WOLLoginMenu.cpp): the ping response feeds checkLogin, the
// PeerResponse GROUPROOM / LOGIN / DISCONNECT arms follow it statement for
// statement ("TEST" translated room name, "GUI:GSDisconReason%d" /
// "GUI:GSErrorTitle", TearDownGameSpy + SetUpGameSpy with the MOTD and config).
// BFME adds the buddy and persistent-storage response pumps, the Apt
// EnableButton* ActionScript calls, and in the LOGIN arm the Zero Hour locale
// update of WOLLocaleSelectPopup.cpp for a stored locale outside LOC_MIN..LOC_MAX
// (the stats come from the cached KV pairs as in the matched checkLogin).
// Declarations follow the matched siblings OnlineLoginRva00552C40.cpp (string
// model, Apt call) and WOLWelcomeMenuUpdateTwin.cpp (0x330-byte PeerResponse and
// 0x20-byte GameSpyGroupRoom, which this body fills including its tail dword).
#include "ascii_string.h"
#include <wchar.h>
#include <string.h>
#include "Common/UnicodeString.h"
#include <string>
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->releaseBuffer(); }

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum { LOC_MIN = 1, LOC_MAX = 37 };

// upstream: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PingThread.h
class PingResponse
{
public:
	std::string hostname;
	Int avgPing;
	Int repetitions;
};

class PingerInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18();
	virtual Bool getResponse( PingResponse &resp );
};
extern PingerInterface *ThePinger;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerThread.h
// BFME's record is 0x330 bytes; only the accessed members are modelled. The
// union starts at +0xF4 as in Zero Hour; BFME's groupRoom arm carries a sixth
// dword (+0x108) that the room record copies into its own tail.
class PeerResponse
{
public:
	enum
	{
		PEERRESPONSE_LOGIN,
		PEERRESPONSE_DISCONNECT,
		PEERRESPONSE_MESSAGE,
		PEERRESPONSE_GROUPROOM
	};
	PeerResponse();
	~PeerResponse();

	Int peerResponseType;
	std::string groupRoomName;
	std::string nick;
	char m_unmodelled1C[ 0xf4 - 0x1c ];
	union
	{
		struct
		{
			Int reason;
		} discon;
		struct
		{
			Int id;
			Int numWaiting;
			Int maxWaiting;
			Int numGames;
			Int numPlaying;
			Int bfme108;
		} groupRoom;
		struct
		{
			Int profileID;
			Int wins;
			Int losses;
			Int roomType;
			Int flags;
			UnsignedInt IP;
			Int rankPoints;
			Int side;
			Int preorder;
			UnsignedInt internalIP;
			UnsignedInt externalIP;
		} player;
	};
	char m_unmodelled120[ 0x330 - 0x120 ];
};

class GameSpyPeerMessageQueueInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20();
	virtual Bool getResponse( PeerResponse &resp );
};
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerDefs.h
class GameSpyGroupRoom
{
public:
	GameSpyGroupRoom();
	GameSpyGroupRoom( const GameSpyGroupRoom &that );
	~GameSpyGroupRoom();

	AsciiString m_name;
	UnicodeString m_translatedName;
	Int m_groupID;
	Int m_numWaiting;
	Int m_maxWaiting;
	Int m_numGames;
	Int m_numPlaying;
	Int m_bfme1C;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PersistentStorageThread.h
class PSPlayerStats
{
public:
	PSPlayerStats();
	PSPlayerStats( const PSPlayerStats &other );
	~PSPlayerStats();
	PSPlayerStats &operator=( const PSPlayerStats &other );

	Int id;
	char m_unmodelled004[ 0x148 - 0x004 ];
	Int locale;
	char m_unmodelled14C[ 0x1c4 - 0x14c ];
};

class PSRequest
{
public:
	enum
	{
		PSREQUEST_READPLAYERSTATS,
		PSREQUEST_UPDATEPLAYERSTATS,
		PSREQUEST_UPDATEPLAYERLOCALE
	};
	PSRequest();
	~PSRequest();

	Int requestType;
	PSPlayerStats player;
	char m_unmodelled1C8[ 0x1d4 - 0x1c8 ];
	std::string nick;
	std::string password;
	std::string email;
	char m_unmodelled1F8[ 0x210 - 0x1f8 ];
};

class PSResponse
{
public:
	enum
	{
		PSRESPONSE_PLAYERSTATS
	};
	Int responseType;
	PSPlayerStats player;
	Int preorder;
	char m_unmodelled1CC[ 0x1f0 - 0x1cc ];	// BFME record is 0x1F0 bytes (stack spacing here)
};

class GameSpyPSMessageQueueInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void addRequest( const PSRequest &req );
	virtual void slot14();
	virtual void addResponse( const PSResponse &resp );
	virtual void slot1C();
	virtual void trackPlayerStats( PSPlayerStats stats );
	virtual PSPlayerStats findPlayerStatsByID( Int id );

	static PSPlayerStats parsePlayerKVPairs( std::string kvPairs );
};
extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;

#define BFME_GSI_SLOT(n) virtual void slot##n( void )
class GameSpyInfoInterface
{
public:
	BFME_GSI_SLOT(00); BFME_GSI_SLOT(01); BFME_GSI_SLOT(02); BFME_GSI_SLOT(03);
	virtual void addGroupRoom( GameSpyGroupRoom room );
	BFME_GSI_SLOT(05); BFME_GSI_SLOT(06); BFME_GSI_SLOT(07); BFME_GSI_SLOT(08); BFME_GSI_SLOT(09);
	BFME_GSI_SLOT(10); BFME_GSI_SLOT(11); BFME_GSI_SLOT(12); BFME_GSI_SLOT(13); BFME_GSI_SLOT(14);
	BFME_GSI_SLOT(15); BFME_GSI_SLOT(16); BFME_GSI_SLOT(17); BFME_GSI_SLOT(18); BFME_GSI_SLOT(19);
	BFME_GSI_SLOT(20); BFME_GSI_SLOT(21); BFME_GSI_SLOT(22); BFME_GSI_SLOT(23); BFME_GSI_SLOT(24);
	virtual void setLocalName( AsciiString name );
	BFME_GSI_SLOT(26);
	virtual void setLocalProfileID( Int profileID );
	virtual Int getLocalProfileID( void );
	virtual AsciiString getLocalEmail( void );
	BFME_GSI_SLOT(30);
	virtual AsciiString getLocalPassword( void );
	BFME_GSI_SLOT(32); BFME_GSI_SLOT(33);
	virtual AsciiString getLocalBaseName( void );
	virtual void setCachedLocalPlayerStats( PSPlayerStats stats );
	BFME_GSI_SLOT(36); BFME_GSI_SLOT(37); BFME_GSI_SLOT(38); BFME_GSI_SLOT(39);
	BFME_GSI_SLOT(40); BFME_GSI_SLOT(41); BFME_GSI_SLOT(42); BFME_GSI_SLOT(43); BFME_GSI_SLOT(44);
	BFME_GSI_SLOT(45); BFME_GSI_SLOT(46); BFME_GSI_SLOT(47); BFME_GSI_SLOT(48); BFME_GSI_SLOT(49);
	BFME_GSI_SLOT(50); BFME_GSI_SLOT(51); BFME_GSI_SLOT(52); BFME_GSI_SLOT(53); BFME_GSI_SLOT(54);
	BFME_GSI_SLOT(55); BFME_GSI_SLOT(56); BFME_GSI_SLOT(57); BFME_GSI_SLOT(58); BFME_GSI_SLOT(59);
	BFME_GSI_SLOT(60); BFME_GSI_SLOT(61); BFME_GSI_SLOT(62); BFME_GSI_SLOT(63); BFME_GSI_SLOT(64);
	virtual const AsciiString &getMOTD( void );
	BFME_GSI_SLOT(66);
	virtual const AsciiString &getConfig( void );
	BFME_GSI_SLOT(68); BFME_GSI_SLOT(69);
	BFME_GSI_SLOT(70); BFME_GSI_SLOT(71); BFME_GSI_SLOT(72); BFME_GSI_SLOT(73); BFME_GSI_SLOT(74);
	BFME_GSI_SLOT(75); BFME_GSI_SLOT(76);
	virtual void loadSavedIgnoreList( void );
	BFME_GSI_SLOT(78); BFME_GSI_SLOT(79);
	BFME_GSI_SLOT(80); BFME_GSI_SLOT(81);
	virtual void setLocalIPs( UnsignedInt internalIP, UnsignedInt externalIP );
	BFME_GSI_SLOT(83); BFME_GSI_SLOT(84);
	BFME_GSI_SLOT(85); BFME_GSI_SLOT(86); BFME_GSI_SLOT(87); BFME_GSI_SLOT(88); BFME_GSI_SLOT(89);
	virtual void setMaxMessagesPerUpdate( Int num );
	BFME_GSI_SLOT(91); BFME_GSI_SLOT(92); BFME_GSI_SLOT(93);
	virtual void readAdditionalDisconnects( void );
};
extern GameSpyInfoInterface *TheGameSpyInfo;

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08();
	// MSVC groups overloaded virtuals in reverse declaration order:
	// fetch(AsciiString) lands on +0x24 and fetch(const char *) on +0x28.
	virtual UnicodeString fetch( const char *label, Bool *exists = 0 );
	virtual UnicodeString fetch( AsciiString label, Bool *exists = 0 );
};
extern GameTextInterface *TheGameText;

class UserPreferences
{
public:
	virtual ~UserPreferences();
	virtual Bool load( AsciiString fname );
	virtual Bool load( const UnicodeString &fname );
	virtual Bool write( void );

	char m_unmodelled04[ 0x10 ];
};

class GameSpyMiscPreferences : public UserPreferences
{
public:
	GameSpyMiscPreferences();
	virtual ~GameSpyMiscPreferences();
	Int getLocale( void );
	void setLocale( Int val );
	AsciiString getCachedStats( void );
	Int getMaxMessagesPerUpdate( void );
};

class WindowManager
{
public:
	void *_bfme_callAptFunction( unsigned int, const char *, int, const char *, const char *, const char *, const char *, const char * );
};
extern WindowManager *g_rva012F19E8WindowManager;

class Rva00548D30WindowGroup { public: void winEnable( bool ); };

void HandleBuddyResponses( void );
void HandlePersistentStorageResponses( void );
void GSMessageBoxOk( UnicodeString title, UnicodeString message, void (*okFunc)( void ) = 0 );
void TearDownGameSpy( void );
void SetUpGameSpy( const char *motdBuffer, const char *configBuffer );

struct LoginContext00552100 { char field000[ 0x250 ]; unsigned int field250; };

class BfmeAptScreenOnlineLogin
{
public:
	virtual void _bfme_update( void );
	void _bfme_checkLogin( void );
	void rva00551C80( bool refresh );
	bool applyLoginGadgets0054FB10( void );

private:
	char m_unmodelled04[ 0x30 ];
	LoginContext00552100 *m_context;
	char m_unmodelled38[ 0x5c ];
	char m_loggedInOK;
	char m_unmodelled95[ 3 ];
	int m_z98;
	char m_z9c;
	char m_flag9D;
	char m_unmodelled9E[ 2 ];
	char m_flagA0;
	char m_unmodelledA1[ 3 ];
	int m_localeA4;
	char m_unmodelledA8[ 4 ];
	char m_flagAC;
};

// ?_bfme_update@BfmeAptScreenOnlineLogin@@UAEXXZ
void BfmeAptScreenOnlineLogin::_bfme_update( void )
{
	if( TheGameSpyPeerMessageQueue )
	{
		PingResponse pingResp;
		if( ThePinger && ThePinger->getResponse( pingResp ) )
		{
			_bfme_checkLogin();
		}

		m_flagA0 = false;
		m_flagAC = false;
		HandleBuddyResponses();
		HandlePersistentStorageResponses();
		if( m_flagAC )
			rva00551C80( true );
		if( m_flagA0 )
		{
			((Rva00548D30WindowGroup *)this)->winEnable( true );
			{ unsigned int level = m_context->field250; g_rva012F19E8WindowManager->_bfme_callAptFunction( level, "CallChild", 1, "EnableButtonDeleteNickname", 0, 0, 0, 0 ); }
			{ unsigned int level = m_context->field250; g_rva012F19E8WindowManager->_bfme_callAptFunction( level, "CallChild", 1, "EnableButtonCreate", 0, 0, 0, 0 ); }
			{ unsigned int level = m_context->field250; g_rva012F19E8WindowManager->_bfme_callAptFunction( level, "CallChild", 1, "EnableButtonLogin", 0, 0, 0, 0 ); }
			{ unsigned int level = m_context->field250; g_rva012F19E8WindowManager->_bfme_callAptFunction( level, "CallChild", 1, "EnableButtonServiceTerms", 0, 0, 0, 0 ); }
		}

		PeerResponse resp;
		if( !m_loggedInOK && TheGameSpyPeerMessageQueue->getResponse( resp ) )
		{
			switch( resp.peerResponseType )
			{
			case PeerResponse::PEERRESPONSE_GROUPROOM:
				{
					GameSpyGroupRoom room;
					room.m_groupID = resp.groupRoom.id;
					room.m_maxWaiting = resp.groupRoom.maxWaiting;
					room.m_name = resp.groupRoomName.c_str();
					room.m_translatedName = UnicodeString( L"TEST" );
					room.m_numGames = resp.groupRoom.numGames;
					room.m_numPlaying = resp.groupRoom.numPlaying;
					room.m_numWaiting = resp.groupRoom.numWaiting;
					room.m_bfme1C = resp.groupRoom.bfme108;
					TheGameSpyInfo->addGroupRoom( room );
				}
				break;
			case PeerResponse::PEERRESPONSE_LOGIN:
				{
					m_loggedInOK = true;

					// fetch our player info
					TheGameSpyInfo->setLocalName( resp.nick.c_str() );
					TheGameSpyInfo->setLocalProfileID( resp.player.profileID );
					TheGameSpyInfo->loadSavedIgnoreList();
					TheGameSpyInfo->setLocalIPs( resp.player.internalIP, resp.player.externalIP );
					TheGameSpyInfo->readAdditionalDisconnects();

					GameSpyMiscPreferences miscPref;
					TheGameSpyInfo->setMaxMessagesPerUpdate( miscPref.getMaxMessagesPerUpdate() );
					if( miscPref.getLocale() < LOC_MIN || miscPref.getLocale() > LOC_MAX )
					{
						miscPref.setLocale( m_localeA4 );
						miscPref.write();

						PSRequest psReq;
						psReq.requestType = PSRequest::PSREQUEST_UPDATEPLAYERLOCALE;
						psReq.player.locale = m_localeA4;
						psReq.email = TheGameSpyInfo->getLocalEmail().str();
						psReq.nick = TheGameSpyInfo->getLocalBaseName().str();
						psReq.password = TheGameSpyInfo->getLocalPassword().str();
						psReq.player.id = TheGameSpyInfo->getLocalProfileID();
						if( TheGameSpyPSMessageQueue )
							TheGameSpyPSMessageQueue->addRequest( psReq );

						PSPlayerStats stats = GameSpyPSMessageQueueInterface::parsePlayerKVPairs( miscPref.getCachedStats().str() );
						stats.id = TheGameSpyInfo->getLocalProfileID();
						stats.locale = psReq.player.locale;
						TheGameSpyPSMessageQueue->trackPlayerStats( stats );
						TheGameSpyInfo->setCachedLocalPlayerStats( stats );

						PSResponse newResp;
						newResp.responseType = PSResponse::PSRESPONSE_PLAYERSTATS;
						newResp.player = TheGameSpyPSMessageQueue->findPlayerStatsByID( TheGameSpyInfo->getLocalProfileID() );
						TheGameSpyPSMessageQueue->addResponse( newResp );
					}
				}
				break;
			case PeerResponse::PEERRESPONSE_DISCONNECT:
				{
					if( !m_flagA0 )
					{
						AsciiString disconMunkee;
						m_z98 = 0;
						disconMunkee.format( "GUI:GSDisconReason%d", resp.discon.reason );
						GSMessageBoxOk( TheGameText->fetch( "GUI:GSErrorTitle" ), TheGameText->fetch( disconMunkee ) );
						((Rva00548D30WindowGroup *)this)->winEnable( true );
					}

					// kill & restart the threads
					AsciiString motd = TheGameSpyInfo->getMOTD();
					AsciiString config = TheGameSpyInfo->getConfig();
					TearDownGameSpy();
					SetUpGameSpy( motd.str(), config.str() );
					m_flag9D = false;
					applyLoginGadgets0054FB10();
				}
				break;
			}
		}

		_bfme_checkLogin();
	}
}
