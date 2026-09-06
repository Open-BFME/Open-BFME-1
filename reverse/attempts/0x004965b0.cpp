// ?updateAnimateWindow@ProcessAnimateWindowSlideFromBottom@@UAE_NPAVAnimateWindow@@@Z
// partial score=0.95 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Readable body of ?updateAnimateWindow@ProcessAnimateWindowSlideFromBottom@@UAE_NPAVAnimateWindow@@@Z.
// Retail 0x004965B0, 238 bytes.  This is the y-axis update used by the
// SlideFromBottom process selected in AnimateWindowManager.

typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;
typedef bool Bool;

// Retail's -1.0f clamp is the address-pinned BfmeShadowScale field at 0x0109BF3C.
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

class ProcessAnimateWindowSlideFromBottom
{
public:
	virtual ~ProcessAnimateWindowSlideFromBottom();
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

// ?updateAnimateWindow@ProcessAnimateWindowSlideFromBottom@@UAE_NPAVAnimateWindow@@@Z
Bool ProcessAnimateWindowSlideFromBottom::updateAnimateWindow(AnimateWindow *animWin)
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
	curPos.y += (Int)vel.y;

	if (curPos.y < endPos.y)
	{
		curPos.y = endPos.y;
		animWin->setFinished(true);
		win->winSetPosition(curPos.x, curPos.y);
		return true;
	}

	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);

	if (curPos.y - endPos.y <= m_slowDownThreshold)
		vel.y *= m_slowDownRatio;
	if (vel.y >= BfmeShadowScale)
		vel.y = BfmeShadowScale;
	animWin->setVel(vel);
	return false;
}


