// cl: /DNDEBUG /MD /EHs-c-
// Lift the FullFadeTransition::init __emit thunk to clean C++.
//
// Zero Hour's GameWindowTransitionsStyles.cpp carries this body, but BFME
// parameterised what ZH hard-codes. ZH calls update(FULLFADETRANSITION_START)
// and divides by the FULLFADETRANSITION_END constant; retail reads both from
// the object instead -- the update argument comes from this+0x10 and the frame
// count from this+0x14 -- so the transition length is data rather than a
// compile-time constant here.
//
// Retail pins the rest of the layout: m_isFinished and m_isForward are adjacent
// bytes at +0x08/+0x09, m_win at +0x0C, m_pos at +0x18/+0x1C, m_size at
// +0x20/+0x24 and m_percent at +0x28. update is the virtual at vtable +0x08.
//
// The halving is `cdq / sub / sar 1`, MSVC's signed divide by two, so the frame
// count is a signed Int rather than unsigned.

typedef int Int;
typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	Int winGetSize(Int *width, Int *height);				///< ILT thunk at 0x00036EBC
	Int winGetScreenPosition(Int *x, Int *y);				///< ILT thunk at 0x0002F94B
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h
class FullFadeTransition
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void update(Int frame);							///< vtable +0x08

	virtual void init(GameWindow *win);

private:
	unsigned char m_unreconstructed_04[4];
	unsigned char m_isFinished;								///< retail this+0x08
	unsigned char m_isForward;								///< retail this+0x09
	unsigned char m_unreconstructed_0A[2];
	GameWindow *m_win;										///< retail this+0x0C
	Int m_startFrame;										///< retail this+0x10
	Int m_endFrame;											///< retail this+0x14
	Int m_posX;												///< retail this+0x18
	Int m_posY;												///< retail this+0x1C
	Int m_sizeX;											///< retail this+0x20
	Int m_sizeY;											///< retail this+0x24
	Real m_percent;											///< retail this+0x28
};

// ?init@FullFadeTransition@@UAEXPAVGameWindow@@@Z
void FullFadeTransition::init(GameWindow *win)
{
	if (win)
	{
		m_win = win;
		m_win->winGetSize(&m_sizeX, &m_sizeY);
		m_win->winGetScreenPosition(&m_posX, &m_posY);
	}

	m_isForward = 0;
	update(m_startFrame);
	m_isFinished = 0;
	m_isForward = 1;

	m_percent = 1.0f / (m_endFrame / 2);
}
