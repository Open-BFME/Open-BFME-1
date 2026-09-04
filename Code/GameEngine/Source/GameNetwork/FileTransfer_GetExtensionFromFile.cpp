// cl: /GX
//
// Open-BFME: GetExtensionFromFile, retail 0x0066D480 (152B). ZH FileTransfer.cpp
// sits this helper between GetFileFromPath (0x0066D3C0, also 152B, last '\\')
// and GetBaseFileFromFile (0x0066D540, last '.' then prefix). Same inlined
// reverseFind walk; found path returns s+1, miss returns the original name.

class AsciiString;
AsciiString GetExtensionFromFile(AsciiString fname);

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend AsciiString GetExtensionFromFile(AsciiString fname);

	StringBase(const StringBase<T> &other);
	StringBase(const T *str);
	~StringBase();

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}

	friend AsciiString GetExtensionFromFile(AsciiString fname);
};

// ?GetExtensionFromFile@@YA?AVAsciiString@@V1@@Z
AsciiString GetExtensionFromFile(AsciiString fname)
{
	StringBase<char>::Header *data = fname.m_data;
	const char *start;
	unsigned int len;
	if (data)
	{
		start = &data->data[0];
		len = data->length;
	}
	else
	{
		start = (const char *)0x0107388B;
		len = 0;
	}

	const char *p = start + len;
	while (p != start)
	{
		char ch = p[-1];
		--p;
		if (ch == '.')
			return p + 1;
	}
	return fname;
}
