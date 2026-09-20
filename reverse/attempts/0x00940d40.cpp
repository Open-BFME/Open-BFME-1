// ?loadCharacterData@FontCharsClass@@QAEPBUFontCharsClassCharDataStruct@@G@Z
// partial score=0.34 date=2026-09-19
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// BFME FontCharsClass cache-miss rasterizer.  The retail body renders a
// supersampled glyph into the process-wide 64-pixel-wide GDI bitmap and
// downsamples its high nibble into the 4-bit alpha channel of an A4R4G4B4
// character-buffer entry.

#include <windows.h>
#include <map>

struct ABC
{
	int abcA;
	unsigned int abcB;
	int abcC;
};

extern "C" __declspec(dllimport) BOOL WINAPI GetTextExtentPointI(
	HDC dc, const unsigned short *glyphs, int count, SIZE *size);
extern "C" __declspec(dllimport) BOOL WINAPI GetCharABCWidthsI(
	HDC dc, unsigned int first, unsigned int count,
	const unsigned short *glyphs, ABC *widths);

struct FontCharsGDIState
{
	int references;
	HGDIOBJ old_bitmap;
	HBITMAP bitmap;
	unsigned char *bitmap_bits;
	HDC dc;
};

struct Gen_uw_0093c330
{
	HDC device_context;
	HGDIOBJ old_object;
	~Gen_uw_0093c330()
	{
		SelectObject(device_context, old_object);
	}
};

#define TheFontCharsGDIState (*(FontCharsGDIState **)0x0134AEAC)

struct FontCharsClassCharDataStruct
{
	unsigned short value;
	short width;
	short spacing;
	short reserved;
	unsigned short *buffer;
};

struct FontCharsBuffer
{
	unsigned short buffer[32768];
};

struct Gen_lt_00940b40 : public std::less<unsigned short> {};
typedef std::map<unsigned short, int, Gen_lt_00940b40> FontCharDataMap;

class FontCharsClass
{
public:
	const FontCharsClassCharDataStruct *loadCharacterData(unsigned short character);

private:
	void Update_Current_Buffer(int width);

	unsigned char field_00[0x14];
	FontCharsBuffer **buffers;             // +0x14, witnessed by retail access
	unsigned char field_18[8];
	int buffer_count;                      // +0x20
	unsigned char field_24[4];
	int current_pixel_offset;              // +0x28
	int character_height;                  // +0x2c, name_oracle witness
	int character_ascent;                  // +0x30, upstream family evidence
	unsigned char field_34[0x0c];
	int sample_width;                      // +0x40, BFME-only font setting
	unsigned char field_44[4];
	HFONT font;                            // +0x48, matched GDI-font source
	unsigned char field_4c[0x404];
	FontCharDataMap character_data;         // +0x450, matched Get_Char_Data
};

const FontCharsClassCharDataStruct *FontCharsClass::loadCharacterData(
	unsigned short character)
{
	FontCharsClassCharDataStruct *data;
	if (character == 0xffff)
	{
		data = new FontCharsClassCharDataStruct;
		data->value = character;
		data->width = 0;
		data->spacing = 0;
		data->buffer = 0;
		character_data[character] = reinterpret_cast<int>(data);
		return data;
	}

	HDC dc = TheFontCharsGDIState->dc;
	Gen_uw_0093c330 old_font;
	old_font.device_context = dc;
	old_font.old_object = SelectObject(dc, font);
	const int samples = sample_width;
	const int sample_area = samples * samples;
	const int half_sample_area = sample_area / 2;
	const int sample_step = 64 / samples;
	const int scaled_sample_width = samples * sample_step;

	SIZE text_size;
	if (!GetTextExtentPointI(dc, &character, 1, &text_size))
	{
		text_size.cx = 1;
		text_size.cy = 1;
	}

	ABC abc;
	if (!GetCharABCWidthsI(dc, character, 1, 0, &abc))
	{
		abc.abcA = 0;
		abc.abcB = 1;
		abc.abcC = 0;
	}

	int source_width = abc.abcB;
	if (abc.abcC > 0)
		source_width += abc.abcC;
	if (abc.abcA > 0)
		source_width += abc.abcA;
	else
		abc.abcA = -abc.abcA;

	const int glyph_width = (source_width + samples - 1) / samples;
	const int glyph_height = (text_size.cy + samples - 1) / samples;
	Update_Current_Buffer(glyph_width);

	FontCharsBuffer *current_buffer = buffers[buffer_count - 1];
	unsigned short *glyph = current_buffer->buffer + current_pixel_offset;
	const int lower_margin = character_ascent - character_ascent / 2;
	ZeroMemory(glyph, glyph_width * character_ascent * sizeof(*glyph));
	ZeroMemory(glyph + glyph_width * (character_ascent + lower_margin),
		glyph_width * lower_margin * sizeof(*glyph));
	glyph += glyph_width * character_ascent;

	const int horizontal_blocks = (glyph_width + sample_step - 1) / sample_step;
	const int vertical_blocks = (text_size.cy + sample_step - 1) / sample_step;
	for (int block_y = 0; block_y < vertical_blocks; ++block_y)
	{
		for (int block_x = 0; block_x < horizontal_blocks; ++block_x)
		{
			RECT draw_rect = { 0, 0, 0, 0 };
			ExtTextOutW(dc, -abc.abcA, 0, 0x12,
				&draw_rect, &character, 1, 0);

			const int x_begin = block_x * sample_step;
			int x_end = x_begin + sample_step;
			if (x_end > source_width)
				x_end = source_width;
			const int y_begin = block_y * sample_step;
			int y_end = y_begin + sample_step;
			if (y_end > text_size.cy)
				y_end = text_size.cy;

			unsigned int intensity = 0;
			for (int y = y_begin; y < y_end; ++y)
			{
				const unsigned char *pixel = TheFontCharsGDIState->bitmap_bits
					+ ((y * 64) + x_begin) * 3;
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

	data = new FontCharsClassCharDataStruct;
	data->value = character;
	data->width = static_cast<short>(glyph_width);
	data->spacing = static_cast<short>((1 - samples - abc.abcA) / samples);
	data->buffer = current_buffer->buffer + current_pixel_offset;
	character_data[character] = reinterpret_cast<int>(data);
	current_pixel_offset += glyph_width * character_height;
	return data;
}
