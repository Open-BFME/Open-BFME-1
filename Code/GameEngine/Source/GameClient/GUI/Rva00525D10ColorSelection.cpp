// cl: /O2 /DNDEBUG /MD /EHsc
// Retail 0x00525D10 (368 bytes, thiscall, ret 4), called through its ILT
// from the still-dumped 0x00529EC0.
//
// Zero Hour twin: handleColorSelection in
// reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/SkirmishGameOptionsMenu.cpp
// -- read the colour combo's selected item data, reject an unchanged colour,
// an out-of-range colour and a colour another slot already uses, then apply.
// BFME reads the combo through the same image-combo handle as 0x00526660 and
// applies the colour through owner vtable slot 3 instead of slot->setColor.
// The receiver's owning class is not proven, so the class keeps the address
// token.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	int getColor(void) const { return m_color; }

private:
	unsigned char m_unmodelled00[0x0C];
	int m_color;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	GameSlot *getSlot(int index);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MultiplayerSettings.h
class MultiplayerColorList
{
public:
	int size() const { return m_size; }

private:
	int m_size;
	int m_tree;
};

class MultiplayerSettings
{
public:
	int getNumColors()
	{
		if (m_numColors == 0)
			m_numColors = m_colorList.size();
		return m_numColors;
	}

private:
	char m_unmodelled[0x34];
	MultiplayerColorList m_colorList;
	int m_numColors;
};

extern MultiplayerSettings *TheMultiplayerSettings;

class Rva00525D10Owner
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual bool slot03(GameSlot *slot, int color) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual bool contains(GameInfo *game) = 0;
};

// Four-byte image-combo handle (see Rva00526660SlotControls.cpp). The two
// accessors keep their existing address-derived ledger names: 0x004B5BC0
// returns the selected position and 0x004B5C30 the item data at a position.
class Rva004B5C90
{
public:
	Rva004B5C90(const Rva004B5C90 &other);
	~Rva004B5C90();

	void *m_00;
};

class BfmeC1040
{
public:
	int bfmeGo1040C(void);
};

class BfmeThingCCH
{
public:
	int bfmeGoCCH(void *what);
};

class Rva00525D10Setup
{
public:
	bool handleColorSelection(int index);

private:
	unsigned char m_vtable[4];
	Rva00525D10Owner *m_owner;
	GameInfo *m_first;
	GameInfo *m_second;
	unsigned char m_unmodelled10[7];
	bool m_pending;
	unsigned char m_unmodelled18[0x70];
	Rva004B5C90 m_color[8];
};

// ?handleColorSelection@Rva00525D10Setup@@QAE_NH@Z
bool Rva00525D10Setup::handleColorSelection(int index)
{
	if (m_first && !m_owner->contains(m_first))
		m_first = 0;

	if (m_second && !m_owner->contains(m_second))
		m_second = 0;

	if (!m_first)
		return false;

	m_pending = false;
	Rva004B5C90 combo(m_color[index]);
	int selIndex = ((BfmeC1040 *)&combo)->bfmeGo1040C();
	int color = ((BfmeThingCCH *)&combo)->bfmeGoCCH((void *)selIndex);
	if (color < -1)
		return false;

	GameSlot *slot = m_first->getSlot(index);
	if (!slot)
		return false;
	if (color == slot->getColor())
		return false;
	if (color >= TheMultiplayerSettings->getNumColors())
		return false;

	if (color != -1)
	{
		for (int i = 0; i < 8; ++i)
		{
			GameSlot *checkSlot = m_first->getSlot(i);
			if (checkSlot && color == checkSlot->getColor() && slot != checkSlot)
				return false;
		}
	}

	return m_owner->slot03(slot, color);
}
