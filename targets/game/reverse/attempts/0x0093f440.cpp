// ?Store_GDI_Char@FontCharsClass@@AAEPBVFontCharsClassCharDataStruct@@G@Z
// partial score=0.2829 date=2026-10-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
// stlport
#include <windows.h>
#include "always.h"
#include "refcount.h"
#include "wwstring.h"
#include "vector.h"
#include "bittype.h"
#include "vector2i.h"
#include <string.h>
#include <algorithm>

extern "C" __declspec(dllimport) DWORD WINAPI GetGlyphIndicesW(
	HDC hdc, LPCWSTR lpstr, int c, LPWORD pgi, DWORD fl);
#ifndef GGI_MARK_NONEXISTING_GLYPHS
#define GGI_MARK_NONEXISTING_GLYPHS 0x0001
#endif

class FontCharsBuffer;

class FontCharsClassGdiState
{
public:
	int m_refs;
	HBITMAP m_oldBitmap;
	HBITMAP m_bitmap;
	uint8 *m_bits;
	HDC m_dc;
};

extern FontCharsClassGdiState *g_fontCharsGdiState0134AEAC;
#define g_fontCharsGdiState g_fontCharsGdiState0134AEAC

class FontCharsClassCharDataStruct
{
public:
	WCHAR Value;
	short Width;
	short Offset04;
	uint16 *Buffer;
};

class FontCharsSelectObjectGuard
{
public:
	FontCharsSelectObjectGuard(HDC dc, HGDIOBJ object)
		: m_dc(dc), m_oldObject(::SelectObject(dc, object))
	{
	}
	~FontCharsSelectObjectGuard()
	{
		::SelectObject(m_dc, m_oldObject);
	}
	HDC m_dc;
	HGDIOBJ m_oldObject;
};

struct BfmeFontCharsBuffer
{
	uint16 *Buffer;
	int BufferMax;
	int BufferPosition;
};

class FontCharsClass : public W3DMPO, public RefCountClass
{
public:
	FontCharsClass();
	virtual ~FontCharsClass();
	FontCharsClass *AlternateUnicodeFont;

private:
	const FontCharsClassCharDataStruct *Store_GDI_Char(WCHAR ch);
	void Update_Current_Buffer(int char_width);

	StringClass Name;
	DynamicVectorClass<FontCharsBuffer *> BufferList;
	int CurrPixelOffset;
	int CharHeight;
	int CharAscent;
	int CharOverhang;
	int PixelOverlap;
	float PointSize;
	int ExtraSetting;
	StringClass GDIFontName;
	HFONT GDIFont;
	FontCharsClassCharDataStruct *ASCIICharArray[256];
	FontCharsClassCharDataStruct **UnicodeCharArray;
	unsigned int CharMap[3];
	uint16 FirstUnicodeChar;
	uint16 LastUnicodeChar;
	bool IsBold;
};

const FontCharsClassCharDataStruct *
FontCharsClass::Store_GDI_Char(WCHAR ch)
{
	FontCharsSelectObjectGuard old_font(g_fontCharsGdiState->m_dc, GDIFont);

	unsigned int glyph_index = 0xFFFF;
	::GetGlyphIndicesW(g_fontCharsGdiState->m_dc, &ch, 1, (WORD*)&glyph_index, GGI_MARK_NONEXISTING_GLYPHS);
	if ((WORD)glyph_index == 0xFFFF) {
		if (ch < 256) {
			ASCIICharArray[ch] = (FontCharsClassCharDataStruct *)-1;
		} else {
			UnicodeCharArray[ch - FirstUnicodeChar] = (FontCharsClassCharDataStruct *)-1;
		}
		return (FontCharsClassCharDataStruct *)-1;
	}

	int sample_area = ExtraSetting * ExtraSetting;
	int half_sample_area = sample_area >> 1;
	int step = 64 / ExtraSetting;
	SIZE cell;
	cell.cx = ExtraSetting * step;
	cell.cy = ExtraSetting * (64 / ExtraSetting);

	SIZE char_size;
	if (!::GetTextExtentPoint32W(g_fontCharsGdiState->m_dc, &ch, 1, &char_size)) {
		char_size.cx = char_size.cy = 1;
	}

	int char_width = (char_size.cx + ExtraSetting - 1) / ExtraSetting + PixelOverlap;
	int char_height = (char_size.cy + ExtraSetting - 1) / ExtraSetting;

	Update_Current_Buffer(char_width);
	uint16 *curr_buffer_p = reinterpret_cast<BfmeFontCharsBuffer *>(BufferList[BufferList.Count() - 1])->Buffer;
	curr_buffer_p += CurrPixelOffset;

	int top = CharAscent / 2;
	int bottom = CharAscent - top;
	uint16 *glyph_p = curr_buffer_p + top * char_width;
	::memset(curr_buffer_p, 0, top * char_width * sizeof(uint16));
	::memset(glyph_p + char_height * char_width, 0, bottom * char_width * sizeof(uint16));

	int blocks_x = (char_width + step - 1) / step;
	int blocks_y = (char_height + step - 1) / step;
	Vector2i block;
	int &block_x = block.I;
	int &block_y = block.J;
	for (block_y = 0; block_y < blocks_y; block_y++) {
		for (block_x = 0; block_x < blocks_x; block_x++) {
			RECT rect = { 0, 0, cell.cx, cell.cy };
			::ExtTextOutW(g_fontCharsGdiState->m_dc, -(block_x * cell.cx), -(block_y * cell.cy),
				ETO_OPAQUE, &rect, &ch, 1, NULL);

			int x_begin = block_x * step;
			int x_end = x_begin + step;
			if (x_end > char_width) {
				x_end = char_width;
			}
			int y_begin = block_y * step;
			int y_end = y_begin + step;
			if (y_end > char_height) {
				y_end = char_height;
			}

			for (int y = y_begin; y < y_end; y++) {
				uint16 *dest = glyph_p + y * char_width + x_begin;
				int sy_begin = ExtraSetting * y;
				int sy_end = _STL::min<int>(ExtraSetting + sy_begin, char_size.cy);
				for (int x = x_begin; x < x_end; x++) {
					int sx_begin = ExtraSetting * x;
					int sx_end = ExtraSetting + sx_begin;
					if (sx_end > char_size.cx) {
						sx_end = char_size.cx;
					}
					unsigned int total = 0;
					for (int sy = sy_begin; sy < sy_end; sy++) {
						for (int sx = sx_begin; sx < sx_end; sx++) {
							uint8 pixel_value = g_fontCharsGdiState->m_bits[((sy - block_y * cell.cy) * 64 + sx - block_x * cell.cx) * 3];
							total += pixel_value >> 4;
						}
					}
					*dest++ = (uint16)((((total + half_sample_area) / sample_area) << 12) | 0x0FFF);
				}
			}
		}
	}

	FontCharsClassCharDataStruct *char_data = new FontCharsClassCharDataStruct;
	char_data->Value = ch;
	char_data->Width = char_width;
	char_data->Offset04 = 0;
	char_data->Buffer = reinterpret_cast<BfmeFontCharsBuffer *>(BufferList[BufferList.Count() - 1])->Buffer + CurrPixelOffset;

	if (ch < 256) {
		ASCIICharArray[ch] = char_data;
	} else {
		UnicodeCharArray[ch - FirstUnicodeChar] = char_data;
	}

	CurrPixelOffset += (char_width + PixelOverlap) * CharHeight;
	return char_data;
}
