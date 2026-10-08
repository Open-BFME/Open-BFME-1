// ?setRect@Rva00435270Layout@@AAEXMMMMHH@Z
// partial score=0.6472 date=2026-10-09
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

class Display;
extern Display *TheDisplay;

class Rva00433DC0DisplaySlots
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
	virtual void slot0A();
	virtual void slot0B();
	virtual void slot0C();
	virtual void slot0D();
	virtual void slot0E();
	virtual void slot0F();
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
	virtual void slot1A();
	virtual void slot1B();
	virtual void slot1C();
	virtual void slot1D();
	virtual void slot1E();
	virtual void slot1F();
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
	virtual void slot2A();
	virtual void slot2B();
	virtual void begin();
	virtual void slot2D();
	virtual void slot2E();
	virtual void outline(float left, float top, float width, float height, float border, unsigned long color);
	virtual void fill(float left, float top, float width, float height, int color);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void end();
	// ?drawFill@Rva00433DC0DisplaySlots@@QAEXMMMMH@Z absent-from-retail
	void drawFill(float left, float top, float width, float height, int color)
	{
		begin();
		fill(left, top, width, height, color);
		end();
	}
	// ?drawOutline@Rva00433DC0DisplaySlots@@QAEXMMMMMK@Z absent-from-retail
	void drawOutline(float left, float top, float width, float height, float border, unsigned long color)
	{
		begin();
		outline(left, top, width, height, border, color);
		end();
	}
};

// ?bfmeMin@@YAABHABH0@Z absent-from-retail
static const int &bfmeMin(const int &first, const int &second)
{
	return second < first ? second : first;
}

class Rva00435270Layout
{
private:
	void setRect(float left, float top, float right, float bottom, int color, int border);
	char m_unreconstructed00[0x28];
	int m_progress28;
};

// ?setRect@Rva00435270Layout@@AAEXMMMMHH@Z present-unmatched
void Rva00435270Layout::setRect(float left, float top, float right, float bottom, int color, int border)
{
	float width = right - left;
	float height = bottom - top;
	int originalAlpha = (unsigned int)color >> 24;
	color &= 0x00ffffff;
	int alpha = bfmeMin(m_progress28, originalAlpha);
	color |= alpha << 24;
	reinterpret_cast<Rva00433DC0DisplaySlots *>(TheDisplay)->drawFill(left, top, width, height, color);
	alpha = bfmeMin(m_progress28, alpha * 2);
	reinterpret_cast<Rva00433DC0DisplaySlots *>(TheDisplay)->drawOutline(left - border + 1.0f, top - border + 1.0f, width + border * 2, height + border * 2, (float)border, alpha << 24);
	reinterpret_cast<Rva00433DC0DisplaySlots *>(TheDisplay)->drawOutline(left - border, top - border, width + border * 2, height + border * 2, (float)border, 0x7f7f7f7f);
}
