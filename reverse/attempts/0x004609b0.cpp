// ?erase@?$hashtable@URva00461360Value@@VAsciiString@@U?$hash@VAsciiString@@@rts@@URva00461360ExtractKey@@U?$equal_to@VAsciiString@@@_STL@@V?$allocator@URva00461360Value@@@7@@_STL@@QAEXABU?$_Ht_iterator@URva00461360Value@@U?$_Const_traits@URva00461360Value@@@_STL@@VAsciiString@@U?$hash@VAsciiString@@@rts@@URva00461360ExtractKey@@U?$equal_to@VAsciiString@@@3@V?$allocator@URva00461360Value@@@3@@2@@Z
// partial score=0.3 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
//
// 154B twin of AsciiStringParticleHashErase.cpp's
// hashtable<pair<const AsciiString, ParticleSystemTemplate *>, ...>::erase
// (retail 0x00614C50): byte-identical unlink-and-deallocate shape, but the
// node size pushed before _M_deallocate is 0x34 here (not 0xc), so the
// hashtable's mapped value is a 0x30-byte struct carrying the AsciiString
// key as its first member, not a bare pointer. Address-derived value/key
// types; the bucket-number and value-destructor callees are new
// address-derived pins reusing the existing addresses documented for this
// body's family (0x0003068E, 0x0003D2B7).

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef int Int;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other) : m_data(other.m_data) {}

private:
	char *m_data;
};

namespace rts
{
template <class T>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/STLTypedefs.h
struct hash
{
	unsigned int operator()(T value) const; // ILT 0x0000EC91
};
}

// Reusing the exact address-derived names from the existing
// ?_M_bkt_num_key@?$hashtable@URva00461360Value@@... pin (0x0003068E) so
// this erase's own bucket-number call resolves against it without a new pin.
struct Rva00461360Value
{
	AsciiString m_key;
	char m_rest[0x30 - 4];
};

struct Rva00461360ExtractKey
{
	const AsciiString &operator()(const Rva00461360Value &value) const { return value.m_key; }
};

typedef _STL::hashtable<Rva00461360Value, AsciiString, rts::hash<AsciiString>,
	Rva00461360ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva00461360Value> > Rva00461360Hashtable;

template void Rva00461360Hashtable::erase(const Rva00461360Hashtable::const_iterator &);
