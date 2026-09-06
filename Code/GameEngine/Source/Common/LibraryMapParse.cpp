// cl: /DNDEBUG /MD /EHsc
// stlport

#include <vector>

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class Open2Elem063700;

public:
	void set(const StringBase<T> &source);

private:
	StringBase(const StringBase<T> &source);
	void releaseBuffer();
	void *m_data;
};

class AsciiString
{
public:
	AsciiString() : m_text(0) {}

	AsciiString(const AsciiString &source)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&source);
	}

	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

	AsciiString &operator=(const AsciiString &source)
	{
		((StringBase<char> *)this)->set(*(const StringBase<char> *)&source);
		return *this;
	}

private:
	void *m_text;
};

class INI
{
public:
	AsciiString getNextQuotedAsciiString();
};

class Open2Elem063700
{
public:
	Open2Elem063700(const Open2Elem063700 &source)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&source);
	}

	~Open2Elem063700()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

private:
	void *m_text;
};

class LibraryMap
{
public:
	static void parse(INI *ini, void *instance, void *store,
		const void *userData);

private:
	AsciiString m_name;
	std::vector<Open2Elem063700> m_libraryMaps;
};

void LibraryMap::parse(INI *ini, void *instance, void *, const void *)
{
	((LibraryMap *)instance)->m_libraryMaps.push_back(
		reinterpret_cast<const Open2Elem063700 &>(
			ini->getNextQuotedAsciiString()));
}
