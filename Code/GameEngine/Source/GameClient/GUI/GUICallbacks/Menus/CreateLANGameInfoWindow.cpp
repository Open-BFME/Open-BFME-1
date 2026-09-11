// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// BFME's LAN game-info window setup.  The retail WindowLayout interface is
// virtual; this small ABI view preserves the BFME slots without importing the
// later Zero Hour layout used by the reference header.

typedef int Int;
typedef int Bool;

template <typename T> class StringBase
{
friend class BFMERetailAsciiString;

private:
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	void releaseBuffer();
	void *m_data;
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString(const char *text) : StringBase<char>(text) {}
	BFMERetailAsciiString(const BFMERetailAsciiString &other)
		: StringBase<char>(other) {}
	~BFMERetailAsciiString() { releaseBuffer(); }
};

class WindowLayout
{
public:
	virtual void runInit(void *userData = 0);
	virtual void bfmeLayoutSlot04();
	virtual void bfmeLayoutSlot08();
	virtual void bfmeLayoutSlot0C();
	virtual void hide(Bool hidden);
	virtual void bringForward();
};

class GameWindow
{
public:
	Int winGetScreenPosition(Int *x, Int *y);
	Int winSetPosition(Int x, Int y);
	Int winGetSize(Int *width, Int *height);
	Int winSetSize(Int width, Int height);
};

class GameWindowManager
{
public:
	virtual void bfmeWindowManagerSlot00();
	virtual void bfmeWindowManagerSlot04();
	virtual void bfmeWindowManagerSlot08();
	virtual void bfmeWindowManagerSlot0C();
	virtual void bfmeWindowManagerSlot10();
	virtual void bfmeWindowManagerSlot14();
	virtual void bfmeWindowManagerSlot18();
	virtual void bfmeWindowManagerSlot1C();
	virtual void bfmeWindowManagerSlot20();
	virtual void bfmeWindowManagerSlot24();
	virtual void bfmeWindowManagerSlot28();
	virtual void bfmeWindowManagerSlot2C();
	virtual void bfmeWindowManagerSlot30();
	virtual void bfmeWindowManagerSlot34();
	virtual void bfmeWindowManagerSlot38();
	virtual void bfmeWindowManagerSlot3C();
	virtual void bfmeWindowManagerSlot40();
	virtual void bfmeWindowManagerSlot44();
	virtual void bfmeWindowManagerSlot48();
	virtual void bfmeWindowManagerSlot4C();
	virtual void bfmeWindowManagerSlot50();
	virtual void bfmeWindowManagerSlot54();
	virtual void bfmeWindowManagerSlot58();
	virtual void bfmeWindowManagerSlot5C();
	virtual void bfmeWindowManagerSlot60();
	virtual void bfmeWindowManagerSlot64();
	virtual void bfmeWindowManagerSlot68();
	virtual WindowLayout *winCreateLayout(BFMERetailAsciiString filename);
};

extern GameWindowManager *TheWindowManager;
extern WindowLayout *gameInfoWindowLayout;
extern GameWindow *gameInfoWindowParent;

void CreateLANGameInfoWindow(GameWindow *sizeAndPosWin)
{
	if (!gameInfoWindowLayout)
		gameInfoWindowLayout = TheWindowManager->winCreateLayout(
			BFMERetailAsciiString("Menus/GameInfoWindow.wnd"));

	gameInfoWindowLayout->runInit();
	gameInfoWindowLayout->bringForward();
	gameInfoWindowLayout->hide(1);

	if (!gameInfoWindowParent || !sizeAndPosWin)
		return;

	Int x, y, width, height;
	sizeAndPosWin->winGetScreenPosition(&x, &y);
	gameInfoWindowParent->winSetPosition(x, y);
	sizeAndPosWin->winGetSize(&width, &height);
	gameInfoWindowParent->winSetSize(width, height);
}
