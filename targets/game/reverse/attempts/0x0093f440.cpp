// ?Rva0093F440_LoadCharacterData@Rva00941400Font@@QAEPBURva00941400CharRecord@@G@Z
// partial score=0.07 date=2026-09-22
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Array-backed BFME glyph rasterizer called by the 0x009412F0 lookup.

#include <windows.h>

extern "C" __declspec(dllimport) DWORD WINAPI GetGlyphIndicesW(
	HDC dc, LPCWSTR text, int count, LPWORD glyphs, DWORD flags);

struct FontCharsClassGDIState
{
	int references;
	HGDIOBJ old_bitmap;
	HBITMAP bitmap;
	unsigned char *bitmap_bits;
	HDC dc;
};

#define TheFontCharsGDIState (*(FontCharsClassGDIState **)0x0134AEAC)

struct Rva00941400CharRecord
{
	unsigned short value;
	short width;
	short extra;
	unsigned short *buffer;
};

struct Rva00941400Buffer
{
	unsigned short *buffer;
};

struct Rva0093F440SelectObjectGuard
{
	HDC device_context;
	HGDIOBJ old_object;

	~Rva0093F440SelectObjectGuard()
	{
		SelectObject(device_context, old_object);
	}
};

class FontCharsClass
{
public:
	void Update_Current_Buffer(int width);
};

class Rva00941400Font
{
public:
	Rva00941400CharRecord const *Rva0093F440_LoadCharacterData(unsigned short character);

private:
	char fields_00[0x14];
	Rva00941400Buffer **buffers;
	char fields_18[8];
	int buffer_count;
	char fields_24[4];
	int current_pixel_offset;
	int character_height;
	int character_ascent;
	char fields_34[4];
	int pixel_overlap;
	char fields_3c[4];
	int sample_width;
	char fields_44[4];
	HGDIOBJ font;
	Rva00941400CharRecord *ascii[256];
	Rva00941400CharRecord **unicode;
	unsigned short first_unicode;
	unsigned short last_unicode;
};

Rva00941400CharRecord const *Rva00941400Font::Rva0093F440_LoadCharacterData(
	unsigned short character)
{
	FontCharsClassGDIState *state = TheFontCharsGDIState;
	HDC dc = state->dc;
	Rva0093F440SelectObjectGuard old_font;
	old_font.device_context = dc;
	old_font.old_object = SelectObject(dc, font);
	unsigned short glyph_index = 0xffff;
	GetGlyphIndicesW(dc, &character, 1, &glyph_index, 1);
	if (glyph_index == 0xffff)
	{
		if (character < 256)
			ascii[character] = reinterpret_cast<Rva00941400CharRecord *>(-1);
		else
			unicode[character - first_unicode] = reinterpret_cast<Rva00941400CharRecord *>(-1);
		return reinterpret_cast<Rva00941400CharRecord const *>(-1);
	}

	const int samples = sample_width;
	const int sample_area = samples * samples;
	const int half_sample_area = sample_area / 2;
	const int sample_step = 64 / samples;
	const int scaled_sample_width = samples * sample_step;
	SIZE text_size = { 0, 0 };
	if (!GetTextExtentPoint32W(dc, &character, 1, &text_size))
	{
		text_size.cx = 1;
		text_size.cy = 1;
	}

	const int glyph_width = (text_size.cx + samples - 1) / samples +
		pixel_overlap;
	const int glyph_height = (text_size.cy + samples - 1) / samples;
	reinterpret_cast<FontCharsClass *>(this)->Update_Current_Buffer(glyph_width);
	Rva00941400Buffer *current_buffer = buffers[buffer_count - 1];
	unsigned short *glyph = current_buffer->buffer + current_pixel_offset;

	const int upper_margin = character_ascent / 2;
	const int lower_margin = character_ascent - upper_margin;
	glyph += glyph_width * upper_margin;
	ZeroMemory(glyph, glyph_width * upper_margin * sizeof(*glyph));
	ZeroMemory(glyph + glyph_width * glyph_height,
		glyph_width * lower_margin * sizeof(*glyph));

	const int horizontal_blocks = (glyph_width + sample_step - 1) / sample_step;
	const int vertical_blocks = (glyph_height + sample_step - 1) / sample_step;
	for (int block_y = 0; block_y < vertical_blocks; ++block_y)
	{
		for (int block_x = 0; block_x < horizontal_blocks; ++block_x)
		{
			RECT rect = { 0, 0, scaled_sample_width, text_size.cy };
			ExtTextOutW(dc, -block_x * sample_step, -block_y * sample_step,
				2, &rect, &glyph_index, 1, 0);

			int x_begin = block_x * sample_step;
			int x_end = x_begin + sample_step;
			if (x_end > text_size.cx)
				x_end = text_size.cx;
			int y_begin = block_y * sample_step;
			int y_end = y_begin + sample_step;
			if (y_end > text_size.cy)
				y_end = text_size.cy;
			unsigned int intensity = 0;
			for (int y = y_begin; y < y_end; ++y)
			{
				unsigned char const *pixel = state->bitmap_bits + ((y * 64) + x_begin) * 3;
				for (int x = x_begin; x < x_end; ++x)
				{
					intensity += *pixel >> 4;
					pixel += 3;
				}
			}
			unsigned int alpha = (intensity + half_sample_area) / sample_area;
			glyph[block_y * glyph_width + block_x] =
				static_cast<unsigned short>((alpha << 12) | 0x0fff);
		}
	}

	Rva00941400CharRecord *data = new Rva00941400CharRecord;
	data->value = character;
	data->width = static_cast<short>(glyph_width);
	data->extra = 0;
	data->buffer = current_buffer->buffer + current_pixel_offset;
	if (character < 256)
		ascii[character] = data;
	else
		unicode[character - first_unicode] = data;
	current_pixel_offset += (glyph_width + pixel_overlap) * character_height;
	return data;
}
