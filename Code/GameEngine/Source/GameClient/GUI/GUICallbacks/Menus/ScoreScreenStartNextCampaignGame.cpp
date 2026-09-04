// cl: /DNDEBUG /MD /EHsc
// Open-BFME: startNextCampaignGame, retail 0x004E2C60, 189 bytes.
// Converted from gen-dump d_004e2c60. ZH twin is in ScoreScreen.cpp; BFME
// drops the challenge-campaign GameInfo block and assigns m_pendingFile
// (+0xB84) from CampaignManager::getCurrentMap. Named by the ZH body and
// the MSG_NEW_GAME / GAME_SINGLE_PLAYER / InitRandom(0) tail.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void set( const StringBase<T> &other );

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	AsciiString &operator=( const AsciiString &other )
	{
		set( other );
		return *this;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shell.h
class Shell
{
public:
	void popImmediate();
	void hide( bool hide );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class GameMessage
{
public:
	void appendIntegerArgument( int value );
};

#define STARTNEXT_STREAM_SLOT(n) virtual void slot##n();
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class MessageStream
{
public:
	STARTNEXT_STREAM_SLOT(00) STARTNEXT_STREAM_SLOT(01)
	STARTNEXT_STREAM_SLOT(02) STARTNEXT_STREAM_SLOT(03)
	STARTNEXT_STREAM_SLOT(04) STARTNEXT_STREAM_SLOT(05)
	STARTNEXT_STREAM_SLOT(06) STARTNEXT_STREAM_SLOT(07)
	STARTNEXT_STREAM_SLOT(08) STARTNEXT_STREAM_SLOT(09)
	STARTNEXT_STREAM_SLOT(10) STARTNEXT_STREAM_SLOT(11)
	STARTNEXT_STREAM_SLOT(12)
	virtual GameMessage *appendMessage( int type );
};
#undef STARTNEXT_STREAM_SLOT

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/CampaignManager.h
class CampaignManager
{
public:
	AsciiString getCurrentMap();

	char m_pad[ 0x14 ];
	int m_rankPoints;
	int m_gameDifficulty;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	char m_pad[ 0xB84 ];
	AsciiString m_pendingFile;
};

extern Shell *TheShell;
extern CampaignManager *TheCampaignManager;
extern GlobalData *TheWritableGlobalData;
extern MessageStream *TheMessageStream;

void InitRandom( unsigned int seed );

enum
{
	GAME_SINGLE_PLAYER = 0
};

enum
{
	MSG_NEW_GAME = 30
};

// ?startNextCampaignGame@@YAXXZ
void startNextCampaignGame( void )
{
	TheShell->popImmediate();
	TheShell->hide( true );
	TheWritableGlobalData->m_pendingFile = TheCampaignManager->getCurrentMap();
	GameMessage *msg = TheMessageStream->appendMessage( MSG_NEW_GAME );
	msg->appendIntegerArgument( GAME_SINGLE_PLAYER );
	msg->appendIntegerArgument( TheCampaignManager->m_gameDifficulty );
	msg->appendIntegerArgument( TheCampaignManager->m_rankPoints );
	InitRandom( 0 );
}
