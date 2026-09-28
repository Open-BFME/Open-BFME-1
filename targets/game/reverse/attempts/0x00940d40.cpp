// ?loadCharacterData@FontCharsClass@@QAEPBUFontCharsClassCharDataStruct@@G@Z
// partial score=0.815 date=2026-09-28
// ?loadCharacterData@FontCharsClass@@QAEPBUFontCharsClassCharDataStruct@@G@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
//
// FontCharsClass::loadCharacterData, RVA 00940D40, 1355 bytes through ret 4
// at 00941288. Identity: the pin and the matched Get_Char_Data caller at
// 00941290 (FontCharsClass_Get_Char_Data_BFME.cpp).
//
// Rewritten from the retail disassembly (opus-5.5, 2026-09-28). The older
// bank (1022 B, shape 0.429) rendered one ExtTextOutW per block but lacked
// the per-output-pixel level: retail is six loops deep -- block row, block
// column (ExtTextOutW with ETO_OPAQUE|ETO_GLYPH_INDEX = 0x12 into a clip rect
// of one 64-pixel cell, shifted by lead - bx*cellW, -by*cellH), output row,
// output column, then the samples x samples box it averages from the shared
// 24-bit DIB (GDI state +0x0C, 64 pixels a row, high nibble of the blue byte).
// Layout: FontCharsClass as the matched destructor (FontCharsClassDestructorBFME.cpp):
// DynamicVectorClass BufferList at +0x10 (Vector +0x14, ActiveCount +0x20),
// CurrPixelOffset +0x28, CharHeight +0x2C, CharAscent +0x30, samples +0x40,
// GDIFont +0x48, the char-data map at +0x450.
//
// Measured: 1359 B vs 1355, probe shape 0.815, frame 0xB4 vs retail 0xB8.
// The missing frame slot is the second samples*step product: retail keeps the
// cell width (esp+40) and height (esp+44) as two values computed from the
// same registers (mov eax,ecx; imul ecx,ebx; imul eax,ebx), ours CSEs them
// into one. Forcing a distinct value (samples * (64 / m_samples)) gives the
// 0xB8 frame but a second idiv, so the retail spelling is still unknown.
// Other residues: retail does not strength-reduce the block-row loop
// (it recomputes by*step and by*cellH with imul at each block row and keeps
// by in esp+AC), and holds step in EBX and this in EBP.
#include <windows.h>

struct ABC { int abcA; unsigned int abcB; int abcC; };
enum { Rva940D40_ETO_OPAQUE = 2, Rva940D40_ETO_GLYPH_INDEX = 0x10 };
extern "C" __declspec(dllimport) BOOL WINAPI GetTextExtentPointI(
	HDC dc, unsigned short *glyphs, int count, SIZE *size);
extern "C" __declspec(dllimport) BOOL WINAPI GetCharABCWidthsI(
	HDC dc, unsigned int first, unsigned int count, unsigned short *glyphs, ABC *widths);

class FontCharsClassGdiState
{
public:
	int m_refs;
	HBITMAP m_oldBitmap;
	HBITMAP m_bitmap;
	void *m_bits;
	HDC m_dc;
};
extern FontCharsClassGdiState *g_fontCharsGdiState0134AEAC;

// 0x0093C330: SelectObject(m_dc, m_object) on scope exit; retail's unwind
// funclet passes EBP-0x34 to it, the normal path inlines it.
class Gen_uw_0093c330
{
public:
	Gen_uw_0093c330(HDC dc, HGDIOBJ object) : m_dc(dc), m_object(::SelectObject(dc, object)) {}
	~Gen_uw_0093c330() { apply(); }
	void apply() { ::SelectObject(m_dc, m_object); }
	HDC m_dc;
	HGDIOBJ m_object;
};

struct FontCharsClassCharDataStruct
{
	unsigned short Value;
	short Width;
	short Spacing;
	unsigned short *Buffer;
};

struct FontCharsBuffer
{
	unsigned short *Buffer;
};

namespace _STL
{
template <class T> struct less;
template <class T1, class T2> struct pair;
template <class T> class allocator;
template <class K, class V, class C, class A>
class map
{
public:
	V &operator[](const K &key);
	char m_body[12];
};
}
typedef _STL::map<unsigned short, int, _STL::less<unsigned short>,
	_STL::allocator<_STL::pair<const unsigned short, int> > > FontCharDataMap;

template <class T> struct DynamicVectorShim
{
	void *vptr;
	T *Vector;
	int VectorMax;
	int IsValid;
	int ActiveCount;
	int GrowthStep;
	int Count() const { return ActiveCount; }
	T &operator[](int i) { return Vector[i]; }
};

class FontCharsClass
{
public:
	const FontCharsClassCharDataStruct *loadCharacterData(unsigned short ch);

private:
	void Update_Current_Buffer(int width);

	char m_fields00[0x10];
	DynamicVectorShim<FontCharsBuffer *> BufferList;	// +0x10
	int CurrPixelOffset;				// +0x28
	int CharHeight;					// +0x2c
	int CharAscent;					// +0x30
	int m_dword34[3];
	int m_samples;					// +0x40
	int m_dword44;
	HFONT GDIFont;					// +0x48
	char m_fields4c[0x404];
	FontCharDataMap m_characterData;		// +0x450
};

const FontCharsClassCharDataStruct *FontCharsClass::loadCharacterData(unsigned short ch)
{
	if (ch == 0xffff)
	{
		FontCharsClassCharDataStruct *char_data = new FontCharsClassCharDataStruct;
		char_data->Value = ch;
		char_data->Width = 0;
		char_data->Spacing = 0;
		char_data->Buffer = 0;
		m_characterData[ch] = (int)char_data;
		return char_data;
	}

	Gen_uw_0093c330 oldFont(g_fontCharsGdiState0134AEAC->m_dc, GDIFont);

	int samples = m_samples;
	int sample_area = samples * samples;
	int half_area = sample_area >> 1;
	int step = 64 / samples;
	int cell_width = samples * step;
	int cell_height = (unsigned)step * samples;

	SIZE char_size;
	if (!::GetTextExtentPointI(g_fontCharsGdiState0134AEAC->m_dc, &ch, 1, &char_size))
	{
		char_size.cx = 1;
		char_size.cy = 1;
	}

	int lead = 0;
	ABC abc;
	if (!::GetCharABCWidthsI(g_fontCharsGdiState0134AEAC->m_dc, ch, 1, 0, &abc))
	{
		abc.abcA = 0;
		abc.abcB = 1;
		abc.abcC = 0;
	}
	else
	{
		int width = abc.abcB;
		if (abc.abcC > 0)
			width += abc.abcC;
		if (abc.abcA > 0)
			width += abc.abcA;
		else
			lead = -abc.abcA;
		char_size.cx = width;
	}

	int glyph_width = (char_size.cx + m_samples - 1) / m_samples;
	int glyph_height = (char_size.cy + m_samples - 1) / m_samples;
	Update_Current_Buffer(glyph_width);

	unsigned short *curr_buffer_p = BufferList[BufferList.Count() - 1]->Buffer;
	curr_buffer_p += CurrPixelOffset;
	int top = CharAscent / 2;
	int bottom = CharAscent - top;
	unsigned short *pixels = curr_buffer_p + top * glyph_width;
	memset(curr_buffer_p, 0, top * glyph_width * 2);
	memset(pixels + glyph_height * glyph_width, 0, bottom * glyph_width * 2);
	curr_buffer_p = pixels;

	int blocks_x = (glyph_width + step - 1) / step;
	int blocks_y = (glyph_height + step - 1) / step;
	for (int block_y = 0; block_y < blocks_y; ++block_y)
	{
		for (int block_x = 0; block_x < blocks_x; ++block_x)
		{
			RECT rect = { 0, 0, cell_width, cell_height };
			::ExtTextOutW(g_fontCharsGdiState0134AEAC->m_dc, lead - block_x * cell_width,
				-(block_y * cell_height), Rva940D40_ETO_OPAQUE | Rva940D40_ETO_GLYPH_INDEX, &rect, &ch, 1, NULL);

			int x_begin = block_x * step;
			int x_end = x_begin + step;
			if (x_end > glyph_width)
				x_end = glyph_width;
			int y_begin = block_y * step;
			int y_end = y_begin + step;
			if (y_end > glyph_height)
				y_end = glyph_height;

			for (int y = y_begin; y < y_end; ++y)
			{
				unsigned short *out = curr_buffer_p + y * glyph_width + x_begin;
				int sy_begin = y * m_samples;
				int sy_end = sy_begin + m_samples;
				if (sy_end > char_size.cy)
					sy_end = char_size.cy;
				for (int x = x_begin; x < x_end; ++x)
				{
					int sx_begin = x * m_samples;
					int sx_end = sx_begin + m_samples;
					if (sx_end > char_size.cx)
						sx_end = char_size.cx;
					unsigned int total = 0;
					for (int sy = sy_begin; sy < sy_end; ++sy)
					{
						for (int sx = sx_begin; sx < sx_end; ++sx)
						{
							const unsigned char *bits = (const unsigned char *)g_fontCharsGdiState0134AEAC->m_bits;
							total += bits[(((sy - block_y * cell_height) << 6) + (sx - block_x * cell_width)) * 3] >> 4;
						}
					}
					*out++ = (unsigned short)((((half_area + total) / sample_area) << 12) | 0x0fff);
				}
			}
		}
	}

	FontCharsClassCharDataStruct *char_data = new FontCharsClassCharDataStruct;
	char_data->Value = ch;
	char_data->Width = (short)glyph_width;
	char_data->Spacing = (short)((1 - m_samples - lead) / m_samples);
	char_data->Buffer = BufferList[BufferList.Count() - 1]->Buffer + CurrPixelOffset;
	m_characterData[ch] = (int)char_data;
	CurrPixelOffset += CharHeight * glyph_width;
	return char_data;
}
