// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef bool Bool;

enum PlayerType
{
	PLAYER_COMPUTER = 0,
	PLAYER_HUMAN = 1
};

class Player
{
public:
	PlayerType getPlayerType() const { return m_playerType; }

private:
	unsigned char m_bfmePrefix[0x2c];
	PlayerType m_playerType;
};

class Team
{
public:
	Player *getControllingPlayer() const;
};

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
