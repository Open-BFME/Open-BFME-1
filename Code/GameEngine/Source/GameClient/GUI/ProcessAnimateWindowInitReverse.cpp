// cl: /DNDEBUG /MD /EHsc
// readable body of ?initReverseAnimateWindow@ProcessAnimateWindowSlideFromRight@@UAEXPAVAnimateWindow@@I@Z: Code/GameEngine/Source/GameClient/GUI/ProcessAnimateWindow.cpp
// readable body of ?initReverseAnimateWindow@ProcessAnimateWindowSlideFromLeft@@UAEXPAVAnimateWindow@@I@Z: Code/GameEngine/Source/GameClient/GUI/ProcessAnimateWindow.cpp
// readable body of ?initReverseAnimateWindow@ProcessAnimateWindowSlideFromTop@@UAEXPAVAnimateWindow@@I@Z: Code/GameEngine/Source/GameClient/GUI/ProcessAnimateWindow.cpp
// readable body of ?initReverseAnimateWindow@ProcessAnimateWindowSlideFromBottom@@UAEXPAVAnimateWindow@@I@Z: Code/GameEngine/Source/GameClient/GUI/ProcessAnimateWindow.cpp
// readable body of ?initReverseAnimateWindow@ProcessAnimateWindowSlideFromTopFast@@UAEXPAVAnimateWindow@@I@Z: Code/GameEngine/Source/GameClient/GUI/ProcessAnimateWindow.cpp
//
// The five slide processors' reverse-init overrides, at 0x004956A0, 0x00495B10,
// 0x00495F80, 0x00496400 and 0x00496F80. Retail wrote the same body five times,
// once per direction, and each copy used to sit in its own file with its own
// copy of Coord2D and of AnimateWindow -- five declarations of two classes for
// five bodies that are one body with five names.
//
// Reversing an animation means two things: hold the window back by the slack
// between its own delay and the longest delay in the group, so the ones that
// started late finish late too, and flip the velocity so it travels the way it
// came. SlideFromRight is the one that differs, and only by clearing the
// finished flag between the two negations -- retail's own four bytes of
// difference across the five bodies.
//
// AnimateWindow below is the union of the five views: the four that do not call
// setFinished never reach past +0x34, so the flag and the padding that carries
// it to +0x41 change none of their bytes.

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

class ProcessAnimateWindowSlideFromLeft
{
public:
	virtual void initReverseAnimateWindow(AnimateWindow *window, UnsignedInt maxDelay);
};

class ProcessAnimateWindowSlideFromTop
{
public:
	virtual void initReverseAnimateWindow(AnimateWindow *window, UnsignedInt maxDelay);
};

class ProcessAnimateWindowSlideFromBottom
{
public:
	virtual void initReverseAnimateWindow(AnimateWindow *window, UnsignedInt maxDelay);
};

class ProcessAnimateWindowSlideFromTopFast
{
public:
	virtual void initReverseAnimateWindow(AnimateWindow *window, UnsignedInt maxDelay);
};

// ?initReverseAnimateWindow@ProcessAnimateWindowSlideFromRight@@UAEXPAVAnimateWindow@@I@Z
// Retail 0x004956A0, 104 bytes: the odd one out, clearing the finished flag
// between the two negations.
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

// ?initReverseAnimateWindow@ProcessAnimateWindowSlideFromLeft@@UAEXPAVAnimateWindow@@I@Z
// Retail 0x00495B10, 100 bytes.
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

// ?initReverseAnimateWindow@ProcessAnimateWindowSlideFromTop@@UAEXPAVAnimateWindow@@I@Z
// Retail 0x00495F80, 100 bytes.
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

// ?initReverseAnimateWindow@ProcessAnimateWindowSlideFromBottom@@UAEXPAVAnimateWindow@@I@Z
// Retail 0x00496400, 100 bytes.
void ProcessAnimateWindowSlideFromBottom::initReverseAnimateWindow(
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

// ?initReverseAnimateWindow@ProcessAnimateWindowSlideFromTopFast@@UAEXPAVAnimateWindow@@I@Z
// Retail 0x00496F80, 100 bytes.
void ProcessAnimateWindowSlideFromTopFast::initReverseAnimateWindow(
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
