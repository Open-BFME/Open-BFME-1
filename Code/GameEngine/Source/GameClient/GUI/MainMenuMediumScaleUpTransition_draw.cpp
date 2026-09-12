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

// 0x0059E1F0 installs the medium transition vtable at 0x0110C994.  The
// adjacent named init/update/reverse bodies establish this BFME layout: frame
// bounds at +0x10/+0x14, the source window at +0x0c, and its medium grow window
// at +0x44.  The draw body uses the source window's +0x48 image data.
class MainMenuMediumScaleUpTransition
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
	Int m_startFrame;
	Int m_endFrame;
	ICoord2D m_pos;
	ICoord2D m_size;
	Int m_drawState;
	ICoord2D m_growPos;
	ICoord2D m_growSize;
	ICoord2D m_incrementSize;
	void *m_growWin;
};

struct BfmeMediumScaleUpWindow
{
	unsigned char m_unreconstructed_00[ 0x48 ];
	const Image *m_enabledImage;
};

// ?draw@MainMenuMediumScaleUpTransition@@UAEXXZ
void MainMenuMediumScaleUpTransition::draw()
{
	if(!m_win)
		return;

	const Image *image = ((const BfmeMediumScaleUpWindow *)m_win)->m_enabledImage;
	if(m_drawState <= m_startFrame || m_drawState >= m_endFrame)
		return;

	Int x = m_pos.x - ((m_incrementSize.x * m_drawState) / 2);
	Int y = m_pos.y - ((m_incrementSize.y * m_drawState) / 2);
	Int x1 = m_pos.x + m_size.x + ((m_incrementSize.x * m_drawState) / 2);
	Int y1 = m_pos.y + m_size.y + ((m_incrementSize.y * m_drawState) / 2);
	TheDisplay->drawImage(image, (Real)x, (Real)y, (Real)x1, (Real)y1, -1, 2);
}
