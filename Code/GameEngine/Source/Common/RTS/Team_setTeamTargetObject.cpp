// cl: /DNDEBUG /MD /EHsc
//
// Team::setTeamTargetObject. Zero Hour's body: null clears the id; only
// computer players above easy difficulty store Object::getID. BFME keeps
// the prototype at Team+4 and the player at Prototype+8, the type at
// Player+0x2c, and the object id at Object+0x74; the target slot is Team+0xE8.

enum PlayerType
{
	PLAYER_HUMAN = 0,
	PLAYER_COMPUTER = 1
};

enum GameDifficulty
{
	DIFFICULTY_EASY = 0,
	DIFFICULTY_NORMAL = 1,
	DIFFICULTY_HARD = 2
};

class Player
{
public:
	GameDifficulty getPlayerDifficulty() const;
	PlayerType getPlayerType() const { return m_playerType; }

private:
	char m_pad[0x2C];
	PlayerType m_playerType;				// +0x2c
};

class TeamPrototype
{
public:
	char m_pad[8];
	Player *m_owningPlayer;					// +8
};

class Object
{
public:
	unsigned int getID() const { return m_id; }

private:
	char m_pad[0x74];
	unsigned int m_id;					// +0x74
};

class Team
{
public:
	void setTeamTargetObject(const Object *target);

	__forceinline Player *getControllingPlayer() const
	{
		TeamPrototype *proto = m_proto;
		if (!proto)
			return 0;
		return proto->m_owningPlayer;
	}

private:
	char m_pad0[4];
	TeamPrototype *m_proto;					// +4
	char m_pad1[0xE0];					// 0xE8 - 8
	unsigned int m_commonAttackTarget;			// +0xE8
};

void Team::setTeamTargetObject(const Object *target)
{
	if (target == 0)
	{
		m_commonAttackTarget = 0;
		return;
	}
	if (getControllingPlayer()->getPlayerType() == PLAYER_COMPUTER)
	{
		if (getControllingPlayer()->getPlayerDifficulty() == DIFFICULTY_EASY)
			return;
		m_commonAttackTarget = target->getID();
	}
}
