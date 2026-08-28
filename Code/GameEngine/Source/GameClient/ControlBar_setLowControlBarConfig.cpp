// cl: /DNDEBUG /MD /EHsc
// readable body of ?setLowControlBarConfig@ControlBar@@IAEXXZ: Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp
// Open-BFME: ControlBar::setLowControlBarConfig, retail 0x0049E120, 136 bytes.
//
// The reference's body once its commented-out head is gone: record the stage,
// put the bar a tenth of the screen up from the bottom, give the tactical view
// the whole screen height, move and unhide the master context parent, and tail
// into setUpDownImages.
//
// The one thing the reference leaves ambiguous is where the truncation
// happens. Retail converts only the tenth -- fild, multiply by 0.1, ftol --
// and subtracts that integer from a freshly fetched height, so the cast sits
// on the second term rather than around the whole expression. getHeight is
// fetched three times and is unsigned, the fild carrying the 2^32 fixup.
//
// The layout falls out with it: the default position at this+0x18, the stage
// at +0x20, and the context parents from +0x34 with the master first.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum { CONTROL_BAR_STAGE_LOW = 2 };
enum { CP_MASTER = 0, CP_COUNT = 8 };

struct ICoord2D { Int x, y; };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Display.h
class Display
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual UnsignedInt getHeight(void) = 0;		// slot 12, vtable+0x30
};

extern Display *TheDisplay;					// 0x012F1270

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/View.h
class View
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void setHeight(Int height) = 0;			// slot 16, vtable+0x40
};

extern View *TheTacticalView;					// 0x012F1600

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	Int winSetPosition(Int x, Int y);			// ILT 0x0001949D
	Int winHide(Bool hide);				// ILT 0x00027F2A
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
protected:
	void setLowControlBarConfig(void);
	void setUpDownImages(void);				// ILT 0x0000D869

	char m_slice_pad[0x18];					// retail this+0x00 .. +0x17, untouched
	ICoord2D m_defaultControlBarPosition;			// this+0x18
	Int m_currentControlBarStage;				// this+0x20
	char m_slice_padB[0x34 - 0x24];				// this+0x24 .. +0x33, untouched
	GameWindow *m_contextParent[CP_COUNT];			// this+0x34
};

void ControlBar::setLowControlBarConfig( void )
{
	m_currentControlBarStage = CONTROL_BAR_STAGE_LOW;
	ICoord2D pos;
	pos.x = m_defaultControlBarPosition.x;
	pos.y = TheDisplay->getHeight() - (Int)(.1 * TheDisplay->getHeight());
	TheTacticalView->setHeight((Int)(TheDisplay->getHeight()));
	m_contextParent[ CP_MASTER ]->winSetPosition(pos.x, pos.y);
	m_contextParent[ CP_MASTER ]->winHide(false);
	setUpDownImages();

}
