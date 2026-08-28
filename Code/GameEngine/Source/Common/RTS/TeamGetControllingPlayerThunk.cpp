// cl: /DNDEBUG /MD /EHsc
// readable body of ?getControllingPlayer@Team@@QBEPAVPlayer@@XZ: Code/GameEngine/Source/Common/RTS/Team.cpp

// Open-BFME5: Team::getControllingPlayer lifted from the BFME retail layout.

class Player;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
	unsigned char m_pad[8];
public:
	Player *m_controllingPlayer;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	virtual ~Team();
	Player *getControllingPlayer() const;

private:
	TeamPrototype *m_proto;
};

Player *Team::getControllingPlayer() const
{
	TeamPrototype *proto = m_proto;
	if (!proto)
		return reinterpret_cast<Player *>(proto);
	return proto->m_controllingPlayer;
}
