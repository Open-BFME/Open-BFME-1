// ?resize@?$hashtable@URva00461250Value@@VAsciiString@@U?$hash@VAsciiString@@@rts@@URva00461250ExtractKey@@U?$equal_to@VAsciiString@@@_STL@@V?$allocator@URva00461250Value@@@7@@_STL@@QAEXI@Z
// The caller at 0x00461250 is the matching _M_insert specialization.
// Its value has an AsciiString key and a four-byte mapped field, so this
// body is the STLport resize specialization for that table.
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "string_base.h"

#include "../../../../GameEngine/Include/Common/ScalarTypes.h"

extern "C" int __cdecl memcmp(const void *left, const void *right,
	unsigned int count);
#pragma intrinsic(memcmp)

class AsciiString
{
public:
	AsciiString(const AsciiString &other) : m_data(other.m_data) {}

	const char *str() const
	{
		return m_data.m_data ? &m_data.m_data->data[0] : "";
	}

	int compare(const AsciiString &other) const
	{
		const int otherLength = other.m_data.m_data
			? other.m_data.m_data->length : 0;
		const char *otherText = other.m_data.m_data
			? &other.m_data.m_data->data[0] : "";
		const int length = m_data.m_data ? m_data.m_data->length : 0;
		const char *text = m_data.m_data ? &m_data.m_data->data[0] : "";
		const int result = memcmp(text, otherText,
			length < otherLength ? length : otherLength);
		if (result != 0)
			return result;
		return length - otherLength;
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

template <>
struct hash<AsciiString>
{
	unsigned int operator()(AsciiString value) const
	{
		return static_cast<unsigned int>(_STL::__stl_hash_string(value.str()));
	}
};
}

struct Rva00461250Value
{
	AsciiString m_key;
	Int m_mapped;
};

struct Rva00461250ExtractKey
{
	const AsciiString &operator()(const Rva00461250Value &entry) const
	{
		return entry.m_key;
	}
};

typedef _STL::hashtable<Rva00461250Value, AsciiString,
	rts::hash<AsciiString>, Rva00461250ExtractKey,
	_STL::equal_to<AsciiString>, _STL::allocator<Rva00461250Value> >
	Rva00461250Table;

template void Rva00461250Table::resize(unsigned int);

// retail 0x006A4E70: AudioManager::m_allAudioEventInfo, Zero Hour's AudioEventInfoHash
// (ilt_oracle CONFIRMED at ILT 0x0001CBED; see AudioEventInfoHash.cpp).
class AudioEventInfo;

namespace rts
{
template <class T>
struct equal_to
{
	bool operator()(const T &left, const T &right) const { return left == right; }
};
}

typedef _STL::pair<const AsciiString, AudioEventInfo *> AudioEventInfoHashValue;

typedef _STL::hashtable<AudioEventInfoHashValue, AsciiString,
	rts::hash<AsciiString>, _STL::_Select1st<AudioEventInfoHashValue>,
	rts::equal_to<AsciiString>, _STL::allocator<AudioEventInfoHashValue> >
	AudioEventInfoHashTable;

template void AudioEventInfoHashTable::resize(unsigned int);
