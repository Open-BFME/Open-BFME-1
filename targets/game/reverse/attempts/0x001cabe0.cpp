// ?bfmeAskBIC@BfmeSubBIC@@QAEHXZ
// partial score=1.0 date=2026-11-10
// cl: /DNDEBUG /MD /EHsc
// ?bfmeAskBIC@BfmeSubBIC@@QAEHXZ
// candidate (wf 001cabe0): Zero Hour Radar::addObject colour-selection shape

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum NameKeyType
{
	NameKeyTypeDummy = 0
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES,
	// Compatibility spelling for the canonical ALLIES value.
	RelationshipEnemy = ALLIES
};

class Player;
class Team;
class Module;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class ThingTemplate
{
public:
	ThingTemplate *getFinalOverride();

	void *m_vtable;
	ThingTemplate *m_override;
	unsigned char m_pad08[0xc0];
	UnsignedInt m_kindOf[3];
};

#define OBJECT_TU_MEMBERS public: Module *findModule(NameKeyType key) const;
#include "../../../../game/GameEngine/Source/GameLogic/Object/object.h"

class Team
{
public:
	Player *getControllingPlayer() const;
};

class Player
{
public:
	Relationship getRelationship(const Team *team) const;
	int getPlayerColor() const { return m_color; }

	unsigned char m_pad00[0x1c4];
	int m_color;
	unsigned char m_pad1c8[0x68];
	Team *m_defaultTeam;
	const Team *getDefaultTeam() const { return m_defaultTeam; }
};

class Rva000DF7F0Player : public Player
{
public:
	Bool active() const;
};

class PlayerList
{
public:
	unsigned char m_pad00[0xc];
	Player *m_localPlayer;
	Player *getLocalPlayer() { return m_localPlayer; }
	Player *getNthPlayer(int index);
};

extern PlayerList *ThePlayerList;

class StealthUpdate
{
public:
	unsigned char m_pad00[0x34];
	int m_disguisedPlayerIndex;
	const ThingTemplate *m_active;

	int getDisguisedPlayerIndex() const { return m_disguisedPlayerIndex; }
};

class ContainModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual const Player *getApparentPlayer(const Player *localPlayer) const = 0;
};

class BfmeSubBIC
{
public:
	virtual void slot00();
	int bfmeAskBIC();
	ContainModuleInterface *getContain() const { return m_contain; }

	ThingTemplate *m_template;
	unsigned char m_pad08[0x1f4];
	ContainModuleInterface *m_contain;
	unsigned char m_pad200[0x3c];
	Team *m_team;
	UnsignedInt m_originalTeamName;
	int m_indicatorColor;
};

// ?bfmeAskBIC@BfmeSubBIC@@QAEHXZ
int BfmeSubBIC::bfmeAskBIC()
{
	const Player *localPlayer = ThePlayerList->getLocalPlayer();
	const Player *controller = m_team ? m_team->getControllingPlayer() : 0;
	const Player *colorPlayer = controller;
	Bool useDefaultColor = true;

	ThingTemplate *thing = m_template;
	if (thing != 0 && thing->m_override != 0)
		thing = thing->m_override->getFinalOverride();

	if ((thing->m_kindOf[2] & 0x00800000) != 0)
	{
		static NameKeyType key_StealthUpdate =
			(NameKeyType)TheNameKeyGenerator->nameToKey("StealthUpdate");
		StealthUpdate *stealth = (StealthUpdate *)
			reinterpret_cast<Object *>(this)->findModule(key_StealthUpdate);

		if (stealth != 0 && stealth->m_active != 0 &&
			controller != 0 && localPlayer != 0 &&
			controller->getRelationship(localPlayer->getDefaultTeam()) !=
				RelationshipEnemy &&
			reinterpret_cast<const Rva000DF7F0Player *>(localPlayer)->active())
		{
			colorPlayer = ThePlayerList->getNthPlayer(
				stealth->getDisguisedPlayerIndex());
			if (colorPlayer != 0)
				useDefaultColor = false;
		}
	}

	if (getContain() != 0)
	{
		colorPlayer = getContain()->getApparentPlayer(localPlayer);
		if (colorPlayer != 0)
			useDefaultColor = false;
	}

	if (useDefaultColor || colorPlayer == 0)
	{
		if (m_indicatorColor != 0)
			return m_indicatorColor;

		if (m_team != 0)
		{
			const Player *player = m_team->getControllingPlayer();
			if (player != 0)
				return player->getPlayerColor();
		}

		return 0xff000000;
	}

	return colorPlayer->getPlayerColor();
}
