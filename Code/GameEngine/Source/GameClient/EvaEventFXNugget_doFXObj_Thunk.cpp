// cl: /DNDEBUG /MD /EHsc
// Clean C++ reconstruction of BFME's Eva-event FX dispatch.

typedef bool Bool;

enum EvaMessage
{
	EVA_INVALID = -1
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};

struct Coord3D;
class Team;

class Player
{
public:
	Bool isLocalPlayer() const;
	Relationship getRelationship(const Team *that) const;
};

class Object
{
public:
	Player *getControllingPlayer() const;

	const Team *getTeam() const
	{
		return m_team;
	}

private:
	unsigned char m_pad[0x23C];
	Team *m_team;
};

class PlayerList
{
public:
	Player *getLocalPlayer() const
	{
		return m_localPlayer;
	}

private:
	unsigned char m_pad[0x0C];
	Player *m_localPlayer;
};

class Eva
{
public:
	Bool setShouldPlay(EvaMessage message, const Coord3D *position);
};

extern PlayerList *ThePlayerList;
extern Eva *TheEva;

class EvaEventFXNugget
{
public:
	virtual void doFXObj(const Object *primary, const Object *secondary) const;

private:
	unsigned char m_pad[0xB0];
	EvaMessage m_evaEventOwner;
	EvaMessage m_evaEventAlly;
	EvaMessage m_evaEventEnemy;
};

void EvaEventFXNugget::doFXObj(const Object *primary, const Object *) const
{
	if (primary)
	{
		Player *player = primary->getControllingPlayer();
		if (player && player->isLocalPlayer())
		{
			TheEva->setShouldPlay(m_evaEventOwner, 0);
			return;
		}

		Player *localPlayer = ThePlayerList->getLocalPlayer();
		if (localPlayer && localPlayer->getRelationship(primary->getTeam()) == ALLIES)
		{
			TheEva->setShouldPlay(m_evaEventAlly, 0);
			return;
		}

		TheEva->setShouldPlay(m_evaEventEnemy, 0);
	}
}
