// cl: /DNDEBUG /MD /EHsc
// readable body of ?getTeamTargetObject@Team@@QAEPAVObject@@XZ: Code/GameEngine/Source/Common/RTS/Team.cpp
// readable body of ?setTeamTargetObject@Team@@QAEXPBVObject@@@Z: Code/GameEngine/Source/Common/RTS/Team.cpp

// The team's common attack target at Team+0xE8: the setter that stores an
// object id there and the getter that resolves it back.
//
// Zero Hour's two bodies. Only computer players above easy difficulty store a
// target, and reading one back drops it if the object is stealthed to the
// team's own player, is flagged at Object+0x344, or has been put inside
// something -- and clears the slot when the object is gone entirely.
//
// Both walk the same two hops to the owning player, Team+0x04 to the prototype
// and Prototype+0x08 to the player, which is why they now share
// getControllingPlayer rather than each open-coding it. The single Object slice
// below carries the four offsets they need between them: the id at +0x74, the
// container at +0x214 and the flag at +0x344.

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	GameDifficulty getPlayerDifficulty() const;
	PlayerType getPlayerType() const { return m_playerType; }

private:
	char m_pad[0x2C];
	PlayerType m_playerType;				// +0x2c
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	char m_pad[8];
	Player *m_owningPlayer;					// +8
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	bool isStealthedAndUndetected(const Object *viewer) const;
	unsigned int getID() const { return m_id; }

	char m_pad0[0x74];
	unsigned int m_id;					// +0x74
	char m_pad1[0x214 - 0x78];
	void *m_containedBy;					// +0x214
	char m_pad2[0x344 - 0x218];
	unsigned char m_flag344;				// +0x344
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(int id);
};

extern GameLogic *TheBfmeGameLogic;				// retail [0x012F0898]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Object *getTeamTargetObject();
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

// ?getTeamTargetObject@Team@@QAEPAVObject@@XZ
Object *Team::getTeamTargetObject()
{
	if (m_commonAttackTarget == 0)
		return 0;

	Object *target = TheBfmeGameLogic->findObjectByID(m_commonAttackTarget);
	if (target)
	{
		Player *viewer = getControllingPlayer();
		if (target->isStealthedAndUndetected((const Object *)viewer))
			target = 0;
		else if (target->m_flag344 & 1)
			target = 0;
		else if (target->m_containedBy)
			target = 0;
		else
			return target;
	}
	m_commonAttackTarget = 0;
	return target;
}

// ?setTeamTargetObject@Team@@QAEXPBVObject@@@Z
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
