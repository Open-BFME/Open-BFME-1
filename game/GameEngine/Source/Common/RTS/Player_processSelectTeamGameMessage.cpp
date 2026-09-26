// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

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

// ?processSelectTeamGameMessage@Player@@QAEXHPAVGameMessage@@@Z
void Player::processSelectTeamGameMessage(Int hotkeyNum, GameMessage *msg)
{
	(void)msg;

	if (hotkeyNum < 0 || hotkeyNum >= NUM_HOTKEY_SQUADS)
		return;

	if (((BFMEPlayerHotkeyView *)this)->m_squads[hotkeyNum] == NULL)
		return;

	if (((BFMEPlayerSelectionView *)this)->m_currentSelection == NULL)
	{
		((BFMEPlayerSelectionView *)this)->m_currentSelection =
			new Rva000D1930;
	}

	BfmeVecHolder holder = {
		((BFMEPlayerHotkeyView *)this)->m_squads[hotkeyNum]->bfmeCompact(true)
	};
	Int numObjects = holder.objects->size();
	for (Int i = 0; i < numObjects; ++i)
	{
		Object *object = (Object *)holder.objects->begin()[i];
		((Rva0018B9A0Holder *)
			((BFMEPlayerSelectionView *)this)->m_currentSelection)->addObject(object);
		PlayerMaskType playerMask =
			(PlayerMaskType)(1 << ((BFMEPlayerIndexView *)this)->m_playerIndex);
		TheGameLogic->selectObject(object, FALSE,
			playerMask, FALSE);
	}
}
