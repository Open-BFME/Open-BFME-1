// ?updateAnimateWindow@ProcessAnimateWindowSlideFromRightFast@@UAE_NPAVAnimateWindow@@@Z
// partial score=0.96 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc
// Readable body of ?updateAnimateWindow@ProcessAnimateWindowSlideFromRightFast@@UAE_NPAVAnimateWindow@@@Z.
// Retail 0x00497640, 230 bytes.  This is the x-axis update used by the
// SlideFromRightFast process selected in AnimateWindowManager.

typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;
typedef bool Bool;

extern const Real BfmeShadowScale;

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
	Real length(void) const;
	void normalize(void);
	Real toAngle(void) const;
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
	int m_animType;
	Bool m_needsToFinish;
	Bool m_finished;
};

class ProcessAnimateWindowSlideFromRightFast
{
public:
	virtual ~ProcessAnimateWindowSlideFromRightFast();
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

// ?updateAnimateWindow@ProcessAnimateWindowSlideFromRightFast@@UAE_NPAVAnimateWindow@@@Z
Bool ProcessAnimateWindowSlideFromRightFast::updateAnimateWindow(AnimateWindow *animWin)
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
		vel.x *= m_slowDownRatio;
	if (vel.x >= BfmeShadowScale)
		vel.x = BfmeShadowScale;
	animWin->setVel(vel);
	return false;
}
