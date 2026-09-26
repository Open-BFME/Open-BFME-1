// cl: /O2 /Ob1 /GF /Gy /MD /EHsc /GR /DNDEBUG /DWIN32 /D_WINDOWS /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad

typedef int Color;
typedef bool Bool;

struct ICoord2D
{
	int x;
	int y;
};

#define FALSE 0
#define TRUE 1

class Vector2
{
	public:
	float X;
	float Y;

	Vector2(int x, int y)
		: X((float)x), Y((float)y)
	{
	}
};

class Render2DSentenceClass
{
public:
	void Reset_Polys();
	void Set_Location(const Vector2 &location);
	void Draw_Sentence(int red, int green, int blue, int alpha);
	void Render();

private:
	char m_storage[0xC0];
};

class GameWindowManager
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual Color winMakeColor(unsigned char red, unsigned char green,
		unsigned char blue, unsigned char alpha);
};

extern GameWindowManager *TheWindowManager;

class W3DGameWindow
{
public:
	void drawText(Color color);

private:
	char m_vftable[4];
	Render2DSentenceClass m_textRenderer;
	char m_bfme_pad[0x0C];
	ICoord2D m_textPos;
	Color m_currTextColor;
	Bool m_needPolyDraw;
	Bool m_newTextPos;
};

void W3DGameWindow::drawText(Color color)
{
	Bool needDraw = FALSE;

	if (m_newTextPos)
	{
		m_newTextPos = FALSE;
		needDraw = TRUE;
	}

	if (m_currTextColor != color)
	{
		m_currTextColor = color;
		needDraw = TRUE;
	}

	if (needDraw || m_needPolyDraw)
	{
		Color outline = TheWindowManager->winMakeColor(0, 0, 0, 255);

		m_textRenderer.Reset_Polys();
		m_textRenderer.Set_Location(Vector2(m_textPos.x + 1, m_textPos.y + 1));
		m_textRenderer.Draw_Sentence(outline, outline, outline, outline);

		m_textRenderer.Set_Location(Vector2(m_textPos.x, m_textPos.y));
		m_textRenderer.Draw_Sentence(m_currTextColor, m_currTextColor,
			m_currTextColor, m_currTextColor);

		m_needPolyDraw = FALSE;
	}
	m_textRenderer.Render();
}
