// cl: /DNDEBUG /MD /EHsc
// readable body of ?reverseAnimateWindow@ProcessAnimateWindowSlideFromBottom@@UAE_NPAVAnimateWindow@@@Z: Code/GameEngine/Source/GameClient/GUI/ProcessAnimateWindow.cpp

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
	Coord2D( void ) {}
	Coord2D( const Coord2D &that ) : x(that.x), y(that.y) {}
	~Coord2D( void ) {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	Int winSetPosition( Int x, Int y );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/AnimateWindowManager.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ProcessAnimateWindow.h
class ProcessAnimateWindowSlideFromBottom
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

Bool ProcessAnimateWindowSlideFromBottom::reverseAnimateWindow( AnimateWindow *animWin )
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

	if(curPos.y > startPos.y)
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
	if(curPos.y - endPos.y <= m_slowDownThreshold)
		nextVelocity = vel.y * m_speedUpRatio;
	else
		nextVelocity = -m_maxVel.y;

	const Real minimumVelocity = -m_maxVel.y;
	if(nextVelocity > minimumVelocity)
		nextVelocity = minimumVelocity;
	vel.y = nextVelocity;

	animWin->setVel(vel);
	return false;
}

