// ?drawTypeText@@YAXPAVGameWindow@@PAVDisplayString@@@Z
// partial score=0.99 date=2026-09-06
// cl: /DNDEBUG /DWIN32 /MD /EHs-c- /O2
// ?drawTypeText@@YAXPAVGameWindow@@PAVDisplayString@@@Z
// Static helper used by TextTypeTransition::draw at retail 0x005A0450.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char Bool;
typedef int Color;

class GameFont;

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

class DisplayString
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual Int getTextLength();
	virtual void unused04();
	virtual void unused05();
	virtual void setFont(GameFont *);
	virtual GameFont *getFont();
	virtual void setWordWrap(Int);
	virtual void setWordWrapCentered(Bool);
	virtual void setTextColor(Color, Color);
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void draw(Int, Int, Int, Int);
	virtual void getSize(Int *, Int *);
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void setUseHotkey(Bool, Color);
	virtual void setClipRegion(IRegion2D *);
};

struct TextData
{
	DisplayString *text;
	Bool centered;
};

class GameWindow
{
public:
	void *winGetUserData();
	Int winGetScreenPosition(Int *, Int *);
	Int winGetSize(Int *, Int *);
	UnsignedInt winGetStatus();
	Int winGetEnabledTextColor();
	Int winGetEnabledTextBorderColor();
};

static __forceinline Int addCoords(Int base, Int offset)
{
	return base + offset;
}

static void drawTypeText(GameWindow *window, DisplayString *str)
{
	TextData *tData = (TextData *)window->winGetUserData();
	Int textColor = window->winGetEnabledTextColor();
	Int textDropColor = window->winGetEnabledTextBorderColor();
	Int textWidth, textHeight, wordWrap;
	DisplayString *text = tData->text;
	ICoord2D origin, size, textPos;
	IRegion2D clipRegion;

	if(text == 0 || text->getTextLength() == 0)
		return;

	GameFont *font = text->getFont();
	str->setFont(font);

	window->winGetScreenPosition(&origin.x, &origin.y);
	window->winGetSize(&size.x, &size.y);

	wordWrap = size.x - 10;
	text->setWordWrap(wordWrap);
	str->setWordWrap(wordWrap);
	if((window->winGetStatus() & 0x00040000) != 0)
	{
		str->setWordWrapCentered(1);
		text->setWordWrapCentered(1);
	}
	else
	{
		text->setWordWrapCentered(0);
		str->setWordWrapCentered(0);
	}

	text->getSize(&textWidth, &textHeight);

	clipRegion.lo.x = origin.x;
	clipRegion.lo.y = origin.y;
	Int width = size.x;
	clipRegion.hi.x = addCoords(origin.x, width);
	clipRegion.hi.y = origin.y + size.y;

	if(tData->centered)
	{
		textPos.x = origin.x + (width / 2) - (textWidth / 2);
		textPos.y = origin.y + (size.y / 2) - (textHeight / 2);
	}
	else
	{
		textPos.x = origin.x + 7;
		textPos.y = origin.y + (size.y / 2) - (textHeight / 2);
	}

	str->setClipRegion(&clipRegion);
	str->setTextColor(textColor, textDropColor);
	str->draw(textPos.x, textPos.y, 1, 1);
}

void drawTypeTextCaller(GameWindow *window, DisplayString *str)
{
	drawTypeText(window, str);
}
