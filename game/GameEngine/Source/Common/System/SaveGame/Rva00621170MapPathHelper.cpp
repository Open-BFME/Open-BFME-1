// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_STLP_NODE_ALLOC /D_STLP_USE_STATIC_LIB /Iinputs/vendor/stlport /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/stringinline /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
//
// Retail 0x00621170 is the map-path formatter's compact token loop.  Its
// public owner/spelling is not recovered, so this source keeps the proven
// free-function ABI address-derived.  The matched caller's object flow names
// the two GameState routes: the ordinary real-to-portable conversion at
// 0x0010F280 and the distinct hidden-sret/const-reference route at 0x0010F820.

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
	const T *find(T c) const
	{
		const T *start = m_data ? &m_data->data[0] : (const T *)"";
		const T *end = start + (m_data ? m_data->length : 0);
		for (const T *p = start; p != end; ++p)
		{
			if (*p == c)
				return p;
		}
		return 0;
	}
	void concat(const T *text, int length);
	void concat(const StringBase<T> &source);
	void set(const StringBase<T> &source);

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
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
	const char *find(char c) const
	{
		const StringBase<char>::Header *data = ((const StringBase<char> *)this)->m_data;
		const char *start = data ? &data->data[0] : "";
		const char *end = start + (data ? data->length : 0);
		for (const char *p = start; p != end; ++p)
		{
			if (*p == c)
				return p;
		}
		return 0;
	}

	// Retail inlines this character append as pointer-plus-length-one into
	// StringBase::concat(const char *,int), not as the single-character body.
	void concat(char source)
	{
		StringBase<char>::concat(&source, 1);
	}

	// Retail likewise forwards the source data and header length to the same
	// two-argument concat body; it does not call the object overload here.
	void concat(const AsciiString &source)
	{
		StringBase<char>::concat(source.str(), source.getLength());
	}
};

class GameState
{
public:
	AsciiString realMapPathToPortableMapPath(const AsciiString &in) const;
	AsciiString rva0010f820MapPathCode(const AsciiString &in) const;
};

extern GameState *TheGameState;

AsciiString _Rva00621170MapPathHelperConcat(const AsciiString &input, Bool option)
{
	AsciiString mapName = TheGameState->realMapPathToPortableMapPath(input);
	if (option)
		mapName = TheGameState->rva0010f820MapPathCode(mapName);

	AsciiString newMapName;
	if (mapName.getLength() > 0)
	{
		AsciiString token;
		mapName.nextToken(&token, "\\/");
		while (mapName.find('\\') != 0)
		{
			if (newMapName.getLength() > 0)
				newMapName.concat('/');
			newMapName.concat(token);
			mapName.nextToken(&token, "\\/");
		}
	}
	return newMapName;
}
