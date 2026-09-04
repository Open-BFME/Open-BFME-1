// GameMessage destructor body at retail RVA 0x0008A2F0.

class GameMessage;

class GameMessageArgument
{
public:
	virtual void deleteInstance(int flags);

	GameMessageArgument *m_next;
};

void GameMessageArgument::deleteInstance(int)
{
}

class GameMessageList
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual void removeMessage(GameMessage *message);
};

class GameMessage
{
public:
	virtual ~GameMessage(void);

private:
	char m_pad04[8];
	GameMessageList *m_list;
	char m_pad10[12];
	GameMessageArgument *m_argList;
};

GameMessage::~GameMessage(void)
{
	GameMessageArgument *argument = m_argList;
	if (argument != 0)
	{
		do
		{
			GameMessageArgument *next = argument->m_next;
			argument->deleteInstance(1);
			argument = next;
		}
		while (argument != 0);
	}

	m_argList = 0;
	if (m_list != 0)
		m_list->removeMessage(this);
}
