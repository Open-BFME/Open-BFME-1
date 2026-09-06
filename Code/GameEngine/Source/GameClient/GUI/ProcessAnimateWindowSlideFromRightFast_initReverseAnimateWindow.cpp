// cl: /DNDEBUG /MD /EHsc
// Clean C++ reconstruction of the manager-selected SlideFromRightFast
// initReverseAnimateWindow virtual (slot 2), retail RVA 0x00497410, 178 bytes.
// The proven identity is the original class and its manager registration;
// fields and helper calls below use the observed AnimateWindow layout.

typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;
typedef unsigned char Bool;

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
	Int winGetPosition(Int *x, Int *y);
};

class AnimateWindow
{
public:
	virtual void unused(void) = 0;

	UnsignedInt getDelay(void) const { return m_delay; }
	GameWindow *getGameWindow(void) { return m_gameWindow; }
	Coord2D getVel(void);
	ICoord2D getCurPos(void) { return m_curPos; }
	ICoord2D getEndPos(void) { return m_endPos; }
	ICoord2D getStartPos(void) { return m_startPos; }
	void setStartTime(UnsignedInt value) { m_startTime = value; }
	void setFinished(Bool value) { m_finished = value; }
	void setVel(Coord2D value) { m_vel = value; }
	void setCurPos(ICoord2D value) { m_curPos = value; }
	void setEndPos(ICoord2D value) { m_endPos = value; }
	void setStartPos(ICoord2D value) { m_startPos = value; }

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

class ProcessAnimateWindowSlideFromRightFast
{
public:
	virtual ~ProcessAnimateWindowSlideFromRightFast();
	virtual void initAnimateWindow(AnimateWindow *);
	virtual void initReverseAnimateWindow(AnimateWindow *, UnsignedInt);
	virtual Bool updateAnimateWindow(AnimateWindow *);
	virtual Bool reverseAnimateWindow(AnimateWindow *);
};

extern "C" UnsignedInt __stdcall bfme_timeGetTime(void);

// ?initReverseAnimateWindow@ProcessAnimateWindowSlideFromRightFast@@UAEXPAVAnimateWindow@@I@Z
void ProcessAnimateWindowSlideFromRightFast::initReverseAnimateWindow(
	AnimateWindow *window, UnsignedInt maxDelay)
{
	if (!window)
		return;
	UnsignedInt delay = window->getDelay();
	if (delay > 0)
		window->setStartTime(bfme_timeGetTime() + (maxDelay - delay));
	{
		Coord2D vel = window->getVel();
		vel.x *= -1.0f;
		vel.y *= -1.0f;
		window->setFinished(0);
		window->setVel(vel);
	}
	GameWindow *win = window->getGameWindow();
	ICoord2D pos, tempPos;
	win->winGetPosition(&pos.x, &pos.y);
	tempPos = window->getCurPos();
	tempPos.y = pos.y;
	window->setCurPos(tempPos);
	tempPos = window->getEndPos();
	tempPos.y = pos.y;
	window->setEndPos(tempPos);
	tempPos = window->getStartPos();
	tempPos.y = pos.y;
	window->setStartPos(tempPos);
}

