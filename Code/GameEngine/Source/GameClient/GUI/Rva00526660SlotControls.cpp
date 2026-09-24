// cl: /O2 /DNDEBUG /MD /EHsc
// Retail 0x00526660 (523 bytes, thiscall, ret 8), reached through ILT
// 0x0001C8D2 from the wrapper at 0x00527200 and from 0x00528B60.
//
// Zero Hour twin: EnableAcceptControls in
// reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameNetwork/GUIUtil.cpp
// -- same slot fallback, observer test, colour/template/team enables,
// canChooseStartSpot scan and start-position button loops. BFME moved the
// arrays into the receiver and adds a start-position lookup through the
// matched MpGameSetup::bfmeGetStartPositionInfo on the same receiver.
// The receiver's owning class and the method's own name are not proven, so
// both keep the address token (see
// reverse/identity_evidence/0x00526660-false-drawable-route.md).

class GameWindow
{
public:
	int winEnable(bool enable);
};

void GadgetComboBoxHideList(GameWindow *comboBox);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	bool isAI(void) const;
	bool hasMap(void) const { return m_hasMap; }
	int getPlayerTemplate(void) const { return m_playerTemplate; }

private:
	unsigned char m_unmodelled00[9];
	bool m_hasMap;
	unsigned char m_unmodelled0A[0x0A];
	int m_playerTemplate;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual bool amIHost(void) const = 0;
	virtual int getLocalSlotNum(void) const = 0;

	const GameSlot *getConstSlot(int index) const;
};

class Rva00526660Owner
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual bool contains(GameInfo *game) = 0;
};

// Four-byte GameWindow handle. invoke(true) at 0x004B5C90 hides the combo
// box list. Here retail copies the colour handle with 0x004B5A60 (ILT
// 0x0001B90F) and its unwind funclet destroys the copy with 0x004B5A70
// (ILT 0x0003EB53).
class Rva004B5C90
{
public:
	Rva004B5C90(const Rva004B5C90 &other);
	~Rva004B5C90();
	void invoke(bool hide);

	GameWindow *m_00;
};

struct StartPositionInfo;

class MpGameSetup
{
public:
	const StartPositionInfo *bfmeGetStartPositionInfo(int slotIndex);
};

// Member offsets agree with MpGameSetup.cpp and MpGameSetupOnInitGadget.cpp:
// Color (+0x88), Team (+0xA8) and PlayerTemplate (+0xC8) are bound by the
// literal-named gadget callback 0x00525AB0; the start-position buttons are
// the embedded AptMapPreview's children at +0x28 + 0x14.
class Rva00526660Body
{
public:
	void run(bool enable, int index);

private:
	unsigned char m_vtable[4];
	Rva00526660Owner *m_owner;
	GameInfo *m_first;
	GameInfo *m_second;
	unsigned char m_unmodelled10[0x2C];
	GameWindow *m_startPositions[8];
	unsigned char m_unmodelled5C[0x2C];
	Rva004B5C90 m_color[8];
	GameWindow *m_team[8];
	GameWindow *m_playerTemplate[8];
	unsigned char m_unmodelledE8[0x3C];
	bool m_isMultiplayer;
};

// ?run@Rva00526660Body@@QAEX_NH@Z
void Rva00526660Body::run(bool enable, int index)
{
	if (m_first && !m_owner->contains(m_first))
		m_first = 0;

	if (m_second && !m_owner->contains(m_second))
		m_second = 0;

	if (!m_first)
		return;

	if (index == -1 || index >= 8)
		index = m_first->getLocalSlotNum();

	bool slotEnable = enable;
	if (m_isMultiplayer && !((MpGameSetup *)this)->bfmeGetStartPositionInfo(index))
		slotEnable = false;

	bool isObserver = m_first->getConstSlot(index)->getPlayerTemplate() == -2;

	Rva004B5C90 color(m_color[index]);
	if (color.m_00)
	{
		if (isObserver)
			color.invoke(true);
		color.m_00->winEnable(enable && !isObserver);
	}

	if (m_playerTemplate[index])
		m_playerTemplate[index]->winEnable(slotEnable);

	if (m_team[index])
	{
		if (isObserver)
			GadgetComboBoxHideList(m_team[index]);
		m_team[index]->winEnable(slotEnable && !isObserver);
	}

	bool canChooseStartSpot = !isObserver || m_isMultiplayer;
	for (int i = 0; i < 8 && !canChooseStartSpot && m_first->amIHost(); ++i)
	{
		if (m_first->getConstSlot(i) && m_first->getConstSlot(i)->isAI())
			canChooseStartSpot = true;
	}

	// The twin reads the buttons through an array parameter; retail keeps that
	// indexed form rather than a strength-reduced cursor.
	GameWindow **buttonMapStartPosition = m_startPositions;
	if (index == m_first->getLocalSlotNum())
	{
		if (m_first->getConstSlot(m_first->getLocalSlotNum())->hasMap())
		{
			for (int i = 0; i < 8; ++i)
			{
				if (buttonMapStartPosition[i])
					buttonMapStartPosition[i]->winEnable(enable && canChooseStartSpot);
			}
		}
		else
		{
			for (int i = 0; i < 8; ++i)
			{
				if (buttonMapStartPosition[i])
					buttonMapStartPosition[i]->winEnable(false);
			}
		}
	}
}
