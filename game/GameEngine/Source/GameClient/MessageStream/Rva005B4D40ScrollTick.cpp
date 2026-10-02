// cl: /DNDEBUG /DWIN32 /MD
// Retail 0x005B4D40 (902 B): the per-frame camera scroll tick of the object at 0x012F4C80.
// Identity: its sole caller, the matched ClientUpdate004329D0::update (0x004329D0), calls it as
// Calls004329D0::rva005B4D40 through ILT 0x0003EC48 (existing pin); the member name is not known.
// The body is Zero Hour LookAtTranslator's MSG_FRAME_TICK scrolling branch (LookAtXlat.cpp) with
// BFME's scroll-type bit mask, a rotate term and a host camera object (0x012F7048); member names
// follow that ZH twin. GlobalData offsets are FieldParse-witnessed except +0xb6c.
// Retail keeps TheWritableGlobalData in edi across the out-of-line Coord2D::normalize call:
// a local assigned after the RMB anchor clamp (and in the other branch). The vec block lets
// the int-to-float temporary share vec's slot, and one v34() after the if/else-if chain gives
// retail's tail duplication.
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct Coord2D
{
	Real x, y;
	void normalize();
};

struct ICoord2D { Int x, y; };

class Glo012F1028Type
{
public:
	char m_pad00[0x1c];
	Bool m_at1C;
	char m_pad1d[0xf];
	Bool m_at2C;
};

class GameLogic;
class BfmeGameLogicPause { public: Bool isGamePaused(); };

class Gen_00609320
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
	virtual void scrollBy14(const Coord2D *offset, Real rotate); // +0x14
	virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28();
	virtual void v2c(); virtual void v30();
	virtual void v34(); // +0x34
	unsigned char bfmeDisabled() const;
};

class InGameUI
{
public:
	char m_pad[0x12bd];
	Bool m_moveRMBScrollAnchor; // +0x12bd
	Bool shouldMoveRMBScrollAnchor() const { return m_moveRMBScrollAnchor; }
};

class Display
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
	virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
	virtual void v28();
	virtual UnsignedInt getWidth(); // +0x2c
	virtual UnsignedInt getHeight(); // +0x30
};

class GlobalData
{
public:
	char m_pad000[0xb64];
	Real m_horizontalScrollSpeedFactor; // +0xb64
	Real m_verticalScrollSpeedFactor; // +0xb68
	Real m_atB6C; // +0xb6c
	char m_padb70[0xbbc - 0xb70];
	Real m_keyboardScrollFactor; // +0xbbc
	char m_padbc0[0xcc8 - 0xbc0];
	Real m_keyboardCameraRotateSpeed; // +0xcc8
};

extern Glo012F1028Type *Glo012F1028;
extern GameLogic *TheGameLogic;
extern Gen_00609320 *g_bfmeStateDF;
extern InGameUI *TheInGameUI;
extern Display *TheDisplay;
extern GlobalData *TheWritableGlobalData;

enum
{
	SCROLL_RMB = 1,
	SCROLL_ROTATE = 2,
	SCROLL_KEY = 4,
	SCROLL_SCREENEDGE = 8
};

enum { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT, NUM_DIRS };

struct Calls004329D0
{
	void rva005B4D40();

	void *m_vtbl;
	Int m_scrollType; // +0x4
	Int m_at08;
	ICoord2D m_anchor; // +0xc
	ICoord2D m_currentPos; // +0x14
	ICoord2D m_rotateAnchor; // +0x1c
	ICoord2D m_rotatePos; // +0x24
	Bool m_isScrolling; // +0x2c
	Bool m_scrollDir[NUM_DIRS]; // +0x2d
	Bool m_rotateLeft; // +0x31
	Bool m_rotateRight; // +0x32
};

void Calls004329D0::rva005B4D40()
{
	if (!Glo012F1028 || !Glo012F1028->m_at2C)
		return;
	if (((BfmeGameLogicPause *)TheGameLogic)->isGamePaused())
		return;
	Glo012F1028->m_at1C = false;

	Coord2D offset;
	offset.x = 0.0f;
	offset.y = 0.0f;
	Real rotate = 0.0f;

	if (m_isScrolling)
	{
		if (g_bfmeStateDF->bfmeDisabled())
		{
			if (m_scrollType & SCROLL_RMB)
				m_scrollType -= SCROLL_RMB;
			if (m_scrollType < 0)
				m_scrollType = 0;
			if (m_scrollType == 0)
				m_isScrolling = false;
		}
	}

	if (m_isScrolling)
	{
		const GlobalData *gd;
		if (m_scrollType & SCROLL_RMB)
		{
			if (TheInGameUI->shouldMoveRMBScrollAnchor())
			{
				Int maxX = TheDisplay->getWidth() / 2;
				Int maxY = TheDisplay->getHeight() / 2;

				if (m_currentPos.x + maxX < m_anchor.x)
					m_anchor.x = m_currentPos.x + maxX;
				else if (m_currentPos.x - maxX > m_anchor.x)
					m_anchor.x = m_currentPos.x - maxX;

				if (m_currentPos.y + maxY < m_anchor.y)
					m_anchor.y = m_currentPos.y + maxY;
				else if (m_currentPos.y - maxY > m_anchor.y)
					m_anchor.y = m_currentPos.y - maxY;
			}
			gd = TheWritableGlobalData;

			offset.x = gd->m_horizontalScrollSpeedFactor * (m_currentPos.x - m_anchor.x);
			offset.y = gd->m_verticalScrollSpeedFactor * (m_currentPos.y - m_anchor.y);
			{
				Coord2D vec;
				vec.x = offset.x;
				vec.y = offset.y;
				vec.normalize();
				Real k = gd->m_keyboardScrollFactor;
				offset.x += k * gd->m_horizontalScrollSpeedFactor * k * vec.x;
				k = gd->m_keyboardScrollFactor;
				offset.y += k * gd->m_verticalScrollSpeedFactor * k * vec.y;
			}
		}
		else
			gd = TheWritableGlobalData;

		if (m_scrollType & SCROLL_ROTATE)
			rotate = (m_rotatePos.x - m_rotateAnchor.x) * 0.005f;

		if (m_scrollType & SCROLL_KEY)
		{
			if (m_scrollDir[DIR_UP])
				offset.y -= gd->m_keyboardScrollFactor * gd->m_verticalScrollSpeedFactor * 350.0f;
			if (m_scrollDir[DIR_DOWN])
				offset.y += gd->m_keyboardScrollFactor * gd->m_verticalScrollSpeedFactor * 350.0f;
			if (m_scrollDir[DIR_LEFT])
				offset.x -= gd->m_keyboardScrollFactor * gd->m_horizontalScrollSpeedFactor * 350.0f;
			if (m_scrollDir[DIR_RIGHT])
				offset.x += gd->m_keyboardScrollFactor * gd->m_horizontalScrollSpeedFactor * 350.0f;
		}

		if (m_scrollType & SCROLL_SCREENEDGE)
		{
			UnsignedInt height = TheDisplay->getHeight();
			UnsignedInt width = TheDisplay->getWidth();
			if (m_currentPos.y < 3)
				offset.y -= TheWritableGlobalData->m_keyboardScrollFactor * TheWritableGlobalData->m_atB6C * TheWritableGlobalData->m_verticalScrollSpeedFactor * 350.0f;
			if (m_currentPos.y >= height - 3)
				offset.y += TheWritableGlobalData->m_keyboardScrollFactor * TheWritableGlobalData->m_atB6C * TheWritableGlobalData->m_verticalScrollSpeedFactor * 350.0f;
			if (m_currentPos.x < 3)
				offset.x -= TheWritableGlobalData->m_keyboardScrollFactor * TheWritableGlobalData->m_atB6C * TheWritableGlobalData->m_horizontalScrollSpeedFactor * 350.0f;
			if (m_currentPos.x >= width - 3)
				offset.x += TheWritableGlobalData->m_keyboardScrollFactor * TheWritableGlobalData->m_atB6C * TheWritableGlobalData->m_horizontalScrollSpeedFactor * 350.0f;
		}

		g_bfmeStateDF->scrollBy14(&offset, rotate);
	}
	else if (m_rotateLeft)
		g_bfmeStateDF->scrollBy14(&offset, TheWritableGlobalData->m_keyboardCameraRotateSpeed * -15.0f);
	else if (m_rotateRight)
		g_bfmeStateDF->scrollBy14(&offset, TheWritableGlobalData->m_keyboardCameraRotateSpeed * 15.0f);
	g_bfmeStateDF->v34();
}
