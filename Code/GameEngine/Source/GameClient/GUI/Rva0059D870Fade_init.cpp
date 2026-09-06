// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: retail 0x0059D870 (111 bytes) is the twin of CrossFadeImage::init with TWO
// image pointers (+0x30 and +0x34): either one missing finishes the transition at once.
// Names re-tagged for this address.

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

class Rva0059D870Fade : public Transition
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
	void *m_image2;
};

// ?init@Rva0059D870Fade@@UAEXPAVGameWindow@@@Z
void Rva0059D870Fade::init(GameWindow *win)
{
	m_isForward = false;
	update(m_startFrame);
	m_isFinished = false;
	m_isForward = true;
	m_percent = 1.0f / (m_endFrame - 1);

	if (!m_image || !m_image2)
	{
		m_isFinished = true;
		return;
	}

	m_posY = 0;
	m_posX = 0;
	m_sizeX = TheDisplay->getWidth();
	m_sizeY = TheDisplay->getHeight();
}
