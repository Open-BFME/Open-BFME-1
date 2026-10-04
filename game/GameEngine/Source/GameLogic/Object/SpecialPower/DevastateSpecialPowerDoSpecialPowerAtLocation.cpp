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
class GlobalData;

#define OBJECT_TU_MEMBERS
#include "../object.h"

class Money
{
public:
	void deposit(UnsignedInt amount, bool playSound);
};

// 0x00027D6D is the five-byte tail jump the ledger records against
// Rva00027D6DMoney::unidentified_00027d6d (defined in
// game/GameEngine/Source/Common/RTS/MoneyDepositILT.cpp, route=0x000C8730).
// That name, not a `j_` spelling, is the address retail called through here, so
// this TU names the same thunk and calls it directly.
class Rva00027D6DMoney
{
public:
	void unidentified_00027d6d(UnsignedInt amount, bool playSound);
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

class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;

static __forceinline Rva012EF4CCTerrain *localTerrainLogic()
{
	return (Rva012EF4CCTerrain *)TheTerrainLogic;
}

// The retail global at 0x012F0898 is EA's `GameLogic *TheGameLogic`, defined
// once in game/GameEngine/Source/GameLogic/System/GameLogic.cpp. The method
// below is reached through this TU's GameLogicPortraitShim view.
class GameLogic;
extern GameLogic *TheGameLogic;
extern PlayerList *ThePlayerList;
extern GlobalData *TheWritableGlobalData;

// Retail reached each of these bodies through an incremental-link thunk, so the
// call target the linker used to substitute is the 5-byte ILT entry, spelled
// here directly as a plain `extern void f()` and called through a same-shaped
// member pointer.  The union keeps the flat thunk address and the typed call
// in one local without inventing a member or a body here.
extern void j_000226ab();
extern void j_0001acbc();
extern void j_00011f77();
extern void j_0001bb21();
extern void j_00003166();
extern void j_0001e0ab();
extern void j_000389f6();
extern void j_00009e12();
extern void j_00024938();
extern void j_0003a45e();
extern void j_00020824();
extern void j_000170da();

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

	typedef Player *(Object::*GetControllingPlayer)() const;
	union { void (*fn)(); GetControllingPlayer call; } uOwner = { j_00020824 };
	player = (owner->*uOwner.call)();

	if (player == 0)
		return;

	{
		typedef void (SpecialPowerModuleInterface::*Call)(const Coord3D *,
			UnsignedInt);
		union { void (*fn)(); Call call; } u = { j_000170da };
		(((SpecialPowerModuleInterface *)this)->*u.call)(target,
			commandOptions);
	}

	DevastateSpecialPowerModuleData *data = getModuleData();
	money = 0.0f;
	localTerrainLogic()->m_queryScratch = 0.1f;

	BfmeX1035 *thing;

	{
		typedef int (BfmeA1275::*Call)(int, int, int, int);
		union { void (*fn)(); Call call; } u = { j_000226ab };
		thing = (BfmeX1035 *)(((BfmeA1275 *)localTerrainLogic())->*u.call)(
			(int)target, data->m_queryKind, 0, 2);
	}

	while (thing != 0)
	{
		if (*(unsigned char *)((char *)thing + 0x18) == 0)
		{
			typedef void (Rva012EF4CCTerrain::*Call)(BfmeX1035 *, int);
			union { void (*fn)(); Call call; } u = { j_0001acbc };
			(localTerrainLogic()->*u.call)(thing, (int)target);
		}

		FXList *fx = data->m_fx;

		if (fx != 0)
		{
			typedef bool (FXList::*IsBlocked)();
			union { void (*fn)(); IsBlocked call; } u = { j_00011f77 };
			bool blocked = (fx->*u.call)();

			if (!blocked)
			{
				typedef void (FXList::*DoFXPos)(const Coord3D *,
					const Matrix3D *, float, const Coord3D *) const;
				union { void (*fn)(); DoFXPos call; } u2 = { j_0001bb21 };
				(fx->*u2.call)((const Coord3D *)thing, 0, 0.0f, 0);
			}
		}

		UnsignedInt amount;
		UnsignedInt scale;
		float reward;

		{
			typedef int (TerrainLogicP48Owner::*Call)(TerrainLogicP48Rec *,
				int);
			union { void (*fn)(); Call call; } u = { j_00003166 };
			amount = (UnsignedInt)(
				(((TerrainLogicP48Owner *)localTerrainLogic())->*u.call)(
					(TerrainLogicP48Rec *)thing, 0x1869f));
		}

		scale = (UnsignedInt)player->getSupplyBoxValue();

		reward = (float)(amount * scale);

		if (reward > 0.0f)
		{
			{
				typedef bool (GameLogicPortraitShim::*IsMultiplayer)();
				union { void (*fn)(); IsMultiplayer call; } u =
					{ j_0001e0ab };
				bool mp = (((GameLogicPortraitShim *)TheGameLogic)->*u.call)();

				if (mp)
				{
					int playerCount;
					float factor;

					{
						typedef int (PlayerList::*Count)(bool);
						union { void (*fn)(); Count call; } u = { j_000389f6 };
						playerCount = (ThePlayerList->*u.call)(false);
					}

					{
						typedef float (Gen_00083240::*Get0)(int) const;
						union { void (*fn)(); Get0 call; } u = { j_00009e12 };
						factor = (((Gen_00083240 *)((char *)
							TheWritableGlobalData + 0xee0))->*u.call)(
								playerCount);
					}

					reward *= factor;
				}
			}

			{
				typedef int (Rva000C97C0Player::*Adjust)(int);
				union { void (*fn)(); Adjust call; } u = { j_00024938 };
				money += (float)(((Rva000C97C0Player *)player)->*u.call)(
					(int)reward) * data->m_bountyScale;
			}
		}

		{
			typedef int (BfmeA1275::*Call)(int, int, int, int);
			union { void (*fn)(); Call call; } u = { j_000226ab };
			thing = (BfmeX1035 *)(((BfmeA1275 *)localTerrainLogic())->*u.call)(
				(int)target, data->m_queryKind, 0, 2);
		}
	}

	localTerrainLogic()->m_queryScratch = 0.0f;

	int deposit = (int)devastateMin(money, data->m_bountyCap);

	((Rva00027D6DMoney *)player->getMoney())->unidentified_00027d6d(
		deposit, true);

	{
		typedef void (Gen_000E8AF0::*AddCount)(int);
		union { void (*fn)(); AddCount call; } u = { j_0003a45e };
		(player->getScoreKeeper()->*u.call)(deposit);
	}
}
