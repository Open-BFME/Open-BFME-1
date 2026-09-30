// ?rva004B0D40@Gen_004B1720@@QAEXXZ
// partial score=0.9918 date=2026-09-30
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath
// stlport
//
// Retail 0x004B0D40 (979 B): vtable 0x010FD1D8 slot 7 of the menu owner; lays its
// windows out on a ring rotated by m_40 per step (0x012B6624 = 650.0f duration).
// Residue: 8 B of x87 operand order in both inlined rotations (retail loads dir.y
// first, ours sine/cosine). Landing needs a find<UnsignedInt> pin at 0x004B0530
// and a DIR32 name for 0x012B6624.
#include <map>
#include <vector>
#include <math.h>
#include "coord2d.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

class GameWindow
{
public:
	Int winSetSize(Int width, Int height);
	Int winSetPosition(Int x, Int y);
	UnsignedInt winSetStatus(UnsignedInt status);
	UnsignedInt winClearStatus(UnsignedInt status);
};

class WindowManager
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28();
	virtual const Coord2DBase *getScreenPoint();		// +0x2c
};
extern WindowManager *g_theWindowManager;

// bfmeGo1073B (BfmeConv1073.cpp) takes the target's +0x08 block.
struct BfmeN1073
{
	char m_body[4];
};
void __cdecl bfmeGo1073B(BfmeN1073 *value, Real x, Real y);

struct Rva004B0C80Target
{
	char m_pad00[8];
	BfmeN1073 m_08;			// +0x08, handed to bfmeGo1073B
	Real m_left;				// +0x0c
	Real m_top;				// +0x10
};

struct Rva004B0C80Value
{
	Rva004B0C80Target *m_target;
};

class BfmeB1044
{
public:
	void bfmeTailA1044();	// 0x004B0850 via ILT 0x00006E83
};

extern Real g_rva004B0D40Duration;	// 0x012B6624 (650.0f)

// Window size; height stays in a register but keeps its frame slot.
struct Rva004B0D40Size
{
	Int x;
	Int y;
};

#define RVA004B0D40_MIN(a, b) ((a) < (b) ? (a) : (b))

// Built through the inline constructor so its fields stay on the x87 stack.
// ??0Coord2D@@QAE@MM@Z absent-from-retail
inline Coord2D::Coord2D(float px, float py) { x = px; y = py; }
// ??1Coord2D@@QAE@XZ absent-from-retail
inline Coord2D::~Coord2D() {}

// Coord2D::Rotate (coord2d.cpp), inlined here as retail does.
__forceinline Coord2D &Coord2D::Rotate(float angle)
{
	float sine;
	float cosine;

	sine = (float)sin(angle);
	cosine = (float)cos(angle);
	__asm {
		fld angle
		fsincos
		fstp cosine
		fstp sine
	}

	float new_x = cosine * x - sine * y;
	float new_y = cosine * y;
	new_y += sine * x;
	y = new_y;
	x = new_x;
	return *this;
}

class Gen_004B1720
{
public:
	void rva004B0D40();

private:
	void *m_vtable;
	char *m_name;
	bool m_active;						// +0x08
	_STL::vector<GameWindow *> m_windows;	// +0x0c
	Int m_18;
	Int m_1c;
	Int m_20;							// +0x20
	Int m_24;							// +0x24
	Int m_28;							// +0x28
	Int m_2c;							// +0x2c
	UnsignedInt m_30;					// +0x30
	Int m_34;
	UnsignedInt m_38;					// +0x38
	Real m_3c;							// +0x3c
	Real m_40;							// +0x40
	_STL::map<UnsignedInt, Rva004B0C80Value> m_targets;	// +0x44
};

void Gen_004B1720::rva004B0D40()
{
	UnsignedInt count = m_windows.size();
	if (count == 0)
		return;

	((BfmeB1044 *)this)->bfmeTailA1044();
	if (!m_active)
		return;

	Coord2D dir(0.0f, (Real)(1 < count ? -1 : 0));
	if (count > 1)
	{
		Real t = RVA004B0D40_MIN(g_rva004B0D40Duration, (Real)m_38);
		dir.Rotate(1.0f - t / g_rva004B0D40Duration);
	}

	Coord2DBase lo;
	Coord2DBase hi;
	lo.y = 999999.0f;
	lo.x = 999999.0f;
	hi.y = 0.0f;
	hi.x = 0.0f;

	for (_STL::vector<GameWindow *>::iterator it = m_windows.begin(); it != m_windows.end(); ++it)
	{
		GameWindow *window = *it;
		Rva004B0D40Size size;
		size.x = (Int)(((Real)m_28 - 1.0f) * RVA004B0D40_MIN(1.0f, m_3c) + 1.0f);
		size.y = (Int)(((Real)m_2c - 1.0f) * RVA004B0D40_MIN(1.0f, m_3c) + 1.0f);
		window->winSetSize(size.x, size.y);

		Real distance = ((Real)m_30 - 0.1f) * m_3c + 0.1f;
		Coord2D offset(dir.x * distance, dir.y * distance);
		Int x = (Int)((Real)m_20 + offset.x);
		Int y = (Int)((Real)m_24 + offset.y);

		_STL::map<UnsignedInt, Rva004B0C80Value>::iterator found = m_targets.find((UnsignedInt &)window);
		if (found != m_targets.end())
		{
			const Coord2DBase *screen = g_theWindowManager->getScreenPoint();
			Coord2D scale(screen->x, screen->y);
			Rva004B0C80Target *target = (*found).second.m_target;
			Real sy = (Real)y * scale.y;
			Real sx = (Real)x * scale.x;
			if (sx != target->m_left || sy != target->m_top)
			{
				bfmeGo1073B(&target->m_08, sx, sy);
				target->m_left = sx;
				target->m_top = sy;
			}
		}

		x -= size.x / 2;
		y -= size.y / 2;
		window->winSetPosition(x, y);
		if ((Real)x < lo.x)
			lo.x = (Real)x;
		if ((Real)y < lo.y)
			lo.y = (Real)y;
		x += size.x;
		y += size.y;
		if ((Real)x > hi.x)
			hi.x = (Real)x;
		if ((Real)y > hi.y)
			hi.y = (Real)y;

		dir.Rotate(m_40);

		if ((Real)m_38 < 600.0f)
			window->winSetStatus(0x200);
		else
			window->winClearStatus(0x200);
	}

	if ((Real)m_38 > g_rva004B0D40Duration)
		m_active = false;
}
