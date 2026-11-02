// cl: /DNDEBUG /MD /EHsc
// readable body of ?Create_GDI_Font@FontCharsClass@@AAEXPBD@Z: game/Libraries/Source/WWVegas/WW3D2/render2dsentence.cpp
// Retail 0x0093C570, 398 bytes: BFME's FontCharsClass::Create_GDI_Font. The
// render2dsentence.cpp unit keeps Zero Hour's integer PointSize layout, so this
// split unit carries the BFME float point size (+0x3C) and extra setting
// (+0x40) seen by the matched Initialize_GDI_Font sibling.
// Shape ported from Open BFME 2 Code/Libraries/Source/WWVegas/WW3D2/
// FontCharsClassCreateGDIFont.cpp (donor 45afcff3): "Generals" maps to Arial
// with a 0.4 width scale, PixelOverlap is the clamped 0.125 of the point size
// and the metrics come from the shared GDI state's DC (VA 0x0134AEAC +0x10).
#include <math.h>
#include <string.h>
#include <windows.h>

class FontCharsClassGdiState
{
public:
	int refs;
	void *old_bitmap;
	void *bitmap;
	int unused;
	HDC dc;
};

// retail VA 0x0134AEAC: the shared GDI state.
extern FontCharsClassGdiState *g_fontCharsGdiState0134AEAC;

class FontCharsClass
{
private:
	void Create_GDI_Font(const char *font_name);

	unsigned char pad_to_metrics[0x2C];
	int charHeightDiv;		// +0x2C
	int charExtLeadDiv;		// +0x30
	int charOverhangDiv;	// +0x34
	int PixelOverlap;		// +0x38
	float point_size;		// +0x3C
	int extra_setting;		// +0x40
	unsigned char pad_to_font[4];
	HFONT GDIFont;			// +0x48
	unsigned char pad_to_bold[0x414];
	bool is_bold;			// +0x460
};

// Remembers the DC and the font it replaced; retail keeps the old font in
// its own stack slot (as in the donor), which a bare HGDIOBJ local does not.
struct FontCharsSelectFont
{
	HDC dc;
	HGDIOBJ old;
	FontCharsSelectFont(HDC d, HFONT font) : dc(d) { old = ::SelectObject(d, font); }
	void restore() { ::SelectObject(dc, old); }
};

// ?Create_GDI_Font@FontCharsClass@@AAEXPBD@Z
void FontCharsClass::Create_GDI_Font(const char *font_name)
{
	bool doingGenerals = false;
	if (strcmp(font_name, "Generals") == 0) {
		font_name = "Arial";
		doingGenerals = true;
	}

	float height_base = point_size;
	float width_scale = 0.0f;
	if (doingGenerals) {
		width_scale = height_base * 0.4f;
	}

	PixelOverlap = (int)floor(height_base * 0.125f + 0.5f);
	if (PixelOverlap < 0) {
		PixelOverlap = 0;
	}
	if (PixelOverlap > 4) {
		PixelOverlap = 4;
	}

	int weight = is_bold ? FW_BOLD : FW_NORMAL;

	float width_product = (float)extra_setting * width_scale + 0.5f;
	float height_product = (float)extra_setting * height_base + 0.5f;
	float font_height = (float)floor(height_product);

	GDIFont = ::CreateFontA((int)-font_height, (int)floor(width_product),
		0, 0, weight, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, 0, font_name);

	HDC screen_dc = g_fontCharsGdiState0134AEAC->dc;
	FontCharsSelectFont sel(screen_dc, GDIFont);

	TEXTMETRIC text_metric = { 0 };
	::GetTextMetricsA(g_fontCharsGdiState0134AEAC->dc, &text_metric);

	charHeightDiv = (extra_setting + text_metric.tmExternalLeading + text_metric.tmHeight - 1) / extra_setting;
	charExtLeadDiv = text_metric.tmExternalLeading / extra_setting;
	charOverhangDiv = (extra_setting + text_metric.tmOverhang - 1) / extra_setting;

	sel.restore();
}
