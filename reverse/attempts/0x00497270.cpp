// ?reverseAnimateWindow@ProcessAnimateWindowSlideFromTopFast@@UAE_NPAVAnimateWindow@@@Z
// partial score=0.97 date=2026-08-31
// cl: /DNDEBUG /MD /EHsc
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
};

class GameWindow
{
public:
	Int winSetPosition( Int x, Int y );
};

class AnimateWindow
{
public:
	virtual void unused( void ) = 0;

	UnsignedInt getStartTime( void ) { return m_startTime; }
	GameWindow *getGameWindow( void ) { return m_gameWindow; }
	ICoord2D getCurPos( void ) { return m_curPos; }
	ICoord2D getStartPos( void ) { return m_startPos; }
	ICoord2D getEndPos( void ) { return m_endPos; }
	Coord2D getVel( void );
	Bool isFinished( void ) { return m_finished; }
	void setFinished( Bool finished ) { m_finished = finished; }
	void setCurPos( ICoord2D pos ) { m_curPos = pos; }
	void setVel( Coord2D vel ) { m_vel = vel; }

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

class ProcessAnimateWindowSlideFromTopFast
{
public:
	virtual void initReverseAnimateWindow( AnimateWindow *, UnsignedInt );
	virtual void initAnimateWindow( AnimateWindow * );
	virtual Bool updateAnimateWindow( AnimateWindow * );
	virtual Bool reverseAnimateWindow( AnimateWindow * );

private:
	Coord2D m_maxVel;
	Int m_slowDownThreshold;
	Real m_slowDownRatio;
	Real m_speedUpRatio;
};

extern "C" UnsignedInt __stdcall bfme_timeGetTime( void );

Bool ProcessAnimateWindowSlideFromTopFast::reverseAnimateWindow( AnimateWindow *animWin )
{
	if(!animWin)
		return true;

	if(animWin->isFinished())
		return true;

	if(bfme_timeGetTime() < animWin->getStartTime())
		return false;

	GameWindow *win = animWin->getGameWindow();
	if(!win)
		return true;

	ICoord2D curPos = animWin->getCurPos();
	ICoord2D startPos = animWin->getStartPos();
	Coord2D vel = animWin->getVel();
	curPos.y += (Int)vel.y;

	if(curPos.y < startPos.y)
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
	if(endPos.y - curPos.y <= m_slowDownThreshold)
		nextVelocity = vel.y * m_speedUpRatio;
	else
		nextVelocity = -m_maxVel.y;

	const Real minimumVelocity = -m_maxVel.y;
	if(nextVelocity < minimumVelocity)
		nextVelocity = minimumVelocity;
	vel.y = nextVelocity;

	animWin->setVel(vel);
	return false;
}
