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
	bool missing;
	int i;
	register int count = third;
	if (count != 0)
	{
		HGDIOBJ font = m_font;
		register HDC dc = TheFontCharsGDIState->dc;
		missing = false;
		// Two handle slots preserve the retail 8-byte frame; only slot1 is used.
		HGDIOBJ old_font[2];
		old_font[1] = SelectObject(dc, font);
		GetGlyphIndicesW(TheFontCharsGDIState->dc, first, count, second, 1);

		i = 0;
		for (; i < count; ++i)
		{
			if (second[i] == 0xffff &&
				first[i] != 0x000a && first[i] != 0x000d && first[i] != 0x0095)
			{
				missing = true;
				break;
			}
		}

		SelectObject(dc, old_font[1]);
		return missing == false;
	}

	return false;
}
