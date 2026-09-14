// cl: /DNDEBUG /MD /EHsc /O2 /Ob0

typedef int Int;
typedef float Real;
typedef unsigned char Bool;

struct ICoord2D
{
	Int x;
	Int y;
};

class Image;

// Retail calls the decorated direct helper, whose ILT is j_0000a114.  The
// reference Display declaration is a different virtual integer-coordinate
// ABI, so keep this verified BFME call view local to the recovered body.
class Display
{
public:
	void drawImage(const Image *image, Real startX, Real startY,
		Real endX, Real endY, Int color, Int mode);
};

extern Display *TheDisplay;

// 0x0059F5C0 installs ScoreScaleUpTransition's vtable at 0x0110CB30.  This
// view preserves the proven transition offsets without emitting a second
// vtable or relying on the upstream GameWindow image layout.
class ScoreScaleUpTransition
{
public:
	virtual void draw();

private:
	Int m_frameLength;
	Bool m_isFinished;
	Bool m_isForward;
	Bool m_isReversed;
	unsigned char m_unused_0b;
	void *m_win;
	ICoord2D m_pos;
	ICoord2D m_size;
	Int m_drawState;
	ICoord2D m_centerPos;
	ICoord2D m_incrementSize;
};

struct BfmeTransitionWindowImages
{
	unsigned char m_unreconstructed_00[ 0x48 ];
	const Image *m_enabledImage0;
};

// ?draw@ScoreScaleUpTransition@@UAEXXZ
void ScoreScaleUpTransition::draw()
{
	if(!m_win)
		return;

	const Image *image = ((const BfmeTransitionWindowImages *)m_win)->m_enabledImage0;
	if(m_drawState <= 0 || m_drawState >= 6)
		return;

	Int x = m_centerPos.x - ((m_incrementSize.x * m_drawState) / 2);
	Int y = m_centerPos.y - ((m_incrementSize.y * m_drawState) / 2);
	Int x1 = x + m_incrementSize.x * m_drawState;
	Int y1 = y + m_incrementSize.y * m_drawState;
	TheDisplay->drawImage(image, (Real)x, (Real)y, (Real)x1, (Real)y1, -1, 2);
}
