// cl: /DNDEBUG /MD /EHsc
// readable body of ?initAnimateWindow@ProcessAnimateWindowSlideFromTop@@UAEXPAVAnimateWindow@@@Z: Code/GameEngine/Source/GameClient/GUI/ProcessAnimateWindow.cpp
// readable body of ?initAnimateWindow@ProcessAnimateWindowSlideFromBottomTimed@@UAEXPAVAnimateWindow@@@Z: Code/GameEngine/Source/GameClient/GUI/ProcessAnimateWindow.cpp
// readable body of ?initAnimateWindow@ProcessAnimateWindowSlideFromRightFast@@UAEXPAVAnimateWindow@@@Z: Code/GameEngine/Source/GameClient/GUI/ProcessAnimateWindow.cpp
//
// Three slide processors' initAnimateWindow overrides, at 0x00496000,
// 0x00496920 and 0x004974F0. All three do the same four things -- read the
// window's resting position, push it off-screen by one screen dimension, move
// the window there, and hand the layout the start, rest and velocity to
// interpolate between -- and each used to carry its own copy of the six classes
// that takes: 353 lines across three files become 191 in one.
//
// What actually differs between them is three lines apiece:
//   SlideFromTop        starts a screen height ABOVE rest and travels at the
//                       processor's full velocity in both axes.
//   SlideFromBottomTimed starts a screen height BELOW rest with zero velocity,
//                       because it is the timed variant: it passes an end time
//                       of now + delay + m_maxDuration and lets the layout
//                       interpolate, where the others pass 0 and coast.
//   SlideFromRightFast  starts off the RIGHT edge, so its travel has to clear
//                       the window's own width as well, and it pins vel.y to 0
//                       and clears the finished flag first.
//
// The merged AnimateWindow is the union of the three views: only
// SlideFromRightFast reads past m_gameWindow, so the finished flag at +0x41 and
// the padding that carries it there cost the other two nothing.

typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;

struct ICoord2D
{
	Int x;
	Int y;
};

struct BFMECoord2D
{
	Real x;
	Real y;

	BFMECoord2D(void) {}
	BFMECoord2D(Real x_, Real y_) : x(x_), y(y_) {}
	BFMECoord2D(const BFMECoord2D &that) : x(that.x), y(that.y) {}
	~BFMECoord2D(void) {}
};

class GameWindow
{
public:
	Int winGetPosition(Int *x, Int *y);
	Int winGetSize(Int *x, Int *y);
	Int winSetPosition(Int x, Int y);
};

class AnimateWindow
{
public:
	virtual void unused(void) = 0;

	UnsignedInt getDelay(void) const { return m_delay; }
	GameWindow *getGameWindow(void) { return m_gameWindow; }
	void setFinished(unsigned char value) { m_finished = value; }

private:
	UnsignedInt m_delay;
	unsigned char m_padding0[0x20];
	GameWindow *m_gameWindow;
	unsigned char m_padding1[0x15];
	unsigned char m_finished;
};

class Display
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
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual UnsignedInt getWidth(void) = 0;
};

class BFMEAnimateWindowLayout
{
public:
	void setAnimData(ICoord2D startPos, ICoord2D endPos, ICoord2D curPos,
		ICoord2D restPos, BFMECoord2D vel, UnsignedInt startTime,
		UnsignedInt endTime);
};

extern Display *TheDisplay;
extern "C" UnsignedInt __stdcall bfme_timeGetTime(void);

class ProcessAnimateWindowSlideFromTop
{
public:
	virtual void initAnimateWindow(AnimateWindow *animWin);

	BFMECoord2D m_maxVel;
};

class ProcessAnimateWindowSlideFromBottomTimed
{
public:
	virtual void initAnimateWindow(AnimateWindow *animWin);

	UnsignedInt m_maxDuration;
};

class ProcessAnimateWindowSlideFromRightFast
{
public:
	virtual void initAnimateWindow(AnimateWindow *animWin);

	BFMECoord2D m_maxVel;
};

// ?initAnimateWindow@ProcessAnimateWindowSlideFromTop@@UAEXPAVAnimateWindow@@@Z
// Retail 0x00496000, 235 bytes.
void ProcessAnimateWindowSlideFromTop::initAnimateWindow(AnimateWindow *animWin)
{
	ICoord2D restPos = {0, 0};
	ICoord2D startPos = {0, 0};
	ICoord2D curPos = {0, 0};
	ICoord2D endPos = {0, 0};
	BFMECoord2D vel;

	if (!animWin)
		return;

	GameWindow *win = animWin->getGameWindow();
	if (!win)
		return;

	win->winGetPosition(&restPos.x, &restPos.y);
	endPos.x = restPos.x;
	endPos.y = restPos.y;

	Int travelDistance = TheDisplay->getWidth();
	startPos.x = curPos.x = restPos.x;
	startPos.y = curPos.y = restPos.y - travelDistance;

	win->winSetPosition(startPos.x, startPos.y);

	vel.x = m_maxVel.x;
	vel.y = m_maxVel.y;

	((BFMEAnimateWindowLayout *)animWin)->setAnimData(startPos, endPos, curPos,
		restPos, vel, bfme_timeGetTime() + animWin->getDelay(), 0);
}

// ?initAnimateWindow@ProcessAnimateWindowSlideFromBottomTimed@@UAEXPAVAnimateWindow@@@Z
// Retail 0x00496920, 226 bytes.
void ProcessAnimateWindowSlideFromBottomTimed::initAnimateWindow(AnimateWindow *animWin)
{
	ICoord2D restPos = {0, 0};
	ICoord2D startPos = {0, 0};
	ICoord2D curPos = {0, 0};
	ICoord2D endPos = {0, 0};
	BFMECoord2D vel(0.0f, 0.0f);

	if (!animWin)
		return;

	GameWindow *win = animWin->getGameWindow();
	if (!win)
		return;

	win->winGetPosition(&restPos.x, &restPos.y);
	endPos.x = restPos.x;
	endPos.y = restPos.y;

	Int travelDistance = TheDisplay->getWidth();
	startPos.x = curPos.x = restPos.x;
	startPos.y = curPos.y = restPos.y + travelDistance;

	win->winSetPosition(startPos.x, startPos.y);

	UnsignedInt now = bfme_timeGetTime();
	UnsignedInt delay = animWin->getDelay();
	((BFMEAnimateWindowLayout *)animWin)->setAnimData(startPos, endPos, curPos,
		restPos, vel, now + delay, now + m_maxDuration + delay);
}

// ?initAnimateWindow@ProcessAnimateWindowSlideFromRightFast@@UAEXPAVAnimateWindow@@@Z
// Retail 0x004974F0, 263 bytes.
void ProcessAnimateWindowSlideFromRightFast::initAnimateWindow(AnimateWindow *animWin)
{
	ICoord2D restPos = {0, 0};
	ICoord2D startPos = {0, 0};
	ICoord2D curPos = {0, 0};
	ICoord2D endPos = {0, 0};
	ICoord2D size = {0, 0};
	BFMECoord2D vel;

	if (!animWin)
		return;

	animWin->setFinished(0);

	GameWindow *win = animWin->getGameWindow();
	if (!win)
		return;

	win->winGetPosition(&restPos.x, &restPos.y);
	win->winGetSize(&size.x, &size.y);
	endPos.x = restPos.x;
	endPos.y = restPos.y;

	Int travelDistance = TheDisplay->getWidth() - restPos.x + size.x;
	startPos.x = curPos.x = restPos.x + travelDistance;
	startPos.y = curPos.y = restPos.y;

	win->winSetPosition(startPos.x, startPos.y);

	vel.x = m_maxVel.x;
	vel.y = 0.0f;

	((BFMEAnimateWindowLayout *)animWin)->setAnimData(startPos, endPos, curPos,
		restPos, vel, bfme_timeGetTime() + animWin->getDelay(), 0);
}
