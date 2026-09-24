// cl: /DNDEBUG /MD /EHs-c-
// Retail 0x00523460 (258 bytes).  The owner's window table at +0xC8 has the
// SkirmishScreenState shape, but no caller, vtable slot or declaration names
// the class or the method, so both keep the address.  The body drops a
// GameInfo at +8 or +0xC that the handler at +4 no longer accepts, finds the
// entry of combo box `index` whose item data equals `itemData`, selects it,
// and hands the slot and the entry's data back to the handler.

typedef bool Bool;
typedef int Int;

class GameWindow
{
public:
	void *winGetUserData();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Gadget.h
struct ComboBoxData
{
	unsigned char m_pad00[0x2c];
	GameWindow *listBox;
};

Int GadgetListBoxGetNumEntries(GameWindow *listbox);
void *GadgetListBoxGetItemData(GameWindow *listbox, Int row, Int column);
void GadgetComboBoxGetSelectedPos(GameWindow *comboBox, Int *selectedIndex);
void GadgetComboBoxSetSelectedPos(GameWindow *comboBox, Int selectedIndex, Bool dontHide);
void *GadgetComboBoxGetItemData(GameWindow *comboBox, Int index);

class GameSlot;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual Bool slot04();

	GameSlot *getSlot(Int slotNum);
};

class Rva00523460Handler
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04(GameSlot *slot, void *itemData);
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual Bool slot09(GameInfo *game);
};

class Rva00523460Owner
{
public:
	void rva00523460(Int index, Int itemData);

private:
	void *m_vtable;
	Rva00523460Handler *m_handler;
	GameInfo *m_game;
	GameInfo *m_otherGame;
	unsigned char m_pad10[0xc8 - 0x10];
	GameWindow *m_comboBoxes[1];
};

// ?rva00523460@Rva00523460Owner@@QAEXHH@Z
void Rva00523460Owner::rva00523460(Int index, Int itemData)
{
	if (m_game && !m_handler->slot09(m_game))
		m_game = 0;
	if (m_otherGame && !m_handler->slot09(m_otherGame))
		m_otherGame = 0;
	if (!m_game)
		return;

	GameWindow *comboBox = m_comboBoxes[index];
	if (!comboBox)
		return;

	ComboBoxData *data = (ComboBoxData *)comboBox->winGetUserData();
	GameWindow *listBox = (data && data->listBox) ? data->listBox : 0;

	Int count = GadgetListBoxGetNumEntries(listBox);
	Int i;
	for (i = 0; i < count; ++i)
	{
		if ((Int)GadgetListBoxGetItemData(listBox, i, 0) == itemData)
			goto found;
	}
	return;

found:
	// Retail keeps the selected position in itemData's own slot.
	GadgetComboBoxGetSelectedPos(comboBox, &itemData);
	if (itemData == i)
		return;

	GadgetComboBoxSetSelectedPos(comboBox, i, false);
	if (!m_game->slot04())
		return;

	GameSlot *slot = m_game->getSlot(index);
	if (!slot)
		return;

	void *entryData = GadgetComboBoxGetItemData(comboBox, i);
	m_handler->slot04(slot, entryData);
}
