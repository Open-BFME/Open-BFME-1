// cl: /DNDEBUG /MD /EHsc
// readable body of ?initAnimateWindow@ProcessAnimateWindowSlideFromRightFast@@UAEXPAVAnimateWindow@@@Z: Code/GameEngine/Source/GameClient/GUI/ProcessAnimateWindow.cpp
//
// Retail 0x004974F0, 263 bytes. Off-screen to the right by
// Display::getWidth() - rest.x + size.x; vel.y forced to 0.

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

class ProcessAnimateWindowSlideFromRightFast
{
public:
	virtual void initAnimateWindow(AnimateWindow *animWin);

	BFMECoord2D m_maxVel;
};

// ?initAnimateWindow@ProcessAnimateWindowSlideFromRightFast@@UAEXPAVAnimateWindow@@@Z
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
