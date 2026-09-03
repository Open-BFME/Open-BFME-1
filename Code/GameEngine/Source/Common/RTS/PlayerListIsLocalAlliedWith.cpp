// cl: /O2

class Team;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	unsigned char m_pad[0x23C];
	Team *m_team;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
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
