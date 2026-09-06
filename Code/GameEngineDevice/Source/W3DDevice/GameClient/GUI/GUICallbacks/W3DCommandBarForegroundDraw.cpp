// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

typedef unsigned int NameKeyType;
typedef int Int;

struct ICoord2D
{
	ICoord2D(void) {}
	Int x;
	Int y;
};

class ControlBarSchemeManager
{
public:
	void drawForeground(ICoord2D offset);
};

class ControlBar
{
public:
	ControlBarSchemeManager *getControlBarSchemeManager(void)
	{
		return m_controlBarSchemeManager;
	}

	void getForegroundMarkerPos(Int *x, Int *y);

	unsigned char m_beforeControlBarSchemeManager[0x30];
	ControlBarSchemeManager *m_controlBarSchemeManager;
};

class GameWindow;
class WinInstanceData;

class GameWindowManager
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual void slot26(void) = 0;
	virtual void slot27(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot29(void) = 0;
	virtual void slot30(void) = 0;
	virtual void slot31(void) = 0;
	virtual void slot32(void) = 0;
	virtual void slot33(void) = 0;
	virtual void slot34(void) = 0;
	virtual void slot35(void) = 0;
	virtual void slot36(void) = 0;
	virtual void slot37(void) = 0;
	virtual void slot38(void) = 0;
	virtual void slot39(void) = 0;
	virtual void slot40(void) = 0;
	virtual void slot41(void) = 0;
	virtual void slot42(void) = 0;
	virtual void slot43(void) = 0;
	virtual void slot44(void) = 0;
	virtual void slot45(void) = 0;
	virtual void slot46(void) = 0;
	virtual void slot47(void) = 0;
	virtual void slot48(void) = 0;
	virtual void slot49(void) = 0;
	virtual void slot50(void) = 0;
	virtual void slot51(void) = 0;
	virtual void slot52(void) = 0;
	virtual void slot53(void) = 0;
	virtual void slot54(void) = 0;
	virtual GameWindow *winGetWindowFromId(GameWindow *parent, NameKeyType id) = 0;
};

class GameWindow
{
public:
	Int winGetScreenPosition(Int *x, Int *y);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern ControlBar *TheControlBar;
extern GameWindowManager *TheWindowManager;
extern NameKeyGenerator *TheNameKeyGenerator;

void W3DCommandBarForegroundDraw(GameWindow *, WinInstanceData *)
{
	ControlBarSchemeManager *man = TheControlBar->getControlBarSchemeManager();
	if (!man)
		return;

	static NameKeyType winNamekey =
		TheNameKeyGenerator->nameToKey(AsciiString("ControlBar.wnd:BackgroundMarker").str());
	GameWindow *win = TheWindowManager->winGetWindowFromId(0, winNamekey);
	static ICoord2D basePos;
	if (!win)
		return;

	TheControlBar->getForegroundMarkerPos(&basePos.x, &basePos.y);
	ICoord2D pos;
	ICoord2D offset;
	win->winGetScreenPosition(&pos.x, &pos.y);
	offset.x = pos.x - basePos.x;
	offset.y = pos.y - basePos.y;
	man->drawForeground(offset);
}
