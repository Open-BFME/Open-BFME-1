// ?updateAnimateWindow@ProcessAnimateWindowSlideFromTopFast@@UAE_NPAVAnimateWindow@@@Z
// cl: /DNDEBUG /MD /EHsc
// Retail 0x00497140, 237 bytes. This is a relocation-masked byte twin of
// ProcessAnimateWindowSlideFromTop::updateAnimateWindow at 0x00496130.

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
	virtual ~AnimateWindow(void);

	UnsignedInt getStartTime(void) { return m_startTime; }
	GameWindow *getGameWindow(void) { return m_gameWindow; }
	const ICoord2D &getCurPos(void) { return m_curPos; }
	const ICoord2D &getEndPos(void) { return m_endPos; }
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
	unsigned char m_padding[5];
	Bool m_isFinished;
};

class ProcessAnimateWindowSlideFromTopFast
{
public:
	virtual void initReverseAnimateWindow(AnimateWindow *, UnsignedInt);
	virtual void initAnimateWindow(AnimateWindow *);
	virtual Bool updateAnimateWindow(AnimateWindow *);
	virtual Bool reverseAnimateWindow(AnimateWindow *);

private:
	Coord2D m_maxVel;
	Int m_slowDownThreshold;
	Real m_slowDownRatio;
	Real m_speedUpRatio;
};

extern "C" UnsignedInt __stdcall bfme_timeGetTime(void);

Bool ProcessAnimateWindowSlideFromTopFast::updateAnimateWindow(AnimateWindow *animWin)
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

	if (curPos.y > endPos.y)
	{
		curPos.y = endPos.y;
		win->winSetPosition(curPos.x, curPos.y);
		animWin->setFinished(true);
		return true;
	}

	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);

	if (endPos.y - curPos.y <= m_slowDownThreshold)
		vel.y *= m_slowDownRatio;

	if (vel.y < 1.0f)
		vel.y = 1.0f;

	animWin->setVel(vel);
	return false;
}
