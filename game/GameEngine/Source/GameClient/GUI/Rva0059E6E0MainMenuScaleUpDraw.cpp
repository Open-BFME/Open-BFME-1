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

// BFME's display helper takes real screen coordinates.  Its retail ILT is
// j_0000a114, whose body is the complete begin/core/end wrapper at 0x0040D900.
class Display
{
public:
	void drawImage(const Image *image, Real startX, Real startY,
		Real endX, Real endY, Int color, Int mode);
};

extern Display *TheDisplay;

// The MainMenuScaleUpTransition source identity is established by the
// neighboring init/update bodies.  BFME inserts start/end frame members into
// the transition layout, so this TU keeps the proven retail offsets local
// without emitting a second or truncated transition vtable.
class Rva0059E6E0MainMenuScaleUp
{
public:
	void draw();

private:
	unsigned char m_unreconstructed_00[ 0x08 ];
	Bool m_isFinished;
	Bool m_isForward;
	unsigned char m_unreconstructed_0a[ 2 ];
	void *m_win;
	Int m_startFrame;
	Int m_endFrame;
	ICoord2D m_pos;
	ICoord2D m_size;
	Int m_drawState;
	ICoord2D m_growPos;
	ICoord2D m_growSize;
	ICoord2D m_incrementPos;
	ICoord2D m_incrementSize;
	void *m_growWin;
};

struct BfmeTransitionWindowImages
{
	unsigned char m_unreconstructed_00[ 0x48 ];
	const Image *m_enabledImage0;
};

// ?draw@Rva0059E6E0MainMenuScaleUp@@QAEXXZ
void Rva0059E6E0MainMenuScaleUp::draw()
{
	if(!m_win)
		return;

	const Image *image = ((const BfmeTransitionWindowImages *)m_growWin)->m_enabledImage0;
	if(m_drawState <= m_startFrame || m_drawState >= m_endFrame)
		return;

	Int x = m_pos.x + (m_incrementPos.x * m_drawState);
	Int y = m_pos.y + (m_incrementPos.y * m_drawState);
	Int x1 = x + m_size.x + (m_incrementSize.x * m_drawState);
	Int y1 = y + m_size.y + (m_incrementSize.y * m_drawState);
	TheDisplay->drawImage(image, (Real)x, (Real)y, (Real)x1, (Real)y1, -1, 2);
}
