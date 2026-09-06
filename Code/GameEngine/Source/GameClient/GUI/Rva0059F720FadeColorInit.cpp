// cl: /DNDEBUG /MD /EHsc /O2 /Ob0

typedef int Int;
typedef float Real;
typedef unsigned char Bool;
typedef unsigned int UnsignedInt;

class GameWindow;

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
extern Real g_bfmeDefaultBU;
extern Real g_bfmeScaleB3;
extern const Real BfmeZeroRange;

// The retail parse table at 0x00D0CBA0 names this transition's fields
// StartFrame (+0x10), EndFrame (+0x14), and FadeColor (+0x30).  The vtable
// starts at 0x0110CB6C: its scalar deleting destructor is slot zero, this init
// body is slot one, and the already matched frame setter/reverse siblings are
// in the following slots.  The class name is intentionally address-derived
// because no source/RTTI spelling survives.
class Rva0059F720FadeColor
{
public:
	virtual ~Rva0059F720FadeColor();
	virtual void init(GameWindow *window);
	virtual void update(Int frame);
	virtual void reverse();
	virtual void draw();
	virtual void skip();
	virtual Bool isFinished();
	virtual Int getFrameLength();

	Int m_frameLength;
	Bool m_isFinished;
	Bool m_isForward;
	Bool m_isReversed;
	unsigned char m_pad0B;
	GameWindow *m_win;
	Int m_startFrame;
	Int m_endFrame;
	Int m_posX;
	Int m_posY;
	Int m_sizeX;
	Int m_sizeY;
	Real m_percent;
	Int m_drawState;
	volatile Real m_fadeRed;
	volatile Real m_fadeGreen;
	volatile Real m_fadeBlue;
	unsigned char m_red;
	unsigned char m_green;
	unsigned char m_blue;
};

// ?init@Rva0059F720FadeColor@@UAEXPAVGameWindow@@@Z
void Rva0059F720FadeColor::init(GameWindow *)
{
	m_isForward = 0;
	update(m_startFrame);
	m_isFinished = 0;
	m_isForward = 1;
	m_posX = 0;
	m_percent = g_bfmeDefaultBU / (m_endFrame - 1);
	m_posY = 0;
	m_sizeX = TheDisplay->getWidth();
	Int sizeY = TheDisplay->getHeight();

	Real scaled = m_fadeRed;
	scaled *= g_bfmeScaleB3;
	m_sizeY = sizeY;
	if (!(scaled < g_bfmeScaleB3))
		scaled = g_bfmeScaleB3;
	else if (scaled > BfmeZeroRange)
	{
	}
	else
		scaled = BfmeZeroRange;
	unsigned char red = (unsigned char)scaled;

	scaled = m_fadeGreen;
	scaled *= g_bfmeScaleB3;
	m_red = red;
	if (!(scaled < g_bfmeScaleB3))
		scaled = g_bfmeScaleB3;
	else if (scaled > BfmeZeroRange)
	{
	}
	else
		scaled = BfmeZeroRange;
	unsigned char green = (unsigned char)scaled;

	scaled = m_fadeBlue;
	scaled *= g_bfmeScaleB3;
	m_green = green;
	if (!(scaled < g_bfmeScaleB3))
		scaled = g_bfmeScaleB3;
	else if (scaled > BfmeZeroRange)
	{
	}
	else
		scaled = BfmeZeroRange;
	m_blue = (unsigned char)scaled;
}
