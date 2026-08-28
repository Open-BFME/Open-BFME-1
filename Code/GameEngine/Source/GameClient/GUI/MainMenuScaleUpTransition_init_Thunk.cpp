// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// readable body of ?init@MainMenuScaleUpTransition@@UAEXPAVGameWindow@@@Z: Code/GameEngine/Source/GameClient/GUI/GameWindowTransitionsStyles.cpp
// Lift the MainMenuScaleUpTransition::init naked dump to clean C++.
//
// Zero Hour's GameWindowTransitionsStyles.cpp body. Same BFME parameterisation
// as the matching update: the frame passed to update and the divisor of the
// four increments both come from members -- this+0x10 and this+0x14 -- where ZH
// uses MAINMENUSCALEUPTRANSITION_START and _END.
//
// winGetDisabledImage does not survive as a call: retail reads the image
// straight out of the window at win+0xB4, so the accessor is inline over an
// array rather than the out-of-line method the other two window calls use.
//
// The layout agrees with the FullFadeTransition conversion done earlier -- same
// winGetSize and winGetScreenPosition thunks, m_pos at +0x18 and m_size at
// +0x20 -- and extends it: the grow window's position and size land at +0x2C
// and +0x34, the four increments at +0x3C through +0x48, and m_growWin at
// +0x4C, which is where the update method reads it.

typedef int Int;
typedef unsigned char Bool;

class Image;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x;
	Int y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	Int winGetSize(Int *width, Int *height);			///< ILT thunk at 0x00036EBC
	Int winGetScreenPosition(Int *x, Int *y);			///< ILT thunk at 0x0002F94B
	Int winSetEnabledImage(Int index, const Image *image);	///< ILT thunk at 0x00035E09

	const Image *winGetDisabledImage(Int index) const { return m_disabledImage[index]; }

private:
	unsigned char m_unreconstructed_00[0xB4];
	const Image *m_disabledImage[1];					///< retail this+0xB4
};

enum NameKeyType { NAMEKEY_INVALID = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);			///< ILT thunk at 0x0003ADD7
};

extern NameKeyGenerator *TheNameKeyGenerator;			///< retail [0x012ED600]

// Only the lookup is reconstructed; the slots ahead of it place it.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();
	virtual void unused42();
	virtual void unused43();
	virtual void unused44();
	virtual void unused45();
	virtual void unused46();
	virtual void unused47();
	virtual void unused48();
	virtual void unused49();
	virtual void unused50();
	virtual void unused51();
	virtual void unused52();
	virtual void unused53();
	virtual void unused54();

	virtual GameWindow *winGetWindowFromId(GameWindow *window, NameKeyType id);	///< vtable +0xDC
};

extern GameWindowManager *TheWindowManager;				///< retail [0x012F1B40]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h
class MainMenuScaleUpTransition
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void update(Int frame);						///< vtable +0x08

	virtual void init(GameWindow *win);

private:
	unsigned char m_unreconstructed_04[8 - 4];
	Bool m_isFinished;									///< retail this+0x08
	Bool m_isForward;									///< retail this+0x09
	unsigned char m_unreconstructed_0A[2];
	GameWindow *m_win;									///< retail this+0x0C
	Int m_startFrame;									///< retail this+0x10
	Int m_endFrame;										///< retail this+0x14
	ICoord2D m_pos;										///< retail this+0x18
	ICoord2D m_size;									///< retail this+0x20
	Int m_drawState;									///< retail this+0x28
	ICoord2D m_growPos;									///< retail this+0x2C
	ICoord2D m_growSize;								///< retail this+0x34
	ICoord2D m_incrementPos;							///< retail this+0x3C
	ICoord2D m_incrementSize;							///< retail this+0x44
	GameWindow *m_growWin;								///< retail this+0x4C
};

// ?init@MainMenuScaleUpTransition@@UAEXPAVGameWindow@@@Z
void MainMenuScaleUpTransition::init( GameWindow *win )
{
	if(win)
	{
		m_win = win;
		m_win->winGetSize(&m_size.x, &m_size.y);
		m_win->winGetScreenPosition(&m_pos.x, &m_pos.y );
	}
	m_growWin = TheWindowManager->winGetWindowFromId(0, TheNameKeyGenerator->nameToKey("MainMenu.wnd:WinGrowMarker"));
	if(!m_growWin)
		return;

	m_growWin->winGetSize(&m_growSize.x, &m_growSize.y);
	m_growWin->winGetScreenPosition(&m_growPos.x, &m_growPos.y );

	m_isForward = 0;
	update(m_startFrame);
	m_isFinished = 0;
	m_isForward = 1;
	m_incrementPos.x = (m_growPos.x - m_pos.x)  / m_endFrame;
	m_incrementPos.y = (m_growPos.y - m_pos.y)  / m_endFrame;
	m_incrementSize.x = (m_growSize.x - m_size.x) / m_endFrame;
	m_incrementSize.y = (m_growSize.y - m_size.y) / m_endFrame;
	const Image *image = m_win->winGetDisabledImage(0);
	m_growWin->winSetEnabledImage(0, image);

}
