// cl: /O2

typedef int Int;
typedef unsigned int UnsignedInt;

class Player
{
public:
	UnsignedInt getPlayerMask() const
	{
		return 1u << m_playerIndex;
	}

private:
	unsigned char m_pad[0x24];
	Int m_playerIndex;
};

class PlayerList
{
public:
	UnsignedInt getPlayersMask();

	Player *getNthPlayer(Int i)
	{
		if (i < 0 || i >= 32)
			return 0;
		return m_players[i];
	}

private:
	unsigned char m_pad[0x10];
	Int m_playerCount;
	Player *m_players[32];
};

UnsignedInt PlayerList::getPlayersMask()
{
	UnsignedInt mask = 0;
	for (Int i = 0; i < m_playerCount; ++i)
	{
		Player *player = getNthPlayer(i);
		if (player)
			mask |= player->getPlayerMask();
	}
	return mask;
}
