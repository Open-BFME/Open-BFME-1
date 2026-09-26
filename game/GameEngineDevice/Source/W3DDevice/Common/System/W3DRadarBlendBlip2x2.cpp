// cl: /DNDEBUG /MD /EHsc
// stlport
// Retail 0x006C2DD0: the static helper W3DRadar::renderObjectList (0x006C43F0,
// call at +0x298) uses to alpha-blend one radar blip into the radar surface.
// It locks the rectangle around (x, y) clipped to the texture bounds the
// caller passes from W3DRadar+0x14A4/+0x14A8, blends the packed color into
// each pixel through Rva006C13E0 with a symmetric 2x2 quarter alpha table
// (the caller passes the table at VA 0x0111D854), then unlocks.  Its 3x3
// sibling at 0x006C2A20 is the same shape with radius 3.
//
// The private register convention (width in ECX, the rest on the stack) is
// MSVC's static-function convention: std::max takes x and y by reference, so
// they stay memory homed and only width is passed in a register.  The
// TU-local caller below exists only so the static has a visible call site.
#include <stddef.h>
#include <stdlib.h>
#include <algorithm>

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/surfaceclass.h
// BFME adds the rectangle Lock overload (0x008FC710).
class SurfaceClass
{
public:
	void *Lock(int *pitch, int left, int top, int right, int bottom);
	void Unlock(void);
};

int Rva006C13E0(int *color, int source, unsigned char alpha);

class SurfaceLock006C2DD0
{
public:
	SurfaceLock006C2DD0(SurfaceClass *surface, void *&bits, int *pitch,
		int left, int top, int right, int bottom)
		: m_surface(surface)
	{
		bits = surface->Lock(pitch, left, top, right, bottom);
	}
	~SurfaceLock006C2DD0() { m_surface->Unlock(); }

	SurfaceClass *m_surface;
};

static void rva006C2DD0(SurfaceClass *surface, int width, int height, int x, int y,
	int color, const unsigned char alpha[][2])
{
	int x0 = x - 2;
	int x1 = x + 2;
	int y0 = y - 2;
	int y1 = y + 2;
	int left = __max(x0, 0);
	int top = __max(y0, 0);
	int right = __min(x1, width);
	int bottom = __min(y1, height);
	int pitch;
	void *bits;
	SurfaceLock006C2DD0 lock(surface, bits, &pitch, left, top, right, bottom);
	if (bits == NULL)
		return;

	int i, j, dy;

	// upper half: rows above the centre, alpha rows counting in from the edge
	for (j = top; j < y && j < bottom; ++j)
	{
		int *row = (int *)((char *)bits + (j - top) * pitch);
		dy = j - y0;
		for (i = left; i < x && i < right; ++i)
			Rva006C13E0(&row[i - left], color, alpha[i - x0][dy]);
		for (i = std::max(x, left); i < right; ++i)
			Rva006C13E0(&row[i - left], color, alpha[x1 - i - 1][dy]);
	}

	if (y >= bottom)
		return;

	// lower half: the same table mirrored
	for (j = std::max(y, top); j < bottom; ++j)
	{
		dy = y1 - j - 1;
		int *row = (int *)((char *)bits + (j - top) * pitch);
		for (i = left; i < x && i < right; ++i)
			Rva006C13E0(&row[i - left], color, alpha[i - x0][dy]);
		for (i = std::max(x, left); i < right; ++i)
			Rva006C13E0(&row[i - left], color, alpha[x1 - i - 1][dy]);
	}
}

// absent-from-retail: TU-local caller shaped like W3DRadar::renderObjectList's
// call, so MSVC gives the static above its private register convention.
static const unsigned char s_blipAlpha006C2DD0[2][2] = { { 0x00, 0x4a }, { 0x4a, 0xff } };

void Rva006C2DD0Caller(SurfaceClass *surface, int width, int height, int x, int y, int color)
{
	rva006C2DD0(surface, width, height, x, y, color, s_blipAlpha006C2DD0);
}
