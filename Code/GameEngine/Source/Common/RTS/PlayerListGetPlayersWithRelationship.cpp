// BFME extends the Zero Hour player-mask query with a direction flag.

typedef unsigned short PlayerMaskType;

class Team;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};

enum AllowPlayerRelationship
{
	ALLOW_SAME_PLAYER = 0x01,
	ALLOW_ALLIES = 0x02,
	ALLOW_ENEMIES = 0x04,
	ALLOW_NEUTRAL = 0x08
};

class Player
{
public:
	unsigned int getPlayerMask() const
	{
		return 1u << m_playerIndex;
	}

	Team *getDefaultTeam() const
	{
		return m_defaultTeam;
	}

	Relationship getRelationship(const Team *that) const;

private:
	unsigned char m_pad00[0x24];
	int m_playerIndex;
	unsigned char m_pad28[0x208];
	Team *m_defaultTeam;
};

class PlayerList
{
public:
	PlayerMaskType getPlayersWithRelationship(int playerIndex,
		int allowedRelationships, bool reverse);

private:
	Player *getNthPlayer(int index)
	{
		if (index < 0 || index >= 32)
			return 0;
		return m_players[index];
	}

	unsigned char m_pad00[0x10];
	int m_playerCount;
	Player *m_players[32];
};

// ?getPlayersWithRelationship@PlayerList@@QAEGHH_N@Z
PlayerMaskType PlayerList::getPlayersWithRelationship(int playerIndex,
	int allowedRelationships, bool reverse)
{
	PlayerMaskType retVal = 0;

	if (allowedRelationships == 0)
		return retVal;

	Player *srcPlayer = getNthPlayer(playerIndex);
	if (!srcPlayer)
		return retVal;

	if (allowedRelationships & ALLOW_SAME_PLAYER)
		retVal |= srcPlayer->getPlayerMask();

	for (int i = 0; i < m_playerCount; ++i)
	{
		if (i < 0 || i >= 32)
			continue;

		Player *player = m_players[i];
		if (!player || player == srcPlayer)
			continue;

		Relationship relationship;
		if (!reverse)
			relationship = srcPlayer->getRelationship(player->getDefaultTeam());
		else
			relationship = player->getRelationship(srcPlayer->getDefaultTeam());

		switch (relationship)
		{
		default:
			if (allowedRelationships == 0x0f)
				retVal |= player->getPlayerMask();
			break;
		case ALLIES:
			if (allowedRelationships & ALLOW_ALLIES)
				retVal |= player->getPlayerMask();
			break;
		case NEUTRAL:
			if (allowedRelationships & ALLOW_NEUTRAL)
				retVal |= player->getPlayerMask();
			break;
		case ENEMIES:
			if (allowedRelationships & ALLOW_ENEMIES)
				retVal |= player->getPlayerMask();
			break;
		}
	}

	return retVal;
}
