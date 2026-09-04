// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: clean reconstruction of the 0x0077BC20 one-name lookup.
//
// The owner name is not recovered: no named caller or pointer xref reaches
// this orphaned body.  Its proven layout is a 0x78-byte prefix followed by a
// vector of 0x14-byte ModuleInfo::Nugget records.  The record's first string
// is the lookup key; the remaining twelve-byte member and tail are zeroed in
// the temporary before it is copied into the vector.

#define _STLP_NO_EXCEPTIONS 1
#include <string.h>
#include <vector>

typedef int Int;

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);

typedef int (__cdecl *CompareFunction)(const char *, const char *);

static __forceinline CompareFunction getCompareFunction()
{
	return *reinterpret_cast<CompareFunction *>(0x0135933C);
}

template <typename T>
class StringBase
{
public:
	void set(const StringBase<T> &source);       // retail 0x00887C90

	void releaseBuffer();                       // retail 0x00887940

	void *m_data;
};

class AsciiString
{
public:
	AsciiString(const char *text);              // retail 0x00888BC0

	~AsciiString();                            // retail 0x00887940

	const AsciiString &operator=(const AsciiString &source)
	{
		m_string.set(source.m_string);
		return *this;
	}

	const char *str() const
	{
		if (m_string.m_data)
			return reinterpret_cast<const char *>(
				reinterpret_cast<const unsigned char *>(m_string.m_data) + 8);
		return reinterpret_cast<const char *>(0x0107388B);
	}

	int compareNoCase(const AsciiString &right) const
	{
		return _strcmpi(str(), right.str());
	}

private:
	StringBase<char> m_string;
};

class Rva00026AB2Vec12
{
public:
	~Rva00026AB2Vec12();                       // retail ILT 0x00026AB2

	void *m_start;
	void *m_finish;
	void *m_end;
};

class ModuleInfo
{
public:
	struct Nugget
	{
		Nugget() : first(reinterpret_cast<const char *>(0x0107301C))
		{
			m_strings.m_start = 0;
			m_strings.m_finish = 0;
			m_strings.m_end = 0;
			m_tail = 0;
		}

		Nugget(const Nugget &source);             // retail ILT 0x0004ABEC

		AsciiString first;
		Rva00026AB2Vec12 m_strings;
		Int m_tail;
	};
};

class Rva0077BC20Owner
{
public:
	ModuleInfo::Nugget *findOrCreateNugget(const AsciiString &name);

private:
	unsigned char m_prefix[0x78];
	_STL::vector<ModuleInfo::Nugget> m_info;
};

// ?findOrCreateNugget@Rva0077BC20Owner@@QAEPAVNugget@ModuleInfo@@ABVAsciiString@@@Z
ModuleInfo::Nugget *Rva0077BC20Owner::findOrCreateNugget(const AsciiString &name)
{
	ModuleInfo::Nugget *it = m_info.begin();
	CompareFunction compare = _strcmpi;
	if (it == m_info.end())
		goto create_nugget;
	for (; it != m_info.end(); ++it)
	{
		if (compare(it->first.str(), name.str()) == 0)
			return it;
	}

	create_nugget:
	ModuleInfo::Nugget *nugget = new ModuleInfo::Nugget;
	nugget->first = name;
	m_info.push_back(*nugget);
	delete nugget;

	return &m_info[m_info.size() - 1];
}
