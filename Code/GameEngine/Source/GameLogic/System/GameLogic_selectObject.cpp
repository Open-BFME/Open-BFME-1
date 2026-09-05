// cl: /DNDEBUG /MD
// readable ZH body: Code/GameEngine/Source/GameLogic/System/GameLogic.cpp
// Open-BFME5: GameLogic::selectObject at 0x00382E30.
// The ZH predicate is isMassSelectable (matched at 0x001C98C0). Retail calls
// Object::queryRva001C9980 ILT 0x00019B5F -> 0x001C9980 instead. After affectClient BFME
// also compares getControllingPlayer and calls queryInterfaceRva001BF6B0
// plus notifyRva001C8830(player).

typedef bool Bool;
typedef unsigned short PlayerMaskType;

class Object;
class Player;
class AIGroup;
class Drawable;
class BfmeInterface001BF6B0
{
public:
	virtual void slot0(void);
	virtual void slot1(void);
};

class Object
{
public:
	bool queryRva001C9980(void);
	Player *getControllingPlayer(void) const;
	BfmeInterface001BF6B0 *queryInterfaceRva001BF6B0(void);
	void notifyRva001C8830(Player *player);

	virtual void slot0(void);
	virtual void slot1(void);
	virtual void slot2(void);
	virtual void slot3(void);
	virtual void slot4(void);
	virtual void slot5(void);
	virtual void slot6(void);
	virtual void slot7(void);
	virtual void slot8(void);
	virtual void slot9(void);
	virtual Drawable *getDrawable(void);
};

class Player
{
public:
	void setCurrentlySelectedAIGroup(AIGroup *group);
	void addAIGroupToCurrentSelection(AIGroup *group);
};

class AIGroup
{
public:
	void add(Object *obj);
};

class AI
{
public:
	AIGroup *createGroup(void);
	void destroyGroup(AIGroup *group);
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(PlayerMaskType &mask);
};

class InGameUI
{
public:
	virtual void s00(void); virtual void s01(void); virtual void s02(void); virtual void s03(void);
	virtual void s04(void); virtual void s05(void); virtual void s06(void); virtual void s07(void);
	virtual void s08(void); virtual void s09(void); virtual void s10(void); virtual void s11(void);
	virtual void s12(void); virtual void s13(void); virtual void s14(void); virtual void s15(void);
	virtual void s16(void); virtual void s17(void); virtual void s18(void); virtual void s19(void);
	virtual void s20(void); virtual void s21(void); virtual void s22(void); virtual void s23(void);
	virtual void s24(void); virtual void s25(void); virtual void s26(void); virtual void s27(void);
	virtual void s28(void); virtual void s29(void); virtual void s30(void); virtual void s31(void);
	virtual void s32(void); virtual void s33(void); virtual void s34(void); virtual void s35(void);
	virtual void s36(void); virtual void s37(void); virtual void s38(void); virtual void s39(void);
	virtual void s40(void); virtual void s41(void); virtual void s42(void); virtual void s43(void);
	virtual void s44(void); virtual void s45(void); virtual void s46(void); virtual void s47(void);
	virtual void s48(void); virtual void s49(void); virtual void s50(void); virtual void s51(void);
	virtual void s52(void); virtual void s53(void); virtual void s54(void); virtual void s55(void);
	virtual void selectDrawable(Drawable *draw);
};

class GameLogic
{
public:
	void selectObject(Object *obj, Bool createNewSelection, PlayerMaskType playerMask, Bool affectClient);
};

extern PlayerList *ThePlayerList;
extern AI *TheAI;
extern InGameUI *TheInGameUI;

// ?selectObject@GameLogic@@QAEXPAVObject@@_NG1@Z
void GameLogic::selectObject(Object *obj, Bool createNewSelection, PlayerMaskType playerMask, Bool affectClient)
{
	if (!obj)
		return;

	if (!obj->queryRva001C9980() && !createNewSelection)
		return;

	while (playerMask)
	{
		Player *player = ThePlayerList->getEachPlayerFromMask(playerMask);
		if (!player)
			return;

		AIGroup *group = TheAI->createGroup();
		group->add(obj);

		if (createNewSelection)
			player->setCurrentlySelectedAIGroup(group);
		else
			player->addAIGroupToCurrentSelection(group);

		TheAI->destroyGroup(group);

		if (affectClient)
		{
			Drawable *draw = obj->getDrawable();
			if (draw)
				TheInGameUI->selectDrawable(draw);
		}

		if (player == obj->getControllingPlayer())
		{
			BfmeInterface001BF6B0 *iface = obj->queryInterfaceRva001BF6B0();
			if (iface)
				iface->slot1();
		}

		obj->notifyRva001C8830(player);
	}
}
