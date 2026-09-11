// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_STLP_NODE_ALLOC /D_STLP_USE_STATIC_LIB /Ivendor/stlport /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/shims/stringinline /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib

typedef bool Bool;

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

public:
	int getLength() const { return m_data ? m_data->length : 0; }
	const T *str() const { return m_data ? &m_data->data[0] : (const T *)""; }
	bool nextToken(StringBase<T> *out, const T *delimiters);
	void concat(const T *text, int length);
	void set(const StringBase<T> &source);

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();
	void releaseBuffer();

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	AsciiString &operator=(const AsciiString &other)
	{
		StringBase<char>::set(other);
		return *this;
	}

	int getLength() const { return StringBase<char>::getLength(); }
	const char *str() const { return StringBase<char>::str(); }
	bool nextToken(AsciiString *out, const char *delimiters)
	{
		return StringBase<char>::nextToken(out, delimiters);
	}
	void concat(const char *text, int length)
	{
		StringBase<char>::concat(text, length);
	}
	void concat(char source)
	{
		StringBase<char>::concat(&source, 1);
	}
	void concat(const AsciiString &source)
	{
		StringBase<char>::concat(source.str(), source.getLength());
	}
};

class GameState
{
public:
	AsciiString rva0010e580MapPathCode(const AsciiString &path) const;
	AsciiString portableMapPathToRealMapPath(const AsciiString &path) const;
};

class MapCache
{
public:
	AsciiString getMapExtension() const;
};

extern GameState *TheGameState;
extern MapCache *TheMapCache;

// ?_Rva00621350GameInfoMapPath@@YA?AVAsciiString@@ABV1@_N@Z
AsciiString _Rva00621350GameInfoMapPath(const AsciiString &input, Bool option)
{
	AsciiString path = input;
	if (option)
		path = TheGameState->rva0010e580MapPathCode(path);

	AsciiString actualpath;
	AsciiString token;
	path.nextToken(&token, "\\/");
	while (path.getLength() > 0)
	{
		actualpath.concat(token);
		actualpath.concat('\\');
		path.nextToken(&token, "\\/");
	}

	actualpath.concat(token);
	actualpath.concat('\\');
	actualpath.concat(token);
	actualpath.concat('.');
	actualpath.concat(TheMapCache->getMapExtension());
	actualpath = TheGameState->portableMapPathToRealMapPath(actualpath);
	return actualpath;
}
