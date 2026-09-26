// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline /Igame/Libraries/Source/WWVegas/WWLib
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

#include "string_base.h"

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
Bool __cdecl parseFont(char *, WinInstanceData *instanceData, char *buffer, void *)
{
	char *fieldToken, *quoteCursor;
	char *fieldDelimiters = " ,\n\r\t";
	char *quotedNameDelimiters = ":,\n\r\t\"";
	char fontName[256];
	Int pointSize;
	Int boldFlag;

	// "NAME"
	fieldToken = strtok(buffer, fieldDelimiters);
	quoteCursor = buffer;
	while (*quoteCursor != '"')
		quoteCursor++;
	quoteCursor++;
	fieldToken = strtok(quoteCursor, quotedNameDelimiters);
	strcpy(fontName, fieldToken);

	// "SIZE"
	fieldToken = strtok(NULL, fieldDelimiters);
	fieldToken = strtok(NULL, fieldDelimiters);
	scanInt(fieldToken, pointSize);

	// "BOLD"
	fieldToken = strtok(NULL, fieldDelimiters);
	fieldToken = strtok(NULL, fieldDelimiters);
	scanInt(fieldToken, boldFlag);

	if (TheFontLibrary)
	{
		GameFont *resolvedFont;
		resolvedFont = TheFontLibrary->getFont(AsciiString(fontName), pointSize, boldFlag);
		if (resolvedFont)
			instanceData->m_font = resolvedFont;
	}

	return true;
}
