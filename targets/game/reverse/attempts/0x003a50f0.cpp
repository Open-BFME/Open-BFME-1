// ?rva003A50F0@Gen003BDE80Element@@QAEXXZ
// partial score=0.63 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc
// Retail 0x003A50F0: advances a two-dimensional element toward its destination.
extern "C" double __cdecl sqrt(double value);
#pragma intrinsic(sqrt)
extern const float g_bfmeDefaultBU;
extern const double g_bfmeSubB3;

struct Coord2D { float x, y; };

class Gen003BDE80Element
{
public:
	void rva003A50F0();
	float rva003A40A0();
	void rva003A4FD0(Coord2D *delta);
private:
	char m_beforeCurrent[0x0c];
	float m_currentX;
	float m_currentY;
	float m_targetX;
	float m_targetY;
};

#pragma comment(linker, "/alternatename:?rva003A40A0@Gen003BDE80Element@@QAEMXZ=?j_000239d9@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva003A4FD0@Gen003BDE80Element@@QAEXPAUCoord2D@@@Z=?j_0001b577@@YAXXZ")

void Gen003BDE80Element::rva003A50F0()
{
	Coord2D target = *(const Coord2D *)&m_targetX;
	float dx = target.x - m_currentX;
	float dy = target.y - m_currentY;
	float inverse = g_bfmeDefaultBU / (float)sqrt(dx * dx + dy * dy);
	float directionX = dx * inverse;
	float directionY = dy * inverse;
	float amount = rva003A40A0();
	m_currentX += directionX * amount;
	m_currentY += directionY * amount;
	Coord2D remaining;
	remaining.x = m_targetX - m_currentX;
	remaining.y = m_targetY - m_currentY;
	if ((float)sqrt(remaining.x * remaining.x + remaining.y * remaining.y) <= g_bfmeSubB3)
		rva003A4FD0(&remaining);
}
