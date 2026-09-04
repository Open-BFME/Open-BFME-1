// cl: /DNDEBUG /MD /EHsc
// readable body of
// ?initReverseAnimateWindow@ProcessAnimateWindowSlideFromTop@@UAEXPAVAnimateWindow@@I@Z:
// Code/GameEngine/Source/GameClient/GUI/ProcessAnimateWindow.cpp
//
// Retail 0x00495F80, 100 bytes. Same shape as SlideFromLeft; sits after the
// landed SlideFromTop ctor at 0x00495F30.

typedef unsigned int UnsignedInt;
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

	UnsignedInt m_delay;
	unsigned char m_padding0[0x24];
	Coord2D m_vel;
	UnsignedInt m_startTime;
};

class ProcessAnimateWindowSlideFromTop
{
public:
	virtual void initReverseAnimateWindow(AnimateWindow *window, UnsignedInt maxDelay);
};

// ?initReverseAnimateWindow@ProcessAnimateWindowSlideFromTop@@UAEXPAVAnimateWindow@@I@Z
void ProcessAnimateWindowSlideFromTop::initReverseAnimateWindow(
	AnimateWindow *window, UnsignedInt maxDelay)
{
	if (!window)
		return;
	UnsignedInt delay = window->getDelay();
	if (delay > 0)
		window->setStartTime(bfme_timeGetTime() + (maxDelay - delay));
	Coord2D vel = window->getVel();
	vel.x *= -1.0f;
	vel.y *= -1.0f;
	window->setVel(vel);
}
