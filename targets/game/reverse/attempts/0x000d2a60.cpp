// ?processAddTeamGameMessage@Player@@QAEXHPAVGameMessage@@@Z
// partial score=0.29 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Retail 0x000D2A60 (209B). Sits between the landed processCreateTeamGameMessage
// (0x000D29C0) and processSelectTeamGameMessage (0x000D2B70); the bounds check,
// m_squads[hotkeyNum] layout (+0x654), m_currentSelection layout (+0x67c),
// bfmeCompact/addObject/selectObject call sequence and TheGameLogic global all
// match those two landed siblings exactly (same BFMEPlayerHotkeyView /
// BFMEPlayerSelectionView / BFMEPlayerIndexView casts as
// Player_processSelectTeamGameMessage.cpp, same Gen_0018B850::bfmeClear as
// Player_processCreateTeamGameMessage.cpp). Unlike ZH's addTeam, retail here
// unconditionally clears m_currentSelection every call (not just on first
// alloc) and passes createNewSelection=true to selectObject only for i==0.

#include "PreRTS.h"

#include "Common/Player.h"

class Object;

class Rva000D1930
{
public:
	Rva000D1930() throw();

private:
	int m_data[7];
};

class BfmeItemAK
{
};

class BfmeVecAK
{
public:
	BfmeItemAK **begin(void)
	{
		return m_start;
	}

	Int size(void)
	{
		return end() - begin();
	}

	BfmeItemAK **end(void)
	{
		return m_finish;
	}

private:
	BfmeItemAK **m_start;
	BfmeItemAK **m_finish;
	BfmeItemAK **m_end;
};

struct BfmeVecHolder
{
	BfmeVecAK *objects;
};

class Gen_0018BC70
{
public:
	BfmeVecAK *bfmeCompact(Bool restart);
};

class Gen_0018B850
{
public:
	void bfmeClear(void);
};

class Rva0018B9A0Holder
{
public:
	void addObject(Object *object);
};

class GameLogic
{
public:
	void selectObject(Object *object, Bool createNewSelection,
		PlayerMaskType playerMask, Bool affectClient);
};

extern GameLogic *TheGameLogic;

struct BFMEPlayerSelectionView
{
	char pad[0x67c];
	Rva000D1930 *m_currentSelection;
};

struct BFMEPlayerHotkeyView
{
	char pad[0x654];
	Gen_0018BC70 *m_squads[NUM_HOTKEY_SQUADS];
};

struct BFMEPlayerIndexView
{
	char pad[0x24];
	Int m_playerIndex;
};

// ?processAddTeamGameMessage@Player@@QAEXHPAVGameMessage@@@Z
void Player::processAddTeamGameMessage(Int hotkeyNum, GameMessage *msg)
{
	(void)msg;

	BFMEPlayerHotkeyView *hotkeyView = (BFMEPlayerHotkeyView *)this;

	if (hotkeyNum < 0 || hotkeyNum >= NUM_HOTKEY_SQUADS)
		return;

	if (hotkeyView->m_squads[hotkeyNum] == NULL)
		return;

	BFMEPlayerSelectionView *selectionView = (BFMEPlayerSelectionView *)this;

	if (selectionView->m_currentSelection == NULL)
	{
		selectionView->m_currentSelection = new Rva000D1930;
	}

	((Gen_0018B850 *)selectionView->m_currentSelection)->bfmeClear();

	BfmeVecHolder holder = {
		hotkeyView->m_squads[hotkeyNum]->bfmeCompact(true)
	};
	Int numObjects = holder.objects->size();
	for (Int i = 0; i < numObjects; ++i)
	{
		Object *object = (Object *)holder.objects->begin()[i];
		((Rva0018B9A0Holder *)selectionView->m_currentSelection)
			->addObject(object);
		PlayerMaskType playerMask = (PlayerMaskType)(
			1 << ((BFMEPlayerIndexView *)this)->m_playerIndex);
		TheGameLogic->selectObject(object, i == 0,
			playerMask, FALSE);
	}
}
