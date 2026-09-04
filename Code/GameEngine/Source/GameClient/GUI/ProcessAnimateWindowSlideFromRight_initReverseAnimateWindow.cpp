// cl: /DNDEBUG /MD /EHsc
// readable body of
// ?initReverseAnimateWindow@ProcessAnimateWindowSlideFromRight@@UAEXPAVAnimateWindow@@I@Z:
// Code/GameEngine/Source/GameClient/GUI/ProcessAnimateWindow.cpp
//
// Retail 0x004956A0, 104 bytes. Same negate/store as SlideFromLeft, plus
// setFinished(FALSE) at +0x41 between the two fmuls. Sits after the landed
// SlideFromRight ctor at 0x00495650.

typedef unsigned int UnsignedInt;
typedef unsigned char Bool;
typedef float Real;

struct Coord2D
{
	Real x;
	Real y;

	Coord2D(void) {}
	Coord2D(Real x_, Real y_) : x(x_), y(y_) {}
	Coord2D(const Coord2D &that) : x(that.x), y(that.y) {}
	~Coord2D(void) {}
};

extern "C" UnsignedInt __stdcall bfme_timeGetTime(void);

class AnimateWindow
{
public:
	virtual ~AnimateWindow();
	UnsignedInt getDelay(void) const { return m_delay; }
	Coord2D getVel(void);
	void setStartTime(UnsignedInt value) { m_startTime = value; }
	void setVel(Coord2D value) { m_vel = value; }
	void setFinished(Bool value) { m_finished = value; }

	UnsignedInt m_delay;
	unsigned char m_padding0[0x24];
	Coord2D m_vel;
	UnsignedInt m_startTime;
	unsigned char m_padding1[0x41 - 0x38];
	Bool m_finished;
};

class ProcessAnimateWindowSlideFromRight
{
public:
	virtual void initReverseAnimateWindow(AnimateWindow *window, UnsignedInt maxDelay);
};

// ?initReverseAnimateWindow@ProcessAnimateWindowSlideFromRight@@UAEXPAVAnimateWindow@@I@Z
void ProcessAnimateWindowSlideFromRight::initReverseAnimateWindow(
	AnimateWindow *window, UnsignedInt maxDelay)
{
	if (!window)
		return;
	UnsignedInt delay = window->getDelay();
	if (delay > 0)
		window->setStartTime(bfme_timeGetTime() + (maxDelay - delay));
	Coord2D vel = window->getVel();
	vel.x *= -1.0f;
	window->setFinished(0);
	vel.y *= -1.0f;
	window->setVel(vel);
}
