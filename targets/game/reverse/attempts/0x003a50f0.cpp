// ?rva003A50F0@Rva003A50F0Element@@QAEXXZ
// partial score=0.6704 date=2026-10-30
// cl: /O2
extern "C" double sqrt(double x);
#pragma intrinsic(sqrt)
class Rva003A40A0Host { public: float limit(); };
class Rva003A4FD0State { public: void update(void *delta); };
struct Coord2D
{
	float x, y;
	__forceinline void scale(float s) { x *= s; y *= s; }
};
struct Rva003A50F0Dir
{
	float x, y;
	Rva003A50F0Dir(float ax, float ay) : x(ax), y(ay) {}
	__forceinline void scale(float s) { x *= s; y *= s; }
};
class Rva003A50F0Element
{
public:
	void rva003A50F0();
private:
	char m_beforeCurrent[0x0c];
	Coord2D m_current;
	Coord2D m_target;
};
// ?rva003A50F0@Rva003A50F0Element@@QAEXXZ
void Rva003A50F0Element::rva003A50F0()
{
	Coord2D dir = m_target;
	Rva003A50F0Dir delta(dir.x - m_current.x, dir.y - m_current.y);
	float inv = 1.0f / (float)sqrt(delta.x * delta.x + delta.y * delta.y);
	dir.x = delta.x * inv;
	dir.y = delta.y * inv;
	float amount = reinterpret_cast<Rva003A40A0Host *>(this)->limit();
	dir.scale(amount);
	m_current.x += dir.x;
	m_current.y += dir.y;
	Coord2D remaining;
	remaining.x = m_target.x - m_current.x;
	remaining.y = m_target.y - m_current.y;
	if (sqrt(remaining.y * remaining.y + remaining.x * remaining.x) < 1.0)
		reinterpret_cast<Rva003A4FD0State *>(this)->update(&remaining);
}
