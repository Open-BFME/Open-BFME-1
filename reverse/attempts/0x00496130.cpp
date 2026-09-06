// ?updateAnimateWindow@ProcessAnimateWindowSlideFromTop@@UAE_NPAVAnimateWindow@@@Z
// partial score=0.95 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc
// readable body of ?updateAnimateWindow@ProcessAnimateWindowSlideFromTop@@UAE_NPAVAnimateWindow@@@Z: Code/GameEngine/Source/GameClient/GUI/ProcessAnimateWindow.cpp

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
	const ICoord2D &getCurPos( void ) { return m_curPos; }	// by reference: retail reads the fields straight into registers
	const ICoord2D &getEndPos( void ) { return m_endPos; }
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
class ProcessAnimateWindowSlideFromTop
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

Bool ProcessAnimateWindowSlideFromTop::updateAnimateWindow( AnimateWindow *animWin )
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
	ICoord2D endPos = animWin->getEndPos();
	Coord2D vel = animWin->getVel();
	curPos.y += (Int)vel.y;

	if(curPos.y > endPos.y)
	{
		curPos.y = endPos.y;
		win->winSetPosition(curPos.x, curPos.y);
		animWin->setFinished(true);
		return true;
	}

	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);

	if(endPos.y - curPos.y <= m_slowDownThreshold)
		vel.y *= m_slowDownRatio;

	if(vel.y < 1.0f)
		vel.y = 1.0f;

	animWin->setVel(vel);
	return false;
}
