// ?d_0077bdf0@@YAXXZ
// partial score=0.65 date=2026-09-20
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport

typedef int Int;

inline void *operator new(unsigned int, void *place)
{
	return place;
}

class AsciiString;

template <class Type>
class StringBase
{
	friend class AsciiString;

private:
	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		Type data[1];
	};

	StringBase() : m_data(0) {}
	StringBase(const StringBase<Type> &source);
	void releaseBuffer();
	Header *m_data;

public:
	void set(const Type *text, int length);
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &source) : StringBase<char>(source) {}
	~AsciiString() { releaseBuffer(); }
};

class INI
{
public:
	const char *getNextTokenOrNull(const char *separators = 0);
	static Int scanInt(const char *token);

	char m_body[0x414];
	const char *m_separators;
};

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

template <class Type>
void __forceinline BfmeElementConstruct(Type *destination, const Type &value)
{
	new (destination) Type(value);
}

template <class Type, class Allocator = allocator<Type> >
class vector
{
public:
	void push_back(const Type *value);

protected:
	void _M_insert_overflow(Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd);

	Type *m_start;
	Type *m_finish;
	Type *m_end_of_storage;
};

template <class Type, class Allocator>
void vector<Type, Allocator>::push_back(const Type *value)
{
	Type *destination = m_finish;
	if (destination != m_end_of_storage)
	{
		if (destination != 0)
			BfmeElementConstruct(destination, *value);
		++m_finish;
	}
	else
	{
		_M_insert_overflow(destination, *value,
			reinterpret_cast<const __false_type &>(value), 1, true);
	}
}
}

struct Rva007701C0Element
{
	AsciiString m_name;
	_STL::vector<AsciiString> m_strings;
	Int m_value;
};

class Rva0077BC20Owner
{
public:
	Rva007701C0Element *findOrCreateRecord(const AsciiString &name);
};

class W3DModelDrawModuleData
{
public:
	static void parseRandomTexture(INI *ini, void *instance, void *store,
		const void *userData);
};

// ?parseRandomTexture@W3DModelDrawModuleData@@SAXPAVINI@@PAX1PBX@Z
void W3DModelDrawModuleData::parseRandomTexture(
	INI *ini, void *volatile instance, void *, const void *)
{
	if (instance == 0)
		return;

	{
		AsciiString groupName;
		AsciiString textureName;
		const char *token = ini->getNextTokenOrNull();
		if (token != 0)
		{
			const char *end = token;
			const char *lengthBase = end + 1;
			while (*end++ != 0)
			{
			}
			((StringBase<char> *)&textureName)->set(token, end - lengthBase);
		}
		else
		{
			((StringBase<char> *)&textureName)->set("", 0);
		}

		token = ini->getNextTokenOrNull();
		Int value = token != 0 ? INI::scanInt(token) : 0;

		token = ini->getNextTokenOrNull();
		if (token != 0)
		{
			const char *end = token;
			const char *lengthBase = end + 1;
			while (*end++ != 0)
			{
			}
			((StringBase<char> *)&groupName)->set(token, end - lengthBase);
		}
		else
		{
			((StringBase<char> *)&groupName)->set(token, 0);
		}

		Rva007701C0Element *record =
			((Rva0077BC20Owner *)instance)->findOrCreateRecord(groupName);
		record->m_strings.push_back(&textureName);
		record->m_value = value;
	}
}
