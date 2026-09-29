// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Retail 0x006FD180 (277 bytes, thiscall, ret 8): a W3DMouse vtable slot
// (rdata 0x00D207E4 via ILT 0x0002A18A).  Projects a world point through the
// mouse's camera (+0x70) the way the landed W3DView::worldToScreenTriReturn
// does, converts the logical screen point to pixels against the display size,
// and reports whether the point projected inside the frustum and within the
// +/-2 logical-screen band.  IDENTITY IS NOT RECOVERED.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct ICoord2D
{
	Int x;
	Int y;
};

class Vector3
{
public:
	Vector3() {}
	Vector3(Real x, Real y, Real z) : X(x), Y(y), Z(z) {}

	Real X;
	Real Y;
	Real Z;
};

class CameraClass
{
public:
	enum ProjectionResType
	{
		INSIDE_FRUSTUM,
		OUTSIDE_FRUSTUM,
		OUTSIDE_NEAR_CLIP,
		OUTSIDE_FAR_CLIP
	};

	ProjectionResType Project(Vector3 &destination, const Vector3 &source) const;
};

extern void W3DLogicalScreenToPixelScreen(Real, Real, Int *, Int *, Int, Int);

class Display
{
public:
#define DISPLAY_SLOT(N) virtual void slot##N() = 0
	DISPLAY_SLOT(00); DISPLAY_SLOT(01); DISPLAY_SLOT(02); DISPLAY_SLOT(03);
	DISPLAY_SLOT(04); DISPLAY_SLOT(05); DISPLAY_SLOT(06); DISPLAY_SLOT(07);
	DISPLAY_SLOT(08); DISPLAY_SLOT(09); DISPLAY_SLOT(10);
#undef DISPLAY_SLOT
	virtual UnsignedInt getWidth() = 0;
	virtual UnsignedInt getHeight() = 0;
};

extern Display *TheDisplay;

class Rva006FD180Mouse
{
public:
	Bool worldToScreen(const Coord3D *world, ICoord2D *screen);

private:
	char m_pad00[0x70];
	CameraClass *m_camera;
};

Bool Rva006FD180Mouse::worldToScreen(const Coord3D *world, ICoord2D *screen)
{
	if (world == 0 || screen == 0)
		return false;

	Vector3 worldVector(world->x, world->y, world->z);
	Vector3 screenVector;
	CameraClass::ProjectionResType projection = m_camera->Project(screenVector, worldVector);

	Real width = (Real)TheDisplay->getWidth();
	Real height = (Real)TheDisplay->getHeight();
	W3DLogicalScreenToPixelScreen(screenVector.X, screenVector.Y, &screen->x, &screen->y,
		(Int)width, (Int)height);

	if (screenVector.X > 2.0f || screenVector.Y > 2.0f ||
		screenVector.X < -2.0f || screenVector.Y < -2.0f)
		return false;
	if (projection == CameraClass::OUTSIDE_NEAR_CLIP || projection == CameraClass::OUTSIDE_FAR_CLIP)
		return false;
	return true;
}
