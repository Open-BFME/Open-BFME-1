// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef float Real;
typedef unsigned char Bool;

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
	virtual Int getWidth();
	virtual Int getHeight();
};

extern Display *TheDisplay;

class GameWindow;

class Transition
{
public:
	virtual ~Transition();
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

class CrossFadeImage : public Transition
{
public:
	virtual void init(GameWindow *win);

private:
	Int m_startFrame;
	Int m_endFrame;
	Int m_posX;
	Int m_posY;
	Int m_sizeX;
	Int m_sizeY;
	Real m_percent;
	Int m_drawState;
	void *m_image;
};

// ?init@CrossFadeImage@@UAEXPAVGameWindow@@@Z
void CrossFadeImage::init(GameWindow *win)
{
	m_isForward = false;
	update(m_startFrame);
	m_isFinished = false;
	m_isForward = true;
	m_percent = 1.0f / (m_endFrame - 1);

	if (!m_image)
	{
		m_isFinished = true;
		return;
	}

	m_posY = 0;
	m_posX = 0;
	m_sizeX = TheDisplay->getWidth();
	m_sizeY = TheDisplay->getHeight();
}
