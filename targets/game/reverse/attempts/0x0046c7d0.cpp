// ?lookup@Rva0046C7D0Owner@@QBEHPBD@Z
// partial score=0.3 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

typedef int Int;
typedef bool Bool;

extern "C" const char *__cdecl bfmeSkipLevelPrefix(const char *path);
extern "C" __declspec(dllimport) char *__cdecl strchr(const char *s, int c);

// AsciiString reused verbatim from the already-landed
// Code/Libraries/Source/WWVegas/WWLib/RvaHashFindAsciiString.cpp and
// Code/GameEngine/Source/Common/AsciiStringHashErase000D6560.cpp (both fold
// the same STLport hashtable<Value, AsciiString>::_M_find<AsciiString> shape
// against many differently-mapped tables); string_base.h grants AsciiString
// friend access to StringBase<char>'s private members, so the ctor-from-
// const-char* below calls the real StringBase<char>::StringBase(const char*)
// -- retail's thin 0x888BC0 body, also reached as BFMERetailAsciiString's
// ctor elsewhere (FileSystem_openFile.cpp) -- and the implicit destructor
// reaches StringBase<char>::~StringBase() (releaseBuffer) the same way.
extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

class AsciiString
{
public:
	AsciiString(const char *s) : m_data(s) {}
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
	unsigned int operator()(T value) const;
};
}

enum Rva0046C7D0Mapped
{
	RVA0046C7D0_MAPPED_PLACEHOLDER = 0
};

struct Rva0046C7D0Value
{
	AsciiString m_key;
	Rva0046C7D0Mapped m_mapped;
};

struct Rva0046C7D0ExtractKey
{
	const AsciiString &operator()(const Rva0046C7D0Value &entry) const { return entry.m_key; }
};

typedef _STL::hashtable<Rva0046C7D0Value, AsciiString, rts::hash<AsciiString>,
	Rva0046C7D0ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva0046C7D0Value> > Rva0046C7D0Hash;

class Rva0046C7D0Owner
{
public:
	int lookup(const char *pathIn) const;

private:
	unsigned char m_pad[0x6c];
	Rva0046C7D0Hash m_table;			// +0x6c
};

int Rva0046C7D0Owner::lookup(const char *pathIn) const
{
	const char *path = bfmeSkipLevelPrefix(pathIn);

	if (*path == 0)
		return 0;

	{
		AsciiString key(path);
		Rva0046C7D0Hash::const_iterator it = m_table.find(key);
		if (it != m_table.end())
			return it->m_mapped;
	}

	char *tilde = strchr(path, '~');
	if (tilde == 0)
		return 0;

	char *cut = tilde;
	if (cut[-1] == '/')
		--cut;

	char saved = *cut;
	*cut = 0;

	int result = 0;
	{
		AsciiString key2(path);
		Rva0046C7D0Hash::const_iterator it2 = m_table.find(key2);
		*cut = saved;
		if (it2 != m_table.end())
			result = it2->m_mapped;
	}

	return result;
}
