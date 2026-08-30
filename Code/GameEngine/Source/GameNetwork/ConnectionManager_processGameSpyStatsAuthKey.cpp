// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef unsigned int UnsignedInt;

template <typename T> class StringBase
{
	friend class BFMEConnectionManager;
	friend class GameSpyGameSlot;
	friend class BFMENetGameSpyStatsAuthKeyCommandMsg;

public:
	int getLength() const { return m_data ? m_data->length : 0; }

private:
	StringBase( const StringBase<T> &source );
	~StringBase();

	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		T data[ 1 ];
	};

	Header *m_data;
};

typedef StringBase<char> AsciiString;

class GameSpyGameSlot
{
public:
	AsciiString getLoginName() const;
	void setLoginName( AsciiString name );
	void setLocale( AsciiString name );
};

class GameSpyStagingRoom
{
public:
	GameSpyGameSlot *getGameSpySlot( int index );
};

extern GameSpyStagingRoom *TheGameSpyGame;

class BFMENetGameSpyStatsAuthKeyCommandMsg
{
public:
	UnsignedInt getPlayerID() const { return m_playerID; }
	AsciiString getText1C();
	AsciiString getText20();

private:
	char m_unmodelled_00[ 0x0C ];
	UnsignedInt m_playerID;
};

class BFMEConnectionManager
{
public:
	void processGameSpyStatsAuthKeyCommand( void *command );
};

void BFMEConnectionManager::processGameSpyStatsAuthKeyCommand( void *command )
{
	BFMENetGameSpyStatsAuthKeyCommandMsg *message =
		(BFMENetGameSpyStatsAuthKeyCommandMsg *)command;

	if( message->getPlayerID() < 8 )
	{
		GameSpyGameSlot *slot = TheGameSpyGame->getGameSpySlot( message->getPlayerID() );
		if( slot && slot->getLoginName().getLength() == 0 )
		{
			slot->setLoginName( message->getText1C() );
			slot->setLocale( message->getText20() );
		}
	}
}
