// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// readable body of ?update@MainMenuMediumScaleUpTransition@@UAEXH@Z: Code/GameEngine/Source/GameClient/GUI/GameWindowTransitionsStyles.cpp
// Lift the MainMenuMediumScaleUpTransition::update naked dump to clean C++.
//
// Zero Hour's GameWindowTransitionsStyles.cpp body with two BFME differences.
//
// First, the frame bounds are data rather than constants: retail compares
// against this+0x10 and this+0x14 where ZH uses MAINMENUMEDIUMSCALEUPTRANSITION_START
// and _END. That is the same parameterisation already seen in
// FullFadeTransition::init, and it has a knock-on effect -- ZH's switch cannot
// survive, because a switch needs constant cases, so the two frame tests are an
// if/else-if chain.
//
// Second, ZH's audio block -- guarded by `frame == 1 && m_isForward` and
// building an AudioEventRTS -- is absent.
// Retail could not have it: that temporary has a destructor and would have
// forced an SEH frame onto a function that has none.
//
// Retail pins the layout: m_isFinished and m_isForward are adjacent bytes at
// +0x08 and +0x09, m_win at +0x0C, the frame bounds at +0x10 and +0x14,
// m_drawState at +0x28 and m_growWin at +0x44.

typedef int Int;
typedef unsigned char Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	void winHide(Bool hide);							///< ILT thunk at 0x00027F2A
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h
class MainMenuMediumScaleUpTransition
{
public:
	virtual void update(Int frame);

private:
	// the vtable pointer occupies +0x00
	unsigned char m_unreconstructed_04[8 - 4];
	Bool m_isFinished;									///< retail this+0x08
	Bool m_isForward;									///< retail this+0x09
	unsigned char m_unreconstructed_0A[2];
	GameWindow *m_win;									///< retail this+0x0C
	Int m_startFrame;									///< retail this+0x10
	Int m_endFrame;										///< retail this+0x14
	unsigned char m_unreconstructed_18[0x28 - 0x18];
	Int m_drawState;									///< retail this+0x28
	unsigned char m_unreconstructed_2C[0x44 - 0x2C];
	GameWindow *m_growWin;								///< retail this+0x44
};

// ?update@MainMenuMediumScaleUpTransition@@UAEXH@Z
void MainMenuMediumScaleUpTransition::update( Int frame )
{
	m_drawState = -1;
	if(frame < m_startFrame || frame > m_endFrame)
	{
		return;
	}

	if (frame == m_startFrame)
	{
		if(!m_isForward && m_win && m_growWin)
		{
			m_win->winHide(0);
			m_growWin->winHide(1);
			m_isFinished = 1;
		}
	}
	else if (frame == m_endFrame)
	{
		if(m_isForward && m_win && m_growWin)
		{
			m_win->winHide(1);
			m_growWin->winHide(0);
			m_isFinished = 1;
		}
	}

	if(frame > m_startFrame && frame < m_endFrame)
	{
		if(m_win)
			m_win->winHide(1);
		if(m_growWin)
			m_growWin->winHide(1);
		m_drawState = frame;
	}

}
