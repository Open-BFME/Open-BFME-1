// cl: /DNDEBUG /MD /EHsc
// readable body of ?reverseAnimateWindow@ProcessAnimateWindowSlideFromRight@@UAE_NPAVAnimateWindow@@@Z: Code/GameEngine/Source/GameClient/GUI/ProcessAnimateWindow.cpp
// readable body of ?reverseAnimateWindow@ProcessAnimateWindowSlideFromTopFast@@UAE_NPAVAnimateWindow@@@Z: Code/GameEngine/Source/GameClient/GUI/ProcessAnimateWindow.cpp
//
// The reverse step of two slide processors, at 0x00495970 and 0x00497270. It is
// the per-frame half of the reversal that initReverseAnimateWindow sets up: it
// advances the window one velocity step back towards where it started, and
// returns true once it is home or there is nothing left to move.
//
// The two bodies are the same walk down different axes -- SlideFromRight along
// x, SlideFromTopFast along y -- and each carried its own copy of ICoord2D,
// Coord2D, GameWindow and the whole 0x42-byte AnimateWindow to say so: 255
// lines across two files become 212 in one, half of which is the two bodies.
//
// Velocity is negative on the way back, so the two comparisons that look
// inverted between the bodies are the same test: SlideFromRight has arrived
// when curPos.x rises above startPos.x, SlideFromTopFast when curPos.y falls
// below startPos.y, and each clamps the next velocity against -m_maxVel from
// the side its axis approaches from.

typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x;
	Int y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord2D
{
	Real x;
	Real y;
	Coord2D(void) {}
	Coord2D(const Coord2D &that) : x(that.x), y(that.y) {}
	~Coord2D(void) {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	Int winSetPosition(Int x, Int y);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/AnimateWindowManager.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ProcessAnimateWindow.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ProcessAnimateWindow.h
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

// ?reverseAnimateWindow@ProcessAnimateWindowSlideFromRight@@UAE_NPAVAnimateWindow@@@Z
// Retail 0x00495970, 260 bytes.
Bool ProcessAnimateWindowSlideFromRight::reverseAnimateWindow(AnimateWindow *animWin)
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
	ICoord2D startPos = animWin->getStartPos();
	Coord2D vel = animWin->getVel();
	curPos.x += (Int)vel.x;

	if (curPos.x > startPos.x)
	{
		curPos.x = startPos.x;
		animWin->setFinished(true);
		win->winSetPosition(curPos.x, curPos.y);
		return true;
	}

	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);

	ICoord2D endPos = animWin->getEndPos();
	Real nextVelocity;
	if (curPos.x - endPos.x <= m_slowDownThreshold)
		nextVelocity = vel.x * m_speedUpRatio;
	else
		nextVelocity = -m_maxVel.x;

	const Real clampVelocity = -m_maxVel.x;
	if (nextVelocity > clampVelocity)
		nextVelocity = clampVelocity;
	vel.x = nextVelocity;

	animWin->setVel(vel);
	return false;
}

// ?reverseAnimateWindow@ProcessAnimateWindowSlideFromTopFast@@UAE_NPAVAnimateWindow@@@Z
// Retail 0x00497270, 263 bytes.
Bool ProcessAnimateWindowSlideFromTopFast::reverseAnimateWindow(AnimateWindow *animWin)
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
	ICoord2D startPos = animWin->getStartPos();
	Coord2D vel = animWin->getVel();
	curPos.y += (Int)vel.y;

	if (curPos.y < startPos.y)
	{
		curPos.y = startPos.y;
		animWin->setFinished(true);
		win->winSetPosition(curPos.x, curPos.y);
		return true;
	}

	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);

	ICoord2D endPos = animWin->getEndPos();
	Real nextVelocity;
	if (endPos.y - curPos.y <= m_slowDownThreshold)
		nextVelocity = vel.y * m_speedUpRatio;
	else
		nextVelocity = -m_maxVel.y;

	const Real minimumVelocity = -m_maxVel.y;
	if (nextVelocity < minimumVelocity)
		nextVelocity = minimumVelocity;
	vel.y = nextVelocity;

	animWin->setVel(vel);
	return false;
}
