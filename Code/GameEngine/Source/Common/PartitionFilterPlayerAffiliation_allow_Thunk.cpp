// cl: /DNDEBUG /MD /EHsc
// Lift the PartitionFilterPlayerAffiliation::allow __emit thunk to clean C++.
//
// Zero Hour's PartitionManager.h declares this filter with exactly the members
// retail uses -- m_player, m_match, m_affiliation -- and they land on the retail
// offsets +0x08/+0x0C/+0x10 in declaration order. The AllowPlayerRelationship
// values from PlayerList.h also match the retail bit tests one for one:
// ENEMIES tests 0x04, NEUTRAL tests 0x08, ALLIES tests 0x02.

class Team;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};

enum AllowPlayerRelationship
{
	ALLOW_SAME_PLAYER	= 0x01,
	ALLOW_ALLIES		= 0x02,
	ALLOW_ENEMIES		= 0x04,
	ALLOW_NEUTRAL		= 0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Relationship getRelationship(const Team *that) const;	///< pinned at 0x0003E77A
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Team *getTeam(void) const { return m_team; }

private:
	unsigned char m_unreconstructed_00[0x23C];
	Team *m_team;											///< retail this+0x23C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionFilterPlayerAffiliation
{
protected:
	virtual bool allow(Object *);

private:
	unsigned char m_unreconstructed_04[0x08 - 4];			///< vtable slot then unpinned base bytes
	const Player *m_player;									///< retail this+0x08
	bool m_match;											///< retail this+0x0C
	unsigned int m_affiliation;								///< retail this+0x10
};

// ?allow@PartitionFilterPlayerAffiliation@@MAE_NPAVObject@@@Z
bool PartitionFilterPlayerAffiliation::allow(Object *other)
{
	switch (m_player->getRelationship(other->getTeam()))
	{
		case ENEMIES:
			if (m_affiliation & ALLOW_ENEMIES)
				return m_match;
			break;

		case NEUTRAL:
			if (m_affiliation & ALLOW_NEUTRAL)
				return m_match;
			break;

		case ALLIES:
			if (m_affiliation & ALLOW_ALLIES)
				return m_match;
			break;
	}

	return !m_match;
}
