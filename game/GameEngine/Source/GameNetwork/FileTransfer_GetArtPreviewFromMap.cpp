// cl: /GX

class AsciiString;
AsciiString GetFileFromPath(AsciiString path);
AsciiString GetBaseFileFromFile(AsciiString fname);
AsciiString GetBasePathFromPath(AsciiString path);
AsciiString GetArtPreviewFromMap(AsciiString path);

template <typename T>
class StringBase
{
	friend class AsciiString;

	StringBase() : m_data(0) {}
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
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}
	const char *str() const
	{
		return m_data ? &m_data->data[0] : (const char *)0x0107388B;
	}
	void format(AsciiString format, ...);
};

AsciiString GetArtPreviewFromMap(AsciiString path)
{
	AsciiString fname = GetBaseFileFromFile(GetFileFromPath(path));
	AsciiString base = GetBasePathFromPath(path);
	AsciiString out;
	out.format("%s\\%s_art.tga", base.str(), fname.str());
	return out;
}
