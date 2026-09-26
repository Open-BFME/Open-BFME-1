// cl: /DNDEBUG /MD /EHsc
// readable body of ?restoreOriginalTeam@Object@@QAEXXZ: game/GameEngine/Source/GameLogic/Object/Object.cpp

// The five bodies that answer "whose is this object?":
//
//   restoreOriginalTeam        0x001C4670  put it back on its birth team
//   getIndicatorColor          0x001BE4F0  override colour, else the owner's
//   bfmeIsComputerControlled   0x001BE410  is the owning player an AI?
//   bfmeTransferPowerInfluence 0x001C3710  move this and its passengers between players
//   unidentified_001BFE20      0x001BFE20  forward one query to the contain module
//
// Three fields, and the five files reached them behind four different pads:
//
//   +0x23C  m_team              named by three of them, agreed
//   +0x240  m_originalTeamName  named by restoreOriginalTeam; a blind 4-byte pad
//                               in getIndicatorColor
//   +0x244  m_indicatorColor    named by getIndicatorColor; past the end of every
//                               other file's Object
//
// So the pad getIndicatorColor stepped over is the AsciiString the file next to it
// already had a name for, and that also settles the string's width at four bytes,
// since m_indicatorColor is at +0x244 with nothing between. Object.h's own order
// is m_team, m_originalTeamName, m_indicatorColor -- the same three, in the same
// order, which is a second and independent agreement.
//
// Player had drifted the same way: getIndicatorColor knew only m_color at +0x1C4,
// bfmeIsComputerControlled only m_playerType at +0x2C, each behind its own pad.
// One Player here names both.
//
// Only restoreOriginalTeam's file gave Object a vtable, because only it makes a
// virtual call -- setTeam through `call [edx+0x50]`, which is slot 20. The other
// four had no vptr at all and started their members at offset 0. Both spellings
// happen to put m_team at +0x23C, so nothing broke, but only one of them can be
// retail's: the merged Object has the vptr and every pad is measured from +0x04.
//
// unidentified_001BFE20 tail-jumps the contain module's slot 26 (+0x68) and
// returns whatever comes back. Its row used to say Player*; the image says
// otherwise, and the row now returns PAX -- an opaque pointer. The chain:
//
//   Object's own vtable is at 0x0109EE58 (the constructor at 0x001D29A0 stores it
//   at +0x7E) and has 28 slots -- slot 28 is already not a code pointer, slot 35
//   reads 0x00000358 and slot 84 reads ASCII "Crea". So the thing four other
//   bodies call at +0x8C, +0xA8, +0x150 and +0x1B0 is not an Object.
//
//   HordeContain's ContainModuleInterface sub-object is at +0x20, vtable
//   0x010AF048, at most 88 slots -- so it is not the contain module itself
//   either.
//
//   That vtable's slot 26 goes through ILT 0x00027831 to a 24-byte body at
//   0x00230730: `lea eax,[ecx-0x20]; test eax,eax; je -> xor eax,eax; ret` then
//   `lea eax,[ecx+0xC4]; ret`. A null-guarded SELF-CAST returning this+0xC4,
//   which from the +0x20 sub-object is HordeContain+0xE4.
//
//   That sub-object's vtable (0x010AE8E0) runs to at least 129 entries and holds
//   exactly the slots the callers use. 126 of its 129 entries are one shared
//   abstract stub, so HordeContain leaves them to its subclasses.
//
//   OpenContain's slot 26 points straight at that same stub: the "I am not a
//   horde contain" answer.
//
// So slot 26 hands back a second interface on the same contain module, and it is
// neither a Player nor an Object. The class is called HordeContainInterface in
// this tree's sources because slot 84 takes a Bool and returns a count, but that
// name is a reconstruction, which is why the ROW says PAX and only the source
// says HordeContainInterface.

typedef bool Bool;
typedef unsigned int UnsignedInt;

class Object;

enum DamageType
{
	DAMAGE_UNRESISTABLE = 8
};

enum DeathType
{
	DEATH_NORMAL = 0
};

enum PlayerType
{
	PLAYER_COMPUTER = 0,
	PLAYER_HUMAN = 1
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
private:
	struct SharedBuffer
	{
		unsigned int m_refCount;
		unsigned short m_length;
	};

	SharedBuffer *m_buffer;

public:
	Bool isEmpty() const
	{
		return m_buffer == 0 || m_buffer->m_length == 0;
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Bool isPlayerDead() const;
	void bfmeObjectEnteringInfluence(Object *object);
	void bfmeObjectLeavingInfluence(Object *object);

	PlayerType getPlayerType() const { return m_playerType; }

	unsigned char m_unmodelled_000[0x2c];
	PlayerType m_playerType;			// +0x02C
	unsigned char m_unmodelled_030[0x1c4 - 0x30];
	UnsignedInt m_color;				// +0x1C4
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Player *getControllingPlayer() const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamFactory
{
public:
	Team *findTeam(const AsciiString &name);
};

extern TeamFactory *TheTeamFactory;

// The second interface on the contain module, reached by slot 26's self-cast.
// Only the pointer is needed here; ObjectContainQueries.cpp and
// ObjectDamageAndWeapons.cpp name its slots.
class HordeContainInterface;

// The doubly-linked contained-items list, walked from its sentinel.
struct ObjectListNode
{
	ObjectListNode *next;
	ObjectListNode *previous;
	Object *object;
};

struct ObjectList
{
	ObjectListNode *sentinel;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
class ContainModuleInterface
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0; virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0; virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0; virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0; virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	// slot 26, +0x68 -- the horde-contain self-cast; see the note at the top.
	virtual HordeContainInterface *getHordeContainInterface() = 0;
	virtual void slot27() = 0; virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30() = 0; virtual void slot31() = 0; virtual void slot32() = 0; virtual void slot33() = 0;
	virtual void slot34() = 0; virtual void slot35() = 0; virtual void slot36() = 0; virtual void slot37() = 0;
	virtual void slot38() = 0; virtual void slot39() = 0; virtual void slot40() = 0; virtual void slot41() = 0;
	virtual void slot42() = 0; virtual void slot43() = 0; virtual void slot44() = 0; virtual void slot45() = 0;
	virtual void slot46() = 0; virtual void slot47() = 0; virtual void slot48() = 0; virtual void slot49() = 0;
	virtual void slot50() = 0; virtual void slot51() = 0; virtual void slot52() = 0; virtual void slot53() = 0;
	virtual void slot54() = 0; virtual void slot55() = 0; virtual void slot56() = 0; virtual void slot57() = 0;
	virtual void slot58() = 0; virtual void slot59() = 0; virtual void slot60() = 0; virtual void slot61() = 0;
	virtual void slot62() = 0; virtual void slot63() = 0; virtual void slot64() = 0;
	// slot 65, +0x104
	virtual const ObjectList *getContainedItemsList() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	virtual void bfmeSlot00() = 0;
	virtual void bfmeSlot01() = 0;
	virtual void bfmeSlot02() = 0;
	virtual void bfmeSlot03() = 0;
	virtual void bfmeSlot04() = 0;
	virtual void bfmeSlot05() = 0;
	virtual void bfmeSlot06() = 0;
	virtual void bfmeSlot07() = 0;
	virtual void bfmeSlot08() = 0;
	virtual void bfmeSlot09() = 0;
	virtual void bfmeSlot10() = 0;
	virtual void bfmeSlot11() = 0;
	virtual void bfmeSlot12() = 0;
	virtual void bfmeSlot13() = 0;
	virtual void bfmeSlot14() = 0;
	virtual void bfmeSlot15() = 0;
	virtual void bfmeSlot16() = 0;
	virtual void bfmeSlot17() = 0;
	virtual void bfmeSlot18() = 0;
	virtual void bfmeSlot19() = 0;
	virtual void setTeam(Team *team) = 0;			// slot 20, +0x50

	void restoreOriginalTeam();
	UnsignedInt getIndicatorColor(void) const;
	Bool bfmeIsComputerControlled() const;
	void bfmeTransferPowerInfluence(Player *oldPlayer, Player *newPlayer);
	void *unidentified_001BFE20(void) const;

	Player *getControllingPlayer() const;
	void kill(DamageType damageType, DeathType deathType);

private:
	unsigned char m_unmodelled_004[0x1fc - 4];
	ContainModuleInterface *m_contain;			// +0x1FC
	unsigned char m_unmodelled_200[0x23c - 0x200];
	Team *m_team;						// +0x23C
	AsciiString m_originalTeamName;				// +0x240
	UnsignedInt m_indicatorColor;				// +0x244
};

// ?restoreOriginalTeam@Object@@QAEXXZ
//
// The first half is the surviving Zero Hour routine. BFME adds a safeguard after
// setTeam: if the restored owner is dead, kill the object with unresistable damage
// rather than leave a useful unit under that player.
void Object::restoreOriginalTeam()
{
	if (m_team == 0 || m_originalTeamName.isEmpty())
		return;

	Team *originalTeam = TheTeamFactory->findTeam(m_originalTeamName);
	if (originalTeam == 0)
		return;

	if (m_team == originalTeam)
		return;

	setTeam(originalTeam);

	if (m_team != 0 && m_team->getControllingPlayer() != 0 &&
		getControllingPlayer()->isPlayerDead())
	{
		kill(DAMAGE_UNRESISTABLE, DEATH_NORMAL);
	}
}

// ?getIndicatorColor@Object@@QBEIXZ
//
// One call, three ways out. The override at +0x244 wins outright when it is
// non-zero; otherwise the owner's colour; anything missing on that path falls to
// opaque black.
UnsignedInt Object::getIndicatorColor(void) const
{
	if (m_indicatorColor)
		return m_indicatorColor;

	if (m_team)
	{
		Player *player = m_team->getControllingPlayer();

		if (player)
			return player->m_color;
	}

	return 0xFF000000;
}

// ?bfmeIsComputerControlled@Object@@QBE_NXZ
//
// The retail spelling is unrecovered. The three Pathfinder callers use this query
// to enable their computer-player pathfinding behaviour.
Bool Object::bfmeIsComputerControlled() const
{
	if (m_team != 0)
	{
		Player *player = m_team->getControllingPlayer();
		if (player != 0)
			return player->getPlayerType() == PLAYER_COMPUTER;
	}

	return false;
}

// ?bfmeTransferPowerInfluence@Object@@QAEXPAVPlayer@@0@Z
//
// Hand this object over, then every object it contains, recursively.
void Object::bfmeTransferPowerInfluence(Player *oldPlayer, Player *newPlayer)
{
	if (!oldPlayer || !newPlayer)
		return;

	oldPlayer->bfmeObjectLeavingInfluence(this);
	newPlayer->bfmeObjectEnteringInfluence(this);

	ContainModuleInterface *contain = m_contain;
	if (contain)
	{
		const ObjectList *items = contain->getContainedItemsList();
		for (ObjectListNode *node = items->sentinel->next;
		     node != items->sentinel;
		     node = node->next)
		{
			if (node->object)
				node->object->bfmeTransferPowerInfluence(oldPlayer, newPlayer);
		}
	}
}

// ?unidentified_001BFE20@Object@@QBEPAXXZ
//
// Read the module once into a local. Testing the member and then calling through
// it again loads it twice, into eax and then ecx; retail loads it straight into
// ecx and tests that.
//
// ScriptActions::doUnitReceiveUpgrade (0x002FE070) shows what callers do with the
// result: it calls slot 42 (+0xA8) with an UpgradeTemplate's index field at +0x20
// and, when that answers false, slot 43 (+0xAC) with the template pointer itself
// -- a hasUpgrade/giveUpgrade pair on the returned interface.
void *Object::unidentified_001BFE20(void) const
{
	ContainModuleInterface *contain = m_contain;

	if (contain == 0)
		return 0;

	return contain->getHordeContainInterface();
}
