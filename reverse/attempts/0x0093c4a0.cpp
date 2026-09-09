// ?Check@Rva0093C4A0Target@@QAE_NPBGPAGH@Z
// partial score=0.9 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc
#include <windows.h>

extern "C" __declspec(dllimport) DWORD WINAPI GetGlyphIndicesW(
	HDC dc, LPCWSTR text, int count, LPWORD glyphs, DWORD flags);

struct FontCharsGDIState
{
	int refs;
	void *old_bitmap;
	void *bitmap;
	int unused;
	void *dc;
};

#define TheFontCharsGDIState (*(FontCharsGDIState **)0x0134AEAC)

class Rva0093C4A0Target
{
public:
	bool Check(const unsigned short *first, unsigned short *second, int third);

private:
	char m_gap00[0x48];
	HFONT m_font;
};

bool Rva0093C4A0Target::Check(
	const unsigned short *first, unsigned short *second, int third)
{
	bool result[8];
	int i;
	register int count = third;
	if (count != 0)
	{
		HGDIOBJ font = m_font;
		register HDC dc = TheFontCharsGDIState->dc;
		result[0x14] = false;
		HGDIOBJ old_font = SelectObject(dc, font);
		GetGlyphIndicesW(TheFontCharsGDIState->dc, first, count, second, 1);

		i = 0;
		for (; i < count; ++i)
		{
			if (second[i] == 0xffff &&
				first[i] != 0x000a && first[i] != 0x000d && first[i] != 0x0095)
			{
				result[0x14] = true;
				break;
			}
		}

		SelectObject(dc, old_font);
		return result[0x14] == false;
	}

	return false;
}
