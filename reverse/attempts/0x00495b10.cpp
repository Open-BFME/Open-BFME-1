// ?initReverseAnimateWindow@ProcessAnimateWindowSlideFromLeft@@UAEXPAVAnimateWindow@@I@Z
// partial score=0.98 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /MD /EHsc

typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

struct Coord2D
{
	Real x;
	Real y;
};

class AnimateWindow
{
public:
	virtual ~AnimateWindow();
	UnsignedInt getDelay(void) const { return m_delay; }
	Coord2D getVel(void);
	void setStartTime(UnsignedInt value) { m_startTime = value; }
	void setVel(Coord2D value) { m_vel = value; }
private:
	UnsignedInt m_delay;
	unsigned char m_padding0[0x24];
	Coord2D m_vel;
	UnsignedInt m_startTime;
};

extern "C" UnsignedInt __stdcall bfme_timeGetTime(void);

class ProcessAnimateWindow
{
public:
	virtual ~ProcessAnimateWindow();
	virtual void initAnimateWindow(AnimateWindow *window) = 0;
	virtual void initReverseAnimateWindow(AnimateWindow *window, UnsignedInt maxDelay) = 0;
	virtual Bool updateAnimateWindow(AnimateWindow *window) = 0;
	virtual Bool reverseAnimateWindow(AnimateWindow *window) = 0;
};

class ProcessAnimateWindowSlideFromLeft : public ProcessAnimateWindow
{
public:
	virtual void initReverseAnimateWindow(AnimateWindow *window, UnsignedInt maxDelay);
};

void ProcessAnimateWindowSlideFromLeft::initReverseAnimateWindow(
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
