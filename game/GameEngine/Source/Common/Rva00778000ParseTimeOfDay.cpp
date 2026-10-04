// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// The callback at retail RVA 0x00778000 parses a string, a time-of-day name,
// an integer, and a second string into the 44-byte S4 record vector at the
// owner's +0x6c field.  The constructor, destructor, and layout come from the
// matched S4 family at 0x00754590, 0x00753E80, and 0x007746E0.  The index list
// at 0x012A9FE0 contains NONE, MORNING, AFTERNOON, EVENING, NIGHT, and
// INTERPOLATE, which identifies the callback's parsed enum.

#include <string>
#include <vector>

typedef int Int;

extern "C" unsigned int __cdecl strlen(const char *text);
#pragma intrinsic(strlen);

class INI
{
public:
	const char *getNextTokenOrNull(const char *separators = 0);
	static Int scanIndexList(const char *token, const char *const *names);
	static Int scanInt(const char *token);
};

class S4Elem007746E0
{
public:
	S4Elem007746E0();
	~S4Elem007746E0();
	S4Elem007746E0 &operator=(const S4Elem007746E0 &other);
	_STL::string m_first;
	_STL::string m_second;
	_STL::string m_unused;
	Int m_unusedValue;
	Int m_value;
};

// The record vector's element type is retail's vector instantiation, which
// names a struct Rva00777E40Element; the copy the fast path makes at retail
// RVA 0x00039879 is an ILT thunk, so the copy constructor body is reached
// through that thunk instead of a mangled call of its own.
extern void j_00039879();

struct Rva00777E40Element
{
	char m_body[44];

	Rva00777E40Element(const Rva00777E40Element &other)
	{
		typedef void (Rva00777E40Element::*Fn)(const Rva00777E40Element &);
		union { void (*fn)(); Fn call; } u = { j_00039879 };
		(this->*u.call)(other);
	}
};

struct Rva00778000Owner
{
	char m_pad[0x6c];
	_STL::vector<Rva00777E40Element> m_records;
};

extern const char *const Rva00778000TimeOfDayNames[];

// ?Rva00778000Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva00778000Parse(INI *ini, void *instance, void *store, const void *userData)
{
	Rva00778000Owner *owner = (Rva00778000Owner *)instance;
	if (owner == 0)
		return;

	S4Elem007746E0 value;
	const char *key = ini->getNextTokenOrNull(0);
	if (key)
		value.m_first.assign(key, key + strlen(key));
	else
		value.m_first.assign("", "");

	const char *timeOfDay = ini->getNextTokenOrNull(0);
	if (timeOfDay)
		value.m_unusedValue = INI::scanIndexList(timeOfDay,
			Rva00778000TimeOfDayNames);
	else
		value.m_unusedValue = 0;

	const char *amount = ini->getNextTokenOrNull(0);
	if (amount)
		value.m_value = INI::scanInt(amount);
	else
		value.m_value = 0;

	const char *name = ini->getNextTokenOrNull(0);
	if (name)
		value.m_second.assign(name, name + strlen(name));
	else
		value.m_second.assign("", "");

	owner->m_records.push_back(*(const Rva00777E40Element *)&value);
}
