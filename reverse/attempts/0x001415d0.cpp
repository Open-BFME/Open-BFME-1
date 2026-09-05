// ?clearModuleDataWithTag@ModuleInfo@@QAE_NABVAsciiString@@AAV2@@Z
// partial score=0.95 date=2026-09-05
// cl: /DNDEBUG /MD
// Open-BFME: ModuleInfo::clearModuleDataWithTag at 0x001415D0.
// The retail record is 20 bytes. It stores two AsciiString handles, a data
// pointer, an interface mask, and two Boolean flags.

#include <string.h>

#pragma intrinsic(memcmp)

typedef bool Bool;
typedef int Int;
#define FALSE 0

template <class T>
class StringBase
{
public:
	void set(const StringBase<T> &source);
	void *m_data;
};

struct BfmeStringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_len;
	unsigned short m_pad;
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
		unsigned char m_strings[8];
		const void *second;
		Int interfaceMask;
		unsigned char m_flags[4];

		~Nugget();
	};
};

namespace _STL
{
struct random_access_iterator_tag
{
};

template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy(InputIterator first,
	InputIterator last,
	OutputIterator result,
	const random_access_iterator_tag &,
	Distance *);
}

class ModuleInfo
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
	};
	struct NuggetVector
	{
		Nugget *m_begin;
		Nugget *m_end;
		Nugget *m_capacity;

		Nugget *begin() { return m_begin; }
		Nugget *end() { return m_end; }
	};

	Bool clearModuleDataWithTag(const AsciiString &tagToClear,
		AsciiString &clearedModuleNameOut);

private:
	NuggetVector m_info;
};

Bool ModuleInfo::clearModuleDataWithTag(const AsciiString &tagToClear,
	AsciiString &clearedModuleNameOut)
{
	Bool cleared = FALSE;
	Nugget *it = m_info.begin();
	while (it != m_info.end())
	{
		if (it->m_moduleTag == tagToClear)
		{
			clearedModuleNameOut = it->first;
			Nugget *next = it + 1;
			if (next != m_info.end())
			{
				_STL::random_access_iterator_tag category;
				typedef Rva001417F0ModuleInfo::Nugget CopyNugget;
				_STL::__copy(reinterpret_cast<CopyNugget *>(next),
					reinterpret_cast<CopyNugget *>(m_info.end()),
					reinterpret_cast<CopyNugget *>(it), category, (int *)0);
			}
			--m_info.m_end;
			reinterpret_cast<Rva001417F0ModuleInfo::Nugget *>(m_info.end())->~Nugget();
			cleared = true;
		}
		else
		{
			++it;
		}
	}
	return cleared;
}
