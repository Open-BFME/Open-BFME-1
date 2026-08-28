// 042-ultrawide-render — keep BFME's fixed-resolution UI in a centred 4:3
// render band on displays wider than its reference aspect.
//
// 041-ultrawide-ui changed layout inputs, but the retail renderer still
// converted those coordinates against the physical display and then submitted
// a full-screen D3D viewport.  That made the experiment visually inert.  This
// feature changes the renderer's two authoritative pieces instead:
//
//   * Set_Coordinate_Range receives a height-led 4:3 screen range, so the
//     Render2D vertex coordinates are generated in the same logical space as
//     BFME's reference layouts.
//   * both BFME Render2D bodies are hooked immediately after their retail
//     DX8Wrapper::Set_Viewport call, so that logical range is presented in a
//     centred 4:3 hardware viewport.
//
// Ready image surfaces take a third path through copySurfaceRects006e and do
// not reach either vertex renderer.  Its destination rectangle is transformed
// by the same integer mapping here.  This is deliberately renderer-level: it
// covers the game-window UI, command bar, display strings, and the APT host
// rendering without pretending that parser-time width substitutions are a
// projection fix.
//
// This is a naked MSVC 7.1 payload: /NODEFAULTLIB, no CRT, and no loader.  The
// only floating point operations are the coordinate-range multiply and the
// D3D viewport's literal depth values.  MSVC emits _fltused for those; the
// local definition is only the compiler marker, not a runtime implementation.

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

static Int map_surface_x(Int x, UnsignedInt width, UnsignedInt band, Int left)
{
	if (width == 0 || band == width)
		return x;

	// UI coordinates are display-sized (normally only a few thousand pixels),
	// so this product remains in signed 32-bit range without a CRT 64-bit
	// helper.  Keeping the division signed also preserves off-screen clipping
	// rectangles instead of clamping them prematurely.
	return left + (x * (Int)band) / (Int)width;
}

// Set_Coordinate_Range at RVA 0x00933A50 is a thiscall entry.  The generated
// cave shim passes ECX as renderer and stack:0 as the const RectClass pointer.
// We alter only a screen-like range whose origin is (0,0) and whose width is
// wider than its height-led 4:3 reference.  Custom local coordinate ranges
// remain untouched.
extern "C" __declspec(dllexport) void __cdecl ui_coordinate_range(
	void *renderer, FloatRect *range)
{
	(void)renderer;
	if (range == 0 || range->left != 0.0f || range->top != 0.0f ||
		range->bottom <= 0.0f)
		return;

	Real reference_width = range->bottom * 1.3333333333f;
	if (range->right > reference_width)
		range->right = reference_width;
}

// The exact Render2DClass::Render body at RVA 0x00933E50 writes its physical
// viewport through DX8Wrapper::Set_Viewport at 0x00933FD0.  The hook is at
// 0x00933FD5, after that call and before the retail renderer continues.
// The body keeps EBP as its Render2DClass this pointer at this point.
//
// The separate active BFME W3DDisplay renderer body starts at RVA 0x00934940
// (entered through the incremental thunk at 0x006E9B86).  It writes its
// physical viewport at 0x00934AD5; the hook at 0x00934ADA sees EDI as its
// renderer this pointer.  The body contains no later Set_Viewport call.
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
	// a half-width centred strip.  If this build looks unchanged, this render
	// body is not the path painting the tested screen.
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

// copySurfaceRects006e at RVA 0x00904D20 is a cdecl function with five
// dword arguments.  W3DDisplay::drawImage passes the destination BfmeRect as
// its fourth argument (stack:3 at this entry), before the retail copy occurs.
// This is the ready-surface branch that bypasses Render2D entirely.
extern "C" __declspec(dllexport) void __cdecl ui_copy_surface(BfmeRect *destination)
{
	if (destination == 0)
		return;

	UnsignedInt width = ScreenWidth;
	UnsignedInt height = ScreenHeight;
	UnsignedInt band = reference_band(width, height);
	if (width == 0 || height == 0 || band == width)
		return;

	Int left = centered_left(width, band);
#ifdef ULTRAWIDE_UI_RENDER_DEBUG
	band = width / 2;
	left = (Int)(width / 4);
#endif
	destination->left = map_surface_x(destination->left, width, band, left);
	destination->right = map_surface_x(destination->right, width, band, left);
}
