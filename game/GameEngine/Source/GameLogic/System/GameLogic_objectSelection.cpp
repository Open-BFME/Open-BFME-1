// cl: /DNDEBUG /MD
// readable ZH body: game/GameEngine/Source/GameLogic/System/GameLogic.cpp
//
// GameLogic::selectObject (retail 0x00382E30) and GameLogic::deselectObject
// (0x00382F50, 178 bytes) -- the two halves of one operation.
//
// They were two files that described the same three classes under different
// names, and between them they knew things neither could state alone:
//
//   InGameUI was `InGameUI` with 56 padding slots in one file and
//   `BFMEGameLogicInGameUIShim` with 57 in the other. It is one class, and
//   selectDrawable and deselectDrawable are ADJACENT -- slots 56 and 57.
//
//   Object was `Object` with getDrawable at slot 10 in one file and
//   `BFMEGameLogicObjectDrawableShim` with getDrawable at slot 10 in the other.
//   Same class, same slot, two spellings. The select path also knew three
//   non-virtual Object entry points the deselect path did not, and the deselect
//   path knew a fourth.
//
//   Player and AIGroup each had half their methods in each file: add/remove on
//   the group, and set/add/get on the player's current selection.
//
// The deselect body's reinterpret_casts are left exactly as they were. With one
// set of types they are now identity casts, but rewriting a byte-verified body
// to tidy a cast is not worth the risk of moving it.

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
	void notifyRva001C8830(Player *player);		// select side, ILT to 0x001C8830

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
	virtual Drawable *getDrawable(void);		// slot 10
};

// The deselect side's Object callback keeps its own shim class, because the
// class name IS the pinned symbol: ?notifyRva001C89E0@BFMEGameLogicObject-
// SelectionDeselectShim@@QAEXPAVPlayer@@@Z. Moving the method onto Object
// renames it and the resolver has no address left to emit -- the call comes
// out as e8 00 00 00 00.
class BFMEGameLogicObjectSelectionDeselectShim
{
public:
	void notifyRva001C89E0(Player *player);		// ILT 0x000380CD -> 0x001C89E0
};

class Player
{
public:
	void setCurrentlySelectedAIGroup(AIGroup *group);
	void addAIGroupToCurrentSelection(AIGroup *group);
	void getCurrentSelectionAsAIGroup(AIGroup *group);
};

class AIGroup
{
public:
	void add(Object *obj);
	Bool remove(Object *obj);
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
	virtual void selectDrawable(Drawable *draw);		// slot 56
	virtual void deselectDrawable(Drawable *draw);		// slot 57
};

class GameLogic
{
public:
	void selectObject(Object *obj, Bool createNewSelection, PlayerMaskType playerMask, Bool affectClient);
	void deselectObject(Object *obj, PlayerMaskType playerMask, Bool affectClient);
};

extern PlayerList *ThePlayerList;
extern AI *TheAI;
extern InGameUI *TheInGameUI;

// Open-BFME5: GameLogic::selectObject at 0x00382E30.
// The ZH predicate is isMassSelectable (matched at 0x001C98C0). Retail calls
// Object::queryRva001C9980 ILT 0x00019B5F -> 0x001C9980 instead. After affectClient BFME
// also compares getControllingPlayer and calls queryInterfaceRva001BF6B0
// plus notifyRva001C8830(player).

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

// BFME GameLogic::deselectObject, retail 0x00382F50, 178 bytes.
// BFME moves Object::getDrawable to virtual slot 10 and
// InGameUI::deselectDrawable to virtual slot 57. The final Object callback
// reaches retail body 0x001C89E0 through ILT 0x000380CD.

// ?deselectObject@GameLogic@@QAEXPAVObject@@G_N@Z
void GameLogic::deselectObject(Object *obj, PlayerMaskType playerMask, Bool affectClient)
{
	if (!obj) {
		return;
	}

	while (playerMask) {
		Player *player = ThePlayerList->getEachPlayerFromMask(playerMask);
		if (!player) {
			return;
		}

		AIGroup *group = 0;
		group = TheAI->createGroup();
		player->getCurrentSelectionAsAIGroup(group);

		Bool deleted = false;
		Bool actuallyRemoved = false;

		if (group) {
			deleted = group->remove(obj);
			actuallyRemoved = true;
		}

		if (actuallyRemoved) {
			if (!deleted) {
				player->setCurrentlySelectedAIGroup(group);
				TheAI->destroyGroup(group);
			} else {
				player->setCurrentlySelectedAIGroup(0);
			}

			if (affectClient) {
				Drawable *draw = reinterpret_cast<Object *>(obj)->getDrawable();
				if (draw) {
					reinterpret_cast<InGameUI *>(TheInGameUI)->deselectDrawable(draw);
				}
			}
		}

		reinterpret_cast<BFMEGameLogicObjectSelectionDeselectShim *>(obj)->notifyRva001C89E0(player);
	}
}
