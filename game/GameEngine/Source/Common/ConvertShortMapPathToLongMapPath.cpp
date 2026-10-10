// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include <string.h>

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

template<> inline const char *StringBase<char>::find(char c) const
{
    const char *start = m_data ? &m_data->data[0] : (const char *)"";
    const char *end = start + (m_data ? m_data->length : 0);
    for (const char *p = start; p != end; ++p) {
        if (*p == c) return p;
    }
    return 0;
}

template<> inline void StringBase<char>::concat(const StringBase<char> &str)
{
    const int len = str.m_data ? str.m_data->length : 0;
    const char *data = str.m_data ? &str.m_data->data[0] : "";
    concat(data, len);
}

template<> inline void StringBase<char>::concat(char c) { concat(&c, 1); }
template<> inline void StringBase<char>::set(const char *str) { set(str, str ? strlen(str) : 0); }

static __forceinline bool shortMapPathNextToken(
	AsciiString *path, AsciiString *token, const char *delimiters)
{
	return reinterpret_cast<StringBase<char> *>(path)->nextToken(
		reinterpret_cast<StringBase<char> *>(token), delimiters);
}

__declspec(noinline) static void ConvertShortMapPathToLongMapPath(AsciiString &mapName)
{
	AsciiString path = mapName;
	AsciiString token;
	AsciiString actualpath;

	if (path.StringBase<char>::find('\\') == 0 && path.StringBase<char>::find('/') == 0)
		return;

	shortMapPathNextToken(&path, &token, "\\/");
	for (;;)
	{
		if (token.StringBase<char>::endsWithNoCase(".map", 4))
			goto done;
		if (token.StringBase<char>::getLength() <= 0)
			goto done;
		actualpath.StringBase<char>::concat(token);
		actualpath.StringBase<char>::concat('\\');
		if (shortMapPathNextToken(&path, &token, "\\/"))
			continue;
		goto done;
	}

done:
	token.StringBase<char>::endsWithNoCase(".map", 4);

	token.StringBase<char>::removeLastChar();
	token.StringBase<char>::removeLastChar();
	token.StringBase<char>::removeLastChar();
	token.StringBase<char>::removeLastChar();
	actualpath.StringBase<char>::concat(token);
	actualpath.StringBase<char>::concat('\\');
	actualpath.StringBase<char>::concat(token);
	actualpath.StringBase<char>::concat(".map", 4);
    mapName.StringBase<char>::set(actualpath);
}

void ConvertShortMapPathToLongMapPathAnchor(AsciiString &mapName)
{
    ConvertShortMapPathToLongMapPath(mapName);
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData;

struct Rva006C9270GlobalData
{
	unsigned char m_bfmePad000[8];
	AsciiString m_bfmeMapName008;
	unsigned char m_bfmePad00C[0xB80 - 0xC];
	AsciiString m_bfmeMapNameB80;
	unsigned char m_bfmePadB84[4];
	bool m_bfmeFlagB88;
};

// Retail 0x012ED5C8 is GlobalData *TheWritableGlobalData
// (game/GameEngine/Source/Common/GlobalData.cpp). This TU keeps its own view of
// the fields it reads and casts at the use.
extern GlobalData *TheWritableGlobalData;

static __forceinline Rva006C9270GlobalData *localWritableGlobalData()
{
	return (Rva006C9270GlobalData *)TheWritableGlobalData;
}

int Rva00062CA0ParseMapName(char **arguments, int count)
{
	localWritableGlobalData()->m_bfmeFlagB88 = 1;

	if (count > 1)
	{
		localWritableGlobalData()->m_bfmeMapNameB80 = arguments[1];
		ConvertShortMapPathToLongMapPath(localWritableGlobalData()->m_bfmeMapNameB80);
	}

	return 2;
}

int Rva00062C50ParseMapName(char **arguments, int count)
{
	Rva006C9270GlobalData *data = localWritableGlobalData();

	if (data != 0 && count > 1)
	{
		data->m_bfmeMapNameB80 = arguments[1];
		ConvertShortMapPathToLongMapPath(localWritableGlobalData()->m_bfmeMapNameB80);
	}

	return 2;
}

// Retail 0x00062D00, 79 bytes: the third CommandLine map-name parser. It stores
// the argument into GlobalData+0x8 and hands that string to the file-static
// helper, which takes it in EDI (same TU convention as the two parsers above).
int Rva00062D00ParseMapName(char **arguments, int count)
{
	if (localWritableGlobalData() != 0 && count >= 2)
	{
		localWritableGlobalData()->m_bfmeMapName008.StringBase<char>::set(arguments[1]);
		ConvertShortMapPathToLongMapPath(localWritableGlobalData()->m_bfmeMapName008);
	}

	return 1;
}
