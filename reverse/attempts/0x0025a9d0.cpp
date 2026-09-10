// ?d_0025a9d0@@YAXXZ
// partial score=0.93 date=2026-09-10
// ?doSpecialPowerAtLocation@DevastateSpecialPowerInterface@@UAEXPBVCoord3D@@I@Z
// Retail identity comes from vtable 0x010B4608 slot 13 and thunk 0x00029AAA.

typedef unsigned int UnsignedInt;

class Object
{
public:
	char m_pad00[0x1a4];
	int m_disabledMask;
	class Player *getControllingPlayer() const;
};

class Player;

class Money
{
public:
	void deposit(UnsignedInt amount, bool playSound);
};

class ScoreKeeper
{
public:
	void addMoneyEarned(int amount);
};

class Player
{
public:
	int adjustBountyForLivingWorld(int amount) const;
	int getMultiplier() const;

	Money *getMoney() const
	{
		return (Money *)((char *)this + 0x48);
	}

	ScoreKeeper *getScoreKeeper() const
	{
		return (ScoreKeeper *)((char *)this + 0x348);
	}
};

class Coord3D;
class SpecialPowerLocation;
class SpecialPowerCommandOptions;

class SpecialPowerModuleInterface
{
public:
	void doSpecialPowerAtLocation(const Coord3D *target,
		UnsignedInt commandOptions);
};

class TerrainLogic
{
public:
	int bfmeGo1275(int a1, int a2, int a3, int a4);
	int bfmeProcess(void *object, int value);

	char m_pad18f8[0x18f8];
	float m_field18f8;
};

class BfmeX1035
{
};

void __stdcall bfmeGo1035C(BfmeX1035 *object, int value);

class BfmeThingCOF
{
public:
	bool bfmeAskCOF();
	void bfmeRunCOF(void *a, void *b, void *c, void *d);
};

class GameLogic
{
public:
	bool isInMultiplayerOrSkirmishGame();
};

class PlayerList
{
public:
	int getPlayersWithRelationship(bool includeFields);
};

class GlobalData
{
};

class GlobalDataField
{
public:
	float get(int index) const;
};

class Rva002EE330PlayerListThunk
{
public:
	int unidentified_000389f6(bool includeFields);
};

class Rva00083240Thunk
{
public:
	float unidentified_00009e12(int index) const;
};

class GameLogicShim
{
public:
	bool unidentified_0001e0ab();
};

class Rva000C97C0PlayerThunk
{
public:
	int unidentified_00024938(int amount);
};

class DevastateSpecialPowerModuleData
{
public:
	char m_pad00[0x210];
	int m_field210;
	BfmeThingCOF *m_fx;
	float m_scale;
	float m_field21c;
};

class DevastateSpecialPowerInterface
{
public:
	virtual void doSpecialPowerAtLocation(const Coord3D *target,
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

extern TerrainLogic *TheTerrainLogic;
extern GameLogic *TheGameLogic;
extern PlayerList *ThePlayerList;
extern GlobalData *TheWritableGlobalData;
extern "C" long __ftol2(double value);

#pragma comment(linker, "/alternatename:?getControllingPlayer@Object@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?doSpecialPowerAtLocation@SpecialPowerModuleInterface@@QAEXPBVCoord3D@@I@Z=?j_000170da@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeGo1275@TerrainLogic@@QAEHHHHH@Z=?j_000226ab@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeGo1035C@@YGXPAVBfmeX1035@@H@Z=?j_0001acbc@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeAskCOF@BfmeThingCOF@@QAE_NXZ=?j_00011f77@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeRunCOF@BfmeThingCOF@@QAEXPAX000@Z=?j_0001bb21@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeProcess@TerrainLogic@@QAEHPAXH@Z=?j_00003166@@YAXXZ")
#pragma comment(linker, "/alternatename:?unidentified_0001e0ab@GameLogicShim@@QAE_NXZ=?j_0001e0ab@@YAXXZ")
#pragma comment(linker, "/alternatename:?unidentified_000389f6@Rva002EE330PlayerListThunk@@QAEH_N@Z=?j_000389f6@@YAXXZ")
#pragma comment(linker, "/alternatename:?unidentified_00009e12@Rva00083240Thunk@@QBEMH@Z=?j_00009e12@@YAXXZ")
#pragma comment(linker, "/alternatename:?unidentified_00024938@Rva000C97C0PlayerThunk@@QAEHH@Z=?j_00024938@@YAXXZ")
#pragma comment(linker, "/alternatename:?isInMultiplayerOrSkirmishGame@GameLogic@@QAE_NXZ=?j_0001e0ab@@YAXXZ")
#pragma comment(linker, "/alternatename:?getPlayersWithRelationship@PlayerList@@QAEH_N@Z=?j_000389f6@@YAXXZ")
#pragma comment(linker, "/alternatename:?get@GlobalDataField@@QBEMH@Z=?j_00009e12@@YAXXZ")
#pragma comment(linker, "/alternatename:?getMultiplier@Player@@QBEHXZ=?j_0000ed3b@@YAXXZ")
#pragma comment(linker, "/alternatename:?adjustBountyForLivingWorld@Player@@QBEHH@Z=?j_00024938@@YAXXZ")
#pragma comment(linker, "/alternatename:?deposit@Money@@QAEXI_N@Z=?j_00027d6d@@YAXXZ")
#pragma comment(linker, "/alternatename:?addMoneyEarned@ScoreKeeper@@QAEXH@Z=?j_0003a45e@@YAXXZ")

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

	((SpecialPowerModuleInterface *)this)->doSpecialPowerAtLocation(
		target,
		commandOptions);

	DevastateSpecialPowerModuleData *data = getModuleData();
	money = 0.0f;
	TheTerrainLogic->m_field18f8 = 0.1f;
	BfmeX1035 *result = (BfmeX1035 *)TheTerrainLogic->bfmeGo1275(
		(int)target, data->m_field210, 0, 2);
	while (result != 0)
	{
		if (*(unsigned char *)((char *)result + 0x18) == 0)
			bfmeGo1035C(result, (int)target);

		BfmeThingCOF *fx = data->m_fx;
		if (fx != 0 && !fx->bfmeAskCOF())
			fx->bfmeRunCOF(result, 0, 0, 0);

		UnsignedInt amount = (UnsignedInt)TheTerrainLogic->bfmeProcess(result, 0x1869f);
		UnsignedInt scale = (UnsignedInt)player->getMultiplier();
		float reward = (float)(amount * scale);
		if (reward > 0.0f)
		{
			if (TheGameLogic->isInMultiplayerOrSkirmishGame())
			{
				int playerIndex = ThePlayerList->getPlayersWithRelationship(false);
				float factor = ((GlobalDataField *)((char *)TheWritableGlobalData + 0xee0))->get(playerIndex);
				reward *= factor;
			}
		}

		money += (float)player->adjustBountyForLivingWorld((int)reward) * data->m_scale;
		result = (BfmeX1035 *)TheTerrainLogic->bfmeGo1275(
			(int)target, data->m_field210, 0, 2);
	}

	TheTerrainLogic->m_field18f8 = 0.0f;
	if (money >= data->m_field21c)
		money = data->m_field21c;
	int deposit = (int)money;
	player->getMoney()->deposit(deposit, true);
	player->getScoreKeeper()->addMoneyEarned(deposit);
}
