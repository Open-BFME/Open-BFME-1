// ?bfmeAskBIC@BfmeSubBIC@@QAEHXZ
// partial score=0.35 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// The BfmeThingBXF family reaches this 376-byte helper through the
// BfmeSubBIC::bfmeAskBIC member ABI.  Retail's complete boundary is
// 0x001CABE0..0x001CAFF8; the final ret is at +0x177 and padding starts at
// +0x178.  The member views below are TU-scoped and keep the recovered retail
// offsets visible without inventing a second production alias.

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum NameKeyType
{
	NameKeyTypeDummy = 0
};

enum Relationship
{
	RelationshipEnemy = 2
};

class Player;
class Team;
class Module;

class NameKeyGenerator
{
public:
	int nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class ThingTemplate
{
public:
	ThingTemplate *getFinalOverride();

	void *m_vtable;
	ThingTemplate *m_override;
	unsigned char m_pad08[0xc8];
	UnsignedInt m_kindOf;
};

class Object
{
public:
	Module *findModule(NameKeyType key) const;
};

class Team
{
public:
	Player *getControllingPlayer() const;
};

class Player
{
public:
	Relationship getRelationship(const Team *team) const;

	unsigned char m_pad00[0x1c4];
	UnsignedInt m_color;
	unsigned char m_pad1c8[0x68];
	Team *m_defaultTeam;
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
	Player *getNthPlayer(int index);
};

extern PlayerList *ThePlayerList;

class StealthUpdate
{
public:
	unsigned char m_pad00[0x34];
	int m_disguisedPlayerIndex;
	int m_active;
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
	virtual Player *getApparentPlayer(Player *localPlayer) = 0;
};

class BfmeSubBIC
{
public:
	virtual void slot00();
	int bfmeAskBIC();

	ThingTemplate *m_template;
	unsigned char m_pad08[0x1f4];
	ContainModuleInterface *m_contain;
	unsigned char m_pad200[0x3c];
	Team *m_team;
	UnsignedInt m_originalTeamName;
	UnsignedInt m_indicatorColor;
};

int __stdcall bfmeGoBIC(BfmeSubBIC *sub)
{
	if (sub == 0)
		return -1;
	return sub->bfmeAskBIC();
}

int BfmeSubBIC::bfmeAskBIC()
{
	Player *localPlayer = ThePlayerList->m_localPlayer;
	Player *controller = m_team ? m_team->getControllingPlayer() : 0;
	Player *colorPlayer = controller;
	Bool useDefaultColor = true;

	ThingTemplate *thing = m_template;
	if (thing != 0)
	{
		if (thing->m_override != 0)
			thing = thing->m_override->getFinalOverride();

		if ((thing->m_kindOf & 0x00800000) != 0)
		{
			static NameKeyType key_StealthUpdate =
				(NameKeyType)TheNameKeyGenerator->nameToKey("StealthUpdate");
			StealthUpdate *stealth = (StealthUpdate *)
				reinterpret_cast<Object *>(this)->findModule(key_StealthUpdate);

			if (stealth != 0 && stealth->m_active != 0 &&
				controller != 0 && localPlayer != 0 &&
				controller->getRelationship(localPlayer->m_defaultTeam) !=
					RelationshipEnemy &&
				reinterpret_cast<Rva000DF7F0Player *>(localPlayer)->active())
			{
				colorPlayer = ThePlayerList->getNthPlayer(
					stealth->m_disguisedPlayerIndex);
				if (colorPlayer != 0)
					useDefaultColor = false;
			}
		}
	}

	if (m_contain != 0)
	{
		Player *containedPlayer = m_contain->getApparentPlayer(localPlayer);
		if (containedPlayer != 0)
			return containedPlayer->m_color;
	}

	if (!useDefaultColor && colorPlayer != 0)
		return colorPlayer->m_color;

	if (m_indicatorColor != 0)
		return m_indicatorColor;

	if (m_team != 0)
	{
		Player *player = m_team->getControllingPlayer();
		if (player != 0)
			return player->m_color;
	}

	return 0xff000000;
}

#pragma comment(linker, "/alternatename:?getControllingPlayer@Team@@QBEPAVPlayer@@XZ=?j_0002369b@@YAXXZ")
#pragma comment(linker, "/alternatename:?getFinalOverride@ThingTemplate@@QAEPAV1@XZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?findModule@Object@@IBEPAVModule@@W4NameKeyType@@@Z=?j_0002ae23@@YAXXZ")
#pragma comment(linker, "/alternatename:?getRelationship@Player@@QBE?AW4Relationship@@PBVTeam@@@Z=?j_0003e77a@@YAXXZ")
#pragma comment(linker, "/alternatename:?active@Rva000DF7F0Player@@QBE_NXZ=?j_000179bd@@YAXXZ")
#pragma comment(linker, "/alternatename:?getNthPlayer@PlayerList@@QAEPAVPlayer@@H@Z=?j_00044f30@@YAXXZ")
#pragma comment(linker, "/alternatename:?nameToKey@NameKeyGenerator@@QAEHPBD@Z=?j_0003add7@@YAXXZ")
