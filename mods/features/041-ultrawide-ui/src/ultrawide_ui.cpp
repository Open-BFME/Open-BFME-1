// 041-ultrawide-ui — centered logical UI for BFME's fixed-resolution layouts.
//
// The retail UI has two separate coordinate paths.  GameWindow .wnd files are
// converted by parseScreenRect(), while the tactical command-bar skin draws
// images directly and obtains its scale from ControlBarSchemeManager.  Both
// paths use Display::getWidth(), so this feature gives them a centered 4:3
// logical width for the duration of their layout/calculation and restores the
// physical width before returning.
//
// This is a naked MSVC 7.1 payload: /NODEFAULTLIB, no CRT and no loader.  The
// arithmetic is integer-only.  No renderer, 2D camera, or retail source body
// is replaced.  The root-window translation is applied after retail has
// written the output x/y values, so child windows and their hit regions remain
// relative to the already-centred parent.

typedef int Int;

enum {
	DISPLAY_WIDTH = 0x08,
	DISPLAY_HEIGHT = 0x0C,

	// Proven by the exact BFME ControlBar::init body at RVA 0x004A0F70:
	// the two winGetScreenPosition calls store x at these offsets.
	CONTROLBAR_FOREGROUND_MARKER_X = 0x2D0,
	CONTROLBAR_BACKGROUND_MARKER_X = 0x2D8
};

// TheDisplay is the BFME global used by the reconstructed Display and UI
// sources.  Display::m_width/m_height are the first scalar fields after the
// base/vtable prefix at +0x08/+0x0C; the retail parser reads the same values
// through vtable slots +0x2C/+0x30.
#define TheDisplay (*(void **)0x012F1270)

static Int g_scheme_depth;
static Int g_scheme_saved_width;

static Int g_parse_active;
static Int g_parse_saved_width;
static Int g_parse_physical_width;
static Int *g_parse_x;

static Int field_int(void *base, Int offset)
{
	return *(Int *)((unsigned char *)base + offset);
}

static void set_field_int(void *base, Int offset, Int value)
{
	*(Int *)((unsigned char *)base + offset) = value;
}

static Int logical_width(Int physical_width, Int height)
{
	if (physical_width <= 0 || height <= 0)
		return physical_width;

	// 4:3 is BFME's reference UI aspect.  The UI is height-led: on a wider
	// display, keep the full physical height and reserve a centred 4:3 band.
	Int reference_width = height * 4 / 3;
	return physical_width < reference_width ? physical_width : reference_width;
}

static Int physical_width(void)
{
	if (g_parse_active)
		return g_parse_physical_width;
	if (g_scheme_depth)
		return g_scheme_saved_width;
	if (TheDisplay == 0)
		return 0;
	return field_int(TheDisplay, DISPLAY_WIDTH);
}

static Int safe_left(void)
{
	if (TheDisplay == 0)
		return 0;

	Int width = physical_width();
	Int height = field_int(TheDisplay, DISPLAY_HEIGHT);
	Int ui_width = logical_width(width, height);
	return (width - ui_width) / 2;
}

// Entry of BFME parseScreenRect(Int*,Int*,Int*,Int*) at RVA 0x004854F0.
// The generated shim lifts the four genuine stack arguments at function entry.
// The function's own getWidth calls then see the centered logical width.
extern "C" __declspec(dllexport) void __cdecl ui_parse_begin(
	Int *x, Int *y, Int *width, Int *height)
{
	(void)y;
	(void)width;
	(void)height;
	if (TheDisplay == 0 || x == 0)
		return;

	if (g_parse_active)
		return;

	g_parse_x = x;
	g_parse_saved_width = field_int(TheDisplay, DISPLAY_WIDTH);
	// g_parse_active must remain clear while this is read: when a control-bar
	// scheme is already being built, g_scheme_saved_width is the physical width
	// behind its temporary logical override.
	g_parse_physical_width = g_scheme_depth ? g_scheme_saved_width : g_parse_saved_width;
	g_parse_active = 1;
	Int display_height = field_int(TheDisplay, DISPLAY_HEIGHT);
	Int ui_width = logical_width(g_parse_physical_width, display_height);
	if (ui_width < g_parse_physical_width)
		set_field_int(TheDisplay, DISPLAY_WIDTH, ui_width);
}

// Internal tail at RVA 0x0048569B, after parseScreenRect has stored x/y and
// before it stores width/height.  EBP is still the inlined peekWindow result:
// NULL means a root window, and a non-NULL value means child coordinates are
// already relative to the centred parent and must not be translated again.
extern "C" __declspec(dllexport) void __cdecl ui_parse_end(void *parent)
{
	if (!g_parse_active)
		return;

	if (parent == 0 && g_parse_x != 0)
		*g_parse_x += (g_parse_physical_width -
			logical_width(g_parse_physical_width,
				field_int(TheDisplay, DISPLAY_HEIGHT))) / 2;

	set_field_int(TheDisplay, DISPLAY_WIDTH, g_parse_saved_width);
	g_parse_x = 0;
	g_parse_physical_width = 0;
	g_parse_saved_width = 0;
	g_parse_active = 0;
}

// Entry of the three BFME ControlBarSchemeManager selection bodies:
// setControlBarScheme RVA 0x004AD880, the real
// setControlBarSchemeByPlayerTemplate body RVA 0x004ADE40, and
// setControlBarSchemeByPlayer RVA 0x004AE080.  Their bodies calculate both
// the manager multiplier and ControlBarScheme::init's local multiplier from
// Display::getWidth().
extern "C" __declspec(dllexport) void __cdecl ui_scheme_begin(void *manager)
{
	(void)manager;
	if (TheDisplay == 0)
		return;

	if (g_scheme_depth++ == 0) {
		g_scheme_saved_width = field_int(TheDisplay, DISPLAY_WIDTH);
		Int height = field_int(TheDisplay, DISPLAY_HEIGHT);
		Int ui_width = logical_width(g_scheme_saved_width, height);
		if (ui_width < g_scheme_saved_width)
			set_field_int(TheDisplay, DISPLAY_WIDTH, ui_width);
	}
}

// Common exits are at setControlBarScheme RVA 0x004AD913,
// setControlBarSchemeByPlayerTemplate RVA 0x004ADFF1, and
// setControlBarSchemeByPlayer RVA 0x004AE2B9.  The template tail is the last
// shared path for both its normal and null-template branches.
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

// ControlBar::init's exact BFME body stores the foreground/background marker
// screen positions at +0x2D0/+0x2D8.  The central .wnd parser has already put
// those roots at safeLeft; make the stored bases logical (zero-origin) so the
// existing W3DCommandBar*Draw callbacks produce the same safeLeft offset when
// they draw the direct command-bar skin images.
// Hook point: ControlBar::init internal epilogue RVA 0x004A1DA6, after both
// marker writes and before the retail cleanup/return sequence.
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
