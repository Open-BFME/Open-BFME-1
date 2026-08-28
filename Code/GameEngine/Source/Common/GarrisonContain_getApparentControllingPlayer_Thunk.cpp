// cl: /DNDEBUG /MD /EHsc
// readable body of ?getApparentControllingPlayer@GarrisonContain@@UBEPBVPlayer@@PBV2@@Z: Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain.cpp

// BFME GarrisonContain::getApparentControllingPlayer, 0x0021E340.
//
// Zero Hour's body is already the right shape; what this TU has to reproduce is
// where the module subobject sits. The method is entered on the contain
// interface subobject, and every displacement in the retail bytes is measured
// off that pointer: m_obj at -0x18, m_originalTeam at +0xb4, and the
// hide-from-nonallies flag at +0x995. With ObjectModule::m_obj at object+0x08
// (named in 160d00ada) the -0x18 puts that subobject at object+0x20, which is
// what the padding below encodes. getObject() is a real inline member for the
// reason that commit records: the adjustment has to belong to the accessor.
//
// getDefaultTeam is inline too - retail reads [eax+0x230] at the call site
// rather than calling anything.

enum Relationship { ENEMIES = 0, NEUTRAL = 1, ALLIES = 2 };

class Team;
class Player;
class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Relationship getRelationship(const Team *that) const;
	Team *getDefaultTeam() const { return m_defaultTeam; }

private:
	char m_pad[0x230];
	Team *m_defaultTeam;			// +0x230
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Player *getControllingPlayer() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	virtual ~ObjectModule();

	Object *getObject() const { return m_obj; }

protected:
	void *m_moduleData;				// +0x04
	Object *m_obj;					// +0x08
};

// Carries the primary chain out to 0x20 so the contain interface lands there.
class GarrisonContainPrimary : public ObjectModule
{
protected:
	char m_pad[0x20 - 0x0c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
class ContainModuleInterface
{
public:
	virtual const Player *getApparentControllingPlayer(const Player *observingPlayer) const = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/GarrisonContain.h
class GarrisonContain : public GarrisonContainPrimary, public ContainModuleInterface
{
public:
	virtual const Player *getApparentControllingPlayer(const Player *observingPlayer) const;

private:
	char m_pad2[0xd4 - 0x24];
	Team *m_originalTeam;			// subobject +0xb4
	char m_pad3[0x9b5 - 0xd8];
	bool m_hideGarrisonedStateFromNonallies;	// subobject +0x995
};

const Player *GarrisonContain::getApparentControllingPlayer(const Player *observingPlayer) const
{
	const Player *myPlayer = getObject()->getControllingPlayer();

	if (m_hideGarrisonedStateFromNonallies && m_originalTeam && myPlayer && observingPlayer)
	{
		Relationship r = myPlayer->getRelationship(observingPlayer->getDefaultTeam());
		if (r != ALLIES)
			return m_originalTeam->getControllingPlayer();
	}
	return myPlayer;
}
