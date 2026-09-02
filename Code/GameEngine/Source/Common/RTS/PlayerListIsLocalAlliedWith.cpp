// cl: /O2

class Team;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class Player
{
public:
	Relationship getRelationship(const Team *team) const;
};

class Rva000DF7F0Player : public Player
{
public:
	bool active() const;
};

class Object
{
public:
	unsigned char m_pad[0x23C];
	Team *m_team;
};

class PlayerList
{
public:
	unsigned char isLocalAlliedWith(Object *obj);

private:
	unsigned char m_pad[0x0C];
	Rva000DF7F0Player *m_local;
};

unsigned char PlayerList::isLocalAlliedWith(Object *obj)
{
	Rva000DF7F0Player *local = m_local;
	if (!local)
		return 0;
	if (!local->active())
		return 1;
	Team *team = *(Team **)(0x23C + (unsigned int)obj);
	return local->getRelationship(team) == ALLIES;
}
