struct LANAddress
{
	int m_address;
	short m_port;
};

class GameSlot
{
public:
	unsigned char m_unmodelled00[ 0x10 ];
	int m_color;
};

class LANGameInfo
{
public:
	virtual void unused0();
	virtual void unused1();
	virtual void unused2();
	virtual void unused3();
	virtual void unused4();
	virtual void unused5();
	virtual void reset();
	GameSlot *getSlot( int index );
};

class LANAPI
{
public:
	virtual void unused00(); virtual void unused01(); virtual void unused02();
	virtual void unused03(); virtual void unused04(); virtual void unused05();
	virtual void unused06(); virtual void unused07(); virtual void unused08();
	virtual void unused09(); virtual void unused10(); virtual void unused11();
	virtual void unused12(); virtual void unused13(); virtual void unused14();
	virtual void unused15(); virtual void unused16(); virtual void unused17();
	virtual void unused18(); virtual void unused19(); virtual void unused20();
	virtual void setLocalAddress( int enabled, LANAddress *address );
	virtual void unused22(); virtual void unused23(); virtual void unused24();
	virtual void unused25(); virtual void unused26(); virtual void unused27();
	virtual void unused28(); virtual void unused29(); virtual void unused30();
	virtual void unused31(); virtual void unused32(); virtual void unused33();
	virtual void unused34(); virtual void unused35(); virtual void unused36();
	virtual void unused37(); virtual void unused38(); virtual void unused39();
	virtual void unused40(); virtual void unused41(); virtual void unused42();
	virtual void unused43(); virtual void unused44(); virtual void unused45();
	virtual void unused46(); virtual void unused47();
	virtual LANGameInfo *getCurrentGame();
};

extern LANAPI *TheLAN;
extern void *g_lanConnection;
extern char g_lanEndpointBuffer[];

void publishLanEndpoint( LANGameInfo *game, char *buffer,
	void *connection, int flags );
void resetLanGameState();
void processInactiveLanMessages();

// ?resetLanSession@@YAXH@Z
void resetLanSession( int mode )
{
	if( mode < 2 )
	{
		if( g_lanConnection )
			publishLanEndpoint( TheLAN->getCurrentGame(),
				g_lanEndpointBuffer, g_lanConnection, 0 );

		if( mode == 0 )
		{
			LANGameInfo *game = TheLAN->getCurrentGame();
			game->reset();
			resetLanGameState();
			processInactiveLanMessages();

			for( int i = 0; i < 8; ++i )
				game->getSlot( i )->m_color = -1;

			LANAddress address = { 0, 0 };
			TheLAN->setLocalAddress( 1, &address );
		}
	}
}
