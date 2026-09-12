// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef float Real;
typedef unsigned char Bool;

struct ICoord2D
{
	Int x;
	Int y;
};

class Image;

class Display
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8C();
	virtual void slot90();
	virtual void slot94();
	virtual void slot98();
	virtual void slot9C();
	virtual void slotA0();
	virtual void slotA4();
	virtual void slotA8();
	virtual void slotAC();
	virtual void beginImageDraw();
	virtual void slotB4();
	virtual void slotB8();
	virtual void slotBC();
	virtual void slotC0();
	virtual void slotC4();
	virtual void slotC8();
	virtual void slotCC();
	virtual void slotD0();
	virtual void drawImageCore(Image *image, Real x0, Real y0, Real x1,
		Real y1, Int color, Int mode);
	virtual void slotD8();
	virtual void endImageDraw();
};

inline void drawImage(Display *display, Image *image, Real x0, Real y0,
	Real x1, Real y1, Int color, Int mode)
{
	display->beginImageDraw();
	display->drawImageCore(image, x0, y0, x1, y1, color, mode);
	display->endImageDraw();
}

extern Display *TheDisplay;
extern Real g_bfmeScaleB3;

inline Int GameMakeColor(unsigned char red, unsigned char green,
	unsigned char blue, unsigned char alpha)
{
	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

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

class Rva0059D870Fade : public Transition
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
	Image *m_image;
	Image *m_image2;
};

// ?draw@CrossFadeImage@@UAEXXZ
void Rva0059D870Fade::draw()
{
	if (m_drawState < 0)
		return;

	register Int alpha = m_drawState * m_percent * g_bfmeScaleB3;
	if (alpha > 255)
		alpha = 255;

	drawImage(TheDisplay, m_image, (Real)m_pos.x, (Real)m_pos.y,
		(Real)(m_pos.x + m_size.x), (Real)(m_pos.y + m_size.y),
		GameMakeColor(255, 255, 255, alpha), 2);
	drawImage(TheDisplay, m_image2, (Real)m_pos.x, (Real)m_pos.y,
		(Real)(m_pos.x + m_size.x), (Real)(m_pos.y + m_size.y),
		GameMakeColor(255, 255, 255, 255 - alpha), 2);
}
