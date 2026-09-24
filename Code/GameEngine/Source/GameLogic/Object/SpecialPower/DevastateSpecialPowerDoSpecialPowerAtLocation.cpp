// cl: /DNDEBUG /MD
//
// DevastateSpecialPowerInterface::doSpecialPowerAtLocation, retail RVA 0x0025A9D0.
//
// Identity: ??0DevastateSpecialPower@@ (matched, 0x0025A7C0) stores vftable
// 0x010B4608 at object offset +0x10, and this body is that table's slot 13 --
// the slot whose shared base body is the matched
// SpecialPowerModuleInterface::doSpecialPowerAtLocation at 0x0026A620, which
// this override chains to through ILT 0x000170DA.  `this` is the interface
// sub-object: -0xc reaches the module data and -8 the object, exactly as in
// the sibling TaintSpecialPowerInterface override at 0x0026BF40.
//
// The override refuses while the object is disabled or without a location,
// runs the base implementation, then drains the terrain query at 0x001A62D0
// for affected things.  For each one it fires the module data's FXList,
// converts the thing into a bounty scaled by the player's multiplier and, in
// a multiplayer or skirmish game, by a global per-player-count factor, and
// accumulates the result.  The total is clamped to the module data's cap and
// deposited.
//
// Two shapes in here are load-bearing and were what took the old 0.93 bank
// from 460 bytes to the exact 458:
//
//   * the per-thing call at 0x001AE4A0 is reached with TheTerrainLogic in ecx.
//     Spelling it as the free __stdcall the ledger row carries drops that load
//     and costs six bytes, so this TU views it as a receiver-taking method and
//     keeps the address in the name rather than asserting an owner.
//   * the bounty accumulation sits INSIDE the reward > 0 test, and the cap is
//     applied by a min that returns a reference.  With the accumulation hoisted
//     out, retail's shared fld/__ftol2 tail and its `lea` of whichever operand
//     wins the comparison both disappear.

typedef unsigned int UnsignedInt;

class Coord3D;
class Matrix3D;
class BfmeX1035;

#define OBJECT_TU_MEMBERS \
	class Player *getControllingPlayer() const;
#include "../object.h"

class Money
{
public:
	void deposit(UnsignedInt amount, bool playSound);
};

// 0x000E8B20, the counter the score keeper sub-object at +0x348 carries.
class Gen_000E8AF0
{
public:
	void bfmeAddCount(int amount);
};

// 0x000C97C0 and 0x000C9710 both take the player in ecx; the latter already
// carries the thiscall spelling Player::getSupplyBoxValue beside its
// address-derived ICF alias.
class Player
{
public:
	unsigned int getSupplyBoxValue();

	Money *getMoney() const
	{
		return (Money *)((char *)this + 0x48);
	}

	Gen_000E8AF0 *getScoreKeeper() const
	{
		return (Gen_000E8AF0 *)((char *)this + 0x348);
	}
};

class Rva000C97C0Player
{
public:
	int adjustBountyForLivingWorld(int amount);
};

class SpecialPowerModuleInterface
{
public:
	void doSpecialPowerAtLocation(const Coord3D *loc, UnsignedInt commandOptions);
};

class BfmeA1275
{
public:
	int bfmeGo1275(int a1, int a2, int a3, int a4);
};

struct TerrainLogicP48Rec;

class TerrainLogicP48Owner
{
public:
	int onMatch(TerrainLogicP48Rec *rec, int value);
};

// The global at VA 0x012EF4CC. The ledger already carries three address-derived
// owner spellings for it; this TU only needs the scratch field and the two
// receiver-taking calls above plus 0x001AE4A0.
class Rva012EF4CCTerrain
{
public:
	void rva001AE4A0(BfmeX1035 *thing, int value);

	char m_pad00[0x18f8];
	float m_queryScratch;
};

class FXList
{
public:
	bool bfmeIsBlocked();
	void doFXPos(const Coord3D *pos, const Matrix3D *transform, float scale,
		const Coord3D *other) const;
};

// 0x00083240 reads an indexed float out of the global data block at +0xee0.
class Gen_00083240
{
public:
	float bfmeGet0(int index) const;
};

class GameLogicPortraitShim
{
public:
	bool isInMultiplayerOrSkirmishGame();
};

class PlayerList
{
public:
	int unidentified_000df510(bool includeFields);
};

class DevastateSpecialPowerModuleData
{
public:
	char m_pad00[0x210];
	int m_queryKind;
	FXList *m_fx;
	float m_bountyScale;
	float m_bountyCap;
};

class DevastateSpecialPowerInterface
{
public:
	void doSpecialPowerAtLocation(const Coord3D *target,
		UnsignedInt commandOptions);

	Object *getObject()
	{
		return *(Object **)((char *)this - 8);
	}

	DevastateSpecialPowerModuleData *getModuleData()
	{
		return *(DevastateSpecialPowerModuleData **)((char *)this - 0xc);
	}
};

extern Rva012EF4CCTerrain *TheTerrainLogic;
extern GameLogicPortraitShim *TheGameLogic;
extern PlayerList *ThePlayerList;
extern char *TheWritableGlobalData;

#pragma comment(linker, "/alternatename:?bfmeGo1275@BfmeA1275@@QAEHHHHH@Z=?j_000226ab@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva001AE4A0@Rva012EF4CCTerrain@@QAEXPAVBfmeX1035@@H@Z=?j_0001acbc@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeIsBlocked@FXList@@QAE_NXZ=?j_00011f77@@YAXXZ")
#pragma comment(linker, "/alternatename:?doFXPos@FXList@@QBEXPBVCoord3D@@PBVMatrix3D@@M0@Z=?j_0001bb21@@YAXXZ")
#pragma comment(linker, "/alternatename:?onMatch@TerrainLogicP48Owner@@QAEHPAUTerrainLogicP48Rec@@H@Z=?j_00003166@@YAXXZ")
#pragma comment(linker, "/alternatename:?isInMultiplayerOrSkirmishGame@GameLogicPortraitShim@@QAE_NXZ=?j_0001e0ab@@YAXXZ")
#pragma comment(linker, "/alternatename:?unidentified_000df510@PlayerList@@QAEH_N@Z=?j_000389f6@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeGet0@Gen_00083240@@QBEMH@Z=?j_00009e12@@YAXXZ")
#pragma comment(linker, "/alternatename:?adjustBountyForLivingWorld@Rva000C97C0Player@@QAEHH@Z=?j_00024938@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeAddCount@Gen_000E8AF0@@QAEXH@Z=?j_0003a45e@@YAXXZ")
#pragma comment(linker, "/alternatename:?getControllingPlayer@Object@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?doSpecialPowerAtLocation@SpecialPowerModuleInterface@@QAEXPBVCoord3D@@I@Z=?j_000170da@@YAXXZ")
#pragma comment(linker, "/alternatename:?deposit@Money@@QAEXI_N@Z=?j_00027d6d@@YAXXZ")

template<class T> inline const T &devastateMin(const T &a, const T &b)
{
	return a < b ? a : b;
}

void DevastateSpecialPowerInterface::doSpecialPowerAtLocation(const Coord3D *target,
	UnsignedInt commandOptions)
{
	float money;
	Object *owner = getObject();
	Player *player;

	if (owner->m_disabledMask != 0)
		return;

	if (target == 0)
		return;

	player = owner->getControllingPlayer();

	if (player == 0)
		return;

	((SpecialPowerModuleInterface *)this)->doSpecialPowerAtLocation(target,
		commandOptions);

	DevastateSpecialPowerModuleData *data = getModuleData();
	money = 0.0f;
	TheTerrainLogic->m_queryScratch = 0.1f;

	BfmeX1035 *thing = (BfmeX1035 *)((BfmeA1275 *)TheTerrainLogic)->bfmeGo1275(
		(int)target, data->m_queryKind, 0, 2);

	while (thing != 0)
	{
		if (*(unsigned char *)((char *)thing + 0x18) == 0)
			TheTerrainLogic->rva001AE4A0(thing, (int)target);

		FXList *fx = data->m_fx;

		if (fx != 0 && !fx->bfmeIsBlocked())
			fx->doFXPos((const Coord3D *)thing, 0, 0.0f, 0);

		UnsignedInt amount = (UnsignedInt)((TerrainLogicP48Owner *)TheTerrainLogic)->onMatch(
			(TerrainLogicP48Rec *)thing, 0x1869f);
		UnsignedInt scale = (UnsignedInt)player->getSupplyBoxValue();
		float reward = (float)(amount * scale);

		if (reward > 0.0f)
		{
			if (TheGameLogic->isInMultiplayerOrSkirmishGame())
			{
				int playerCount = ThePlayerList->unidentified_000df510(false);
				float factor = ((Gen_00083240 *)(TheWritableGlobalData + 0xee0))->bfmeGet0(playerCount);
				reward *= factor;
			}

			money += (float)((Rva000C97C0Player *)player)->adjustBountyForLivingWorld((int)reward)
				* data->m_bountyScale;
		}

		thing = (BfmeX1035 *)((BfmeA1275 *)TheTerrainLogic)->bfmeGo1275(
			(int)target, data->m_queryKind, 0, 2);
	}

	TheTerrainLogic->m_queryScratch = 0.0f;

	int deposit = (int)devastateMin(money, data->m_bountyCap);

	player->getMoney()->deposit(deposit, true);
	player->getScoreKeeper()->bfmeAddCount(deposit);
}
