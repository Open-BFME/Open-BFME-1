// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport

// Open-BFME: hash_map<AsciiString, Rva00692D50Mapped *>::hashtable::erase,
// retail 0x00692D50, 154 bytes; byte-twin of AsciiStringParticleHashErase.cpp (tools/twin_scan.py), the mapped type is address-derived.  The body is the iterator unlink path for the
// particle-template table; its bucket-number helper is the same out-of-line
// _M_bkt_num_key pinned by the neighboring hash-table bodies.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

typedef int Int;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

class Rva00692D50Mapped;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other) : m_string(other.m_string) {}

	int compare(const AsciiString &str) const
	{
		const int len = str.m_string.m_data ? str.m_string.m_data->length : 0;
		const char *data = str.m_string.m_data ? &str.m_string.m_data->data[0] : "";
		const int myLen = m_string.m_data ? m_string.m_data->length : 0;
		const char *myData = m_string.m_data ? &m_string.m_data->data[0] : "";
		const int result = memcmp(myData, data, myLen < len ? myLen : len);
		if (result != 0) {
			return result;
		}
		return myLen - len;
	}

	StringBase<char> m_string;
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return left.compare(right) == 0;
}

namespace rts
{
template <class T>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/STLTypedefs.h
struct hash
{
	unsigned int operator()(T value) const; // ILT 0x0000EC91
};
}

typedef _STL::pair<const AsciiString, Rva00692D50Mapped *> Rva00692D50ParticlePair;
typedef _STL::hashtable<Rva00692D50ParticlePair, AsciiString, rts::hash<AsciiString>,
	_STL::_Select1st<Rva00692D50ParticlePair>, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva00692D50ParticlePair> > Rva00692D50ParticleHashtable;

template void Rva00692D50ParticleHashtable::erase(const Rva00692D50ParticleHashtable::const_iterator &);
