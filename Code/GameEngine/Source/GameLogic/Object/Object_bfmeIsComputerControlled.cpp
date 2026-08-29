// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef bool Bool;

enum PlayerType
{
	PLAYER_COMPUTER = 0,
	PLAYER_HUMAN = 1
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	PlayerType getPlayerType() const { return m_playerType; }

private:
	unsigned char m_bfmePrefix[0x2c];
	PlayerType m_playerType;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Player *getControllingPlayer() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool bfmeIsComputerControlled() const;

private:
	unsigned char m_bfmePrefix[0x23c];
	Team *m_team;
};

// The retail spelling is unrecovered.  The three Pathfinder callers use this
// query to enable their computer-player pathfinding behavior.
Bool Object::bfmeIsComputerControlled() const
{
	if (m_team != 0)
	{
		Player *player = m_team->getControllingPlayer();
		if (player != 0)
			return player->getPlayerType() == PLAYER_COMPUTER;
	}

	return false;
}
