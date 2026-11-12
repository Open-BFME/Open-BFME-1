// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// readable body of ?becomingLocalPlayer@Player@@: game/GameEngine/Source/Common/RTS/Player.cpp
//
// Player::becomingLocalPlayer at retail 0x000D77B0 (748 B, RET 4 at +0x2E9).
//
// BFME 1 identity: ilt_oracle CONFIRMS ?becomingLocalPlayer@Player@@QAEX_N@Z at
// this body (ILT slot 0x00018CB4), and the matched PlayerList::setLocalPlayer
// (0x000DF3C0) calls that thunk twice with ECX = a Player and one bool.
//
// Semantics come from Zero Hour's Player.cpp body; the BFME shape follows the
// Open BFME 2 donor Code/GameEngine/Source/Common/RTS/PlayerBecomingLocal.cpp
// (donor revision 76f0baefa6): the GameClient pointer is cached, objects come
// from the partition manager's one-word refcounted result (the same
// BfmeResultA view as the matched Player::garrisonAllUnits), a
// SpecialDisguiseUpdate notification precedes the disguise-colour pass, and
// there is no final ControlBar dirty call. BFME 1 differs from the donor in
// its offsets, all read from the retail body: Player colour +0x1C4, night
// colour +0x1C8, observer +0x296, dead +0x680; Object contain +0x1FC, team
// +0x23C, the disguiser bit 0x800 of +0x130, drawable at virtual slot 10; the
// template disguise bit 0x800000 of +0xD0; StealthUpdate player index +0x34
// and disguise flag +0x38; GlobalData time of day +0x218. The first
// relationship test inlines isPlayerActive's two flag reads; the second calls
// the matched Player::isPlayerActive.
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum Relationship { ENEMIES = 0, NEUTRAL = 1, ALLIES = 2 };
enum { TIME_OF_DAY_NIGHT = 4 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;
#define NAMEKEY(x) TheNameKeyGenerator->nameToKey(x)

struct RGBColor
{
	Real red, green, blue;
	void setFromInt(Int color);
};

// Pads a class's virtual table to N leading slots.
template <int N> class PlayerLocalSlots : public PlayerLocalSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]) = 0;
};
template <> class PlayerLocalSlots<0> {};

class GameClient : public PlayerLocalSlots<27>
{
public:
	virtual void setTeamColor(Int red, Int green, Int blue) = 0;	// +0x6C
};
extern GameClient *TheGameClient;

class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}
	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_unreconstructed08[0xd0 - 0x08];
	UnsignedInt m_kindOfWord0D0;	// bit 0x800000: disguised drawable colour
};

class Team;
class Module;

class Drawable
{
public:
	void setIndicatorColor(UnsignedInt color);
};

class ContainModuleInterface : public PlayerLocalSlots<16>
{
public:
	virtual void recalcApparentControllingPlayer() = 0;	// +0x40
};

class StealthUpdate
{
public:
	unsigned char m_unreconstructed00[0x34];
	Int m_disguisedPlayerIndex;
	UnsignedInt m_disguised;
};

class SpecialDisguiseUpdate
{
public:
	void changeVisualDisguise(Bool yes);
};

class ObjectVirtuals : public PlayerLocalSlots<10>
{
public:
	virtual Drawable *getDrawable() = 0;	// +0x28
};

class Object : public ObjectVirtuals
{
public:
	const ThingTemplate *getTemplate() const
	{
		if (m_template == 0)
			return 0;
		return (const ThingTemplate *)m_template->getFinalOverride();
	}
	const Team *getTeam() const { return m_team; }
	Module *findModule(NameKeyType key) const;
	UnsignedInt getIndicatorColor() const;
	Int getNightIndicatorColor() const;

	Overridable *m_template;
	unsigned char m_unreconstructed08[0x130 - 0x08];
	UnsignedInt m_kindOfWord130;	// bit 0x800: has a SpecialDisguiseUpdate
	unsigned char m_unreconstructed134[0x1fc - 0x134];
	ContainModuleInterface *m_contain;
	unsigned char m_unreconstructed200[0x23c - 0x200];
	Team *m_team;
};

class Radar
{
public:
	void removeObject(Object *obj);
	void addObject(Object *obj);
};
extern Radar *TheRadar;

class Player;
class PlayerList
{
public:
	Player *getNthPlayer(Int index);
};
extern PlayerList *ThePlayerList;

class GlobalData
{
public:
	unsigned char m_unreconstructed000[0x218];
	Int m_timeOfDay;
};
extern GlobalData *TheWritableGlobalData;

struct BfmeResultEntry
{
	Object *m_object;
	UnsignedInt m_word04;
};

struct BfmeResultData
{
	std::vector<BfmeResultEntry> m_entries;
	BfmeResultEntry *m_current;
	Int m_references;
};

struct BfmeResultA
{
	BfmeResultData *m_value;

	BfmeResultA();
	BfmeResultA(const BfmeResultA &that);
	~BfmeResultA()
	{
		if (--m_value->m_references == 0)
			delete m_value;
	}

	Object *next()
	{
		if (m_value->m_current == m_value->m_entries.end())
			return 0;
		return (m_value->m_current++)->m_object;
	}
};

class BfmeResultForwardA
{
public:
	BfmeResultA bfmeForwardResultA();
};

class PartitionManager;
extern PartitionManager *ThePartitionManager;

class Player
{
public:
	void becomingLocalPlayer(Bool yes);
	Relationship getRelationship(const Team *team) const;
	Bool isPlayerActive() const;

	unsigned char m_unreconstructed000[0x1c4];
	Int m_color;
	Int m_nightColor;
	unsigned char m_unreconstructed1CC[0x296 - 0x1cc];
	Bool m_observer;
	unsigned char m_unreconstructed297[0x680 - 0x297];
	Bool m_isPlayerDead;
};

// ?becomingLocalPlayer@Player@@QAEX_N@Z
void Player::becomingLocalPlayer(Bool yes)
{
	if (yes)
	{
		// This changes the color of the little dot on the upper right side of the screen indicating
		// which team is under control.
		GameClient *client = TheGameClient;
		if (client)
		{
			RGBColor rgb;
			rgb.setFromInt(m_color);
			client->setTeamColor((Int)(rgb.red * 255), (Int)(rgb.green * 255), (Int)(rgb.blue * 255));
		}

		if (ThePartitionManager)
		{
			BfmeResultA iter = ((BfmeResultForwardA *)ThePartitionManager)->bfmeForwardResultA();
			Object *object;
			while ((object = iter.next()) != 0)
			{
				// Added support for updating the perceptions of garrisoned buildings containing enemy stealth units.
				// When changing teams, it is necessary to update this information.
				ContainModuleInterface *contain = object->m_contain;
				if (contain)
				{
					contain->recalcApparentControllingPlayer();
					TheRadar->removeObject(object);
					TheRadar->addObject(object);
				}

				if (object->m_kindOfWord130 & 0x800)
				{
					static NameKeyType key_SpecialDisguiseUpdate = NAMEKEY("SpecialDisguiseUpdate");
					SpecialDisguiseUpdate *disguise = (SpecialDisguiseUpdate *)object->findModule(key_SpecialDisguiseUpdate);
					if (disguise)
						disguise->changeVisualDisguise(getRelationship(object->getTeam()) == ALLIES && !m_observer && !m_isPlayerDead);
				}

				//KM -- August 2002:
				//Added support for disguised objects, based on relationships, we either show the real color or the disguised color.
				if (object->getTemplate()->m_kindOfWord0D0 & 0x800000)
				{
					Drawable *draw = object->getDrawable();
					if (draw)
					{
						static NameKeyType key_StealthUpdate = NAMEKEY("StealthUpdate");
						StealthUpdate *update = (StealthUpdate *)object->findModule(key_StealthUpdate);
						if (update && update->m_disguised)
						{
							Int index = update->m_disguisedPlayerIndex;
							Player *disguisedPlayer = ThePlayerList->getNthPlayer(index);
							if (getRelationship(object->getTeam()) != ALLIES && isPlayerActive())
							{
								//Neutrals and enemies will see this disguised unit as the team it's disguised as.
								if (TheWritableGlobalData->m_timeOfDay == TIME_OF_DAY_NIGHT)
									draw->setIndicatorColor(disguisedPlayer->m_nightColor);
								else
									draw->setIndicatorColor(disguisedPlayer->m_color);
							}
							else
							{
								//Otherwise, the color will show up as the team it really belongs to.
								if (TheWritableGlobalData->m_timeOfDay == TIME_OF_DAY_NIGHT)
									draw->setIndicatorColor(object->getNightIndicatorColor());
								else
									draw->setIndicatorColor(object->getIndicatorColor());
							}
							TheRadar->removeObject(object);
							TheRadar->addObject(object);
						}
					}
				}
			}
		}
	}
}
