// ?rva004B0D40@Gen_004B1720@@QAEXXZ
// partial score=0.5056 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath
// stlport
//
// Retail 0x004B0D40 (979 B, ret at +0x3D2): vtable 0x010FD1D8 slot 7 of the
// SubsystemInterface-derived menu owner (ctor 0x004B18B0, clear 0x004B1720,
// reset 0x004B19A0). Lays out the owner's windows on a rotating ring: count>1
// rotates the start direction by 1 - min(650, t)/650 (0x012B6624 = 650.0f),
// sizes each window by min(1, m_3c), positions it along the direction, syncs
// the window's map<UnsignedInt, Rva004B0C80Value> target through bfmeGo1073B,
// keeps an unused bounds rectangle, rotates by m_40 and toggles status 0x200
// against 600.0f; clears m_active after 650.
// Measured: 969/979 B, 464 raw differing, probe shape 0.953. Residue: retail
// keeps `distance` alive on the x87 stack (reloads dir.y, fmul st(2), spills
// offset.y) and loads both scale floats before reusing EAX; that is the
// missing 4-byte frame slot (0x44 vs 0x48). Rotate is Coord2D::Rotate
// (coord2d.cpp) with separate sine/cosine locals, force-inlined as retail.
// Landing needs one pin: find<UnsignedInt> of this map -> 0x004B0530 (row
// dup_4b0530, next to this map's matched _M_insert/insert_unique) and a DIR32
// name for 0x012B6624.
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

#define RVA004B0D40_MIN(a, b) ((a) < (b) ? (a) : (b))

// Coord2D::Rotate (coord2d.cpp), inlined here as retail does.
__forceinline void rva004B0D40Rotate(Coord2DBase &v, float angle)
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

	float new_x = cosine * v.x - sine * v.y;
	float new_y = cosine * v.y;
	new_y += sine * v.x;
	v.y = new_y;
	v.x = new_x;
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

	Coord2DBase dir;
	dir.x = 0.0f;
	dir.y = (Real)(1 < count ? -1 : 0);
	if (count > 1)
	{
		Real t = RVA004B0D40_MIN(g_rva004B0D40Duration, (Real)m_38);
		rva004B0D40Rotate(dir, 1.0f - t / g_rva004B0D40Duration);
	}

	struct { Coord2DBase lo, hi; } bounds;
	bounds.lo.y = 1000000.0f;
	bounds.lo.x = 1000000.0f;
	bounds.hi.y = 0.0f;
	bounds.hi.x = 0.0f;

	for (_STL::vector<GameWindow *>::iterator it = m_windows.begin(); it != m_windows.end(); ++it)
	{
		GameWindow *window = *it;
		Int width = (Int)(((Real)m_28 - 1.0f) * RVA004B0D40_MIN(1.0f, m_3c) + 1.0f);
		Int height = (Int)(((Real)m_2c - 1.0f) * RVA004B0D40_MIN(1.0f, m_3c) + 1.0f);
		window->winSetSize(width, height);

		Real distance = ((Real)m_30 - 0.1f) * m_3c + 0.1f;
		Coord2DBase offset;
		offset.x = dir.x * distance;
		offset.y = dir.y * distance;
		Int x = (Int)((Real)m_20 + offset.x);
		Int y = (Int)((Real)m_24 + offset.y);

		_STL::map<UnsignedInt, Rva004B0C80Value>::iterator found = m_targets.find((UnsignedInt &)window);
		if (found != m_targets.end())
		{
			const Coord2DBase *scale = g_theWindowManager->getScreenPoint();
			Rva004B0C80Target *target = (*found).second.m_target;
			Real sy = (Real)y * scale->y;
			Real sx = (Real)x * scale->x;
			if (sx != target->m_left || sy != target->m_top)
			{
				bfmeGo1073B(&target->m_08, sx, sy);
				target->m_left = sx;
				target->m_top = sy;
			}
		}

		x -= width / 2;
		y -= height / 2;
		window->winSetPosition(x, y);
		if ((Real)x < bounds.lo.x)
			bounds.lo.x = (Real)x;
		if ((Real)y < bounds.lo.y)
			bounds.lo.y = (Real)y;
		x += width;
		y += height;
		if ((Real)x > bounds.hi.x)
			bounds.hi.x = (Real)x;
		if ((Real)y > bounds.hi.y)
			bounds.hi.y = (Real)y;

		rva004B0D40Rotate(dir, m_40);

		if ((Real)m_38 < 600.0f)
			window->winSetStatus(0x200);
		else
			window->winClearStatus(0x200);
	}

	if ((Real)m_38 > g_rva004B0D40Duration)
		m_active = false;
}
