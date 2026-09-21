// ?inGameTailA0@W3DInGameUI@@UAEXXZ
// partial score=0.15 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef unsigned char byte;

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
	virtual void displayA10();
	virtual Int getWidth();   // +0x2c slot 11
	virtual Int getHeight();  // +0x30 slot 12
};

class Display : public DisplaySlots
{
public:
	virtual View *getFirstView();
	virtual View *getNextView(View *view);
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
	virtual void winRepaintWindows();

private:
	unsigned char m_unmodelled_04[0x34];

public:
	int m_drawState;
};

class W3DInGameUISlots
{
public:
	virtual void draw();
	DECLARE_TEN(inGameA)
	DECLARE_TEN(inGameB)
	DECLARE_TEN(inGameC)
	DECLARE_TEN(inGameD)
	DECLARE_TEN(inGameE)
	DECLARE_TEN(inGameF)
	DECLARE_TEN(inGameG)
	virtual void inGameH1(); virtual void inGameH2();
	virtual void inGameH3();
};

class DisplayLine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09();
	virtual void setColor(UnsignedInt color);                 // +0x28 slot 10
	virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void draw(Int x, Int y, Int a, Int b);             // +0x38 slot 14
	virtual void getSize(Int *width, Int *height);             // +0x3c slot 15
};

struct MilitarySubtitleRecord
{
	DisplayLine *m_lines[4];      // +0x08 .. +0x14
	Int m_lineY[4];               // +0x18 .. +0x24
	DisplayLine *m_block;         // +0x28
	Int m_lineCount;              // +0x2c
	UnsignedInt m_startFrame;     // +0x34 (end - retail reads +0x34 first)
	UnsignedInt m_dummy;
	UnsignedInt m_color;          // +0x40
};

extern "C" void __cdecl GameGetColorComponents(Int color, byte *r, byte *g,
	byte *b, byte *a);

#define g_bfme40BC00 (*(const Real *)0x01075334)
#define g_bfme40BC28 (*(const Real *)0x01075358)
#define g_bfme40BC0C (*(const Real *)0x0107533C)
#define g_bfme4C8615 (*(const Real *)0x0108615C)

class W3DInGameUI : public W3DInGameUISlots
{
public:
	virtual void draw();
	virtual void preDraw();
	virtual void postDraw();
	virtual void inGameTailA0();
	virtual void inGameTailA1(); virtual void inGameTailA2();
	virtual void inGameTailA3(); virtual void inGameTailA4();
	virtual void inGameTailA5(); virtual void inGameTailA6();
	virtual void inGameTailA7(); virtual void inGameTailA8();
	virtual void inGameTailA9();
	DECLARE_TEN(inGameTailB)
	DECLARE_TEN(inGameTailC)
	virtual void inGameTailD0(); virtual void inGameTailD1();
	virtual void inGameTailD2(); virtual void inGameTailD3();
	virtual void drawSelectionRegion();
	virtual void drawMoveHints(View *view);
	virtual void drawAttackHints(View *view);
	virtual void drawPlaceAngle(View *view);

private:
	unsigned char m_unmodelled_04[0x818 - 4];

public:
	MilitarySubtitleRecord *m_subtitle;    // +0x818
	unsigned char m_pad81c[0x86c - 0x81c];
	Real m_widthFraction;                  // +0x86c
	Real m_heightFraction;                 // +0x870
	unsigned char m_pad874[0x890 - 0x874];
	Real m_fadeDuration;                   // +0x890
};

#undef DECLARE_TEN

extern Display *TheDisplay;

void W3DInGameUI::inGameTailA0()
{
	MilitarySubtitleRecord *record = m_subtitle;
	if (record == 0)
		return;

	Int frameDelta = (Int)(record->m_startFrame - record->m_dummy);
	Real fraction = (Real)frameDelta / m_fadeDuration;
	fraction = g_bfme40BC00 - fraction;

	Int width = TheDisplay->getWidth();
	Real fx = (Real)width * m_widthFraction + g_bfme40BC0C;
	Int startX = (Int)fx;

	Int height = TheDisplay->getHeight();
	Real fy = (Real)height * m_heightFraction + g_bfme40BC0C;
	Int startY = (Int)fy;

	byte r, g, b, a;
	GameGetColorComponents((Int)record->m_color, &r, &g, &b, &a);
	UnsignedInt packed = ((UnsignedInt)r) << 24;

	Int cursorY = startY;
	Int index = 0;
	for (; (UnsignedInt)index <= record->m_lineCount; ++index)
	{
		DisplayLine *line = record->m_lines[index];
		Int measuredW, measuredH;
		line->getSize(&measuredW, &measuredH);
		Int lineX = startX + record->m_lineY[index];
		line->setColor(packed);
		line->draw(lineX, cursorY, 1, 1);
		cursorY += measuredH;
	}

	Int blockY = startY + *(Int *)((char *)record + 0x18 + record->m_lineCount * 4);
	byte blend1 = (byte)0;
	byte blend2 = (byte)0;
	UnsignedInt blockColor = (((UnsignedInt)blend1) << 24)
		| (((UnsignedInt)g) << 16) | (((UnsignedInt)b) << 8) | a;

	record->m_block->setColor(blockColor);
	record->m_block->draw(cursorY, blockY, 1, 1);
}
