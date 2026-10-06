// The matched staging-refresh callee and OnlineCustomMatch state siblings tie
// this 560-byte body to the BfmeAptScreenOnlineCustomMatch object. The selector
// scan does not give 0x005406E0 a semantic method name, so the member keeps its
// RVA. Retail returns a status byte at 0x0054090F.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

class Image;
class GameWindow;

// Retail's singleton is ?TheMappedImageCollection@@3PAVImageCollection@@A: the
// class is ImageCollection, only forward declared here (this TU reaches the
// lookup through the 0x0001D606 thunk owner below, which stays as it is).
class ImageCollection;
class Rva0001D606ImageCollection
{
public:
	const Image *findImageByName( const AsciiString &name );
};

extern ImageCollection *TheMappedImageCollection;

// Retail's request view is 0x194 bytes; the upstream Zero Hour PeerRequest has
// a different STL payload and does not describe this BFME ABI.
class PeerRequest
{
public:
	PeerRequest();
	~PeerRequest();
	int peerRequestType;
	unsigned char m_pad[ 0xE0 ];
	unsigned char m_fieldE4;
	unsigned char pad1BC[ 0x194 - 0xE5 ];
};

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

#define GAMESPY_SLOT( n ) virtual void gamespySlot##n() = 0
class GameSpyInfo
{
public:
	GAMESPY_SLOT( 0 ); GAMESPY_SLOT( 1 ); GAMESPY_SLOT( 2 ); GAMESPY_SLOT( 3 );
	GAMESPY_SLOT( 4 ); GAMESPY_SLOT( 5 );
	virtual void joinGroupRoom( void *room ) = 0;
	GAMESPY_SLOT( 7 ); GAMESPY_SLOT( 8 );
	virtual void joinBestGroupRoom(bool refresh) = 0;
	GAMESPY_SLOT( 10 ); GAMESPY_SLOT( 11 ); GAMESPY_SLOT( 12 ); GAMESPY_SLOT( 13 );
	GAMESPY_SLOT( 14 );
	virtual void *getCurrentGroupRoom() = 0;
	GAMESPY_SLOT( 16 ); GAMESPY_SLOT( 17 ); GAMESPY_SLOT( 18 ); GAMESPY_SLOT( 19 );
	GAMESPY_SLOT( 20 ); GAMESPY_SLOT( 21 ); GAMESPY_SLOT( 22 ); GAMESPY_SLOT( 23 );
	GAMESPY_SLOT( 24 ); GAMESPY_SLOT( 25 ); GAMESPY_SLOT( 26 ); GAMESPY_SLOT( 27 );
	GAMESPY_SLOT( 28 ); GAMESPY_SLOT( 29 ); GAMESPY_SLOT( 30 ); GAMESPY_SLOT( 31 );
	GAMESPY_SLOT( 32 ); GAMESPY_SLOT( 33 ); GAMESPY_SLOT( 34 ); GAMESPY_SLOT( 35 );
	GAMESPY_SLOT( 36 );
	virtual void clearStagingRoomList() = 0;
	GAMESPY_SLOT( 38 ); GAMESPY_SLOT( 39 ); GAMESPY_SLOT( 40 ); GAMESPY_SLOT( 41 );
	GAMESPY_SLOT( 42 ); GAMESPY_SLOT( 43 );
	virtual void leaveStagingRoom() = 0;
};
#undef GAMESPY_SLOT

class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;

class GameWindowManager
{
public:
	void refreshLayout( void *host );
};

extern GameWindowManager *TheWindowManager;

class WindowManager
{
public:
	void unidentified_00015235( int movie, const char *function, int argumentCount,
		const void *argument1, const void *argument2, int unused1, int unused2,
		int unused3 );
};

extern WindowManager *g_rva012F19E8WindowManager;	///< retail [0x012F19E8]

class Rva005406E0Field34
{
public:
	unsigned char pad00[ 0x250 ];
	int field250;
};

class BfmeE976
{
public:
	void bfmeGo976E();
};

class AptOnlineCustomMatch
{
public:
	void OpenConnectionScreen( bool value );
};

class Rva005397D0AptScreen
{
public:
	void rva005397D0PopulateGroupRoomListbox();
};

class GameSpyConfigInterface
{
public:
	virtual void s00() = 0; virtual void s01() = 0; virtual void s02() = 0;
	virtual void s03() = 0; virtual void s04() = 0; virtual void s05() = 0;
	virtual void s06() = 0; virtual void s07() = 0; virtual void s08() = 0;
	virtual void s09() = 0; virtual void s0a() = 0; virtual void s0b() = 0;
	virtual void s0c() = 0; virtual void s0d() = 0;
	virtual unsigned char slot14() = 0;
};

extern GameSpyConfigInterface *TheGameSpyConfig;

class BfmeAptScreenOnlineCustomMatch
{
public:
	bool Rva005406E0();
	void applyStagingRoomRefresh();

private:
	unsigned char pad00[ 0x34 ];
	Rva005406E0Field34 *field34;
	unsigned char pad38[ 0x40 - 0x38 ];
	unsigned char pad40[ 4 ];
	unsigned char pad44[ 0x188 - 0x44 ];
	int field188;
	GameWindow *field18C;
	GameWindow *field190;
	GameWindow *field194;
	GameWindow *field198;
	unsigned char pad19C[ 0x1B0 - 0x19C ];
	const Image *field1B0;
	unsigned char field1B4;
	unsigned char pad1B5[ 3 ];
	int field1B8;
	unsigned char pad1BC[ 0x1D4 - 0x1BC ];
	unsigned char field1D4;
};

bool BfmeAptScreenOnlineCustomMatch::Rva005406E0()
{
	if( !field18C ) return false;
	if( !field190 ) return false;
	if( !field194 ) return false;
	if( !field198 ) return false;
					if( TheGameSpyInfo )
						reinterpret_cast<GameSpyInfo *>(TheGameSpyInfo)->leaveStagingRoom();

					((BfmeE976 *)( (char *)this + 0x40 ))->bfmeGo976E();
					((AptOnlineCustomMatch *)this)->OpenConnectionScreen( false );
					TheWindowManager->refreshLayout( field34 );
					field1B0 = ((Rva0001D606ImageCollection *)TheMappedImageCollection)->findImageByName( AsciiString( "AptLock" ) );
					field1B4 = 0;

					if( reinterpret_cast<GameSpyInfo *>(TheGameSpyInfo)->getCurrentGroupRoom() )
					{
						reinterpret_cast<GameSpyInfo *>(TheGameSpyInfo)->joinGroupRoom( reinterpret_cast<GameSpyInfo *>(TheGameSpyInfo)->getCurrentGroupRoom() );
						field1B8 = 0;
					}
					else
					{
						reinterpret_cast<GameSpyInfo *>(TheGameSpyInfo)->joinBestGroupRoom(true);
					}

					reinterpret_cast<GameSpyInfo *>(TheGameSpyInfo)->clearStagingRoomList();

					PeerRequest req;
					req.peerRequestType = 7;
					req.m_fieldE4 = TheGameSpyConfig->slot14();
					TheGameSpyPeerMessageQueue->addRequest( req );

					((Rva005397D0AptScreen *)this)->rva005397D0PopulateGroupRoomListbox();
					applyStagingRoomRefresh();

					int one = 1;
					WindowManager *windowManager = g_rva012F19E8WindowManager;
						int movieCopy1 = field34->field250;
						windowManager->unidentified_00015235( movieCopy1, "CallChild", one, "ClosePassword", 0, 0, 0, 0 );
					windowManager = g_rva012F19E8WindowManager;
						int movieCopy2 = field34->field250;
						windowManager->unidentified_00015235( movieCopy2, "CallChild", 2, "gotoAndPlay", "_lobby", 0, 0, 0 );
					windowManager = g_rva012F19E8WindowManager;
						int movieCopy3 = field34->field250;
						windowManager->unidentified_00015235( movieCopy3, "CallChild", one, "EnableButtonCreateGame", 0, 0, 0, 0 );
					windowManager = g_rva012F19E8WindowManager;
						int movieCopy4;
						movieCopy4 = field34->field250;
						windowManager->unidentified_00015235( movieCopy4, "CallChild", one, "DisableButtonJoinGame", 0, 0, 0, 0 );

					field1D4 = 0;
					field188 = one;
					return true;
}
