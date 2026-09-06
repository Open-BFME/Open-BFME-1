// ?updateAnimateWindow@ProcessAnimateWindowSlideFromRight@@UAE_NPAVAnimateWindow@@@Z
// partial score=0.96 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: ProcessAnimateWindowSlideFromRight::updateAnimateWindow at
// 0x00495850 (230 B) and its SlideFromRightFast sibling at 0x00497640, built
// on the class shapes of the landed SlideFromRight reverseAnimateWindow TU.
// readable body of ?reverseAnimateWindow@ProcessAnimateWindowSlideFromRight@@UAE_NPAVAnimateWindow@@@Z: Code/GameEngine/Source/GameClient/GUI/ProcessAnimateWindow.cpp
//
// Retail 0x00495970, 260 bytes. After initAnimateWindow SlideFromRight
// (0x00495730) and before ctor SlideFromLeft (0x00495AC0). Same shape as
// SlideFromTopFast reverse with x-axis compare/clamp from the ZH twin.

typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;
typedef bool Bool;

struct ICoord2D
{
	Int x;
	Int y;
};

struct Coord2D
{
	Real x;
	Real y;
	Coord2D(void) {}
	Coord2D(const Coord2D &that) : x(that.x), y(that.y) {}
	~Coord2D(void) {}
};

class GameWindow
{
public:
	Int winSetPosition(Int x, Int y);
};

class AnimateWindow
{
public:
	virtual void unused(void) = 0;

	UnsignedInt getStartTime(void) { return m_startTime; }
	GameWindow *getGameWindow(void) { return m_gameWindow; }
	ICoord2D getCurPos(void) { return m_curPos; }
	ICoord2D getStartPos(void) { return m_startPos; }
	ICoord2D getEndPos(void) { return m_endPos; }
	Coord2D getVel(void);
	Bool isFinished(void) { return m_finished; }
	void setFinished(Bool finished) { m_finished = finished; }
	void setCurPos(ICoord2D pos) { m_curPos = pos; }
	void setVel(Coord2D vel) { m_vel = vel; }

private:
	UnsignedInt m_delay;
	ICoord2D m_startPos;
	ICoord2D m_endPos;
	ICoord2D m_curPos;
	ICoord2D m_restPos;
	GameWindow *m_gameWindow;
	Coord2D m_vel;
	UnsignedInt m_startTime;
	UnsignedInt m_endTime;
	unsigned char m_padding[5];
	Bool m_finished;
};

class ProcessAnimateWindowSlideFromRight
{
public:
	virtual ~ProcessAnimateWindowSlideFromRight();
	virtual void initAnimateWindow(AnimateWindow *);
	virtual void initReverseAnimateWindow(AnimateWindow *, UnsignedInt);
	virtual Bool updateAnimateWindow(AnimateWindow *);
	virtual Bool reverseAnimateWindow(AnimateWindow *);

private:
	Coord2D m_maxVel;
	Int m_slowDownThreshold;
	Real m_slowDownRatio;
	Real m_speedUpRatio;
};

extern "C" UnsignedInt __stdcall bfme_timeGetTime(void);

static const Real BfmeMinSlideVelocity = -1.0f;

Bool ProcessAnimateWindowSlideFromRight::updateAnimateWindow(AnimateWindow *animWin)
{
	if (!animWin)
		return true;
	if (animWin->isFinished())
		return true;
	if (bfme_timeGetTime() < animWin->getStartTime())
		return false;
	GameWindow *win = animWin->getGameWindow();
	if (!win)
		return true;
	ICoord2D curPos = animWin->getCurPos();
	ICoord2D endPos = animWin->getEndPos();
	Coord2D vel = animWin->getVel();
	curPos.x += (Int)vel.x;
	if (curPos.x < endPos.x)
	{
		curPos.x = endPos.x;
		animWin->setFinished(true);
		return true;
	}
	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);
	if (curPos.x - endPos.x <= m_slowDownThreshold)
	{
		vel.x *= m_slowDownRatio;
	}
	if (vel.x >= BfmeMinSlideVelocity)
		vel.x = BfmeMinSlideVelocity;
	animWin->setVel(vel);
	return false;
}
