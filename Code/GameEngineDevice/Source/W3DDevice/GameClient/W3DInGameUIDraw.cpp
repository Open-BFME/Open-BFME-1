// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: W3DInGameUI::draw, retail 0x006FBFF0. The upstream control
// flow is preserved; these TU-local facades expose only the BFME slots and
// fields proven by this body.

class View {};

#define DECLARE_TEN(prefix) \
	virtual void prefix##0(); virtual void prefix##1(); \
	virtual void prefix##2(); virtual void prefix##3(); \
	virtual void prefix##4(); virtual void prefix##5(); \
	virtual void prefix##6(); virtual void prefix##7(); \
	virtual void prefix##8(); virtual void prefix##9();

class DisplaySlots
{
public:
	DECLARE_TEN(displayA)
	DECLARE_TEN(displayB)
	virtual void displayC0(); virtual void displayC1();
	virtual void displayC2(); virtual void displayC3();
	virtual void displayC4(); virtual void displayC5();
	virtual void displayC6(); virtual void displayC7();
	virtual void displayC8();
};

class Display : public DisplaySlots
{
public:
	virtual View *getFirstView();             // +0x74
	virtual View *getNextView(View *view);    // +0x78
};

class WindowManagerSlots
{
public:
	DECLARE_TEN(windowA)
	DECLARE_TEN(windowB)
	DECLARE_TEN(windowC)
	virtual void windowD0(); virtual void windowD1();
	virtual void windowD2(); virtual void windowD3();
	virtual void windowD4(); virtual void windowD5();
};

class GameWindowManager : public WindowManagerSlots
{
public:
	virtual void winRepaintWindows();         // +0x90

private:
	unsigned char m_unmodelled_04[0x34];

public:
	int m_drawState;                          // +0x38
};

class W3DInGameUISlots
{
public:
	virtual void draw();                      // slot zero, overridden below
	DECLARE_TEN(inGameA)                      // slots 1..10
	DECLARE_TEN(inGameB)                      // slots 11..20
	DECLARE_TEN(inGameC)                      // slots 21..30
	DECLARE_TEN(inGameD)                      // slots 31..40
	DECLARE_TEN(inGameE)                      // slots 41..50
	DECLARE_TEN(inGameF)                      // slots 51..60
	DECLARE_TEN(inGameG)                      // slots 61..70
	virtual void inGameH1(); virtual void inGameH2();
	virtual void inGameH3();                  // slots 71..73
};

class W3DInGameUI : public W3DInGameUISlots
{
public:
	virtual void draw();
	virtual void preDraw();                   // +0x128, slot 74
	virtual void postDraw();                  // +0x12c, slot 75
	DECLARE_TEN(inGameTailA)                  // slots 76..85
	DECLARE_TEN(inGameTailB)                  // slots 86..95
	DECLARE_TEN(inGameTailC)                  // slots 96..105
	virtual void inGameTailD0(); virtual void inGameTailD1();
	virtual void inGameTailD2(); virtual void inGameTailD3();
	virtual void drawSelectionRegion();       // +0x1b8, slot 110
	virtual void drawMoveHints(View *view);    // +0x1bc, slot 111
	virtual void drawAttackHints(View *view);  // +0x1c0, slot 112
	virtual void drawPlaceAngle(View *view);   // +0x1c4, slot 113

private:
	unsigned char m_unmodelled_04[0x1c];
	bool m_isDragSelecting;                   // +0x20
};

#undef DECLARE_TEN

extern Display *TheDisplay;
extern GameWindowManager *TheWindowManager;

void W3DInGameUI::draw()
{
	int drawState = TheWindowManager->m_drawState;
	switch (drawState)
	{
		case -1:
		case 1:
			break;
		case 0:
			TheWindowManager->winRepaintWindows();
			return;
		default:
			return;
	}

	preDraw();
	if (m_isDragSelecting)
		drawSelectionRegion();

	if (TheDisplay)
	{
		for (View *view = TheDisplay->getFirstView(); view;
			 view = TheDisplay->getNextView(view))
		{
			drawMoveHints(view);
			drawAttackHints(view);
			drawPlaceAngle(view);
		}
	}

	postDraw();
	TheWindowManager->winRepaintWindows();
}
