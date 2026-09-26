// ?updateAnimateWindow@ProcessAnimateWindowSlideFromLeft@@UAE_NPAVAnimateWindow@@@Z
// cl: /DNDEBUG /MD /EHsc
// Retail 0x00495CC0, 230 bytes. The layout and control flow mirror the exact
// SlideFromRight implementation; the horizontal comparisons and clamp face
// the opposite direction.

typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;
typedef bool Bool;

extern const Real g_bfmeDefaultBU;

struct ICoord2D
{
	Int x;
	Int y;
};

struct Coord2D
{
	Real x;
	Real y;
	Coord2D(const Coord2D &that) throw() : x(that.x), y(that.y) {}
	~Coord2D(void) throw() {}
};

class GameWindow
{
public:
	Int winSetPosition(Int x, Int y);
};

class AnimateWindow
{
public:
	virtual ~AnimateWindow(void);

	UnsignedInt getStartTime(void) { return m_startTime; }
	GameWindow *getGameWindow(void) { return m_gameWindow; }
	ICoord2D getCurPos(void) { return m_curPos; }
	ICoord2D getEndPos(void) { return m_endPos; }
	Coord2D getVel(void) { return m_vel; }
	Bool isFinished(void) { return m_isFinished; }
	void setFinished(Bool finished) { m_isFinished = finished; }
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
	int m_animType;
	Bool m_needsToFinish;
	Bool m_isFinished;
};

class ProcessAnimateWindow
{
public:
	virtual ~ProcessAnimateWindow(void) {}
	virtual void initAnimateWindow(AnimateWindow *) = 0;
	virtual void initReverseAnimateWindow(AnimateWindow *, UnsignedInt) = 0;
	virtual Bool updateAnimateWindow(AnimateWindow *) = 0;
	virtual Bool reverseAnimateWindow(AnimateWindow *) = 0;
};

class ProcessAnimateWindowSlideFromLeft : public ProcessAnimateWindow
{
public:
	virtual ~ProcessAnimateWindowSlideFromLeft();
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

Bool ProcessAnimateWindowSlideFromLeft::updateAnimateWindow(AnimateWindow *animWin)
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

	if (curPos.x > endPos.x)
	{
		curPos.x = endPos.x;
		animWin->setFinished(true);
		return true;
	}

	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);

	if (endPos.x - curPos.x <= m_slowDownThreshold)
		vel.x *= m_slowDownRatio;
	if (vel.x < g_bfmeDefaultBU)
		vel.x = g_bfmeDefaultBU;
	animWin->setVel(vel);
	return false;
}
