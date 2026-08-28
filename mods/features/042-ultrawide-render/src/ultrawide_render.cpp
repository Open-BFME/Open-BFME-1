// 042-ultrawide-render — render BFME's fixed-resolution 2D layer into a
// centred, height-led 4:3 band on displays wider than its reference aspect.
//
// The previous revision mixed parser-time Display-width substitutions with a
// renderer viewport.  That left some UI in physical coordinates: it retained
// its vanilla position but was clipped whenever it fell outside the centred
// band.  This revision keeps one coordinate space throughout the layout and
// performs the scale at the two renderer exits instead:
//
//   * Render2D keeps the retail full-display coordinate range [0,width] x
//     [0,height].  Its already-built vertices are presented through a centred
//     viewport whose width is the height-led 4:3 band.  This scales every
//     vertex-rendered UI primitive uniformly and preserves its relative
//     placement.
//   * ready Image surfaces bypass Render2D and are copied by
//     copySurfaceRects006e.  Its destination rectangle receives the same
//     integer x mapping before the retail copy, so buttons and surface-backed
//     controls follow the exact same scale.
//
// Both paths are renderer-level and therefore also cover text, fills, images,
// and the world-overlay UI that BFME submits through the same 2D renderer.
// The 2D camera is not changed; this feature only changes the physical
// presentation of the 2D layer.  The tactical 3D camera remains feature 040.
//
// This is a naked MSVC 7.1 payload: /NODEFAULTLIB, no CRT, and no loader.  The
// integer rectangle mapping avoids runtime math-library dependencies.  The
// viewport literals cause MSVC to emit _fltused; the local definition is only
// that compiler marker, not a CRT implementation.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

extern "C" const int _fltused = 0;

struct FloatRect
{
	Real left;
	Real top;
	Real right;
	Real bottom;
};

struct BfmeRect
{
	Int left;
	Int top;
	Int right;
	Int bottom;
};

struct Viewport
{
	UnsignedInt x;
	UnsignedInt y;
	UnsignedInt width;
	UnsignedInt height;
	Real min_z;
	Real max_z;
};

// These are the two fields of Render2DClass::Set_Screen_Resolution's
// ScreenResolution object.  The active 00934940 body reads the same values
// immediately before it builds its retail full-screen D3DVIEWPORT8.
#define ScreenWidth (*(UnsignedInt *)0x012D6DB4)
#define ScreenHeight (*(UnsignedInt *)0x012D6DB8)

// DX8Wrapper::Set_Viewport(const D3DVIEWPORT8 *) is the matched BFME retail
// function at RVA 0x009043B0, runtime VA 0x00D043B0.  It is cdecl: the only
// argument is a pointer to the six-dword D3DVIEWPORT8 structure.
typedef void (__cdecl *SetViewport)(const Viewport *viewport);
#define c_set_viewport ((SetViewport)0x00D043B0)

static UnsignedInt reference_band(UnsignedInt width, UnsignedInt height)
{
	if (width == 0 || height == 0)
		return width;

	UnsignedInt four_by_three = height * 4 / 3;
	return width < four_by_three ? width : four_by_three;
}

static Int centered_left(UnsignedInt width, UnsignedInt band)
{
	return (Int)((width - band) / 2);
}

static Int map_x(Int coordinate, UnsignedInt width, UnsignedInt band, Int left)
{
	if (width == 0 || band == width)
		return coordinate;

	// BFME screen rectangles are small enough for this signed product.  Keep
	// the operation integer-only so the naked payload does not pull in __allmul
	// or a CRT conversion helper, and preserve off-screen coordinates for the
	// retail clipping tests.
	return left + (coordinate * (Int)band) / (Int)width;
}

// Set_Coordinate_Range at RVA 0x00933A50 is a thiscall entry.  The generated
// cave shim passes ECX as renderer and stack:0 as the const RectClass pointer.
// Retail callers provide the full physical screen range.  Explicitly retain
// that range here: the scale belongs to the hardware viewport below, not to
// the logical coordinates.  This also makes the policy robust if a caller's
// range has stale right/bottom values after a resolution change.
extern "C" __declspec(dllexport) void __cdecl ui_coordinate_range(
	void *renderer, FloatRect *range)
{
	(void)renderer;
	if (range == 0 || range->left != 0.0f || range->top != 0.0f ||
		range->bottom <= 0.0f)
		return;

	UnsignedInt width = ScreenWidth;
	UnsignedInt height = ScreenHeight;
	if (width == 0 || height == 0)
		return;

	range->right = (Real)width;
	range->bottom = (Real)height;
}

// The exact Render2DClass::Render body at RVA 0x00933E50 writes its physical
// viewport through DX8Wrapper::Set_Viewport at 0x00933FD0.  The hook at
// 0x00933FD5 is after that call and before the retail renderer continues.
//
// The separate active BFME W3DDisplay renderer body starts at RVA 0x00934940
// (entered through the incremental thunk at 0x006E9B86).  It writes its
// physical viewport at 0x00934AD5; the hook at 0x00934ADA sees EDI as its
// renderer this pointer.  Neither body makes a later viewport write.
extern "C" __declspec(dllexport) void __cdecl ui_render_viewport(void *renderer)
{
	(void)renderer;

	UnsignedInt width = ScreenWidth;
	UnsignedInt height = ScreenHeight;
	if (width == 0 || height == 0)
		return;

	UnsignedInt band = reference_band(width, height);
	Int left = centered_left(width, band);

#ifdef ULTRAWIDE_UI_RENDER_DEBUG
	// Diagnostic-only build: every vertex-rendered 2D primitive is forced into
	// a half-width centred strip.  Together with ui_copy_surface this makes a
	// missed renderer path immediately obvious during manual testing.
	band = width / 2;
	left = (Int)(width / 4);
#endif

	Viewport viewport;
	viewport.x = (UnsignedInt)left;
	viewport.y = 0;
	viewport.width = band;
	viewport.height = height;
	viewport.min_z = 0.0f;
	viewport.max_z = 1.0f;
	c_set_viewport(&viewport);
}

// copySurfaceRects006e at RVA 0x00904D20 is a cdecl function with five dword
// arguments.  The fourth explicit argument is the destination BfmeRect
// (stack:3 at this entry), immediately before the retail copy occurs.  This
// is the ready-surface branch that bypasses both vertex renderers.
extern "C" __declspec(dllexport) void __cdecl ui_copy_surface(
	BfmeRect *destination)
{
	if (destination == 0)
		return;

	UnsignedInt width = ScreenWidth;
	UnsignedInt height = ScreenHeight;
	if (width == 0 || height == 0)
		return;

	UnsignedInt band = reference_band(width, height);
	Int left = centered_left(width, band);

#ifdef ULTRAWIDE_UI_RENDER_DEBUG
	band = width / 2;
	left = (Int)(width / 4);
#endif

	destination->left = map_x(destination->left, width, band, left);
	destination->right = map_x(destination->right, width, band, left);
}
