// cl: /O2

typedef int Int;
typedef unsigned int UnsignedInt;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
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
	for (Int playerIndex = 0; playerIndex < m_playerCount; ++playerIndex)
	{
		Player *player = getNthPlayer(playerIndex);
		if (player)
			mask |= player->getPlayerMask();
	}
	return mask;
}
