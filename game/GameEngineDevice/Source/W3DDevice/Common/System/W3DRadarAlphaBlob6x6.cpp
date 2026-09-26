// cl: /DNDEBUG /DWIN32 /MD /EHsc
// stlport
// Retail 0x006C2A20: TU-private W3DRadar helper called once from
// W3DRadar::renderObjectList (0x006C43F0, call at +0x279) with the radar
// surface, width in EDX, height, blip x/y, packed colour and the static
// 3x3 alpha table at VA 0x0111D858.  It locks the clipped 6x6 rectangle
// around (x, y) and blends each pixel through Rva006C13E0, mirroring the
// quarter table across both axes.  The unwind state 0 destroys a
// one-pointer lock guard whose out-of-line destructor is 0x006C13D0; the
// guard is only live after Lock returns, so Lock runs inside its ctor.
// 0x006C2DD0 is the radius-2 sibling (2x2 table at VA 0x0111D854).

typedef int Int;
typedef int Color;
typedef unsigned char UnsignedByte;

#include <algorithm>

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/surfaceclass.h
class SurfaceClass
{
public:
	void *Lock(int *pitch, int left, int top, int right, int bottom);
	void Unlock(void);
};

Color Rva006C13E0(Color *color, Color source, UnsignedByte alpha);

class SurfaceLock006C13D0
{
public:
	SurfaceLock006C13D0(SurfaceClass *surface, void *&bits, int *pitch,
		int left, int top, int right, int bottom) : m_surface(surface)
	{
		bits = m_surface->Lock(pitch, left, top, right, bottom);
	}
	~SurfaceLock006C13D0() { m_surface->Unlock(); }

private:
	SurfaceClass *m_surface;
};

static void rva006C2A20(SurfaceClass *surface, Int width, Int height,
	Int x, Int y, Color color, const UnsignedByte *alpha)
{
	Int blobLeft = x - 3;
	Int blobTop = y - 3;
	Int blobRight = x + 3;
	Int blobBottom = y + 3;
	Int left = (blobLeft > 0) ? blobLeft : 0;
	Int startY = (blobTop > 0) ? blobTop : 0;
	Int right = (blobRight < width) ? blobRight : width;
	Int endY = (blobBottom < height) ? blobBottom : height;

	int pitch;
	void *bits;
	SurfaceLock006C13D0 lock(surface, bits, &pitch, left, startY, right, endY);
	if (bits)
	{
		Int row;
		Int col;
		for (row = startY; row < y && row < endY; ++row)
		{
			Color *dst = (Color *)((char *)bits + (row - startY) * pitch);
			Int dy = row - blobTop;
			for (col = left; col < x && col < right; ++col)
				Rva006C13E0(&dst[col - left], color, alpha[(col - blobLeft) * 3 + dy]);
			for (col = std::max(x, left); col < right; ++col)
				Rva006C13E0(&dst[col - left], color, alpha[(blobRight - col - 1) * 3 + dy]);
		}
		if (y < endY)
		for (row = std::max(y, startY); row < endY; ++row)
		{
			Int dy = blobBottom - row - 1;
			Color *dst = (Color *)((char *)bits + (row - startY) * pitch);
			for (col = left; col < x && col < right; ++col)
				Rva006C13E0(&dst[col - left], color, alpha[(col - blobLeft) * 3 + dy]);
			for (col = std::max(x, left); col < right; ++col)
				Rva006C13E0(&dst[col - left], color, alpha[(blobRight - col - 1) * 3 + dy]);
		}
	}
}

// absent-from-retail: TU-local caller that keeps the static above alive so
// MSVC gives it the same private convention (width in EDX, the rest on the
// stack, caller-cleaned) as retail's renderObjectList call site.
void Rva006C2A20Caller(SurfaceClass *surface, Int width, Int height,
	Int x, Int y, Color color, const UnsignedByte *alpha)
{
	rva006C2A20(surface, width, height, x, y, color, alpha);
}
