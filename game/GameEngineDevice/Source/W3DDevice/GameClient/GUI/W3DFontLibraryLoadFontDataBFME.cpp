// cl: /DNDEBUG /MD /EHsc
//
// BFME's font loader differs from the surviving Zero Hour source in two
// related ways: point sizes are floats, and the cached FontChars key carries
// one additional integer setting.  The same-TU cache helper below retains the
// private EBX/EDI argument convention emitted by the retail optimizer.

class FontCharsClass
{
public:
	FontCharsClass();
	bool Is_Font(const char *name, float point_size, bool is_bold, int extra_setting);
	void Initialize_GDI_Font(const char *name, float point_size, bool is_bold,
		int extra_setting);
	void Add_Ref() { ++m_ref_count; }

	void *m_vtable;
	int m_ref_count;
	FontCharsClass *AlternateUnicodeFont;
	unsigned char m_pad0c[0x20];
	int m_char_height;
	unsigned char m_pad30[0x464 - 0x30];
};

// Layout of the SimpleDynVecClass<FontCharsClass *> cache owned by the BFME
// font library.  Add is kept inline because that is how the 0x0078CC10 body
// grows and appends to the cache.
class BFMEFontCharsList
{
public:
	virtual void unused();
	virtual bool Resize(int new_size);
	FontCharsClass *&operator[](int index) { return m_vector[index]; }

	bool Add(FontCharsClass *const &font)
	{
		if (m_active_count >= m_vector_max)
		{
			int quarter = m_vector_max / 4;
			int new_size = m_vector_max + quarter;
			int plus_four = m_vector_max + 4;
			if (new_size <= plus_four)
				new_size = plus_four;
			if (new_size <= 0)
				new_size = 0;
			if (!Resize(new_size))
				return false;
		}

		(*this)[m_active_count++] = font;
		return true;
	}

	FontCharsClass **m_vector;
	int m_vector_max;
	int m_active_count;
};

extern BFMEFontCharsList g_BFMEFontCharsList;

// Source-authentic semantics from WW3DAssetManager::Get_FontChars, specialized
// by BFME into this same-TU helper.  Its ledger name remains address-derived
// because the original private spelling is not present in the retail image.
static __declspec(noinline) FontCharsClass *BFME_Get_Font_Chars(
	const char *name, float point_size, bool is_bold, int extra_setting)
{
	for (int i = 0; i < g_BFMEFontCharsList.m_active_count; ++i)
	{
		if (g_BFMEFontCharsList[i]->Is_Font(name, point_size, is_bold, extra_setting))
		{
			g_BFMEFontCharsList[i]->Add_Ref();
			return g_BFMEFontCharsList[i];
		}
	}

	FontCharsClass *font = new FontCharsClass;
	font->Initialize_GDI_Font(name, point_size, is_bold, extra_setting);
	font->Add_Ref();
	g_BFMEFontCharsList.Add(font);
	return font;
}

class GameFont
{
public:
	unsigned char m_pad00[8];
	char *m_name_data;
	float pointSize;
	int height;
	FontCharsClass *fontData;
	bool bold;
	unsigned char m_pad19[3];
	int m_extra_setting;
};

struct BFMEGlobalLanguage
{
	unsigned char m_pad00[0x14];
	char *m_unicode_name_data;
};

extern BFMEGlobalLanguage *g_bfmeGlobalWR;
extern const char g_bfmeEmptyAscii[];

static __forceinline const char *BFME_String_Data(char *data)
{
	return data ? data + 8 : g_bfmeEmptyAscii;
}

class W3DFontLibrary
{
protected:
	virtual bool loadFontData(GameFont *font);
};

// ?loadFontData@W3DFontLibrary@@MAE_NPAVGameFont@@@Z
bool W3DFontLibrary::loadFontData(GameFont *font)
{
	if (font == 0)
		return false;

	FontCharsClass *font_chars = 0;
	if ((unsigned int)font->pointSize <= 100)
	{
		font_chars = BFME_Get_Font_Chars(BFME_String_Data(font->m_name_data),
			font->pointSize, font->bold ? true : false, font->m_extra_setting);
	}

	if (font_chars == 0)
		return false;

	font->fontData = font_chars;
	font->height = font_chars->m_char_height;

	FontCharsClass *unicode_font;
	if (g_bfmeGlobalWR)
	{
		unicode_font = BFME_Get_Font_Chars(
			BFME_String_Data(g_bfmeGlobalWR->m_unicode_name_data),
			font->pointSize, font->bold ? true : false, font->m_extra_setting);
	}
	else
	{
		unicode_font = BFME_Get_Font_Chars("Arial Unicode MS", font->pointSize,
			font->bold ? true : false, font->m_extra_setting);
	}

	if (unicode_font)
		font_chars->AlternateUnicodeFont = unicode_font;

	return true;
}
