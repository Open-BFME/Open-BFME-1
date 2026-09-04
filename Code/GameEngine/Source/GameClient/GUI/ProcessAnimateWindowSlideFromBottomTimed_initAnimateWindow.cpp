// cl: /DNDEBUG /MD /EHsc
// readable body of
// ?initAnimateWindow@ProcessAnimateWindowSlideFromBottomTimed@@UAEXPAVAnimateWindow@@@Z:
// Code/GameEngine/Source/GameClient/GUI/ProcessAnimateWindow.cpp
//
// Retail 0x00496920, 226 bytes. Bottom travel (restPos.y + Display width)
// with zero velocity and endTime = now + delay + m_maxDuration.

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
	Int winSetPosition(Int x, Int y);
};

class AnimateWindow
{
public:
	virtual void unused(void) = 0;

	UnsignedInt getDelay(void) const { return m_delay; }
	GameWindow *getGameWindow(void) { return m_gameWindow; }

private:
	UnsignedInt m_delay;
	unsigned char m_padding[0x20];
	GameWindow *m_gameWindow;
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

class ProcessAnimateWindowSlideFromBottomTimed
{
public:
	virtual void initAnimateWindow(AnimateWindow *animWin);

	UnsignedInt m_maxDuration;
};

// ?initAnimateWindow@ProcessAnimateWindowSlideFromBottomTimed@@UAEXPAVAnimateWindow@@@Z
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
