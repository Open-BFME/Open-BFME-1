// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// readable body of ?setInputEnabled@InGameUI@@UAEX_N@Z: Code/GameEngine/Source/GameClient/InGameUI.cpp

typedef bool Bool;

class BfmeSelectionTranslator
{
public:
	void setDragSelecting();
};
extern BfmeSelectionTranslator *TheSelectionTranslator;

// TU-scoped BFME vtable view. The three named slots are the mode resets used
// when input is re-enabled; the remaining slots preserve their retail offsets.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
public:
#define BFME_UI_SLOT(n) virtual void slot##n() = 0;
	BFME_UI_SLOT(00) BFME_UI_SLOT(01) BFME_UI_SLOT(02) BFME_UI_SLOT(03)
	BFME_UI_SLOT(04) BFME_UI_SLOT(05) BFME_UI_SLOT(06) BFME_UI_SLOT(07)
	BFME_UI_SLOT(08) BFME_UI_SLOT(09) BFME_UI_SLOT(10) BFME_UI_SLOT(11)
	BFME_UI_SLOT(12) BFME_UI_SLOT(13) BFME_UI_SLOT(14) BFME_UI_SLOT(15)
	BFME_UI_SLOT(16) BFME_UI_SLOT(17) BFME_UI_SLOT(18) BFME_UI_SLOT(19)
	BFME_UI_SLOT(20) BFME_UI_SLOT(21) BFME_UI_SLOT(22) BFME_UI_SLOT(23)
	BFME_UI_SLOT(24) BFME_UI_SLOT(25)
	virtual void clearMode68(Bool enabled) = 0;
	BFME_UI_SLOT(27) BFME_UI_SLOT(28) BFME_UI_SLOT(29) BFME_UI_SLOT(30)
	BFME_UI_SLOT(31) BFME_UI_SLOT(32) BFME_UI_SLOT(33) BFME_UI_SLOT(34)
	BFME_UI_SLOT(35) BFME_UI_SLOT(36) BFME_UI_SLOT(37) BFME_UI_SLOT(38)
	BFME_UI_SLOT(39) BFME_UI_SLOT(40) BFME_UI_SLOT(41)
	virtual void setSelecting(Bool selecting) = 0;
	BFME_UI_SLOT(43) BFME_UI_SLOT(44) BFME_UI_SLOT(45) BFME_UI_SLOT(46)
	BFME_UI_SLOT(47) BFME_UI_SLOT(48) BFME_UI_SLOT(49) BFME_UI_SLOT(50)
	BFME_UI_SLOT(51) BFME_UI_SLOT(52) BFME_UI_SLOT(53) BFME_UI_SLOT(54)
	BFME_UI_SLOT(55) BFME_UI_SLOT(56) BFME_UI_SLOT(57) BFME_UI_SLOT(58)
	BFME_UI_SLOT(59) BFME_UI_SLOT(60) BFME_UI_SLOT(61) BFME_UI_SLOT(62)
	BFME_UI_SLOT(63) BFME_UI_SLOT(64) BFME_UI_SLOT(65) BFME_UI_SLOT(66)
	BFME_UI_SLOT(67) BFME_UI_SLOT(68) BFME_UI_SLOT(69) BFME_UI_SLOT(70)
	virtual void clearMode11C() = 0;
	virtual void setInputEnabled(Bool enable);
#undef BFME_UI_SLOT

private:
	unsigned char m_pad04[0x834];
	Bool m_inputEnabled;
	unsigned char m_pad839[0x12B0 - 0x839];
	Bool m_modes[12];
};

void InGameUI::setInputEnabled(Bool enable)
{
	Bool wasEnabled = m_inputEnabled;
	m_inputEnabled = enable;

	if (!wasEnabled && enable)
	{
		if (TheSelectionTranslator)
			TheSelectionTranslator->setDragSelecting();
		setSelecting(false);
		clearMode68(false);
		clearMode11C();
		m_modes[1] = false;
		m_modes[2] = false;
		m_modes[0] = false;
		m_modes[3] = false;
		m_modes[4] = false;
		m_modes[5] = false;
		m_modes[6] = false;
		m_modes[7] = false;
		m_modes[8] = false;
		m_modes[9] = false;
		m_modes[10] = false;
		m_modes[11] = false;
	}
}
