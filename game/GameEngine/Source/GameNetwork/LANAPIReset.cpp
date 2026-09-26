// cl: /DNDEBUG /MD /EHs-c-
// readable body: game/GameEngine/Source/GameNetwork/lanapi.cpp

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;

struct BfmeNetAddress
{
	UnsignedInt m_ip;
	unsigned short m_port;
};

struct LANMessage
{
	enum { MSG_REQUEST_LOBBY_LEAVE = 7 };
	Int LANMessageType;
	UnsignedByte m_payload[0x1d8];
};

class Transport
{
public:
	void update();
};

class LANGameInfo
{
public:
	~LANGameInfo();
	LANGameInfo *getNext() { return m_next; }

private:
	UnsignedByte m_unknown[0x398];
	LANGameInfo *m_next;
};

class LANPlayer
{
public:
	~LANPlayer();
	LANPlayer *getNext() { return m_next; }

private:
	UnsignedByte m_unknown[0x10];
	LANPlayer *m_next;
};

class LANAPI
{
public:
	virtual void reset();
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void fillInLANMessage(LANMessage *message) = 0;

protected:
	void sendMessage(LANMessage *message, UnsignedInt address = 0);

private:
	UnsignedByte m_unknown04[4];
	LANPlayer *m_lobbyPlayers;
	LANGameInfo *m_games;
	UnsignedByte m_unknown10[0x14];
	Int m_pendingAction;
	UnsignedInt m_expiration;
	UnsignedInt m_actionTimeout;
	BfmeNetAddress m_directConnectRemoteAddress;
	UnsignedInt m_lastResendTime;
	Bool m_isInLANMenu;
	Bool m_inLobby;
	UnsignedByte m_unknown3e[2];
	LANGameInfo *m_currentGame;
	UnsignedByte m_unknown44[8];
	Transport *m_transport;
};

void LANAPI::reset()
{
	if (m_inLobby)
	{
		LANMessage message;
		fillInLANMessage(&message);
		message.LANMessageType = LANMessage::MSG_REQUEST_LOBBY_LEAVE;
		sendMessage(&message);
	}

	m_transport->update();

	LANGameInfo *game = m_games;
	while (game)
	{
		LANGameInfo *deletable = game;
		game = game->getNext();
		delete deletable;
	}

	LANPlayer *player = m_lobbyPlayers;
	while (player)
	{
		LANPlayer *deletable = player;
		player = player->getNext();
		delete deletable;
	}

	m_games = 0;
	m_lobbyPlayers = 0;
	BfmeNetAddress noAddress = { 0, 0 };
	m_directConnectRemoteAddress = noAddress;
	m_pendingAction = 0;
	m_expiration = 0;
	m_inLobby = true;
	m_isInLANMenu = true;
	m_currentGame = 0;
}
