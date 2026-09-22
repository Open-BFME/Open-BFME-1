// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#include <map>

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

	StringBase();
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();
	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	static AsciiString TheEmptyString;

	int compare(const AsciiString &other) const;
};

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left.compare(right) < 0;
	}
};
}

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
};

extern void j_00025306(void);
extern void j_00025266(void);
extern void j_00026f35(void);
extern void j_00047b27(void);
extern void j_00016680(void);

struct Rva00142DF0Value
{
	Rva00142DF0Value(const AsciiString &name, int extra)
	{
		typedef void (Rva00142DF0Value::*Call)(const AsciiString &, int);
		union { void *address; Call member; } call;
		call.address = (void *)j_00025306;
		(this->*call.member)(name, extra);
	}

	Rva00142DF0Value(const Rva00142DF0Value &right)
	{
		typedef void (Rva00142DF0Value::*Call)(const Rva00142DF0Value &);
		union { void *address; Call member; } call;
		call.address = (void *)j_00047b27;
		(this->*call.member)(right);
	}

	~Rva00142DF0Value()
	{
		typedef void (Rva00142DF0Value::*Call)();
		union { void *address; Call member; } call;
		call.address = (void *)j_00026f35;
		(this->*call.member)();
	}

	void setEventName(AsciiString name)
	{
		typedef void (Rva00142DF0Value::*Call)(AsciiString);
		union { void *address; Call member; } call;
		call.address = (void *)j_00025266;
		(this->*call.member)(name);
	}

	unsigned char m_storage[0x70];
};

typedef std::map<AsciiString, Rva00142DF0Value> PerUnitSoundMap;
typedef std::pair<AsciiString, Rva00142DF0Value> Rva0013F8B0Pair;
typedef Rva0013F8B0Pair (__cdecl *Rva0013F8B0Call)(
	const AsciiString &, const Rva00142DF0Value &);

// ?parseArbitrarySoundsIntoMap@@YAXPAVINI@@PAX1PBX@Z
void parseArbitrarySoundsIntoMap(INI *ini, void *instance, void *, const void *userData)
{
	PerUnitSoundMap *mapSounds = (PerUnitSoundMap *)instance;
	const char *name = (const char *)userData;
	const char *token = ini->getNextToken();
	Rva00142DF0Value a(AsciiString::TheEmptyString, 0);
	if (token)
	{
		typedef void (Rva00142DF0Value::*Call)(AsciiString);
		union { void *address; Call member; } setName;
		setName.address = (void *)j_00025266;
		(a.*setName.member)(token);
	}
	union { void *address; Rva0013F8B0Call function; } call;
	call.address = (void *)j_00016680;
	mapSounds->insert(call.function(AsciiString(name), a));
}
