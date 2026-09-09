// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Open-BFME: readable reconstruction of the retail window-definition FONT
// callback.  The callback is registered by gameWindowFieldList in the
// reference GameWindowManagerScript.cpp and uses the BFME font-library ABI.

#include <string.h>

typedef int Int;
typedef float Real;
typedef bool Bool;

#define NULL 0

extern "C" __declspec(dllimport) int __cdecl sscanf(const char *, const char *, ...);
extern "C" __declspec(dllimport) char *__cdecl strtok(char *, const char *);

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase(const T *text);
	void releaseBuffer();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() { releaseBuffer(); }
	operator AsciiString *(void) { return this; }
};

class GameFont;

class FontLibrary
{
public:
	GameFont *getFont(AsciiString *name, Real pointSize, Bool bold);
};

extern FontLibrary *TheFontLibrary;

class WinInstanceData
{
public:
	unsigned char m_unreconstructed_00[0x184];
	GameFont *m_font;
};

static Int scanInt(const char *source, Int &val)
{
	Int ret = sscanf(source, "%d", &val);
	return ret;
}

// ?parseFont@@YA_NPADPAVWinInstanceData@@0PAX@Z
Bool __cdecl parseFont(char *, WinInstanceData *instData, char *buffer, void *)
{
	char *c, *ptr;
	char *seps = " ,\n\r\t";
	char *stringSeps = ":,\n\r\t\"";
	char fontName[256];
	Int fontSize;
	Int fontBold;

	// "NAME"
	c = strtok(buffer, seps);
	ptr = buffer;
	while (*ptr != '"')
		ptr++;
	ptr++;
	c = strtok(ptr, stringSeps);
	strcpy(fontName, c);

	// "SIZE"
	c = strtok(NULL, seps);
	c = strtok(NULL, seps);
	scanInt(c, fontSize);

	// "BOLD"
	c = strtok(NULL, seps);
	c = strtok(NULL, seps);
	scanInt(c, fontBold);

	if (TheFontLibrary)
	{
		GameFont *font;
		font = TheFontLibrary->getFont(AsciiString(fontName), fontSize, fontBold);
		if (font)
			instData->m_font = font;
	}

	return true;
}
