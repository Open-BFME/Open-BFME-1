// ?d_001f6db0@@YAXXZ
// partial score=0.95 date=2026-09-12
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
//
// Retail 0x001F6DB0, 165 bytes.  FieldParse table at RVA 0x00CA2D28 names this
// the FireName parser (offset 0) for Rva001F6EA0::buildFieldParse.

#include <vector>

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class Open2Elem063700;

private:
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	StringInlineData<T> *m_data;
};

class Open2Elem063700 : private StringBase<char>
{
public:
	Open2Elem063700(const char *text) : StringBase<char>(text) {}
	Open2Elem063700(const Open2Elem063700 &other) : StringBase<char>(other) {}
	~Open2Elem063700() {}
};

class INI
{
public:
	const char *getNextToken(const char *separators);
};

class Rva001F6EA0
{
public:
	static void parseFireName(INI *ini, void *instance, void *store, const void *userData);

private:
	unsigned char m_pad[0x18];
	std::vector<Open2Elem063700> m_fireNames;
};

// ?parseFireName@Rva001F6EA0@@SAXPAVINI@@PAX1PBX@Z
void Rva001F6EA0::parseFireName(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	const char *token = ini->getNextToken(0);
	if (token)
	{
		Open2Elem063700 name(token);
		((Rva001F6EA0 *)instance)->m_fireNames.push_back(name);
	}
}
