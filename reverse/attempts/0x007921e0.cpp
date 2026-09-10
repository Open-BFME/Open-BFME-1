// ?d_007921e0@@YAXXZ
// partial score=0.99 date=2026-09-10
typedef int Int;
typedef int Color;
typedef unsigned char Bool;

struct ICoord2D
{
	Int x;
	Int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

class Image
{
public:
	Int getImageWidth() const
	{
		return *(const Int *)((const char *)this + 0x24);
	}

	Int getImageHeight() const
	{
		return *(const Int *)((const char *)this + 0x28);
	}
};

#define BFME_DISPLAY_UNUSED(n) virtual void unused##n();
class BfmeListDisplay
{
public:
	BFME_DISPLAY_UNUSED(00)
	BFME_DISPLAY_UNUSED(01)
	BFME_DISPLAY_UNUSED(02)
	BFME_DISPLAY_UNUSED(03)
	BFME_DISPLAY_UNUSED(04)
	BFME_DISPLAY_UNUSED(05)
	BFME_DISPLAY_UNUSED(06)
	BFME_DISPLAY_UNUSED(07)
	BFME_DISPLAY_UNUSED(08)
	BFME_DISPLAY_UNUSED(09)
	BFME_DISPLAY_UNUSED(10)
	BFME_DISPLAY_UNUSED(11)
	BFME_DISPLAY_UNUSED(12)
	BFME_DISPLAY_UNUSED(13)
	BFME_DISPLAY_UNUSED(14)
	BFME_DISPLAY_UNUSED(15)
	BFME_DISPLAY_UNUSED(16)
	BFME_DISPLAY_UNUSED(17)
	BFME_DISPLAY_UNUSED(18)
	BFME_DISPLAY_UNUSED(19)
	BFME_DISPLAY_UNUSED(20)
	BFME_DISPLAY_UNUSED(21)
	BFME_DISPLAY_UNUSED(22)
	BFME_DISPLAY_UNUSED(23)
	BFME_DISPLAY_UNUSED(24)
	BFME_DISPLAY_UNUSED(25)
	BFME_DISPLAY_UNUSED(26)
	BFME_DISPLAY_UNUSED(27)
	BFME_DISPLAY_UNUSED(28)
	BFME_DISPLAY_UNUSED(29)
	BFME_DISPLAY_UNUSED(30)
	BFME_DISPLAY_UNUSED(31)
	BFME_DISPLAY_UNUSED(32)
	BFME_DISPLAY_UNUSED(33)
	virtual void setClipRegion(IRegion2D *region);
	BFME_DISPLAY_UNUSED(35)
	virtual void enableClipping(Bool onoff);
};
#undef BFME_DISPLAY_UNUSED

#define BFME_WINDOW_UNUSED(n) virtual void unused##n();
class GameWindowManager
{
public:
	BFME_WINDOW_UNUSED(00)
	BFME_WINDOW_UNUSED(01)
	BFME_WINDOW_UNUSED(02)
	BFME_WINDOW_UNUSED(03)
	BFME_WINDOW_UNUSED(04)
	BFME_WINDOW_UNUSED(05)
	BFME_WINDOW_UNUSED(06)
	BFME_WINDOW_UNUSED(07)
	BFME_WINDOW_UNUSED(08)
	BFME_WINDOW_UNUSED(09)
	BFME_WINDOW_UNUSED(10)
	BFME_WINDOW_UNUSED(11)
	BFME_WINDOW_UNUSED(12)
	BFME_WINDOW_UNUSED(13)
	BFME_WINDOW_UNUSED(14)
	BFME_WINDOW_UNUSED(15)
	BFME_WINDOW_UNUSED(16)
	BFME_WINDOW_UNUSED(17)
	BFME_WINDOW_UNUSED(18)
	BFME_WINDOW_UNUSED(19)
	BFME_WINDOW_UNUSED(20)
	BFME_WINDOW_UNUSED(21)
	BFME_WINDOW_UNUSED(22)
	BFME_WINDOW_UNUSED(23)
	BFME_WINDOW_UNUSED(24)
	BFME_WINDOW_UNUSED(25)
	BFME_WINDOW_UNUSED(26)
	BFME_WINDOW_UNUSED(27)
	BFME_WINDOW_UNUSED(28)
	BFME_WINDOW_UNUSED(29)
	BFME_WINDOW_UNUSED(30)
	BFME_WINDOW_UNUSED(31)
	BFME_WINDOW_UNUSED(32)
	BFME_WINDOW_UNUSED(33)
	BFME_WINDOW_UNUSED(34)
	BFME_WINDOW_UNUSED(35)
	BFME_WINDOW_UNUSED(36)
	BFME_WINDOW_UNUSED(37)
	BFME_WINDOW_UNUSED(38)
	BFME_WINDOW_UNUSED(39)
	BFME_WINDOW_UNUSED(40)
	BFME_WINDOW_UNUSED(41)
	BFME_WINDOW_UNUSED(42)
	BFME_WINDOW_UNUSED(43)
	BFME_WINDOW_UNUSED(44)
	BFME_WINDOW_UNUSED(45)
	BFME_WINDOW_UNUSED(46)
	BFME_WINDOW_UNUSED(47)
	BFME_WINDOW_UNUSED(48)
	BFME_WINDOW_UNUSED(49)
	BFME_WINDOW_UNUSED(50)
	BFME_WINDOW_UNUSED(51)
	BFME_WINDOW_UNUSED(52)
	BFME_WINDOW_UNUSED(53)
	BFME_WINDOW_UNUSED(54)
	BFME_WINDOW_UNUSED(55)
	BFME_WINDOW_UNUSED(56)
	BFME_WINDOW_UNUSED(57)
	BFME_WINDOW_UNUSED(58)
	BFME_WINDOW_UNUSED(59)
	BFME_WINDOW_UNUSED(60)
	virtual void winDrawImage(const Image *image, Int left, Int top, Int right,
		Int bottom, Color color = -1);
};
#undef BFME_WINDOW_UNUSED

extern BfmeListDisplay *TheDisplay;
extern GameWindowManager *TheWindowManager;

static void drawHiliteBar(const Image *left, const Image *right,
	const Image *center, Int startX, Int startY, Int endX, Int endY)
{
	ICoord2D barWindowSize;
	Int xOffset = 0, yOffset = 0;
	ICoord2D start, end;
	Int i;
	IRegion2D clipRegion;

	barWindowSize.x = endX - startX;
	barWindowSize.y = endY - startY;
	if (barWindowSize.x < left->getImageWidth() + right->getImageWidth())
		barWindowSize.x = left->getImageWidth() + right->getImageWidth();

	ICoord2D leftSize, rightSize;
	leftSize.x = left->getImageWidth();
	leftSize.y = left->getImageHeight();
	rightSize.x = right->getImageWidth();
	rightSize.y = right->getImageHeight();

	ICoord2D leftEnd, rightStart;
	leftEnd.x = startX + leftSize.x + xOffset;
	leftEnd.y = startY + barWindowSize.y + yOffset;
	rightStart.x = startX + barWindowSize.x - rightSize.x + xOffset;
	rightStart.y = startY + yOffset;

	Int centerWidth, pieces;
	centerWidth = rightStart.x - leftEnd.x;
	pieces = centerWidth / center->getImageWidth();

	start.x = leftEnd.x;
	start.y = startY + yOffset;
	end.y = start.y + barWindowSize.y;
	for (i = 0; i < pieces; i++)
	{
		end.x = start.x + center->getImageWidth();
		TheWindowManager->winDrawImage(center, start.x, start.y, end.x, end.y);
		start.x += center->getImageWidth();
	}

	clipRegion.lo.x = leftEnd.x;
	clipRegion.lo.y = startY + yOffset;
	clipRegion.hi.x = leftEnd.x + centerWidth;
	clipRegion.hi.y = start.y + barWindowSize.y;
	TheDisplay->setClipRegion(&clipRegion);
	TheDisplay->enableClipping(FALSE);

	start.x = startX + xOffset;
	start.y = startY + yOffset;
	end = leftEnd;
	TheWindowManager->winDrawImage(left, start.x, start.y, end.x, end.y);

	start = rightStart;
	end.x = rightSize.x + (start.x * 1);
	end.y = start.y + barWindowSize.y;
	TheWindowManager->winDrawImage(right, start.x, start.y, end.x, end.y);
}
