// cl: /DNDEBUG /MD /EHsc

typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;
typedef unsigned char Bool;

struct ICoord2D
{
	Int x;
	Int y;
};

class Display
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();
	virtual void unused42();
	virtual void unused43();
	virtual void beginImageDraw();
	virtual void unused45();
	virtual void unused46();
	virtual void drawOpenRect(Real x, Real y, Real width, Real height,
		Real lineWidth, UnsignedInt color);
	virtual void drawFillRect(Real x, Real y, Real width, Real height,
		UnsignedInt color);
	virtual void unused49();
	virtual void unused50();
	virtual void unused51();
	virtual void unused52();
	virtual void unused53();
	virtual void unused54();
	virtual void endImageDraw();
};

inline void drawFillRect(Display *display, Real x, Real y, Real width,
	Real height, UnsignedInt color)
{
	display->beginImageDraw();
	display->drawFillRect(x, y, width, height, color);
	display->endImageDraw();
}

inline void drawOpenRect(Display *display, Real x, Real y, Real width,
	Real height, Real lineWidth, UnsignedInt color)
{
	display->beginImageDraw();
	display->drawOpenRect(x, y, width, height, lineWidth, color);
	display->endImageDraw();
}

inline UnsignedInt GameMakeColor(unsigned char red, unsigned char green,
	unsigned char blue, unsigned char alpha)
{
	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

extern Display *TheDisplay;
extern Real g_bfmeScaleB3;

class Transition
{
public:
	virtual void init(void *win);
	virtual void update(Int frame);
	virtual void reverse();
	virtual void draw();
	virtual void skip();

protected:
	Int m_frameLength;
	Bool m_isFinished;
	Bool m_isForward;
	Bool m_isReversed;
	void *m_win;
};

class FullFadeTransition : public Transition
{
public:
	virtual void draw();

private:
	Int m_startFrame;
	Int m_endFrame;
	ICoord2D m_pos;
	ICoord2D m_size;
	Real m_percent;
	Int m_drawState;
};

// ?draw@FullFadeTransition@@UAEXXZ
void FullFadeTransition::draw()
{
	Int alpha;
	if (m_drawState > m_endFrame / 2)
		alpha = m_percent * (m_endFrame - m_drawState) * g_bfmeScaleB3;
	else
		alpha = m_percent * m_drawState * g_bfmeScaleB3;
	if (alpha > 255)
		alpha = 255;
	drawFillRect(TheDisplay, (Real)m_pos.x, (Real)m_pos.y,
		(Real)m_size.x, (Real)m_size.y, GameMakeColor(0, 0, 0, alpha));
	drawOpenRect(TheDisplay, (Real)m_pos.x, (Real)m_pos.y,
		(Real)m_size.x, (Real)m_size.y, 1.0f,
		GameMakeColor(255, 190, 0, alpha));
}
