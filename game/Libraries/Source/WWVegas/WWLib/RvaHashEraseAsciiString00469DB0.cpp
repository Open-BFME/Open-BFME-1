// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
//
// Open-BFME: STLport hashtable erase(const AsciiString&) at retail 0x00469DB0.
// The neighbouring Rva00469FC0 insert and operator[] bodies identify the
// address-derived value and its extract-key functor.  Retail walks the bucket,
// unlinks matching nodes, destroys the pair, and returns the number removed.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "string_base.h"

typedef int Int;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other) : m_data(other.m_data) {}

	int compare(const AsciiString &str) const
	{
		const int len = str.m_data.m_data ? str.m_data.m_data->length : 0;
		const char *data = str.m_data.m_data ? &str.m_data.m_data->data[0] : "";
		const int myLen = m_data.m_data ? m_data.m_data->length : 0;
		const char *myData = m_data.m_data ? &m_data.m_data->data[0] : "";
		const int result = memcmp(myData, data, myLen < len ? myLen : len);
		if (result != 0)
			return result;
		return myLen - len;
	}

	StringBase<char> m_data;
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return left.compare(right) == 0;
}

namespace rts
{
template <class T>
struct hash
{
	unsigned int operator()(T value) const; // ILT 0x0000EC91
};
}

struct Rva00469FC0Value
{
	AsciiString m_key;
	int m_mapped;
};

// Retail's erase cleanup call goes through ILT thunk 0x00042C8F (`j_00042c8f`),
// which routes to the value destructor body at 0x00042C8F.  STLport reaches that
// destructor through `_STL::_Destroy`, so the TU-local specialization below is
// the one place the thunk can be named; it carries the destructor signature
// (thiscall, void, no arguments) the way the erased node holds it.
extern void j_00042c8f();

namespace _STL
{
template <>
inline void _Destroy(Rva00469FC0Value *p)
{
	typedef void (Rva00469FC0Value::*Fn)();
	union { void (*fn)(); Fn call; } u = { j_00042c8f };
	(p->*u.call)();
}
}

struct Rva00469FC0ExtractKey
{
	const AsciiString &operator()(const Rva00469FC0Value &entry) const
	{
		return entry.m_key;
	}
};

typedef _STL::hashtable<Rva00469FC0Value, AsciiString, rts::hash<AsciiString>,
	Rva00469FC0ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva00469FC0Value> > Rva00469FC0HashTable;

template unsigned int Rva00469FC0HashTable::erase(const AsciiString &key);
