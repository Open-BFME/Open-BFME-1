// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /MD /EHsc /Ireference/shims/stringbaseunicode /Ireference/shims/asciistring_downloadmanager /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /DBFME_MODULE_NO_MPO
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#include "PreRTS.h"
#include "Common/GlobalData.h"
#include "Common/Player.h"
#include "GameClient/GameText.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/SalvageCrateCollide.h"

struct BfmeSalvageModuleDataLayout
{
	char prefix[0x68];
	Int minimumMoney;
	Int maximumMoney;
};

struct BfmeSalvageLayout
{
	void *vtable;
	BfmeSalvageModuleDataLayout *moduleData;
	Object *object;
};

class GameLogicPortraitShim
{
public:
	Bool isInMultiplayerOrSkirmishGame();
};

class Gen_00083240
{
public:
	Real bfmeGet0(Int index) const;
};

class Rva000C97C0Player
{
public:
	Int adjustBountyForLivingWorld(Int bounty);
};

class BfmeQ1254
{
public:
	char prefix[0x1c4];
	UnsignedInt field1c4;
};

class BfmeS1254
{
public:
	BfmeQ1254 *bfmeGet1254();
};

class BfmeA1254
{
public:
	void bfmeDraw1254(BfmeS1254 *object, Int text);
};

class GameLogic;
class PlayerList;

extern char g_bfmeFileAO[];
extern GameLogic *TheBfmeGameLogic;
extern PlayerList *Rva002EE330ThePlayers;
extern void j_0002dcfe();
extern void j_000389f6();
extern void j_0003a45e();

static __forceinline Int bfmeCurrentPlayerIndex(PlayerList *players)
{
	class PlayerListCall {};
	typedef Int (PlayerListCall::*Function)(Bool);
	union { void (*raw)(); Function member; } target;
	target.raw = j_000389f6;
	return (reinterpret_cast<PlayerListCall *>(players)->*target.member)(FALSE);
}

static __forceinline void bfmeAddMoneyEarned(ScoreKeeper *scoreKeeper, Int amount)
{
	class ScoreKeeperCall {};
	typedef void (ScoreKeeperCall::*Function)(Int);
	union { void (*raw)(); Function member; } target;
	target.raw = j_0003a45e;
	(reinterpret_cast<ScoreKeeperCall *>(scoreKeeper)->*target.member)(amount);
}

static __forceinline void bfmeDrawSalvageText(
	BfmeA1254 *draw, BfmeS1254 *object, Int text)
{
	typedef void (BfmeA1254::*Function)(BfmeS1254 *, Int);
	union { void (*raw)(); Function member; } target;
	target.raw = j_0002dcfe;
	(draw->*target.member)(object, text);
}

SalvageCrateCollide::SalvageCrateCollide(Thing *thing, const ModuleData *moduleData)
	: CrateCollide(thing, moduleData)
{
}

SalvageCrateCollide::~SalvageCrateCollide()
{
}

void SalvageCrateCollide::doMoney(Object *other)
{
	BfmeSalvageModuleDataLayout *md =
		reinterpret_cast<BfmeSalvageLayout *>(this)->moduleData;
	Int money;

	if (md->minimumMoney != md->maximumMoney)
		money = GetGameLogicRandomValue(md->minimumMoney, md->maximumMoney,
			g_bfmeFileAO, 0xc4);
	else
		money = md->minimumMoney;

	if (money > 0) {
		if (reinterpret_cast<GameLogicPortraitShim *>(TheBfmeGameLogic)->
			isInMultiplayerOrSkirmishGame()) {
			Int playerIndex = bfmeCurrentPlayerIndex(Rva002EE330ThePlayers);
			Real factor = reinterpret_cast<Gen_00083240 *>(
				reinterpret_cast<char *>(TheWritableGlobalData) + 0xee0)->bfmeGet0(playerIndex);
			money = static_cast<Int>(money * factor);
		}

		Player *player = other->getControllingPlayer();
		if (player != NULL) {
			money = reinterpret_cast<Rva000C97C0Player *>(player)->
				adjustBountyForLivingWorld(money);
			reinterpret_cast<Money *>(reinterpret_cast<char *>(player) + 0x48)->deposit(money);
			bfmeAddMoneyEarned(
				reinterpret_cast<ScoreKeeper *>(reinterpret_cast<char *>(player) + 0x348), money);
		}

		UnicodeString moneyString;
		moneyString.format(TheGameText->fetch("GUI:AddCash"), money);
		bfmeDrawSalvageText(reinterpret_cast<BfmeA1254 *>(this),
			reinterpret_cast<BfmeS1254 *>(other), reinterpret_cast<Int>(&moneyString));
	}
}
