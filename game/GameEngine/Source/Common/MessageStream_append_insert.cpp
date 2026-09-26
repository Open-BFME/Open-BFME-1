// Open-BFME: MessageStream::appendMessage and insertMessage, retail 0x8A690
// and 0x8A720.  The BFME build inlines GameMessage's constructor and the list
// splice, so the local layout is kept here instead of making either call.

void * __cdecl operator new(unsigned int bytes);

struct BfmePlayer_AppendInsert
{
	char m_pad[0x24];
	int m_playerIndex;
};

struct BfmePlayerList_AppendInsert
{
	char m_pad[0x0C];
	BfmePlayer_AppendInsert *m_localPlayer;
};

extern BfmePlayerList_AppendInsert *ThePlayerList;

class GameMessage
{
public:
	enum Type { MSG_INVALID = 0 };

	GameMessage(Type type);
	virtual ~GameMessage() {}

	GameMessage *m_next;                      // +0x04
	GameMessage *m_prev;                      // +0x08
	void *m_list;                             // +0x0C
	Type m_type;                              // +0x10
	int m_playerIndex;                        // +0x14
	unsigned char m_argCount;                 // +0x18
	char m_pad[3];                            // +0x19
	GameMessage *m_argList;                   // +0x1C
	GameMessage *m_argTail;                   // +0x20
};

GameMessage::GameMessage(Type type)
{
	m_playerIndex = ThePlayerList->m_localPlayer->m_playerIndex;
	m_type = type;
	m_argList = 0;
	m_argTail = 0;
	m_argCount = 0;
	m_list = 0;
	m_next = 0;
	m_prev = 0;
}

class MessageStream
{
public:
	virtual GameMessage *appendMessage(GameMessage::Type type);
	virtual GameMessage *insertMessage(GameMessage::Type type,
		GameMessage *messageToInsertAfter);

private:
	char m_pad[4];                            // +0x04
	GameMessage *m_firstMessage;              // +0x08
	GameMessage *m_lastMessage;               // +0x0C
};

GameMessage *MessageStream::appendMessage( GameMessage::Type type )
{
	GameMessage *message = new GameMessage(type);
	message->m_next = 0;

	if (m_lastMessage)
	{
		m_lastMessage->m_next = message;
		message->m_prev = m_lastMessage;
		m_lastMessage = message;
	}
	else
	{
		m_firstMessage = message;
		m_lastMessage = message;
		message->m_prev = 0;
	}

	message->m_list = this;
	return message;
}

GameMessage *MessageStream::insertMessage( GameMessage::Type type,
	GameMessage *messageToInsertAfter )
{
	GameMessage *message = new GameMessage(type);
	GameMessage *next = messageToInsertAfter->m_next;
	message->m_next = next;
	message->m_prev = messageToInsertAfter;

	if (next)
		next->m_prev = message;
	else
		m_lastMessage = message;

	messageToInsertAfter->m_next = message;
	message->m_list = this;
	return message;
}
