// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AISkirmishPlayer::getMyEnemyPlayerIndex, retail 0x001687B0, 63 bytes.

typedef int Int;

enum PlayerType
{
	PLAYER_HUMAN = 0
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Int getPlayerIndex(void) const { return m_playerIndex; }
	PlayerType getPlayerType(void) const { return m_playerType; }

private:
	unsigned char m_unreconstructed_00[0x24];
	Int m_playerIndex;
	unsigned char m_unreconstructed_28[4];
	PlayerType m_playerType;
};

class PlayerList
{
public:
	Int getPlayerCount(void) const { return m_playerCount; }
	Player *getNthPlayer(Int playerIndex);

private:
	unsigned char m_unreconstructed_00[0x10];
	Int m_playerCount;
};

extern PlayerList *ThePlayerList;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AISkirmishPlayer.h
class AISkirmishPlayer
{
protected:
	Int getMyEnemyPlayerIndex(void);

private:
	unsigned char m_unreconstructed_00[0x9C];
	Player *m_currentEnemy;
};

// ?getMyEnemyPlayerIndex@AISkirmishPlayer@@IAEHXZ
Int AISkirmishPlayer::getMyEnemyPlayerIndex(void)
{
	Int playerNdx;
	if (m_currentEnemy)
		return m_currentEnemy->getPlayerIndex();

	for (playerNdx = 0; playerNdx < ThePlayerList->getPlayerCount(); playerNdx++)
	{
		if (ThePlayerList->getNthPlayer(playerNdx)->getPlayerType() == PLAYER_HUMAN)
			break;
	}
	return playerNdx;
}
