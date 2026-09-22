// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// Open-BFME: address-derived PassengerBone INI callback, retail 0x002274A0.

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int Int;

extern "C" int __cdecl strcmp(const char *, const char *);
#pragma intrinsic(strcmp)

template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	void set(const StringBase<T> &source);

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &source);
	~StringBase();

	void *m_data;
};

class INI
{
public:
	const char *getNextToken(const char *seps);
	static void parseAsciiString(INI *, void *, void *, const void *);

	const char *getSepsColon() const
	{
		return *(const char **)((const char *)this + 0x41C);
	}
};

class INIException
{
public:
	char *mFailureMessage;
	Int m_argCount;
	INIException(Int, const char *, ...);
	INIException(const INIException &other);
	~INIException();
};

template <int NUMBITS>
class BitFlags
{
public:
	static void parseFromINI(INI *, void *, void *, const void *);

public:
	UnsignedInt m_bits[6];
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	AsciiString &operator=(const AsciiString &other)
	{
		StringBase<char>::set(other);
		return *this;
	}
};

struct Rva00225B80Element
{
	BitFlags<116> m_kindOf;
	AsciiString m_boneName;

	Rva00225B80Element() : m_kindOf(), m_boneName() {}
};

namespace _STL
{
	template <class T>
	class allocator;

	template <class T, class Alloc>
	class list
	{
	public:
		void push_back(const T &value);
	};
}

// ?rva002274a0ParsePassengerBone@@YAXPAVINI@@PAX1PBX@Z
void rva002274a0ParsePassengerBone(INI *ini, void *instance, void *, const void *)
{
	BitFlags<116> kindOf = {};
	AsciiString boneName;
	Rva00225B80Element entry;

	const char *token = ini->getNextToken(ini->getSepsColon());
	if (token == 0 || strcmp(token, "PassengerBone") != 0)
		throw INIException(3, "PassengerBone expected");

	INI::parseAsciiString(ini, instance, &boneName, 0);

	token = ini->getNextToken(ini->getSepsColon());
	if (token == 0 || strcmp(token, "KindOf") != 0)
		throw INIException(3, "KindOf expected");

	BitFlags<116>::parseFromINI(ini, instance, &kindOf, 0);
	entry.m_kindOf = kindOf;
	entry.m_boneName = boneName;
	((_STL::list<Rva00225B80Element, _STL::allocator<Rva00225B80Element> > *)
		((char *)instance + 0x11C))->push_back(entry);
}
