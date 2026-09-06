// ?getPlayersWithRelationship@PlayerList@@QAEGHH_N@Z
// partial score=0.8 date=2026-09-06
// cl: /DNDEBUG /MD /EHs-c-
// BFME extends the ZH player-mask query with a direction flag.

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

PlayerMaskType PlayerList::getPlayersWithRelationship(int playerIndex,
	int allowedRelationships, bool reverse)
{
	Player *srcPlayer;
	PlayerMaskType retVal = 0;

	if (allowedRelationships == 0)
		return retVal;

	srcPlayer = getNthPlayer(playerIndex);
	if (!srcPlayer)
		return retVal;

	if (allowedRelationships & ALLOW_SAME_PLAYER)
		retVal |= srcPlayer->getPlayerMask();

	int i = 0;
	if (m_playerCount > 0)
	{
		do
		{
			Player *player;
			if (i < 0 || i >= 32)
				return retVal;
			player = m_players[i];
			if (!player)
				return retVal;

			if (player == srcPlayer)
				return retVal;

			Relationship relationship;
			if (reverse)
				relationship = player->getRelationship(srcPlayer->getDefaultTeam());
			else
				relationship = srcPlayer->getRelationship(player->getDefaultTeam());

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

			++i;
		}
		while (i < m_playerCount);
	}

	return (PlayerMaskType)retVal;
}
