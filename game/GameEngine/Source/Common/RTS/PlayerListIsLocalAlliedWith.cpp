// cl: /O2

class Team;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	bool isPlayerActive() const;
	Relationship getRelationship(const Team *team) const;
};

#include "../../GameLogic/Object/object.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	unsigned char isLocalAlliedWith(Object *obj);

private:
	unsigned char m_pad[0x0C];
	Player *m_local;
};

unsigned char PlayerList::isLocalAlliedWith(Object *obj)
{
	Player *local = m_local;
	if (!local)
		return 0;
	if (!local->isPlayerActive())
		return 1;
	Team *team = *(Team **)(0x23C + (unsigned int)obj);
	return local->getRelationship(team) == ALLIES;
}
