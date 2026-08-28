// cl: /DNDEBUG /MD /EHsc
// readable body of ?initReverseAnimateWindow@ProcessAnimateWindowSlideFromBottomTimed@@UAEXPAVAnimateWindow@@I@Z: Code/GameEngine/Source/GameClient/GUI/ProcessAnimateWindow.cpp
// Open-BFME5: convert the retail animation initializer to clean C++.

typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x;
	Int y;
};

struct BFMECoord2D
{
	Real x;
	Real y;

	BFMECoord2D( void ) {}
	BFMECoord2D( Real x_, Real y_ ) : x(x_), y(y_) {}
	BFMECoord2D( const BFMECoord2D &that ) : x(that.x), y(that.y) {}
	~BFMECoord2D( void ) {}
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

	GameWindow *getGameWindow( void ) { return m_gameWindow; }
	ICoord2D getRestPos( void ) { return m_restPos; }

private:
	char m_padding[0x1c];
	ICoord2D m_restPos;
	GameWindow *m_gameWindow;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Display.h
class Display
{
public:
	virtual void slot00( void ) = 0;
	virtual void slot01( void ) = 0;
	virtual void slot02( void ) = 0;
	virtual void slot03( void ) = 0;
	virtual void slot04( void ) = 0;
	virtual void slot05( void ) = 0;
	virtual void slot06( void ) = 0;
	virtual void slot07( void ) = 0;
	virtual void slot08( void ) = 0;
	virtual void slot09( void ) = 0;
	virtual void slot10( void ) = 0;
	virtual UnsignedInt getWidth( void ) = 0;
};

class BFMEAnimateWindowLayout
{
public:
	void setAnimData( ICoord2D startPos, ICoord2D endPos, ICoord2D curPos,
		ICoord2D restPos, BFMECoord2D vel, UnsignedInt startTime,
		UnsignedInt endTime );
};

extern Display *TheDisplay;
extern "C" __declspec(dllimport) UnsignedInt __stdcall timeGetTime( void );

extern "C" __declspec(noinline) UnsignedInt __stdcall bfme_timeGetTime( void )
{
	// BFME's pause-clock state predates the shared Zero Hour declarations.
	if (!*reinterpret_cast<volatile unsigned char *>(0x012ed8b0)) {
		const unsigned __int64 elapsed =
			static_cast<unsigned __int64>(timeGetTime()) -
			*reinterpret_cast<const unsigned __int64 *>(0x012ed8a8);
		*reinterpret_cast<unsigned __int64 *>(0x012ed898) = elapsed;
		return static_cast<UnsignedInt>(elapsed);
	}
	return *reinterpret_cast<UnsignedInt *>(0x012ed898);
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ProcessAnimateWindow.h
class ProcessAnimateWindowSlideFromBottomTimed
{
public:
	virtual void initReverseAnimateWindow( AnimateWindow *, UnsignedInt );

	UnsignedInt m_maxDuration;
};

// ?initReverseAnimateWindow@ProcessAnimateWindowSlideFromBottomTimed@@UAEXPAVAnimateWindow@@I@Z
void ProcessAnimateWindowSlideFromBottomTimed::initReverseAnimateWindow( AnimateWindow *animWin,
	UnsignedInt maxDelay )
{
	ICoord2D restPos = {0,0};
	ICoord2D startPos = {0,0};
	ICoord2D curPos = {0,0};
	ICoord2D endPos = {0,0};
	BFMECoord2D vel(0.0f,0.0f);

	if(!animWin)
		return;

	GameWindow *win = animWin->getGameWindow();
	if(!win)
		return;

	restPos = animWin->getRestPos();
	startPos.x = restPos.x;
	curPos.y = startPos.y = restPos.y;

	Int travelDistance = TheDisplay->getWidth();
	endPos.x = curPos.x = restPos.x;
	endPos.y = restPos.y + travelDistance;

	win->winSetPosition(startPos.x, startPos.y);

	UnsignedInt now = bfme_timeGetTime();
	((BFMEAnimateWindowLayout *)animWin)->setAnimData(startPos, endPos, curPos,
		restPos, vel, now, now + m_maxDuration);
}
