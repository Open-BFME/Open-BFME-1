// Retail 0x00589040 draws a line from two two-float points.
// The Display vtable slots at 0xB0, 0xD4, and 0xDC prove the three calls.
// TheDisplay at 0x012F1270 supplies the receiver.

extern const float g_bfmeK1257;

class Rva00589040Vec2
{
public:
	float m_x;
	float m_y;
};

class Display
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
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
	virtual void begin();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void line(int tag, float x1, float y1, float x2, float y2,
		int color, int width);
	virtual void slot54();
	virtual void end();
};

extern Display *TheDisplay;

void Rva00589040Draw(int tag, float bx, float by,
	const Rva00589040Vec2 *v1, const Rva00589040Vec2 *v2)
{
	bx += (v1->m_x - v2->m_x) * g_bfmeK1257;

	by += (v1->m_y - v2->m_y) * g_bfmeK1257;

	float ey = by + v2->m_y;
	float ex = bx + v2->m_x;

	Display *display = TheDisplay;

	TheDisplay->begin();
	display->line(tag, bx, by, ex, ey, -1, 2);
	display->end();
}
