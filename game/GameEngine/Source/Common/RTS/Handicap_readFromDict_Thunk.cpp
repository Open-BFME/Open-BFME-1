// cl: /DNDEBUG /MD /EHsc

extern "C" unsigned int __cdecl strlen(const char *text);
#pragma intrinsic(strlen)

typedef float Real;
typedef bool Bool;

enum NameKeyType {};

template <typename T> class StringBase;
class AsciiString;

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;

public:
	void set(const T *text, int length);
	void concat(const T *text, int length);

private:
	void releaseBuffer();
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}

	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

	void clear()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

	void set(const char *text)
	{
		((StringBase<char> *)this)->set(text, text ? (int)strlen(text) : 0);
	}

	void concat(const char *text)
	{
		((StringBase<char> *)this)->concat(text, text ? (int)strlen(text) : 0);
	}

	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : (const char *)0x0107388B;
	}
};

class Dict
{
public:
	Real getReal(NameKeyType key, Bool *exists) const;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Handicap
{
public:
	enum HandicapType
	{
		BUILDCOST,
		BUILDTIME,
		HANDICAP_TYPE_COUNT
	};

	void readFromDict(const Dict *d);

private:
	Real m_handicaps[2][2];
};

// ?readFromDict@Handicap@@QAEXPBVDict@@@Z
void Handicap::readFromDict(const Dict *d)
{
	const char *htNames[HANDICAP_TYPE_COUNT] =
	{
		"BUILDCOST",
		"BUILDTIME",
	};

	const char *ttNames[2] =
	{
		"GENERIC",
		"BUILDINGS",
	};

	AsciiString c;
	for (int i = 0; i < HANDICAP_TYPE_COUNT; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			c.clear();
			c.set("HANDICAP_");
			c.concat(htNames[i]);
			c.concat("_");
			c.concat(ttNames[j]);
			NameKeyType k = TheNameKeyGenerator->nameToKey(c.str());
			Bool exists;
			Real r = d->getReal(k, &exists);
			if (exists)
				m_handicaps[i][j] = r;
		}
	}
}
