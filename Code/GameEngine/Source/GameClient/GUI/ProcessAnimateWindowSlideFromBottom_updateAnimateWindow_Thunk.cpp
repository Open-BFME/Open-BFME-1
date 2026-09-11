// cl: /DNDEBUG /MD /EHsc
// Clean C++ reconstruction of the retail SlideFromBottom update body.
//
// Identity: AnimateWindowManager::getProcessAnimate selects this processor
// for WIN_ANIMATION_SLIDE_BOTTOM.  The matched constructor at 0x004963B0
// installs ProcessAnimateWindowSlideFromBottom's vtable, and the matched
// reverseAnimateWindow body at 0x004966E0 is the adjacent slot of the same
// class.  The algorithm and virtual ordering are also present in the
// GeneralsMD ProcessAnimateWindow.cpp reference source.

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

// Coord2D is a two-float value in the upstream BaseType.h.  The explicit
// special members preserve the BFME caller's return-value lifetime shape.
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
	ICoord2D getEndPos(void) { return m_endPos; }
	// The matched 0x00495610 body is out of line.  Keeping its real body
	// visible here lets MSVC reuse the hidden-result temporary without making
	// a second non-inline definition of the already matched member.
	__declspec(noinline) Coord2D getVel(void) { return m_vel; }
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
extern const Real BfmeShadowScale;

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
	Coord2D velocity = animWin->getVel();
	Real &velocityY = velocity.y;
	curPos.y += (Int)velocityY;

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
		velocityY *= m_slowDownRatio;
	if (velocityY >= BfmeShadowScale)
		velocityY = BfmeShadowScale;
	animWin->setVel(velocity);
	return false;
}
