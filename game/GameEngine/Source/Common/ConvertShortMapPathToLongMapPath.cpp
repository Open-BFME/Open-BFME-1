// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include <string.h>

class AsciiString;

template <typename T>
class StringBase
{
    friend class AsciiString;

private:
    struct Header
    {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };

    StringBase() : m_data(0) {}
    StringBase(const StringBase<T> &other);
    ~StringBase();

public:
    int getLength() const
    {
        if (m_data != 0)
            return static_cast<int>(m_data->length);
        return 0;
    }
    const T *str() const;
    bool endsWithNoCase(const T *text, int length) const;
    void concat(const T *text, int length);
    bool nextToken(StringBase<T> *token, const T *delimiters);
    void removeLastChar();
    void set(const StringBase<T> &other);
    void set(const T *text, int length);

private:
    Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	const char *str() const
	{
		return m_data ? m_data->data : "";
	}

	int getLength() const
	{
		return StringBase<char>::getLength();
	}

	const char *find(char value) const
	{
		const char *first = str();
		const char *last = first + getLength();
		for (const char *current = first; current != last; ++current)
		{
			if (*current == value)
				return current;
		}
		return 0;
	}

	bool nextToken(AsciiString *token, const char *delimiters)
	{
		return StringBase<char>::nextToken(
			reinterpret_cast<StringBase<char> *>(token), delimiters);
	}

	bool endsWithNoCase(const char *text, int length) const
	{
		return StringBase<char>::endsWithNoCase(text, length);
	}

	void concat(const char *text, int length)
	{
		StringBase<char>::concat(text, length);
	}

	void concat(const AsciiString &other)
	{
		concat(other.str(), other.getLength());
	}

	void concat(char value)
	{
		concat(&value, 1);
	}

	void removeLastChar()
	{
		StringBase<char>::removeLastChar();
	}

	void set(const AsciiString &other)
	{
		StringBase<char>::set(reinterpret_cast<const StringBase<char> &>(other));
	}

	void set(const char *text)
	{
		StringBase<char>::set(text, text ? strlen(text) : 0);
	}

	AsciiString &operator=(const char *text);
};

__declspec(noinline) static void ConvertShortMapPathToLongMapPath(AsciiString &mapName)
{
	AsciiString path = mapName;
	AsciiString token;
	AsciiString actualpath;

	if (path.find('\\') == 0 && path.find('/') == 0)
		return;

	path.nextToken(&token, "\\/");
	for (;;)
	{
		if (token.endsWithNoCase(".map", 4))
			goto done;
		if (token.getLength() <= 0)
			goto done;
		actualpath.concat(token);
		actualpath.concat('\\');
		if (path.nextToken(&token, "\\/"))
			continue;
		goto done;
	}

done:
	token.endsWithNoCase(".map", 4);

	token.removeLastChar();
	token.removeLastChar();
	token.removeLastChar();
	token.removeLastChar();
	actualpath.concat(token);
	actualpath.concat('\\');
	actualpath.concat(token);
	actualpath.concat(".map", 4);
    mapName.set(actualpath);
}

void ConvertShortMapPathToLongMapPathAnchor(AsciiString &mapName)
{
    ConvertShortMapPathToLongMapPath(mapName);
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
struct Rva006C9270GlobalData
{
	unsigned char m_bfmePad000[8];
	AsciiString m_bfmeMapName008;
	unsigned char m_bfmePad00C[0xB80 - 0xC];
	AsciiString m_bfmeMapNameB80;
	unsigned char m_bfmePadB84[4];
	bool m_bfmeFlagB88;
};

extern Rva006C9270GlobalData *TheWritableGlobalData;

int Rva00062CA0ParseMapName(char **arguments, int count)
{
	TheWritableGlobalData->m_bfmeFlagB88 = 1;

	if (count > 1)
	{
		TheWritableGlobalData->m_bfmeMapNameB80 = arguments[1];
		ConvertShortMapPathToLongMapPath(TheWritableGlobalData->m_bfmeMapNameB80);
	}

	return 2;
}

int Rva00062C50ParseMapName(char **arguments, int count)
{
	Rva006C9270GlobalData *data = TheWritableGlobalData;

	if (data != 0 && count > 1)
	{
		data->m_bfmeMapNameB80 = arguments[1];
		ConvertShortMapPathToLongMapPath(TheWritableGlobalData->m_bfmeMapNameB80);
	}

	return 2;
}

// Retail 0x00062D00, 79 bytes: the third CommandLine map-name parser. It stores
// the argument into GlobalData+0x8 and hands that string to the file-static
// helper, which takes it in EDI (same TU convention as the two parsers above).
int Rva00062D00ParseMapName(char **arguments, int count)
{
	if (TheWritableGlobalData != 0 && count >= 2)
	{
		TheWritableGlobalData->m_bfmeMapName008.set(arguments[1]);
		ConvertShortMapPathToLongMapPath(TheWritableGlobalData->m_bfmeMapName008);
	}

	return 1;
}
