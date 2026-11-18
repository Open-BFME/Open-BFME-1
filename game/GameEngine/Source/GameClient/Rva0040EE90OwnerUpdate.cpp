// Address-derived view of the display update and its six-word drawing state.
extern const float g_rva01075350;
#define Rva01075350Zero g_rva01075350
extern float g_bfmeDefaultBU;
#define Rva01075334One g_bfmeDefaultBU
#define Rva01084068Scale 255.0f

#include "../../Include/Common/ScalarTypes.h"


class Image;

// Local Display view copied from the verified vtable-slot layout already
// proven by ControlBarArrowTransition_draw_Thunk.cpp and reused for the
// sibling body at 0x0046F060: beginImageDraw/+0xB0, drawImageCore/+0xD4,
// endImageDraw/+0xDC.
class Display
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();
	virtual void unused42();
	virtual void unused43();
	virtual void beginImageDraw();
	virtual void unused45();
	virtual void unused46();
	virtual void unused47();
	virtual void unused48();
	virtual void unused49();
	virtual void unused50();
	virtual void unused51();
	virtual void unused52();
	virtual void drawImageCore(const Image *image, Real x0, Real y0,
		Real x1, Real y1, Int color, Int mode);
	virtual void unused54();
	virtual void endImageDraw();
};

extern Display *TheDisplay;

inline void drawImage(Display *display, const Image *image, Real x0,
	Real y0, Real x1, Real y1, Int color, Int mode)
{
	display->beginImageDraw();
	display->drawImageCore(image, x0, y0, x1, y1, color, mode);
	display->endImageDraw();
}

// A six-word image draw record: +0x00 image, +0x04..+0x10 the rectangle
// corners, +0x14 the key the caller must pass to draw it. Two callers name
// it differently: this TU's display update (Rva0040E2F0State) and
// BfmeConv923.cpp's three-record owner (BfmeElem923E).
class Rva0040E2F0State
{
public:
	void call_0040E2F0(void *o, int k, unsigned int c);

	const Image *m_00;
	Real m_04;
	Real m_08;
	Real m_0c;
	Real m_10;
	int m_14;
};

// Retail 0x0040E2F0 (RET 12): draws the record's image through the display
// `o` with colour `c` when `k` matches the record's key.
void Rva0040E2F0State::call_0040E2F0(void *o, int k, unsigned int c)
{
	if (m_00 && k == m_14)
		drawImage((Display *)o, m_00, m_04, m_08, m_0c, m_10, c, 2);
}

class BfmeElem923E
{
public:
	void bfmeTail923E(void *t, void *b);

	const Image *m_00;
	Real m_04;
	Real m_08;
	Real m_0c;
	Real m_10;
	void *m_14;
};

// Retail 0x0040E260 (RET 8): the same draw with colour -1, keyed by `b`.
void BfmeElem923E::bfmeTail923E(void *t, void *b)
{
	if (m_00 && b == m_14)
		drawImage((Display *)t, m_00, m_04, m_08, m_0c, m_10, -1, 2);
}

class Rva0040EE90Owner
{
public:
	void update();

	unsigned char m_000[0x10c];
	volatile int m_10c;
	unsigned char m_110[8];
	float m_118;
	float m_11c;
	Rva0040E2F0State m_120;
};

// ?update@Rva0040EE90Owner@@QAEXXZ
void Rva0040EE90Owner::update()
{
	unsigned int c = 0xffffff;

	if (m_11c > Rva01075350Zero)
	{
		int v = m_10c;

		if (v != 0)
		{
			int negative = v - 1 < 0;
			v = v - 1;
			m_10c = v;
			v &= negative - 1;
			m_10c = v;

			if (v > 0x2d)
			{
				v = 0x2d;
			}
			m_10c = v;

			c = 0xffffffff;
			m_11c = 1.0f;
		}
		else if (m_11c > Rva01075350Zero)
		{
			m_11c = m_11c - m_118;

			if (m_11c <= Rva01075350Zero)
			{
				m_11c = 0;
				m_120.m_00 = 0;
				m_120.m_04 = 0;
				m_120.m_08 = 0;
				m_120.m_0c = 0;
				m_120.m_10 = 0;
				m_120.m_14 = 0;
			}

			float x = (Rva01075334One < m_11c) ? Rva01075334One : m_11c;

			m_11c = x;

			c = ((unsigned int)(int)(x * Rva01084068Scale) << 24) | 0xffffff;
		}

		if (c & 0xff000000)
			m_120.call_0040E2F0(this, 1, c);
	}
}
