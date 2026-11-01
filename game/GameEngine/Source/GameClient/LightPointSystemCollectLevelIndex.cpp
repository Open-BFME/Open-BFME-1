// cl: /EHsc /MD /O2 /GR- /EHsc- /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x0039CB60 (314 bytes), between LightPointSystem::addLevel and
// INI::parseLightPointLevel and called once from bfmeGoBRB.  It finds the
// LightPointSystem level (final override) whose name matches and records its
// index in a unique-integer store, inlining the store's matched add
// (0x0039C8C0).  The method is not proven, so it keeps the address.

#include <cstring>

// Retail reaches memmove through its MSVCR71 import slot (`ff 15`, IAT
// 0x0135945C); /MD's <string.h> declares it dllimport, so the call binds to
// __imp__memmove.
#include <string.h>
#include <vector>

#include "ascii_string.h"

// Retail AsciiString::compare shape (repe cmpsb over the shared prefix, then
// the length difference), spelled as the StringBase<char> specialization so
// this TU emits no AsciiString::compare COMDAT of its own. Same spelling as
// game/GameEngine/Source/GameNetwork/Rva00692570KeyLess.cpp.
template <> inline int StringBase<char>::compare(const StringBase<char> &str) const
{
	int otherLength = str.m_data ? str.m_data->length : 0;
	const char *otherData = str.m_data ? str.m_data->data : (const char *)"";
	int length = m_data ? m_data->length : 0;
	const char *data = m_data ? m_data->data : (const char *)"";
	int result = memcmp(data, otherData, length < otherLength ? length : otherLength);
	return result ? result : length - otherLength;
}

struct Gen_t_000bbe70_m4pod { int a[1]; };
bool operator==(const Gen_t_000bbe70_m4pod &, const Gen_t_000bbe70_m4pod &);
bool operator<(const Gen_t_000bbe70_m4pod &, const Gen_t_000bbe70_m4pod &);

namespace _STL
{
template <> struct __type_traits<Gen_t_000bbe70_m4pod> : __type_traits_aux<1> {};
}

class BfmeUniqueIntegerStoreC8C0
{
public:
	char m_bfmePrefix[8];
	_STL::vector<Gen_t_000bbe70_m4pod> m_values;
};

static __forceinline void addLightPointLevelIndex(BfmeUniqueIntegerStoreC8C0 *store, int value)
{
	Gen_t_000bbe70_m4pod *at = store->m_values.begin();
	Gen_t_000bbe70_m4pod *end = store->m_values.end();
	while (at != end)
	{
		if (at->a[0] == value)
			return;
		++at;
	}
	Gen_t_000bbe70_m4pod *item = (Gen_t_000bbe70_m4pod *)&value;
	store->m_values.push_back(*item);
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	// A visible out-of-line body lets MSVC keep the name's data across the
	// call, as retail does; the call itself still binds to the pinned ILT.
	__declspec(noinline) Overridable *friend_getFinalOverride()
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

	// Call-site walk: one retail inlined level, deeper recursion in the
	// non-const friend_getFinalOverride ILT 0x00048C61 (ilt_oracle
	// CONFIRMED; the const twin is a different body, 0x000978A0).
	const Overridable *finalOverrideViaConstFriend() const
	{
		const Overridable *next = m_nextOverride;
		if (next)
			return const_cast<Overridable *>(next)->friend_getFinalOverride();
		return this;
	}

private:
	void *m_vtable;
	Overridable *m_nextOverride;
};

class LightPointLevel : public Overridable
{
public:
	unsigned char m_pad08[0x0c - 0x08];
	AsciiString m_name;
};

class LightPointSystem
{
public:
	void rva0039CB60(BfmeUniqueIntegerStoreC8C0 *indices, const AsciiString &name);

private:
	char m_pad[8];
	_STL::vector<LightPointLevel *> m_levels;
};

// ?rva0039CB60@LightPointSystem@@QAEXPAVBfmeUniqueIntegerStoreC8C0@@ABVAsciiString@@@Z
void LightPointSystem::rva0039CB60(BfmeUniqueIntegerStoreC8C0 *indices, const AsciiString &name)
{
	for (unsigned int i = 0; i < m_levels.size(); ++i)
	{
		const LightPointLevel *level = (const LightPointLevel *)m_levels[i]->finalOverrideViaConstFriend();
		if (level->m_name.StringBase<char>::compare(name) == 0)
		{
			addLightPointLevelIndex(indices, i);
			return;
		}
	}
}
