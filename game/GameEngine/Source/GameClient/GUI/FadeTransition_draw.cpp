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

class Display
{
public:
	void drawImage(const Image *image, Real startX, Real startY,
		Real endX, Real endY, Int color, Int mode);
};

extern Display *TheDisplay;

// The base layout and the +0x48 window image agree with the landed
// ScaleUpTransition draw and the FadeTransition update in this directory.
class FadeTransition
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
};

struct FadeTransitionWindowImages
{
	unsigned char m_unreconstructed_00[0x48];
	const Image *m_enabledImage0;
};

// ?draw@FadeTransition@@UAEXXZ
void FadeTransition::draw()
{
	if (!m_win)
		return;
	const Image *image = ((FadeTransitionWindowImages *)m_win)->m_enabledImage0;
	switch (m_drawState)
	{
	case 1:
		TheDisplay->drawImage(image, (Real)m_pos.x, (Real)m_pos.y,
			(Real)(m_pos.x + m_size.x), (Real)(m_pos.y + m_size.y), 0x19ffffff, 2);
		break;
	case 2:
		TheDisplay->drawImage(image, (Real)m_pos.x, (Real)m_pos.y,
			(Real)(m_pos.x + m_size.x), (Real)(m_pos.y + m_size.y), 0x32ffffff, 2);
		break;
	case 3:
		TheDisplay->drawImage(image, (Real)m_pos.x, (Real)m_pos.y,
			(Real)(m_pos.x + m_size.x), (Real)(m_pos.y + m_size.y), 0x4bffffff, 2);
		break;
	case 4:
		TheDisplay->drawImage(image, (Real)m_pos.x, (Real)m_pos.y,
			(Real)(m_pos.x + m_size.x), (Real)(m_pos.y + m_size.y), 0x64ffffff, 2);
		break;
	case 5:
		TheDisplay->drawImage(image, (Real)m_pos.x, (Real)m_pos.y,
			(Real)(m_pos.x + m_size.x), (Real)(m_pos.y + m_size.y), 0x7dffffff, 2);
		break;
	case 6:
		TheDisplay->drawImage(image, (Real)m_pos.x, (Real)m_pos.y,
			(Real)(m_pos.x + m_size.x), (Real)(m_pos.y + m_size.y), 0x96ffffff, 2);
		break;
	case 7:
		TheDisplay->drawImage(image, (Real)m_pos.x, (Real)m_pos.y,
			(Real)(m_pos.x + m_size.x), (Real)(m_pos.y + m_size.y), 0xafffffff, 2);
		break;
	case 8:
		TheDisplay->drawImage(image, (Real)m_pos.x, (Real)m_pos.y,
			(Real)(m_pos.x + m_size.x), (Real)(m_pos.y + m_size.y), 0xc8ffffff, 2);
		break;
	case 9:
		TheDisplay->drawImage(image, (Real)m_pos.x, (Real)m_pos.y,
			(Real)(m_pos.x + m_size.x), (Real)(m_pos.y + m_size.y), 0xe1ffffff, 2);
		break;
	}
}
