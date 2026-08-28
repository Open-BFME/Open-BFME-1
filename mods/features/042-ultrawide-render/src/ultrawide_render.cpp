// 042-ultrawide-render — keep BFME's fixed-resolution UI in a centred 4:3
// render band on displays wider than its reference aspect.
//
// 041-ultrawide-ui changed layout inputs, but it had no matching renderer
// transform and was visually inert.  This feature keeps that layout correction
// only where it is needed, then changes the renderer's authoritative pieces:
//
//   * screen-layout roots and control-bar scheme selection use a height-led
//     4:3 logical width, then restore the physical Display width.  Root screen
//     positions therefore already include the centred margin.
//   * Set_Coordinate_Range receives the physical centred interval
//     [left,left+band], so those already-centred coordinates are not shifted a
//     second time.
//   * both BFME Render2D bodies are hooked immediately after their retail
//     DX8Wrapper::Set_Viewport call, so that logical range is presented in a
//     centred 4:3 hardware viewport.
//
// Ready image surfaces take a third path through copySurfaceRects006e and do
// not reach either vertex renderer.  Their destination rectangles are already
// physical screen coordinates after the layout correction, so this feature
// deliberately leaves that copy routine alone.  This avoids applying a second
// scale to buttons and other surface-backed UI.
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

static Int field_int(void *base, Int offset)
{
	return *(Int *)((unsigned char *)base + offset);
}

static void set_field_int(void *base, Int offset, Int value)
{
	*(Int *)((unsigned char *)base + offset) = value;
}

// BFME Display::m_width/m_height are the first scalar fields after its
// polymorphic prefix.  These are the same fields used by the old 041 layout
// experiment and by the exact parseScreenRect body.
#define TheDisplay (*(void **)0x012F1270)
enum {
	DISPLAY_WIDTH = 0x08,
	DISPLAY_HEIGHT = 0x0C,
	CONTROLBAR_FOREGROUND_MARKER_X = 0x2D0,
	CONTROLBAR_BACKGROUND_MARKER_X = 0x2D8
};

static Int logical_width(Int width, Int height)
{
	if (width <= 0 || height <= 0)
		return width;
	Int reference_width = height * 4 / 3;
	return width < reference_width ? width : reference_width;
}

static Int safe_left(void)
{
	if (TheDisplay == 0)
		return 0;
	Int width = field_int(TheDisplay, DISPLAY_WIDTH);
	Int height = field_int(TheDisplay, DISPLAY_HEIGHT);
	return (width - logical_width(width, height)) / 2;
}

static Int g_scheme_depth;
static Int g_scheme_saved_width;
static Int g_parse_active;
static Int g_parse_saved_width;
static Int g_parse_physical_width;
static Int *g_parse_x;

// parseScreenRect at RVA 0x004854F0 receives four stack arguments.  During a
// root parse, make Display::getWidth report the 4:3 logical width, then add the
// physical centring margin back to the stored root x before restoring width.
// Child coordinates remain relative to their already-centred parent.
extern "C" __declspec(dllexport) void __cdecl ui_parse_begin(
	Int *x, Int *y, Int *width, Int *height)
{
	(void)y;
	(void)width;
	(void)height;
	if (TheDisplay == 0 || x == 0 || g_parse_active)
		return;

	g_parse_active = 1;
	g_parse_x = x;
	g_parse_saved_width = field_int(TheDisplay, DISPLAY_WIDTH);
	g_parse_physical_width = g_scheme_depth ? g_scheme_saved_width : g_parse_saved_width;
	Int ui_width = logical_width(g_parse_physical_width,
		field_int(TheDisplay, DISPLAY_HEIGHT));
	if (ui_width < g_parse_physical_width)
		set_field_int(TheDisplay, DISPLAY_WIDTH, ui_width);
}

extern "C" __declspec(dllexport) void __cdecl ui_parse_end(void *parent)
{
	if (!g_parse_active)
		return;

	if (parent == 0 && g_parse_x != 0) {
		*g_parse_x += (g_parse_physical_width -
			logical_width(g_parse_physical_width,
				field_int(TheDisplay, DISPLAY_HEIGHT))) / 2;
	}
	set_field_int(TheDisplay, DISPLAY_WIDTH, g_parse_saved_width);
	g_parse_x = 0;
	g_parse_physical_width = 0;
	g_parse_saved_width = 0;
	g_parse_active = 0;
}

// The three ControlBarSchemeManager selection bodies calculate their scheme
// multiplier from Display::getWidth.  Keep that calculation in 4:3 space,
// while allowing the normal retail function to restore the physical width.
extern "C" __declspec(dllexport) void __cdecl ui_scheme_begin(void *manager)
{
	(void)manager;
	if (TheDisplay == 0)
		return;
	if (g_scheme_depth++ == 0) {
		g_scheme_saved_width = field_int(TheDisplay, DISPLAY_WIDTH);
		Int ui_width = logical_width(g_scheme_saved_width,
			field_int(TheDisplay, DISPLAY_HEIGHT));
		if (ui_width < g_scheme_saved_width)
			set_field_int(TheDisplay, DISPLAY_WIDTH, ui_width);
	}
}

extern "C" __declspec(dllexport) void __cdecl ui_scheme_end(void)
{
	if (g_scheme_depth <= 0)
		return;
	--g_scheme_depth;
	if (g_scheme_depth == 0) {
		if (TheDisplay != 0)
			set_field_int(TheDisplay, DISPLAY_WIDTH, g_scheme_saved_width);
		g_scheme_saved_width = 0;
	}
}

// The command-bar draw callbacks subtract the stored marker from the current
// marker window before drawing scheme images.  Store a zero-origin marker so
// the callback's offset supplies the centred physical margin exactly once.
extern "C" __declspec(dllexport) void __cdecl ui_controlbar_markers(void *bar)
{
	if (bar == 0)
		return;
	Int left = safe_left();
	if (left == 0)
		return;
	*(Int *)((unsigned char *)bar + CONTROLBAR_FOREGROUND_MARKER_X) -= left;
	*(Int *)((unsigned char *)bar + CONTROLBAR_BACKGROUND_MARKER_X) -= left;
}

// Set_Coordinate_Range at RVA 0x00933A50 is a thiscall entry.  The generated
// cave shim passes ECX as renderer and stack:0 as the const RectClass pointer.
// We alter only the full-screen range.  Its physical bounds already include
// the centred root margin, so custom local coordinate ranges remain untouched.
extern "C" __declspec(dllexport) void __cdecl ui_coordinate_range(
	void *renderer, FloatRect *range)
{
	(void)renderer;
	if (range == 0 || range->left != 0.0f || range->top != 0.0f ||
		range->bottom <= 0.0f)
		return;

	UnsignedInt width = ScreenWidth;
	UnsignedInt height = ScreenHeight;
	UnsignedInt band = reference_band(width, height);
	if (width == 0 || height == 0 || band == width)
		return;
	Int left = centered_left(width, band);
	range->left = (Real)left;
	range->right = (Real)(left + (Int)band);
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
