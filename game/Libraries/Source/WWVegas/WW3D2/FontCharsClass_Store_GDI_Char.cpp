// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x0093F440, 1329 bytes, RET 4: the BFME glyph-cache loader that
// rasterizes one character through the shared GDI DIB in 64x64 tiles and
// box-filters it by Scale into 4-bit alpha (Zero Hour Store_GDI_Char
// semantics). Ported from the BFME 2 donor
// Code/Libraries/Source/WWVegas/WW3D2/FontCharsClassLoadCharBitmap.cpp
// (open-bfme-2 b5a7b8290). BFME 1 facts from the retail body: font +0x48,
// Scale +0x40, overlap +0x38, ExtraHeight +0x30, CharHeight +0x2C,
// CurrPixelOffset +0x28, BufferList items/count +0x14/+0x20, direct table
// +0x4C, page table +0x44C, first page char +0x45C, the GDI state global
// 0x0134AEAC with its DC at +0x10, and Update_Current_Buffer 0x0093DFB0. The
// only caller, Rva00941400Font::Get_Char_Data 0x009412F0, reaches it on a
// cache miss. render2dsentence.cpp still defines Zero Hour's private
// Store_GDI_Char (present-unmatched); this view's public spelling, with the
// struct record the ledger's Get_Char_Data row uses, keeps the two apart.
#include <windows.h>
#include <string.h>

extern "C" __declspec(dllimport) DWORD WINAPI GetGlyphIndicesW(HDC, LPCWSTR, int, LPWORD, DWORD);

struct FontCharsClassCharDataStruct
{
	unsigned short Value;
	unsigned short Width;
	short Bearing;
	unsigned short unused;
	unsigned short *Buffer;
};

class FontCharsClassGdiState
{
public:
	int refs;
	HBITMAP oldBitmap, bitmap;
	unsigned char *bits;
	HDC dc;
};
extern FontCharsClassGdiState *g_fontCharsGdiState0134AEAC;

class FontGlyphDCSelection
{
	HDC dc;
	HGDIOBJ old;

public:
	FontGlyphDCSelection(HDC dc_, HFONT font) : dc(dc_), old(::SelectObject(dc_, font)) {}
	~FontGlyphDCSelection() { ::SelectObject(dc, old); }
};

class FontCharsBuffer
{
public:
	unsigned short *Buffer;
};

template <class T> class Rva0093F440Vector
{
public:
	int vptr;
	T *items;
	int capacity;
	bool valid, allocated;
	unsigned short padding;
	int activeCount;
	int growth;
	T &operator[](int i) { return items[i]; }
	int Count() const { return activeCount; }
};

class FontCharsClass
{
public:
	const FontCharsClassCharDataStruct *Store_GDI_Char(unsigned short ch);

private:
	void Update_Current_Buffer(int width);

	void *unused00, *unused04;
	FontCharsClass *alternate;
	int unused0c;
	Rva0093F440Vector<FontCharsBuffer *> BufferList;
	int CurrPixelOffset, CharHeight, ExtraHeight;
	int unknown34, overlap, unknown3c;
	int Scale;
	int unknown44;
	HFONT font;
	const FontCharsClassCharDataStruct *directChars[256];
	const FontCharsClassCharDataStruct **pages;
	char glyphs[12];
	unsigned short first, last;
};

typedef char Rva0093F440Layout[(sizeof(FontCharsClass) == 0x460) ? 1 : -1];

const FontCharsClassCharDataStruct *FontCharsClass::Store_GDI_Char(unsigned short ch)
{
	FontGlyphDCSelection selection(g_fontCharsGdiState0134AEAC->dc, font);
	unsigned int glyphIndex = 0xffff;
	::GetGlyphIndicesW(g_fontCharsGdiState0134AEAC->dc, &ch, 1, reinterpret_cast<WORD *>(&glyphIndex), 1);
	if (static_cast<unsigned short>(glyphIndex) == 0xffff)
	{
		if (ch < 256)
			directChars[ch] = reinterpret_cast<const FontCharsClassCharDataStruct *>(-1);
		else
			pages[ch - first] = reinterpret_cast<const FontCharsClassCharDataStruct *>(-1);
		return reinterpret_cast<const FontCharsClassCharDataStruct *>(-1);
	}

	int area = Scale * Scale;
	int halfArea = area >> 1;
	int tileX = 64 / Scale;
	int tileY = 64 / Scale;
	SIZE tile_size = {Scale * tileX, Scale * tileY};
	SIZE charSize;
	if (!::GetTextExtentPoint32W(g_fontCharsGdiState0134AEAC->dc, &ch, 1, &charSize))
		charSize.cx = charSize.cy = 1;
	SIZE cell_size;
	cell_size.cx = (Scale + charSize.cx - 1) / Scale + overlap;
	cell_size.cy = (Scale + charSize.cy - 1) / Scale;

	Update_Current_Buffer(cell_size.cx);
	unsigned short *pixels = BufferList[BufferList.Count() - 1]->Buffer + CurrPixelOffset;
	int top = ExtraHeight / 2;
	int bottom = ExtraHeight - top;
	unsigned short *start = pixels;
	pixels += top * cell_size.cx;
	memset(start, 0, top * cell_size.cx * 2);
	memset(pixels + cell_size.cx * cell_size.cy, 0, bottom * cell_size.cx * 2);
	SIZE tile_count;
	tile_count.cx = (cell_size.cx + tileX - 1) / tileX;
	tile_count.cy = (cell_size.cy + tileY - 1) / tileY;

	POINT tile_pos;
	for (tile_pos.y = 0; tile_pos.y < tile_count.cy; ++tile_pos.y)
	{
		for (tile_pos.x = 0; tile_pos.x < tile_count.cx; ++tile_pos.x)
		{
			RECT rect = {0, 0, tile_size.cx, tile_size.cy};
			POINT tile_origin;
			tile_origin.x = tile_size.cx * tile_pos.x;
			tile_origin.y = tile_size.cy * tile_pos.y;
			::ExtTextOutW(g_fontCharsGdiState0134AEAC->dc, -tile_origin.x, -tile_origin.y, 2, &rect, &ch, 1, 0);
			POINT cell_start;
			cell_start.x = tileX * tile_pos.x;
			cell_start.y = tileY * tile_pos.y;
			POINT cell_end;
			cell_end.x = cell_start.x + tileX;
			if (cell_end.x > cell_size.cx)
				cell_end.x = cell_size.cx;
			cell_end.y = cell_start.y + tileY;
			if (cell_end.y > cell_size.cy)
				cell_end.y = cell_size.cy;
			for (int y = cell_start.y; y < cell_end.y; ++y)
			{
				unsigned short *dest = pixels + y * cell_size.cx + cell_start.x;
				int y0 = Scale * y;
				int y1 = y0 + Scale;
				if (y1 > charSize.cy)
					y1 = charSize.cy;
				for (int x = cell_start.x; x < cell_end.x; ++x)
				{
					unsigned int intensity = 0;
					int x0 = Scale * x;
					int x1 = x0 + Scale;
					if (x1 > charSize.cx)
						x1 = charSize.cx;
					for (int row = y0; row < y1; ++row)
					{
						int index = (row - tile_origin.y) * 192 + (x0 - tile_origin.x) * 3;
						for (int col = x0; col < x1; ++col)
						{
							unsigned char sample = g_fontCharsGdiState0134AEAC->bits[index];
							index += 3;
							intensity += (sample >> 4) & 15;
						}
					}
					unsigned short alpha = (intensity + halfArea) / area;
					*dest++ = 0xfff | (alpha << 12);
				}
			}
		}
	}

	FontCharsClassCharDataStruct *data = new FontCharsClassCharDataStruct;
	data->Value = ch;
	data->Width = cell_size.cx;
	data->Bearing = 0;
	data->Buffer = BufferList[BufferList.Count() - 1]->Buffer + CurrPixelOffset;
	if (ch < 256)
		directChars[ch] = data;
	else
		pages[ch - first] = data;
	CurrPixelOffset += CharHeight * (cell_size.cx + overlap);
	return data;
}
