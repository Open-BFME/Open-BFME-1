// cl: /O2 /D_STLP_USE_STATIC_LIB /Ivendor/stlport
// stlport
// Converted from Code/gen_asm/d_00140de0.asm at retail RVA 0x001415D0.
// The ThingTemplate.cpp caller and the ModuleInfo method name identify this
// body. The 20-byte Nugget layout and STLport vector erase reproduce its calls.

#include <string.h>
#include <vector>

#pragma intrinsic(memcmp)

typedef bool Bool;
typedef int Int;

struct BfmeStringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_len;
	unsigned short m_pad;
};

template <class T>
class StringBase
{
public:
	void set(const StringBase<T> &source);
	void *m_data;
};

class AsciiString
{
public:
	Int compare(const AsciiString &that) const
	{
		Int thatLen = that.m_data ? that.m_data->m_len : 0;
		const char *thatData = that.m_data
			? reinterpret_cast<const char *>(that.m_data) + 8 :
			reinterpret_cast<const char *>(0x0107388B);
		Int thisLen = m_data ? m_data->m_len : 0;
		const char *thisData = m_data
			? reinterpret_cast<const char *>(m_data) + 8 :
			reinterpret_cast<const char *>(0x0107388B);
		Int count = thisLen < thatLen ? thisLen : thatLen;
		Int result = memcmp(thisData, thatData, count);
		if (result != 0)
			return result;
		return thisLen - thatLen;
	}

	AsciiString &operator=(const AsciiString &source)
	{
		((StringBase<char> *)this)->set(
			*(const StringBase<char> *)&source);
		return *this;
	}

	BfmeStringData *m_data;
};

inline Bool operator==(const AsciiString &left, const AsciiString &right)
{
	return left.compare(right) == 0;
}

class Rva001417F0ModuleInfo
{
public:
	struct Nugget
	{
		AsciiString first;
		AsciiString m_moduleTag;
		const void *second;
		Int interfaceMask;
		Bool copiedFromDefault;
		Bool inheritable;

		Nugget(const AsciiString &n, const AsciiString &moduleTag,
			const void *d, Int i, Bool inh)
			: first(n), m_moduleTag(moduleTag), second(d), interfaceMask(i),
			  copiedFromDefault(false), inheritable(inh)
		{
		}
		~Nugget();
	};
};

class ModuleInfo
{
private:
	typedef Rva001417F0ModuleInfo::Nugget Nugget;
	std::vector<Nugget> m_info;

public:
	Bool clearModuleDataWithTag(const AsciiString &tagToClear,
		AsciiString &clearedModuleNameOut);
};

Bool ModuleInfo::clearModuleDataWithTag(const AsciiString &tagToClear,
	AsciiString &clearedModuleNameOut)
{
	Bool cleared = false;
	for (std::vector<Nugget>::iterator it = m_info.begin();
		it != m_info.end(); )
	{
		if (it->m_moduleTag == tagToClear)
		{
			clearedModuleNameOut = it->first;
			it = m_info.erase(it);
			cleared = true;
		}
		else
		{
			++it;
		}
	}
	return cleared;
}
